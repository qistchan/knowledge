package com.ge.transportation.plm.sbom.common;

import java.io.FileNotFoundException;
import java.util.Date;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

import org.apache.poi.hssf.util.HSSFColor;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellStyle;
import org.apache.poi.ss.usermodel.FillPatternType;
import org.apache.poi.ss.usermodel.Font;
import org.apache.poi.ss.usermodel.IndexedColors;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import com.ge.transportation.plm.sbom.constants.Constants;

/* excel */

public class ReportExcel 
{
	private static int rowCountServicePartCr = 0;
	private static int rowCountServicePartFormUpdate = 0;
	private static int rowCountEnggPartFormCr = 0;
	private static int rowCountAlternatepartsUpdate = 0;
	private static int rowCountServicePartRelations = 0;
	private static int rowCountChangeOwnership = 0;
	private static int rowCountStr = 0;
	private static int rowCountSummar = 0;
	
	private static XSSFWorkbook workbook;
	private static XSSFSheet sheetServicePartCr;
	private static XSSFSheet sheetServicePartFormUpd;
	private static XSSFSheet sheetEnggPartFormCr;
	private static XSSFSheet sheetServiceAltrPartUpd;
	private static XSSFSheet sheetServicePartReln;
	private static XSSFSheet sheetServicePartOwnerChange;
	private static XSSFSheet sheetStr;
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
	 */
	public ReportExcel ()
	{
		workbook = new XSSFWorkbook();
		
		SheetSummary = workbook.createSheet(Constants.sbomConstants.SUMMARY_SHEET);
		ReportExcel.createSummarySheet();
		
		sheetServicePartCr = workbook.createSheet(Constants.sbomConstants.SERVICE_PART_CREATION_SHEET);
		createHeadline(sheetServicePartCr,rowCountServicePartCr);
		
		sheetServicePartFormUpd = workbook.createSheet(Constants.sbomConstants.SERVICE_PART_FORM_UPDATE);
		createHeadline(sheetServicePartFormUpd,rowCountServicePartFormUpdate);
		
		sheetEnggPartFormCr = workbook.createSheet(Constants.sbomConstants.ENGG_PART_FORM_SHEET);
		createHeadline(sheetEnggPartFormCr,rowCountEnggPartFormCr);
		
		sheetServiceAltrPartUpd = workbook.createSheet(Constants.sbomConstants.SERVICE_PART_ALTER_SHEET);
		createAltSheet();
		
		sheetServicePartReln = workbook.createSheet(Constants.sbomConstants.SERVICE_PART_RELN_SHEET);
		createRelnSheet();
		
		sheetServicePartOwnerChange = workbook.createSheet(Constants.sbomConstants.SERVICE_PART_OWNNERSHIP_SHEET);
		createHeadline(sheetServicePartOwnerChange,rowCountChangeOwnership);
		
		sheetStr = workbook.createSheet(Constants.sbomConstants.SERVICE_ASSEMBLY_MIGRATION);
		ReportExcel.createStrSheet();
		
	}
	
	private static void createSummarySheet() 
	{
		style = workbook.createCellStyle();
		font = workbook.createFont();
		font.setFontHeightInPoints((short) 12);
		font.setBold(true);
		style.setFont(font); 
		
		style1 = workbook.createCellStyle();
		font1 = workbook.createFont();
		font1.setFontHeightInPoints((short) 12);
		font1.setBold(true);
		style1.setFont(font1); 
		style1.setFillForegroundColor(IndexedColors.GREY_50_PERCENT.getIndex());
		style1.setFillPattern(FillPatternType.SOLID_FOREGROUND);
		
		style2 = workbook.createCellStyle();
		font2 = workbook.createFont();
		font2.setFontHeightInPoints((short) 12);
		font2.setBold(true);
		style2.setFont(font1); 
		style2.setFillForegroundColor(IndexedColors.LIGHT_YELLOW.getIndex());
		style2.setFillPattern(FillPatternType.SOLID_FOREGROUND);
		
		style3 = workbook.createCellStyle();
		font3 = workbook.createFont();
		font3.setFontHeightInPoints((short) 12);
		font3.setBold(true);
		style3.setFont(font1); 
		style3.setFillForegroundColor(IndexedColors.GREY_25_PERCENT.getIndex());
		style3.setFillPattern(FillPatternType.SOLID_FOREGROUND);
		
		for ( int rowCount = 1; rowCount < 10; rowCount++  )
		{
			rowCountSummar++;
		}
		
		Row row0 = SheetSummary.createRow (0);
		Cell cell0 = row0.createCell (0);
		cell0.setCellValue(Constants.sbomConstants.MIGRATION_OVERVIEW);
		cell0.setCellStyle(style);
		
		
		Row row23 = SheetSummary.createRow (rowCountSummar);
		Cell cell1 = row23.createCell (0);
		cell1.setCellValue(Constants.sbomConstants.BELOW_LINE_ITEMS_FAILED);
		cell1.setCellStyle(style);
		
		Row row24 = SheetSummary.createRow (++rowCountSummar);
		Cell cell2 = row24.createCell (0);
		cell2.setCellValue(Constants.sbomConstants.LINE_ITEM_DATALOADER);
		cell2.setCellStyle(style1);
		
		Cell cell3 = row24.createCell (1);
		cell3.setCellValue(Constants.sbomConstants.ID);
		cell3.setCellStyle(style1);
		
		Cell cell4 = row24.createCell (2);
		cell4.setCellValue(Constants.sbomConstants.COMMENTS);
		cell4.setCellStyle(style1);
		
		Cell cell5 = row24.createCell (3);
		cell5.setCellValue(Constants.sbomConstants.ERRORDESC);
		cell5.setCellStyle(style1);
		
	}

