package com.ge.transportation.plm.sbom.report;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.DataFormatter;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import com.ge.transportation.plm.sbom.common.ReportExcel;
import com.ge.transportation.plm.sbom.constants.Constants;

public class sbomReport 
{
	/* class Variables */
	private static int successPartCreation;
    private static int failPartCreation;
    private static int spFormUpdateSuccess;
    private static int spFormUpdateFail;
    private static int epServFormCreateFail;
    private static int epServFormCreateSuccess;
    private static int relationAttachFail;
    private static int relationAttachSuccess;
    private static int changeOwnerShipFail;
    private static int changeOwnerShipSuccess;
    private static int strCreFail;
    private static int strCreSuccess;
    private static int altPartUpdSuccess;
    private static int altPartUpdFail;
    
    private static String logFilesDir;
	static ReportExcel repExcel;
	Vector<String> allLogFiles;
	static Vector<String> dataLoaderLineItemIdVector = new Vector<String>();
	static String dataLoaderFile;
	static Map<String, String> dataLoaderMap = new HashMap<String, String>();
	protected static DataFormatter FORMATTER = new DataFormatter();

	/**
	 * @param args
	 *  -help or -h will print out a Usage statement
	 */
	public static void main(String[] args) 
	{
		System.out.println("\n----------------sBom Migration Report Generation utility started----------------\n");
		if (args.length > 0) 
		{
			// System.out.println( "enter the arguments" );
			for (int argLen = 0; argLen < args.length; argLen++) 
			{
				if (args[0].equals("-help") || args[0].equals("-h")|| args[0].equals("")) 
				{
					printHelp();
					System.exit(0);
				}

				String argV1[] = args[argLen].split("=");
				if (argV1.length == 2) 
				{
					if (argV1[0].equals("-inputLogDir")) 
					{
						logFilesDir = argV1[1];
					}
					else if (argV1[0].equals("-DataLoader")) 
					{
						dataLoaderFile = argV1[1];
					}
				} 
				else 
				{
					System.out.println("\nError: Argument format is invalid.Refer help\n");
					printHelp();
					System.exit(0);
				}
			}
			System.out.println("logFilesDir=" + logFilesDir);

			if (logFilesDir == null) 
			{
				System.out.println("Error:Invalid Arguments");
				printHelp();
				System.exit(0);
			}
			if ( dataLoaderFile == null )
			{
				System.out.println("Error:Invalid Arguments");
				printHelp();
				System.exit(0);
			}
			
			/* get all the files in directory location */
			listFiles();
		} 
		else 
		{
			System.out.println("Error:No arguments were entered");
			printHelp();
		}
		System.out.println("\n----------------sBom Migration Report Generation utility Ended----------------\n");
	}

