package com.ge.transportation.plm.cam.operations;


import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.Date;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.swt.widgets.Shell;

import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentBOMWindow;
import com.teamcenter.rac.kernel.TCComponentBOPLine;
import com.teamcenter.rac.kernel.TCComponentDataset;
import com.teamcenter.rac.kernel.TCComponentDatasetType;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCComponentGroup;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCComponentRole;
import com.teamcenter.rac.kernel.TCComponentUser;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.ge.transportation.plm.cam.common.Common;
import com.ge.transportation.plm.cam.common.Logger;
import com.ge.transportation.plm.cam.constants.Constants;
import com.ge.transportation.plm.cam.dialogs.CAMItemCreationDialog;
import com.ge.transportation.plm.cam.dialogs.CAMItemConfirmDialog;
import com.teamcenter.services.rac.manufacturing.DataManagementService;
import com.teamcenter.services.rac.manufacturing._2009_10.DataManagement.CreateIn;
import com.teamcenter.services.rac.manufacturing._2009_10.DataManagement.CreateResponse;
import com.teamcenter.soa.client.model.ServiceData;

public class CAMItemCreationOperation
{
	public int CreateResponse 	= 0;
	int check 			= 2;
	public int DatasetNotFound = 0;
	int exitval 		= -9;
	
	String DatasetName 		= null;
	String DSFinal 			= null;
	String DSFinal1 		= null;
	String castpart 		= "NULL";
	String castpartrevision = "Null";
	String fixpart			= "''";
	String fixpartrevision	= "Null";
	String setupNum 		= "null";
	String prefixSetupNum 	= "OP"; //To Prefix OP to setup number
	String cntId 			= "null";
	String mcId 			= "null";
	String SiteId 			= "null";
	String userName 		= null;
	String groupName 		= null;
	String  pwd 			= null;
	String roleName 		= null;
	public String ItemIDFinal 		= null;
	String ItemID  			= null;
	public String UGPART 			= null;
	
