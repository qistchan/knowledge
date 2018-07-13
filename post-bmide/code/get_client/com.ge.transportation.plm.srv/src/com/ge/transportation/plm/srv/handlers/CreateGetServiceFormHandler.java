package com.ge.transportation.plm.srv.handlers;

import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.srv.constants.Constants;
import com.ge.transportation.plm.srv.ui.CreateGetServiceForm;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCSession;

public class CreateGetServiceFormHandler {
	
	public static TCComponent comp;
	public InterfaceAIFComponent[] selectedComponents;

	public CreateGetServiceFormHandler() {
	}

	/**
	 * the command has been executed, to extract the needed information from the
	 * application context.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException {

		IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked(event);
		
		try {
			selectedComponents = SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
			String strRoleName = ((TCSession)AIFUtility.getDefaultSession()).getRole().getRoleName();
			
			if ((null != selectedComponents) && (selectedComponents.length == 1)) {
				if (selectedComponents[0].getType().equals(Constants.BusinessObjects.strGET6MechPartRev) && (Constants.Role.strSrvEngineer).equals(strRoleName) || (Constants.Role.strSrvEngineerManager).equals(strRoleName)){
					if ((selectedComponents[0] instanceof TCComponentFolder) || (selectedComponents[0] instanceof TCComponentBOMLine)) {
						
						CreateGetServiceForm CreateGetSrvFormObj = new CreateGetServiceForm(window, selectedComponents);
						CreateGetSrvFormObj.CreateServiceForm();
					
					} else {
						CreateGetServiceForm CreateGetObsFormObj = new CreateGetServiceForm(window, selectedComponents);
						CreateGetObsFormObj.CreateServiceForm();
			          	}
				}else {
					MessageDialog.openError(window.getShell(), "Error", Constants.ServicesDialogUI.strMsg6);
					return null;
				}
				
			} 
		} catch(Exception eObj) {
			
			MessageDialog.openError(window.getShell(), "Error", eObj.getMessage());
		}
		return null;
	}

}
