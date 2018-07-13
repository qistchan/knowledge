package com.ge.transportation.plm.srv.ui;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.InputStream;

import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;

import org.eclipse.core.runtime.jobs.IJobChangeEvent;
import org.eclipse.core.runtime.jobs.IJobChangeListener;
import org.eclipse.core.runtime.jobs.Job;
import org.eclipse.jface.dialogs.IDialogConstants;
import org.eclipse.jface.dialogs.IMessageProvider;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.dialogs.TitleAreaDialog;
import org.eclipse.jface.util.IPropertyChangeListener;
import org.eclipse.jface.util.PropertyChangeEvent;
import org.eclipse.swt.SWT;
import org.eclipse.swt.awt.SWT_AWT;
import org.eclipse.swt.custom.TableEditor;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;

import com.ge.transportation.plm.srv.beans.ServicesAttributesFormBean;
import com.ge.transportation.plm.srv.constants.Constants;
import com.ge.transportation.plm.srv.operations.ServiceAttributesOperation;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.common.lov.common.LOVPropertyValue;
import com.teamcenter.rac.common.lov.view.controls.LOVDisplayer;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentFormType;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCComponentItemType;
import com.teamcenter.rac.kernel.TCComponentProject;
import com.teamcenter.rac.kernel.TCPropertyDescriptor;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.util.iTextField;
import com.teamcenter.rac.util.combobox.iComboBox;
import com.teamcenter.services.loose.core.DataManagementService;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.Property;
/**
* <h1>ServicesAttributes</h1>
* This class implements creation of 
* Services Form Type for Services functionality 
* using the Custom UI
*
* @author  Sudheer Arikere
* @version 1.0
* @since   2017-09-07
*/

public class ServicesAttributes extends TitleAreaDialog{
	
	private Button m_saveButton = null;
	 private Button m_cancelButton = null;
	 private boolean m_isValueChanged = false;
	 private boolean m_canClosewindow = false;
	 private Table m_SelectedItemsTable = null;
	 private TCPropertyDescriptor m_TCPropertyEFDescriptorObj = null;
	 private TCPropertyDescriptor m_TCPropertySCDescriptorObj = null;
	 private TCPropertyDescriptor m_TCPropertyTTDescriptorObj = null;
	 private TCPropertyDescriptor m_TCPropertyCIDescriptorObj = null;
	 
	 private InterfaceAIFComponent[] m_selectedComponent = null;
	 
	 private Map<String, ServicesAttributesFormBean> m_hshMapFormValues = Collections.synchronizedMap(new LinkedHashMap<String, ServicesAttributesFormBean>());
	 
	 public ServicesAttributes(Shell p_parentShell) {
		 
		 super(p_parentShell);
		
	 }
	 
	 @Override
	  public void create() {
	    super.create();
	    this.getShell().setText(Constants.ManufacturingAttributesDialog.strTitle);
	    setTitle(Constants.ManufacturingAttributesDialog.strTitle);
	    setMessage(Constants.ManufacturingAttributesDialog.strTitleDesc, IMessageProvider.INFORMATION);
	  }

