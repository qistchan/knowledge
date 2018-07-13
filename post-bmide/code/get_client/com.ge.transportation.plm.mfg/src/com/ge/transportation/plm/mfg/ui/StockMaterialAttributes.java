package com.ge.transportation.plm.mfg.ui;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.InputStream;
import java.util.Arrays;
import java.util.LinkedHashMap;

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
import org.eclipse.swt.graphics.Color;
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

import com.ge.transportation.plm.mfg.beans.StockMaterialAttributesFormBean;
import com.ge.transportation.plm.mfg.constants.Constants;
import com.ge.transportation.plm.mfg.operations.StockMaterialAttributesOperation;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.common.lov.view.controls.LOVDisplayer;
import com.teamcenter.rac.kernel.TCComponentFormType;
import com.teamcenter.rac.kernel.TCComponentProject;
import com.teamcenter.rac.kernel.TCPropertyDescriptor;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.util.combobox.iComboBox;
import com.teamcenter.soa.client.model.Property;

public class StockMaterialAttributes extends TitleAreaDialog{
	
	 private Button m_saveButton = null;
	 private Button m_cancelButton = null;
	 private boolean m_isValueChanged = false;
	 private boolean m_canClosewindow = false;
	 private Table m_SelectedItemsTable = null;
	 private String m_strCurrentProject = Constants.General.EMPTY_STRING_VALUE_C;
	 private TCPropertyDescriptor m_TCPropertySCDescriptorObj = null;
	 private InterfaceAIFComponent[] m_selectedComponent = null;
	 
	 private LinkedHashMap<String, StockMaterialAttributesFormBean> m_hshMapFormValues = new LinkedHashMap<String, StockMaterialAttributesFormBean>();
	 
	 public StockMaterialAttributes(Shell p_parentShell) {
		 
		 super(p_parentShell);
		 this.getCurrentProject();
	 }
	 
	 @Override
	  public void create() {
	    super.create();
	    this.getShell().setText(this.m_strCurrentProject + Constants.StockMaterialAttributesDialog.strTitle);
	    setTitle(this.m_strCurrentProject + Constants.StockMaterialAttributesDialog.strTitle);
	    setMessage(Constants.StockMaterialAttributesDialog.strTitleDesc, IMessageProvider.INFORMATION);
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
	    itemIDTableColumn.setText(Constants.StockMaterialAttributesDialog.strColumnItemID);
	    
	    TableColumn preferredStockTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
	    preferredStockTableColumn.pack();
	    preferredStockTableColumn.setText(Constants.StockMaterialAttributesDialog.strColumnPreferredStockMaterial);
	    
	    TableColumn structureCodeTableColumn = new TableColumn(m_SelectedItemsTable, SWT.LEFT);
	    structureCodeTableColumn.pack();
	    structureCodeTableColumn.setText(Constants.StockMaterialAttributesDialog.strColumnStructureCode);
	   
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
	                    		
	                    		addSetPreferredLOVDisplayer(TableItemObj, m_hshMapFormValues.get(TableItemObj.getText(0)));
	                    	} else if(icol == 2) {
	                    		
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
			  Job StockMaterialAttributesOperationObj = new StockMaterialAttributesOperation("Saving Stock Material Attributes...", this.m_strCurrentProject, this.m_SelectedItemsTable, this.m_hshMapFormValues);
			  StockMaterialAttributesOperationObj.schedule();
			  StockMaterialAttributesOperationObj.addJobChangeListener(new IJobChangeListener() {

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
	  
	  public String getCurrentProject() {
		  
		  String strCurrentProject = Constants.General.EMPTY_STRING_VALUE_C;
		  
		  try {
			  TCComponentProject tcCurrentProject = ((TCSession)AIFUtility.getDefaultSession()).getCurrentProject();
			  if(null != tcCurrentProject) {
				  
				  this.m_strCurrentProject = tcCurrentProject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strProjectID);
			  }
		  } catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.getMessage());
		  }
		  
		  return strCurrentProject;
	  }
	  
	  public void getStructureCodeDescriptor() {
		  
		  try {
			  TCComponentFormType  TCComponentFormTypeObj = (TCComponentFormType)((TCSession)AIFUtility.getDefaultSession()).getTypeComponent(Constants.BusinessObjects.strGET6MfgOrgAttrForm);
			  m_TCPropertySCDescriptorObj = TCComponentFormTypeObj.getPropDesc(Constants.BusinessObjects.Properties.strget6StructureCode);
		  }  catch(Exception eObj) {
			  
			  MessageDialog.openError(this.m_SelectedItemsTable.getShell(), "Error", eObj.getMessage());
		  }
	  }
	  
