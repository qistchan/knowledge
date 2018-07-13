/* STARTFILEDOC ***
//===========================================================================
//Filename:   GET_CASDataDownload.java
//Purpose:   Class for getting the disposition data from VAX and export it as excel file
//
//History:
// Who                   Date                      Description
//TCS Development Team     22 August, 2017         Initial creation
//
//============================================================================
*/

//==== Package  ===============================================================

package com.get.casDataDownloader.model;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Properties;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.commons.net.ftp.FTP;
import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPReply;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.poi.ss.usermodel.BorderStyle;
import org.apache.poi.ss.usermodel.DataValidation;
import org.apache.poi.ss.usermodel.FillPatternType;
import org.apache.poi.ss.usermodel.Footer;
import org.apache.poi.ss.usermodel.HorizontalAlignment;
import org.apache.poi.ss.usermodel.IndexedColors;
import org.apache.poi.ss.util.CellRangeAddress;
import org.apache.poi.ss.util.CellRangeAddressList;

import com.get.casDataDownloader.logger.GETLogger;

import org.apache.poi.hssf.usermodel.DVConstraint;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFDataValidation;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;

import org.apache.poi.hpsf.HPSFException;
/**
* Servlet implementation class GET_CASDataDownload
*/
@WebServlet("/GET_CASDataDownload")
public class GET_CASDataDownload extends HttpServlet
{
    private static final long serialVersionUID = 1L;    
    static Properties prop = new Properties();
    InputStream inputProperties = null;
    private static final String EXCEL_FILE_EXT = ".xls";    
    private static final String EXCEL_FILE_EXT_DISP = "_Disposition";

    private static final String CONFIG_FILE = "config.properties";
    private static final String CONFIG_FTP_USER_ATTR = "FTPUser";
    private static final String CONFIG_FTP_PASSWORD_ATTR = "FTPPassword";
    private static final String CONFIG_FTP_DIRECTORY_ATTR = "FTPDirectory";
    private static final String CONFIG_FTP_FTP_ATTR = "FTP";
    private static final String CONFIG_SERVER_TEMP_DIR_ATTR = "LocalTempDir";
    private static final String CONFIG_DISPINST_ATTR = "DispositionInst";
    private static final String CONFIG_DISPVALUES_ATTR = "DispositionValues";

    private static final String REQUEST_ITEMID_ATTR = "ID";
    private static final String DAT_FILE_EXT = ".dat";

    private static final String MIME_TYPE_VALUE = "application/octet-stream";
    private static final String HEADER_KEY = "Content-Disposition";
    private static final String ACTHID_M = "M";
    private static final String ACTHID_C = "C";
    private static final String DISPOSITIONSPLIT_DELIMITER = "\\|";
    private static final String DIRSEPARATOR = "//";
    private static final String FTPSEPARATOR = "/";

    private static final String EXCEL_HEADER_ACTION = "Action";
    private static final String EXCEL_HEADER_GROUP = "Group";
    private static final String EXCEL_HEADER_ITEMNO = "Item No ";
    private static final String EXCEL_HEADER_ZONE = "Zone ";
    private static final String EXCEL_HEADER_IDENTNO = "Ident No ";
    private static final String EXCEL_HEADER_DESCNOMECL = "Descr/Nomenclature";
    private static final String EXCEL_HEADER_UNITQTY = "UnitQty";
    private static final String EXCEL_HEADER_UM = "U/M";
    private static final String EXCEL_HEADER_DISPCODE = "DispositionCode";
    private static final String EXCEL_HEADER_MISCINFO = "MiscInfo ";
    private static final String EXCEL_CAS_SHEET = "CAS Data";
    private static final String EXCEL_GE_INSPIRA_PITCH_FONT = "GE Inspira Pitch";
    private static final String EXCEL_GE_FOOTER = "GE CONFIDENTIAL";

    FTPClient ftpClient = new FTPClient();
    private  static Logger logger;
    
