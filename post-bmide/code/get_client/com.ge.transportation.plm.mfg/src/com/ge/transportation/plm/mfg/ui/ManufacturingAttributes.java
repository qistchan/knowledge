package com.ge.transportation.plm.mfg.ui;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;

import javax.swing.ImageIcon;

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
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Spinner;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;

import com.ge.transportation.plm.mfg.beans.ManufacturingAttributesFormBean;
import com.ge.transportation.plm.mfg.beans.StockMaterialAttributesFormBean;
import com.ge.transportation.plm.mfg.constants.Constants;
import com.ge.transportation.plm.mfg.operations.ManufacturingAttributesOperation;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.common.lov.common.LOVPropertyValue;
import com.teamcenter.rac.common.lov.view.controls.LOVDisplayer;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentFormType;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentProject;
import com.teamcenter.rac.kernel.TCPropertyDescriptor;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.util.combobox.iComboBox;
import com.teamcenter.services.loose.core.DataManagementService;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.Property;

public class ManufacturingAttributes extends TitleAreaDialog{
	
	 private Button m_saveButton = null;
	 private Button m_cancelButton = null;
	 private Button m_autoPopulateCheckBox = null;
	 private boolean m_isValueChanged = false;
	 private boolean m_isBuyAutoPopulated = false;
	 private boolean m_canClosewindow = false;
	 private Table m_SelectedItemsTable = null;
	 private TCPropertyDescriptor m_TCPropertyMBDescriptorObj = null;
	 private TCPropertyDescriptor m_TCPropertyPCDescriptorObj = null;
	 private TCPropertyDescriptor m_TCPropertySCDescriptorObj = null;
	 private String m_strCurrentProject = Constants.General.EMPTY_STRING_VALUE_C;
	 private InterfaceAIFComponent[] m_selectedComponent = null;
	 
	 private Map<String, ManufacturingAttributesFormBean> m_hshMapFormValues = Collections.synchronizedMap(new LinkedHashMap<String, ManufacturingAttributesFormBean>());
	 
	 public ManufacturingAttributes(Shell p_parentShell) {
		 
		 super(p_parentShell);
		 this.getCurrentProject();
	 }
	 
	 @Override
	  public void create() {
	    super.create();
	    this.getShell().setText(this.m_strCurrentProject + Constants.ManufacturingAttributesDialog.strTitle);
	    setTitle(this.m_strCurrentProject + Constants.ManufacturingAttributesDialog.strTitle);
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
	    
	    TableColumn makeBuyTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
	    makeBuyTableColumn.pack();
	    makeBuyTableColumn.setText(this.m_strCurrentProject + Constants.ManufacturingAttributesDialog.strColumnMakeBuy);
	    
	    TableColumn stockMaterialTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
	    stockMaterialTableColumn.pack();
	    stockMaterialTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnStockMaterials);
	    
