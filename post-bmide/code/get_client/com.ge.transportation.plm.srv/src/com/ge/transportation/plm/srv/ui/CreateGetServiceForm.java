package com.ge.transportation.plm.srv.ui;

import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;

import com.ge.transportation.plm.srv.constants.Constants;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.commands.open.OpenFormDialog;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCPreferenceService;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.ui.commands.handlers.GenericFormHandler;
import com.teamcenter.rac.ui.commands.handlers.NewBOHandler;

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

public class CreateGetServiceForm {
	private IWorkbenchWindow m_IWorkbenchWindowObj = null;
	private InterfaceAIFComponent[] m_InterfaceAIFComponentObj = null;

	public CreateGetServiceForm(IWorkbenchWindow p_IWorkbenchWindow, InterfaceAIFComponent[] p_InterfaceAIFComponentObj) {
		this.m_IWorkbenchWindowObj = p_IWorkbenchWindow;
		this.m_InterfaceAIFComponentObj = p_InterfaceAIFComponentObj;
		
	}
public void CreateServiceForm() {
		
		try {
			TCPreferenceService TCPreferenceServiceObj = ((TCSession)AIFUtility.getDefaultSession()).getPreferenceService();
			TCPreferenceServiceObj.setStringValue(Constants.BusinessObjects.strGET6defaultrel, Constants.BusinessObjects.strGET6SrvRelation);
			
			Map<Object, Object> mapParameters = new HashMap<Object, Object>();
			mapParameters.put(Constants.BusinessObjects.Properties.strObjectTypeVal, Constants.BusinessObjects.strGET6SrvForm);
			mapParameters.put(Constants.BusinessObjects.Properties.strSelectionVal,	this.m_InterfaceAIFComponentObj);
			final ExecutionEvent ExecutionEventObj = new ExecutionEvent(null, mapParameters, null, null);
			final GenericFormHandler GenericFormHandlerObj = new GenericFormHandler();
			GenericFormHandlerObj.execute(ExecutionEventObj);
			TCPreferenceServiceObj.setStringValue(Constants.BusinessObjects.strGET6defaultrel,"");

		}

		catch (ExecutionException eObj) {

			MessageDialog.openError(this.m_IWorkbenchWindowObj.getShell(), "Error", eObj.getMessage());
		} catch (TCException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

///open operation for the Service Form- Start
public void openServiceForm(TCComponent tcc) throws ExecutionException {
	try {

	 OpenFormDialog ofd = new OpenFormDialog((TCComponentForm) tcc);
     ofd.setVisible(true);
	 ofd.addSaveCheckOutButtonListener((ActionListener) this );
  
	}
	catch (Exception e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
}
/// End

}