    /**
    *  Method to connect to VAX using FTP and get the file
    */
    protected void doGet( HttpServletRequest httpRequest, HttpServletResponse httpResponse ) throws ServletException, IOException 
    {
       GETLogger.initLogger( GET_CASDataDownload.class );
       logger = GETLogger.getCurrentLogger();
       try 
       {
           // get the configuration properties file
           inputProperties = getClass().getClassLoader().getResourceAsStream( CONFIG_FILE );
    
           // load a properties file
           prop.load( inputProperties );
    
           String sUserID = prop.getProperty( CONFIG_FTP_USER_ATTR );
           String sPassword = prop.getProperty( CONFIG_FTP_PASSWORD_ATTR );
           String sFtpDir = prop.getProperty( CONFIG_FTP_DIRECTORY_ATTR );
           String sInputFile = httpRequest.getParameter( REQUEST_ITEMID_ATTR );
           System.out.println( sInputFile );
           logger.debug( "Item ID = " + sInputFile );
          
           if(sInputFile.length()<3)
           {
               httpRequest.setAttribute("errorMsg", "No file found. Please enter a valid ID and try again.");
               RequestDispatcher requestdispatch = httpRequest.getRequestDispatcher("/GET_CASDataDownload.jsp");  
               requestdispatch.include(httpRequest, httpResponse);
               return;
           }
           
           if( sInputFile.contains(DAT_FILE_EXT) == false )
           {
               sInputFile = sInputFile.concat(DAT_FILE_EXT);
           }
           // pass directory path on server to connect
           ftpClient.connect( prop.getProperty( CONFIG_FTP_FTP_ATTR ) );
           showServerReply();
    
           int replyCode = ftpClient.getReplyCode();
           if ( !FTPReply.isPositiveCompletion(replyCode) ) 
           {
               logger.error( "FTP Connection Failed" );
               httpRequest.setAttribute( "errorMsg", "FTP Connection Failed. Please enter a valid ID and try again." );
               RequestDispatcher requestdispatch = httpRequest.getRequestDispatcher("/GET_CASDataDownload.jsp");  
               requestdispatch.include( httpRequest, httpResponse );
               return;
           }
           // pass username and password, returned true if authentication is successful
           boolean success = ftpClient.login( sUserID, sPassword );
           showServerReply();
    
           if ( !success ) 
           {
               logger.error( "FTP: Could not login to the server. Check username and Pasword" );
               httpRequest.setAttribute( "errorMsg", "FTP Connection Failed. Could not retrive the file from CAS. Please contact the System Administrator." );
               RequestDispatcher requestdispatch = httpRequest.getRequestDispatcher("/GET_CASDataDownload.jsp");  
               requestdispatch.include( httpRequest, httpResponse );
               return;
           }
    
           ftpClient.enterLocalPassiveMode();
           ftpClient.setFileType( FTP.BINARY_FILE_TYPE );
           String remoteFile = sFtpDir + FTPSEPARATOR + sInputFile.toLowerCase();
           logger.debug( "RemoteFile is " + remoteFile );
           
           String sInputLoc = prop.getProperty( CONFIG_SERVER_TEMP_DIR_ATTR );
           logger.debug( "sInputLoc directory is " + sInputLoc );
           File downloadftpFile = new File( sInputLoc + DIRSEPARATOR + sInputFile );
           logger.debug( "DownloadFile is " + downloadftpFile );
           System.out.println("downloadftpFile: "+ downloadftpFile);
           
           // retrieve file from VAX
           OutputStream outputStream = new BufferedOutputStream( new FileOutputStream( downloadftpFile ) );
           success = ftpClient.retrieveFile( remoteFile, outputStream );
           outputStream.close();
           if ( success ) 
           {
               logger.info( "File " + sInputFile + " has been downloaded successfully." );

               readDatFile ( sInputLoc + sInputFile, httpRequest, httpResponse );
    
               //download the file to user location
               sInputFile = sInputFile.substring( 0, ( sInputFile.length() - 4 ) );
               System.out.println( "sInputFile: " + sInputFile );
               String filePath = sInputLoc + sInputFile.toLowerCase() + EXCEL_FILE_EXT_DISP + EXCEL_FILE_EXT;
               File downloadFile = new File( filePath );
               FileInputStream inStream = new FileInputStream( downloadFile );
               ServletContext context = getServletContext();
               String mimeType = context.getMimeType( filePath );
               
               if ( mimeType == null ) 
               {
                   //set to binary type if MIME mapping not found
                   mimeType = MIME_TYPE_VALUE;
               }
               
               logger.debug( "MIME type: " + mimeType );
               //modify the response
               httpResponse.setContentType( mimeType );
               httpResponse.setContentLength( (int) downloadFile.length() );
               //force the file to be downloaded
               String headerKey = HEADER_KEY;
               String headerValue = String.format( "attachment; filename=\"%s\"", downloadFile.getName() );
               httpResponse.setHeader( headerKey, headerValue );
               //obtains response's output stream
               OutputStream outStream = httpResponse.getOutputStream();
               
               byte[] buffer = new byte[4096];
               int bytesRead = -1;
               while ( (bytesRead = inStream.read(buffer)) != -1 ) 
               {
                   outStream.write( buffer, 0, bytesRead );
               }
               inStream.close();
               outStream.close();
           }
           else
           { 
               logger.error( "File " + sInputFile + " not found on VAX." );
               httpRequest.setAttribute( "errorMsg", "File " + sInputFile + " not found on VAX." + " Please contact the System Administrator." );
               RequestDispatcher requestdispatch = httpRequest.getRequestDispatcher("/GET_CASDataDownload.jsp");
               requestdispatch.include( httpRequest, httpResponse );
               downloadftpFile.delete();
           }
       } 
       catch (IOException ex) 
       {
           logger.error( "Error occured in the Servlet." );
           ex.printStackTrace();
       }
       finally 
       {
           if ( inputProperties != null ) 
           {
               try 
               {
                   inputProperties.close();
                   if (ftpClient.isConnected()) 
                   {
                       ftpClient.logout();
                       ftpClient.disconnect();
                   }
               } 
               catch (IOException e) 
               {
                   e.printStackTrace();
               }
           }
       }
    }    
    