	public static void createAltSheet() 
	{
		try 
		{
			Row row = sheetServiceAltrPartUpd.createRow(rowCountAlternatepartsUpdate);
			Cell cell = row.createCell(0);
			cell.setCellValue(Constants.sbomConstants.PRIMARY_ID);
			Cell cell1 = row.createCell(1);
			cell1.setCellValue(Constants.sbomConstants.ALTERNATE_ID);
			Cell cell2 = row.createCell(2);
			cell2.setCellValue(Constants.sbomConstants.STATUS);
			Cell cell3 = row.createCell(3);
			cell3.setCellValue(Constants.sbomConstants.COMMENTS);
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	public static void createRelnSheet() 
	{
		try 
		{
			Row row = sheetServicePartReln.createRow(rowCountServicePartRelations);
			Cell cell = row.createCell(0);
			cell.setCellValue(Constants.sbomConstants.PRIMARY_OBJ_ID);
			Cell cell1 = row.createCell(1);
			cell1.setCellValue(Constants.sbomConstants.SECONDARY_OBJ_ID);
			Cell cell2 = row.createCell(2);
			cell2.setCellValue(Constants.sbomConstants.STATUS);
			Cell cell3 = row.createCell(3);
			cell3.setCellValue(Constants.sbomConstants.COMMENTS);
			Cell cell4 = row.createCell(4);
			cell4.setCellValue(Constants.sbomConstants.ERRORDESC);
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}


	/**
	 *   @param ReportName
	 *   Method to update excel report for service assembly.
	 */
	public static void createStrSheet ()
	{
		try 
		{
			Row row = sheetStr.createRow(rowCountStr);
			Cell cell = row.createCell(0);
			cell.setCellValue(Constants.sbomConstants.ChildID);
			Cell cell1 = row.createCell(1);
			cell1.setCellValue(Constants.sbomConstants.ParentID);
			Cell cell2 = row.createCell(2);
			cell2.setCellValue(Constants.sbomConstants.Add_Child_Status);
			Cell cell3 = row.createCell(3);
			cell3.setCellValue(Constants.sbomConstants.COMMENTS);
			Cell cell4 = row.createCell(4);
			cell4.setCellValue(Constants.sbomConstants.ERRORDESC);
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 *   @param sheet, excel row count
	 *   Method to update excel report column headings.
	 */
	private static void createHeadline(XSSFSheet sheet2, int rowCount) 
	{
		try 
		{
			Row row = sheet2.createRow(rowCount);
			Cell cell = row.createCell(0);
			cell.setCellValue(Constants.sbomConstants.ID);
			Cell cell1 = row.createCell(1);
			cell1.setCellValue(Constants.sbomConstants.ACTION);
			Cell cell2 = row.createCell(2);
			cell2.setCellValue(Constants.sbomConstants.STATUS);
			Cell cell3 = row.createCell(3);
			cell3.setCellValue(Constants.sbomConstants.COMMENTS);
			Cell cell4 = row.createCell(4);
			cell4.setCellValue(Constants.sbomConstants.ERRORDESC);
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}

	/**
	 *   @param strValue
	 *   Method to update excel report for service part creation.
	 */
	public static void writeServicePartCrea ( String strValue)
	{
		try 
		{
			//System.out.println ( "writeServicePartCrea=" + strValue );
			String splitPipeLne[] = strValue.split("\\?");
			if ( splitPipeLne.length == 5)
			{
				Row row = sheetServicePartCr.createRow(++rowCountServicePartCr);
				Cell cell = row.createCell(0);
				cell.setCellValue(splitPipeLne[0]);
				Cell cell1 = row.createCell(1);
				cell1.setCellValue(splitPipeLne[1]);
				Cell cell2 = row.createCell(2);
				cell2.setCellValue(splitPipeLne[2]);
				Cell cell3 = row.createCell(3);
				cell3.setCellValue(splitPipeLne[3]);
				Cell cell4 = row.createCell(4);
				cell4.setCellValue(splitPipeLne[4]);
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 *   @param strValue
	 *   Method to update excel report for service part form update.
	 */
	public static void writeServFormPartUpd ( String strValue)
	{
		try 
		{
			String splitPipeLne[] = strValue.split("\\?");
			if ( splitPipeLne.length == 5)
			{
				Row row = sheetServicePartFormUpd.createRow(++rowCountServicePartFormUpdate);
				Cell cell = row.createCell(0);
				cell.setCellValue(splitPipeLne[0]);
				Cell cell1 = row.createCell(1);
				cell1.setCellValue(splitPipeLne[1]);
				Cell cell2 = row.createCell(2);
				cell2.setCellValue(splitPipeLne[2]);
				Cell cell3 = row.createCell(3);
				cell3.setCellValue(splitPipeLne[3]);
				Cell cell4 = row.createCell(4);
				cell4.setCellValue(splitPipeLne[4]);
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 *   @param strValue
	 *   Method to update excel report for engg part form create.
	 */
	public static void writeEnggPartFormCre ( String strValue)
	{
		try 
		{
			String splitPipeLne[] = strValue.split("\\?");
			if ( splitPipeLne.length == 5)
			{
				Row row = sheetEnggPartFormCr.createRow(++rowCountEnggPartFormCr);
				Cell cell = row.createCell(0);
				cell.setCellValue(splitPipeLne[0]);
				Cell cell1 = row.createCell(1);
				cell1.setCellValue(splitPipeLne[1]);
				Cell cell2 = row.createCell(2);
				cell2.setCellValue(splitPipeLne[2]);
				Cell cell3 = row.createCell(3);
				cell3.setCellValue(splitPipeLne[3]);
				Cell cell4 = row.createCell(4);
				cell4.setCellValue(splitPipeLne[4]);
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 *   @param strValue
	 *   Method to update excel report for Alterante part Update.
	 */
	public static void writeAlternatePartUpd ( String strValue)
	{
		try 
		{
			String splitPipeLne[] = strValue.split("\\?");
			if ( splitPipeLne.length == 5)
			{
				Row row = sheetServiceAltrPartUpd.createRow(++rowCountAlternatepartsUpdate);
				Cell cell = row.createCell(0);
				cell.setCellValue(splitPipeLne[0]);
				Cell cell1 = row.createCell(1);
				cell1.setCellValue(splitPipeLne[1]);
				Cell cell2 = row.createCell(2);
				cell2.setCellValue(splitPipeLne[2]);
				Cell cell3 = row.createCell(3);
				cell3.setCellValue(splitPipeLne[3]);
				Cell cell4 = row.createCell(4);
				cell4.setCellValue(splitPipeLne[4]);
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 *   @param strValue
	 *   Method to update excel report for group change ownership.
	 */
	public static void writeChangeOnwership ( String strValue)
	{
		try 
		{
			String splitPipeLne[] = strValue.split("\\?");
			if ( splitPipeLne.length == 5)
			{
				Row row = sheetServicePartOwnerChange.createRow(++rowCountChangeOwnership);
				Cell cell = row.createCell(0);
				cell.setCellValue(splitPipeLne[0]);
				Cell cell1 = row.createCell(1);
				cell1.setCellValue(splitPipeLne[1]);
				Cell cell2 = row.createCell(2);
				cell2.setCellValue(splitPipeLne[2]);
				Cell cell3 = row.createCell(3);
				cell3.setCellValue(splitPipeLne[3]);
				Cell cell4 = row.createCell(4);
				cell4.setCellValue(splitPipeLne[4]);
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 *   @param strValue
	 *   Method to update excel report for service part relations.
	 */
	public static void writeServPartRelns ( String strValue)
	{
		try 
		{
			String splitPipeLne[] = strValue.split("\\?");
			if ( splitPipeLne.length == 5)
			{
				Row row = sheetServicePartReln.createRow(++rowCountServicePartRelations);
				Cell cell = row.createCell(0);
				cell.setCellValue(splitPipeLne[0]);
				Cell cell1 = row.createCell(1);
				cell1.setCellValue(splitPipeLne[1]);
				Cell cell2 = row.createCell(2);
				cell2.setCellValue(splitPipeLne[2]);
				Cell cell3 = row.createCell(3);
				cell3.setCellValue(splitPipeLne[3]);
				Cell cell4 = row.createCell(4);
				cell4.setCellValue(splitPipeLne[4]);
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 *   @param strValue
	 *   Method to update excel report for service assembly.
	 */
	public static void writeExcelStr ( String strValue)
	{
		try 
		{
			String splitPipeLne[] = strValue.split("\\?");
			if ( splitPipeLne.length == 5)
			{
				Row row = sheetStr.createRow(++rowCountStr);
				Cell cell = row.createCell(0);
				cell.setCellValue(splitPipeLne[0]);
				Cell cell1 = row.createCell(1);
				cell1.setCellValue(splitPipeLne[1]);
				Cell cell2 = row.createCell(2);
				cell2.setCellValue(splitPipeLne[2]);
				Cell cell3 = row.createCell(3);
				cell3.setCellValue(splitPipeLne[3]);
				Cell cell4 = row.createCell(4);
				String cell4Value = splitPipeLne[4];
				String splitAgain[] = splitPipeLne[4].split (Constants.sbomConstants.SEP3);
				if (  splitAgain.length > 1 )
				{
					if ( splitAgain[1].contains(Constants.sbomConstants.CHILD_ITEM) )
					{
						cell4Value = splitAgain[1];
					}
				}
				cell4.setCellValue(cell4Value);
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	public static void writeSummaryReport(String excelSummaryRep) 
	{
		try 
		{
			String splitPipeLne[] = excelSummaryRep.split("\\?");
			if ( splitPipeLne.length == 4)
			{
				Row row = SheetSummary.createRow(++rowCountSummar);
				Cell cell = row.createCell(0);
				cell.setCellValue(splitPipeLne[0]);
				cell.setCellStyle(style2);
				
				Cell cell1 = row.createCell(1);
				cell1.setCellValue(splitPipeLne[1]);
				cell1.setCellStyle(style2);
				
				Cell cell2 = row.createCell(2);
				cell2.setCellValue(splitPipeLne[2]);
				cell2.setCellStyle(style2);
				
				Cell cell3 = row.createCell(3);
				cell3.setCellValue(splitPipeLne[3]);
				String splitAgain[] = splitPipeLne[3].split (Constants.sbomConstants.SEP3);
				String cell3Value = splitPipeLne[3];
				if (  splitAgain.length > 1 )
				{
					if ( splitAgain[1].contains(Constants.sbomConstants.CHILD_ITEM) )
					{
						cell3Value = splitAgain[1];
					}
				}
				cell3.setCellValue(cell3Value);
				cell3.setCellStyle(style2);
			}
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	public static void writeSummaryInfo(int successPartCreation, int spFormUpdateSuccess, int altPartUpdSuccess
			, int relationAttachSuccess, int strCreSuccess, int changeOwnerShipSuccess, int epServFormCreateSuccess ) 
	{
		try 
		{
			Row row3 =  SheetSummary.createRow (1);
			Cell cell1 = row3.createCell(0);
			cell1.setCellValue(Constants.sbomConstants.NO_SERV_SUCCESS);
			cell1.setCellStyle(style3);
			Cell cell2 = row3.createCell(1);
			cell2.setCellValue(successPartCreation);
			cell2.setCellStyle(style3);
			Cell cell3 = row3.createCell(2);
			cell3.setCellValue( "Refer Tab\" " + Constants.sbomConstants.SERVICE_PART_CREATION_SHEET + " \"For More Details"     );
			cell3.setCellStyle(style3);
			
			Row row5 =  SheetSummary.createRow (2);
			Cell cellA = row5.createCell(0);
			cellA.setCellValue(Constants.sbomConstants.NO_SERV_FORM_SUCCESS);
			cellA.setCellStyle(style3);
			Cell cellB = row5.createCell(1);
			cellB.setCellValue(spFormUpdateSuccess);
			cellB.setCellStyle(style3);
			Cell cellC = row5.createCell(2);
			cellC.setCellValue( "Refer Tab\" " + Constants.sbomConstants.SERVICE_PART_FORM_UPDATE + " \"For More Details"     );
			cellC.setCellStyle(style3);
			
			Row row7 =  SheetSummary.createRow (3);
			Cell cellX = row7.createCell(0);
			cellX.setCellValue(Constants.sbomConstants.NO_ALT_UPD_SUCCESS);
			cellX.setCellStyle(style3);
			Cell cellY = row7.createCell(1);
			cellY.setCellValue(altPartUpdSuccess);
			cellY.setCellStyle(style3);
			Cell cellZ = row7.createCell(2);
			cellZ.setCellValue( "Refer Tab\" " + Constants.sbomConstants.SERVICE_PART_ALTER_SHEET + " \"For More Details" );
			cellZ.setCellStyle(style3);
			
			Row row9 =  SheetSummary.createRow (4);
			Cell cellP = row9.createCell(0);
			cellP.setCellValue(Constants.sbomConstants.NO_RELN_UPD_SUCCESS);
			cellP.setCellStyle(style3);
			Cell cellQ = row9.createCell(1);
			cellQ.setCellValue(relationAttachSuccess);
			cellQ.setCellStyle(style3);
			Cell cellO = row9.createCell(2);
			cellO.setCellValue( "Refer Tab\" " + Constants.sbomConstants.SERVICE_PART_RELN_SHEET + " \"For More Details" );
			cellO.setCellStyle(style3);
			
			Row row11 =  SheetSummary.createRow (5);
			Cell cellR = row11.createCell(0);
			cellR.setCellValue(Constants.sbomConstants.NO_STR_UPD_SUCCESS);
			cellR.setCellStyle(style3);
			Cell cellS = row11.createCell(1);
			cellS.setCellValue(strCreSuccess);
			cellS.setCellStyle(style3);
			Cell cellT = row11.createCell(2);
			cellT.setCellValue( "Refer Tab\" " + Constants.sbomConstants.SERVICE_ASSEMBLY_MIGRATION + " \"For More Details" );
			cellT.setCellStyle(style3);
			
			Row row13 =  SheetSummary.createRow (6);
			Cell cellM = row13.createCell(0);
			cellM.setCellValue(Constants.sbomConstants.NO_OWNERSHIP_SUCCESS);
			cellM.setCellStyle(style3);
			Cell cellN = row13.createCell(1);
			cellN.setCellValue(changeOwnerShipSuccess);
			cellN.setCellStyle(style3);
			Cell cellD = row13.createCell(2);
			cellD.setCellValue( "Refer Tab\" " + Constants.sbomConstants.SERVICE_PART_OWNNERSHIP_SHEET + " \"For More Details" );
			cellD.setCellStyle(style3);
			
			Row row15 =  SheetSummary.createRow (7);
			Cell cellV = row15.createCell(0);
			cellV.setCellValue(Constants.sbomConstants.NO_ENG_FORM_SUCCESS);
			cellV.setCellStyle(style3);
			Cell cellW = row15.createCell(1);
			cellW.setCellValue(epServFormCreateSuccess);
			cellW.setCellStyle(style3);
			Cell cellE = row15.createCell(2);
			cellE.setCellValue( "Refer Tab\" " + Constants.sbomConstants.ENGG_PART_FORM_SHEET + " \"For More Details" );
			cellE.setCellStyle(style3);
		}
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 *   @param strValue
	 *   Method to update close and save excel report file.
	 */
	public static String closeExcel( String logFileDir ) throws FileNotFoundException, IOException
	{
		setTime();
		String summaryFileFullPath = logFileDir + "\\" + Constants.sbomConstants.REPORTFILENAME + "_" + currentTime + ".xlsx";
		try (FileOutputStream outputStream = new FileOutputStream(summaryFileFullPath)) 
		{
			workbook.write(outputStream);
			workbook.close();
		}
		return summaryFileFullPath;
	}
	
	/**
	 *   @param void
	 *   Method to get system  date and time .
	 */
	public static void setTime() 
	{
		try 
		{
			DateFormat dateFormat = new SimpleDateFormat("dd-MMM-yyyy_HHmmss");
			Date date = new Date();
			currentTime = dateFormat.format(date);
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}

}
