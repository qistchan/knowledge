package com.ge.transportation.plm.mfg.operations;

import java.awt.Desktop;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Date;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellStyle;
import org.apache.poi.ss.usermodel.Font;
import org.apache.poi.ss.usermodel.IndexedColors;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import com.ge.transportation.plm.mfg.constants.Constants;

public class ReportStockBOMExcel 
{
	private static int iSlNo = 0;
	private static int rowCount = 0;
	static boolean startedExcelCreation = false;
	
	private static XSSFWorkbook workbook1;
	
	private static XSSFSheet SheetSummary;
	private static CellStyle style;
	private static CellStyle style1;
	private static CellStyle style2;
	private static CellStyle style3;
	private static Font font;
	private static Font font1;
	private static Font font2;
	private static Font font3;
	private static String currentTime;
	
	/**
	 * Constructor
	 * @param sprojName 
	 */
	public ReportStockBOMExcel ( String sprojName )
	{
		if ( startedExcelCreation == false )
		{
			startedExcelCreation = true;
		}
		else
		{
			createNewDialog ( "Already one report generation in still in progress. You can start new report, only once it is completed" );
			return;
		}
		
		workbook1 = new XSSFWorkbook();
		
		SheetSummary = workbook1.createSheet ( Constants.ReportStockBOM.BOMSTOCK );
		ReportStockBOMExcel.createSheet ( sprojName );
	}
	
	private static void createSheet(String sprojName) 
	{
		String sShortProjName = "";
		if ( sprojName.equals ( ( Constants.ReportStockBOM.GRR ) ) )
		{
			sShortProjName = Constants.ReportStockBOM.GRRID;
		}
		else if ( sprojName.equals ( ( Constants.ReportStockBOM.GRV) ) )
		{
			sShortProjName = Constants.ReportStockBOM.GRVID;
		}
		
		style = workbook1.createCellStyle();
		font = workbook1.createFont();
		font.setFontHeightInPoints ( ( short ) 12 );
		style.setFont(font); 
		
		style1 = workbook1.createCellStyle();
		font1 = workbook1.createFont();
		font1.setFontHeightInPoints( ( short ) 12 );
		style1.setFont(font1); 
		style1.setFillForegroundColor ( IndexedColors.GREY_50_PERCENT.getIndex() );
		
		style2 = workbook1.createCellStyle();
		font2 = workbook1.createFont();
		font2.setFontHeightInPoints ( ( short ) 12 );
		style2.setFont(font1); 
		style2.setFillForegroundColor ( IndexedColors.LIGHT_YELLOW.getIndex() );
		
		style3 = workbook1.createCellStyle();
		font3 = workbook1.createFont();
		font3.setFontHeightInPoints ( ( short ) 12 );
		style3.setFont(font1); 
		style3.setFillForegroundColor ( IndexedColors.GREY_25_PERCENT.getIndex() );
		
		Row row0 = SheetSummary.createRow ( 0 );
		Cell cell0 = row0.createCell ( 0 );
		cell0.setCellValue ( Constants.ReportStockBOM.HOME );
		cell0.setCellStyle ( style );
		
		Cell cellA = row0.createCell ( 1 );
		cellA.setCellValue ( Constants.ReportStockBOM.LEVEL );
		cellA.setCellStyle ( style );
		
		Cell cell1 = row0.createCell ( 2 );
		cell1.setCellValue ( Constants.ReportStockBOM.BOMLINES );
		cell1.setCellStyle ( style );
		
		Cell cell2 = row0.createCell( 3 );
		cell2.setCellValue ( Constants.ReportStockBOM.QTY );
		cell2.setCellStyle ( style );
		
		Cell cell3 = row0.createCell ( 4 );
		cell3.setCellValue ( Constants.ReportStockBOM.FINDNO );
		cell3.setCellStyle ( style );
		
		Cell cell4 = row0.createCell ( 5 );
		cell4.setCellValue ( Constants.ReportStockBOM.PACKCOUNTS );
		cell4.setCellStyle ( style );
		
		Cell cell5 = row0.createCell ( 6 );
		cell5.setCellValue ( Constants.ReportStockBOM.PARENTREVNAME );
		cell5.setCellStyle ( style );
		
		Cell cell6 = row0.createCell ( 7 );
		cell6.setCellValue ( Constants.ReportStockBOM.ITEMID );
		cell6.setCellStyle ( style );
		
		Cell cell7 = row0.createCell ( 8 );
		cell7.setCellValue ( Constants.ReportStockBOM.PARTNAMES );
		cell7.setCellStyle ( style );
		
		Cell cell8 = row0.createCell ( 9 );
		cell8.setCellValue ( Constants.ReportStockBOM.UOMS );
		cell8.setCellStyle ( style );
		
		Cell cell9 = row0.createCell ( 10 );
		cell9.setCellValue ( Constants.ReportStockBOM.REVS );
		cell9.setCellStyle ( style );
		
		Cell cell10 = row0.createCell ( 11 );
		cell10.setCellValue ( Constants.ReportStockBOM.STRCODES );
		cell10.setCellStyle ( style );
		
		Cell cell11 = row0.createCell ( 12 );
		cell11.setCellValue ( Constants.ReportStockBOM.ENGMAKEBUYS );
		cell11.setCellStyle ( style );
		
		Cell cell12 = row0.createCell ( 13 );
		cell12.setCellValue ( Constants.ReportStockBOM.RULECONF );
		cell12.setCellStyle ( style );
		
		Cell cell13 = row0.createCell ( 14 );
		cell13.setCellValue ( Constants.ReportStockBOM.RELSTAT );
		cell13.setCellStyle ( style );
		
		Cell cell14 = row0.createCell ( 15 );
		cell14.setCellValue ( sShortProjName  + Constants.ReportStockBOM.PROJMAKEBUYS );
		cell14.setCellStyle ( style );
		
		Cell cell15 = row0.createCell ( 16 );
		cell15.setCellValue ( Constants.ReportStockBOM.ITEMTYPE );
		cell15.setCellStyle ( style );
		
		Cell cell16 = row0.createCell ( 17 );
		cell16.setCellValue ( Constants.ReportStockBOM.ISMADEFROMPART );
		cell16.setCellStyle ( style );
		
	}

