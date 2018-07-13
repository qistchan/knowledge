package com.ge.transportation.plm.srv.dialogs;

import java.awt.Frame;
import java.util.ArrayList;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.dialogs.TitleAreaDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;
import org.eclipse.swt.graphics.*;

import com.ge.transportation.plm.srv.constants.Constants;
import com.ge.transportation.plm.srv.handlers.CreateGetSrvItemHandler;
import com.ge.transportation.plm.srv.operations.SrvItemCreationOperation;

import com.teamcenter.rac.aif.AIFClipboard;
import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.aif.AIFPortal;
import com.teamcenter.rac.aif.InterfaceAIFOperationListener;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.kernel.ServiceData;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;

public class ServiceItemCreationDialog extends TitleAreaDialog implements InterfaceAIFOperationListener{
	
	static Text labelMID;
	static Text setup;
	static Text labelCasting 						= null;
	static Text labelCastinglimgREVID 				= null;
	static Text labelFPlimgREVID 					= null;
	static Text labelFP;
	
	static Text labelCO;
	
	private Composite m_CompositeContainerObj		= null;
	private TCComponent comp          				= null ;
	private TCComponent seleted          				= null ;
	
	public static Text textModel 					= null;
	public static Text REVID 						= null;
	public static  Text Nametitle                   = null;
	
	public static InterfaceAIFComponent[] selectedComponents;
	
	TCComponent rel[] 								= null;
	String DatasetNameF 							= null;
	String itemId 									= null;
	String itemName 								= null;
	String ItemTest 								= null;	
	ArrayList<String> J1							=null;
	Frame frame;
	String DSFinal;

	static Button buttonOk;
	static Button buttonCancel;
	Shell p_parentShell;
	
	String newstr;
	TCSession m_session = (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
	
	
	public ServiceItemCreationDialog(Shell p_parentShell) 
	{
		super(p_parentShell);
		
	}
	
	public void create() 
	{
		super.create();
		
		setTitle(Constants.ServicesDialogUI.strTitle);
		
	}
	
	protected Control createDialogArea(Composite p_CompositeParent)
	{
		p_CompositeParent.setToolTipText("Create GET Service Part From Engineering Part");
		Composite CompositeContainer = (Composite)super.createDialogArea(p_CompositeParent);
		
		m_CompositeContainerObj = new Composite(CompositeContainer, SWT.NONE);
		GridLayout gl_CompositeContainer = new GridLayout();
		gl_CompositeContainer.numColumns = 20;
		m_CompositeContainerObj.setLayout(gl_CompositeContainer);
		
		/*Item ID */
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.ServicesDialogUI.strLabelId );
		textModel = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER);
		GridData gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		textModel.setEditable(true);
		gridData.horizontalSpan = 19;
		textModel.setLayoutData(gridData);
		/*2*/
		/*Name*/
		new Label(m_CompositeContainerObj, SWT.NULL).setText( Constants.ServicesDialogUI.strLabelNameTitle );
		Nametitle = new Text(m_CompositeContainerObj, SWT.SINGLE | SWT.BORDER);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 19;
		Nametitle.setLayoutData(gridData);
		//get the Item Id from the Engineering Part - start
		InterfaceAIFComponent[] HanlderSelected = CreateGetSrvItemHandler.selectedComponents;
		comp = (TCComponent)HanlderSelected[0];
		if( comp instanceof TCComponentItem )
		{
			try {
				itemId = comp.getProperty( Constants.BusinessObjects.Properties.strItemID );
				itemName = comp.getProperty( Constants.BusinessObjects.Properties.strObjectName );
			} catch (TCException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			textModel.setText( itemId );
			Nametitle.setText( itemName );
		}
		return m_CompositeContainerObj;
		
	}
	
	@Override
	protected void createButtonsForButtonBar(Composite parent) 
	{
		Label separator1 = new Label((Composite) m_CompositeContainerObj, SWT.HORIZONTAL | SWT.SEPARATOR);
		separator1.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));
		GridData gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 19;
		separator1.setLayoutData(gridData);
		
		/*Ok button*/
		buttonOk = new Button((Composite) m_CompositeContainerObj, SWT.PUSH);
		gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		gridData.horizontalSpan = 5;
		buttonOk.setLayoutData(gridData);
		buttonOk.setText(" OK ");
		buttonOk.addListener(SWT.Selection, new Listener() 
		{
			public void handleEvent(Event event) 
			{
				if(event.widget==buttonOk)
				{
					newstr = textModel.getText();
					if(textModel.getText().isEmpty())
					{
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
						messageBox1.setText("Error");
						messageBox1.setMessage( Constants.ServicesDialogUI.strMsg1 );
						messageBox1.open();
						
					}
					else if(Nametitle.getText().isEmpty())
					{
						MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR|SWT.OK);
						messageBox1.setText("Error");
						messageBox1.setMessage( Constants.ServicesDialogUI.strMsg2 );
						messageBox1.open();

					}
					else
					{
						
						SrvItemCreationOperation srvSOA = new SrvItemCreationOperation();
						InterfaceAIFComponent[] HanlderSelected = CreateGetSrvItemHandler.selectedComponents;
						seleted = (TCComponent)HanlderSelected[0];
						try {
							srvSOA.createGetSrvItem();
							srvSOA.propertiesUpdate(seleted);
							((Composite) m_CompositeContainerObj).getShell().dispose();
						} catch (ServiceException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						} catch (TCException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}

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
	     gridData.horizontalSpan = 19;
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
	
	@Override
	public void endOperation() {
		
	}

	@Override
	public void startOperation(String arg0) {
		
	}
	
}