	    TableColumn stockMaterialQuantityTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
	    stockMaterialQuantityTableColumn.pack();
	    stockMaterialQuantityTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnStockMaterialQuantity);
	    
	    TableColumn partPlanningCodeTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
	    partPlanningCodeTableColumn.pack();
	    partPlanningCodeTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnPlanningCode);
	    
	    TableColumn structureCodeTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
	    structureCodeTableColumn.pack();
	    structureCodeTableColumn.setText(Constants.ManufacturingAttributesDialog.strColumnStructureCode);
	  
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

	                    	if(icol == Constants.ManufacturingAttributesDialog.MAKE_BUY_COLUMN) {
	                    		
	                    		addMakeBuyLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
	                    	} else if(icol == Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN) {
	                    		
	                    		addStockMaterialLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
	                    	} else if(icol == Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN) {
	                    	
	                    		addStockMaterialQuantitySpinner(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
	                    	} else if(icol == Constants.ManufacturingAttributesDialog.PLANNING_CODE_COLUMN) {
	                    		
	                    		addPlanningCodeLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
	                    	} else if(icol == Constants.ManufacturingAttributesDialog.STRUCTURE_CODE_COLUMN) {
	                    		
	                    		addStructureCodeLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
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
			return new Point(850, 500);
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
	  
	  protected Control createButtonBar(final Composite parent) {
	      
	      final Composite buttonBar = new Composite(parent, SWT.NONE);

	      final GridLayout layout = new GridLayout();
	      layout.numColumns = 2;
	      layout.makeColumnsEqualWidth = false;
	      layout.horizontalSpacing = convertHorizontalDLUsToPixels(IDialogConstants.HORIZONTAL_SPACING);
	      buttonBar.setLayout(layout);

	      final GridData data = new GridData(SWT.FILL, SWT.BOTTOM, true, false);
	      data.grabExcessHorizontalSpace = true;
	      data.grabExcessVerticalSpace = false;
	      buttonBar.setLayoutData(data);
	      buttonBar.setFont(parent.getFont());
	      
	      this.m_autoPopulateCheckBox =  new Button(buttonBar, SWT.CHECK);
	      this.m_autoPopulateCheckBox.setText("Set Manufacturing Buy for Engineering Buy Parts");

	      final GridData leftButtonBarData = new GridData(SWT.LEFT, SWT.CENTER, true, true);
	      leftButtonBarData.grabExcessHorizontalSpace = true;
	      leftButtonBarData.horizontalIndent = convertHorizontalDLUsToPixels(IDialogConstants.HORIZONTAL_MARGIN);
	      this.m_autoPopulateCheckBox.setLayoutData(leftButtonBarData);

	      final Control buttonControl = super.createButtonBar(buttonBar);
	      buttonControl.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, true, false));
	      
	      this.m_autoPopulateCheckBox.addSelectionListener(new SelectionAdapter() {

	          @Override
	          public void widgetSelected(final SelectionEvent SelectionEventObj) {
	              
                     Display.getDefault().asyncExec(new Runnable() {
                         public void run() {
                          
                          int inx = 0;
                          for(ManufacturingAttributesFormBean ManufacturingAttributesFormBeanObj : m_hshMapFormValues.values()) {
                               
                              TableItem TableItemObj = m_SelectedItemsTable.getItem(inx);
                              
                              if((Constants.ManufacturingAttributesDialog.strBuyValue).equals(ManufacturingAttributesFormBeanObj.getEngMakeBuy())) {
                                  
                                  if(((Button)SelectionEventObj.widget).getSelection()) {
                                      if((Constants.General.EMPTY_STRING_VALUE_C).equals(ManufacturingAttributesFormBeanObj.getMakeBuy())) {
                                          
                                          m_isBuyAutoPopulated = true;
                                          m_hshMapFormValues.get(TableItemObj.getText(0)).setModified(true);
                                          m_hshMapFormValues.get(TableItemObj.getText(0)).setEngMakeBuySet(true);
                                          m_hshMapFormValues.get(TableItemObj.getText(0)).setMakeBuy(ManufacturingAttributesFormBeanObj.getEngMakeBuy());
                                          TableItemObj.setText(Constants.ManufacturingAttributesDialog.MAKE_BUY_COLUMN, ManufacturingAttributesFormBeanObj.getMakeBuy());
                                      }
                                  } else {
                                      
                                      if(ManufacturingAttributesFormBeanObj.getEngMakeBuySet()) {
                                          
                                          m_isBuyAutoPopulated = false;
                                          m_hshMapFormValues.get(TableItemObj.getText(0)).setModified(false);
                                          m_hshMapFormValues.get(TableItemObj.getText(0)).setEngMakeBuySet(false);
                                          m_hshMapFormValues.get(TableItemObj.getText(0)).setMakeBuy(Constants.General.EMPTY_STRING_VALUE_C);
                                          TableItemObj.setText(Constants.ManufacturingAttributesDialog.MAKE_BUY_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
                                      }
                                  }                                      
                              }
                              
                              inx++;
                          }
                      }
                 });
	          }
	      });

	      return buttonBar;
	  }
	  
	  @Override
	  protected void okPressed() {
		
		  if(m_isValueChanged || m_isBuyAutoPopulated) {
			  
			  m_isValueChanged = false;
			  m_isBuyAutoPopulated = false;
			  Job ManufacturingAttributesOperationObj = new ManufacturingAttributesOperation("Saving Manufacturing Attributes...", this.m_strCurrentProject, this.m_SelectedItemsTable, this.m_selectedComponent, this.m_hshMapFormValues);
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
		  
		  if(m_isBuyAutoPopulated) {
		      
		      if(!MessageDialog.openConfirm(this.m_SelectedItemsTable.getShell(), "Confirmation" , "Manufacturing Buy is auto populated for Engineering Buy parts\nAre you sure to close without saving?")) {
                  
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
		  
		  if(m_isBuyAutoPopulated) {
              
              if(!MessageDialog.openConfirm(this.m_SelectedItemsTable.getShell(), "Confirmation" , "Manufacturing Buy is auto populated for Engineering Buy parts\nAre you sure to close without saving?")) {
                  
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
	  
	  public String getCurrentProject() {
		  
		  String strCurrentProject = Constants.General.EMPTY_STRING_VALUE_C;
		  
		  try {
			  TCComponentProject tcCurrentProject = ((TCSession)AIFUtility.getDefaultSession()).getCurrentProject();
			  if(null != tcCurrentProject) {
				  
				  this.m_strCurrentProject = tcCurrentProject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strProjectID);
			  }
		  } catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.toString());
		  }
		  
		  return strCurrentProject;
	  }
	  
	  public void setTableImage(TableItem p_TableItemObj, String p_strObjectType) {
		  
		  InputStream imageStream = getClass().getClassLoader().getResourceAsStream(Constants.ManufacturingAttributesDialog.strIconsPrefix + p_strObjectType + Constants.ManufacturingAttributesDialog.strIconsSuffix);
			if(null != imageStream) {
			  Image iconImage = new Image(Display.getDefault(), imageStream);
			  if(null != iconImage) {
				  
				  if((Constants.BusinessObjects.strGET6StockMtrl).equals(p_strObjectType)) {
					  p_TableItemObj.setImage(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, iconImage);
				  } else {
					  p_TableItemObj.setImage(0, iconImage);
				  }
		      }
		  }
	  }
	  
	  
	  public void getMakeBuyDescriptor() {
		  
		  try {
			  TCComponentFormType  TCComponentFormTypeObj = (TCComponentFormType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6MfgOrgAttrForm);
			  m_TCPropertyMBDescriptorObj = TCComponentFormTypeObj.getPropDesc(Constants.BusinessObjects.Properties.strget6MakeBuy);
		  }  catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.toString());
		  }
	  }
	  
	  public void getPlanningCodeDescriptor() {
		  
		  try {
			  TCComponentFormType  TCComponentFormTypeObj = (TCComponentFormType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6MfgOrgAttrForm);
			  m_TCPropertyPCDescriptorObj = TCComponentFormTypeObj.getPropDesc(Constants.BusinessObjects.Properties.strget6PlanningCode);
		  }  catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.toString());
		  }
	  }
	  
	  public void getStructureCodeDescriptor() {
		  
		  try {
			  TCComponentFormType  TCComponentFormTypeObj = (TCComponentFormType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6MfgOrgAttrForm);
			  m_TCPropertySCDescriptorObj = TCComponentFormTypeObj.getPropDesc(Constants.BusinessObjects.Properties.strget6StructureCode);
		  }  catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.toString());
		  }
	  }
	  
	  public void addMakeBuyLOVDisplayer(TableItem p_TableItemObj, ManufacturingAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
		  
		  try {
			  			  
			  TableEditor MakeBuyTableEditor = new TableEditor(this.m_SelectedItemsTable);
		      MakeBuyTableEditor.grabHorizontal = true;
		      
		      if(null == this.m_TCPropertyMBDescriptorObj) {
		    	  this.getMakeBuyDescriptor();
		      }
		      
		     LOVDisplayer LOVMakeBuyDisplayerObj = new LOVDisplayer(this.m_SelectedItemsTable, 0);
		     LOVMakeBuyDisplayerObj.initialize(null, this.m_TCPropertyMBDescriptorObj, null);
			 LOVMakeBuyDisplayerObj.setSelectedValue(p_ManufacturingAttributesFormBeanObj.getMakeBuy());
			 
			  LOVMakeBuyDisplayerObj.addPropertyChangeListener(new IPropertyChangeListener() {

				@Override
				public void propertyChange(PropertyChangeEvent PropertyChangeEventObj) {
					
					final PropertyChangeEvent fPropertyChangeEventObj = PropertyChangeEventObj;
					
					 Display.getDefault().asyncExec(new Runnable() {
					        public void run() {
								try {
									if(null != fPropertyChangeEventObj.getNewValue()) {
										
										final TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
										String strMakeBuyValue = ((LOVPropertyValue)fPropertyChangeEventObj.getNewValue()).getDisplayableValue();
										final ManufacturingAttributesFormBean ManufacturingAttributesFormBeanObj = m_hshMapFormValues.get(tableItemObj.getText(0));
										
										
										if((null != ManufacturingAttributesFormBeanObj.getItemPublishDate()) || (null != ManufacturingAttributesFormBeanObj.getBOMPublishDate())) {
											  if(!MessageDialog.openConfirm(m_SelectedItemsTable.getShell(), "Confirmation" , "Item is already sent to Oracle\nDo you really want to change?")) {
												 
												 return;
											  }
										}
										
										 if((Constants.ManufacturingAttributesDialog.strMakeValue).equals(strMakeBuyValue)) {
												
											 if((Constants.ManufacturingAttributesDialog.strBuyValue).equals(ManufacturingAttributesFormBeanObj.getEngMakeBuy())) {
									    	 	 
												 showErrorMessage("Engineering Make/Buy is Buy\nPlease select Buy.");
												 return;
											 }
									     }
										 
										 
										 if((Constants.ManufacturingAttributesDialog.strBuyValue).equals(strMakeBuyValue)) {
											 
											 if(!(Constants.General.EMPTY_STRING_VALUE_C).equals(ManufacturingAttributesFormBeanObj.getStockMaterial())) {
												 
												 if(!MessageDialog.openConfirm(m_SelectedItemsTable.getShell(), "Confirmation" , "Changing to Buy will clear the following values \n\n     -Stock Material\n     -Stock Material Quantity")) {
													 
													 return;
												  } else {
													  
													  tableItemObj.setImage(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, null);
													  tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
													  m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterial(Constants.General.EMPTY_STRING_VALUE_C);
													  m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterialItem(null);
													  
													  tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
													  m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterialQuantity(Double.parseDouble(Constants.General.ZERO_STRING_VALUE_C));
												  }
											 }
										 }
										
										m_isValueChanged = true;
										ManufacturingAttributesFormBeanObj.setMakeBuy(strMakeBuyValue);
										ManufacturingAttributesFormBeanObj.setModified(true);
										
										if((Constants.ManufacturingAttributesDialog.strNoneValue).equals(strMakeBuyValue)) {
											
											tableItemObj.setImage(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, null);
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.MAKE_BUY_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.PLANNING_CODE_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.STRUCTURE_CODE_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
											
											m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStructureCode(Constants.ManufacturingAttributesDialog.iClearIntProperty);
											m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterialItem(null);
											m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setMakeBuy(Constants.General.EMPTY_STRING_VALUE_C);
											m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setPlanningCode(Constants.General.EMPTY_STRING_VALUE_C);
											m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterial(Constants.General.EMPTY_STRING_VALUE_C);
											m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterialQuantity(Double.parseDouble(Constants.General.ZERO_STRING_VALUE_C));
											 
											return;
										} 
										
										tableItemObj.setText(Constants.ManufacturingAttributesDialog.MAKE_BUY_COLUMN, strMakeBuyValue);
										
										if((ManufacturingAttributesFormBeanObj.getStockMaterials().size() == 0) && (!(Constants.BusinessObjects.strGET6MfgPart).equals(ManufacturingAttributesFormBeanObj.getTCComponentItem().getType()))) {
											
											  Display.getDefault().asyncExec(new Runnable() {
											        public void run() {
											        	
											        	TreeMap<String, StockMaterialAttributesFormBean> treeStockMaterials = getStockMaterial(ManufacturingAttributesFormBeanObj.getTCComponentItem());
											        	if(treeStockMaterials.size() != 0) {
											        		ManufacturingAttributesFormBeanObj.setStockMaterials(treeStockMaterials);
											        		m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterials(treeStockMaterials);
											        		
											        		for(StockMaterialAttributesFormBean StockMaterialAttributesFormBeanObj : ManufacturingAttributesFormBeanObj.getStockMaterials().values()) {
																
																if((StockMaterialAttributesFormBeanObj.getPreferred().equalsIgnoreCase(Constants.StockMaterialAttributesDialog.strTrueValue)) && ((Constants.ManufacturingAttributesDialog.strMakeValue).equals(ManufacturingAttributesFormBeanObj.getMakeBuy()))) {
																	
																	tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, StockMaterialAttributesFormBeanObj.getObjectString());
																	m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterial(StockMaterialAttributesFormBeanObj.getObjectString());
																	m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterialItem(StockMaterialAttributesFormBeanObj.getTCComponentItem());
																	setTableImage(tableItemObj, Constants.BusinessObjects.strGET6StockMtrl);
																	break;
																}
															}
											        	}
											        }
											  });
										 } else {
											 
											 for(StockMaterialAttributesFormBean StockMaterialAttributesFormBeanObj : ManufacturingAttributesFormBeanObj.getStockMaterials().values()) {
													
												if((StockMaterialAttributesFormBeanObj.getPreferred().equalsIgnoreCase(Constants.StockMaterialAttributesDialog.strTrueValue)) && ((Constants.ManufacturingAttributesDialog.strMakeValue).equals(ManufacturingAttributesFormBeanObj.getMakeBuy()))) {
													
													tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, StockMaterialAttributesFormBeanObj.getObjectString());
													m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterial(StockMaterialAttributesFormBeanObj.getObjectString());
													m_hshMapFormValues.get(ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterialItem(StockMaterialAttributesFormBeanObj.getTCComponentItem());
													setTableImage(tableItemObj, Constants.BusinessObjects.strGET6StockMtrl);
													break;
												}
											}
										}
									}
									   
								} catch(Exception tcObj) {
									
									showErrorMessage(tcObj.toString());
								}
					        }
					 });
				}
			  });
		      
		      MakeBuyTableEditor.setEditor(LOVMakeBuyDisplayerObj, p_TableItemObj, Constants.ManufacturingAttributesDialog.MAKE_BUY_COLUMN);
		  } catch(Exception eObj) {
			  
			  showErrorMessage(eObj.toString());
		  }
	  }
	  
	  public void addPlanningCodeLOVDisplayer(TableItem p_TableItemObj, ManufacturingAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
		  
		  try {
			  

			  TableEditor PlanningCodeTableEditor = new TableEditor(this.m_SelectedItemsTable);
			  PlanningCodeTableEditor.grabHorizontal = true;
		      
			  if(null == this.m_TCPropertyPCDescriptorObj) {
		    	  this.getPlanningCodeDescriptor();
		      }
		   
			  LOVDisplayer LOVPlanningCodeDisplayerObj = new LOVDisplayer(this.m_SelectedItemsTable, 0);
			  LOVPlanningCodeDisplayerObj.initialize(p_ManufacturingAttributesFormBeanObj.getTCComponentForm(), this.m_TCPropertyPCDescriptorObj, null);
			  LOVPlanningCodeDisplayerObj.setSelectedValue(p_ManufacturingAttributesFormBeanObj.getPlanningCode());
			  
			  LOVPlanningCodeDisplayerObj.addPropertyChangeListener(new IPropertyChangeListener() {
	
					public void propertyChange(PropertyChangeEvent PropertyChangeEventObj) {
						 
						final PropertyChangeEvent fPropertyChangeEventObj = PropertyChangeEventObj;
						
						 Display.getDefault().asyncExec(new Runnable() {
						        public void run() {
									try {
										if(null != fPropertyChangeEventObj.getNewValue()) {
											
											String strRoleName = ((TCSession)AIFUtility.getDefaultSession()).getRole().getRoleName();
											if(!(Constants.Role.strMfgProcessPlanner).equals(strRoleName)) {
												
												showErrorMessage("Invalid Group/Role, Allowed Roles are \n\n	-Mfg Process Planner");
												return;
											}
											m_isValueChanged = true;
											TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
											String strPlanningCodeValue = ((LOVPropertyValue)fPropertyChangeEventObj.getNewValue()).getDisplayableValue();
											m_hshMapFormValues.get(tableItemObj.getText(0)).setPlanningCode(strPlanningCodeValue);
											m_hshMapFormValues.get(tableItemObj.getText(0)).setModified(true);
											
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.PLANNING_CODE_COLUMN, strPlanningCodeValue);
										}
										   
									} catch(Exception tcObj) {
										showErrorMessage(tcObj.toString());
									}
						        }
						 });
					}
			  });
		      
		      PlanningCodeTableEditor.setEditor(LOVPlanningCodeDisplayerObj, p_TableItemObj, Constants.ManufacturingAttributesDialog.PLANNING_CODE_COLUMN);
		  } catch(Exception eObj) {
			  
			  showErrorMessage(eObj.toString());
		  }
	  }
	  
	  public TreeMap<String, StockMaterialAttributesFormBean> getStockMaterial(TCComponentItem p_tcCurrentComponent) {
		  
		  ArrayList<ModelObject> arrOrgPropertiesForm = new ArrayList<ModelObject>();
		  TreeMap<String, StockMaterialAttributesFormBean> treeStockMaterials = new TreeMap<String, StockMaterialAttributesFormBean>();
		  DataManagementService DataManagementServiceObj = DataManagementService.getService(((TCSession)AIFUtility.getDefaultSession()).getSoaConnection());
		  
		  try {
			  
			  if(((Constants.BusinessObjects.strGET6ElectPart).equals(p_tcCurrentComponent.getType()) || (Constants.BusinessObjects.strGET6MechPart).equals(p_tcCurrentComponent.getType()) || (Constants.BusinessObjects.strGET6SoftwarePart).equals(p_tcCurrentComponent.getType()))) {
	    			
				  DataManagementServiceObj.getProperties(new ModelObject[] { p_tcCurrentComponent }, new String[] { Constants.BusinessObjects.Properties.strObjectString, Constants.BusinessObjects.strGET6MadeFromMatl });
				  Property propertyMaterialObj = p_tcCurrentComponent.getPropertyObject(Constants.BusinessObjects.strGET6MadeFromMatl);
				  
				  DataManagementServiceObj.getProperties(propertyMaterialObj.getModelObjectArrayValue(), new String[] { Constants.BusinessObjects.strGET6HasStockMatl });
				  
				  Property propertyStockMaterialObj = null;
				  for(int inx = 0; inx < propertyMaterialObj.getModelObjectArrayValue().length; inx++) {
					  
					  propertyStockMaterialObj = propertyMaterialObj.getModelObjectArrayValue()[inx].getPropertyObject(Constants.BusinessObjects.strGET6HasStockMatl);
					  DataManagementServiceObj.getProperties(propertyStockMaterialObj.getModelObjectArrayValue(), new String[] { Constants.BusinessObjects.Properties.strObjectString, Constants.BusinessObjects.strGET6StockHasOrgPropsAttri });
					  for(int jnx = 0; jnx < propertyStockMaterialObj.getModelObjectArrayValue().length; jnx++) {
						  
						  Property propertyStockMaterialsForm = propertyStockMaterialObj.getModelObjectArrayValue()[jnx].getPropertyObject(Constants.BusinessObjects.strGET6StockHasOrgPropsAttri);
						  for(int knx = 0; knx < propertyStockMaterialsForm.getModelObjectArrayValue().length; knx++) {
							  
							  arrOrgPropertiesForm.add(propertyStockMaterialsForm.getModelObjectArrayValue()[knx]);
						  }
					  }
				  }
				  
				  DataManagementServiceObj.getProperties(arrOrgPropertiesForm.toArray(new ModelObject[ arrOrgPropertiesForm.size() ]), new String[] { Constants.BusinessObjects.Properties.strOwningProject, Constants.BusinessObjects.Properties.strget6OrgPreferredStock });
				  
				  if(null != propertyStockMaterialObj) {
					  for(int inx = 0; inx < propertyStockMaterialObj.getModelObjectArrayValue().length; inx++) {
						  Property propertyStockMaterialsForm = propertyStockMaterialObj.getModelObjectArrayValue()[inx].getPropertyObject(Constants.BusinessObjects.strGET6StockHasOrgPropsAttri);
						  for(int jnx = 0; jnx < propertyStockMaterialsForm.getModelObjectArrayValue().length; jnx++) {
							  
							  StockMaterialAttributesFormBean StockMaterialAttributesFormBeanObj = new StockMaterialAttributesFormBean();
							  String strOwningProject = propertyStockMaterialsForm.getModelObjectArrayValue()[jnx].getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strOwningProject);
							  if(strOwningProject.contains(this.m_strCurrentProject)) {
								  
								  boolean isPreferredStock = ((TCComponent)propertyStockMaterialsForm.getModelObjectArrayValue()[jnx]).getLogicalProperty(Constants.BusinessObjects.Properties.strget6OrgPreferredStock);
								  String strStockMaterial = propertyStockMaterialObj.getModelObjectArrayValue()[inx].getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strObjectString);
								  StockMaterialAttributesFormBeanObj.setObjectString(strStockMaterial);
								  StockMaterialAttributesFormBeanObj.setPreferred(Boolean.toString(isPreferredStock));
								  StockMaterialAttributesFormBeanObj.setTCProject(strOwningProject);
								  StockMaterialAttributesFormBeanObj.setTCComponentForm((TCComponentForm)propertyStockMaterialsForm.getModelObjectArrayValue()[jnx]);
								  StockMaterialAttributesFormBeanObj.setTCComponentItem((TCComponentItem)propertyStockMaterialObj.getModelObjectArrayValue()[inx]);
								  treeStockMaterials.put(strStockMaterial, StockMaterialAttributesFormBeanObj);
							  } 
						  }
				  	  }
				  }
			  }
		  } catch(Exception eObj) {
			  
			  this.showErrorMessage(eObj.toString());
		  }
		  
		  return treeStockMaterials;
	  }
	  
	public void addStockMaterialLOVDisplayer(final TableItem p_TableItemObj, final ManufacturingAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
		  
		  try {
			  
			  TableEditor StockMaterialTableEditor = new TableEditor(this.m_SelectedItemsTable);
			  StockMaterialTableEditor.grabHorizontal = true;
			  p_TableItemObj.setImage(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, null);
			  final iComboBox stockMaterialComboBox = new iComboBox();
			  stockMaterialComboBox.setRendererIcon(new ImageIcon(getClass().getClassLoader().getResource(Constants.ManufacturingAttributesDialog.strIconsPrefix + Constants.BusinessObjects.strGET6StockMtrl + Constants.ManufacturingAttributesDialog.strIconsSuffix)));
			  
			  Composite stockMaterialComposite = new Composite(this.m_SelectedItemsTable, SWT.EMBEDDED);
			  Frame stockMaterialsFrame = SWT_AWT.new_Frame(stockMaterialComposite);
			  stockMaterialsFrame.add(stockMaterialComboBox);
			  stockMaterialComposite.pack();
			  
			  if(p_ManufacturingAttributesFormBeanObj.getStockMaterials().size() != 0) {
				  stockMaterialComboBox.setItems(p_ManufacturingAttributesFormBeanObj.getStockMaterials().keySet().toArray(new String[p_ManufacturingAttributesFormBeanObj.getStockMaterials().size()]));
				  stockMaterialComboBox.setText(p_ManufacturingAttributesFormBeanObj.getStockMaterial());
			  } else {
				  
				  Display.getDefault().asyncExec(new Runnable() {
				        public void run() {
				        	TreeMap<String, StockMaterialAttributesFormBean> treeStockMaterials = getStockMaterial(p_ManufacturingAttributesFormBeanObj.getTCComponentItem());
							  if(treeStockMaterials.size() != 0) {
								  stockMaterialComboBox.setItems(treeStockMaterials.keySet().toArray(new String[treeStockMaterials.size()]));
								  stockMaterialComboBox.setText(p_ManufacturingAttributesFormBeanObj.getStockMaterial());
								  m_hshMapFormValues.get(p_ManufacturingAttributesFormBeanObj.getObjectString()).setStockMaterials(treeStockMaterials);
							 }
				        }
				    });
			  }
			  stockMaterialComboBox.setName(p_ManufacturingAttributesFormBeanObj.getObjectString());
			  
			  stockMaterialComboBox.addActionListener(new ActionListener() {

					@Override
					public void actionPerformed(ActionEvent ActionEventObj) {
						
						final ActionEvent ActionEventObjF = ActionEventObj;
						
						 Display.getDefault().asyncExec(new Runnable() {
						        public void run() {
									try {
										
										String strSelectedStockMaterial = ((iComboBox)ActionEventObjF.getSource()).getSelectedItem().toString();
										m_isValueChanged = true;
										TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
										if(!(Constants.ManufacturingAttributesDialog.strNoneValue).equals(strSelectedStockMaterial)) {
											
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, strSelectedStockMaterial);
								        	m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource()).getName())).setModified(true);
								        	TCComponentItem tcSelectedStockMaterial = m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).getStockMaterials().get(strSelectedStockMaterial).getTCComponentItem();
								        	m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setStockMaterial(strSelectedStockMaterial);
								        	m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setStockMaterialItem(tcSelectedStockMaterial);
								        	setTableImage(p_TableItemObj, Constants.BusinessObjects.strGET6StockMtrl);
										} else {
											
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, Constants.General.EMPTY_STRING_VALUE_C);
											m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource()).getName())).setModified(true);
											m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setStockMaterial(Constants.General.EMPTY_STRING_VALUE_C);
								        	m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setStockMaterialItem(null);
										}
										   
									} catch(Exception tcObj) {
										showErrorMessage(tcObj.toString());
									}
						        }
						 });
					}
			  });
			  
			  StockMaterialTableEditor.setEditor(stockMaterialComposite, p_TableItemObj, Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN);
			 // setTableImage(p_TableItemObj, Constants.BusinessObjects.strGET6StockMtrl);
		  } catch(Exception eObj) {
			  
			  showErrorMessage(eObj.toString());
		  }
	  }
	
	
	public void addStockMaterialQuantitySpinner(final TableItem p_TableItemObj, final ManufacturingAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
		
		 try {
			  
			 if(!(Constants.General.EMPTY_STRING_VALUE_C).equals(p_ManufacturingAttributesFormBeanObj.getStockMaterial())) {
				 
				  p_TableItemObj.setGrayed(false);
				  TableEditor stockMaterialQuantityTableEditor = new TableEditor(this.m_SelectedItemsTable);
				  stockMaterialQuantityTableEditor.grabHorizontal = true;
				  
				  Spinner stockMaterialQuantitySpinner = new Spinner(this.m_SelectedItemsTable, SWT.BORDER);
				  if ( ! p_TableItemObj.getText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN).isEmpty() )
				  {
					  int iSpinnerDigit = p_TableItemObj.getText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN).split(Constants.General.DOT_DELIMITER_VALUE_C)[1].length();
					  stockMaterialQuantitySpinner.setDigits(iSpinnerDigit);
					  stockMaterialQuantitySpinner.setIncrement(Constants.ManufacturingAttributesDialog.iStockMaterialQuantityBaseIncrement * iSpinnerDigit);
					  stockMaterialQuantitySpinner.setMaximum(Constants.ManufacturingAttributesDialog.iStockMaterialQuantityMaxValue);
					  String strSelectedQuantity = p_TableItemObj.getText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN).replace(Constants.General.DOT_STRING_VALUE_C, Constants.General.EMPTY_STRING_VALUE_C);
					  int iSelectedQuantity = Integer.parseInt((Constants.General.EMPTY_STRING_VALUE_C).equals(strSelectedQuantity)?Constants.General.ZERO_STRING_VALUE_C:strSelectedQuantity);
					  stockMaterialQuantitySpinner.setSelection(iSelectedQuantity);
				  }
				  
				  stockMaterialQuantitySpinner.addModifyListener(new ModifyListener() {

					@Override
					public void modifyText(ModifyEvent ModifyEventObj) {
						
						  m_isValueChanged = true;
						  TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
						  double dQuantityValue = (double) Math.round(Double.parseDouble(((Spinner)ModifyEventObj.widget).getText()) * 1000) / 1000;
						  m_hshMapFormValues.get(tableItemObj.getText(0)).setStockMaterialQuantity(dQuantityValue);
						  m_hshMapFormValues.get(tableItemObj.getText(0)).setModified(true);
						
						  tableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN, Double.toString(dQuantityValue));
					}
					  
				  });
				  
				 stockMaterialQuantitySpinner.pack();
			      
				 stockMaterialQuantityTableEditor.setEditor(stockMaterialQuantitySpinner, p_TableItemObj, Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN);
				 
			 } else {
				 
				 p_TableItemObj.setGrayed(true);
			 }
		  } catch(Exception eObj) {
			  
			  showErrorMessage(eObj.toString());
		  }
	}
	
	 public void addStructureCodeLOVDisplayer(TableItem p_TableItemObj, ManufacturingAttributesFormBean p_ManufacturingAttributesFormBeanObj) {
		  
		  try {
			  

			  TableEditor structureCodeCodeTableEditor = new TableEditor(this.m_SelectedItemsTable);
			  structureCodeCodeTableEditor.grabHorizontal = true;
			  
			  if(null == this.m_TCPropertySCDescriptorObj) {
		    	  this.getStructureCodeDescriptor();
		      }
		   
			  LOVDisplayer LOVStructureCodeDisplayerObj = new LOVDisplayer(this.m_SelectedItemsTable, 0);	
			  LOVStructureCodeDisplayerObj.initialize(null, this.m_TCPropertySCDescriptorObj, null);
			  LOVStructureCodeDisplayerObj.setSelectedValue((-1 != p_ManufacturingAttributesFormBeanObj.getStructureCode())?Property.toIntString(p_ManufacturingAttributesFormBeanObj.getStructureCode()):Constants.General.EMPTY_STRING_VALUE_C);
			  LOVStructureCodeDisplayerObj.setEnabled(false);

			  LOVStructureCodeDisplayerObj.addPropertyChangeListener(new IPropertyChangeListener() {
	
					public void propertyChange(PropertyChangeEvent PropertyChangeEventObj) {
						 
						final PropertyChangeEvent fPropertyChangeEventObj = PropertyChangeEventObj;
						
						 Display.getDefault().asyncExec(new Runnable() {
						        public void run() {
									try {
										if(null != fPropertyChangeEventObj.getNewValue()) {
											
											m_isValueChanged = true;
											TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
											int iStructureCode = Integer.parseInt(((LOVPropertyValue)fPropertyChangeEventObj.getNewValue()).getDisplayableValue());
											m_hshMapFormValues.get(tableItemObj.getText(0)).setStructureCode(iStructureCode);
											m_hshMapFormValues.get(tableItemObj.getText(0)).setModified(true);
											
											tableItemObj.setText(Constants.ManufacturingAttributesDialog.STRUCTURE_CODE_COLUMN, Integer.toString(iStructureCode));
										}
										   
									} catch(Exception tcObj) {
										showErrorMessage(tcObj.toString());
									}
						        }
						 });
					}
			  });
		      
			  structureCodeCodeTableEditor.setEditor(LOVStructureCodeDisplayerObj, p_TableItemObj, Constants.ManufacturingAttributesDialog.STRUCTURE_CODE_COLUMN);
		  } catch(Exception eObj) {
			  
			  showErrorMessage(eObj.toString());
		  }
	  }

	  public void init() {
		  
		  try {
			  
			  Job ManufacturingAttributesOperationObj = new  ManufacturingAttributesOperation("Fetching Manufacturing Attributes...", this.m_strCurrentProject, this.m_SelectedItemsTable, this.m_selectedComponent);
			  
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
				        	 m_hshMapFormValues = ((ManufacturingAttributesOperation)paramIJobChangeEvent.getJob()).getSelectedComponentsData();
							  
							 for(ManufacturingAttributesFormBean ManufacturingAttributesFormBeanObj : m_hshMapFormValues.values()) {
								   
								  TableItem TableItemObj = new TableItem(m_SelectedItemsTable, SWT.NONE);
								  setTableImage(TableItemObj, ManufacturingAttributesFormBeanObj.getTCComponentItem().getType());
								 							      
							      TableItemObj.setText(Constants.ManufacturingAttributesDialog.ITEM_ID_COLUMN, ManufacturingAttributesFormBeanObj.getObjectString());
							      
							      if((null != ManufacturingAttributesFormBeanObj.getItemPublishDate()) || (null != ManufacturingAttributesFormBeanObj.getBOMPublishDate())) {
							    	  
							    	  TableItemObj.setBackground(Constants.ManufacturingAttributesDialog.ITEM_ID_COLUMN, new Color(Display.getCurrent(), 138,  242, 122));
							      }
							      
							      
							      TableItemObj.setText(Constants.ManufacturingAttributesDialog.MAKE_BUY_COLUMN, ManufacturingAttributesFormBeanObj.getMakeBuy());
							      
							      TableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_COLUMN, ManufacturingAttributesFormBeanObj.getStockMaterial());
							      if(!(Constants.General.EMPTY_STRING_VALUE_C).equals(ManufacturingAttributesFormBeanObj.getStockMaterial())) {
							    	  
							    	  setTableImage(TableItemObj, Constants.BusinessObjects.strGET6StockMtrl);
							    	  TableItemObj.setText(Constants.ManufacturingAttributesDialog.STOCK_MATERIAL_QUANTITY_COLUMN, Double.toString(ManufacturingAttributesFormBeanObj.getStockMaterialQuantity()));
							      } 
							      
							      TableItemObj.setText(Constants.ManufacturingAttributesDialog.PLANNING_CODE_COLUMN, ManufacturingAttributesFormBeanObj.getPlanningCode());
							      
							      TableItemObj.setText(Constants.ManufacturingAttributesDialog.STRUCTURE_CODE_COLUMN, (ManufacturingAttributesFormBeanObj.getStructureCode() == -1)?Constants.General.EMPTY_STRING_VALUE_C:Integer.toString(ManufacturingAttributesFormBeanObj.getStructureCode()));
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
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.toString());
		  }
		  
	  }
}

