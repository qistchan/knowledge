package com.get.ontrack.common;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.List;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.poi.ss.usermodel.Font;
import org.apache.poi.ss.usermodel.Footer;
import org.apache.poi.ss.util.CellRangeAddress;
import com.get.ontrack.model.DesignRelease;


public class ExportToExcel{
	
	@SuppressWarnings("deprecation")
	public static HSSFWorkbook buildExcelDocumentNew(List<DesignRelease> result) throws FileNotFoundException,IOException{      
		String[] header1 ={"General","Engineering","Design"};
		String[] header ={"Activity ID","Activity Description","EDOT",
				"Main Group","Auto Close?","Status","State","Start Date",
				"Required Date", "Promise Date","Actual Date",
				"TD Release Date","Date Change Reason",
				"Eng Org Project","Engineer","ECR","Technical Data",
				"Comment","Required Date","Promise Date",
				"Actual Date","Date Change Reason","Design Org Project",
				"Design Coordinator","ECN", "Comment"};

		HSSFWorkbook workbook = new HSSFWorkbook(); 
		HSSFSheet worksheet = workbook.createSheet("EDOT Report");
		Font defaultFont = workbook.getFontAt((short) 0);
		defaultFont.setFontName("GE Inspira Pitch");

		HSSFRow row;
		HSSFCellStyle headerCellStyle = workbook.createCellStyle();

		HSSFCell cell = null;
		headerCellStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
		headerCellStyle.setVerticalAlignment(HSSFCellStyle.ALIGN_CENTER);
		headerCellStyle.setBorderTop(HSSFCellStyle.BORDER_THIN);
		headerCellStyle.setBorderBottom(HSSFCellStyle.BORDER_THIN);
		headerCellStyle.setBorderRight(HSSFCellStyle.BORDER_THIN);


		HSSFFont headerFont = workbook.createFont();
		headerFont.setFontName("GE Inspira Pitch");
		headerFont.setFontHeightInPoints((short) 11);
		headerFont.setBoldweight(HSSFFont.BOLDWEIGHT_BOLD);

		headerCellStyle.setFont(headerFont);
		headerCellStyle.setFillForegroundColor(HSSFColor.PALE_BLUE.index);
		headerCellStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);
		HSSFFont dataFont = workbook.createFont();
		dataFont.setFontName("GE Inspira Pitch");
		dataFont.setFontHeightInPoints((short) 10);

		HSSFCellStyle dataCellStyle = workbook.createCellStyle(); 
		dataCellStyle.setFont(dataFont);
		dataCellStyle.setFillForegroundColor(HSSFColor.LEMON_CHIFFON.index);
		dataCellStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		dataCellStyle.setBorderBottom(HSSFCellStyle.BORDER_THIN);
		dataCellStyle.setBorderTop(HSSFCellStyle.BORDER_THIN);
		dataCellStyle.setBorderRight(HSSFCellStyle.BORDER_THIN);
		dataCellStyle.setBorderLeft(HSSFCellStyle.BORDER_THIN);
		