	/**
	 *   @param strValue
	 *   Method to update excel report for group change ownership.
	 */
	public static void writeExcel ( String strValue )
	{
		iSlNo = iSlNo + 1;
		String sSlNo = Integer.toString(iSlNo);
		try 
		{
			String splitPipeLne[] = strValue.split ( "\\?" );
			System.out.println ( "\nLength excel = " + splitPipeLne.length );
			
			if ( splitPipeLne.length == 17)
			{
				Row row = SheetSummary.createRow ( ++rowCount );
				Cell cell0 = row.createCell ( 0 );
				cell0.setCellValue ( sSlNo );
				cell0.setCellStyle ( style );
				
				Cell cellA = row.createCell ( 1 );
				cellA.setCellValue ( splitPipeLne[0] );
				cellA.setCellStyle ( style );
				
				Cell cell1 = row.createCell ( 2 );
				cell1.setCellValue ( splitPipeLne[1] );
				cell1.setCellStyle ( style );
				
				Cell cell2 = row.createCell ( 3 );
				cell2.setCellValue ( splitPipeLne[2] );
				cell2.setCellStyle ( style );
				
				Cell cell3 = row.createCell ( 4 );
				cell3.setCellValue ( splitPipeLne[3] );
				cell3.setCellStyle ( style );
				
				Cell cell4 = row.createCell ( 5 );
				cell4.setCellValue ( splitPipeLne[4] );
				cell4.setCellStyle ( style );
				
				Cell cell5 = row.createCell ( 6 );
				cell5.setCellValue ( splitPipeLne[5] );
				cell5.setCellStyle ( style );
				
				Cell cell6 = row.createCell ( 7 );
				cell6.setCellValue( splitPipeLne[6] );
				cell6.setCellStyle ( style );
				
				Cell cell7 = row.createCell ( 8 );
				cell7.setCellValue ( splitPipeLne[7] );
				cell7.setCellStyle ( style );
				
				Cell cell8 = row.createCell ( 9 );
				cell8.setCellValue ( splitPipeLne[8] );
				cell8.setCellStyle ( style );
				
				Cell cell9 = row.createCell ( 10 );
				cell9.setCellValue ( splitPipeLne[9] );
				cell9.setCellStyle ( style );
				
				Cell cell10 = row.createCell ( 11 );
				cell10.setCellValue ( splitPipeLne[10] );
				cell10.setCellStyle ( style );
				
				Cell cell11 = row.createCell ( 12 );
				cell11.setCellValue ( splitPipeLne[11] );
				cell11.setCellStyle ( style );
				
				Cell cell12 = row.createCell ( 13 );
				cell12.setCellValue ( splitPipeLne[12] );
				cell12.setCellStyle ( style );
				
				Cell cell13 = row.createCell ( 14 );
				cell13.setCellValue ( splitPipeLne[13] );
				cell13.setCellStyle ( style );
				
				Cell cell14 = row.createCell ( 15 );
				cell14.setCellValue ( splitPipeLne[14] );
				cell14.setCellStyle ( style );
				
				Cell cell15 = row.createCell ( 16 );
				cell15.setCellValue ( splitPipeLne[15] );
				cell15.setCellStyle ( style );
				
				Cell cell16 = row.createCell ( 17 );
				cell16.setCellValue ( splitPipeLne[16] );
				cell16.setCellStyle ( style );
				
			}
		}
		catch ( ArrayIndexOutOfBoundsException ex )
		{
			ex.printStackTrace();
			createNewDialog( ex.getMessage() );
			
			return;
		}
		catch ( Exception e ) 
		{
			e.printStackTrace();
			createNewDialog ( e.getMessage() );
			
			return;
		}
		
	}
	
