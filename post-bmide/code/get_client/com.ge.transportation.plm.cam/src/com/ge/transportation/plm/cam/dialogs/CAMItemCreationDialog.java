package com.ge.transportation.plm.cam.dialogs;

import java.awt.Frame;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Vector;

import org.eclipse.jface.dialogs.TitleAreaDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;
import org.eclipse.swt.graphics.*;

import com.ge.transportation.plm.cam.common.Common;
import com.ge.transportation.plm.cam.common.Logger;
import com.ge.transportation.plm.cam.constants.Constants;
import com.ge.transportation.plm.cam.dialogs.CAMItemConfirmDialog;
import com.ge.transportation.plm.cam.handlers.CamUtilsHandler;
import com.teamcenter.rac.aif.AIFClipboard;
import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.aif.AIFPortal;
import com.teamcenter.rac.aif.InterfaceAIFOperationListener;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.util.Registry;

public class CAMItemCreationDialog extends TitleAreaDialog implements InterfaceAIFOperationListener
{
	static Text labelMID;
	static Text setup;
	static Text labelCasting 						= null;
	static Text labelCastinglimgREVID 				= null;
	static Text labelFPlimgREVID 					= null;
	static Text labelFP;
	static  Text Mfgtitle;
	static Text labelCO;
	
	private Composite m_CompositeContainerObj		= null;
	private TCComponent comp          				= null ;
	
	public static Text textModel 					= null;
	public static Text REVID 						= null;
	
	TCComponent rel[] 								= null;
	String DatasetNameF 							= null;
	String itemId 									= null;
	String ItemTest 								= null;	
	ArrayList<String> J1							=null;
	Frame frame;
	String DSFinal;
	
