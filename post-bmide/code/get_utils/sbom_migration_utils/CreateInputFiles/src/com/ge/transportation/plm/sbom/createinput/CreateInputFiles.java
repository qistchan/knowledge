/***************************************************************************************
 * File Name		:	CreateInputFiles.java
 * 
 * Description		:	This class creates different input files for IPS_DATA_UPLOAD
 * 					    and a custom ITK utility.
 *    
 * Author			:	Nisarg Shah (Capgemini India)
 * 
 * Creation Date   	:   Oct 2017
 **************************************************************************************/

package com.ge.transportation.plm.sbom.createinput;

import static com.ge.transportation.plm.sbom.createinput.UtilityConstants.*;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.apache.commons.collections4.map.MultiValueMap;
import org.apache.commons.lang.ArrayUtils;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.DataFormatter;
import org.apache.poi.ss.usermodel.RichTextString;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

/**
 * This class creates different input files for IPS_DATA_UPLOAD and PS_UPLOAD utilities.
 */
@SuppressWarnings("deprecation")
public class CreateInputFiles

{
	protected static Row currentRow;
	protected static String INPUT_FILE_NAME = "";
	protected static FileInputStream EXCEL_FILE;

	/**
	 * Constructor to initiate all file writers
	 */
	public CreateInputFiles()
	{
		try
		{
			EXCEL_FILE = new FileInputStream(new File(INPUT_FILE_NAME));
			/* Log File */
			LOG_WRITER = writerCreator(LOG_FILE, BLANK);
			LOG_WRITER.write(START_TIME + new java.util.Date() + LINE_SEPERATOR);
			System.out.println(NEW_LINE + START_TIME + new java.util.Date() + LINE_SEPERATOR);

			/* Service Part Creation */
			SERVICE_PART_WRITER = writerCreator(SERVICE_PARTS_CREATION_INPUT_FILE,
					SERVICE_PART_CREATION_CONFIG);

			/* Service Form Update */
			SERVICE_FORM_WRITER = writerCreator(SERVICE_FORM_PROPERTIES_INPUT_FILE,
					SERVICE_FORM_UPDATE_CONFIG);

			/* PS_UPLOAD - Service Structures Creation 
			PS_STRUCTURE_WRITER = writerCreator(PS_STRUCTURE_CREATION_INPUT_FILE,
					PS_STRUCTURE_CREATION_CONFIG); */

			/* Service Structures Creation */
			STRUCTURE_WRITER = writerCreator(STRUCTURE_CREATION_INPUT_FILE,
					STRUCTURE_CREATION_CONFIG);

			/* EngParts' Service Form Creation and Attachment*/
			EP_SERVICE_FORM_WRITER = writerCreator(EP_SERVICE_FORM_CREATION_INPUT_FILE,
					EP_SERVICE_FORM_CREATION_CONFIG);

			/* Service Parts' Global Alternate */
			SP_GLOBAL_ALT_WRITER = writerCreator(SP_GLOBAL_ALT_INPUT_FILE, BLANK);

			/* Service Parts' Group ID update */
			SP_GROUP_ID_WRITER = writerCreator(SP_GROUP_ID_INPUT_FILE, SP_GROUP_ID_UPDATE_CONFIG);

			/* Relate Service Parts to three types of attachments*/
			SP_ATTACHMENT_WRITER = writerCreator(SP_ATTACHMENT_INPUT_FILE, SP_ATTACHMENT_CONFIG);

			/* Made From Relation Creation */
			MADE_FROM_RELATION_WRITER = writerCreator(MADE_FROM_REL_INPUT_FILE,
					MADE_FROM_REL_CONFIG);

		} catch (Exception e)
		{
			System.out.println(EXCEPTION + e.getMessage());
			System.exit(1);
		}
	}

	/* main method */
	public static void main(String[] args)
	{
		if (args.length == 1)
		{
			if (HELP_ARGS.contains(args[0]))
			{
				printHelp();
				System.exit(0);
			} else if (args[0].startsWith("-i="))
			{
				INPUT_FILE_NAME = args[0].substring(3).trim();
				if (INPUT_FILE_NAME == null || INPUT_FILE_NAME.isEmpty()
						|| INPUT_FILE_NAME.length() == 0)
				{
					printHelp();
					System.exit(0);
				}
				System.out.println(INPUT_FILE_NAME);
			} else
			{
				printHelp();
				System.exit(0);
			}
		} else
		{
			printHelp();
			System.exit(0);
		}
		createRequiredDirectories();
		CreateInputFiles ifCreator = new CreateInputFiles();
		createMigrationInputFiles();
	}