	TCComponentDataset SaveD = null;
	TCSession m_session 	= (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
	TCComponentUser user 	= null;
	TCComponentGroup group 	= null;
	TCComponentRole role 	= null;
	CreateResponse resp 	= null;
	TCComponentItemRevision compRev2;
	
	/*CAMSOAHelp(String ID, String machineId ,String setupnumber)
	{
		this.ItemID = ID;
		this.mcId = machineId;
		this.setupNum = setupnumber; 
	}*/	
  
	public int CAMcreateItem() throws ServiceException, TCException
	{
		// Create Item
		DataManagementService dmService = DataManagementService.getService(m_session);			
			
		ItemID = CAMItemCreationDialog.textModel.getText();
		
		CreateIn createIn = new CreateIn();
		
		createIn.clientId = "Test";
		createIn.context = null;
		createIn.relationName = null;
		createIn.target = null;
		createIn.data.type = Constants.BusinessObjects.strGET6NCMachining;
		
		setupNum = CAMItemConfirmDialog.ConfirmSetupNumber.getText();
		SiteId = "GRV"; //No Need -//BPK-03May2017
		mcId = CAMItemConfirmDialog.ConfirmMachineID.getText();
		Logger.write("DEBUG32 - "+"CAMSOAHelp:# mcId="+mcId+"# setupNum="+ prefixSetupNum + setupNum);
		ItemIDFinal = ItemID + "-" + mcId + "-" + prefixSetupNum + setupNum; //Removed Site ID & Prefixed OP for setup number - Pradeep - //BPK-09May2017
		Logger.write("INFO - "+"CAM Item ID to be created: "+ItemIDFinal);
						
		createIn.data.stringProps.put( Constants.BusinessObjects.Properties.strItemID, ItemIDFinal );
		createIn.data.stringProps.put( Constants.BusinessObjects.Properties.strObjectName, ItemIDFinal );
		createIn.data.stringProps.put( Constants.BusinessObjects.Properties.strObjectDesc, " " ); //Modified - Pradeep-20July2017
		createIn.data.stringProps.put(Constants.BusinessObjects.Properties.strIPClassification, "GE - Internal" );
		
		resp = dmService.createObjects(new CreateIn[]{createIn});
		ServiceData sd = resp.serviceData;
		
		System.out.println("Partial Error Size: " + sd.sizeOfPartialErrors() );
		System.out.println("Created Object Size: "+ sd.sizeOfCreatedObjects() );
		
		if(sd.sizeOfPartialErrors() > 0)
		{	
			for (int i=0; i < sd.sizeOfPartialErrors(); i++)
			{
				String strmessage = "";
				String[] errMessages = sd.getPartialError(i).getMessages();				
				for (int j=0; j<errMessages.length; j++)
				{
					strmessage = strmessage+errMessages[j];
					System.out.println("["+j+"]" + errMessages[j]);
				}
				MessageDialog.openError(getShell(), "Partial Error", strmessage);
			}
		}
		
		CreateResponse = resp.output.length;
		System.out.println( "CreateResponse:" + CreateResponse );
		for ( int j = 0; j < resp.output.length; j++ ) 
		{
			for ( int i = 0; i < resp.output[j].objects.length; i++ )
			{
				TCComponent tccomp=resp.output[j].objects[i];
            	if( tccomp instanceof TCComponentBOPLine )
            	{
            		TCComponentBOMWindow bomWindow;
            		TCComponentBOPLine tccompbop=( TCComponentBOPLine ) tccomp;
            		try
            		{
            			bomWindow = tccompbop.window();
            			bomWindow.close();
            		}
            		catch (TCException e) 
            		{
            			e.printStackTrace();

            		}

            	}

			}

		}

		try
		{
			TCComponentItem comp = ( TCComponentItem ) Common.itemQuery( ItemID );
			TCComponentItemRevision compRevision = ( TCComponentItemRevision )comp.getLatestItemRevision();
			TCComponent rel[] = null;
	
		
			rel = compRevision.getRelatedComponents( "IMAN_specification" );
			if( rel != null )
			{
				for( int cnt =0 ; cnt <rel.length; cnt++ )
				{	
					if( rel[cnt].getProperty("object_type").equalsIgnoreCase( "UGMASTER" ) )
					{
						DatasetName = rel[cnt].getProperty( "object_name" );
						boolean KTest = DatasetName.contains("-");
						boolean KTest2 = DatasetName.contains("/");
						if( KTest )
						{
							String[] ddd = DatasetName.split("-");
							DSFinal = ddd[0].toString().concat("-MFG-");
							DSFinal1 = DSFinal.concat(ddd[1]);

						}
						else if( KTest2 )
						{
							String[] ddd = DatasetName.split("/");
							DSFinal = ddd[0].toString().concat("-MFG-");
							DSFinal1 = DSFinal.concat(ddd[1]);

						}
						else
						{
							MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR | SWT.ABORT);
							messageBox1.setText("Error");
							messageBox1.setMessage("DatasetName should be in format 'ITEMID-REV'");
							messageBox1.open();
							Logger.write("ERROR - "+"DatasetName should be in format 'ITEMID-REV'");

						}

						TCComponentDataset DatasetType1 = ( TCComponentDataset )rel[cnt];
						SaveD = DatasetType1.saveAs( DSFinal1 );
						
					}
					else
					{
						DatasetNotFound = -1;
						
					}
					
				}
				
			}
			
		}
		catch ( TCException e1 ) 
		{
			e1.printStackTrace();
			Logger.write(e1);
			
		}
	
		 if( CreateResponse != 0 )
		 try
		 {
			 TCComponentItem comp2 = ( TCComponentItem ) Common.itemQuery( ItemIDFinal );
			 Date date = comp2.getDateProperty( ItemIDFinal );
			 
			 compRev2 = ( TCComponentItemRevision )comp2.getLatestItemRevision();

			 TCComponentDatasetType DatasetType = ( TCComponentDatasetType )m_session.getTypeService().getTypeComponent( Constants.BusinessObjects.strDataset );
			 TCComponent Dataset1 = DatasetType.create( DSFinal1, "test", "UGMASTER" );
			 
			 compRev2.add( Constants.BusinessObjects.Relations.strSpecification, SaveD );	
			 
		 }
		 catch ( TCException e1 )
		 {
			 e1.printStackTrace();
			 Logger.write( e1 );
			 
		 }

		 user 		= new TCComponentUser();
		 setupNum 	= CAMItemConfirmDialog.ConfirmSetupNumber.getText();
		 cntId 		= CAMItemConfirmDialog.ConfirmControllerID.getText();
		 mcId 		= CAMItemConfirmDialog.ConfirmMachineID.getText();

		 try
		 {
			 user 		= m_session.getUser();
			 userName 	= user.getUserId();
			 group 		= m_session.getGroup();
			 groupName 	= group.getFullName();
			 role 		= m_session.getRole();
			 roleName 	= m_session.getRole().toString();
			 castpart 	= "''";
			 castpartrevision = "''";
			 fixpart 	= "''";
			 fixpartrevision = "''";
			 //UGPART 	= ItemID.concat("-").concat("S").concat(setupNum).concat("-").concat(mcId).concat("-").concat("1");
			 UGPART 	= ItemID.concat("-").concat(setupNum).concat("-").concat(mcId).concat("-").concat("1");
			 
			 TCComponentItem comp = (TCComponentItem)  Common.itemQuery( ItemIDFinal );
			 TCComponentItem compI = (TCComponentItem)  Common.itemQuery( ItemID );
			 TCComponentItemRevision compRevision = ( TCComponentItemRevision )comp.getLatestItemRevision();
			 TCComponentItemRevision compRevisionI = ( TCComponentItemRevision )compI.getLatestItemRevision();

			 TCComponentFolder folder = user.getNewStuffFolder();

			 folder.add( Constants.BusinessObjects.Relations.strContents, comp );			

			 String compRevision1 = compRevision.getProperty( Constants.BusinessObjects.Properties.strCurrentRevId );
			 String compRevision11 = compRevisionI.getProperty( Constants.BusinessObjects.Properties.strCurrentRevId );

			 String GETS_CAM_BIN_DIR_UFUNC = System.getenv( Constants.CamUtilsDialogUI.strEnvVar1 );
			 if( GETS_CAM_BIN_DIR_UFUNC.isEmpty() )
			 {
				 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR | SWT.ABORT);
				 messageBox1.setText("Error");
				 messageBox1.setMessage( Constants.CamUtilsDialogUI.strEnvError1);
				 messageBox1.open();
				 Logger.write("ERROR - "+"DatasetName should be in format 'ITEMID-REV'");

			 }
			 else
			 {
				 //String filePath1 = "cmd.exe /C " +GETS_CAM_BIN_DIR_UFUNC+"\\gets_cam_ufunc_new_part.bat -u="+userName+" -p="+" "+" "+ItemIDFinal+" "+compRevision1+" "+ItemID+" "+compRevision11+" "+castpart +" "+castpartrevision+" "+fixpart +" "+fixpartrevision+" "+UGPART+" "+setupNum+" "+cntId+" "+mcId+" "+userName +" -g=\"Operations\"";
				//Modified UGPART to ItemIDFinal for NX Dataset name - Pradeep-20July2017
				 String filePath1 = "cmd.exe /C " +GETS_CAM_BIN_DIR_UFUNC+"\\gets_cam_ufunc_new_part.bat -u="+userName+" -p="+" "+" "+ItemIDFinal+" "+compRevision1+" "+ItemID+" "+compRevision11+" "+castpart +" "+castpartrevision+" "+fixpart +" "+fixpartrevision+" "+ItemIDFinal+" "+setupNum+" "+cntId+" "+mcId+" "+userName +" -g=\"Operations\"";
				 Logger.write("filePath:"+filePath1);
				 System.out.println("filePath:"+filePath1);
				 String[] filePath = {"wscript", GETS_CAM_BIN_DIR_UFUNC+"\\CAMUtils.vbs", filePath1};
				 System.out.println("VBS Path:"+GETS_CAM_BIN_DIR_UFUNC+"\\CAMUtils.vbs");
				 //PartBatch.Bat
				 try 
				 {
					 Process p = Runtime.getRuntime().exec(filePath);

					 exitval = p.waitFor();
					 System.out.println("exit value From Exe : "+exitval);

					 InputStream in = p.getInputStream();
					 ByteArrayOutputStream baos = new ByteArrayOutputStream();
					 int c = -1;
					 while((c = in.read()) != -1)
					 {
						 baos.write(c);

					 }

					 String response = new String(baos.toByteArray());
					 System.out.println("Value of response: " + response);

				 }
				 catch (Exception e) 
				 {
					 e.printStackTrace();
					 Logger.write(e);

				 }

			 }

		 }
		 catch (Exception e)
		 {
			 e.printStackTrace();
			 Logger.write(e);
			 
		 }

		 return exitval;
		 
	}

	private Shell getShell()
	{
		return null;
	}
}
