package com.ge.transportation.plm.mfg.ui;

import java.awt.Frame;

//import org.apache.log4j.Logger;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;

import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.aif.AbstractAIFApplication;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.commands.newitem.NewItemCommand;
import com.teamcenter.rac.kernel.TCSession;
//import com.teamcenter.rac.cmcme.bvr.create.item.CreateItemPanel;

@SuppressWarnings("deprecation")
public class CreateGetDepartment extends NewItemCommand {
	private IWorkbenchWindow m_IWorkbenchWindowObj = null;
	private InterfaceAIFComponent[] m_InterfaceAIFComponentObj = null;

	public CreateGetDepartment(IWorkbenchWindow p_IWorkbenchWindow, InterfaceAIFComponent[] p_InterfaceAIFComponentObj) {
		this.m_IWorkbenchWindowObj = p_IWorkbenchWindow;
		this.m_InterfaceAIFComponentObj = p_InterfaceAIFComponentObj;
	}
	
	public CreateGetDepartment(Frame paramFrame, AbstractAIFApplication paramAbstractAIFApplication, String paramString1, String paramString2, boolean paramBoolean) {
		
		//super(paramFrame, paramAbstractAIFApplication, paramString1, paramString2, paramBoolean);
		//Logger logger = Logger.getLogger(NewItemCommand.class);
		//logger.setLevel(Level.ALL);
		this.objectType = paramString1;
	    this.defaultSelectionObjectType = paramString1;
	    this.parentFrame = paramFrame;
	    this.application = paramAbstractAIFApplication;
	    setPasteRelation(paramString2);
	    setRevisionFlag(paramBoolean);
	    try
	    {
	      this.session = (TCSession) (AIFUtility.getDefaultSession());
	      InterfaceAIFComponent[] arrayOfInterfaceAIFComponent = getTargets();
	      this.targetArray = checkComponents(arrayOfInterfaceAIFComponent);
	      if ((this.targetArray == null) && (arrayOfInterfaceAIFComponent != null)) {
	        return;
	      }
	    }
	    catch (Exception localException)
	    {
	     // MessageBox.post(paramFrame, localException);
	    }
	    postDialog(paramFrame);	
	}
	
	protected String getRegistrationKeyForDialog()
	  {
	    //Registry localRegistry = Registry.getRegistry(this);
	    String str1 = getClass().getName() + "." + "DIALOG";
	    System.out.println(str1);
	    //String str2 = localRegistry.getString(str1, null);
	    //if ((str2 == null) || (str2.length() <= 0)) {
	      str1 = "newDesignDialog";
	      str1 = "com.teamcenter.rac.cme.bvr.create.item.CreateItemPanel";
	    //}
	    //logger.debug("Registration key for dialog : " + str1);
	    return str1;
	  }

	public void createMachineItem() {

		try {
			
			NewItemCommand NewItemCommandObj = new NewItemCommand(AIFDesktop.getActiveDesktop().getFrame(), AIFUtility.getCurrentApplication(), "GET6MEDepartment", null, false, m_InterfaceAIFComponentObj);
			System.out.println("tfsdf");
			//NewItemCommand NewItemCommandObj = new NewItemCommand();
			NewItemCommandObj.objectType = "GET6MEDepartment";
			NewItemCommandObj.defaultSelectionObjectType = "GET6MEDepartment";
			
			/*NewItemDialog NewItemDialogObj = new NewItemDialog(NewItemCommandObj, false);
			NewItemDialogObj.objectType = "GET6MEDepartment";
			NewItemDialogObj.defaultSelectionObjectType = "GET6MEDepartment";
			NewItemDialogObj.showUOM = false;
			System.out.println(NewItemDialogObj.objectType);*/
			System.out.println("tfsdf");
			NewItemCommandObj.executeModal();

		}
		catch (Exception eObj) {

			MessageDialog.openError(this.m_IWorkbenchWindowObj.getShell(), "Error", eObj.getMessage());
		}
	}

}