	/**
	 * This method reads xlsx input file and creates various files, which all will be used as input
	 * for IPS_DATA_UPLOAD and PS_UPLOAD utilities.
	 */
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public static void createMigrationInputFiles()
	{
		@SuppressWarnings({ "rawtypes" })
		MultiValueMap structureMap = new MultiValueMap(); // MultiValueMap for adding child item rows for every parentId

		try
		{
			Workbook workbook = new XSSFWorkbook(EXCEL_FILE);
			Sheet datatypeSheet = workbook.getSheetAt(0);

			int linkDocCount = 0, linkDwgCount = 0, linkPurchSpecCount = 0, linkMadeFromCount = 0, engParts = 0, altPartsCount = 0;

			List<String> serviceItemsList = new ArrayList<String>();
			List<String> engItemsList = new ArrayList<String>();

			// Skipping top two rows
			Iterator<Row> rowIterator = datatypeSheet.iterator();
			if (rowIterator.hasNext())
				rowIterator.next();
			if (rowIterator.hasNext())
				rowIterator.next();

			// Reading the rows one by one
			while (rowIterator.hasNext())
			{
				currentRow = rowIterator.next();
				String tierType = BLANK;
				if (v(TIER_TYPE) != null && v(TIER_TYPE).trim().length() != 0
						&& !v(TIER_TYPE).trim().isEmpty())
				{
					tierType = v(TIER_TYPE).replace(SEMICOLON_SPACE, COMMA);
					tierType = tierType.replace(SPACE_SEMICOLON, COMMA);
					tierType = tierType.replace(SEMICOLON, COMMA);
				}

				String engineFamily = BLANK;
				if (v(ENGINE_FAMILY) != null && v(ENGINE_FAMILY).trim().length() != 0
						&& !v(ENGINE_FAMILY).trim().isEmpty())
				{
					engineFamily = v(ENGINE_FAMILY).replace(SEMICOLON_SPACE, COMMA);
					engineFamily = engineFamily.replace(SPACE_SEMICOLON, COMMA);
					engineFamily = engineFamily.replace(SEMICOLON, COMMA);
					/*
					engineFamily = v(ENGINE_FAMILY).replace(SPACE, BLANK);
					engineFamily = engineFamily.replace(SEMICOLON, COMMA);*/
				}

				String componentId = BLANK;
				try
				{
					if (v(SERVICE_CMP_ID) != null && v(SERVICE_CMP_ID).trim().length() != 0
							&& !v(SERVICE_CMP_ID).trim().isEmpty())
					{
						/*System.out.println(currentRow.getCell(SERVICE_CMP_ID)
								.getRichStringCellValue()); */
						componentId = (currentRow.getCell(SERVICE_CMP_ID).getRichStringCellValue())
								.toString();
						componentId = componentId.replace(SEMICOLON_SPACE, COMMA);
						componentId = componentId.replace(SPACE_SEMICOLON, COMMA);
						componentId = componentId.replace(SEMICOLON, COMMA);
						//System.out.println(componentId);
					}
				} catch (IllegalStateException e)
				{
					System.out.println("\nError : Item " + v(ITEM_ID)
							+ " has invalid Component ID formula.");
					LOG_WRITER.write("\nError : Item " + v(ITEM_ID)
							+ " has invalid Component ID formula.");
				}

				String catalogNum = BLANK;
				if (v(CATALOG_ITEM) != null && v(CATALOG_ITEM).trim().length() != 0
						&& !v(CATALOG_ITEM).trim().isEmpty())
				{
					catalogNum = v(CATALOG_ITEM).replace(SPACE, BLANK);
					catalogNum = catalogNum.replace(SEMICOLON, COMMA);
				}
				//convertRowToPipeDelimited(currentRow);
				//if it is for Service Part
				if (v(LINE_TYPE).equals(NEW_SERVICE_PART))
				{
					/* Check for the revision field */
					String revision_id = DEFAULT_REVISION_ID;
					if (v(REVISION) != null && v(REVISION).trim().length() != 0
							&& !v(REVISION).trim().isEmpty())
					{
						revision_id = v(REVISION).replace(SPACE, BLANK);
					}

					/* Service Part Writer */

					if (!serviceItemsList.contains(v(ITEM_ID)))
					{
						SERVICE_PART_WRITER
								.write(v(ITEM_ID)
										+ DEL
										+ v(ITEM_NAME)
										+ DEL
										+ revision_id
										+ DEL
										+ TYPE_REAL_NAME
										+ DEL
										+ ((v(UOM) == null || v(UOM).trim().length() == 0
												|| v(UOM).trim().isEmpty() || v(UOM)
												.equalsIgnoreCase(EACH)) ? BLANK : v(UOM).trim())
										+ DEL
										+ v(IP_CLASS)
										+ DEL
										+ v(OBJ_WEIGHT)
										+ DEL
										+ v(OBJ_WEIGHT_UOM)
										+ DEL
										+ v(ENG_PRODUCT_LINE)
										+ DEL
										+ ((v(DATA_MODEL).contains(MODEL_BASED)) ? MB
												: ((v(DATA_MODEL).contains(MODEL_CENTRIC)) ? MC
														: BLANK)

										)

										+ DEL + v(ECCN) + DEL + v(ECCN_SOURCE) + DEL + v(OBJ_EVI)
										+ DEL + v(CTQ) + DEL + v(CCC) + DEL + v(ECC) + DEL + DEL
										+ v(HOMOLOGATION) + DEL + v(CRITICAL_PART) + DEL
										+ v(ENG_MAKE_BUY) + NEW_LINE);

						/* Service Form Update Writer */
						SERVICE_FORM_WRITER
								.write(v(ITEM_NAME) + DEL + v(ITEM_ID) + DEL + componentId + DEL
										+ v(SERVICEABLE) + DEL + v(REPAIRABLE) + DEL
										+ v(SERIALIZED) + DEL + v(POS_TRACKED) + DEL
										+ v(SERVICE_ITEM_TYPE) + DEL + tierType + DEL
										+ engineFamily + DEL + catalogNum + NEW_LINE);

						/* Service Parts' Owning Group update */
						SP_GROUP_ID_WRITER.write(v(ITEM_ID) + NEW_LINE);

						/* Relate Service Parts to Document */
						if (v(LINK_DOC) != null && v(LINK_DOC).trim().length() != 0
								&& !v(LINK_DOC).isEmpty())
						{
							SP_ATTACHMENT_WRITER.write(v(ITEM_ID) + DEL + revision_id + DEL
									+ v(LINK_DOC) + DEL + SP_DOC_RELATION_NAME + NEW_LINE);
							linkDocCount++;
						}

						/* Relate Service Parts to Drawing */
						if (v(LINK_DWG) != null && v(LINK_DWG).trim().length() != 0
								&& !v(LINK_DWG).isEmpty())
						{
							SP_ATTACHMENT_WRITER.write(v(ITEM_ID) + DEL + revision_id + DEL
									+ v(LINK_DWG) + DEL + SP_DWG_RELATION_NAME + NEW_LINE);
							linkDwgCount++;
						}
						/* Relate Service Parts to Purchase Specifications */
						if (v(LINK_PURCHSPEC) != null && v(LINK_PURCHSPEC).trim().length() != 0
								&& !v(LINK_PURCHSPEC).isEmpty())
						{
							SP_ATTACHMENT_WRITER.write(v(ITEM_ID) + DEL + revision_id + DEL
									+ v(LINK_PURCHSPEC) + DEL + SP_PURCHSPEC_RELATION_NAME
									+ NEW_LINE);
							linkPurchSpecCount++;
						}
						/* Relate Service Parts to MadeFrom */
						if (v(LINK_MADEFROM) != null && v(LINK_MADEFROM).trim().length() != 0
								&& !v(LINK_MADEFROM).isEmpty())
						{
							MADE_FROM_RELATION_WRITER.write(v(ITEM_ID) + DEL + v(LINK_MADEFROM)
									+ DEL + SP_MADEFROM_RELATION_NAME + NEW_LINE);
							linkMadeFromCount++;
						}
						serviceItemsList.add(v(ITEM_ID));
					} else
					{
						LOG_WRITER.write(DUPLICATE_ENTRY + v(ITEM_ID));
					}

				}

				else if (v(LINE_TYPE).equals(EXISTING_ENG_PART))
				{
					/* EngParts' Service Form Creation - ITEM_ID will be used as the Service Form's NAME */
					if (!engItemsList.contains(v(ITEM_ID)))
					{
						EP_SERVICE_FORM_WRITER.write(v(ITEM_NAME) + DEL + componentId + DEL
								+ v(SERVICEABLE) + DEL + v(REPAIRABLE) + DEL + v(SERIALIZED) + DEL
								+ v(POS_TRACKED) + DEL + v(SERVICE_ITEM_TYPE) + DEL + tierType
								+ DEL + engineFamily + DEL + catalogNum + DEL + v(ITEM_ID)
								+ NEW_LINE);
						engParts++;
						engItemsList.add(v(ITEM_ID));
					} else
					{
						LOG_WRITER.write(DUPLICATE_ENTRY + v(ITEM_ID));
					}
				}

				/*	Add child item rows for each assembly */
				if (v(PARENT_ID) != null && v(PARENT_ID).trim().length() != 0
						&& !v(PARENT_ID).isEmpty())
				{
					structureMap.put(v(PARENT_ID), currentRow.getRowNum());
					/*	STRUCTURE_WRITER.write(v(PARENT_ID) + DEL + v(ITEM_ID) + DEL + v(QTY) + DEL
								+ v(SEQ) + NEW_LINE); - can not write it here, as the same parent might come again later. IPS_DATA_UPLOAD fails if the parent has existing BVR with -bom mode. */
				}

				/* Global Alternate */
				String globalAltStr = v(GLOBAL_ALT);
				if (globalAltStr != null && !globalAltStr.trim().isEmpty()
						&& globalAltStr.trim().length() != 0)
				{
					globalAltStr = globalAltStr.replace(SPACE, BLANK);
					String globalAltArray[] = globalAltStr.split(SEMICOLON);
					for (int i = 0; i < globalAltArray.length; i++)
					{
						SP_GLOBAL_ALT_WRITER.write(v(ITEM_ID) + DEL + globalAltArray[i].trim()
								+ NEW_LINE);
						altPartsCount++;
					}

				}
			}

			LOG_WRITER.write(TOTAL_SERVICE_PARTS + serviceItemsList.size() + NEW_LINE);
			LOG_WRITER.write(TOTAL_DOCUMENTS_TO_ATTACH + linkDocCount + NEW_LINE);
			LOG_WRITER.write(TOTAL_DRAWINGS_TO_ATTACH + linkDwgCount + NEW_LINE);
			LOG_WRITER.write(TOTAL_PURCHSPEC_TO_ATTACH + linkPurchSpecCount + NEW_LINE);
			LOG_WRITER.write(TOTAL_MADEFROM_TO_ATTACH + linkMadeFromCount + NEW_LINE);
			LOG_WRITER.write(TOTAL_ALTERNATE_PARTS_TO_ADD + altPartsCount + NEW_LINE);
			LOG_WRITER.write(TOTAL_ENG_PARTS_FOR_SERVICE_FORM_CREATON + engParts + NEW_LINE);
			LOG_WRITER.write(LINE_SEPERATOR);

			/* Write Structures */
			LOG_WRITER.write(STRUCTURE_START_TIME + new java.util.Date() + NEW_LINE);
			Set<String> parentIDs = structureMap.keySet();
			Iterator parentIDsIterator = parentIDs.iterator();
			LOG_WRITER.write(TOTAL_STRUCTURES + parentIDs.size() + NEW_LINE);
			/*PS_STRUCTURE_WRITER.write(NEW_LINE + HASH_SIGN + TOTAL_STRUCTURES + parentIDs.size()
					+ NEW_LINE);*/
			while (parentIDsIterator.hasNext())
			{
				Object parentID = parentIDsIterator.next();

				/*PS_STRUCTURE_WRITER.write(NEW_LINE + parentID + DEL + DEFAULT_REVISION_ID + DEL
						+ TYPE_REAL_NAME + DEL + ZERO + NEW_LINE);*/

				Collection childRows = (Collection) structureMap.get(parentID);
				Iterator childRowsIterator = childRows.iterator();
				while (childRowsIterator.hasNext())
				{
					Row cRow = datatypeSheet.getRow((int) childRowsIterator.next());
					/*PS_STRUCTURE_WRITER.write(rv(cRow, ITEM_ID) + DEL + DEFAULT_REVISION_ID + DEL
							+ TYPE_REAL_NAME + DEL + ONE + DEL + rv(cRow, SEQ) + DEL
							+ rv(cRow, QTY) + NEW_LINE);*/
					STRUCTURE_WRITER.write(parentID + DEL + rv(cRow, ITEM_ID) + DEL + rv(cRow, QTY)
							+ DEL + rv(cRow, SEQ) + NEW_LINE);
				}
			}
			LOG_WRITER.write(STRUCTURE_END_TIME + new java.util.Date() + LINE_SEPERATOR);
			workbook.close();
		} catch (FileNotFoundException e)
		{
			System.out.println(EXCEPTION + e.getMessage());
		} catch (IOException e)
		{
			System.out.println(EXCEPTION + e.getMessage());
		} finally
		{
			try
			{
				if (SERVICE_PART_WRITER != null)
				{
					SERVICE_PART_WRITER.close();
				}
				if (SERVICE_FORM_WRITER != null)
				{
					SERVICE_FORM_WRITER.close();
				}
				if (EP_SERVICE_FORM_WRITER != null)
				{
					EP_SERVICE_FORM_WRITER.close();
				}
				if (SP_GLOBAL_ALT_WRITER != null)
				{
					SP_GLOBAL_ALT_WRITER.close();
				}
				if (SP_GROUP_ID_WRITER != null)
				{
					SP_GROUP_ID_WRITER.close();
				}
				if (SP_ATTACHMENT_WRITER != null)
				{
					SP_ATTACHMENT_WRITER.close();
				}
				if (MADE_FROM_RELATION_WRITER != null)
				{
					MADE_FROM_RELATION_WRITER.close();
				}
				/*
				if (PS_STRUCTURE_WRITER != null)
				{
					PS_STRUCTURE_WRITER.close();
				}*/
				if (STRUCTURE_WRITER != null)
				{
					STRUCTURE_WRITER.close();
				}
				if (LOG_WRITER != null)
				{
					LOG_WRITER.write(END_TIME + new java.util.Date() + LINE_SEPERATOR);
					System.out.println(END_TIME + new java.util.Date() + LINE_SEPERATOR);
					LOG_WRITER.close();
				}

			} catch (IOException ex)
			{
				System.out.println(EXCEPTION + ex.getMessage());
			}
		}
	}