		HSSFCellStyle redStyle = workbook.createCellStyle(); 
		redStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);
		redStyle.setFillForegroundColor(HSSFColor.RED.index);
		redStyle.setBorderBottom(HSSFCellStyle.BORDER_THIN);
		redStyle.setBorderTop(HSSFCellStyle.BORDER_THIN);
		redStyle.setBorderRight(HSSFCellStyle.BORDER_THIN);
		redStyle.setBorderLeft(HSSFCellStyle.BORDER_THIN);
		
		HSSFCellStyle blueStyle = workbook.createCellStyle();
		blueStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);
		blueStyle.setFillForegroundColor(HSSFColor.BLUE.index);
		blueStyle.setBorderBottom(HSSFCellStyle.BORDER_THIN);
		blueStyle.setBorderTop(HSSFCellStyle.BORDER_THIN);
		blueStyle.setBorderRight(HSSFCellStyle.BORDER_THIN);
		blueStyle.setBorderLeft(HSSFCellStyle.BORDER_THIN);
		
		HSSFCellStyle yellowStyle = workbook.createCellStyle();
		yellowStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);
		yellowStyle.setFillForegroundColor(HSSFColor.YELLOW.index);
		yellowStyle.setBorderBottom(HSSFCellStyle.BORDER_THIN);
		yellowStyle.setBorderTop(HSSFCellStyle.BORDER_THIN);
		yellowStyle.setBorderRight(HSSFCellStyle.BORDER_THIN);
		yellowStyle.setBorderLeft(HSSFCellStyle.BORDER_THIN);
		
		HSSFCellStyle whiteStyle = workbook.createCellStyle();
		whiteStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);
		whiteStyle.setFillForegroundColor(HSSFColor.WHITE.index);
		whiteStyle.setBorderBottom(HSSFCellStyle.BORDER_THIN);
		whiteStyle.setBorderTop(HSSFCellStyle.BORDER_THIN);
		whiteStyle.setBorderRight(HSSFCellStyle.BORDER_THIN);
		whiteStyle.setBorderLeft(HSSFCellStyle.BORDER_THIN);

		row = worksheet.createRow(0);

		// row.setRowStyle(hcs2);
		worksheet.addMergedRegion(new CellRangeAddress(0,0,0,6));
		cell = row.createCell((short)0);
		cell.setCellValue(header1[0]);
		cell.setCellStyle(headerCellStyle);  

		worksheet.addMergedRegion(new CellRangeAddress(0,0,7,17));
		cell = row.createCell((short)7);
		cell.setCellValue(header1[1]);
		cell.setCellStyle(headerCellStyle); 

		worksheet.addMergedRegion(new CellRangeAddress(0,0,18,25));
		cell = row.createCell((short)18);
		cell.setCellValue(header1[2]);
		cell.setCellStyle(headerCellStyle); 


		row = worksheet.createRow(1);       
		for (int i = 0; i < header.length; i++) {        
			worksheet.setColumnWidth((short)0,(short)4500);
			worksheet.setColumnWidth((short)1,(short)6000);
			worksheet.setColumnWidth((short)2,(short)4500);
			worksheet.setColumnWidth((short)3,(short)3000);
			worksheet.setColumnWidth((short)4,(short)6000);
			worksheet.setColumnWidth((short)5,(short)3000);
			worksheet.setColumnWidth((short)6,(short)6000);
			worksheet.setColumnWidth((short)7,(short)6000);
			worksheet.setColumnWidth((short)8,(short)6000);
			worksheet.setColumnWidth((short)9,(short)6000);
			worksheet.setColumnWidth((short)10,(short)6000);
			worksheet.setColumnWidth((short)11,(short)6000);
			worksheet.setColumnWidth((short)12,(short)6000);
			worksheet.setColumnWidth((short)13,(short)6000);
			worksheet.setColumnWidth((short)14,(short)6000);
			worksheet.setColumnWidth((short)15,(short)6000);
			worksheet.setColumnWidth((short)16,(short)5000);
			worksheet.setColumnWidth((short)17,(short)6000);
			worksheet.setColumnWidth((short)18,(short)6000);
			worksheet.setColumnWidth((short)19,(short)6000);
			worksheet.setColumnWidth((short)20,(short)6000);
			worksheet.setColumnWidth((short)21,(short)6000);
			worksheet.setColumnWidth((short)22,(short)6000);
			worksheet.setColumnWidth((short)23,(short)6000);
			worksheet.setColumnWidth((short)24,(short)6000);
			worksheet.setColumnWidth((short)25,(short)12000); 
			//worksheet.setColumnWidth((short)26,(short)6000); 
			//worksheet.setColumnWidth((short)27,(short)6000); 


			cell = row.createCell((short)i);
			cell.setCellValue(header[i]);
			cell.setCellStyle(headerCellStyle);   
		}

		String text = "GE CONFIDENTIAL";
		Footer footer = worksheet.getFooter();
		footer.setLeft(text);

		int rowNum =2 ;


		for (int inx = 0; inx < result.size(); inx++) {
			DesignRelease edotRowData = (DesignRelease) result.get(inx);
			String color = "";
			row = worksheet.createRow(rowNum++);
			for (int jnx = 0; jnx <= 25 ; jnx++) {
				cell = row.createCell((short)jnx);
				cell.setCellStyle(dataCellStyle);  
				switch(jnx){
				case 0:
					cell.setCellValue(edotRowData.getBomLineItemId());
					break;
				case 1:
					cell.setCellValue(edotRowData.getDescription());
					break;
				case 2:
					cell.setCellValue(edotRowData.getDesignReleaseId());
					break;
				case 3:
					cell.setCellValue(edotRowData.getMainGroup());
					break;
				case 4:
					cell.setCellValue(edotRowData.getAutoClose()); 
					break;
				case 5:
					cell.setCellValue(edotRowData.getStatus());
					break;
				case 6:
					color = edotRowData.getState();
					if(color.equals("Red"))
					{
						cell.setCellStyle(redStyle);
					}
					else if(color.equals("Blue"))
					{
						cell.setCellStyle(blueStyle);
					}
					else if(color.equals("Yellow"))
					{
						cell.setCellStyle(yellowStyle);
					}
					else if(color.equals("White"))
					{
						cell.setCellStyle(whiteStyle);
					}
					else
					{
						cell.setCellValue(color);
					}
					
					break;
				
				case 7:
					cell.setCellValue(edotRowData.getEngrStartDateLabel());
					break;
				case 8:
					cell.setCellValue(edotRowData.getEngrRequiredDateLabel());
					break;
				case 9:
					cell.setCellValue(edotRowData.getEngrPromiseDateLabel());
					break;
				case 10:
					cell.setCellValue(edotRowData.getEngrActualDateLabel());
					break;
				case 11:
					cell.setCellValue("");
					break;
				case 12:
					cell.setCellValue(edotRowData.getEngrDateChangeReason());
					break;
				case 13:
					cell.setCellValue(edotRowData.getEngrOrgProject());
					break;
				case 14:
					cell.setCellValue(edotRowData.getEngrResource());
					break;
				case 15:
					cell.setCellValue(edotRowData.getEngrECR());
					break;
				case 16:
					cell.setCellValue(edotRowData.getTechnicalData());
					break;
				case 17:
					cell.setCellValue(edotRowData.getEngrComment());
					break;
				case 18:
					cell.setCellValue(edotRowData.getDesignRequiredDateLabel());
					break;
				case 19:
					cell.setCellValue(edotRowData.getDesignPromiseDateLabel());
					break;
				case 20:
					cell.setCellValue(edotRowData.getDesignActualDateLabel());
					break;
				case 21:
					cell.setCellValue(edotRowData.getDesignDateChangeReason());
					break;
				case 22:
					cell.setCellValue(edotRowData.getDesignOrgProject());
					break;
				case 23:
					cell.setCellValue(edotRowData.getDesignResource());
					break;
				case 24:
					cell.setCellValue(edotRowData.getDesignECN());
					break;
				case 25:
					cell.setCellValue(edotRowData.getDesignComment());
					break;

				}
			}

		}
		return workbook;
	}
}