	static Combo labelSite;
	static Button buttonOk;
	static Button buttonCancel;
	Shell p_parentShell;
	TCSession m_session = (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
	protected Registry appReg = Registry.getRegistry(this);
	
	
	public CAMItemCreationDialog(Shell p_parentShell) 
	{
		super(p_parentShell);
		
	}
	
	public void create() 
	{
		super.create();
		
		setTitle(Constants.CamUtilsDialogUI.strTitle);
		
	}
	
	protected Control createDialogArea(Composite p_CompositeParent)
	{
		p_CompositeParent.setToolTipText("");
		Composite CompositeContainer = (Composite)super.createDialogArea(p_CompositeParent);
		
		m_CompositeContainerObj = new Composite(CompositeContainer, SWT.NONE);
		GridLayout gl_CompositeContainer = new GridLayout();
		gl_CompositeContainer.numColumns = 5;
		m_CompositeContainerObj.setLayout(gl_CompositeContainer);
		
		//Logger.write("INFO - "+"User able to selected SITE from drop-down");
		/*Site Label*/
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelSelectSite );
		labelSite = new Combo(m_CompositeContainerObj, SWT.NULL);
		
		try 
		{
			J1 = get_sites();
			
		}
		catch (SQLException e1) 
		{
			e1.printStackTrace();
			Logger.write(e1);
			
		}
		labelSite.setItems(new String [] {Constants.CamUtilsDialogUI.strLabelSelectSite, J1.get(0),J1.get(1)});
		GridData gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 4;
		labelSite.setLayoutData(gridData);
		labelSite.select(0);
		
		/*labelModel */
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelCADModelId );
		textModel = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER | SWT.READ_ONLY);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		textModel.setLayoutData(gridData);
		Image ImageIcon1 = appReg.getImage( Constants.CamUtilsDialogUI.strPasteIcon );
		
		Button button = new Button(m_CompositeContainerObj, SWT.BORDER );
		button.setImage(ImageIcon1);

		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelRevIdstar );
		REVID = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER | SWT.READ_ONLY);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 1;
		REVID.setLayoutData(gridData);
		CAMUtilsrun();
		
		/*1*/
		button.addListener(SWT.Selection, new Listener() 
		{
			public void handleEvent(Event event) 
			{
				MessageBox messageBox = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
				
				messageBox.setText("Copy");
				messageBox.setMessage(Constants.CamUtilsDialogUI.strMsg1);
				AIFClipboard aifclipboard = AIFPortal.getClipboard();
				Transferable transferable = aifclipboard.getContents(this);
				if(transferable == null)
				{
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
					messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg2 );
					messageBox1.open();
					
					return;
					
				}
				Vector<?> selComps2 = new Vector<Object>();
				try
				{
					DataFlavor[] flavors = transferable.getTransferDataFlavors();
					selComps2 = (Vector<?>) transferable.getTransferData(flavors[1]);
					
				}
				catch(Exception exception)
				{
					new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					Logger.write(exception);
					
				}
				
				int no_of_objects2 = 0; 	// no. of objects copied
				no_of_objects2 = selComps2.size();
				
				if ( no_of_objects2 > 1 )
				{
					new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					//	messageBox.setVisible(true);
					return;
					
				}
				
				if(((TCComponent)selComps2.elementAt(0)) instanceof TCComponentItem )
				{
					try 
					{
						TCComponentItem componentToPaste =  ( TCComponentItem ) selComps2.elementAt( 0 ) ;
						textModel.setText( componentToPaste.getProperty( Constants.BusinessObjects.Properties.strItemID ) );
						
						REVID.setText( componentToPaste.getLatestItemRevision().getProperty( Constants.BusinessObjects.Properties.strItemRevId ) );
						
					}
					catch( Exception ex )
					{
						Logger.write(ex);
						return;
						
					}
					
				}
				else if( ((TCComponent)selComps2.elementAt(0)) instanceof TCComponentItemRevision )
				{
					try 
					{
						TCComponentItem item = ((TCComponentItemRevision)selComps2.elementAt(0)).getItem();
						
						String itemId = item.getProperty( Constants.BusinessObjects.Properties.strItemID );
						//item.getDateProperty( Constants.BusinessObjects.Properties.strItemID);
						textModel.setText( itemId );
						REVID.setText( ((TCComponentItemRevision)selComps2.elementAt(0)).getProperty( Constants.BusinessObjects.Properties.strItemRevId ) );
						
					}
					catch( Exception ex )
					{
						Logger.write(ex);
						return;
						
					}
					
				}
				else
				{
					new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					
					return;
					
				}
				
			}
			
		});
		
				
		/*labelCasting */
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelCastingForging );
		labelCasting = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		labelCasting.setLayoutData(gridData);
		
		button = new Button(m_CompositeContainerObj, SWT.BORDER );
		Image pasteButton = appReg.getImage( Constants.CamUtilsDialogUI.strPasteIcon );
		button.setImage(pasteButton);
		
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelRevId );
		labelCastinglimgREVID = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 1;
		labelCastinglimgREVID.setLayoutData(gridData);
		/*1*/
		
		button.addListener(SWT.Selection, new Listener() 
		{
			public void handleEvent(Event event) 
			{
				AIFClipboard aifclipboard = AIFPortal.getClipboard();
				Transferable transferable = aifclipboard.getContents(this);
				if(transferable == null)
				{
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
					messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg3 );
					messageBox1.open();
					return;
					
				}
				
				Vector<?> selComps2 = new Vector<Object>();
				try
				{
					DataFlavor[] flavors = transferable.getTransferDataFlavors();
					selComps2 = (Vector<?>) transferable.getTransferData(flavors[1]);
					
				}
				catch(Exception exception)
				{
					new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					Logger.write(exception);
					
				}
				
				int no_of_objects2 = 0; 	// no. of objects copied
				no_of_objects2 = selComps2.size();
				
				if ( no_of_objects2 > 1 )
				{
					new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					//	messageBox.setVisible(true);
					return;
					
				}
				
				if(((TCComponent)selComps2.elementAt(0)) instanceof TCComponentItem )
				{
					try 
					{
						TCComponentItem componentToPaste =  (TCComponentItem) selComps2.elementAt(0) ;
						labelCasting.setText( componentToPaste.getProperty( Constants.BusinessObjects.Properties.strItemID ) );
						labelCastinglimgREVID.setText( componentToPaste.getLatestItemRevision().getProperty( Constants.BusinessObjects.Properties.strItemRevId ) );
						
					}
					catch( Exception ex )
					{
						Logger.write(ex);
						return;
						
					}
					
				}
				else if( ((TCComponent)selComps2.elementAt(0)) instanceof TCComponentItemRevision )
				{
					try 
					{
						TCComponentItem item = ((TCComponentItemRevision)selComps2.elementAt(0)).getItem();
						String itemId = item.getProperty( Constants.BusinessObjects.Properties.strItemID );
						labelCasting.setText( itemId );
						labelCastinglimgREVID.setText( ( ( TCComponentItemRevision )selComps2.elementAt(0) ).getProperty( Constants.BusinessObjects.Properties.strItemRevId ) );
						
					}
					catch( Exception ex )
					{
						Logger.write(ex);
						return;
						
					}
					
				}
				else
				{
					new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					//messageBox.setVisible(true);
					return;
					}
				}
			});
		
		/*2*/
		/*labelFP */
		new Label( m_CompositeContainerObj, SWT.NULL ).setText( Constants.CamUtilsDialogUI.strLabelFixturePartNumber );
		labelFP = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		labelFP.setLayoutData(gridData);
		button = new Button(m_CompositeContainerObj, SWT.BORDER );
		Image pasteButton1 = appReg.getImage( Constants.CamUtilsDialogUI.strPasteIcon );
		button.setImage(pasteButton1);
		/*1*/
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelRevId);
		labelFPlimgREVID = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 1;
		labelFPlimgREVID.setLayoutData(gridData);
		
		button.addListener(SWT.Selection, new Listener() 
		{
			public void handleEvent(Event event) 
			{
				MessageBox messageBox = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
				messageBox.setText("Copy");
				messageBox.setMessage( Constants.CamUtilsDialogUI.strMsg1 );
				AIFClipboard aifclipboard = AIFPortal.getClipboard();
				Transferable transferable = aifclipboard.getContents(this);
				if(transferable == null)
				{
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
					messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg3 );
					messageBox1.open();
					return;
					
				}
				
				Vector<?> selComps2 = new Vector<Object>();
				try
				{
					DataFlavor[] flavors = transferable.getTransferDataFlavors();
					selComps2 = (Vector<?>) transferable.getTransferData(flavors[1]);
					
				}
				catch(Exception exception)
				{
					new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					Logger.write(exception);
					
				}
				
				int no_of_objects2 = 0; 	// no. of objects copied
				no_of_objects2 = selComps2.size();

				if ( no_of_objects2 > 1 )
				{
					new MessageBox(getShell(),SWT.ERROR|SWT.OK);
					//	messageBox.setVisible(true);
					return;
					
				}
				
				if(((TCComponent)selComps2.elementAt(0)) instanceof TCComponentItem )
				{
					try 
					{
						TCComponentItem componentToPaste =  (TCComponentItem) selComps2.elementAt(0) ;
						labelFP.setText(componentToPaste.getProperty( Constants.BusinessObjects.Properties.strItemID ) );
						labelFPlimgREVID.setText( componentToPaste.getLatestItemRevision().getProperty( Constants.BusinessObjects.Properties.strItemRevId ) );
						
					}
					catch( Exception ex )
					{
						Logger.write(ex);
						return;
						
					}
					
				}
				else if( ((TCComponent)selComps2.elementAt(0)) instanceof TCComponentItemRevision )
				{
					try 
					{
						TCComponentItem item = ((TCComponentItemRevision)selComps2.elementAt(0)).getItem();
						String itemId = item.getProperty( Constants.BusinessObjects.Properties.strItemID );
						labelFP.setText( itemId );
						labelFPlimgREVID.setText( ((TCComponentItemRevision)selComps2.elementAt(0)).getProperty( Constants.BusinessObjects.Properties.strItemRevId ) );
						
					}
					catch( Exception ex )
					{
						Logger.write(ex);
						return;
						
					}
					
				}
				else
				{
					new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					//messageBox.setVisible(true);
					return;
					
				}
				
			}
			
		});
		
		/*2*/
		/*setup*/
		
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelSetupNumber );
		setup = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 4;
		setup.setText("1");
		setup.addListener(SWT.Verify, new Listener() 
		{
			public void handleEvent(Event e) 
			{
				String string = e.text;
				char[] chars = new char[string.length()];
				string.getChars(0, chars.length, chars, 0);
				for (int i = 0; i < chars.length; i++) 
				{
					if (!('0' <= chars[i] && chars[i] <= '9')) 
					{
						e.doit = false;
						return;
						
					}
					
				}
				
			}
			
		});
		
		setup.setLayoutData(gridData);
		
		/*labelMID*/
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelMachineId );
		//labelMID = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER | SWT.READ_ONLY);
		//GP 3/15/2017 Open the Machine ID field for editing
		labelMID = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER );
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		labelMID.setLayoutData(gridData);
		labelMID.setText( Constants.CamUtilsDialogUI.strLabelMachineId );
		Logger.write("DEBUG - "+ Constants.CamUtilsDialogUI.strLabelMachineId );
		/*1*/
		
		button = new Button(m_CompositeContainerObj, SWT.BORDER );
		Image SearchButton = appReg.getImage( Constants.CamUtilsDialogUI.strFindIcon );
		button.setImage(SearchButton);		
		button.addListener(SWT.Selection, new Listener() 
		{
			public void handleEvent(Event e) 
			{
				String SitePullDown = labelSite.getText();
				String str = Constants.CamUtilsDialogUI.strLabelSelectSite;
				if(str.equals(SitePullDown)||(SitePullDown.isEmpty()))
				{
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
					messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg4 );
					messageBox1.open();
					Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg4 );
					return;
					
				}
				else
				{
					CAMItemSearchDialog obj = new CAMItemSearchDialog(null);
					obj.open();
					
				}
				
			}
			
		});
		
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 3;
		labelMID.setLayoutData(gridData);
		
		/*Mfgtitle*/
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.CamUtilsDialogUI.strLabelCNCTitle );
		Mfgtitle = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 4;
		Mfgtitle.setLayoutData(gridData);
		
		return m_CompositeContainerObj;
		
	}
	
	@Override
	protected void createButtonsForButtonBar(Composite parent) 
	{
		Label separator1 = new Label((Composite) m_CompositeContainerObj, SWT.HORIZONTAL | SWT.SEPARATOR);
		separator1.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));
		GridData gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 5;
		separator1.setLayoutData(gridData);
		
		/*Ok button*/
		buttonOk = new Button((Composite) m_CompositeContainerObj, SWT.PUSH);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		buttonOk.setLayoutData(gridData);
		buttonOk.setText(" OK ");
		buttonOk.addListener(SWT.Selection, new Listener() 
		{
			public void handleEvent(Event event) 
			{
				if(event.widget==buttonOk)
				{
					if(labelSite.getText().equals( Constants.CamUtilsDialogUI.strLabelSelectSite ) || labelSite.getText().isEmpty())
					{
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
						messageBox1.setText("Error");
						messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg5 );
						Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg5 );
						messageBox1.open();
						
					}
					else if(labelMID.getText().equals( Constants.CamUtilsDialogUI.strLabelMachineId ) || labelMID.getText().isEmpty())
					{
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
						messageBox1.setText("Error");
						messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg6 );
						Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg6 );
						messageBox1.open();
						
					} 
					else if(setup.getText().isEmpty())
					{
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
						messageBox1.setText("Error");
						messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg7 );
						Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg7 );
						messageBox1.open();
						
					}
					else if(Mfgtitle.getText().isEmpty())
					{
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
						messageBox1.setText("Error");
						messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg8 );
						messageBox1.open();
						Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg8 );

					}
					else if( Mfgtitle.getText().isEmpty() == false && Common.containsWhiteSpace(Mfgtitle.getText()))
					{
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
						messageBox1.setText("Error");
						messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg19 );
						messageBox1.open();
						Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg19 );
					}
					else if(labelSite.getText().equalsIgnoreCase(Constants.CamUtilsDialogUI.strGRVSite))
					{
						if(labelMID.getText().isEmpty() == false && labelMID.getText().length()>4)
						{
							String strMachineID = labelMID.getText();
													
							if ( Character.isLetter(strMachineID.charAt(0)) && Character.isLetter(strMachineID.charAt(1)) &&
									Character.isDigit(strMachineID.charAt(2)) && Character.isDigit(strMachineID.charAt(3)) && 
											Character.isDigit(strMachineID.charAt(4)) )
							{
								CAMItemConfirmDialog ConfirmDialogobj = new CAMItemConfirmDialog(getShell());
								ConfirmDialogobj.create();
								ConfirmDialogobj.open();
							}
							else
							{
								MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
								messageBox1.setText("Error");
								messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg18 );
								Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg18 );
								messageBox1.open();
							}
							
						}
						else if(labelMID.getText().length()<5)
						{
							MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
							messageBox1.setText("Error");
							messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg18 );
							Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg18 );
							messageBox1.open();
						}
					}
					else
					{
						CAMItemConfirmDialog ConfirmDialogobj = new CAMItemConfirmDialog(getShell());
						ConfirmDialogobj.create();
						ConfirmDialogobj.open();
					}
					
				}
				
			}
			
		});
			
	   
	     /*Cancel button*/
	     buttonCancel = new Button((Composite) m_CompositeContainerObj, SWT.PUSH);
	     gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
	     buttonCancel.setText("Cancel");
	     buttonCancel.setLayoutData(gridData);
	     
	     Label separator11 = new Label((Composite) m_CompositeContainerObj, SWT.HORIZONTAL | SWT.SEPARATOR);
	     separator11.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));
	     gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
	     gridData.horizontalSpan = 5;
	     separator11.setLayoutData(gridData);
	     
	     buttonCancel.addListener(SWT.Selection, new Listener() 
	     {
	    	 public void handleEvent(Event event) 
	    	 {
	    		 if(event.widget==buttonCancel)
	    		 {
	    			 ((Composite) m_CompositeContainerObj).getShell().dispose();
	    			 
	    		 }
	    		 
	    	 }
	    	 
	     });
	     
	}
	
	public void CAMUtilsrun()
	{	
		
		InterfaceAIFComponent[] HanlderSelected = CamUtilsHandler.selectedComponents;
		comp = (TCComponent)HanlderSelected[0];
		try
		{
			if( comp instanceof TCComponentItem )
			{
				itemId = comp.getProperty( Constants.BusinessObjects.Properties.strItemID );
				textModel.setText( itemId );
				TCComponentItemRevision rev = ((TCComponentItem)comp).getLatestItemRevision();
				REVID.setText( rev.getProperty( Constants.BusinessObjects.Properties.strItemRevId ) );
				rel = rev.getRelatedComponents( Constants.BusinessObjects.Relations.strSpecification );				
				
				if(rel.length!=0)
				{
					for( int cnt =0 ; cnt <rel.length; cnt++)
					{
						if(rel[cnt].getProperty( Constants.BusinessObjects.Properties.strObjectTypeVal ).equalsIgnoreCase( Constants.BusinessObjects.strUGMaster ) )
						{
							DatasetNameF = rel[cnt].getProperty( Constants.BusinessObjects.Properties.strObjectName );
							
						}
						else
						{
							MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
							messageBox1.setText("Error");
							messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg11 );
							messageBox1.open();
							if(SWT.OK>0)
							{
								getShell().dispose();
								
							}
							Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg11 );
							
						}
						
					}
					
				}
				else
				{
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
			        messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg11 );
			        messageBox1.open();
			        if(SWT.OK>0)
			        {
			        	
			        	getShell().dispose();
			        }
			        Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg11 );
				}
				ItemTest = itemId.concat("-MFG");
				Object testQuery =  Common.itemQuery(ItemTest);
				if(ItemTest!=null)
				{
					int k = CAM_DB_Check_Item(ItemTest);
					if((k==-1) && (testQuery!=null))
					{
						testQuery =  Common.itemQuery(ItemTest);
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
						messageBox1.setText("Error");
				        messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg12 );
				        messageBox1.open();
				        if(SWT.OK>0)
				        {				        	
				        	getShell().dispose();
				        }
				        Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg12 );
					}
					else if((k==0) && (testQuery!=null))
					{
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
						messageBox1.setText("Error");
				        messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg13 );
				        messageBox1.open();
				        if(SWT.OK>0)
				        {
				        	getShell().dispose();
				        }
				        Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg13 );
					}
					else if(testQuery==null)
					{
						Delete_Mfg(ItemTest);
						Logger.write("INFO - "+"Deleted MFG Item:"+ItemTest+"from RIN Database");						
					}
					else
					{						
						Logger.write("INFO - "+"Mfg Item not yet created for this Item");
					}
				}
				else
				{
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
			        messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg14 );
			        messageBox1.open();
			        if(SWT.OK>0)
			        {			        	
			        	getShell().dispose();
			        }
			        Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg14 );
				}			
			}
			else if( comp instanceof TCComponentItemRevision )
			{				
				TCComponentItem item = ((TCComponentItemRevision)comp).getItem();
				itemId = item.getProperty( Constants.BusinessObjects.Properties.strItemID );
				textModel.setText( itemId );
				REVID.setText( comp.getProperty( Constants.BusinessObjects.Properties.strItemRevId ) );
				rel = comp.getRelatedComponents( Constants.BusinessObjects.Relations.strSpecification );
				
				if(rel.length!=0)
				{
					for( int cnt =0 ; cnt <rel.length; cnt++)
					{
						if(rel[cnt].getProperty( Constants.BusinessObjects.Properties.strObjectTypeVal ).equalsIgnoreCase( Constants.BusinessObjects.strUGMaster ) )
						{
							DatasetNameF = rel[cnt].getProperty( Constants.BusinessObjects.Properties.strObjectName );							
						}						
					}
					
				}
				else
				{					
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
					messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg15 );
					messageBox1.open();
					if(SWT.OK>0)
					{
						getShell().dispose();						
					}
					Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg15 );					
				}
				
				ItemTest = itemId.concat("-MFG");
				Object testQuery =  Common.itemQuery(ItemTest);
				int k = CAM_DB_Check_Item(ItemTest);
				if((k==-1) && (testQuery!=null))
				{
					testQuery =  Common.itemQuery(ItemTest);
					
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
					messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg12 );
					messageBox1.open();
					if(SWT.OK>0)
					{
						getShell().dispose();						
					}
					Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg12 );					
				}
				else if((k==0) && (testQuery!=null))
				{
					System.out.println( Constants.CamUtilsDialogUI.strMsg16 );
					MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
					messageBox1.setText("Error");
					Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg13 );
					messageBox1.open();
					if(SWT.OK>0)
					{
						getShell().dispose();						
					}
					Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg13 );					
				}
				else if(testQuery==null)
				{
					// ItemTest doesn't exists in Teamcenter, User deleted. So call Deletion method here
					Delete_Mfg(ItemTest);
					Logger.write("INFO - "+"Deleted MFG Item:"+ItemTest+"from Dtatabase");					
				}
				else
				{
					Logger.write("INFO - "+"Mfg Item not yet created for this Item");					
				}
				
			}
			else
			{
				MessageBox messageBox1 = new MessageBox(getShell(), SWT.ERROR|SWT.OK);
				messageBox1.setText("Error");
		        messageBox1.setMessage( Constants.CamUtilsDialogUI.strMsg17 );
		        messageBox1.open();
		        if(SWT.OK>0)
		        {
		        	getShell().dispose();
		        	
		        }
		        Logger.write("ERROR - "+ Constants.CamUtilsDialogUI.strMsg17 );
			}
			
		}
		catch(Exception exception)
		{
			new MessageBox(getShell(), SWT.ERROR|SWT.OK);
			Logger.write(exception);
			
		}
		
	}
	
	protected ArrayList<String> get_sites() throws SQLException
	{
		final ArrayList<String> allItems = new ArrayList<String>();
		
		/* Check for JDBC Driver */
		Common.checkDriver();
		
		/* get connected to DB */
		Connection conn = Common.connectDB();
		
		Statement stmt=conn.createStatement();
		ResultSet rs=stmt.executeQuery("select  DISTINCT SITE_NAME from GETS_MFG_SITES");
		
		try 
		{
			while (rs.next()) 
			{
				String result = rs.getString(1);
				
				if (result != null ) 
				{
					result = result.trim();
					
				}
				
				allItems.add(result);
				
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
					e.printStackTrace();
					Logger.write(e);
					
				}
				
			}
			
		}
		return allItems;
	}
	
	public String getDatasetName()
	{
		return DSFinal;
		
	}

	@Override
	public void endOperation() {
		
	}

	@Override
	public void startOperation(String arg0) {
		
	}
	
	/*
	 * Check if item already exists in DB.
	 * If yes then return -1 as error status.
	 * Else return 0 if item.
	 * Currently search is based on Item ID
	 */	
	protected int CAM_DB_Check_Item( String item_Id )
	{
		Connection conn = null;
		int is_Item_Exists = 0;
		
		/* Check for JDBC Driver */
		Common.checkDriver();
		conn = Common.connectDB();
		try
		{
			Statement stmt=conn.createStatement();
			ResultSet rs = stmt.executeQuery("select *FROM GETS_CAM_ITEMS where ITEM_ID=item_Id");
			
			while( rs.next() )
			{
				String result = null;
				result = rs.getString("ITEM_ID");
				if( result != null )
				{
					result = result.trim();
					if(result.equalsIgnoreCase(item_Id))
					{
						
						is_Item_Exists=-1;
						break;
					}
				}
				
			}
			if( conn != null)
			{
				conn.close();
			}

		}
		catch( SQLException e )
		{
			com.ge.transportation.plm.cam.common.Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
			e.printStackTrace();
			Logger.write(e);
			return e.getErrorCode();
		}
		return is_Item_Exists;
	}
	
	/*Delete MFG Item, IF doesn't exists in Teamcenter DB*/
	protected int Delete_Mfg( String item_Id )
	{
		int item_Seq = -1;
		int item_rev_Seq = -1;
		int J = -1;
		/* Check for JDBC Driver */
		Common.checkDriver();
		
		/* get connected to DB */
		Connection conn = Common.connectDB();
		
		try
		{
			PreparedStatement preparedStatement = null;
			/* Get ITEM_SEQ for Mfg Item */
			//select ITEM_SEQ from GETS_CAM_ITEMS where ITEM_ID='TESTCAM7CAM-MFG';
			String getItemSeq= "SELECT ITEM_SEQ FROM GETS_CAM_ITEMS WHERE ITEM_ID=?";
			conn.createStatement();
			preparedStatement = conn.prepareCall( getItemSeq );
			preparedStatement.setString( 1, item_Id );
			ResultSet sqlResult = preparedStatement.executeQuery();
			
			while( sqlResult.next() )
			{
				item_Seq = sqlResult.getInt("ITEM_SEQ");
				
				
			}
			if (!sqlResult.next() ) 
			{
			    J=0;
			}
			/* Get ITEM_REV_SEQ for Mfg Item */
			//select ITEM_REV_SEQ from GETS_CAM_ITEM_REVISIONS where ITEM_SEQ=1890;
			String getItemSite= "SELECT ITEM_REV_SEQ FROM GETS_CAM_ITEM_REVISIONS WHERE ITEM_SEQ=?";
			preparedStatement = conn.prepareCall( getItemSite );
			preparedStatement.setInt( 1, item_Seq );
			sqlResult = preparedStatement.executeQuery();
			
			while( sqlResult.next() )
			{
				item_rev_Seq = sqlResult.getInt("ITEM_REV_SEQ");							
			}
			
			if (!sqlResult.next() ) 
			{
			    J=0;
			}
			
			/* Delete Dataset Table */
			//select * from GETS_CAM_DATASETS where ITEM_REV_SEQ='2430';
			String DeleteDatasets= "DELETE FROM GETS_CAM_DATASETS WHERE ITEM_REV_SEQ=?";
			preparedStatement = conn.prepareCall( DeleteDatasets );
			preparedStatement.setInt( 1, item_rev_Seq );
			sqlResult = preparedStatement.executeQuery();
			
			/* Delete Item_revisions Table */
			//select * from GETS_CAM_ITEM_REVISIONS where ITEM_SEQ=1890;
			String DeleteItemRevisions= "DELETE FROM GETS_CAM_ITEM_REVISIONS WHERE ITEM_SEQ=?";
			preparedStatement = conn.prepareCall( DeleteItemRevisions );
			preparedStatement.setInt( 1, item_Seq );
			sqlResult = preparedStatement.executeQuery();
			
			/* Delete Item Table */
			//select * from GETS_CAM_ITEMS where ITEM_ID='TESTCAM7CAM-MFG';
			String DeleteItem= "DELETE FROM GETS_CAM_ITEMS WHERE ITEM_ID=?";
			preparedStatement = conn.prepareCall( DeleteItem );
			preparedStatement.setString( 1, item_Id );
			sqlResult = preparedStatement.executeQuery();
			conn.commit();
					
			if( conn != null )
			{
				conn.close();
			}			
			
		}
		catch( SQLException e )
		{
			com.ge.transportation.plm.cam.common.Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
			e.printStackTrace();
			Logger.write(e);
			
		}
		
		return J;		
	}
}