	/**
	 * This method converts each row of xlsx to pipe delimited format.
	 * 
	 * @param currentRow
	 */
	public static void convertRowToPipeDelimited(Row currentRow)
	{
		int count = 0;
		Iterator<Cell> cellIterator = currentRow.iterator();

		try
		{
			while (cellIterator.hasNext())
			{
				if (!ArrayUtils.contains(AVOID_COLUMNS, count))
				{
					Cell currentCell = cellIterator.next();

					DataFormatter formatter = new DataFormatter();
					String fText = formatter.formatCellValue(currentCell);
					if (fText == null || (fText.trim().length() == 0))
					{
						fText = DEL;
					}
					INPUT_FORMAT_WRITER.write(fText + DEL);

				}
			}
			INPUT_FORMAT_WRITER.write(NEW_LINE);
		} catch (IOException e)
		{
			System.out.println(EXCEPTION + e.getMessage());
		}
	}

	/**
	 * returns Value at ColumnId in the current row
	 * 
	 * @param columnId
	 */
	public static String v(int columnId)
	{
		return (FORMATTER.formatCellValue(currentRow.getCell(columnId)));
	}

	/**
	 * returns Value at ColumnId in the mentioned row
	 * 
	 * @param cRow
	 *            - row
	 * @param columnId
	 */
	public static String rv(Row cRow, int columnId)
	{
		return (FORMATTER.formatCellValue(cRow.getCell(columnId)));
	}

