package com.ge.transportation.plm.mfg.operations;

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
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Table;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.progress.IProgressService;

import com.ge.transportation.plm.mfg.beans.ManufacturingAttributesFormBean;
import com.ge.transportation.plm.mfg.constants.Constants;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCPreferenceService;
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

   public class ManufacturingAttributesOperation extends Job  {
	 
	  private int m_iIndex = 0;
	  private boolean m_isInitData = false;
	  private boolean m_isSaveData = false;
	  private Table m_SelectedItemsTable = null;
	  private InterfaceAIFComponent[] m_selectedComponents = null;
	  private String m_strStatusMessage = Constants.General.EMPTY_STRING_VALUE_C;
	  private String m_strCurrentProject = Constants.General.EMPTY_STRING_VALUE_C;
	  private DataManagementService m_DataManagementServiceObj = null;
	  
	  private Map<String, ManufacturingAttributesFormBean> m_hshMapFormValues = Collections.synchronizedMap(new LinkedHashMap<String, ManufacturingAttributesFormBean>());
	  
	  public ManufacturingAttributesOperation(String p_strStatusMessage, String p_strCurrentProject, Table p_SelectedItemsTable, InterfaceAIFComponent[] p_selectedComponents) {
		  	
		super(p_strStatusMessage);
		setUser(true);
	    this.m_iIndex = 0;
	    this.m_hshMapFormValues.clear();
	    this.m_strStatusMessage = p_strStatusMessage;
	    this.m_strCurrentProject = p_strCurrentProject;
	    this.m_SelectedItemsTable = p_SelectedItemsTable;
	    this.m_selectedComponents = p_selectedComponents;
	    this.m_isInitData = true;
	    this.m_DataManagementServiceObj = DataManagementService.getService(((TCSession)AIFUtility.getDefaultSession()).getSoaConnection());
	  }
	  
	  public ManufacturingAttributesOperation(String p_strStatusMessage, String p_strCurrentProject, Table p_SelectedItemsTable, InterfaceAIFComponent[] p_selectedComponents, Map<String, ManufacturingAttributesFormBean> p_hshMapFormValues) {
		  	
		super(p_strStatusMessage); 
		setUser(true);
	    this.m_iIndex = 0;
	    this.m_hshMapFormValues.clear(); 
	    this.m_strStatusMessage = p_strStatusMessage;
	    this.m_strCurrentProject = p_strCurrentProject;
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
		        			
		        			childStatuses.add(new Status(IStatus.ERROR, "com.ge.transportation.plm.mfg", stackTraceMessage.toString()));
		        		}
		        	} else {
		        		
		        		for(int inx = 0; inx < p_strErrorMessages.size(); inx++) {
			        		
			        		 childStatuses.add(new Status(IStatus.ERROR, "com.ge.transportation.plm.mfg", p_strErrorMessages.get(inx)));
			        	}
		        	}
		        	
		        	MultiStatus MultiStatusObj = new MultiStatus("com.ge.transportation.plm.mfg", IStatus.ERROR, childStatuses.toArray(new Status[] {}), p_strReason, new Exception(p_strErrorTraceHeading));
		        	ErrorDialog.openError(m_SelectedItemsTable.getShell(), "Error", p_strErrorMessage, MultiStatusObj);
		        }
		 });
	  }
	  
	  public IStatus run(IProgressMonitor p_IProgressMonitor) {
		 
		  Display.getDefault().asyncExec(new Runnable() {
		        public void run() {
		        	
		        	IProgressService iProgressService = PlatformUI.getWorkbench().getProgressService(); 
		  		    iProgressService.showInDialog(m_SelectedItemsTable.getShell(), ManufacturingAttributesOperation.this); 
		        }
		  });
		  
		  if(this.m_isInitData) {
			  
			  p_IProgressMonitor.beginTask(this.m_strStatusMessage, m_selectedComponents.length);
              getMfgAttributes(p_IProgressMonitor);
              p_IProgressMonitor.done();
		  } else if(this.m_isSaveData) {
			  
			  p_IProgressMonitor.beginTask(this.m_strStatusMessage, m_hshMapFormValues.size());
			  assignOrg(p_IProgressMonitor);
              p_IProgressMonitor.done();
		  } 
		  
		  return Status.OK_STATUS;
	  }
	  
	  public void getMfgAttributes(IProgressMonitor p_IProgressMonitor) {
  		 
		  ArrayList<ModelObject> arrItemObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrMiscObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrBOMLineObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrRevisionObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrSelectedItemObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrAllSecondaryMfgForms = new ArrayList<ModelObject>();
		  LinkedHashMap<ModelObject, List<ModelObject>> lnhMfgOrgAttrForms = new LinkedHashMap<ModelObject, List<ModelObject>>();
		  
		  try {
			  
			  p_IProgressMonitor.worked(10);
		      p_IProgressMonitor.subTask("Loading...Manufacturing Items");
		      
		      for(int inx = 0; inx < m_selectedComponents.length; inx++) {
		    	  
		    	  if(m_selectedComponents[inx] instanceof TCComponentBOMLine) {
		    		  
		    		  arrBOMLineObjects.add((ModelObject)m_selectedComponents[inx]); 
		    	  } else {
		    		  		    		  
		    		  if(((Constants.BusinessObjects.strGET6MfgPart).equals(m_selectedComponents[inx].getType()) || (Constants.BusinessObjects.strGET6ElectPart).equals(m_selectedComponents[inx].getType()) || (Constants.BusinessObjects.strGET6MechPart).equals(m_selectedComponents[inx].getType()) || (Constants.BusinessObjects.strGET6SoftwarePart).equals(m_selectedComponents[inx].getType()))) {
		    			  
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
					  if(null != PropertyObj.getModelObjectValue()) {
						  
						  if((Constants.BusinessObjects.strGET6MfgPart).equals(PropertyObj.getModelObjectValue().getTypeObject().toString()) || (Constants.BusinessObjects.strGET6ElectPart).equals(PropertyObj.getModelObjectValue().getTypeObject().toString()) || (Constants.BusinessObjects.strGET6MechPart).equals(PropertyObj.getModelObjectValue().getTypeObject().toString()) || (Constants.BusinessObjects.strGET6SoftwarePart).equals(PropertyObj.getModelObjectValue().getTypeObject().toString())) {
				    			
							  arrSelectedItemObjects.add(PropertyObj.getModelObjectValue());
						  } else {
							  
							  arrMiscObjects.add(PropertyObj.getModelObjectValue());
						  }
					  }
				  }
		      } 
		      
		      if(arrItemObjects.size() > 0) {
		    	  
		    	  arrSelectedItemObjects.addAll(arrItemObjects);
		      }
			  
			  p_IProgressMonitor.worked(10);
		      p_IProgressMonitor.subTask("Loading...Manufacturing Attributes Forms");
			  ServiceData selectedSecondaryObjectsSD = this.m_DataManagementServiceObj.getProperties(arrSelectedItemObjects.toArray(new ModelObject[ arrSelectedItemObjects.size() ]), new String[] { Constants.BusinessObjects.Properties.strObjectString, Constants.BusinessObjects.Properties.strRevisionList, Constants.BusinessObjects.strGET6PartOrgRelation });
			  for(int inx = 0; inx < selectedSecondaryObjectsSD.sizeOfPlainObjects(); inx++) {
				  
				  Property PropertyObj = selectedSecondaryObjectsSD.getPlainObject(inx).getPropertyObject(Constants.BusinessObjects.strGET6PartOrgRelation);
				  lnhMfgOrgAttrForms.put(selectedSecondaryObjectsSD.getPlainObject(inx), Arrays.asList(PropertyObj.getModelObjectArrayValue()));
				  arrAllSecondaryMfgForms.addAll(Arrays.asList(PropertyObj.getModelObjectArrayValue()));  
				  
				  Property PropertyRevObj = selectedSecondaryObjectsSD.getPlainObject(inx).getPropertyObject(Constants.BusinessObjects.Properties.strRevisionList);
				  arrRevisionObjects.addAll(Arrays.asList(PropertyRevObj.getModelObjectArrayValue()));
			  }
			 
			 p_IProgressMonitor.worked(10);
			 p_IProgressMonitor.subTask("Loading...Manufacturing Attributes Form Properties");
			 this.m_DataManagementServiceObj.getProperties(arrAllSecondaryMfgForms.toArray(new ModelObject[ arrAllSecondaryMfgForms.size() ]), new String[] { Constants.BusinessObjects.Properties.strget6MakeBuy, Constants.BusinessObjects.Properties.strOwningProject, Constants.BusinessObjects.Properties.strget6PlanningCode, Constants.BusinessObjects.Properties.strget6StructureCode, Constants.BusinessObjects.Properties.strget6StockMaterial, Constants.BusinessObjects.Properties.strget6StockMaterialQuantity, Constants.BusinessObjects.Properties.strget6ItemPublishDate, Constants.BusinessObjects.Properties.strget6BOMPublishDate });
			 
			 p_IProgressMonitor.worked(10);
			 p_IProgressMonitor.subTask("Loading...Manufacturing Attributes Form Properties");
			 this.m_DataManagementServiceObj.getProperties(arrRevisionObjects.toArray(new ModelObject[ arrRevisionObjects.size() ]), new String[] { Constants.BusinessObjects.Properties.strget6EngMakeBuy });
			 
			 for(ModelObject selectedItemObject : lnhMfgOrgAttrForms.keySet()) {
				 
				 ManufacturingAttributesFormBean ManufacturingAttributesFormBeanObj = new ManufacturingAttributesFormBean();
				 ManufacturingAttributesFormBeanObj.setObjectString(selectedItemObject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString));
				 ManufacturingAttributesFormBeanObj.setTCComponentItem((TCComponentItem)selectedItemObject);
				 if(!(Constants.BusinessObjects.strGET6MfgPart).equals(selectedItemObject.getTypeObject().getName())) {
					 Property PropertyObj = selectedItemObject.getPropertyObject(Constants.BusinessObjects.Properties.strRevisionList);
					 ManufacturingAttributesFormBeanObj.setEngMakeBuy(PropertyObj.getModelObjectArrayValue()[PropertyObj.getModelObjectArrayValue().length - 1].getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6EngMakeBuy));
				 }
				  
				for(int inx = 0; inx < lnhMfgOrgAttrForms.get(selectedItemObject).size(); inx++) {
					
					 if(lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strOwningProject).contains(this.m_strCurrentProject)) {
						 
						 ManufacturingAttributesFormBeanObj.setMakeBuy(lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6MakeBuy));
						 ManufacturingAttributesFormBeanObj.setTCProject(lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strOwningProject));
						 ManufacturingAttributesFormBeanObj.setPlanningCode(lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6PlanningCode));
						 
						 if(!lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6StockMaterialQuantity).equals(Constants.General.EMPTY_STRING_VALUE_C)) {
							
							 ManufacturingAttributesFormBeanObj.setStockMaterialQuantity(Double.parseDouble(lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6StockMaterialQuantity)));
						 }
						 
						 if(!lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6StructureCode).equals(Constants.General.EMPTY_STRING_VALUE_C)) {
							 ManufacturingAttributesFormBeanObj.setStructureCode(((TCComponent)lnhMfgOrgAttrForms.get(selectedItemObject).get(inx)).getIntProperty(Constants.BusinessObjects.Properties.strget6StructureCode));
						 }
						 
						 if(!(Constants.General.EMPTY_STRING_VALUE_C).equals(lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6StockMaterial))) {
							 ManufacturingAttributesFormBeanObj.setStockMaterialItem((TCComponentItem)lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyObject(Constants.BusinessObjects.Properties.strget6StockMaterial).getModelObjectValue());
							 ManufacturingAttributesFormBeanObj.setStockMaterial(lnhMfgOrgAttrForms.get(selectedItemObject).get(inx).getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6StockMaterial));
						 }
						 ManufacturingAttributesFormBeanObj.setItemPublishDate(((TCComponent)lnhMfgOrgAttrForms.get(selectedItemObject).get(inx)).getDateProperty(Constants.BusinessObjects.Properties.strget6ItemPublishDate));
						 ManufacturingAttributesFormBeanObj.setBOMPublishDate(((TCComponent)lnhMfgOrgAttrForms.get(selectedItemObject).get(inx)).getDateProperty(Constants.BusinessObjects.Properties.strget6BOMPublishDate));
						 ManufacturingAttributesFormBeanObj.setTCComponentForm((TCComponentForm)lnhMfgOrgAttrForms.get(selectedItemObject).get(inx)); 
						 break;
					 }
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
				 
				 showErrorMessage("Valid Objects are\n	-GET Mechanical Part\n	-GET Software Part\n	-GET Electrical part\n	-GET Manufacturing Part", "Invalid Objects Found", "Following objects are found invalid and will be ignored", arrErrorMessage);
			 }
			  
		  } catch (Exception tcObj) {
			  
			  ArrayList<String> arrErrorMessage = new ArrayList<String>();
			  arrErrorMessage.add(tcObj.toString());
			  showErrorMessage(tcObj.toString(), "Exception Thrown", "Exception", arrErrorMessage);
		  }
	  }
	  
	  public Map<String, ManufacturingAttributesFormBean> getSelectedComponentsData() {
		  
		  return m_hshMapFormValues;
	  }
	  
	  public void assignOrg(IProgressMonitor p_IProgressMonitor) {
		  
		  ArrayList<ManufacturingAttributesFormBean> arrNewMfgAttributesForms = new ArrayList<ManufacturingAttributesFormBean>();
		  ArrayList<String> vItemIDs = new ArrayList<String> ();
		  
		  try {
			  
			  p_IProgressMonitor.worked(10);
			  p_IProgressMonitor.subTask("Collecting Input...");
			  for(ManufacturingAttributesFormBean ManufacturingAttributesFormBeanObj : this.m_hshMapFormValues.values()) {
				    
				   m_iIndex++;
		        	if(ManufacturingAttributesFormBeanObj.getModified()) {
						  
		        		if(null != ManufacturingAttributesFormBeanObj.getTCComponentForm()) {
							// Check the form release status and if released it should be in workflow.
		        			
		        			String sRelStatus = ManufacturingAttributesFormBeanObj.getTCComponentForm().getProperty ( Constants.BusinessObjects.Properties.strRelStatus );
							String sProcessStage = ManufacturingAttributesFormBeanObj.getTCComponentForm().getProperty ( Constants.BusinessObjects.Properties.strProcessStage );
							if ( ( sRelStatus.equalsIgnoreCase ( Constants.General.RELEASE_STATUS_VALUE) ==false ) || !( sProcessStage.isEmpty() ) )
							{
								this.setMFGFormAttributes ( ManufacturingAttributesFormBeanObj.getTCComponentForm(), ManufacturingAttributesFormBeanObj );
							}
							else
							{
								vItemIDs.add  (ManufacturingAttributesFormBeanObj.getTCComponentItem().getProperty ( Constants.BusinessObjects.Properties.strObjectString ) );
							}
						} else {

							arrNewMfgAttributesForms.add(ManufacturingAttributesFormBeanObj);
					   }
				   }
		  		}
			  p_IProgressMonitor.worked(2);
			  if ( vItemIDs.size()!= 0 )
			  {
				  showErrorMessage ( " Manufacturing Attributes for the following Part(s) are non-editable. Click on Details for More Information...", "Manufacturing Attributes cannot be modified ", "Following are the Item Details", vItemIDs );  
			  }
			  p_IProgressMonitor.worked(10);
			  p_IProgressMonitor.subTask("Creating New Data...");
			  this.createMFGAttributesForms(arrNewMfgAttributesForms);
			  
			  p_IProgressMonitor.worked(40);
			  p_IProgressMonitor.subTask("Refreshing Application...");
			  
			  if(AIFUtility.getCurrentApplication() instanceof AbstractPSEApplication) {
				  ((AbstractPSEApplication)AIFUtility.getCurrentApplication()).getBOMWindow().refresh();
			  }
			 
		  } catch(Exception eObj) {
			  
			  ArrayList<String> arrErrorMessage = new ArrayList<String>();
			  arrErrorMessage.add(eObj.toString());
			  showErrorMessage(eObj.toString(), "Exception Thrown", "Exception", arrErrorMessage);
		  }
	  }
	  
	  
	  private Map<String, String[]> getMFGFormAttributesCreateMap(ManufacturingAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
		  
		  Map<String, String[]> propertiesValues = new  HashMap<String, String[]>();
		  String[] strPropertyValues = new String[] {  p_ManufacturingAttributesFormBeanObj.getMakeBuy() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6MakeBuy, strPropertyValues);
		  
		  strPropertyValues = new String[] {  p_ManufacturingAttributesFormBeanObj.getPlanningCode() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6PlanningCode, strPropertyValues);
		  
		  strPropertyValues = new String[] {  Double.toString(p_ManufacturingAttributesFormBeanObj.getStockMaterialQuantity()) };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StockMaterialQuantity, strPropertyValues);
		  
		  if(p_ManufacturingAttributesFormBeanObj.getStructureCode() != -1) {
			  
			  if(Constants.ManufacturingAttributesDialog.iClearIntProperty == p_ManufacturingAttributesFormBeanObj.getStructureCode()) {
				  
				  strPropertyValues = new String[] {  Constants.General.EMPTY_STRING_VALUE_C };
			  } else {
				  strPropertyValues = new String[] {  Property.toIntString(p_ManufacturingAttributesFormBeanObj.getStructureCode()) };
			  }
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StructureCode, strPropertyValues);
		  }
		  
		  if(null != p_ManufacturingAttributesFormBeanObj.getStockMaterialItem()) {
			  
			  strPropertyValues = new String[] { Property.toModelObjectString(p_ManufacturingAttributesFormBeanObj.getStockMaterialItem()) };
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StockMaterial, strPropertyValues);
		  } else {
			  
			  strPropertyValues = new String[] { Constants.General.EMPTY_STRING_VALUE_C };
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StockMaterial, strPropertyValues);
		  }
		  
		  return propertiesValues;
	  }
	  
	  private Map<String, DataManagementService.VecStruct> getMFGFormAttributesUpdateMap(ManufacturingAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
		  
		  Map<String, DataManagementService.VecStruct> propertiesValues = new  HashMap<String, DataManagementService.VecStruct>();
		  DataManagementService.VecStruct vectorPropertyMakeBuy = new DataManagementService.VecStruct();
		  vectorPropertyMakeBuy.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getMakeBuy() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6MakeBuy, vectorPropertyMakeBuy);
		  
		  DataManagementService.VecStruct vectorPropertyPlanningCode = new DataManagementService.VecStruct();
		  vectorPropertyPlanningCode.stringVec = new String[] {  p_ManufacturingAttributesFormBeanObj.getPlanningCode() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6PlanningCode, vectorPropertyPlanningCode);
		  
		  DataManagementService.VecStruct vectorPropertyStockMaterialQuantity = new DataManagementService.VecStruct();
		  vectorPropertyStockMaterialQuantity.stringVec = new String[] {  Double.toString(p_ManufacturingAttributesFormBeanObj.getStockMaterialQuantity()) };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StockMaterialQuantity, vectorPropertyStockMaterialQuantity);
		  
		  if(p_ManufacturingAttributesFormBeanObj.getStructureCode() != -1) {
			  
			  DataManagementService.VecStruct vectorPropertyStructureCode = new DataManagementService.VecStruct();
			  
			  if(Constants.ManufacturingAttributesDialog.iClearIntProperty == p_ManufacturingAttributesFormBeanObj.getStructureCode()) {
				 
				  vectorPropertyStructureCode.stringVec = new String[] { Constants.General.EMPTY_STRING_VALUE_C };
			  } else {
				  vectorPropertyStructureCode.stringVec = new String[] { Property.toIntString(p_ManufacturingAttributesFormBeanObj.getStructureCode()) };
			  }
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StructureCode, vectorPropertyStructureCode);
		  }
		  
		  if(null != p_ManufacturingAttributesFormBeanObj.getStockMaterialItem()) {
			  
			  DataManagementService.VecStruct vectorPropertyStockMaterial = new DataManagementService.VecStruct();
			  vectorPropertyStockMaterial.stringVec = new String[] { Property.toModelObjectString(p_ManufacturingAttributesFormBeanObj.getStockMaterialItem()) };
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StockMaterial, vectorPropertyStockMaterial);
		  } else {
			  
			  DataManagementService.VecStruct vectorPropertyStockMaterial = new DataManagementService.VecStruct();
			  vectorPropertyStockMaterial.stringVec = new String[] { Constants.General.EMPTY_STRING_VALUE_C };
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StockMaterial, vectorPropertyStockMaterial);
		  }
		  
		  DataManagementService.VecStruct vectorPropertyTemplateId = new DataManagementService.VecStruct();
		  vectorPropertyTemplateId.stringVec = new String[] { "true" };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6IsMfgAttrModT4OXfer, vectorPropertyTemplateId);
		  
		  return propertiesValues;
	  }
	  
	  private void setMFGFormAttributes(TCComponentForm p_TCComponentFormObj,  ManufacturingAttributesFormBean p_ManufacturingAttributesFormBeanObj) throws ServiceException {
		  		
		      String strErrorMessage = Constants.General.EMPTY_STRING_VALUE_C;
			  
			  ServiceData ServiceDataObj = this.m_DataManagementServiceObj.setProperties(new ModelObject[]{ p_TCComponentFormObj }, getMFGFormAttributesUpdateMap(p_ManufacturingAttributesFormBeanObj));
			  if(ServiceDataObj.sizeOfPartialErrors() > 0) {
				  
				  for(int inx = 0; inx < ServiceDataObj.sizeOfPartialErrors(); inx++) {
					  
					  strErrorMessage +=  ServiceDataObj.getPartialError(inx).getMessages()[1] + "\n";
				  }
				  
				  throw new ServiceException(strErrorMessage);
			  }
	  }
	  
	  public void createMFGAttributesForms(ArrayList<ManufacturingAttributesFormBean> p_arrNewMfgAttributesForms) throws ServiceException {
		
		String strErrorMessage = Constants.General.EMPTY_STRING_VALUE_C;
		TCPreferenceService TCPreferenceServiceObj = ((TCSession)AIFUtility.getDefaultSession()).getPreferenceService();
		final String strFormName = m_strCurrentProject + Constants.ManufacturingAttributesDialog.strManufacturingAttributesSuffix;
		final String strFormType = TCPreferenceServiceObj.getStringValue(Constants.ManufacturingAttributesDialog.strFormTypePrefPrefix + this.m_strCurrentProject + Constants.ManufacturingAttributesDialog.strFormTypePrefSuffix);
		FormInfo[] FormInfoInput = new FormInfo[p_arrNewMfgAttributesForms.size()];
		
		for(int inx = 0; inx < p_arrNewMfgAttributesForms.size(); inx++) {
			
			FormInfoInput[inx] = new FormInfo();
			FormInfoInput[inx].clientId = p_arrNewMfgAttributesForms.get(inx).getObjectString();
			FormInfoInput[inx].description= strFormName;
			FormInfoInput[inx].name = strFormName;
			FormInfoInput[inx].formType = strFormType;
			FormInfoInput[inx].saveDB = true;
			FormInfoInput[inx].parentObject = null;
			FormInfoInput[inx].relationName = Constants.BusinessObjects.strGET6PartOrgRelation;
			FormInfoInput[inx].attributesMap = this.getMFGFormAttributesCreateMap(p_arrNewMfgAttributesForms.get(inx));
		}
		
		CreateOrUpdateFormsResponse CreateOrUpdateFormsResponseObj = this.m_DataManagementServiceObj.createOrUpdateForms(FormInfoInput);
		
		Relationship[] RelationshipObjs = new Relationship[CreateOrUpdateFormsResponseObj.outputs.length];
		for(int inx = 0; inx < CreateOrUpdateFormsResponseObj.outputs.length; inx++) {
			
			for(ManufacturingAttributesFormBean ManufacturingAttributesFormBeanObj : p_arrNewMfgAttributesForms) {
				
				if(ManufacturingAttributesFormBeanObj.getObjectString().equals(CreateOrUpdateFormsResponseObj.outputs[inx].clientId)) {
					
					RelationshipObjs[inx] = new Relationship();
					RelationshipObjs[inx].primaryObject = ManufacturingAttributesFormBeanObj.getTCComponentItem();
					RelationshipObjs[inx].relationType =  Constants.BusinessObjects.strGET6PartOrgRelation;
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