    // method to display the FTP server replies
    
    private void showServerReply()
    {
       String[] replies = ftpClient.getReplyStrings();
       if ( replies != null && replies.length > 0 ) 
       {
           for (String aReply : replies) 
           {
               logger.info("SERVER: " + aReply);
           }
       }
    }
    
    // Method to read the Data file and format the strings to write into Excel
    
    private void readDatFile( String sFilename, HttpServletRequest request, HttpServletResponse response ) throws IOException, ServletException
    {
       List<String> lsRecords = new ArrayList<String>();
       ArrayList<String> sList = new ArrayList<String>();
       String sLine = null;
       BufferedReader reader = null;
    
       try
       {
           reader = new BufferedReader( new FileReader( sFilename ) );
         
           while ( (sLine = reader.readLine() ) != null )
           {
                  lsRecords.add( sLine );
           }
         
           logger.debug( "Number of rows in dat file = " + lsRecords.size() );
           for ( int iJnx= 0; iJnx < lsRecords.size(); iJnx++ )
           {
               logger.debug( "records get = " + lsRecords.get(iJnx) );
               // set the length of StringBuilder to 5
               String srecords =  lsRecords.get( iJnx );
               //*Fourth column is zone information. It is always empty when we get it from cas.
               /* Ninth column is disposition. It will be empty when we get it
               from CAS*/
               logger.debug( "srecords get = " + srecords.length() );
    
               srecords.substring(0, 11);
               sList.add(srecords.substring(64, 65));//action
               sList.add(srecords.substring(11, 15)); //group
               sList.add(srecords.substring(48, 52));//item
    
               sList.add(""); //Zone
    
               sList.add(srecords.substring(33, 48));//sID
               sList.add(srecords.substring(15, 25)); //desc
               String sUom = srecords.substring(52, 64);
               sUom = sUom.replaceFirst("^0+(?!$)", "");
               Float.parseFloat(sUom);
               sList.add(sUom);//unit
    
               String sActhld = srecords.substring(65, 66);
    
               logger.debug( "sActhld get = " + sActhld );
    
               sList.add(srecords.substring(78, 80));//uom
    
               sList.add(" ");//disp
    
               if( sActhld.compareToIgnoreCase(ACTHID_M) == 0 )
               {
                   sActhld = ACTHID_C;
                   sList.add( srecords.substring(25, 33) );//misc
               }
               else
               {
                   String sMisc = " ";
                   sList.add( sMisc );
               } 
           }    
           exportDashboardNew( sList, sFilename, lsRecords, request, response );
       }
       catch (Exception e)
       {
           logger.error( "Exception occurred trying to read " + sFilename );
           e.printStackTrace();
           request.setAttribute( "errorMsg", "Exception occurred while trying to read downloaded dat file. Please contact System Administrator." );
           RequestDispatcher requestdispatch=request.getRequestDispatcher("/GET_CASDataDownload.jsp");  
           requestdispatch.include(request, response);
       }
       finally 
       {
           if ( reader != null ) 
           {
               reader.close();
           }
       }
    }
    