	  public void addSetPreferredLOVDisplayer(TableItem p_TableItemObj, StockMaterialAttributesFormBean p_StockMaterialAttributesFormBean) {
		  
		  try {
			
			  TableEditor SetPreferredTableEditor = new TableEditor(this.m_SelectedItemsTable);
			  SetPreferredTableEditor.grabHorizontal = true;
			  final iComboBox setPreferredCB = new iComboBox();
			 
			  Composite setPreferredComposite = new Composite(this.m_SelectedItemsTable, SWT.EMBEDDED);
			  Frame setPreferredFrame = SWT_AWT.new_Frame(setPreferredComposite);
			  setPreferredFrame.add(setPreferredCB);
			  setPreferredComposite.pack();
			  
			  setPreferredCB.setName(p_StockMaterialAttributesFormBean.getObjectString());
			  setPreferredCB.setText(p_StockMaterialAttributesFormBean.getPreferred());
			  setPreferredCB.setItems(Arrays.asList(new String[] { Constants.StockMaterialAttributesDialog.strTrueValue, Constants.StockMaterialAttributesDialog.strFalseValue, Constants.StockMaterialAttributesDialog.strNoneValue}));
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
					        	m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).setPreferred(strSetPreferredValue);
								TableItem tableItemObj = m_SelectedItemsTable.getSelection()[0];
					        	tableItemObj.setText(1, strSetPreferredValue);
					        	tableItemObj.setText(2, Integer.toString(m_hshMapFormValues.get((((iComboBox)ActionEventObjF.getSource())).getName()).getStructureCode()));
					        	if((Constants.StockMaterialAttributesDialog.strNoneValue).equals(strSetPreferredValue)) {
					        		
					        		//TableItemObj.setBackground(0, new Color(Display.getCurrent(), 138,  242, 122));
					        		tableItemObj.setText(1, Constants.General.EMPTY_STRING_VALUE_C);
					        		tableItemObj.setText(2, Constants.General.EMPTY_STRING_VALUE_C);
					        	}
								   
							} catch(Exception tcObj) {
								showErrorMessage(tcObj.getMessage());
							}
				        }
				 });
					
				}
				  
			  });
			  
			  SetPreferredTableEditor.setEditor(setPreferredComposite, p_TableItemObj, 1);
		  } catch(Exception eObj) {
			  
			  showErrorMessage(eObj.getMessage());
		  }
	  }
	  
	 public void addStructureCodeLOVDisplayer(TableItem p_TableItemObj, StockMaterialAttributesFormBean p_StockMaterialAttributesFormBean) {
		  
		  try {
			  
			  if(null == this.m_TCPropertySCDescriptorObj) {
		    	  this.getStructureCodeDescriptor();
		      }
			  
			  TableEditor StructureCodeTableEditor = new TableEditor(this.m_SelectedItemsTable);
			  StructureCodeTableEditor.grabHorizontal = true;
		      
			  
			  LOVDisplayer LOVStructureCodeDisplayerObj = new LOVDisplayer(this.m_SelectedItemsTable, 0);	
			  LOVStructureCodeDisplayerObj.initialize(null, this.m_TCPropertySCDescriptorObj, null);
			  LOVStructureCodeDisplayerObj.setSelectedValue((-1 != p_StockMaterialAttributesFormBean.getStructureCode())?Property.toIntString(p_StockMaterialAttributesFormBean.getStructureCode()):Constants.General.EMPTY_STRING_VALUE_C);
			  
			  LOVStructureCodeDisplayerObj.addPropertyChangeListener(new IPropertyChangeListener() {
	
					public void propertyChange(PropertyChangeEvent PropertyChangeEventObj) {
						 
						final PropertyChangeEvent fPropertyChangeEventObj = PropertyChangeEventObj;
						
						 Display.getDefault().asyncExec(new Runnable() {
						        public void run() {
									try {
										if(null != fPropertyChangeEventObj.getNewValue()) {
											
											showErrorMessage("Access Denied - Cannot change Structure Code for Stock Material");
										}
										   
									} catch(Exception tcObj) {
										showErrorMessage(tcObj.getMessage());
									}
						        }
						 });
					}
			  });
		      
			  StructureCodeTableEditor.setEditor(LOVStructureCodeDisplayerObj, p_TableItemObj, 2);
		  } catch(Exception eObj) {
			  
			  showErrorMessage(eObj.getMessage());
		  }
	  }

	  public void init() {
		  
		  try {
			  
			  Job StockMaterialAttributesOperationObj = new  StockMaterialAttributesOperation("Fetching Stock Material Attributes...", this.m_strCurrentProject, this.m_SelectedItemsTable, this.m_selectedComponent);
			  
			  StockMaterialAttributesOperationObj.schedule();
			  StockMaterialAttributesOperationObj.addJobChangeListener(new IJobChangeListener() {

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
				        	 m_hshMapFormValues = ((StockMaterialAttributesOperation)paramIJobChangeEvent.getJob()).getSelectedComponentsData();
							  
							 for(StockMaterialAttributesFormBean StockMaterialAttributesFormBeanObj : m_hshMapFormValues.values()) {
								  
								  TableItem TableItemObj = new TableItem(m_SelectedItemsTable, SWT.NONE);
							      
								  InputStream imageStream = getClass().getClassLoader().getResourceAsStream(Constants.StockMaterialAttributesDialog.strIconsPrefix + StockMaterialAttributesFormBeanObj.getTCComponentItem().getType() + Constants.StockMaterialAttributesDialog.strIconsSuffix);
								  if(null != imageStream) {
									  Image iconImage = new Image(Display.getDefault(), imageStream);
									  if(null != iconImage) {
								    	  TableItemObj.setImage(0, iconImage);
								      }
								  }
							      
							      TableItemObj.setText(0, StockMaterialAttributesFormBeanObj.getObjectString());
							      							      
							      TableItemObj.setText(1, StockMaterialAttributesFormBeanObj.getPreferred());
							      
							      if(!(Constants.General.EMPTY_STRING_VALUE_C).equals(StockMaterialAttributesFormBeanObj.getPreferred())) {
							    	  
							    	  TableItemObj.setBackground(0, new Color(Display.getCurrent(), 138,  242, 122));
							    	  TableItemObj.setText(2, Integer.toString(StockMaterialAttributesFormBeanObj.getStructureCode()));
							      }							   
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

