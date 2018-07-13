package com.ge.transportation.plm.srv.ui;

import java.util.HashMap;
import java.util.Map;

import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;

import com.ge.transportation.plm.srv.constants.Constants;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.commands.newform.NewFormCommand;
import com.teamcenter.rac.commands.newform.NewFormDialog;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCPreferenceService;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.ui.commands.handlers.GenericFormHandler;
import com.teamcenter.rac.ui.commands.handlers.NewBOHandler;

/**
* <h1>CreateGetObsoleteForm</h1>
* This class implements creation of 
* Supersudure/Obsolute Form for Services functionality 
* using the Custom UI
*
* @author  Sudheer Arikere
* @version 1.0
* @since   2017-09-07
*/
public class CreateGetObsoleteForm {
	private IWorkbenchWindow m_IWorkbenchWindowObj = null;
	private InterfaceAIFComponent[] m_InterfaceAIFComponentObj = null;
	String type;

	public CreateGetObsoleteForm(IWorkbenchWindow p_IWorkbenchWindow, InterfaceAIFComponent[] p_InterfaceAIFComponentObj) {
		this.m_IWorkbenchWindowObj = p_IWorkbenchWindow;
		this.m_InterfaceAIFComponentObj = p_InterfaceAIFComponentObj;
		type = p_InterfaceAIFComponentObj[0].getType();
	}

	public void CreateObsoleteForm() {
		
		
		try {
			//System.out.println("type:..."+type);
			TCPreferenceService TCPreferenceServiceObj = ((TCSession)AIFUtility.getDefaultSession()).getPreferenceService();
			if (type.equals(Constants.BusinessObjects.strGET6MechPartRev)){
				
				TCPreferenceServiceObj.setStringValue(Constants.BusinessObjects.strGET6defaultrel, Constants.BusinessObjects.strGET6ObsRel);
			}
			if (type.equals(Constants.BusinessObjects.strGET6SrvPartRevi)){
				TCPreferenceServiceObj.setStringValue(Constants.BusinessObjects.strGET6Srvdefaultrel, Constants.BusinessObjects.strGET6ObsRel);
			}

			Map<Object, Object> mapParameters = new HashMap<Object, Object>();
			mapParameters.put(Constants.BusinessObjects.Properties.strObjectTypeVal, Constants.BusinessObjects.strGET6ObsForm);
			mapParameters.put(Constants.BusinessObjects.Properties.strSelectionVal,	this.m_InterfaceAIFComponentObj);
			final ExecutionEvent ExecutionEventObj = new ExecutionEvent(null, mapParameters, null, null);
			final GenericFormHandler GenericFormHandlerObj = new GenericFormHandler();
			GenericFormHandlerObj.execute(ExecutionEventObj);
            if (type.equals(Constants.BusinessObjects.strGET6MechPartRev)){
				
            	TCPreferenceServiceObj.setStringValue(Constants.BusinessObjects.strGET6defaultrel,"");
			}if (type.equals(Constants.BusinessObjects.strGET6SrvPartRevi)){
				TCPreferenceServiceObj.setStringValue(Constants.BusinessObjects.strGET6Srvdefaultrel,"");
			}
			
			
		}

		catch (ExecutionException eObj) {

			MessageDialog.openError(this.m_IWorkbenchWindowObj.getShell(), "Error", eObj.getMessage());
		} catch (TCException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}

}