    //@Override
    // Method to create excel file with the CAS data
    
    public void exportDashboardNew( ArrayList<String> listOfContents, String sInputFile, List<String> records, HttpServletRequest request, 
                                       HttpServletResponse response ) throws FileNotFoundException, IOException, ServletException 
    {
       int rowIdx = 0;
       short cellIdx = 0;
       HSSFCell cell = null;
       ArrayList<String> header = new ArrayList<String>();

       sInputFile = sInputFile.substring( 0,(sInputFile.length()-4) );//41a113519al
       String sHeaderMsg = prop.getProperty(CONFIG_DISPINST_ATTR);
       header.add(EXCEL_HEADER_ACTION);
       header.add(EXCEL_HEADER_GROUP);
       header.add(EXCEL_HEADER_ITEMNO);
       header.add(EXCEL_HEADER_ZONE);
       header.add(EXCEL_HEADER_IDENTNO);
       header.add(EXCEL_HEADER_DESCNOMECL);
       header.add(EXCEL_HEADER_UNITQTY);
       header.add(EXCEL_HEADER_UM);
       header.add(EXCEL_HEADER_DISPCODE);
       header.add(EXCEL_HEADER_MISCINFO);

       //Create new excel file
       FileOutputStream out = new FileOutputStream( sInputFile.toLowerCase() + EXCEL_FILE_EXT_DISP + EXCEL_FILE_EXT );
       //Create new workbook
       HSSFWorkbook workbook = new HSSFWorkbook();
       //create new sheet
       HSSFSheet workSheet = workbook.createSheet(EXCEL_CAS_SHEET);
    
       //header disposition message       
       HSSFCellStyle cellStyleHeader = workbook.createCellStyle();
       HSSFFont headerFont = workbook.createFont();
       HSSFRow row = workSheet.createRow(rowIdx);
       workSheet.addMergedRegion( new CellRangeAddress(0,0,0,15) );

       cellStyleHeader.setAlignment( HorizontalAlignment.CENTER );
       cellStyleHeader.setBorderTop( BorderStyle.THIN );
       cellStyleHeader.setBorderBottom( BorderStyle.THIN );
       cellStyleHeader.setBorderRight( BorderStyle.THIN );
       cell = row.createCell((short)0);
       cell.setCellValue( sHeaderMsg );
       cell.setCellStyle( cellStyleHeader );

       cellStyleHeader.setWrapText( true );

       rowIdx = 1;
       // Header
       HSSFCellStyle cellStyleHdr = workbook.createCellStyle();
       HSSFRow hssfHeader = workSheet.createRow(rowIdx);
       headerFont.setColor( IndexedColors.DARK_RED.getIndex() );
       cellStyleHdr.setAlignment(HorizontalAlignment.CENTER);
       cellStyleHdr.setBorderTop(BorderStyle.THIN);
       cellStyleHdr.setBorderBottom(BorderStyle.THIN);
       cellStyleHdr.setBorderRight(BorderStyle.THIN);
   
       headerFont.setFontName( EXCEL_GE_INSPIRA_PITCH_FONT );
       headerFont.setFontHeightInPoints((short) 11);
       headerFont.setBold( true );
       cellStyleHdr.setFont( headerFont );
       cellStyleHdr.setFillForegroundColor( HSSFColor.HSSFColorPredefined.LIGHT_CORNFLOWER_BLUE.getIndex() );
       cellStyleHdr.setFillPattern( FillPatternType.SOLID_FOREGROUND );
       HSSFFont dataFont = workbook.createFont();
       dataFont.setFontName( EXCEL_GE_INSPIRA_PITCH_FONT );
       dataFont.setFontHeightInPoints((short) 10);

       for ( Iterator<String> cells = header.iterator(); cells.hasNext(); )
       {
           HSSFCell hssfCell = hssfHeader.createCell( cellIdx++ );
           hssfCell.setCellStyle( cellStyleHdr );
           workSheet.autoSizeColumn( cellIdx );
           hssfCell.setCellValue( (String) cells.next() );
       }
       cellStyleHdr.setWrapText( true );

       // Data
       rowIdx = 2;
       HSSFCellStyle cellStyle = workbook.createCellStyle();

       short contentPosition = 0;
       for ( short rows = (short) 0; rows < records.size(); rows ++ )
       {
           HSSFRow hssfRow = workSheet.createRow( rowIdx++ );
           cellIdx = 0;
           for ( short cellnum = (short) 0; cellnum < 10; cellnum ++ )
           {
               HSSFCell hssfCell = hssfRow.createCell(cellIdx++);
               hssfCell.setCellStyle(cellStyle);
               workSheet.autoSizeColumn(cellnum);
               hssfCell.setCellValue( listOfContents.get(contentPosition));
               contentPosition++;
           }
       } 
       rowIdx--;
    
       String sDispositionValues = prop.getProperty( CONFIG_DISPVALUES_ATTR );
       String [] sDisposition = sDispositionValues.split( DISPOSITIONSPLIT_DELIMITER );
       CellRangeAddressList addressList = new CellRangeAddressList( 1, rowIdx, 8, 8 );
       DVConstraint dvConstraint = DVConstraint.createExplicitListConstraint( sDisposition );
       DataValidation dataValidation = new HSSFDataValidation( addressList, dvConstraint );
       dataValidation.setSuppressDropDownArrow( false );
       workSheet.addValidationData( dataValidation );
       cellStyle.setAlignment(HorizontalAlignment.CENTER);
       cellStyle.setBorderTop(BorderStyle.THIN);
       cellStyle.setBorderBottom(BorderStyle.THIN);
       cellStyle.setBorderRight(BorderStyle.THIN);
       cellStyle.setFillForegroundColor( HSSFColor.HSSFColorPredefined.AQUA.getIndex() );
       cellStyleHdr.setFillPattern( FillPatternType.SOLID_FOREGROUND );
       try
       { 
           workbook.write( out );
           System.out.println(" Excel created ");
           logger.debug( "Excel created successfully" );
           String text = EXCEL_GE_FOOTER;
           Footer footer = workSheet.getFooter();
           footer.setLeft(text); 
           workbook.write(out);
           workbook.close();
       }
       catch (IOException e) 
       {
           try 
           {
               request.setAttribute("errorMsg", "Could not generate the Excel format. Please contact System Administrator.");
               RequestDispatcher requestdispatch = request.getRequestDispatcher("/GET_CASDataDownload.jsp");  
               requestdispatch.include( request, response );
               throw new HPSFException(e.getMessage());
           } 
           catch (HPSFException e1) 
           {
               e1.printStackTrace();
           }
       }
       finally
       {
           if ( out != null )
           {
               out.close();
           }
       }
    }
}