	/**
	 *   @param strValue
	 *   Method to update close and save excel report file.
	 */
	public static void closeExcel() throws FileNotFoundException, IOException
	{
		setTime();
		String sSystemTemp = System.getProperty ( Constants.ReportStockBOM.TEMPDIR );
		String summaryFileFullPath = sSystemTemp + currentTime + "MBOM_STOCKMTL_REPORT.xls";
		FileOutputStream outputStream = new FileOutputStream ( new  File ( summaryFileFullPath ) );
	    workbook1.write(outputStream);
	    outputStream.close();
	    rowCount = 0;
		iSlNo = 0;
		
		/** Opening Excel File From Java **/
		try 
        {
            Desktop.getDesktop().open ( new File ( summaryFileFullPath ) );
            System.out.println ( "\nReport Generated Successfully" );
            startedExcelCreation = false;
            
        } 
        catch (IOException e) 
        {
        	e.printStackTrace();
        	createNewDialog ( e.getMessage() );
        	
        	return;
        }
	}
	
	/**
	 *   @param void
	 *   Method to get system  date and time .
	 */
	public static void setTime() 
	{
		try 
		{
			DateFormat dateFormat = new SimpleDateFormat ( "dd-MMM-yyyy_HHmmss" );
			Date date = new Date();
			currentTime = dateFormat.format ( date );
		} 
		catch ( Exception e ) 
		{
			e.printStackTrace();
			createNewDialog ( e.getMessage() );
			
			return;
		}
	}
	
	public static void createNewDialog ( String Message )
	{
		Display display = new Display();
	    Shell shell = new Shell ( display );
	    shell.setText ( "Shell" );
	    shell.setSize(200, 200);
	    
	    MessageDialog.openError ( shell, "Error", "Report Generation Failed." +  Message );
	   
	    while ( !shell.isDisposed() ) 
	    {
	      if ( !display.readAndDispatch() )
	      {
	        display.sleep();
	      }
	    }
	    display.dispose();
	}
}
