package com.ge.transportation.plm.srv.operations;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.MultiStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.core.runtime.jobs.Job;
import org.eclipse.jface.dialogs.ErrorDialog;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Table;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.progress.IProgressService;

import com.ge.transportation.plm.srv.beans.ServicesAttributesFormBean;
import com.ge.transportation.plm.srv.constants.Constants;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCComponentItemType;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.pse.AbstractPSEApplication;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.services.loose.core.DataManagementService;
import com.teamcenter.services.loose.core._2006_03.DataManagement.Relationship;
import com.teamcenter.services.loose.core._2007_01.DataManagement.CreateOrUpdateFormsResponse;
import com.teamcenter.services.loose.core._2007_01.DataManagement.FormInfo;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.Property;
import com.teamcenter.soa.client.model.ServiceData;

/**
* <h1>ServiceAttributesOperation</h1>
* This class implements creation of 
* Services Form Type for Services functionality 
* using the Custom UI
*
* @author  Sudheer Arikere
* @version 1.0
* @since   2017-09-07
*/
   public class ServiceAttributesOperation extends Job  {
	 
	  private int m_iIndex = 0;
	  private boolean m_isInitData = false;
	  private boolean m_isSaveData = false;
	  private Table m_SelectedItemsTable = null;
	  private InterfaceAIFComponent[] m_selectedComponents = null;
	  private String m_strStatusMessage = Constants.General.EMPTY_STRING_VALUE_C;
	  private DataManagementService m_DataManagementServiceObj = null;
	  private TCComponent seleted          				= null ;
	  
	  private Map<String, ServicesAttributesFormBean> m_hshMapFormValues = Collections.synchronizedMap(new LinkedHashMap<String, ServicesAttributesFormBean>());
	  
	  public ServiceAttributesOperation(String p_strStatusMessage,Table p_SelectedItemsTable, InterfaceAIFComponent[] p_selectedComponents) {
		  	
		super(p_strStatusMessage);
		setUser(true);
	    this.m_iIndex = 0;
	 //   this.m_hshMapFormValues.clear();
	    this.m_strStatusMessage = p_strStatusMessage;
	    this.m_SelectedItemsTable = p_SelectedItemsTable;
	    this.m_selectedComponents = p_selectedComponents;
	    this.m_isInitData = true;
	    this.m_DataManagementServiceObj = DataManagementService.getService(((TCSession)AIFUtility.getDefaultSession()).getSoaConnection());
	  }
	  
	  public ServiceAttributesOperation(String p_strStatusMessage,Table p_SelectedItemsTable, InterfaceAIFComponent[] p_selectedComponents, Map<String, ServicesAttributesFormBean> p_hshMapFormValues) {
		  	
		super(p_strStatusMessage); 
		setUser(true);
	    this.m_iIndex = 0;
	    this.m_hshMapFormValues.clear(); 
	    this.m_strStatusMessage = p_strStatusMessage;
	    this.m_SelectedItemsTable = p_SelectedItemsTable;
	    this.m_selectedComponents = p_selectedComponents;
	    this.m_hshMapFormValues = p_hshMapFormValues;
	    this.m_isSaveData = true;
	    this.m_DataManagementServiceObj = DataManagementService.getService(((TCSession)AIFUtility.getDefaultSession()).getSoaConnection());
	  }
	  
	  public void showErrorMessage(final String p_strReason, final String p_strErrorMessage, final String p_strErrorTraceHeading, final ArrayList<String> p_strErrorMessages) {
		  
		  Display.getDefault().syncExec(new Runnable() {
		        public void run() {
		        	
		        	List<Status> childStatuses = new ArrayList<>();
		            
		        	
		        	if(p_strErrorTraceHeading.equals("Exception")) {
		        		
		        		StackTraceElement[]  stackErrorMessage = Thread.currentThread().getStackTrace();
		        		for(StackTraceElement stackTraceMessage : stackErrorMessage) {
		        			
		        			childStatuses.add(new Status(IStatus.ERROR, "com.ge.transportation.plm.srv", stackTraceMessage.toString()));
		        		}
		        	} else {
		        		
		        		for(int inx = 0; inx < p_strErrorMessages.size(); inx++) {
			        		
			        		 childStatuses.add(new Status(IStatus.ERROR, "com.ge.transportation.plm.srv", p_strErrorMessages.get(inx)));
			        	}
		        	}
		        	
		        	MultiStatus MultiStatusObj = new MultiStatus("com.ge.transportation.plm.srv", IStatus.ERROR, childStatuses.toArray(new Status[] {}), p_strReason, new Exception(p_strErrorTraceHeading));
		        	ErrorDialog.openError(m_SelectedItemsTable.getShell(), "Error", p_strErrorMessage, MultiStatusObj);
		        }
		 });
	  }
	  
	  public IStatus run(IProgressMonitor p_IProgressMonitor) {
		 
		  Display.getDefault().asyncExec(new Runnable() {
		        public void run() {
		        	
		        	IProgressService iProgressService = PlatformUI.getWorkbench().getProgressService(); 
		  		    iProgressService.showInDialog(m_SelectedItemsTable.getShell(), ServiceAttributesOperation.this); 
		        }
		  });
		  
		  if(this.m_isInitData) {
			  
			  p_IProgressMonitor.beginTask(this.m_strStatusMessage, m_selectedComponents.length);
              getSrvAttributes(p_IProgressMonitor);
              p_IProgressMonitor.done();
		  } else if(this.m_isSaveData) {
			  
			  p_IProgressMonitor.beginTask(this.m_strStatusMessage, m_hshMapFormValues.size());
			  assignServiceForm(p_IProgressMonitor);
              p_IProgressMonitor.done();
		  } 
		  
		  return Status.OK_STATUS;
	  }

	  public void getSrvAttributes(IProgressMonitor p_IProgressMonitor) {
  		 
		  ArrayList<ModelObject> arrItemObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrMiscObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrBOMLineObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrRevisionObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrSelectedItemObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrAllSecondaryMfgForms = new ArrayList<ModelObject>();
		  LinkedHashMap<ModelObject, List<ModelObject>> lnhMfgOrgAttrForms = new LinkedHashMap<ModelObject, List<ModelObject>>();
		  
		  try {
			  
			  p_IProgressMonitor.worked(10);
		      p_IProgressMonitor.subTask("Loading...Service Items");
		      
		      for(int inx = 0; inx < m_selectedComponents.length; inx++) {
		    	  
		    	  if(m_selectedComponents[inx] instanceof TCComponentBOMLine) {
		    		  
		    		  arrBOMLineObjects.add((ModelObject)m_selectedComponents[inx]); 
		    		
		    	  } else {
		    		  
		    		  if(((Constants.BusinessObjects.strGET6SrvPartRevi).equals(m_selectedComponents[inx].getType()) || (Constants.BusinessObjects.strGET6MechPartRev).equals(m_selectedComponents[inx].getType()))) {

		    			  arrItemObjects.add((ModelObject)m_selectedComponents[inx]);
		    		  } else {

		    			  arrMiscObjects.add((ModelObject)m_selectedComponents[inx]);
		    		  }
		    	  }
		      }
		      
		      
		      if(arrBOMLineObjects.size() > 0) {
		    	  
				  ServiceData selectedItemObjectsSD = this.m_DataManagementServiceObj.getProperties(Arrays.copyOf(m_selectedComponents, m_selectedComponents.length, ModelObject[].class), new String[] { Constants.BusinessObjects.strBLItem });
				  for(int inx = 0; inx < selectedItemObjectsSD.sizeOfPlainObjects(); inx++) {
					  
					  Property PropertyObj = selectedItemObjectsSD.getPlainObject(inx).getPropertyObject(Constants.BusinessObjects.strBLItem);
					  if((Constants.BusinessObjects.strGET6MechPart).equals(PropertyObj.getModelObjectValue().getTypeObject().toString())||(Constants.BusinessObjects.strGET6SrvPart).equals(PropertyObj.getModelObjectValue().getTypeObject().toString())) {
						  
						  arrSelectedItemObjects.add(PropertyObj.getModelObjectValue());
					  } else {
	
						  arrMiscObjects.add(PropertyObj.getModelObjectValue());
					  }
				  }
		      } 
		      
		      if(arrItemObjects.size() > 0) {
		    	  
		    	  arrSelectedItemObjects.addAll(arrItemObjects);
		    	  
		      }

			  p_IProgressMonitor.worked(10);
		      p_IProgressMonitor.subTask("Loading...Service Attributes Forms");

		      ServiceData selectedSecondaryObjectsSD = this.m_DataManagementServiceObj.getProperties(arrSelectedItemObjects.toArray(new ModelObject[ arrSelectedItemObjects.size() ]), new String[] { Constants.BusinessObjects.Properties.strObjectString, Constants.BusinessObjects.Properties.strRevisionList, Constants.BusinessObjects.strGET6SrvRelation });
			  for(int inx = 0; inx < selectedSecondaryObjectsSD.sizeOfPlainObjects(); inx++) {
		
				  Property PropertyObj = selectedSecondaryObjectsSD.getPlainObject(inx).getPropertyObject(Constants.BusinessObjects.Properties.strRevisionList);
				  lnhMfgOrgAttrForms.put(selectedSecondaryObjectsSD.getPlainObject(inx), Arrays.asList(PropertyObj.getModelObjectArrayValue()));
				  arrAllSecondaryMfgForms.addAll(Arrays.asList(PropertyObj.getModelObjectArrayValue()));  
	 
				  Property PropertyRevObj = selectedSecondaryObjectsSD.getPlainObject(inx).getPropertyObject(Constants.BusinessObjects.Properties.strRevisionList);
				  arrRevisionObjects.addAll(Arrays.asList(PropertyRevObj.getModelObjectArrayValue()));
				
			  }
			 
			 p_IProgressMonitor.worked(10);
			 p_IProgressMonitor.subTask("Loading...Service Attributes Form Properties");
			 this.m_DataManagementServiceObj.getProperties(arrAllSecondaryMfgForms.toArray(new ModelObject[ arrAllSecondaryMfgForms.size() ]), new String[] {Constants.BusinessObjects.Properties.strEngineFamily, Constants.BusinessObjects.Properties.strget6Serviceable, Constants.BusinessObjects.Properties.strget6Serialize, Constants.BusinessObjects.Properties.strget6Repairable, Constants.BusinessObjects.Properties.strObjectName,Constants.BusinessObjects.Properties.strget6ServiceItemType });
			 p_IProgressMonitor.worked(10);
			 p_IProgressMonitor.subTask("Loading...Service Attributes Form Properties");

			 this.m_DataManagementServiceObj.getProperties(arrAllSecondaryMfgForms.toArray(new ModelObject[ arrRevisionObjects.size() ]), new String[] { Constants.BusinessObjects.Properties.strget6Serviceable });
			 for(ModelObject selectedItemObject : lnhMfgOrgAttrForms.keySet()) {
				 ServicesAttributesFormBean ManufacturingAttributesFormBeanObj = new ServicesAttributesFormBean();
				 ManufacturingAttributesFormBeanObj.setObjectString(selectedItemObject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString));

				 // get attribute - START
				 String objstr = selectedItemObject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString);
				 String [] newsttr = objstr.split("-");

				 TCComponentItemType  TCComponentItemTypeObj = (TCComponentItemType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6MechPart);
				 TCComponentItem it = TCComponentItemTypeObj.find(newsttr[0]);
				 TCComponentItemRevision rev = it.getLatestItemRevision();
				 TCComponent srvForm = rev.getRelatedComponent(Constants.BusinessObjects.Relations.strServFormRel);
				 if (srvForm!=null){
					 String frm1 = srvForm.getProperty(Constants.BusinessObjects.Properties.strEngineFamily);	//get6EngineFamily
					 String frm2 = srvForm.getProperty(Constants.BusinessObjects.Properties.strServiceable);		//get6Serviceable
					 String frm3 = srvForm.getProperty(Constants.BusinessObjects.Properties.strSerialized);		//get6Serialized
					 String frm4 = srvForm.getProperty(Constants.BusinessObjects.Properties.strPositionTracked);	//get6PositionTracked
					 String frm5 = srvForm.getProperty(Constants.BusinessObjects.Properties.strRepairable);		//get6Repairable
					 String frm6 = srvForm.getProperty(Constants.BusinessObjects.Properties.strServiceItemType);		//get6ServiceItemType
					 String frm7 = srvForm.getProperty(Constants.BusinessObjects.Properties.strTierType);		//get6ServiceItemType
					 String frm8 = srvForm.getProperty(Constants.BusinessObjects.Properties.strCompID);		//get6ServiceItemType

					 ManufacturingAttributesFormBeanObj.setEngineFamily(frm1);
					 ManufacturingAttributesFormBeanObj.setServiceable(frm2);
					 ManufacturingAttributesFormBeanObj.setSerialized(frm3);
					 ManufacturingAttributesFormBeanObj.setPositionTracked(frm4);
					 ManufacturingAttributesFormBeanObj.setRepairable(frm5);
					 ManufacturingAttributesFormBeanObj.setSrvItemType(frm6);
					 ManufacturingAttributesFormBeanObj.setTierType(frm7);
					 ManufacturingAttributesFormBeanObj.setCompID(frm8);

				 }
				 ManufacturingAttributesFormBeanObj.setTCComponentItem((TCComponentItem)selectedItemObject);
				 for(int inx = 0; inx < lnhMfgOrgAttrForms.get(selectedItemObject).size(); inx++) {

				 }

				 p_IProgressMonitor.worked(1);
				 p_IProgressMonitor.subTask("Loading..." + "(" + m_iIndex + "/" + m_selectedComponents.length + ")" + selectedItemObject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString));
				 m_hshMapFormValues.put(selectedItemObject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString), ManufacturingAttributesFormBeanObj);
				 m_iIndex++;
			 }
			 
			 
			 if(arrMiscObjects.size() > 0) {
				 
				 ArrayList<String> arrErrorMessage = new ArrayList<String>();
				 for(int inx = 0; inx < arrMiscObjects.size(); inx++) {
					 
					 arrErrorMessage.add(arrMiscObjects.get(inx) + " 	- 	" + arrMiscObjects.get(inx).getTypeObject().getUIFValue());
				 }
				 showErrorMessage(Constants.ServicesDialogUI.strMsg9, "Invalid Objects Found","Following objects are found invalid and will be ignored", arrErrorMessage);

			 }
			  
		  } catch (Exception tcObj) {
			  
			  ArrayList<String> arrErrorMessage = new ArrayList<String>();
			  arrErrorMessage.add(tcObj.getMessage());
			  showErrorMessage(tcObj.getMessage(), "Exception Thrown", "Exception", arrErrorMessage);
		  }
	  }
	  
	  public Map<String, ServicesAttributesFormBean> getSelectedComponentsData() {
		  
		  return m_hshMapFormValues;
	  }
 
	public void assignServiceForm(IProgressMonitor p_IProgressMonitor) {
			  
			  ArrayList<ServicesAttributesFormBean> arrNewMfgAttributesForms = new ArrayList<ServicesAttributesFormBean>();
			  
			  try {
				  
				  p_IProgressMonitor.worked(10);
				  p_IProgressMonitor.subTask("Collecting Input...");
				  for(ServicesAttributesFormBean ManufacturingAttributesFormBeanObj : this.m_hshMapFormValues.values()) {
					   m_iIndex++;
			        	if(ManufacturingAttributesFormBeanObj.getModified()) {
			        		TCComponentItem tci = ManufacturingAttributesFormBeanObj.getTCComponentItem();
			        		TCComponentItemRevision tcr = tci.getLatestItemRevision();
			        		TCComponent srvForm = tcr.getRelatedComponent(Constants.BusinessObjects.Relations.strServFormRel);
			        		
			        		if(null != srvForm) {
			        		
			        			String frm = srvForm.getProperty("object_name");

			        			formpropertiesUpdate(srvForm,ManufacturingAttributesFormBeanObj);
								// this.setServicesFormAttributes(ManufacturingAttributesFormBeanObj.getTCComponentForm(), ManufacturingAttributesFormBeanObj);
								  
							} else {
								arrNewMfgAttributesForms.add(ManufacturingAttributesFormBeanObj);
						   }
					   }
			  		}
				  
				  p_IProgressMonitor.worked(10);
				  p_IProgressMonitor.subTask("Creating New Data...");
				  this.createServiceAttributesForms(arrNewMfgAttributesForms);
				  
				  p_IProgressMonitor.worked(40);
				  p_IProgressMonitor.subTask("Refreshing Application...");
				  
				  if(AIFUtility.getCurrentApplication() instanceof AbstractPSEApplication) {
					  ((AbstractPSEApplication)AIFUtility.getCurrentApplication()).getBOMWindow().refresh();
				  }
				 
			  } catch(Exception eObj) {
				  
				  ArrayList<String> arrErrorMessage = new ArrayList<String>();
				  arrErrorMessage.add(eObj.getMessage());
				  showErrorMessage(eObj.getMessage(), "Exception Thrown", "Exception", arrErrorMessage);
			  }
		  }
	
		  // This Method is to update the Service Attribute Form
		public void formpropertiesUpdate(TCComponent srvFrm,ServicesAttributesFormBean p_ManufacturingAttributesFormBeanObj){
			
			String frmEngineFamily = p_ManufacturingAttributesFormBeanObj.getEngineFamily();
			if (!frmEngineFamily.isEmpty()){
				try {
					srvFrm.setProperty(Constants.BusinessObjects.Properties.strEngineFamily, frmEngineFamily.toString());
				} catch (TCException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
			}
			String frm3 = p_ManufacturingAttributesFormBeanObj.getPositionTracked();
			if (!frm3.isEmpty()){
				try {
					srvFrm.setProperty(Constants.BusinessObjects.Properties.strPositionTracked, frm3.toString());
				} catch (TCException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
			}
			String frm4 = p_ManufacturingAttributesFormBeanObj.getRepairable();
			if (!frm4.isEmpty()){
				try {
					srvFrm.setProperty(Constants.BusinessObjects.Properties.strRepairable, frm4.toString());
				} catch (TCException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
			}
			String frm5 = p_ManufacturingAttributesFormBeanObj.getSerialized();
			if (!frm5.isEmpty()){
				try {
					srvFrm.setProperty(Constants.BusinessObjects.Properties.strSerialized, frm5.toString());
				} catch (TCException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
			}
			String frm6 = p_ManufacturingAttributesFormBeanObj.getServiceable();
			if (!frm6.isEmpty()){
				try {
					srvFrm.setProperty(Constants.BusinessObjects.Properties.strServiceable, frm6.toString());
				} catch (TCException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
			}
			String frm7 = p_ManufacturingAttributesFormBeanObj.getSrvItemType();
			if (!frm7.isEmpty()){
				try {
					srvFrm.setProperty(Constants.BusinessObjects.Properties.strServiceItemType, frm7.toString());
				} catch (TCException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
			}
			String frmTierType = p_ManufacturingAttributesFormBeanObj.getTierType();
			if (!frmTierType.isEmpty()){
				System.out.println("frmTierType..."+frmTierType);
				String updatestr = stringManupulate(frmTierType);
				System.out.println("finally string..."+updatestr);
				try {
					if (frmTierType.toString().equals("NA")){
						srvFrm.setProperty(Constants.BusinessObjects.Properties.strTierType, frmTierType.toString());
					}else {
						srvFrm.setProperty(Constants.BusinessObjects.Properties.strTierType, updatestr);
					}
					
				} catch (TCException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
			}
			String frmCompID = p_ManufacturingAttributesFormBeanObj.getCompID();
			if (!frmCompID.isEmpty()){
				try {
					srvFrm.setProperty(Constants.BusinessObjects.Properties.strCompID, frmCompID.toString());
				} catch (TCException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
			}
			
		}
	
	  private Map<String, String[]> getServiceFormAttributesCreateMap(ServicesAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
	
		  Map<String, String[]> propertiesValues = new  HashMap<String, String[]>();
		  String[] strPropertyValues = new String[] {  p_ManufacturingAttributesFormBeanObj.getServiceable() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6Serviceable, strPropertyValues);
		  strPropertyValues = new String[] {  p_ManufacturingAttributesFormBeanObj.getSerialized() };
		 
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6Serialize, strPropertyValues);
		  strPropertyValues = new String[] {  p_ManufacturingAttributesFormBeanObj.getRepairable() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6Repairable, strPropertyValues);
		 
		  strPropertyValues = new String[] {  p_ManufacturingAttributesFormBeanObj.getSrvItemType() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6ServiceItemType, strPropertyValues);

		  // Multi values entry - Defect 1413
		  String [] strPropertyValuesEF = new String[] {  p_ManufacturingAttributesFormBeanObj.getEngineFamily() };
		  System.out.println("strPropertyValuesEF string..."+strPropertyValuesEF[0]);
		  if (!strPropertyValuesEF[0].isEmpty()){
			  String[] newstrPropertyValuesEF = strPropertyValuesEF[0].split(",");
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6EngineFamily, newstrPropertyValuesEF); 
		  }
		  strPropertyValues = new String[] {  p_ManufacturingAttributesFormBeanObj.getPositionTracked() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6PositionTracked, strPropertyValues);
		  //Defect 1413
		  String[] strPropertyValuestt = new String[] {  p_ManufacturingAttributesFormBeanObj.getTierType() };
		  if (!strPropertyValuestt[0].isEmpty()){
			  String updatestr = stringManupulate(strPropertyValuestt[0]);
			  System.out.println("finally string..."+updatestr);
			  String[] newstrPropertyValues = updatestr.split(",");
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6TierType,newstrPropertyValues );
		  }
		  // Multi Values - Defect 1413
		  String [] strPropertyValuesComp = new String[] {  p_ManufacturingAttributesFormBeanObj.getCompID() };
		  System.out.println("strPropertyValuesComp string..."+strPropertyValuesComp[0]);
		  if (!strPropertyValuesComp[0].isEmpty()){
			  String[] newstrPropertyValuesComp = strPropertyValuesComp[0].split(",");
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6CompID, newstrPropertyValuesComp);
		  }
		  
	
		  return propertiesValues;
	  }
	  

	  private Map<String, DataManagementService.VecStruct> getMFGFormAttributesUpdateMap(ServicesAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
		  
		  Map<String, DataManagementService.VecStruct> propertiesValues = new  HashMap<String, DataManagementService.VecStruct>();
		  DataManagementService.VecStruct vectorPropertyMakeBuy = new DataManagementService.VecStruct();
		  vectorPropertyMakeBuy.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getServiceable() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6Serviceable, vectorPropertyMakeBuy);
		  
		  DataManagementService.VecStruct vectorPropertyPlanningCode = new DataManagementService.VecStruct();
		  vectorPropertyPlanningCode.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getSerialized() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6Serialize, vectorPropertyPlanningCode);
		  
		  DataManagementService.VecStruct vectorstrPositionTracked = new DataManagementService.VecStruct();
		  vectorstrPositionTracked.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getPositionTracked() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6PositionTracked, vectorstrPositionTracked);
		  
		  DataManagementService.VecStruct vectorstrServiceItemType = new DataManagementService.VecStruct();
		  vectorstrServiceItemType.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getSrvItemType() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6ServiceItemType, vectorstrServiceItemType);
		  
		  DataManagementService.VecStruct vectorstrEngineFamily = new DataManagementService.VecStruct();
		  vectorstrEngineFamily.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getEngineFamily() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6EngineFamily, vectorstrEngineFamily);
		  
		  DataManagementService.VecStruct vectorstrTierType = new DataManagementService.VecStruct();
		  vectorstrTierType.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getTierType() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6TierType, vectorstrTierType);
		  
		  DataManagementService.VecStruct vectorstrCompID = new DataManagementService.VecStruct();
		  vectorstrCompID.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getCompID() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6CompID, vectorstrCompID);
		  
		  DataManagementService.VecStruct vectorstrRepairable = new DataManagementService.VecStruct();
		  vectorstrRepairable.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getRepairable() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6Repairable, vectorstrRepairable);
		  
		  return propertiesValues;

		  
	  }
	  
	  /**
		 * Defect 1413
		 * The stringManupulate Method.
		 * This method takes the string as input and the prepares the output string 
		 * for the TypeTier Attribute on the GET Service Form
		 * output string format : "Tier 0+,Tier 1+C"
		 */
		
		public String stringManupulate(String str){
			String T="Tier ";
			String s1 = null,s2 = null,s3 = null,s4 = null,s5 = null,s6= null,s7= null,s8= null,s9= null,s10= null,s11 = null,s12,s13,s14;
			String strnw = str.replace(" ", "");
			String [] ary=strnw.split(",");
			if (ary.length>1){
				for (int ii = 0;ii<ary.length;ii++){
				if (ary[ii].toString().equals("0"))
					 s1=T.concat(ary[ii]); 	
				else if  (ary[ii].toString().equals("0+"))
					s2=T.concat(ary[ii]); 	
				else if (ary[ii].toString().equals("1"))
					s3=T.concat(ary[ii]); 	
				else if (ary[ii].toString().equals("1+"))
					s4=T.concat(ary[ii]); 	
				else if (ary[ii].toString().equals("1+C"))
					s5=T.concat(ary[ii]); 
				else if (ary[ii].toString().equals("2"))
					s6=T.concat(ary[ii]); 
				else if (ary[ii].toString().equals("2+"))
					s7=T.concat(ary[ii]); 
				else if (ary[ii].toString().equals("3"))
					s8=T.concat(ary[ii]); 
				else if (ary[ii].toString().equals("4C"))
					s9=T.concat(ary[ii]); 
				else if (ary[ii].toString().equals("4T"))
					s10=T.concat(ary[ii]); 
				else if (ary[ii].toString().equals("NA"))
					s11="NA";
			  }
				s12=s1+","+s2+","+s3+","+s4+","+s5+","+s6+","+s7+","+s8+","+s9+","+s10+","+s11;
				s13=s12.replace("null,", "");
				s14=s13.replace("null", "");
				if (s14.endsWith(",")) {
					s14 = s14.substring(0, s14.length()-1);
					}
				return  s14;
		
		   }else
		   {
			   if (ary[0].toString().equals("NA")){
				   return ary[0];   
			   }else {
				   return T.concat(ary[0]);
			   }
		   }
			  
		}
	  private void setServicesFormAttributes(TCComponentForm p_TCComponentFormObj,  ServicesAttributesFormBean p_ManufacturingAttributesFormBeanObj) throws ServiceException {
		  		
		      String strErrorMessage = Constants.General.EMPTY_STRING_VALUE_C;
			  
			  ServiceData ServiceDataObj = this.m_DataManagementServiceObj.setProperties(new ModelObject[]{ p_TCComponentFormObj }, getMFGFormAttributesUpdateMap(p_ManufacturingAttributesFormBeanObj));
			  if(ServiceDataObj.sizeOfPartialErrors() > 0) {
				  
				  for(int inx = 0; inx < ServiceDataObj.sizeOfPartialErrors(); inx++) {
					  
					  strErrorMessage +=  ServiceDataObj.getPartialError(inx).getMessages()[0] + "\n";
				  }
				  
				  throw new ServiceException(strErrorMessage);
			  }
	  }
	  
	  public void createServiceAttributesForms(ArrayList<ServicesAttributesFormBean> p_arrNewMfgAttributesForms) throws ServiceException, TCException {
		
		String strErrorMessage = Constants.General.EMPTY_STRING_VALUE_C;
		final String strFormName = Constants.ManufacturingAttributesDialog.strManufacturingAttributesSuffix;
		final String strFormType = Constants.BusinessObjects.strGET6SrvForm;
		FormInfo[] FormInfoInput = new FormInfo[p_arrNewMfgAttributesForms.size()];
		
		for(int inx = 0; inx < p_arrNewMfgAttributesForms.size(); inx++) {
			FormInfoInput[inx] = new FormInfo();
			FormInfoInput[inx].clientId = p_arrNewMfgAttributesForms.get(inx).getObjectString();
			FormInfoInput[inx].description= strFormName;
			FormInfoInput[inx].name = strFormName;
			FormInfoInput[inx].formType = strFormType;
			FormInfoInput[inx].saveDB = true;
			FormInfoInput[inx].parentObject = null;
			FormInfoInput[inx].relationName = Constants.BusinessObjects.strGET6SrvRelation;
			FormInfoInput[inx].attributesMap = this.getServiceFormAttributesCreateMap(p_arrNewMfgAttributesForms.get(inx));
		}

		CreateOrUpdateFormsResponse CreateOrUpdateFormsResponseObj = this.m_DataManagementServiceObj.createOrUpdateForms(FormInfoInput);

		Relationship[] RelationshipObjs = new Relationship[CreateOrUpdateFormsResponseObj.outputs.length];
		for(int inx = 0; inx < CreateOrUpdateFormsResponseObj.outputs.length; inx++) {
			
			for(ServicesAttributesFormBean ManufacturingAttributesFormBeanObj : p_arrNewMfgAttributesForms) {
				
				
				if(ManufacturingAttributesFormBeanObj.getObjectString().equals(CreateOrUpdateFormsResponseObj.outputs[inx].clientId)) {
					TCComponentItem tci = ManufacturingAttributesFormBeanObj.getTCComponentItem();
					TCComponentItemRevision tcr = tci.getLatestItemRevision();

					RelationshipObjs[inx] = new Relationship();
					//RelationshipObjs[inx].primaryObject = ManufacturingAttributesFormBeanObj.getTCComponentItem();
					RelationshipObjs[inx].primaryObject = tcr;
					RelationshipObjs[inx].relationType =  Constants.BusinessObjects.strGET6SrvRelation;
					RelationshipObjs[inx].secondaryObject = CreateOrUpdateFormsResponseObj.outputs[inx].form;
					break;
				}
			}
		}
		
		this.m_DataManagementServiceObj.createRelations(RelationshipObjs);

		if(CreateOrUpdateFormsResponseObj.serviceData.sizeOfPartialErrors() > 0) {
			
			for(int jnx = 0; jnx < CreateOrUpdateFormsResponseObj.serviceData.sizeOfPartialErrors(); jnx++) {
				
				strErrorMessage += CreateOrUpdateFormsResponseObj.serviceData.getPartialError(jnx).getMessages()[0] + "\n";
			}
			throw new ServiceException(strErrorMessage);
		}
	}
}