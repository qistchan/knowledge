package com.util;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

import jxl.*;
import jxl.read.biff.BiffException;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.StringTokenizer;


/**
 * This class reads excel primary project numbers and writes into TCXML file.
 * 
 * @author
 *
 */
public class CreateAdminLOVsTCXML
{
	
	public void createTCXML( String siteID, String TCVersion, String valueCat, String uniqueID, String filePath ) throws BiffException, IOException
	{
		
		String TCxmlStart = new String ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n<TCXML xmlns=\"http://www.tcxml.org/Schemas/TCXMLSchema\" format=\"high_level\">\n");
		
		
		FileInputStream fs = new FileInputStream(filePath);
		File inputFile = new File(filePath);
		String absFilePath = inputFile.getAbsoluteFile().getParentFile().getAbsolutePath();
		System.out.println("Path of the inputFile:" + absFilePath);
		Workbook wb = Workbook.getWorkbook(fs);

		// To get the access to the sheet
		Sheet sh = wb.getSheet("Export Worksheet");

		// To get the number of rows present in sheet
		int totalNoOfRows = sh.getRows();
		
		System.out.println("No. of rows:" + totalNoOfRows);
		
		ArrayList<String> IdList = new ArrayList<String>();
		
		//Creation of TCXML file
		File outputFile = new File( absFilePath + "/" + valueCat + "_Output.xml");
		System.out.println("Path of the outputFile: " + outputFile);
		
	    BufferedWriter bw = new BufferedWriter( new FileWriter( outputFile ) );
	   
	    DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	    Date systemDate = new Date();
	    
	    String date = dateFormat.format(systemDate);
	    System.out.println("System Date: " + date);
	    
	    StringTokenizer st = new StringTokenizer(date, " "); 
	    String str1,str2,creationDate ;
	    StringBuilder sb = new StringBuilder();
	    
	    while(st.hasMoreTokens()) { 
	    str1 = st.nextToken(); 
	    str2 = st.nextToken(); 
	    System.out.println(str1 + "\t" + str2); 
	    sb.append(str1 + "T" + str2 + "Z");
	    }
	    
	    creationDate = sb.toString();
	    System.out.println("Creation Date: " + creationDate); 
	    
	    //START writing of TCXML file
        bw.write(TCxmlStart);
		for (int row = 1, id = 100; row < totalNoOfRows; row++)
		{
			String lovVal = new String (sh.getCell(0, row).getContents());
			String lovValDesc = new String (sh.getCell(1, row).getContents());
			
			//Handling special characters like "", & etc in lov value description
			lovValDesc = lovValDesc.replaceAll( "&", "&amp;" );
			lovValDesc = lovValDesc.replaceAll( "\"", "&quot;" );
			/*lovValDesc = lovValDesc.replaceAll( """, "&ldquo;" );
			lovValDesc = lovValDesc.replaceAll( """, "&rdquo;" );
			lovValDesc = lovValDesc.replaceAll( "'", "&lsquo;" );
			lovValDesc = lovValDesc.replaceAll( "'", "&rsquo;" );*/
			lovValDesc = lovValDesc.replaceAll( ">", "&gt;" );
			lovValDesc = lovValDesc.replaceAll( "<", "&lt;" );
			
			String Id = "id" + Integer.toString(id);
			
			String one = new String("<Fnd0AdminLOVValue creation_date=\"" + creationDate + "\" date_released=\"\"\n"
		      		+ "ead_paragraph=\"\" " );
			String idstr = "elemId=\"" + Id + "\"\n";
			
			String lovValuestr = "fnd0lov_value=\"" + lovVal + "\"\n";
			
			String lovValueDesc = "fnd0lov_description=\"" + lovValDesc + "\"\n";
			
			String ObjName = new String("");
			
			if ( valueCat.equals("PrimProjNumbersLOV") )
			{
			    ObjName = "prim_proj_lov_" + lovVal;
			}
			if ( valueCat.equals("SecProjNumbersLOV") )
			{
				ObjName = "sec_proj_lov_" + lovVal;	
			}
			String two = new String("fnd0lov_category=\""+ valueCat + "\"\n"
	      		+ "gov_classification=\"\" ip_classification=\"\" last_mod_date=\"" + creationDate + "\"  license_list=\"\" object_desc=\"\"\n"
	      		+ "object_name=\"" + ObjName + "\" owning_group=\"#id14\" owning_organization=\"\"\n"
	      		+ "owning_project=\"\" owning_site=\"#id16\" owning_user=\"#id18\" project_list=\"\"\n"
	      		+ "release_status_list=\"\" revision_number=\"0\">\n");
			
			id++;
			
			String gsID = "id" + Integer.toString(id);
			
			String gsLabel = Integer.toString(id) + uniqueID;
			
			id++;
			
			String gsIDstr = "<GSIdentity elemId=\"" + gsID + "\" label=\"" + gsLabel + "\"/>\n"
		      		+ "</Fnd0AdminLOVValue>\n";
			
			String total = one + idstr + lovValuestr + lovValueDesc + two + gsIDstr;
			
			IdList.add(Id);
			
			bw.write( total );
			
		}
		
		
		String TCxmlEnd = new String ( "<Group elemId=\"id13\" list_of_role=\"#id18\" name=\"dba\" object_full_name=\"dba\"\nowning_site=\"#id16\" transient_island_id=\"1\">\n" +
				                       "<GSIdentity elemId=\"id14\" label=\"AcZBPS6IYtcuYD\"/>\n</Group>\n<POM_imc elemId=\"id15\" owning_site=\"#id16\" site_id=\"" + siteID + "\" transient_island_id=\"0\">\n" +
				                        "<GSIdentity elemId=\"id16\" label=\"w9TBPSppYtcuYD\"/>\n</POM_imc>\n<User elemId=\"id17\" owning_site=\"#id16\" transient_island_id=\"1\" user_id=\"infodba\">\n" +
				                        "<GSIdentity elemId=\"id18\" label=\"AkVBPS6IYtcuYD\"/>\n</User>\n<Role creation_date=\"\" elemId=\"id19\" last_mod_date=\"\" owning_group=\"#id14\" owning_site=\"#id16\"\n" +
				                        "owning_user=\"#id18\" role_name=\"DBA\" transient_island_id=\"0\">\n<GSIdentity elemId=\"id20\" label=\"AYaBPS6IYtcuYD\"/>\n</Role>\n" +
				                        "<Header author=\"infodba\" date=\"\" elemId=\"id21\" originatingSite=\""+ siteID + "\"\ntargetSite=\""+ siteID +"\" time=\"\" version=\""+ TCVersion + "\">\n" +
				                        "<TransferFormula elemId=\"id22\">\n<TransferMode elemId=\"id23\" gov_classification=\"\" ip_classification=\"\" license_list=\"\"\nobject_name=\"TIEExportDefaultTM\" owning_site=\"id16\" project_list=\"\"/>\n" +
				                        "<Reason elemId=\"id24\"></Reason>\n</TransferFormula>\n");
		
