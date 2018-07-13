package com.ge.transportation.plm.mfg.operations;

import java.util.ArrayList;
import java.util.Arrays;
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

import com.ge.transportation.plm.mfg.beans.StockMaterialAttributesFormBean;
import com.ge.transportation.plm.mfg.constants.Constants;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.services.loose.core.DataManagementService;
import com.teamcenter.services.loose.core._2006_03.DataManagement.Relationship;
import com.teamcenter.services.loose.core._2007_01.DataManagement.CreateOrUpdateFormsResponse;
import com.teamcenter.services.loose.core._2007_01.DataManagement.FormInfo;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.Property;
import com.teamcenter.soa.client.model.ServiceData;

   public class StockMaterialAttributesOperation extends Job  {
	 
	  private int m_iIndex = 0;
	  private boolean m_isInitData = false;
	  private boolean m_isSaveData = false;
	  private Table m_SelectedItemsTable = null;
	  private InterfaceAIFComponent[] m_selectedComponents = null;
	  private String m_strStatusMessage = Constants.General.EMPTY_STRING_VALUE_C;
	  private String m_strCurrentProject = Constants.General.EMPTY_STRING_VALUE_C;
	  private DataManagementService m_DataManagementServiceObj = null;
	  
	  private LinkedHashMap<String, StockMaterialAttributesFormBean> m_hshMapFormValues = new LinkedHashMap<String, StockMaterialAttributesFormBean>();
	  
	  public StockMaterialAttributesOperation(String p_strStatusMessage, String p_strCurrentProject, Table p_SelectedItemsTable, InterfaceAIFComponent[] p_selectedComponents) {
		  	
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
	  
	  public StockMaterialAttributesOperation(String p_strStatusMessage, String p_strCurrentProject, Table p_SelectedItemsTable, LinkedHashMap<String, StockMaterialAttributesFormBean> p_hshMapFormValues) {
		  	
		super(p_strStatusMessage); 
		setUser(true);
	    this.m_iIndex = 0;
	    this.m_hshMapFormValues.clear(); 
	    this.m_strStatusMessage = p_strStatusMessage;
	    this.m_strCurrentProject = p_strCurrentProject;
	    this.m_SelectedItemsTable = p_SelectedItemsTable;
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
		  		    iProgressService.showInDialog(m_SelectedItemsTable.getShell(), StockMaterialAttributesOperation.this); 
		        }
		  });
		  
		  if(this.m_isInitData) {
			  
			  p_IProgressMonitor.beginTask(this.m_strStatusMessage, m_selectedComponents.length);
			  getStockMaterialAttributes(p_IProgressMonitor);
              p_IProgressMonitor.done();
		  } else if(this.m_isSaveData) {
			  
			  p_IProgressMonitor.beginTask(this.m_strStatusMessage, m_hshMapFormValues.size());
			  setStockMaterialAttributes(p_IProgressMonitor);
              p_IProgressMonitor.done();
		  } 
		  
		  return Status.OK_STATUS;
	  }
	  
	  public void getStockMaterialAttributes(IProgressMonitor p_IProgressMonitor) {
  		 
		  ArrayList<ModelObject> arrItemObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrMiscObjects = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrAllSecondaryStockMaterials = new ArrayList<ModelObject>();
		  ArrayList<ModelObject> arrAllStockMaterialsAttrForms = new ArrayList<ModelObject>();
		  
		  try {
			  
			  p_IProgressMonitor.worked(10);
		      p_IProgressMonitor.subTask("Loading...Stock Material Items");
		      
		      for(int inx = 0; inx < m_selectedComponents.length; inx++) {
		    	  
		    	  if(m_selectedComponents[inx] instanceof TCComponentBOMLine) {
		    		  
		    		  arrMiscObjects.add((ModelObject)m_selectedComponents[inx]); 
		    	  } else {
		    		  
		    		  if((Constants.BusinessObjects.strGET6Material).equals(m_selectedComponents[inx].getType())) {
		    			  
		    			  arrItemObjects.add((ModelObject)m_selectedComponents[inx]);
		    		  } else {
		    			  
		    			  arrMiscObjects.add((ModelObject)m_selectedComponents[inx]);
		    		  }
		    	  }
		      }
			  
			  p_IProgressMonitor.worked(10);
		      p_IProgressMonitor.subTask("Loading...Stock Material Items");
			  ServiceData selectedSecondaryObjectsSD = this.m_DataManagementServiceObj.getProperties(arrItemObjects.toArray(new ModelObject[ arrItemObjects.size() ]), new String[] { Constants.BusinessObjects.strGET6HasStockMatl });
			  for(int inx = 0; inx < selectedSecondaryObjectsSD.sizeOfPlainObjects(); inx++) {
				  
				  Property PropertyObj = selectedSecondaryObjectsSD.getPlainObject(inx).getPropertyObject(Constants.BusinessObjects.strGET6HasStockMatl);
				  arrAllSecondaryStockMaterials.addAll(Arrays.asList(PropertyObj.getModelObjectArrayValue()));  
			  }
			 
			 p_IProgressMonitor.worked(10);
			 p_IProgressMonitor.subTask("Loading...Stock Material Attributes Properties");
			 this.m_DataManagementServiceObj.getProperties(arrAllSecondaryStockMaterials.toArray(new ModelObject[ arrAllSecondaryStockMaterials.size() ]), new String[] { Constants.BusinessObjects.Properties.strObjectString, Constants.BusinessObjects.strGET6StockHasOrgPropsAttri });
			 
			 for(ModelObject stockMaterialObject : arrAllSecondaryStockMaterials) {
				 
				 Property PropertyObj = stockMaterialObject.getPropertyObject(Constants.BusinessObjects.strGET6StockHasOrgPropsAttri);
				 arrAllStockMaterialsAttrForms.addAll(Arrays.asList(PropertyObj.getModelObjectArrayValue()));	
			 }
			 
			 p_IProgressMonitor.worked(10);
			 p_IProgressMonitor.subTask("Loading...Stock Material Attributes Properties");
			 this.m_DataManagementServiceObj.getProperties(arrAllStockMaterialsAttrForms.toArray(new ModelObject[ arrAllStockMaterialsAttrForms.size() ]), new String[] { Constants.BusinessObjects.Properties.strOwningProject, Constants.BusinessObjects.Properties.strget6StructureCode, Constants.BusinessObjects.Properties.strget6OrgPreferredStock });
			 
			 for(ModelObject stockMaterialObject : arrAllSecondaryStockMaterials) {
				 
				 StockMaterialAttributesFormBean StockMaterialAttributesFormBeanObj = new StockMaterialAttributesFormBean();
				 StockMaterialAttributesFormBeanObj.setObjectString(stockMaterialObject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString));
				 StockMaterialAttributesFormBeanObj.setTCComponentItem((TCComponentItem)stockMaterialObject);
				 
				 Property PropertyObj = stockMaterialObject.getPropertyObject(Constants.BusinessObjects.strGET6StockHasOrgPropsAttri);
				 for(int inx = 0; inx < PropertyObj.getModelObjectArrayValue().length; inx++) {
					 
					 if(PropertyObj.getModelObjectArrayValue()[inx].getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strOwningProject).contains(this.m_strCurrentProject)) {
						 
						 StockMaterialAttributesFormBeanObj.setTCProject(PropertyObj.getModelObjectArrayValue()[inx].getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strOwningProject));
						 if(!PropertyObj.getModelObjectArrayValue()[inx].getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6StructureCode).equals(Constants.General.EMPTY_STRING_VALUE_C)) {
							 StockMaterialAttributesFormBeanObj.setStructureCode(((TCComponent)PropertyObj.getModelObjectArrayValue()[inx]).getIntProperty(Constants.BusinessObjects.Properties.strget6StructureCode));
						 }
						
						 StockMaterialAttributesFormBeanObj.setPreferred(PropertyObj.getModelObjectArrayValue()[inx].getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strget6OrgPreferredStock).toLowerCase());
						 StockMaterialAttributesFormBeanObj.setTCComponentForm((TCComponentForm)PropertyObj.getModelObjectArrayValue()[inx]);
						 break;
					 }
				 }
				 
				 p_IProgressMonitor.worked(1);
				 p_IProgressMonitor.subTask("Loading..." + "(" + this.m_iIndex + "/" + m_selectedComponents.length + ")" + stockMaterialObject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString));
				 m_hshMapFormValues.put(stockMaterialObject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString), StockMaterialAttributesFormBeanObj);
				 this.m_iIndex++;
			 }
			 
			 if(arrMiscObjects.size() > 0) {
				 
				 ArrayList<String> arrErrorMessage = new ArrayList<String>();
				 for(int inx = 0; inx < arrMiscObjects.size(); inx++) {
					 
					 arrErrorMessage.add(arrMiscObjects.get(inx) + " 	- 	" + arrMiscObjects.get(inx).getTypeObject().getUIFValue());
				 }
				 
				 showErrorMessage("Valid Objects are\n	-GET Material", "Invalid Objects Found", "Following objects are found invalid and will be ignored", arrErrorMessage);
			 }
			  
		  } catch (Exception tcObj) {
			  
			  ArrayList<String> arrErrorMessage = new ArrayList<String>();
			  arrErrorMessage.add(tcObj.getMessage());
			  showErrorMessage(tcObj.getMessage(), "Exception Thrown", "Exception", arrErrorMessage);
		  }
	  }
	  
	  public LinkedHashMap<String, StockMaterialAttributesFormBean> getSelectedComponentsData() {
		  
		  return m_hshMapFormValues;
	  }
	  
	  private Map<String, String[]> getStockMtrlAttributesCreateMap(StockMaterialAttributesFormBean p_StockMaterialAttributesFormBeanObj) {
		  
		  Map<String, String[]> propertiesValues = new  HashMap<String, String[]>();
		  String[] strPropertyValues = new String[] {  p_StockMaterialAttributesFormBeanObj.getPreferred() };
		  
		  strPropertyValues = new String[] {  p_StockMaterialAttributesFormBeanObj.getPreferred() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6OrgPreferredStock, strPropertyValues);
		  
		  if(p_StockMaterialAttributesFormBeanObj.getStructureCode() != -1) {
			  
			  strPropertyValues = new String[] {  Integer.toString(p_StockMaterialAttributesFormBeanObj.getStructureCode()) };
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StructureCode, strPropertyValues);
		  }
		  
		  return propertiesValues;
	  }
	  
	  private Map<String, DataManagementService.VecStruct> getStockMtrlAttributesUpdateMap(StockMaterialAttributesFormBean p_StockMaterialAttributesFormBeanObj) {
		  
		  Map<String, DataManagementService.VecStruct> propertiesValues = new  HashMap<String, DataManagementService.VecStruct>();
		  DataManagementService.VecStruct vectorPropertyOrgPreferred = new DataManagementService.VecStruct();
		  
		  vectorPropertyOrgPreferred = new DataManagementService.VecStruct();
		  vectorPropertyOrgPreferred.stringVec = new String[] {  p_StockMaterialAttributesFormBeanObj.getPreferred() };
		  propertiesValues.put(Constants.BusinessObjects.Properties.strget6OrgPreferredStock, vectorPropertyOrgPreferred);
		  
		  if(p_StockMaterialAttributesFormBeanObj.getStructureCode() != -1) {
			  
			  DataManagementService.VecStruct vectorPropertyStructureCode = new DataManagementService.VecStruct();
			  vectorPropertyStructureCode.stringVec = new String[] { Integer.toString(p_StockMaterialAttributesFormBeanObj.getStructureCode()) };
			  propertiesValues.put(Constants.BusinessObjects.Properties.strget6StructureCode, vectorPropertyStructureCode);
		  }
		  
		  return propertiesValues;
	  }
	  
	  private void setStockMaterialAttributes(TCComponentForm p_TCComponentFormObj,  StockMaterialAttributesFormBean p_StockMaterialAttributesFormBeanObj) throws ServiceException {
	  		
	      String strErrorMessage = Constants.General.EMPTY_STRING_VALUE_C;
		  
		  ServiceData ServiceDataObj = this.m_DataManagementServiceObj.setProperties(new ModelObject[]{ p_TCComponentFormObj }, getStockMtrlAttributesUpdateMap(p_StockMaterialAttributesFormBeanObj));
		  if(ServiceDataObj.sizeOfPartialErrors() > 0) {
			  
			  for(int inx = 0; inx < ServiceDataObj.sizeOfPartialErrors(); inx++) {
				  
				  strErrorMessage +=  ServiceDataObj.getPartialError(inx).getMessages()[0] + "\n";
			  }
			  
			  throw new ServiceException(strErrorMessage);
		  }
	  }
	  
	  public void setStockMaterialAttributes(IProgressMonitor p_IProgressMonitor) {
		  
		  ArrayList<StockMaterialAttributesFormBean> arrNewStockAttributesForms = new ArrayList<StockMaterialAttributesFormBean>();
		 
		  try {
			  for(StockMaterialAttributesFormBean StockMaterialAttributesFormBeanObj : this.m_hshMapFormValues.values()) {
				    
				   p_IProgressMonitor.worked(1);
				   p_IProgressMonitor.subTask("Saving..." + "(" + m_iIndex + "/" + m_hshMapFormValues.size() + ")" + StockMaterialAttributesFormBeanObj.getObjectString());
				   m_iIndex++;
		        	if(StockMaterialAttributesFormBeanObj.getModified()) {
						  
					  if((Constants.StockMaterialAttributesDialog.strNoneValue).equals(StockMaterialAttributesFormBeanObj.getPreferred())) {
						  
						   this.clearSelectedOrg(StockMaterialAttributesFormBeanObj);
						   continue;
					  }
					  
					 if(null != StockMaterialAttributesFormBeanObj.getTCComponentForm()) {
						  
						 this.setStockMaterialAttributes(StockMaterialAttributesFormBeanObj.getTCComponentForm(), StockMaterialAttributesFormBeanObj);
						  
					 } else {
						  	  
						 arrNewStockAttributesForms.add(StockMaterialAttributesFormBeanObj);
					 }
				  }
		  	   }
			  
			  p_IProgressMonitor.worked(10);
			  p_IProgressMonitor.subTask("Creating New Data...");
			  this.createStockMaterialAttrForms(arrNewStockAttributesForms);
			  
			  p_IProgressMonitor.worked(40);
			  p_IProgressMonitor.subTask("Refreshing Application...");
		  
		  } catch(Exception eObj) {
			  
			  ArrayList<String> arrErrorMessage = new ArrayList<String>();
			  arrErrorMessage.add(eObj.getMessage());
			  showErrorMessage(eObj.getMessage(), "Exception Thrown", "Exception", arrErrorMessage);
		  }
	  }
	  
	  private void clearSelectedOrg(StockMaterialAttributesFormBean p_StockMaterialAttributesFormBeanObj) throws TCException {
		  
		  if(null != p_StockMaterialAttributesFormBeanObj.getTCComponentForm()) {
			  	
			  p_StockMaterialAttributesFormBeanObj.getTCComponentItem().cutOperation(Constants.BusinessObjects.strGET6StockHasOrgPropsAttri, new TCComponent[] { p_StockMaterialAttributesFormBeanObj.getTCComponentForm() });
			  p_StockMaterialAttributesFormBeanObj.getTCComponentForm().delete();
			  this.m_hshMapFormValues.get(p_StockMaterialAttributesFormBeanObj.getObjectString()).setTCComponentForm(null);
		  } 
	  }
	  
	  public void createStockMaterialAttrForms(ArrayList<StockMaterialAttributesFormBean> p_arrNewStockMaterialAttrForms) throws ServiceException {
			
			String strErrorMessage = Constants.General.EMPTY_STRING_VALUE_C;
			final String strFormName = m_strCurrentProject + Constants.StockMaterialAttributesDialog.strStockMaterialAttributesSuffix;
			final String strFormType = Constants.BusinessObjects.strGET6StockOrgPropsFrm;
			FormInfo[] FormInfoInput = new FormInfo[p_arrNewStockMaterialAttrForms.size()];
			
			for(int inx = 0; inx < p_arrNewStockMaterialAttrForms.size(); inx++) {
				
				FormInfoInput[inx] = new FormInfo();
				FormInfoInput[inx].clientId = p_arrNewStockMaterialAttrForms.get(inx).getObjectString();
				FormInfoInput[inx].description= strFormName;
				FormInfoInput[inx].name = strFormName;
				FormInfoInput[inx].formType = strFormType;
				FormInfoInput[inx].saveDB = true;
				FormInfoInput[inx].parentObject = null;
				FormInfoInput[inx].relationName = Constants.BusinessObjects.strGET6StockHasOrgPropsAttri;
				FormInfoInput[inx].attributesMap = this.getStockMtrlAttributesCreateMap(p_arrNewStockMaterialAttrForms.get(inx));
			}
			
			CreateOrUpdateFormsResponse CreateOrUpdateFormsResponseObj = this.m_DataManagementServiceObj.createOrUpdateForms(FormInfoInput);
			
			Relationship[] RelationshipObjs = new Relationship[CreateOrUpdateFormsResponseObj.outputs.length];
			for(int inx = 0; inx < CreateOrUpdateFormsResponseObj.outputs.length; inx++) {
				
				for(StockMaterialAttributesFormBean StockMaterialAttributesFormBeanObj : p_arrNewStockMaterialAttrForms) {
					
					if(StockMaterialAttributesFormBeanObj.getObjectString().equals(CreateOrUpdateFormsResponseObj.outputs[inx].clientId)) {
						
						RelationshipObjs[inx] = new Relationship();
						RelationshipObjs[inx].primaryObject = StockMaterialAttributesFormBeanObj.getTCComponentItem();
						RelationshipObjs[inx].relationType =  Constants.BusinessObjects.strGET6StockHasOrgPropsAttri;
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