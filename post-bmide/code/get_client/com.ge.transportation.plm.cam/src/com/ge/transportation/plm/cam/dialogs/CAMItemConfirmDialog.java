package com.ge.transportation.plm.cam.dialogs;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Arrays;

import org.eclipse.jface.dialogs.Dialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.ge.transportation.plm.cam.common.Common;
import com.ge.transportation.plm.cam.common.Logger;
import com.ge.transportation.plm.cam.operations.CAMItemCreationOperation;

public class CAMItemConfirmDialog extends Dialog {
	 static Text ConfirmSite;
	 static Text ConfirmModelNumber;
	 static Text ConfirmCastingPart;
	 static Text ConfirmFixturePart;
	 public static Text ConfirmMachineID;
	 public static Text ConfirmControllerID;
	 public static Text ConfirmSetupNumber;
	 static Text ConfirmMfgItemTitle;
	 static Text ConfirmECO;
	 
	 static Button buttonOk;
	 static Button buttonCancel;
	 Button buttonEdit;
	 
	 int sIte_Seq;	 
	 
	 boolean F1 = false;
	 boolean deleteFlag = false;
	 
	 String ConfirmModelNumber1;
	 String ConfirmModelNumberRev;
	 String ConfirmCastingPart1;
	 String ConfirmCastingPart1Rev;
	 String ConfirmFixturePart1;
	 String ConfirmFixturePart1Rev;
	 String s,s1,s2;
	 String ConfirmSite1;
	 String sCurrentLine;
	 String sCurrentLine1;
	 String ContollerID;
	 String ContollerID1;
	 String iTem_Id= null;
	 String selectedValue = null;
	 String test1 = null;
	 String SiteSelected = null;
	 String MachineNo = null;
	 Shell tmpparentshell;
	 