		System.out.println("No of Admin LOVs added to TCXML file : "+ IdList.size());
		
		String traverse1 = "<TraverseRootRefs>";
		for ( int j = 0; j < IdList.size() ; j++)
		{
			String traverseID = "#" + IdList.get(j);
			
			if ( j+1 != IdList.size() )
			{
				traverseID = traverseID + " ";
			}
			traverse1 = traverse1 + traverseID;
		}
		
		traverse1 = traverse1 + "</TraverseRootRefs>";
		TCxmlEnd = TCxmlEnd + traverse1 + "\n</Header>\n</TCXML>\n";
		bw.write( TCxmlEnd );
		bw.close();
		//END writing of TCXML file
	}

	
	public static void main(String args[]) throws BiffException, IOException
	{
		Scanner in = new Scanner(System.in);
		String siteID = new String("");
		String sAdminLovCat = new String("");
		String sFilePath = new String("");
		String sTCVersion = new String("");
		String sUniqueID = new String("");
		
		System.out.println("In here");
		while ( siteID.isEmpty() )
		{
			System.out.println("Please enter a valid site ID ( ex: -1410311200):");
			siteID = in.nextLine();
			
		}
		
		while ( sTCVersion.isEmpty() )
		{
			System.out.println("Please enter a valid TC Version ( ex: Teamcenter V11000.2.2.20_20160504.00):");
			sTCVersion = in.nextLine();
			
		}
		
		while ( sAdminLovCat.isEmpty() )
		{
			System.out.println("Please enter a valid Value Category: (eg: PrimProjNumbersLOV (or) SecProjNumbersLOV ) ");
			sAdminLovCat = in.nextLine();
			
		}
		
		while ( sUniqueID.isEmpty() )
		{
			System.out.println("Please enter a valid unique id: (ex: B1J9Wu4Q6oxYUE) ");
			sUniqueID = in.nextLine();
			
		}
		
		while ( sFilePath.isEmpty() )
		{
			System.out.println("Please enter a valid Value FilePath: (ex: C:\\PLM20\\ats_primary.xls)");
			sFilePath = in.nextLine();
			
		}
		
		
		System.out.println("You entered string "+siteID);
		System.out.println("You entered string "+sTCVersion);
		System.out.println("You entered string "+sAdminLovCat);
		System.out.println("You entered string "+sUniqueID);
		System.out.println("You entered string "+sFilePath);
	    in.close();
		
		CreateAdminLOVsTCXML DT = new CreateAdminLOVsTCXML();
		DT.createTCXML( siteID, sTCVersion, sAdminLovCat, sUniqueID, sFilePath );
	}
}