	/**
	 *   Method to list the files in LoG directory
	 *  -help or -h will print out a Usage statement
	 */
	private static void listFiles()
	{
		try 
		{
			File dir = new File(logFilesDir);
			if (dir.exists()) 
			{
				File[] files = dir.listFiles();
				if (files.length == 0) 
				{
					System.out.println("Error:The directory is empty");
					printHelp();
				} 
				else 
				{
					/*call class to write in excel*/
					repExcel = new ReportExcel();
					boolean LogFilesFound = false;
					
					/* read files from log files */
					for (File aFile1 : files)
					{
						String fileName1 = aFile1.getName();
						
						/*Check Atleast one log file exists*/
						if ((fileName1.equalsIgnoreCase(Constants.sbomConstants.SERVICEPARTCREATE)) ||
							(fileName1.equalsIgnoreCase(Constants.sbomConstants.SERVICEFORMUPDATE)) ||
							(fileName1.equalsIgnoreCase(Constants.sbomConstants.ENGGPARTFORMUPDT)) ||
							(fileName1.equalsIgnoreCase(Constants.sbomConstants.ITEMRELNS)) ||
							(fileName1.equalsIgnoreCase(Constants.sbomConstants.ITEMRELNS2)) ||
							(fileName1.equalsIgnoreCase(Constants.sbomConstants.OWNERSHIPCHANGE)) ||
							(fileName1.equalsIgnoreCase(Constants.sbomConstants.ALTERNATEPARTS)) ||
							(fileName1.equalsIgnoreCase(Constants.sbomConstants.BOMCREATION)))
						{
							LogFilesFound = true;
						}
					}
					if ( LogFilesFound )
					{
						readDataLoaderExcel();
						/* read files from log files */
						for (File aFile : files) 
						{
							String fileName = aFile.getName();
							
							if (fileName.equalsIgnoreCase(Constants.sbomConstants.SERVICEPARTCREATE)) 
							{
								/* call function to create service part migration report */
								createServicePartMigrationReport(aFile);
							} 
							else if (fileName.equalsIgnoreCase(Constants.sbomConstants.SERVICEFORMUPDATE)) 
							{
								/*
								 * call function to create service form update migration
								 * report
								 */
								createServicePartFormUpdateMigrationReport(aFile);
							} 
							else if (fileName.equalsIgnoreCase(Constants.sbomConstants.ENGGPARTFORMUPDT)) 
							{
								/*
								 * call function to create engineering serv form update
								 * migration report
								 */
								createEngineeringServForm(aFile);
							}
							
							else if ( (fileName.equalsIgnoreCase(Constants.sbomConstants.ITEMRELNS)) ||
									  ((fileName.equalsIgnoreCase(Constants.sbomConstants.ITEMRELNS2))))
							{
								/*
								 * call function to create engineering serv form update
								 * migration report
								 */
								createItemRelnsReport(aFile);
							} 
							else if (fileName.equalsIgnoreCase(Constants.sbomConstants.OWNERSHIPCHANGE)) 
							{
								/*
								 * call function to create engineering serv form update
								 * migration report
								 */
								createOwnershipChangeReport(aFile);
							} 
							else if (fileName.equalsIgnoreCase(Constants.sbomConstants.ALTERNATEPARTS)) 
							{
								/*
								 * call function to create Alternate part update log
								 * migration report
								 */
								createAlternatePartsReport(aFile);
							}
							
							else if (fileName.equalsIgnoreCase(Constants.sbomConstants.BOMCREATION)) 
							{
								/*
								 * call function to create assembly update migration
								 * report
								 */
								createStructureMigrationReport(aFile);
							}
	
						}
					}
					else
					{
						System.out.println("Error:No Log files found at  "+ logFilesDir);
						printHelp();
						System.exit(0);
					} 
					
					/*Enter the sumary info */
					ReportExcel.writeSummaryInfo(successPartCreation,spFormUpdateSuccess
					,altPartUpdSuccess,relationAttachSuccess,strCreSuccess,changeOwnerShipSuccess,epServFormCreateSuccess);
					
					/*print the report file*/
					String reportsFile = ReportExcel.closeExcel(logFilesDir);
					System.out.println("\n Migration Report File is generated at "+ reportsFile + "\n");
				}
			} 
			else 
			{
				System.out.println("Error:input log directory is invalid");
				printHelp();
			}
		} 
		catch (FileNotFoundException e) 
		{
			e.printStackTrace();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}

	private static void readDataLoaderExcel()
	{
		System.out.println("Reading Data Loader excel.....");
		try 
		{
			File dataLoadedrFile = new File(dataLoaderFile);
			if ( dataLoadedrFile.exists() )
			{
				FileInputStream inputStream = new FileInputStream ( new File(dataLoaderFile) );
				Workbook workbook = new XSSFWorkbook(inputStream);
				Sheet firstSheet = workbook.getSheetAt(0);
				Iterator<Row> iterator = firstSheet.iterator();
				int dataLoaderNoIndex = 0;
				int dataLoaderIdIndex = 0;
				while (iterator.hasNext())
				{
					 Row nextRow = iterator.next();
					 
					 int rowNo = nextRow.getRowNum();
					 if ( rowNo == 0 )
					 {
						continue;
					 }
					 if ( rowNo == 1 )
					 {
						 Iterator<Cell> cellIterator = nextRow.cellIterator();
						 while (cellIterator.hasNext())
						 {
							Cell cell = cellIterator.next();
							String cellValue = FORMATTER.formatCellValue ( nextRow.getCell(cell.getColumnIndex()) );
							//System.out.println ( "cellValue=" + cellValue );
							if ( cellValue.equals(Constants.sbomConstants.NUMBER) )
							{
								int cellIndex = cell.getColumnIndex();
								dataLoaderNoIndex = cellIndex;
								//System.out.println ( "dataLoaderNoIndex=" + dataLoaderNoIndex );
							}
							else if ( cellValue.equals(Constants.sbomConstants.ITEM_ID_CELL) )
							{
								int cellIndex = cell.getColumnIndex();
								dataLoaderIdIndex = cellIndex;
								//System.out.println ( "dataLoaderItem Id Index=" + dataLoaderIdIndex );
							}
						 }
					 }
					 else if ( rowNo > 1 )
					 {
						 boolean foundMapKey = false;
						 boolean foundMapValue = false;
						 String keyMap = "";
						 String valueMap = "";
						 Iterator<Cell> cellIterator = nextRow.cellIterator(); 
						 while (cellIterator.hasNext())
						 {
							 Cell cell = cellIterator.next();
							 if ( cell.getColumnIndex() ==  dataLoaderNoIndex )
							 {
								foundMapKey = true;
								keyMap = FORMATTER.formatCellValue ( nextRow.getCell ( dataLoaderNoIndex ));
								
							 }
							 else if ( cell.getColumnIndex() ==  dataLoaderIdIndex )
							 {
								 foundMapValue = true;
								 valueMap = FORMATTER.formatCellValue ( nextRow.getCell(dataLoaderIdIndex ));
							}
						 }
						 
						 /* Update the data loader map*/
						 if ( foundMapKey && foundMapValue )
						 dataLoaderMap.put(keyMap, valueMap);
					 }
				}
				
				workbook.close();
			}
			else
			{
				System.out.println ( "Data loader file doesnt exists" );
				printHelp();
				System.exit(0);
			}
		} 
		catch (FileNotFoundException e) 
		{
			printHelp();
			e.printStackTrace();
			System.exit(0);
		} 
		catch (IOException e) 
		{
			printHelp();
			e.printStackTrace();
			System.exit(0);
		}
		catch ( Exception e )
		{
			e.printStackTrace();
			System.out.println("An Unknown Error has Occured.");
			System.out.println("Make sure \"DataLoader\" input file is of excel format.");
			printHelp();
			System.exit(0);
		}
		//System.out.println("data loader size" + dataLoaderMap.size() );
	}
	
	/**
	 *   @param log File
	 *   Method to create report from alternate part Log.
	 */
	private static void createAlternatePartsReport(File aFile)
	{
		System.out.println(" processing log file " + aFile.getName());
		try 
		{
			/* read this file line by line */
			String inputFileLocn = logFilesDir + "\\" + aFile.getName();
			BufferedReader buffer = null;
			buffer = new BufferedReader(new FileReader(inputFileLocn));
			String readLine = "";
			
			while ((readLine = buffer.readLine()) != null) 
			{
				String itemDetails[] = readLine.split("\\|");
				if (itemDetails.length == 4) 
				{
					if (itemDetails[0].equals(Constants.sbomConstants.PARTNUMNBER))
					{
						continue;
					} 
					else 
					{
						String excelStr = "";

						/* update the report excel */
						ReportExcel.writeAlternatePartUpd(excelStr);
						if (  itemDetails[2].contains(Constants.sbomConstants.SUCCESS))
						{
							excelStr = itemDetails[0] 
									+ Constants.sbomConstants.SEP1
									+ itemDetails[1] 
									+ Constants.sbomConstants.SEP1
									+ itemDetails[2] 
									+ Constants.sbomConstants.SEP1 
									+ itemDetails[3]
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.NA;
							
							altPartUpdSuccess++;
						}
						else if (  itemDetails[2].contains(Constants.sbomConstants.FAIL))
						{
							excelStr = itemDetails[0] 
									+ Constants.sbomConstants.SEP1
									+ itemDetails[1] 
									+ Constants.sbomConstants.SEP1
									+ itemDetails[2] 
									+ Constants.sbomConstants.SEP1 
									+ itemDetails[3]
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.NA;
							
							altPartUpdFail++;
							
							/*Update summary report tab */
							readDataLoaderMap(excelStr);
						}
						/* update the report excel */
						ReportExcel.writeAlternatePartUpd(excelStr);
					}
				}
			}
			buffer.close();
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}

	/**
	 *   @param log File
	 *   Method to create StructureMigrationReport from log file.
	 */
	private static void createStructureMigrationReport(File aFile)
	{
		System.out.println(" processing log file " + aFile.getName());

		try 
		{
			/* read this file line by line */
			String inputFileLocn = logFilesDir + "\\" + aFile.getName();
			
			BufferedReader buffer = null;
			buffer = new BufferedReader(new FileReader(inputFileLocn));
			String readLine = "";
			
			boolean startReading = false;
			String parentId = null;
			boolean startErrorReading = false;
			int dashLineCount = 0;
			int drgCount = 0;
			String excelStrfail = ""; 
			while ((readLine = buffer.readLine()) != null) 
			{
				if (readLine.contains(Constants.sbomConstants.STARTREADINGD_FROM_STRING)) 
				{
					startReading = true;
					continue;
				}

				if (startReading == false) 
				{
					continue;
				}

				String trimmedLine = readLine.trim().replaceAll("\\s{2,}", " ");
				if (trimmedLine.contains(Constants.sbomConstants.SAME_BAD_PARENT))
				{
					continue;
				}
				if (trimmedLine.contains(Constants.sbomConstants.TOTALLINES)) 
				{
					break;
				} 
				else 
				{
					String itemDetails[] = trimmedLine.split(" ");
					if (trimmedLine.contains(Constants.sbomConstants.REVFOUND)) 
					{
						if (!(trimmedLine.contains(Constants.sbomConstants.ADDOCCURENCE)))
						{
							parentId = itemDetails[2]; //+ itemDetails[3]
									//+ itemDetails[4];
							if (trimmedLine.contains(Constants.sbomConstants.ERRORNO))
							{
								/*get overview of error message info */
								String errorMes = "";
								for (int lnind = 5; lnind < itemDetails.length; lnind++) 
								{
									errorMes = errorMes + itemDetails[lnind] + " ";
								}
								parentId = parentId + Constants.sbomConstants.SEP1 + errorMes;
							}
						} 
						else if ( (trimmedLine.contains(Constants.sbomConstants.ADDOCCURENCE) ) 
								&& ( !(trimmedLine.contains(Constants.sbomConstants.ERRORNO)) ) )
						{
							String childId = itemDetails[2];// + itemDetails[3]
									//+ itemDetails[4];
							
							String splitParentId[] = parentId.split ("\\?");
							
							String excelStr = "";
							boolean errorExists = false;
							if ( splitParentId.length > 1 )
							{	
								errorExists = true;
								
								excelStr = childId 
									+ Constants.sbomConstants.SEP1 
									+ splitParentId[0]
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.FAIL
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.CHILD_PART_NOT_FOUND
									+ Constants.sbomConstants.SEP1
									+ splitParentId[1]
									+ Constants.sbomConstants.DBLCLN;		
							}
							if ( splitParentId.length == 1 )
							{
								 excelStr =  childId 
									+ Constants.sbomConstants.SEP1 
									+ splitParentId[0]
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.SUCCESS
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.CHILD_PART_FOUND
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.NA;
							}

							/* update the report excel */
							ReportExcel.writeExcelStr(excelStr);
							strCreSuccess++;
							
							if ( errorExists )
							{
								/*Update summary report tab */
								readDataLoaderMap(excelStr);
							}
						}
						else if ( (trimmedLine.contains(Constants.sbomConstants.ADDOCCURENCE) ) 
								&& ( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)) ) )
						{
							startErrorReading = true;
							String childId = itemDetails[2];
							
							String splitParentId[] = parentId.split ("\\?");
							if ( splitParentId.length > 1 )
							{	
								excelStrfail = excelStrfail 
									+ childId  
									+ Constants.sbomConstants.SEP1 
									+ splitParentId[0] 
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.FAIL
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.CHILD_PART_NOT_FOUND
									+ Constants.sbomConstants.SEP1 
									+ splitParentId[1]
									+ Constants.sbomConstants.DBLCLN;		
							}
							else if ( splitParentId.length == 1 )
							{
								excelStrfail = excelStrfail
										+ childId
										+ Constants.sbomConstants.SEP1 
										+ splitParentId[0]
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.FAIL
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.CHILD_PART_FAILED
										+ Constants.sbomConstants.SEP1; 
							}
						}
					} 
					else if ( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)) || startErrorReading ) 
					{
						startErrorReading = true;
						if ( trimmedLine.contains (Constants.sbomConstants.DASH_LINE ))
						{
							dashLineCount++;
						}
						if ( dashLineCount == 0)
						{	
							if (trimmedLine.contains(Constants.sbomConstants.CHILDID)) 
							{
								String childId = itemDetails[2];
								
								String splitParentId[] = parentId.split ("\\?");
								if ( splitParentId.length > 1 )
								{	
									excelStrfail = excelStrfail 
										+ childId  
										+ Constants.sbomConstants.SEP1 
										+ splitParentId[0] 
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.FAIL
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.CHILD_PART_NOT_FOUND
										+ Constants.sbomConstants.SEP1 
										+ splitParentId[1]
										+ Constants.sbomConstants.DBLCLN;		
								}
								else if ( splitParentId.length == 1 )
								{
									excelStrfail = excelStrfail
											+ childId
											+ Constants.sbomConstants.SEP1 
											+ splitParentId[0]
											+ Constants.sbomConstants.SEP1
											+ Constants.sbomConstants.FAIL
											+ Constants.sbomConstants.SEP1
											+ Constants.sbomConstants.CHILD_PART_NOT_FOUND
											+ Constants.sbomConstants.SEP1; 
								}
								
							} 
							else if (trimmedLine.contains(Constants.sbomConstants.PARENTID)) 
							{
								parentId = itemDetails[2];
								
								if ( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)))
								{
									/*get overview of error message info */
									String errorMes = "";
									for (int lnind = 3; lnind < itemDetails.length; lnind++) 
									{
										errorMes = errorMes + itemDetails[lnind] + " ";
									}
									parentId = parentId + Constants.sbomConstants.SEP1 + errorMes;
								}
								
							} 
							else if (trimmedLine.contains(Constants.sbomConstants.BADPARENT)) 
							{
								String childId = itemDetails[1];
								String splitParentId[] = parentId.split ("\\?");
								
								if ( splitParentId.length > 1 )
								{	
									excelStrfail = excelStrfail 
										+ childId  
										+ Constants.sbomConstants.SEP1 
										+ splitParentId[0]
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.FAIL
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.PARENT_NOT_FOUND
										+ Constants.sbomConstants.SEP1 
										+ splitParentId[1]
										+ Constants.sbomConstants.DBLCLN;		
								}
								else if ( splitParentId.length == 1 )
								{
									excelStrfail = excelStrfail
										+ childId 
										+ Constants.sbomConstants.SEP1 
										+ splitParentId[0] 
										+ Constants.sbomConstants.SEP1 
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.FAIL 
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.PARENT_NOT_FOUND
										+ Constants.sbomConstants.SEP1;
								}
							}
						}
						if ( trimmedLine.contains (Constants.sbomConstants.ERROR) )
						{
							if ( trimmedLine.contains (Constants.sbomConstants.DRG_ITEM_ERROR) )
							{
								drgCount++;
								if ( drgCount > 1 )
								{
									continue;
								}
							}
							String splitErrorDEtailLine[] = trimmedLine.split ("]");
							
							if ( splitErrorDEtailLine.length > 1 )
							{
								excelStrfail = excelStrfail + splitErrorDEtailLine[1] + "\n";
							}
						}
						if ( dashLineCount == 2 )
						{
							ReportExcel.writeExcelStr(excelStrfail);
							strCreFail++;
							
							/*Update summary report tab */
							readDataLoaderMap(excelStrfail);
							
							/* reset the values */
							dashLineCount = 0;
							drgCount = 0;
							excelStrfail = "";
							startErrorReading = false;
						}
					}
				}
			}
			buffer.close();
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}

	/**
	 *   @param log File
	 *   Method to create createOwnershipChangeReport from log file.
	 */
	private static void createOwnershipChangeReport(File aFile)
	{
		System.out.println(" processing log file " + aFile.getName());

		try 
		{
			/* read this file line by line */
			String inputFileLocn = logFilesDir + "\\" + aFile.getName();
			
			BufferedReader buffer = null;
			buffer = new BufferedReader(new FileReader(inputFileLocn));
			String readLine = "";
			boolean startReading = false;
			boolean startErrorReading = false;
			int dashLineCount = 0;
			String excelStrfail = "";
			while ((readLine = buffer.readLine()) != null) 
			{
				if (readLine.contains(Constants.sbomConstants.STARTREADINGD_FROM_STRING)) 
				{
					startReading = true;
					continue;
				}

				if (startReading == false) 
				{
					continue;
				}
				
				String trimmedLine = readLine.trim().replaceAll("\\s{2,}", " ");
				if (trimmedLine.contains(Constants.sbomConstants.TOTALLINES)) 
				{
					break;
				} 
				else 
				{
					if ( trimmedLine.contains(Constants.sbomConstants.REV) )
					{
						continue;
					}
					String itemDetails[] = trimmedLine.split(" ");
					if (trimmedLine.contains(Constants.sbomConstants.ITEMFOUNDUPDATED)) 
					{
						String itemId = itemDetails[2];
						
						String excelStr = itemId
								+ Constants.sbomConstants.SEP1
								+ Constants.sbomConstants.ACTIONCHANGEGROUPOWNERSHIP
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.SUCCESS 
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.OWNERSHIP_SUCCESS
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.NA;

						/* update the report excel */
						ReportExcel.writeChangeOnwership(excelStr);
						changeOwnerShipSuccess++;
					} 
					else if (trimmedLine.contains(Constants.sbomConstants.REVFOUNDUPDATED)) 
					{
						String Id = itemDetails[2] + itemDetails[3]+ itemDetails[4];
						
						String excelStr = Id
								+ Constants.sbomConstants.SEP1
								+ Constants.sbomConstants.ACTIONCHANGEGROUPOWNERSHIP
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.SUCCESS 
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.OWNERSHIP_SUCCESS
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.NA;

						/* update the report excel */
						ReportExcel.writeChangeOnwership(excelStr);
						changeOwnerShipSuccess++;
					} 
					else if ( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)) || (startErrorReading) )
					{
						startErrorReading = true;
						if ( trimmedLine.contains (Constants.sbomConstants.DASH_LINE ))
						{
							dashLineCount++;
						}
						if ( dashLineCount == 0)
						{
							/* get overview of error message info */
							String errorMes = "";
							for (int lnind = 3; lnind < itemDetails.length; lnind++) 
							{
								errorMes = errorMes + itemDetails[lnind] + " ";
							}
							
							if ( errorMes.contains ( Constants.sbomConstants.ITEMNOTFOUND) )
							{
								errorMes = Constants.sbomConstants.PART_NOT_FOUND;
							}
							
							else if ( errorMes.contains ( Constants.sbomConstants.ITEM_UPDATE_FAILED) )
							{
								errorMes = Constants.sbomConstants.CHANGE_OWNERSHIP_FAIL;
							}
							
							else if ( errorMes.contains ( Constants.sbomConstants.REV_UPDATE_FAILED) )
							{
								errorMes = Constants.sbomConstants.CHANGE_OWNERSHIP_FAIL_REV;
							}
							
							String Id = itemDetails[2];
							if ( trimmedLine.contains ( Constants.sbomConstants.REV_UPDATE_FAILED)) 
							{
								Id = itemDetails[2] + itemDetails[3] + itemDetails[4];
							}
							
							excelStrfail = excelStrfail + Id
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.ACTIONCHANGEGROUPOWNERSHIP
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.FAIL 
									+ Constants.sbomConstants.SEP1 
									+ errorMes
									+ Constants.sbomConstants.SEP1;
						}
						if ( trimmedLine.contains (Constants.sbomConstants.ERROR) )
						{
							String splitErrorDEtailLine[] = trimmedLine.split ("]");
							
							if ( splitErrorDEtailLine.length > 0 )
							{
								excelStrfail = excelStrfail + splitErrorDEtailLine[1] + "\n";
							}
						}
						if ( dashLineCount == 2 )
						{
							/* update the report excel */
							ReportExcel.writeChangeOnwership(excelStrfail);
							changeOwnerShipFail++;
							
							/*Update summary report tab */
							readDataLoaderMap(excelStrfail);
							
							/* reset the values */
							dashLineCount = 0;
							excelStrfail = "";
							startErrorReading = false;
						}
					}
				}
			}
			buffer.close();
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}

	/**
	 *   @param log File
	 *   Method to create createItemRelnsReport from log file.
	 */
	private static void createItemRelnsReport(File aFile)  
	{
		System.out.println(" processing log file " + aFile.getName());

		try 
		{
			/* read this file line by line */
			String inputFileLocn = logFilesDir + "\\" + aFile.getName();
			
			BufferedReader buffer = null;
			buffer = new BufferedReader(new FileReader(inputFileLocn));
			String readLine = "";
			
			boolean startReading = false;
			boolean revFound = false;
			String itemId = null;
			boolean startErrorReading = false;
			int dashLineCount = 0;
			String excelStrfail = "";
			boolean startErrorReading1 = false;
			int dashLineCount1 = 0;
			String excelStrfail1 = "";
			while ((readLine = buffer.readLine()) != null) 
			{
				if (readLine.contains(Constants.sbomConstants.STARTREADINGD_FROM_STRING)) 
				{
					startReading = true;
					continue;
				}

				if (startReading == false) 
				{
					continue;
				}
				String trimmedLine = readLine.trim().replaceAll("\\s{2,}", " ");
				if (trimmedLine.contains(Constants.sbomConstants.TOTALLINES)) 
				{
					break;
				}
				else 
				{
					if (!revFound) 
					{
						String itemDetails[] = trimmedLine.split(" ");
						if ((trimmedLine
								.contains(Constants.sbomConstants.PARENTREVFOUND))
								&& (!( trimmedLine.contains(Constants.sbomConstants.ERRORNO))) ) 
						{
							itemId = itemDetails[2]; //+ itemDetails[3] + itemDetails[4];
							revFound = true;
						}
						else if ((trimmedLine
								.contains(Constants.sbomConstants.PARENT_ITEM_FOUND))
								&& (!( trimmedLine.contains(Constants.sbomConstants.ERRORNO))) ) 
						{
							itemId = itemDetails[2];
							revFound = true;
						}
						else if ( ( trimmedLine.contains(Constants.sbomConstants.SAMEPARENTREV)) &&
								(!( trimmedLine.contains(Constants.sbomConstants.ERRORNO))) )	
						{
							itemId = itemDetails[2];
							revFound = true;
						}
						else if ( ( trimmedLine.contains(Constants.sbomConstants.SAMEPARENTITEM)) &&
								(!( trimmedLine.contains(Constants.sbomConstants.ERRORNO))) )	
						{
							itemId = itemDetails[2];
							revFound = true;
						}
						else if ( ( trimmedLine.contains(Constants.sbomConstants.ERRORNO)) || (startErrorReading) )	
						{
							//System.out.println(" trimmedLineerrno= " + trimmedLine);
							startErrorReading = true;
							if ( trimmedLine.contains (Constants.sbomConstants.DASH_LINE ))
							{
								dashLineCount++;
							}
							if ( dashLineCount == 0)
							{
								/* get the error message */
								String errMess = "";
								for (int lnind = 3; lnind < itemDetails.length; lnind++) 
								{
									errMess = errMess + itemDetails[lnind] + " ";
								}
								
								if ( errMess.contains ( Constants.sbomConstants.PARENTS_NOT_FOUND))
								{
									errMess = Constants.sbomConstants.PARENT_OBJECT_NOTFOUND;
								}
								else if ( errMess.contains ( Constants.sbomConstants.RELN_TYPE_NOT_FOUND))
								{
									errMess = Constants.sbomConstants.INVALID_RELN_TYPE;
								}
								
								else if ( trimmedLine.contains ( Constants.sbomConstants.PARENTITEMNOTFOUND))
								{
									errMess = Constants.sbomConstants.PARENT_ITEM_NOT_FOUND;
								}
								
								String actParentId = "";
								if (( trimmedLine.contains (Constants.sbomConstants.RELN_TYPE_NOT_FOUND )) ||
									( trimmedLine.contains (Constants.sbomConstants.PARENT_REV_NOT_FOUND )))	
								{
									actParentId = itemDetails[2]; //+ itemDetails[3] + itemDetails[4];
								}
								if ( trimmedLine.contains (Constants.sbomConstants.PARENTITEMNOTFOUND ))
								{
									actParentId = itemDetails[1];
								}
								if ( trimmedLine.contains (Constants.sbomConstants.PARENT_ITEM_FOUND ))
								{
									actParentId = itemDetails[2];
								}
								if ( trimmedLine.contains (Constants.sbomConstants.PARENTREVFOUND ))
								{
									actParentId = itemDetails[2] ;//+ itemDetails[3] + itemDetails[4];
								}
								
								excelStrfail = excelStrfail 
										+ actParentId
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.NA
										+ Constants.sbomConstants.SEP1 
										+ Constants.sbomConstants.FAIL 
										+ Constants.sbomConstants.SEP1 
										+ errMess
										+ Constants.sbomConstants.SEP1;
							}
							if ( trimmedLine.contains (Constants.sbomConstants.ERROR) )
							{
								String splitErrorDEtailLine[] = trimmedLine.split ("]");
								
								if ( ( splitErrorDEtailLine.length > 1 ) )
								{
									excelStrfail = excelStrfail + splitErrorDEtailLine[1] + "\n";
								}
							}
							if ( dashLineCount == 2 )
							{
								/* update the report excel */
								ReportExcel.writeServPartRelns(excelStrfail);
								relationAttachFail++;
								
								/*Update summary report tab */
								readDataLoaderMap(excelStrfail);
								
								/* reset the values */
								dashLineCount = 0;
								excelStrfail = "";
								startErrorReading = false;
							}
						
						}
					} 
					else 
					{
						String itemDetails[] = trimmedLine.split(" ");
						
						if ( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)) || (startErrorReading1) )
						{
							String parentId = itemId;
							startErrorReading1 = true;
							if ( trimmedLine.contains (Constants.sbomConstants.DASH_LINE ))
							{
								dashLineCount1++;
							}
							if ( dashLineCount1 == 0)
							{
								/* get the error message */
								String errMess = "";
								for (int lnind = 2; lnind < itemDetails.length; lnind++) 
								{
									errMess = errMess + itemDetails[lnind] + " ";
								}
								
								/*get proper error message */
								if ( errMess.contains ( Constants.sbomConstants.ATTACH_FAILED))
								{
									errMess = Constants.sbomConstants.FAILED_RELN_TYPE;
								}
								else if ( errMess.contains ( Constants.sbomConstants.NO_SECONDARY_OBJECTS_FOUND) )
								{
									errMess = Constants.sbomConstants.SECONDARY_NOT_FOUND;
								}
								
								String childId = "";
								if ( trimmedLine.contains (Constants.sbomConstants.ATTACH_FAILED ))
								{
									childId = itemDetails[2];
								}
								else if ( trimmedLine.contains (Constants.sbomConstants.CHILDITEMNOTFOUND ))
								{
									childId = itemDetails[1];
								}
								excelStrfail1 = excelStrfail1 + parentId
										+ Constants.sbomConstants.SEP1
										+ childId
										+ Constants.sbomConstants.SEP1 
										+ Constants.sbomConstants.FAIL 
										+ Constants.sbomConstants.SEP1 
										+ errMess
										+ Constants.sbomConstants.SEP1;
							}
							if ( trimmedLine.contains (Constants.sbomConstants.ERROR) )
							{
								//System.out.println ( "entered error description for engg serv");
								
								String splitErrorDEtailLine[] = trimmedLine.split ("]");
								for ( int strInd = 0; strInd < splitErrorDEtailLine.length; strInd++  )
								{
									//System.out.println(" splitErrorDEtailLine " + splitErrorDEtailLine[strInd]);
								}
								
								if ( ( splitErrorDEtailLine.length > 1 ) )
								{
									excelStrfail1 = excelStrfail1 + splitErrorDEtailLine[1] + "\n";
								}
							}
							if ( dashLineCount1 == 2 )
							{
								/* update the report excel */
								//System.out.println ( "excelStrprint=" + excelStrfail );
								ReportExcel.writeServPartRelns(excelStrfail1);
								relationAttachFail++;
								
								/*Update summary report tab */
								readDataLoaderMap(excelStrfail1);
								
								/* reset the values */
								dashLineCount1 = 0;
								excelStrfail1 = "";
								startErrorReading1 = false;
								revFound = false;
							}
							
						}
						else if ( !( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)) ) )
						{
							String parentId = itemId;
							String excelStr = parentId
									+ Constants.sbomConstants.SEP1
									+ itemDetails[2]
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.SUCCESS 
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.RELN_ATTACH_SUCCESS
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.NA;
							
							ReportExcel.writeServPartRelns(excelStr);
							relationAttachSuccess++;
							revFound = false;
							
						}
					}
				}
			}
			buffer.close();
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}

	/**
	 *   @param log File
	 *   Method to create createEngineeringServForm from log file.
	 */
	private static void createEngineeringServForm(File aFile)
	{
		System.out.println(" processing log file " + aFile.getName());

		try 
		{
			/* read this file line by line */
			String inputFileLocn = logFilesDir + "\\" + aFile.getName();
			
			BufferedReader buffer = null;
			buffer = new BufferedReader(new FileReader(inputFileLocn));
			String readLine = "";
			
			boolean startReading = false;
			String parentRev = null;
			String excelStrfail = "";
			boolean startErrorReading = false;
			int dashLineCount = 0;
			while ((readLine = buffer.readLine()) != null) 
			{
				if (readLine.contains(Constants.sbomConstants.STARTREADINGD_FROM_STRING)) 
				{
					startReading = true;
					continue;
				}

				if (startReading == false) 
				{
					continue;
				}
				String trimmedLine = readLine.trim().replaceAll("\\s{2,}", " ");
				if (trimmedLine.contains(Constants.sbomConstants.TOTALLINES)) 
				{
					break;
				} 
				else 
				{
					String itemDetails[] = trimmedLine.split(" ");
					if (trimmedLine.contains(Constants.sbomConstants.ITEMFOUND)) 
					{
						continue;
					} 
					else if (trimmedLine.contains(Constants.sbomConstants.REVFOUND)) 
					{
						parentRev = itemDetails[2]; //+ itemDetails[3] + itemDetails[4];
					} 
					else if (trimmedLine.contains(Constants.sbomConstants.ITEMNOTFOUND)) 
					{
						/* get the error message */
						String errMess = "";
						for (int lnind = 3; lnind < itemDetails.length; lnind++) 
						{
							errMess = errMess + itemDetails[lnind] + " ";
						}
						
						if ( errMess.contains(Constants.sbomConstants.ITEMNOTFOUND) )
						{
							errMess = Constants.sbomConstants.ENGGPARTNOTFOUND;
						}
						else if ( errMess.contains(Constants.sbomConstants.ENGG_FORM_PROP_FAILED) )
						{
							errMess = Constants.sbomConstants.ENGG_FORM_PROP_MESSAGE;
						}
						else if ( errMess.contains(Constants.sbomConstants.ENGG_FORM_ATTCH_FAILED) )
						{
							errMess = Constants.sbomConstants.ENGG_FORM_ATTCH_FAILED_MESSAGE;
						}
						
						String excelStr =itemDetails[2] 
								+ Constants.sbomConstants.SEP1
								+ Constants.sbomConstants.ACTIONENGGFORMUPDATE
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.FAIL 
								+ Constants.sbomConstants.SEP1
								+ errMess
								+ Constants.sbomConstants.SEP1
								+ Constants.sbomConstants.NA;

						/* update the report excel */
						ReportExcel.writeEnggPartFormCre(excelStr);
						epServFormCreateFail++;
						
						/*Update summary report tab */
						readDataLoaderMap(excelStr);
					} 
					else if (trimmedLine.contains(Constants.sbomConstants.REVNOTFOUND)) 
					{
						/* get the error message */
						String errMess = "";
						for (int lnind = 3; lnind < itemDetails.length; lnind++) 
						{
							errMess = errMess + itemDetails[lnind] + " ";
						}
						
						if ( errMess.contains(Constants.sbomConstants.ITEMNOTFOUND) )
						{
							errMess = Constants.sbomConstants.ENGGPARTNOTFOUND;
						}
						else if ( errMess.contains(Constants.sbomConstants.ENGG_FORM_PROP_FAILED) )
						{
							errMess = Constants.sbomConstants.ENGG_FORM_PROP_MESSAGE;
						}
						else if ( errMess.contains(Constants.sbomConstants.ENGG_FORM_ATTCH_FAILED) )
						{
							errMess = Constants.sbomConstants.ENGG_FORM_ATTCH_FAILED_MESSAGE;
						}
						
						String excelStr =itemDetails[2] 
								+ Constants.sbomConstants.SEP1
								+ Constants.sbomConstants.ACTIONENGGFORMUPDATE
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.FAIL 
								+ Constants.sbomConstants.SEP1
								+ errMess
								+ Constants.sbomConstants.SEP1
								+ Constants.sbomConstants.NA;

						/* update the report excel */
						ReportExcel.writeEnggPartFormCre(excelStr);
						epServFormCreateFail++;
						
						/*Update summary report tab */
						readDataLoaderMap(excelStr);
					} 
					else if ( (trimmedLine.contains(Constants.sbomConstants.FORM)) || (startErrorReading) )
					{
						if ( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)) || (startErrorReading) )
						{
							//System.out.println(" trimmedLineerrno= " + trimmedLine);
							startErrorReading = true;
							if ( trimmedLine.contains (Constants.sbomConstants.DASH_LINE ))
							{
								dashLineCount++;
							}
							if ( dashLineCount == 0)
							{
								/* get the error message */
								String errMess = "";
								for (int lnind = 3; lnind < itemDetails.length; lnind++) 
								{
									errMess = errMess + itemDetails[lnind] + " ";
								}
								
								if ( errMess.contains(Constants.sbomConstants.ITEMNOTFOUND) )
								{
									errMess = Constants.sbomConstants.ENGGPARTNOTFOUND;
								}
								else if ( errMess.contains(Constants.sbomConstants.ENGG_FORM_PROP_FAILED) )
								{
									errMess = Constants.sbomConstants.ENGG_FORM_PROP_MESSAGE;
								}
								else if ( errMess.contains(Constants.sbomConstants.ENGG_FORM_ATTCH_FAILED) )
								{
									errMess = Constants.sbomConstants.ENGG_FORM_ATTCH_FAILED_MESSAGE;
								}
								
								excelStrfail = excelStrfail + parentRev
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.ACTIONENGGFORMUPDATE
										+ Constants.sbomConstants.SEP1 
										+ Constants.sbomConstants.FAIL 
										+ Constants.sbomConstants.SEP1 
										+ errMess
										+ Constants.sbomConstants.SEP1;
							}
							if ( trimmedLine.contains (Constants.sbomConstants.ERROR) )
							{
								String splitErrorDEtailLine[] = trimmedLine.split ("]:");
								
								if ( ( splitErrorDEtailLine.length > 1 ) &&
										  (!(trimmedLine.contains(Constants.sbomConstants.RELN_CREATE_FAILED))) &&
										  (!(trimmedLine.contains(Constants.sbomConstants.ERROR_SETTING_PROP))))
								{
									excelStrfail = excelStrfail + splitErrorDEtailLine[1] + "\n";
								}
							}
							if ( dashLineCount == 2 )
							{
								/* update the report excel */
								ReportExcel.writeEnggPartFormCre(excelStrfail);
								epServFormCreateFail++;
								
								/*Update summary report tab */
								readDataLoaderMap(excelStrfail);
								
								/* reset the values */
								dashLineCount = 0;
								excelStrfail = "";
								startErrorReading = false;
							}
						} 
						else 
						{
							
							String excelStr =parentRev 
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.ACTIONENGGFORMUPDATE
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.SUCCESS 
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.ENG_FORM_SUCCESS
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.NA;

							/* update the report excel */
							ReportExcel.writeEnggPartFormCre(excelStr);
							epServFormCreateSuccess++;
						}
					}
				}
			}
			buffer.close();
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}

	/**
	 *   @param log File
	 *   Method to create createServicePartFormUpdateMigrationReport from log file.
	 */
	private static void createServicePartFormUpdateMigrationReport(File aFile)
	{
		System.out.println(" processing log file " + aFile.getName());

		try 
		{
			String inputFileLocn = logFilesDir + "\\" + aFile.getName();
			BufferedReader buffer = null;
			buffer = new BufferedReader(new FileReader(inputFileLocn));
			String readLine = "";
			
			boolean startReading = false;
			boolean yesRevFound = false;
			String itemId = null;
			boolean startErrorReading = false;
			int dashLineCount = 0;
			String excelStrfail = "";
			
			while ((readLine = buffer.readLine()) != null) 
			{
				if (readLine.contains(Constants.sbomConstants.STARTREADINGD_FROM_STRING)) 
				{
					startReading = true;
					continue;
				}

				if (startReading == false) 
				{
					continue;
				}
				String trimmedLine = readLine.trim().replaceAll("\\s{2,}", " ");
				
				if (trimmedLine.contains(Constants.sbomConstants.TOTALLINES)) 
				{
					break;
				} 
				else 
				{
					String itemDetails[] = trimmedLine.split(" ");

					if (!yesRevFound) 
					{
						if (trimmedLine.contains(Constants.sbomConstants.REVFOUND)) 
						{
							yesRevFound = true;
							itemId = itemDetails[2]; //+ itemDetails[3]
									//+ itemDetails[4];
						} 
						else if (trimmedLine.contains(Constants.sbomConstants.ITEMNOTFOUND)) 
						{
							itemId = itemDetails[2];
							yesRevFound = false;
							
							/* get overview of error message info *
							String errorMes = "";
							for (int lnind = 3; lnind < itemDetails.length; lnind++) 
							{
								errorMes = errorMes + itemDetails[lnind] + " ";
							}*/
							
							String excelStr =itemId
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.ACTIONSERVICEPARTFORMUPDATE
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.FAIL 
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.PART_NOT_FOUND
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.NA;

							/* update the report excel */
							ReportExcel.writeServFormPartUpd(excelStr);
							spFormUpdateFail++;
							
							/*Update summary report tab */
							readDataLoaderMap(excelStr);
						}
					} 
					else if (yesRevFound) 
					{
						if ( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)) || (startErrorReading) )
						{
							startErrorReading = true;
							if ( trimmedLine.contains (Constants.sbomConstants.DASH_LINE ))
							{
								dashLineCount++;
							}
							if ( dashLineCount == 0)
							{
								/* get overview of error message info */
								String errorMes = "";
								for (int lnind = 3; lnind < itemDetails.length; lnind++) 
								{
									errorMes = errorMes + itemDetails[lnind] + " ";
								}
								
								if ( trimmedLine.contains(Constants.sbomConstants.ERROR_PROPERTY))
								{
									errorMes = Constants.sbomConstants.PROPERTY_FORM_ERROR;
								}
								
								excelStrfail = excelStrfail + itemId
										+ Constants.sbomConstants.SEP1
										+ Constants.sbomConstants.ACTIONSERVICEPARTFORMUPDATE
										+ Constants.sbomConstants.SEP1 
										+ Constants.sbomConstants.FAIL 
										+ Constants.sbomConstants.SEP1 
										+ errorMes
										+ Constants.sbomConstants.SEP1;
							}
							if ( trimmedLine.contains (Constants.sbomConstants.ERROR) )
							{
								
								String splitErrorDEtailLine[] = trimmedLine.split (Constants.sbomConstants.SEP4);
								
								if ( ( splitErrorDEtailLine.length > 1 ) )
								{
									excelStrfail = excelStrfail + splitErrorDEtailLine[1] + "\n";
								}
							}
							if ( dashLineCount == 2 )
							{
								/* update the report excel */
								ReportExcel.writeServFormPartUpd(excelStrfail);
								spFormUpdateFail++;
								
								/*Update summary report tab */
								readDataLoaderMap(excelStrfail);
								
								/* reset the values */
								dashLineCount = 0;
								excelStrfail = "";
								startErrorReading = false;
								yesRevFound = false;
								itemId = null;
							}
						}
						else if ((trimmedLine.contains(Constants.sbomConstants.FORM_NOT_FOUND)))
						{
							String excelStr =itemId
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.ACTIONSERVICEPARTFORMUPDATE
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.FAIL 
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.NO_FORM 
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.NA;

							/* update the report excel */
							ReportExcel.writeServFormPartUpd(excelStr);
							spFormUpdateFail++;
							
							/*Update summary report tab */
							readDataLoaderMap(excelStr);
							
							/* reset the values */
							yesRevFound = false;
							itemId = null;
						}
						else 
						{
							String excelStr =itemId
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.ACTIONSERVICEPARTFORMUPDATE
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.SUCCESS 
									+ Constants.sbomConstants.SEP1 
									+ Constants.sbomConstants.SP_FORM_UPDATE_SUCCESS
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.NA;

							/* update the report excel */
							ReportExcel.writeServFormPartUpd(excelStr);
							spFormUpdateSuccess++;
							
							/* reset the values */
							yesRevFound = false;
							itemId = null;
						}
					}
				}
			}
			buffer.close();
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}

	/**
	 *   @param log File
	 *   Method to create createServicePartMigrationReport from log file.
	 */
	private static void createServicePartMigrationReport(File serPartFile)
	{
		System.out.println(" processing log file " + serPartFile.getName());
		
		try 
		{
			/* read this file line by line */
			String inputFileLocn = logFilesDir + "\\" + serPartFile.getName();
			BufferedReader buffer = null;
			buffer = new BufferedReader(new FileReader(inputFileLocn));
			String readLine = "";
			boolean startReading = false;
			boolean startErrorReading = false;
			int dashLineCount = 0;
			String excelStrfail = "";
			while ((readLine = buffer.readLine()) != null) 
			{
				if (readLine.contains(Constants.sbomConstants.STARTREADINGD_FROM_STRING)) 
				{
					startReading = true;
					continue;
				}

				if (startReading == false) 
				{
					continue;
				}

				String trimmedLine = readLine.trim().replaceAll("\\s{2,}", " ");
				String itemDetails[] = trimmedLine.split(" ");
				
				if (trimmedLine.contains(Constants.sbomConstants.TOTALLINES)) 
				{
					break;
				} 
				else 
				{
					if ((trimmedLine.contains(Constants.sbomConstants.CREATED)) && (itemDetails.length == 8)) 
					{
						
						String excelStr =itemDetails[2] 
								+ Constants.sbomConstants.SEP1
								+ Constants.sbomConstants.ACTIONSERVICEPARTCREATION
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.SUCCESS 
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.SP_CREATED_SUCCESS
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.NA;
								
						/* update the report excel */
						ReportExcel.writeServicePartCrea(excelStr);
						successPartCreation++;
						
					} 
					else if ( (trimmedLine.contains(Constants.sbomConstants.ERRORNO)) || (startErrorReading) )
					{
						//System.out.println(" trimmedLineerrno= " + trimmedLine);
						startErrorReading = true;
						if ( trimmedLine.contains (Constants.sbomConstants.DASH_LINE ))
						{
							dashLineCount++;
						}
						if ( dashLineCount == 0)
						{
							/* get overview of error message info */
							String errorMes = "";
							for (int lnind = 3; lnind < itemDetails.length; lnind++) 
							{
								errorMes = errorMes + itemDetails[lnind] + " ";
							}
							if ( errorMes.contains(Constants.sbomConstants.ITEM_CREATE_FAILED1))
							{
								errorMes = Constants.sbomConstants.CREATION_FAILED;
							}
							else if ( errorMes.contains(Constants.sbomConstants.ITEM_PROPERTY_FAILED)) 
							{
								errorMes = Constants.sbomConstants.PROPERTY_FAILED;
							}
							else if ( errorMes.contains(Constants.sbomConstants.ITEM_PROPERTY_FAILED1)) 
							{
								errorMes = Constants.sbomConstants.PROPERTY_FAILED;
							}
							
							else if ( errorMes.contains(Constants.sbomConstants.ITEM_EXISTS)) 
							{
								errorMes = Constants.sbomConstants.ALREADY_EXISTS;
							}
							
							excelStrfail = excelStrfail + itemDetails[2]
									+ Constants.sbomConstants.SEP1
									+ Constants.sbomConstants.ACTIONSERVICEPARTCREATION
									+ Constants.sbomConstants.SEP1 + Constants.sbomConstants.FAIL 
									+ Constants.sbomConstants.SEP1 + errorMes
									+ Constants.sbomConstants.SEP1;
						}
						if ( trimmedLine.contains (Constants.sbomConstants.ERROR) )
						{
							String splitErrorDEtailLine[] = trimmedLine.split (":");
							
							if ( ( splitErrorDEtailLine.length > 1 ) &&
								  (!(trimmedLine.contains(Constants.sbomConstants.ITEM_CREATE_FAILED))) &&
								  (!(trimmedLine.contains(Constants.sbomConstants.ERROR_SETTING_PROP))))
							{
								excelStrfail = excelStrfail + splitErrorDEtailLine[1] + "\n";
							}
						}
						if ( dashLineCount == 2 )
						{
							//System.out.println ( "Enetered dashline count =");
							/* update the report excel */
							ReportExcel.writeServicePartCrea(excelStrfail);
							failPartCreation++;
							
							/*Update summary report tab */
							readDataLoaderMap(excelStrfail);
							
							/* reset the values */
							dashLineCount = 0;
							excelStrfail = "";
							startErrorReading = false;
						}
					} 
					else if (trimmedLine.contains(Constants.sbomConstants.ITEMEXISTS)) 
					{
						/* get overview of error message info */
						String errorMes = "";
						String errorMes1 = ":";
						for (int lnind = 6; lnind < itemDetails.length; lnind++) 
						{
							errorMes1 = errorMes1 + itemDetails[lnind] + " ";
						}
						errorMes = Constants.sbomConstants.ALREADY_EXISTS;
						
						
						String excelStr =itemDetails[2] 
								+ Constants.sbomConstants.SEP1
								+ Constants.sbomConstants.ACTIONSERVICEPARTCREATION
								+ Constants.sbomConstants.SEP1 
								+ Constants.sbomConstants.FAIL 
								+ Constants.sbomConstants.SEP1
								+ errorMes
								+ Constants.sbomConstants.SEP1
								+ errorMes1;
								
						/* update the report excel */
						ReportExcel.writeServicePartCrea(excelStr);
						failPartCreation++;
						
						/*Update summary report tab */
						readDataLoaderMap(excelStr);
					}
				}
			}
			buffer.close();
		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/**
	 * method to readDataLoaderMap, to update summary report
	 * @param string itemID
	 * @return String data loader Line No
	 */

	private static void readDataLoaderMap(String excelStrfail1 ) 
	{
		//System.out.println ( "Entered readDataLoaderMap" );
		try 
		{
			//System.out.println ( "excelStrfail1 =" + excelStrfail1 );
			/*update the summary report tab */
			String splitPipeLne[] = excelStrfail1.split("\\?");
			//System.out.println ( "splitPipeLne length =" + splitPipeLne.length);
			String itemId = "";
			if ( ( splitPipeLne.length == 5 ) || ( splitPipeLne.length == 4 ) )
			{
				itemId = splitPipeLne[0];
				if ( !(dataLoaderLineItemIdVector.contains(itemId) ) )
				{
					dataLoaderLineItemIdVector.addElement(itemId);
					String dataLoaderLineNo = "";
					
					/* Read map content using Iterator*/
					Set set = dataLoaderMap.entrySet();
					Iterator iterator = set.iterator();
					while(iterator.hasNext()) 
					{
						Map.Entry mapEntry = (Map.Entry)iterator.next();
						String mapVal = (String) mapEntry.getValue();
						if ( mapVal.equals(itemId))
						{	
							//System.out.println ( "key is: "+ mapEntry.getKey() + " & Value is: " );
							//System.out.println ( mapEntry.getValue() );
							dataLoaderLineNo = (String) mapEntry.getKey();
							break;
						}
					}
					String excelSummaryRep = "";
					
					/*excel string for summary report tab */
					excelSummaryRep = dataLoaderLineNo 
				                 + Constants.sbomConstants.SEP1 
				                 + itemId
				                 + Constants.sbomConstants.SEP1 		 
				                 + splitPipeLne[3]
				                 + Constants.sbomConstants.SEP1 		 
				                 + splitPipeLne[4];
					
					ReportExcel.writeSummaryReport (excelSummaryRep);
				}
			}
		} 
		catch (Exception e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 *  Prints usage of the utility
	 */
	private static void printHelp() 
	{
		System.out.println("\nPRINT HELP\n");
		System.out.println("Utility usage is as below\n");
		System.out.println("\"java -jar migrationSbomReports.jar -inputLogDir=<directory where all log files are saved > "
				+ "-DataLoader=<input data loader excel File>\"");
	}
}