	  @Override
	  protected Control createDialogArea(Composite p_CompositeParent) {
		  p_CompositeParent.setToolTipText("");

		  Composite CompositeContainer = (Composite)super.createDialogArea(p_CompositeParent);

		  m_SelectedItemsTable = new Table(CompositeContainer, SWT.BORDER | SWT.FULL_SELECTION | SWT.MULTI | SWT.EMBEDDED);
		  m_SelectedItemsTable.setLinesVisible(true);
		  m_SelectedItemsTable.setHeaderVisible(true);
		  m_SelectedItemsTable.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));

		  TableColumn itemIDTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  itemIDTableColumn.pack();
		  itemIDTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnItemID);

		  TableColumn preferredNameTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  preferredNameTableColumn.pack();
		  preferredNameTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnName);

		  TableColumn preferredStockTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  preferredStockTableColumn.pack();
		  preferredStockTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnServiceable);

		  TableColumn serializeTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  serializeTableColumn.pack();
		  serializeTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnSerialize);

		  TableColumn repairableTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  repairableTableColumn.pack();
		  repairableTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnRepairable);

		  TableColumn positiontrackTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  positiontrackTableColumn.pack();
		  positiontrackTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnPositionTrack);


		  TableColumn structureCodeTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  structureCodeTableColumn.pack();
		  structureCodeTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnStructureCode);

		  TableColumn tierTypeTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  tierTypeTableColumn.pack();
		  tierTypeTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnTierType);

		  TableColumn compIDTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
		  compIDTableColumn.pack();
		  compIDTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnCompID);

		  m_SelectedItemsTable.addListener(SWT.Resize, new Listener() {

			  public void handleEvent(Event event) {

				  Table selectedItemTable = (Table)event.widget;
				  int iColumnCount = selectedItemTable.getColumnCount();
				  if(iColumnCount == 0) {
					  return;
				  }

				  for(TableColumn TableColumnObj: selectedItemTable.getColumns()) {

					  TableColumnObj.setWidth((selectedItemTable.getClientArea().width)/(iColumnCount));
				  }
			  }
		  });

		  m_SelectedItemsTable.addListener(SWT.MouseDown, new Listener(){
			  public void handleEvent(Event event){
				  Point PointObj = new Point(event.x, event.y);
				  TableItem TableItemObj = m_SelectedItemsTable.getItem(PointObj);
				  Control[] embededControlObjs = m_SelectedItemsTable.getChildren();
				  for(int inx = 0; inx < embededControlObjs.length; inx++) {

					  if(embededControlObjs[inx] instanceof Composite) {
						  embededControlObjs[inx].dispose();
					  }
				  }
				  if(TableItemObj != null) {
					  for (int icol = 0; icol < m_SelectedItemsTable.getColumnCount(); icol++) {
						  Rectangle RectangleObj = TableItemObj.getBounds(icol);
						  if (RectangleObj.contains(PointObj)) {

							  if(icol == 1) {

								  addServiceEngineFamilyLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
							  } else if(icol == 2) {

								  addSetServiceableDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));

							  } else if(icol == 3) {

								  addSetSerializeDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));

							  }else if(icol == 4) {

								  addSetRepairableDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));

							  } else if(icol == 5) {

								  addSetPositionTrackDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
							  } else if(icol == 6) {

								  addServiceItemTypeLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
							  } else if(icol == 7) {

								  addServiceTierTypeLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));

							  } else if(icol == 8) {

								  addServiceCompIDLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));

							  }
						  }
					  }
				  }

				  m_SelectedItemsTable.redraw();
			  }
		  });

		  Display.getDefault().asyncExec(new Runnable() {
			  public void run() {
				  init();
			  }
		  });

		  return CompositeContainer;
	  }
	  
	  protected Point getInitialSize() {
			return new Point(820, 500);
	  }
	  
	  @Override
	  protected boolean isResizable() {
	    return true;
	  }
	  
	  protected boolean canHandleShellCloseEvent() {
		    return m_canClosewindow;
	  }

	  
	  protected void createButtonsForButtonBar(Composite parent) {
		  
	        this.m_saveButton = createButton(parent, IDialogConstants.OK_ID, "Save", true);
	        this.m_cancelButton = createButton(parent, IDialogConstants.CANCEL_ID, "Close", true);
	        this.m_saveButton.setEnabled(false);
	        this.m_cancelButton.setEnabled(false);
	  }
	  
	  @Override
	  protected void okPressed() {
		
		  if(m_isValueChanged) {
			  
			  m_isValueChanged = false;
			  Job ManufacturingAttributesOperationObj = new ServiceAttributesOperation("Saving Service Attributes...", this.m_SelectedItemsTable, this.m_selectedComponent, this.m_hshMapFormValues);
			  ManufacturingAttributesOperationObj.schedule();
			  ManufacturingAttributesOperationObj.addJobChangeListener(new IJobChangeListener() {

				  @Override
					public void aboutToRun(IJobChangeEvent paramIJobChangeEvent) {
						// TODO Auto-generated method stub
						
					}

					@Override
					public void awake(IJobChangeEvent paramIJobChangeEvent) {
						// TODO Auto-generated method stub
						
					}

					@Override
					public void done(final IJobChangeEvent paramIJobChangeEvent) {
						  Display.getDefault().asyncExec(new Runnable() {
						        public void run() {
						        	setReturnCode(0);
									close();
						        }
						    });
					}

					@Override
					public void running(IJobChangeEvent paramIJobChangeEvent) {
						// TODO Auto-generated method stub
						
					}

					@Override
					public void scheduled(IJobChangeEvent paramIJobChangeEvent) {
						// TODO Auto-generated method stub
						
					}

					@Override
					public void sleeping(IJobChangeEvent paramIJobChangeEvent) {
						// TODO Auto-generated method stub
						
					}
					  
				  });
		  } else {
			  super.okPressed();
		  }
	  }
	  
	  @Override
	  protected void handleShellCloseEvent() {
		  
		  if(m_isValueChanged) {
			  
			  if(!MessageDialog.openConfirm(this.m_SelectedItemsTable.getShell(), "Confirmation" , "Values are changed\nAre you sure to close without saving?")) {
					 
					 return;
			   }
		  }
		super.handleShellCloseEvent();  
	  }
	  
	  @Override
	  protected void cancelPressed() {
		  
		  if(m_isValueChanged) {
			  
			  if(!MessageDialog.openConfirm(this.m_SelectedItemsTable.getShell(), "Confirmation" , "Values are changed\nAre you sure to close without saving?")) {
					 
					 return;
			   }
		  }
		super.cancelPressed();  
	  }
	  
	  public void showErrorMessage(String p_strMessage) {
		  
		  final String strMessage = p_strMessage;
		  Display.getDefault().syncExec(new Runnable() {
		        public void run() {
		        	MessageDialog.open(MessageDialog.ERROR, m_SelectedItemsTable.getShell(), "Message", strMessage, MessageDialog.OK);
		        }
		 });
	  }
	  
	  public void setSelectedComponents(InterfaceAIFComponent[] p_selectedComponent) {
		  this.m_selectedComponent = p_selectedComponent;
	  }	  
	  
	  public void getStructureCodeDescriptor() {
		  
		  try {
			  TCComponentFormType  TCComponentFormTypeObj = (TCComponentFormType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6SrvAttrForm);
			  m_TCPropertySCDescriptorObj = TCComponentFormTypeObj.getPropDesc(Constants.BusinessObjects.Properties.strServiceItemType);
		  }  catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.getMessage());
		  }
	  }
	
      public void getEngineFamilyDescriptor() {
		  
		  try {
			  TCComponentFormType  TCComponentFormTypeObj = (TCComponentFormType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6SrvAttrForm);
			  m_TCPropertyEFDescriptorObj = TCComponentFormTypeObj.getPropDesc(Constants.BusinessObjects.Properties.strEngineFamily);
		  }  catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.getMessage());
		  }
	  }
      
       public void getTierTypeDescriptor() {
		  
		  try {
			  TCComponentFormType  TCComponentFormTypeObj = (TCComponentFormType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6SrvAttrForm);
			  m_TCPropertyTTDescriptorObj = TCComponentFormTypeObj.getPropDesc(Constants.BusinessObjects.Properties.strTierType);
		  }  catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.getMessage());
		  }
	  }
       
       public void getCompIDDescriptor() {

    	   try {
    		   TCComponentFormType  TCComponentFormTypeObj = (TCComponentFormType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6SrvAttrForm);
    		   m_TCPropertyCIDescriptorObj = TCComponentFormTypeObj.getPropDesc(Constants.BusinessObjects.Properties.strCompID);
    	   }  catch(Exception eObj) {

    		   MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.getMessage());
    	   }
       }
        
	  /*Set Serviceable*/
	  public void addSetServiceableDisplayer(TableItem p_TableItemObj, ServicesAttributesFormBean p_StockMaterialAttributesFormBean) {

		  try {

			  TableEditor SetPreferredTableEditor = new TableEditor(this.m_SelectedItemsTable);
			  SetPreferredTableEditor.grabHorizontal = true;
			  final iComboBox setPreferredCB = new iComboBox();

			  Composite setPreferredComposite = new Composite(this.m_SelectedItemsTable, SWT.EMBEDDED);
			  Frame setPreferredFrame = SWT_AWT.new_Frame(setPreferredComposite);
			  setPreferredFrame.add(setPreferredCB);
			  setPreferredComposite.pack();

			  setPreferredCB.setName(p_StockMaterialAttributesFormBean.getObjectString());
			  setPreferredCB.setText(p_StockMaterialAttributesFormBean.getServiceable());
			  setPreferredCB.setItems(Arrays.asList(new String[] { Constants.ManufacturingAttributesDialog.strTrueValue, Constants.ManufacturingAttributesDialog.strFalseValue}));
			  setPreferredCB.addActionListener(new ActionListener() {

				  @Override
				  public void actionPerformed(ActionEvent ActionEventObj) {

					  final ActionEvent ActionEventObjF = ActionEventObj;

					  Display.getDefault().asyncExec(new Runnable() {
						  public void run() {
							  try {

								  String strSetPreferredValue = ((iComboBox)ActionEventObjF.getSource()).getSelectedItem().toString();
								  m_isValueChanged = true;
								  m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource()).getName())).setModified(true);
								  m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setServiceable(strSetPreferredValue);
								  TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
								  tableItemObj.setText(2, strSetPreferredValue);

							  } catch(Exception tcObj) {
								  showErrorMessage(tcObj.getMessage());
							  }
						  }
					  });

				  }

			  });

			  SetPreferredTableEditor.setEditor(setPreferredComposite, p_TableItemObj, 2);
		  } catch(Exception eObj) {

			  showErrorMessage(eObj.getMessage());
		  }
	  }
	  
	  /*Set Repairable*/
	  
	  public void addSetRepairableDisplayer(TableItem p_TableItemObj, ServicesAttributesFormBean p_StockMaterialAttributesFormBean) {

		  try {

			  TableEditor SetRepairableTableEditor = new TableEditor(this.m_SelectedItemsTable);
			  SetRepairableTableEditor.grabHorizontal = true;
			  final iComboBox setRepairableCB = new iComboBox();
			  Composite setRepairableComposite = new Composite(this.m_SelectedItemsTable, SWT.EMBEDDED);
			  Frame setRepairableFrame = SWT_AWT.new_Frame(setRepairableComposite);
			  setRepairableFrame.add(setRepairableCB);
			  setRepairableComposite.pack();

			  setRepairableCB.setName(p_StockMaterialAttributesFormBean.getObjectString());
			  setRepairableCB.setText(p_StockMaterialAttributesFormBean.getRepairable());
			  setRepairableCB.setItems(Arrays.asList(new String[] { Constants.ManufacturingAttributesDialog.strTrueValue, Constants.ManufacturingAttributesDialog.strFalseValue}));
			  setRepairableCB.addActionListener(new ActionListener() {


				  @Override
				  public void actionPerformed(ActionEvent ActionEventObj) {

					  final ActionEvent ActionEventObjF = ActionEventObj;

					  Display.getDefault().asyncExec(new Runnable() {
						  public void run() {
							  try {

								  String strSetRepairableValue = ((iComboBox)ActionEventObjF.getSource()).getSelectedItem().toString();
								  m_isValueChanged = true;
								  m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource()).getName())).setModified(true);
								  m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setRepairable(strSetRepairableValue);
								  TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
								  tableItemObj.setText(4, strSetRepairableValue);

							  } catch(Exception tcObj) {
								  showErrorMessage(tcObj.getMessage());
							  }
						  }
					  });

				  }

			  });

			  SetRepairableTableEditor.setEditor(setRepairableComposite, p_TableItemObj, 4);
		  } catch(Exception eObj) {

			  showErrorMessage(eObj.getMessage());
		  }
	  }
	  
  /*Set Serialize*/
  
  public void addSetSerializeDisplayer(TableItem p_TableItemObj, ServicesAttributesFormBean p_StockMaterialAttributesFormBean) {

	  try {

		  TableEditor SetSerializeTableEditor = new TableEditor(this.m_SelectedItemsTable);
		  SetSerializeTableEditor.grabHorizontal = true;
		  final iComboBox setSerializeCB = new iComboBox();

		  Composite setSerializeComposite = new Composite(this.m_SelectedItemsTable, SWT.EMBEDDED);
		  Frame setSerializeFrame = SWT_AWT.new_Frame(setSerializeComposite);
		  setSerializeFrame.add(setSerializeCB);
		  setSerializeComposite.pack();

		  setSerializeCB.setName(p_StockMaterialAttributesFormBean.getObjectString());
		  setSerializeCB.setText(p_StockMaterialAttributesFormBean.getServiceable());
		  setSerializeCB.setItems(Arrays.asList(new String[] { Constants.ManufacturingAttributesDialog.strTrueValue, Constants.ManufacturingAttributesDialog.strFalseValue}));
		  setSerializeCB.addActionListener(new ActionListener() {

			  @Override
			  public void actionPerformed(ActionEvent ActionEventObj) {

				  final ActionEvent ActionEventObjF = ActionEventObj;

				  Display.getDefault().asyncExec(new Runnable() {
					  public void run() {
						  try {

							  String strSetSerializeValue = ((iComboBox)ActionEventObjF.getSource()).getSelectedItem().toString();
							  m_isValueChanged = true;
							  m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource()).getName())).setModified(true);
							  m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setSerialized(strSetSerializeValue);
							  TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
							  tableItemObj.setText(3, strSetSerializeValue);

						  } catch(Exception tcObj) {
							  showErrorMessage(tcObj.getMessage());
						  }
					  }
				  });

			  }

		  });

		  SetSerializeTableEditor.setEditor(setSerializeComposite, p_TableItemObj, 3);
	  } catch(Exception eObj) {

		  showErrorMessage(eObj.getMessage());
	  }
  }

  /* set Position Tracker*/
  public void addSetPositionTrackDisplayer(TableItem p_TableItemObj, ServicesAttributesFormBean p_StockMaterialAttributesFormBean) {

	  try {

		  TableEditor SetPositionTrackTableEditor = new TableEditor(this.m_SelectedItemsTable);
		  SetPositionTrackTableEditor.grabHorizontal = true;
		  final iComboBox setPositionTrackCB = new iComboBox();

		  Composite setPositionTrackComposite = new Composite(this.m_SelectedItemsTable, SWT.EMBEDDED);
		  Frame setPositionTrackFrame = SWT_AWT.new_Frame(setPositionTrackComposite);
		  setPositionTrackFrame.add(setPositionTrackCB);
		  setPositionTrackComposite.pack();

		  setPositionTrackCB.setName(p_StockMaterialAttributesFormBean.getObjectString());
		  setPositionTrackCB.setText(p_StockMaterialAttributesFormBean.getServiceable());
		  setPositionTrackCB.setItems(Arrays.asList(new String[] { Constants.ManufacturingAttributesDialog.strTrueValue, Constants.ManufacturingAttributesDialog.strFalseValue}));
		  setPositionTrackCB.addActionListener(new ActionListener() {

			  @Override
			  public void actionPerformed(ActionEvent ActionEventObj) {

				  final ActionEvent ActionEventObjF = ActionEventObj;

				  Display.getDefault().asyncExec(new Runnable() {
					  public void run() {
						  try {

							  String strSetPositionTrackValue = ((iComboBox)ActionEventObjF.getSource()).getSelectedItem().toString();
							  m_isValueChanged = true;
							  m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource()).getName())).setModified(true);
							  m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setPositionTracked(strSetPositionTrackValue);
							  TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
							  tableItemObj.setText(5, strSetPositionTrackValue);

						  } catch(Exception tcObj) {
							  showErrorMessage(tcObj.getMessage());
						  }
					  }
				  });

			  }

		  });

		  SetPositionTrackTableEditor.setEditor(setPositionTrackComposite, p_TableItemObj, 5);
	  } catch(Exception eObj) {

		  showErrorMessage(eObj.getMessage());
	  }
  }
     /*set Service Item type*/
 public void addServiceItemTypeLOVDisplayer(TableItem p_TableItemObj, ServicesAttributesFormBean p_StockMaterialAttributesFormBean) {

	 try {

		 if(null == this.m_TCPropertySCDescriptorObj) {
			 this.getStructureCodeDescriptor();
		 }

		 TableEditor StructureCodeTableEditor = new TableEditor(this.m_SelectedItemsTable);
		 StructureCodeTableEditor.grabHorizontal = true;


		 LOVDisplayer LOVStructureCodeDisplayerObj = new LOVDisplayer(this.m_SelectedItemsTable, 0);	
		 LOVStructureCodeDisplayerObj.initialize(null, this.m_TCPropertySCDescriptorObj, null);
		 LOVStructureCodeDisplayerObj.setSelectedValue(p_StockMaterialAttributesFormBean.getSrvItemType());

		 LOVStructureCodeDisplayerObj.addPropertyChangeListener(new IPropertyChangeListener() {

			 public void propertyChange(PropertyChangeEvent PropertyChangeEventObj) {

				 final PropertyChangeEvent fPropertyChangeEventObj = PropertyChangeEventObj;

				 Display.getDefault().asyncExec(new Runnable() {
					 public void run() {
						 try {
							 if(null != fPropertyChangeEventObj.getNewValue()) {

								 final TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
								 final ServicesAttributesFormBean ServicesAttributesFormBeanObj = m_hshMapFormValues.get(tableItemObj.getText(0));
								 m_isValueChanged = true;
								 String strMakeBuyValue = ((LOVPropertyValue)fPropertyChangeEventObj.getNewValue()).getDisplayableValue();
								 ServicesAttributesFormBeanObj.setSrvItemType(strMakeBuyValue);
								 ServicesAttributesFormBeanObj.setModified(true);
								 tableItemObj.setText(6, strMakeBuyValue);

							 }

						 } catch(Exception tcObj) {
							 showErrorMessage(tcObj.getMessage());
						 }
					 }
				 });
			 }
		 });

		 StructureCodeTableEditor.setEditor(LOVStructureCodeDisplayerObj, p_TableItemObj, 6);
	 } catch(Exception eObj) {

		 showErrorMessage(eObj.getMessage());
	 }
 }

	 /*Set Engine Family*/
	 public void addServiceEngineFamilyLOVDisplayer(TableItem p_TableItemObj, ServicesAttributesFormBean p_StockMaterialAttributesFormBean) {
		  
		  try {
			  
			  if(null == this.m_TCPropertyEFDescriptorObj) {
		    	  this.getEngineFamilyDescriptor();
		      }
			  
			  TableEditor StructureCodeTableEditor = new TableEditor(this.m_SelectedItemsTable);
			  StructureCodeTableEditor.grabHorizontal = true;
		      
			  
			  LOVDisplayer LOVStructureCodeDisplayerObj = new LOVDisplayer(this.m_SelectedItemsTable, 0);	
			  LOVStructureCodeDisplayerObj.initialize(null, this.m_TCPropertyEFDescriptorObj, null);
			  LOVStructureCodeDisplayerObj.setSelectedValue(p_StockMaterialAttributesFormBean.getEngineFamily());
			  
			  LOVStructureCodeDisplayerObj.addPropertyChangeListener(new IPropertyChangeListener() {
	
					public void propertyChange(PropertyChangeEvent PropertyChangeEventObj) {
						 
						final PropertyChangeEvent fPropertyChangeEventObj = PropertyChangeEventObj;
						
						 Display.getDefault().asyncExec(new Runnable() {
						        public void run() {
									try {
										if(null != fPropertyChangeEventObj.getNewValue()) {
											
											final TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
											final ServicesAttributesFormBean ServicesAttributesFormBeanObj = m_hshMapFormValues.get(tableItemObj.getText(0));
											m_isValueChanged = true;
											String strMakeBuyValue = ((LOVPropertyValue)fPropertyChangeEventObj.getNewValue()).getDisplayableValue();
											ServicesAttributesFormBeanObj.setEngineFamily(strMakeBuyValue);
											ServicesAttributesFormBeanObj.setModified(true);
											tableItemObj.setText(1, strMakeBuyValue);
											
										}
										   
									} catch(Exception tcObj) {
										showErrorMessage(tcObj.getMessage());
									}
						        }
						 });
					}
			  });
		      
			  StructureCodeTableEditor.setEditor(LOVStructureCodeDisplayerObj, p_TableItemObj, 1);
		  } catch(Exception eObj) {
			  
			  showErrorMessage(eObj.getMessage());
		  }
	  }
	 /*Set Tier Type*/
	 public void addServiceTierTypeLOVDisplayer(TableItem p_TableItemObj, ServicesAttributesFormBean p_StockMaterialAttributesFormBean) {

		 try {

			 if(null == this.m_TCPropertyTTDescriptorObj) {
				 this.getTierTypeDescriptor();
			 }

			 TableEditor StructureCodeTableEditor = new TableEditor(this.m_SelectedItemsTable);
			 StructureCodeTableEditor.grabHorizontal = true;


			 LOVDisplayer LOVStructureCodeDisplayerObj = new LOVDisplayer(this.m_SelectedItemsTable, 0);	
			 LOVStructureCodeDisplayerObj.initialize(null, this.m_TCPropertyTTDescriptorObj, null);
			 LOVStructureCodeDisplayerObj.setSelectedValue(p_StockMaterialAttributesFormBean.getTierType());

			 LOVStructureCodeDisplayerObj.addPropertyChangeListener(new IPropertyChangeListener() {

				 public void propertyChange(PropertyChangeEvent PropertyChangeEventObj) {

					 final PropertyChangeEvent fPropertyChangeEventObj = PropertyChangeEventObj;

					 Display.getDefault().asyncExec(new Runnable() {
						 public void run() {
							 try {
								 if(null != fPropertyChangeEventObj.getNewValue()) {

									 final TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
									 final ServicesAttributesFormBean ServicesAttributesFormBeanObj = m_hshMapFormValues.get(tableItemObj.getText(0));
									 m_isValueChanged = true;
									 String strMakeBuyValue = ((LOVPropertyValue)fPropertyChangeEventObj.getNewValue()).getDisplayableValue();
									 ServicesAttributesFormBeanObj.setTierType(strMakeBuyValue);
									 ServicesAttributesFormBeanObj.setModified(true);
									 tableItemObj.setText(7, strMakeBuyValue);

								 }

							 } catch(Exception tcObj) {
								 showErrorMessage(tcObj.getMessage());
							 }
						 }
					 });
				 }
			 });

			 StructureCodeTableEditor.setEditor(LOVStructureCodeDisplayerObj, p_TableItemObj, 7);
		 } catch(Exception eObj) {

			 showErrorMessage(eObj.getMessage());
		 }
	 }
	 /*Set Component ID*/
	 public void addServiceCompIDLOVDisplayer(TableItem p_TableItemObj, ServicesAttributesFormBean p_StockMaterialAttributesFormBean) {

		 try {

			 if(null == this.m_TCPropertyCIDescriptorObj) {
				 this.getCompIDDescriptor();
			 }

			 TableEditor StructureCodeTableEditor = new TableEditor(this.m_SelectedItemsTable);
			 StructureCodeTableEditor.grabHorizontal = true;


			 LOVDisplayer LOVStructureCodeDisplayerObj = new LOVDisplayer(this.m_SelectedItemsTable, 0);	
			 LOVStructureCodeDisplayerObj.initialize(null, this.m_TCPropertyCIDescriptorObj, null);
			 LOVStructureCodeDisplayerObj.setSelectedValue(p_StockMaterialAttributesFormBean.getCompID());

			 LOVStructureCodeDisplayerObj.addPropertyChangeListener(new IPropertyChangeListener() {

				 public void propertyChange(PropertyChangeEvent PropertyChangeEventObj) {

					 final PropertyChangeEvent fPropertyChangeEventObj = PropertyChangeEventObj;

					 Display.getDefault().asyncExec(new Runnable() {
						 public void run() {
							 try {
								 if(null != fPropertyChangeEventObj.getNewValue()) {

									 final TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
									 final ServicesAttributesFormBean ServicesAttributesFormBeanObj = m_hshMapFormValues.get(tableItemObj.getText(0));
									 m_isValueChanged = true;
									 String strMakeBuyValue = ((LOVPropertyValue)fPropertyChangeEventObj.getNewValue()).getDisplayableValue();
									 ServicesAttributesFormBeanObj.setCompID(strMakeBuyValue);
									 ServicesAttributesFormBeanObj.setModified(true);
									 tableItemObj.setText(8, strMakeBuyValue);

								 }

							 } catch(Exception tcObj) {
								 showErrorMessage(tcObj.getMessage());
							 }
						 }
					 });
				 }
			 });

			 StructureCodeTableEditor.setEditor(LOVStructureCodeDisplayerObj, p_TableItemObj, 8);
		 } catch(Exception eObj) {

			 showErrorMessage(eObj.getMessage());
		 }
	 }

	 public void init() {

		 try {

			 Job ManufacturingAttributesOperationObj = new  ServiceAttributesOperation("Fetching Services Attributes...",this.m_SelectedItemsTable, this.m_selectedComponent);
			 ManufacturingAttributesOperationObj.schedule();
			 ManufacturingAttributesOperationObj.addJobChangeListener(new IJobChangeListener() {

				 @Override
				 public void aboutToRun(IJobChangeEvent paramIJobChangeEvent) {
					 // TODO Auto-generated method stub

				 }

				 @Override
				 public void awake(IJobChangeEvent paramIJobChangeEvent) {
					 // TODO Auto-generated method stub

				 }

				 @Override
				 public void done(final IJobChangeEvent paramIJobChangeEvent) {

					 Display.getDefault().asyncExec(new Runnable() {
						 public void run() {

							 m_saveButton.setEnabled(true);
							 m_cancelButton.setEnabled(true);
							 m_canClosewindow = true;
							 m_hshMapFormValues = ((ServiceAttributesOperation)paramIJobChangeEvent.getJob()).getSelectedComponentsData();

							 for(ServicesAttributesFormBean ServicesAttributesFormBeanObj : m_hshMapFormValues.values()) {
  
								 TableItem TableItemObj = new TableItem(m_SelectedItemsTable, SWT.NONE);

								 InputStream imageStream = getClass().getClassLoader().getResourceAsStream(Constants.ManufacturingAttributesDialog.strIconsPrefix + ServicesAttributesFormBeanObj.getTCComponentItem().getType() + Constants.ManufacturingAttributesDialog.strIconsSuffix);
								 if(null != imageStream) {
									 Image iconImage = new Image(Display.getDefault(), imageStream);
									 if(null != iconImage) {
										 TableItemObj.setImage(0, iconImage);
									 }
								 }

								 TableItemObj.setText(0, ServicesAttributesFormBeanObj.getObjectString());
								 TableItemObj.setText(1, ServicesAttributesFormBeanObj.getEngineFamily());
								 TableItemObj.setText(2, ServicesAttributesFormBeanObj.getServiceable());
								 TableItemObj.setText(3, ServicesAttributesFormBeanObj.getSerialized());
								 TableItemObj.setText(4, ServicesAttributesFormBeanObj.getRepairable());
								 TableItemObj.setText(5, ServicesAttributesFormBeanObj.getPositionTracked());
								 TableItemObj.setText(6, ServicesAttributesFormBeanObj.getSrvItemType());
								 TableItemObj.setText(7, ServicesAttributesFormBeanObj.getTierType());
								 TableItemObj.setText(8, ServicesAttributesFormBeanObj.getCompID());
							 }
						 }
					 });
				 }

				 @Override
				 public void running(IJobChangeEvent paramIJobChangeEvent) {
					 // TODO Auto-generated method stub

				 }

				 @Override
				 public void scheduled(IJobChangeEvent paramIJobChangeEvent) {
					 // TODO Auto-generated method stub

				 }

				 @Override
				 public void sleeping(IJobChangeEvent paramIJobChangeEvent) {
					 // TODO Auto-generated method stub

				 }

			 });

		 } catch(Exception eObj) {

			 MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.getMessage());
		 }

	 }
}