	 TCSession m_session = (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
	 
	 protected CAMItemConfirmDialog(Shell parentshell) 
	 {
		 super(parentshell);
		 tmpparentshell = parentshell;
		 
	 }
	 
	 protected Control createDialogArea(Composite parent) 
	 {
		 final Composite DialogArea = (Composite) super.createDialogArea(parent);
		 DialogArea.getShell().setText("Confirm Dialog");
		 GridLayout gridLayout = new GridLayout();
		 gridLayout.numColumns = 3;
		 DialogArea.setLayout(gridLayout);
		 Logger.write("INFO - "+"Confirm Dialog opened for MFG ITEM Creation");
		 
		 /*Text1 */
		 new Label(DialogArea, SWT.NULL).setText("Site:");
		 ConfirmSite = new Text(DialogArea, SWT.READ_ONLY);
		 GridData gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 ConfirmSite1 = CAMItemCreationDialog.labelSite.getText();
		 ConfirmSite.setText(ConfirmSite1);
		 gridData.horizontalSpan = 2;
		 ConfirmSite.setText(ConfirmSite1);
		 ConfirmSite.setLayoutData(gridData);
		
		 /*Text 2*/
		 new Label(DialogArea, SWT.NULL).setText("CAD Model ID/Revision:"); //Modified - Pradeep-20July2017
		 ConfirmModelNumber =  new Text(DialogArea, SWT.READ_ONLY);
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 ConfirmModelNumber1 = CAMItemCreationDialog.textModel.getText();
		 ConfirmModelNumberRev = CAMItemCreationDialog.REVID.getText();
		 
		 if((ConfirmModelNumber1=="")||(ConfirmModelNumberRev==""))
		 {
			 ConfirmModelNumber.setText("");
			 
		 }
		 else
		 {
			 s=ConfirmModelNumber1+"/"+ConfirmModelNumberRev;
			 //gridData.horizontalSpan = 1;
			 ConfirmModelNumber.setText(s);
			 
		 }
		 
		 gridData.horizontalSpan = 2;	  
		 ConfirmModelNumber.setLayoutData(gridData);
		 /*Text3*/
		 new Label(DialogArea, SWT.NULL).setText("CastingPart/Revision:");
		 ConfirmCastingPart =  new Text(DialogArea, SWT.READ_ONLY);
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 ConfirmCastingPart1 = CAMItemCreationDialog.labelCasting.getText();
		 ConfirmCastingPart1Rev = CAMItemCreationDialog.labelCastinglimgREVID.getText();
		   
		 //gridData.horizontalSpan = 1;
		 
		 if((ConfirmCastingPart1=="")||(ConfirmCastingPart1Rev==""))
		 {
			 ConfirmCastingPart.setText("");
			 
		 }
		 else
		 {
			 s1=ConfirmCastingPart1+"/"+ConfirmCastingPart1Rev;
			 //gridData.horizontalSpan = 1;
			 ConfirmCastingPart.setText(s1);
			 
		 }
		 
		 gridData.horizontalSpan = 2;
		 ConfirmCastingPart.setLayoutData(gridData);
		 /*Text 4*/
		 new Label(DialogArea, SWT.NULL).setText("Fixture Part/Revision:");
		 ConfirmFixturePart =  new Text(DialogArea, SWT.READ_ONLY);
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 ConfirmFixturePart1 = CAMItemCreationDialog.labelFP.getText();
		 ConfirmFixturePart1Rev = CAMItemCreationDialog.labelFPlimgREVID.getText();
		 if((ConfirmFixturePart1=="")||(ConfirmFixturePart1Rev==""))
		 {
			 ConfirmFixturePart.setText("");
			 
		 }
		 else
		 {
			 s2=ConfirmFixturePart1+"/"+ConfirmFixturePart1Rev;
			 //gridData.horizontalSpan = 1;
			 ConfirmFixturePart.setText(s2);
			 
		 }
		 
		 gridData.horizontalSpan = 2;
		 ConfirmFixturePart.setLayoutData(gridData);
		 /*Text 5*/
		 new Label(DialogArea, SWT.NULL).setText("Machine ID:");
		 ConfirmMachineID =  new Text(DialogArea, SWT.READ_ONLY);
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 
		 String ConfirmMachineID1 = CAMItemCreationDialog.labelMID.getText();
		 String[] MIDs = ConfirmMachineID1.split(" - ");
		 
		 ArrayList<String> list = new ArrayList<String>(Arrays.asList(MIDs));
		 
		 String k = (String) list.get(0);
		 ConfirmMachineID.setText(k);
		 gridData.horizontalSpan = 2;
		 ConfirmMachineID.setLayoutData(gridData);
		 /*Controller ID's*/
		 
		 SiteSelected = CAMItemCreationDialog.labelSite.getText();
		 MachineNo = k;
		 try 
		 {
			 //DEBUG
			 Logger.write("#DEBUG - "+"SiteSelected="+SiteSelected+"### MachineNo="+MachineNo);
			 if((SiteSelected!=null) && (MachineNo!=null))
			 {
				 ContollerID1 = get_ControlIDs(SiteSelected,MachineNo);
				 if(ContollerID1!=null)
				 {
					 boolean whitespacecheck = Common.containsWhiteSpace(ContollerID1);
					 if(whitespacecheck)
					 {
						 ContollerID = ContollerID1.replaceAll("\\s", "_");
						 
					 }
					 else
					 {
						 ContollerID = ContollerID1;
						 
					 }
					 //DEBUG
					 //Logger.write("DEBUG - "+"1)ContollerID="+ContollerID);
					 
				 }
				 /*else if(ContollerID1==null)
				 {
					 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					 messageBox1.setText("ERROR");
					 messageBox1.setMessage("Unable to get Controller ID for selected Machine, Controller ID will be set to UNKNOWN");
					 messageBox1.open();
				     
					 
					 ContollerID = "UNKNOWN";
					 //DEBUG
					 //Logger.write("DEBUG - "+"2)ContollerID="+ContollerID);
					 
				 }*/
				 
			 }
			 else if(SiteSelected==null) 
			 {
				 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
				 messageBox1.setText("ERROR");
				 messageBox1.setMessage("User not selected Site");
				 messageBox1.open();
				 
			 }
			 else if(MachineNo==null) 
			 {
				 MessageBox messageBox1 = new MessageBox(getShell(),SWT.ERROR|SWT.OK);
				 messageBox1.setText("ERROR");
				 messageBox1.setMessage("User not selected Machine ID");
				 messageBox1.open();
				 
			 }
			 
		 } 
		 catch (SQLException e1) 
		 {
			 e1.printStackTrace();
			 Logger.write(e1);
			 
		 }
		 
		 //DEBUG
		 //Logger.write("DEBUG - "+"Beginning of Confirmation Dialog");
		 new Label(DialogArea, SWT.NULL).setText("Controller ID:");
		 ConfirmControllerID =  new Text(DialogArea, SWT.READ_ONLY);
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 if(ContollerID!=null)
		 {
			 ConfirmControllerID.setText(ContollerID);
			 
		 }
		 /*else 
		 {
			 ConfirmControllerID.setText("");
			 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
			 messageBox1.setText("ERROR");
			 messageBox1.setMessage("Unable to get Controller ID for selected Machine, Please select another machine");
			 messageBox1.open();
			 
		 }*/
		 
		 gridData.horizontalSpan = 2;
		 ConfirmControllerID.setLayoutData(gridData);		 
		 /*Text 7*/
		 new Label(DialogArea, SWT.NULL).setText("Setup Number:");
		 ConfirmSetupNumber =  new Text(DialogArea, SWT.READ_ONLY);
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 String ConfirmSetupNumber1 = CAMItemCreationDialog.setup.getText();
		 //DEBUG
		 Logger.write("DEBUG - "+"ConfirmDialog:# SiteSelected="+SiteSelected+"# MachineNo="+MachineNo+"# ConfirmSetupNumber1="+ConfirmSetupNumber1);
			
		 ConfirmSetupNumber.setText(ConfirmSetupNumber1);
		 gridData.horizontalSpan = 2;	  
		 ConfirmSetupNumber.setLayoutData(gridData);
		 /*Text 8*/
		 new Label(DialogArea, SWT.NULL).setText("CNC Item Title:");
		 ConfirmMfgItemTitle =  new Text(DialogArea, SWT.READ_ONLY);
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 String ConfirmMfgItemTitle1 = CAMItemCreationDialog.Mfgtitle.getText();
		 
		 ConfirmMfgItemTitle.setText(ConfirmMfgItemTitle1);
		 gridData.horizontalSpan = 2;	  
		 ConfirmMfgItemTitle.setLayoutData(gridData);
		 
		 return DialogArea;
		 
	 }
	 
	 @Override
	 protected void createButtonsForButtonBar(final Composite parent) 
	 {
		 Label separator1 = new Label((Composite) dialogArea, SWT.HORIZONTAL | SWT.SEPARATOR);
		 separator1.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));
		 GridData gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 gridData.horizontalSpan = 6;
 		 separator1.setLayoutData(gridData);
 		 /*Ok button*/
 		 buttonOk = new Button((Composite) dialogArea, SWT.PUSH);
 		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
 		 buttonOk.setLayoutData(gridData);
 		 buttonOk.setText("OK");
 		 buttonOk.addListener(SWT.Selection, new Listener() 
 		 {
 			 public void handleEvent(Event event) 
 			 {
 				 if(event.widget==buttonOk)
 				 {
 					 if(ConfirmSite.getText().isEmpty())
 					 {
 						 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
 						 messageBox1.setText("Error");
 						 messageBox1.setMessage("Unable to get Site from User Selection");
 						 messageBox1.open();
 						 
 					 }
 					 else if(ConfirmMachineID.getText().isEmpty())
 					 {
 						 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
 						 messageBox1.setText("Error");
 						 messageBox1.setMessage("Unable to get Machine ID for Selected Machine");
 						 messageBox1.open();
 						 
 					 } 					 
 					 /*else if(ConfirmControllerID.getText().isEmpty())
 					 {
 						 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
 						 messageBox1.setText("Error");
 						 messageBox1.setMessage("Unable to get Controller ID for Selected Machine");
 						 messageBox1.open();
 						 
 					 }*/
 					 else
 					 {
 						 CAMItemCreationOperation camSOA = new CAMItemCreationOperation();
 						 try 
 						 {
 							 int createItemStatus = camSOA.CAMcreateItem();
 							 //-1073741515
 							 if(createItemStatus==0)
 							 {
 								 F1 = true;
 								 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
 								 messageBox1.setText("Successfull");
 								 messageBox1.setMessage("NC Item and UGPART are Successfully Created");//Modified - Pradeep-20July2017
 								 messageBox1.open();
 								 if(SWT.OK>0)
 								 {
 									 //DEBUG
 									 Logger.write("DEBUG - "+"NC Item and UGPART are Successfully Created");									 
 									 
 								 }
 								 
 								 Logger.write("INFO - "+"CAM Item and UGPART are Successfully Created"); //Modified - Pradeep-20July2017
 								 //DEBUG
 								 //Logger.write("DEBUG - "+"MFG Item and UGPART are Successfully Created");
 								 
 							 }
 							 else if(createItemStatus==20)
 							 {
 								 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
 								 messageBox1.setText("Error");
		     				     messageBox1.setMessage("ERROR STATUS-20: Invalid/Wrong arguments passed to UFUNC, MFG ITEM got created But UGPART not created");
		     				     messageBox1.open();	
		     				     if(SWT.OK>0)
		     				     {
		     				    	 //DEBUG
		     				    	 Logger.write("DEBUG - "+"STATUS-20: Invalid/Wrong arguments passed to UFUNC, MFG ITEM got created But UGPART not created");
		     				    	 
		     				     }
		     				     
		     				     Logger.write("ERROR - "+"Invalid/Wrong arguments passed to UFUNC, MFG ITEM got created But UGPART not created");
		     				     
 							 }
 							 else if(createItemStatus==21)
 							 {
 								 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
 								 messageBox1.setText("Error");
 								 messageBox1.setMessage("ERROR STATUS-21: User entered Wrong credentials for three times");
 								 messageBox1.open();
 								 if(SWT.OK>0)
 								 {
 									 //getShell().dispose();
 									 //getParentShell().dispose();
 									 
 								 }
 								 
 								 Logger.write("ERROR - "+"User entered Wrong credentials for three times");
 								 
 							 }
 							 else if(createItemStatus==-1073741510)
 							 {
 								 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
 								 messageBox1.setText("Error");
 								 messageBox1.setMessage("ERROR STATUS-(-1073741510): User Intrupted the Execution");
 								 messageBox1.open();
 								 if(SWT.OK>0)
 								 {
 									 //getShell().dispose();
 									 //getParentShell().dispose();
 									 
 								 }
 								 
 								 Logger.write("ERROR - "+"User Intrupted the Execution");
 								 
 							 }
 							 else if(createItemStatus==3)
 							 {
 								 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
 								 messageBox1.setText("Error");
 								 messageBox1.setMessage("ERROR STATUS-3: MFG ITEM got created But UGPART not created, User Authentication Aborted");
 								 messageBox1.open();
 								 if(SWT.OK>0)
 								 {
 									 //getShell().dispose();
 									 //getParentShell().dispose();
 									 
 								 }
 								 Logger.write("ERROR - "+"MFG ITEM got created But UGPART not created, User Authentication Aborted");
 								 
 							 }
 							 else if(createItemStatus==-1)
 							 {
									MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
		     						messageBox1.setText("Error");
		     				        messageBox1.setMessage("ERROR STATUS-(-1): TC Password Decryption Failed, MFG ITEM got created But UGPART not created");
		     				        messageBox1.open();	
		     				       if(SWT.OK>0)
			  				        {
			  				        	//getShell().dispose();
			  				        	//getParentShell().dispose();
			  				        }
		     				        Logger.write("ERROR - "+"Teamcenter Password Decryption Failed, MFG ITEM got created But UGPART not created");
		     				        
 							 }
 							 else if(createItemStatus==25)
 							 {
									MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
		     						messageBox1.setText("Error");
		     				        messageBox1.setMessage("ERROR STATUS-25: MFG ITEM got created But UGPART not created with error \"Cannot delete old reference set\"");
		     				        messageBox1.open();	
		     				       if(SWT.OK>0)
			  				        {
			  				        	//getShell().dispose();
			  				        	//getParentShell().dispose();
			  				        }
		     				        Logger.write("ERROR - "+"MFG ITEM got created But UGPART not created with error \"Cannot delete old reference set\"");
		     				        
 							 }
 							 else if(createItemStatus==1)
 							 {								 
									MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
		     						messageBox1.setText("Error");
		     				        messageBox1.setMessage("ERROR STATUS-1: User interrupted the Execution. MFG ITEM got created But UGPART not created.");
		     				        messageBox1.open();	
		     				       if(SWT.OK>0)
			  				        {
			  				        	//getShell().dispose();
			  				        	//getParentShell().dispose();
			  				        }
		     				        Logger.write("ERROR - "+"User interrupted the Execution. MFG ITEM got created But UGPART not created.");
		     				        
 							 }
 							 else if(createItemStatus==-2147483645)
 							 {
									MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
		     						messageBox1.setText("Error");
		     				        messageBox1.setMessage("ERROR STATUS-(-2147483645): MFG ITEM got created But UGPART not created with error \"Wrong Password entered by user for Authentication\"");
		     				        messageBox1.open();
		     				       if(SWT.OK>0)
			  				        {
			  				        	//getShell().dispose();
			  				        	//getParentShell().dispose();
			  				        }
		     				        Logger.write("ERROR - "+"MFG ITEM got created But UGPART not created with error \"Wrong Password entered by user for Authentication\"");
		     				        
 							 }
 							 else if(createItemStatus==24)
 							 {
									MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
		     						messageBox1.setText("Error");
		     				        messageBox1.setMessage("ERROR STATUS-24: MFG ITEM got created But UGPART not created with error \"Exited with error status 24\"");
		     				        messageBox1.open();	
		     				       if(SWT.OK>0)
			  				        {
			  				        	//getShell().dispose();
			  				        	//getParentShell().dispose();
			  				        }
		     				        Logger.write("ERROR - "+"MFG ITEM got created But UGPART not created with error \"Exited with error status 24\"");
		     				        
 							 }
 							 else if(createItemStatus==(-1073741515))
 							 {
									MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
		     						messageBox1.setText("Error");
		     				        messageBox1.setMessage("ERROR STATUS-(-1073741515): Required dll's are missing from your computer. Please try to re-install");
		     				        messageBox1.open();	
		     				       if(SWT.OK>0)
			  				        {			  				        	
			  				        	//getShell().dispose();
			  				        	//getParentShell().dispose();	  				        	
			  				        }
		     				        Logger.write("ERROR - "+"Required dll's are missing from your computer. Please try to re-install");
		     				        
 							 }
 							 else if(createItemStatus==(-1073741819))
 							 {
									MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_WORKING|SWT.OK);
		     						messageBox1.setText("Error");
		     				        messageBox1.setMessage("ERROR STATUS-(-1073741819): Encountered Debug Exception from UserFunction");
		     				        messageBox1.open();	
		     				       if(SWT.OK>0)
			  				        {		  				        	
			  				        	//getShell().dispose();
			  				        	//getParentShell().dispose();			  				        	
			  				        }
		     				        Logger.write("ERROR - "+"Encountered Debug Exception from UserFunction");
		     				        
 							 }
 							 else
 							 {
									MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
		     						messageBox1.setText("Error");
		     				        messageBox1.setMessage("ERROR STATUS-(unknown): Unexpected error from NX User Function..");
		     				        messageBox1.open();	
		     				       if(SWT.OK>0)
			  				        {
		     				    	    //DEBUG
										Logger.write("DEBUG - "+"After STATUS-(unknown): Unexpected error from NX User Function..");
			  				        	
			  				        }
		     				        Logger.write("ERROR - "+"Unexpected error from NX User Function..");
		     				        
 							 }
 							 
 						 }
 						 catch (ServiceException | TCException e) 
 						 {
 							 Logger.write("DEBUG - "+"Inside UFUNC Errors catch");
 							 e.printStackTrace();
 							 Logger.write(e); 							 
 						 }
 						 							 
 						 //DEBUG
 						 //Logger.write("DEBUG - "+"After DUMP");
 						 
 						 if(camSOA.CreateResponse!=0)
 						 { 
 							 iTem_Id = camSOA.ItemIDFinal;
 							
 							 try 
 							 {   
 								//Included to Delete NC Item in case any failure to UGPART Created //Pradeep-20July2017
// 								 TCComponentItem camNCItem = ( TCComponentItem ) Common.itemQuery( camSOA.ItemIDFinal );
// 								 camNCItem.delete();
 								//Commented. Its not needed  //Pradeep-20July2017
 								 TCComponentItem Confirmcomp = (TCComponentItem)  Common.itemQuery(iTem_Id); 								 
 								 TCComponentItemRevision compRevision = (TCComponentItemRevision)Confirmcomp.getLatestItemRevision();
 								 String last_mod_date = Confirmcomp.getProperty("last_mod_date");
 								 String[] ddd = last_mod_date.split(" ");
 								 
 								 String creation_date = Confirmcomp.getProperty("creation_date");
 								 String[] d = creation_date.split(" ");
 								 
 								 String owning_userT = Confirmcomp.getProperty("owning_user");
 								 
 								 String[] words=owning_userT.split("\\(");
 								 String[] words1=words[1].split("\\)");
     								 
 								 String owning_user = words1[0];
 								 //String current_id = Confirmcomp.getProperty("current_id");
 								 String lAst_Updated_ByT = Confirmcomp.getProperty("last_mod_user");
     								 
   								 String[] wordsL=lAst_Updated_ByT.split("\\(");
   								 String[] wordsL1=wordsL[1].split("\\)");
   								 String lAst_Updated_By = wordsL1[0];
     								
   								 int iTem_Seq = 12;
   								 String iTem_Title = Confirmcomp.getProperty("current_name");
   								 String Site = ConfirmSite1;
   								 if(Site!=null)
   								 {
   									 if(Site.equalsIgnoreCase("GROVECITY"))
   									 {
   										 sIte_Seq = Gets_Site_Sequence("GROVECITY");
   										 
   									 }
   									 else if(Site.equalsIgnoreCase("ERIE")) 
   									 {
   										 sIte_Seq = Gets_Site_Sequence("ERIE");
   										 
   									 }
   									 
   								 }
   								 else
   								 {
   									 MessageBox messageBox11 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
   									 messageBox11.setText("ERROR");
   									 messageBox11.setMessage("Unable to get selected site");

     								 messageBox11.open();
     								 Logger.write("ERROR - "+"Unable to get selected site");
     								 
   								 }
   								 
   								 try 
   								 {
   									 Gets_Cam_Items_Update(iTem_Seq , ddd[0], lAst_Updated_By , d[0], owning_user, iTem_Id, iTem_Title , sIte_Seq);
   									 
   								 }
   								 catch (SQLException e) 
   								 {
   									 e.printStackTrace();
   									 Logger.write(e);
   									 
   								 }
   								 
   								 String item_revision_id = compRevision.getProperty("item_revision_id");
   								 String last_mod_daterev = compRevision.getProperty("last_mod_date");
   								 String[] last = last_mod_daterev.split(" ");
   								 
   								 String creation_daterev = compRevision.getProperty("creation_date");
   								 String[] creat = creation_daterev.split(" ");
   								 
   								 String owning_userrevT = compRevision.getProperty("owning_user");
   								 
   								 String[] wordsRev=owning_userrevT.split("\\(");
   								 String[] wordsR1=wordsRev[1].split("\\)");
   								 
   								 String owning_userrev = wordsR1[0];
   								 
   								 //String current_idrev = compRevision.getProperty("current_id");
   								 String lAst_Updated_ByrevT = compRevision.getProperty("last_mod_user");
   								 
   								 String[] wordsTRev=lAst_Updated_ByrevT.split("\\(");
   								 String[] wordsTR1=wordsTRev[1].split("\\)");
   								 String lAst_Updated_Byrev = wordsTR1[0];
   								 
   								 String engg_Co_Num = "TESTCAM";
   								 String comments="MyTestItemRevision01";
   								 //String com = CamUtilsDialogDataset.comments.getText();
   								 
   								 Gets_Cam_Itemrevision_Update(last[0], lAst_Updated_Byrev, creat[0], owning_userrev, item_revision_id, engg_Co_Num , comments, iTem_Id);
   								 
   								 if(F1==true)
   								 {
   									 Gets_Cam_Dataset_Append(last[0], owning_userrev, last[0], owning_userrev, camSOA.UGPART, "TestCAM", "testdescription", camSOA.ItemIDFinal, "000" );
   									 
   								 }
   								 else
   								 {
   									 Logger.write("ERROR - "+"Ufunc failed, not Inserted  UGPART");
   									 
   								 }
   								 
 							 } 
 							 catch (TCException e1) 
 							 {
 								 e1.printStackTrace();
 								 Logger.write(e1);
 								 
 							 } 
 							 
 						 }
 						 else if(camSOA.DatasetNotFound==-1)
 						 {
 							 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
 							 messageBox1.setText("Error");
 							 messageBox1.setMessage("UGMASTER Dataset missing under Item revision");
 							 messageBox1.open();
 							 Logger.write("ERROR - "+"UGMASTER Dataset missing under Item revision");
 							 
 						 }
 						 else
 						 {
 							 MessageBox messageBox1 = new MessageBox(getShell(),SWT.ERROR|SWT.OK);
 							 messageBox1.setText("Error");
 							 messageBox1.setMessage("MFG Item Created but UGPART creation failed");
 							 messageBox1.open();
 							 Logger.write("ERROR - "+"MFG Item Created but UGPART creation failed");
 							 
 						 }
 						 
 						 ((Composite) dialogArea).getShell().dispose();
 						 
 					 }
 					 
 				 }
 				 
 				 tmpparentshell.dispose();
 				 
 			 }
 			 
 		 });
 		 
 		 /*Edit*/
 		 buttonEdit = new Button((Composite) dialogArea, SWT.PUSH);
 		 buttonEdit.setLayoutData(gridData);
 		 buttonEdit.setText("Edit");
 		 buttonEdit.addListener(SWT.Selection, new Listener() 
 		 {
 			 public void handleEvent(Event event) 
 			 {
 				 if(event.widget==buttonEdit)
 				 {
 					 ((Composite) dialogArea).getShell().dispose();
 					 
 				 }
 				 
 			 }
 			 
 		 });
 		 
 		 /*Cancel button*/
 		 buttonCancel = new Button((Composite) dialogArea, SWT.PUSH);
 		 buttonCancel.setLayoutData(gridData);
 		 buttonCancel.setText("Cancel");
 		 
 		 Label separator11 = new Label((Composite) dialogArea, SWT.HORIZONTAL | SWT.SEPARATOR);
 		 separator11.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));
 		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
 		 gridData.horizontalSpan = 6;
 		 separator11.setLayoutData(gridData);

		 buttonCancel.addListener(SWT.Selection, new Listener() 
		 {
			 public void handleEvent(Event event) 
			 {
				 if(event.widget==buttonCancel)
				 {
					 ((Composite) dialogArea).getShell().dispose();	
					 
				 }
				 
				 tmpparentshell.dispose();
				 
			 }
			 
		 });
		 
		 // new Label((Composite) dialogArea, SWT.NULL).setText("V1.3");
		 //	gridData = new GridData(GridData.HORIZONTAL_ALIGN_END);
		 //gridData.horizontalSpan = 1;
		 
	 }
	 
	 protected String get_ControlIDs(String siteSelected, String machineNo) throws SQLException 
	 {
		 String UsersiteSelected = siteSelected;
		 String UsermachineNo= machineNo;
		 String result = null;

		 /* Check for JDBC Driver */
		 Common.checkDriver();
		 
		 /* get connected to DB */
		 Connection conn = Common.connectDB();
		 
		 Statement stmt=conn.createStatement();
		 ResultSet rs=stmt.executeQuery("SELECT CONTROLLER_NAME FROM GETS_MFG_CONTROLLERS WHERE CONTROLLER_SEQ IN ( SELECT DISTINCT CONTROLLER_SEQ FROM GETS_MFG_POST_PROCESSORS WHERE ACTIVE_FLAG='Y' AND MACHINE_SEQ IN (SELECT MACHINE_SEQ FROM GETS_MFG_MACHINES WHERE MACHINE_NO= '"+UsermachineNo+"' AND ACTIVE_FLAG = 'Y' AND SITE_SEQ IN (SELECT SITE_SEQ FROM GETS_MFG_SITES WHERE SITE_NAME='"+UsersiteSelected+"')))");
		 
		 try
		 {
			 while (rs.next())
			 {
				 result = rs.getString("CONTROLLER_NAME");
				 
				 if (result != null )
				 {
					 result = result.trim();
					 
				 }
				 
				 return result;
				 //get_ControlIDs.add(result);
				 
			 }
			 
		 }
		 catch (SQLException e)
		 {
			 e.printStackTrace();
			 Logger.write(e);
			 
		 }
		 finally
		 {
			 if (conn != null)
			 {
				 try
				 {
					 conn.close();
					 
				 }
				 catch (SQLException e)
				 {
					 Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
					 e.printStackTrace();
					 Logger.write(e);
					 
				 }
				 
			 }
			 
		 }
		 
		 return result;
		 
	 }
	 
	 /*
	  * Append Data set with given dataset name in DB table.
	  */
	 protected int Gets_Cam_Dataset_Append( String lastupdated_Date, String lastupdated_By, String creation_Date, String created_By, String dataset_Name, String e_Conn, String desc, String item_Id, String item_Rev_Id )
	 {
		 int datasetseq_Nextvalue=-1;
		 int itemRevSeq1 = -1;
		 /* Check for JDBC Driver */
		 Common.checkDriver();
		 PreparedStatement preparedStatement = null;
		 
		 String appendDatasetTableSql = "INSERT INTO GETS_CAM_DATASETS"
				 								+ "(DATASET_SEQ,LAST_UPDATED_DATE,LAST_UPDATED_BY,CREATION_DATE,CREATED_BY,DATASET_NAME,ENGG_CO_NUMBER,COMMENTS,ITEM_REV_SEQ)"
												+"VALUES(?,?,?,?,?,?,?,?,?)";
		 
		 /* get connected to DB */
		 Connection conn = Common.connectDB();
		 
		 try
		 {
			 /* get the MAX Item Sequence and increment it by one to store the item */			 
			 Statement sqlStatement = conn.createStatement();
			 
			 ResultSet sqlResult = sqlStatement.executeQuery( "SELECT MAX(ITEM_REV_SEQ) from GETS_CAM_ITEM_REVISIONS WHERE ITEM_REV_ID=item_Rev_Id" );
			 
			 while( sqlResult.next() )
			 {
				 itemRevSeq1 = sqlResult.getInt(1);
				 
			 }
			 
			 /* GETS_CAM_DATASETS_SEQ.NEXTVAL to insert data set */
			 sqlResult = sqlStatement.executeQuery( "SELECT GETS_CAM_DATASETS_SEQ.NEXTVAL FROM GETS_CAM_DATASETS" );
			 
			 while( sqlResult.next() )
			 {
				 datasetseq_Nextvalue = sqlResult.getInt(1);
				 break;
				 
			 }
			 
			 preparedStatement = conn.prepareCall( appendDatasetTableSql );
			 preparedStatement.setInt( 1, datasetseq_Nextvalue );
			 preparedStatement.setString( 2, lastupdated_Date );
			 preparedStatement.setString( 3,lastupdated_By );
			 preparedStatement.setString( 4,creation_Date );
			 preparedStatement.setString( 5,created_By );
			 preparedStatement.setString( 6,dataset_Name );
			 preparedStatement.setString( 7,e_Conn );
			 preparedStatement.setString( 8,desc );
			 preparedStatement.setInt( 9, itemRevSeq1 );
			 
			 int retValue = preparedStatement.executeUpdate();
			 
			 System.out.println("Value of retValue: " + retValue);
			 
			 /* CLose connection */
			 if( preparedStatement != null )
			 {
				 preparedStatement.close();
				 
			 }
			 
			 if( conn != null )
			 {
				 conn.close();
				 
			 }
			 
		 }
		 catch( SQLException e )
		 {
			 Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
			 e.printStackTrace();
			 Logger.write(e);
			 return e.getErrorCode();
			 
		 }
		 return 0;
		 
	 }
	 
	 protected int Gets_Site_Sequence( String site_Name )
	 {
		 int site_Seq = -1;
		 
		 /* Check for JDBC Driver */
		 Common.checkDriver();
		 
		 /* get connected to DB */
		 Connection conn = Common.connectDB();
		 
		 try
		 {
			 PreparedStatement preparedStatement = null;
			 
			 String getItemSeqSqlQuery= "SELECT distinct(SITE_SEQ) FROM GETS_MFG_SITES WHERE SITE_NAME=?";
			 //Statement sqlStatement = conn.createStatement();
			 preparedStatement = conn.prepareCall( getItemSeqSqlQuery );
			 preparedStatement.setString( 1, site_Name );
			 ResultSet sqlResult = preparedStatement.executeQuery();
			 
			 while( sqlResult.next() )
			 {
				 site_Seq = sqlResult.getInt( sqlResult.findColumn("SITE_SEQ"));
				 
			 }
			 
			 return site_Seq;
			 
		 }
		 catch( SQLException e )
		 {
			 Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
			 e.printStackTrace();
			 Logger.write(e);
			 return e.getErrorCode();
			 
		 }
		 
	 }
	 
	 /*
	 * ITEM_REV_SEQ will be calculated automatically using max and incremented by 1.
	 * 
	 */
	 protected int Gets_Cam_Itemrevision_Update( String last_Updated_date, String last_Updated_By, String creation_Date, String created_By, String item_Revision_Id, String engg_Co_Num, String comments, String item_ID )
	 {
		 int item_Seq=-1;
		 int item_Rev_Seq=-1;
		 
		 /* Check for JDBC Driver */
		 Common.checkDriver();
		 PreparedStatement preparedStatement = null;
		 
		 String updateItemRevisionTableSql = "INSERT INTO GETS_CAM_ITEM_REVISIONS"
											+ "(ITEM_REV_SEQ,LAST_UPDATED_DATE,LAST_UPDATED_BY,CREATION_DATE,CREATED_BY,ITEM_REV_ID,ENGG_CO_NUMBER,COMMENTS,ITEM_SEQ)"
											+"VALUES(?,?,?,?,?,?,?,?,?)";
		 String ItemSeqTableSql = "SELECT MAX(ITEM_SEQ) from GETS_CAM_ITEMS WHERE ITEM_ID=?";
		 
		 /* get connected to DB */
		 Connection conn = Common.connectDB();
		 
		 try
		 {
			 /* get the MAX Item Sequence and increment it by one to store the item */
			 preparedStatement = conn.prepareCall( ItemSeqTableSql );
			 preparedStatement.setString(1, item_ID );
			 ResultSet sqlResult = preparedStatement.executeQuery();
			 
			 while( sqlResult.next() )
			 {
				 item_Seq = sqlResult.getInt(1);
				 
			 }
			 
			 /*Get next available slot to insert item revision  */
			 Statement sqlStatement = conn.createStatement();
			 sqlResult = sqlStatement.executeQuery( "SELECT GETS_CAM_ITEM_REVISIONS_SEQ.NEXTVAL FROM GETS_CAM_ITEM_REVISIONS" );
			 
			 while( sqlResult.next() )
			 {
				 item_Rev_Seq = sqlResult.getInt(1);
				 break;
				 
			 }
			 
			 preparedStatement = conn.prepareCall( updateItemRevisionTableSql );
			 preparedStatement.setInt( 1, item_Rev_Seq );
			 preparedStatement.setString( 2, last_Updated_date );
			 preparedStatement.setString( 3,last_Updated_By );
			 preparedStatement.setString( 4,creation_Date );
			 preparedStatement.setString( 5,created_By );
			 preparedStatement.setString( 6,item_Revision_Id );
			 preparedStatement.setString( 7,engg_Co_Num );
			 preparedStatement.setString( 8,comments );
			 preparedStatement.setInt( 9, item_Seq );

			 int retValue = preparedStatement.executeUpdate();
			 
			 System.out.println("Value of retValue: " + retValue);
			
			 /* CLose connection */
			 
			 if( preparedStatement != null )
			 {
				 preparedStatement.close();
				 
			 }
			 
			 if( conn != null )
			 {
				 conn.close();
				 
			 }
			 
		 }
		 catch( SQLException e)
		 {
			 Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
			 e.printStackTrace();
			 Logger.write(e);
			 return e.getErrorCode();
			 
		 }
		 return 0;
		 
	 }
	 
	 /* Insert Items
	 * Table name :: GETS_CAM_ITEMS
	 * 
	 * */
	 protected int Gets_Cam_Items_Update(int iTem_Seq, String lAst_Updated_date, String lAst_Updated_By, String cReation_Date, String cReated_By, String iTem_Id, String iTem_Title, int sIte_Seq ) throws SQLException
	 {
		 /* Check for JDBC Driver */
		 Common.checkDriver();
		 
		 /*Prepared statement */
		 PreparedStatement preparedStatement = null;
		 
		 String updateTableSQL = "INSERT INTO GETS_CAM_ITEMS"
								+ "(ITEM_SEQ,LAST_UPDATED_DATE,LAST_UPDATED_BY,CREATION_DATE,CREATED_BY,ITEM_ID,ITEM_TITLE,SITE_SEQ)"
								+ "VALUES(?,?,?,?,?,?,?,?)";
		 
		 /* get connected to DB */
		 Connection conn = Common.connectDB();
		 try
		 {
			 /* get the MAX Item Sequence and increment it by one to store the item */
			 Statement sqlStatement = conn.createStatement();
			 
			 ResultSet sqlResult = sqlStatement.executeQuery( "SELECT GETS_CAM_ITEMS_SEQ.NEXTVAL FROM GETS_CAM_ITEMS" );
			 while( sqlResult.next() )
			 {
				 iTem_Seq = sqlResult.getInt(1);
				 break;
				 
			 }
			 
			 preparedStatement = conn.prepareCall( updateTableSQL );
			 preparedStatement.setInt( 1, iTem_Seq );
			 preparedStatement.setString( 2, lAst_Updated_date );
			 preparedStatement.setString( 3, lAst_Updated_By );
			 preparedStatement.setString( 4, cReation_Date );
			 preparedStatement.setString( 5, cReated_By );
			 preparedStatement.setString( 6, iTem_Id );
			 preparedStatement.setString( 7, iTem_Title );
			 preparedStatement.setInt( 8, sIte_Seq );
			 
			 int retValue = preparedStatement.executeUpdate();
			 System.out.println("Value of retValue: " + retValue);
			 
		 }
		 catch( SQLException e)
		 {
			 Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
			 e.printStackTrace();
			 Logger.write(e);
			 return e.getErrorCode();
			 
		 }
		 
		 /* CLose connection */
		 
		 if( preparedStatement != null )
		 {
			 preparedStatement.close();
			 
		 }
		 
		 if( conn != null )
		 {
			 conn.close();
			 
		 }		 
		 return 0;
		 
	 }
}