	/**
	 * Returns Writer for the specified file and also writes the config mentioned
	 * 
	 * @param iFile
	 * @param config
	 * @return
	 * @throws IOException
	 */
	public static Writer writerCreator(String iFile, String config) throws IOException
	{
		Writer writer = new BufferedWriter(
				new OutputStreamWriter(new FileOutputStream(iFile), UTF8));
		writer.write(config);
		return writer;
	}

	/**
	 * Creates two directories. 1) Input_Files 2) Logs
	 */
	public static void createRequiredDirectories()
	{

		/*Input_Files dir creation */
		File inpDir = new File(INPUT_DIR_NAME);

		// if the directory does not exist, create it
		if (!inpDir.exists())
		{
			try
			{
				inpDir.mkdir();
			} catch (Exception e)
			{
				try
				{
					LOG_WRITER.write(DIR_CREATION_ERROR + INPUT_DIR_NAME + "\nError : "
							+ e.getMessage());
					System.out.println(DIR_CREATION_ERROR + INPUT_DIR_NAME + "\nError : "
							+ e.getMessage());
				} catch (IOException e1)
				{
					e1.printStackTrace();
				}
				System.exit(1);
			}
		}

		/*Logs dir creation */
		File logsDir = new File(LOGS_DIR_NAME);

		// if the directory does not exist, create it
		if (!logsDir.exists())
		{
			try
			{
				logsDir.mkdir();
			} catch (Exception e)
			{
				try
				{
					LOG_WRITER.write(DIR_CREATION_ERROR + LOGS_DIR_NAME + "\nError : "
							+ e.getMessage());
					System.out.println(DIR_CREATION_ERROR + LOGS_DIR_NAME + "\nError : "
							+ e.getMessage());
				} catch (IOException e1)
				{
					e1.printStackTrace();
				}
				System.exit(1);
			}
		}
	}

}