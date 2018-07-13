package com.ge.transportation.plm.srv.handlers;

import java.util.ArrayList;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.srv.constants.Constants;
import com.ge.transportation.plm.srv.ui.CreateGetObsoleteForm;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.commands.paste.PasteCommand;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentDatasetType;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCSession;

/**
* <h1>CreateGetObsoleteFormHandler</h1>
* This class implements creation of 
* GET Supercedure/Obsolescence Form for Services functionality 
* using the Custom UI
*
* @author  Sudheer Arikere
* @version 1.0
* @since   2017-09-07
*/

public class CreateGetObsoleteFormHandler extends AbstractHandler {
	/**
	 * The constructor.
	 */
	public static TCComponent comp;
	public InterfaceAIFComponent[] selectedComponents;

	public CreateGetObsoleteFormHandler() {
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
				if (selectedComponents[0].getType().equals(Constants.BusinessObjects.strGET6MechPartRev) && ((Constants.Role.strDesigner).equals(strRoleName) || (Constants.Role.strEngineer).equals(strRoleName))){
					CreateGetObsoleteForm CreateGetObsFormObj = new CreateGetObsoleteForm(window, selectedComponents);
					CreateGetObsFormObj.CreateObsoleteForm();
					return null;
				}
				else if (selectedComponents[0].getType().equals(Constants.BusinessObjects.strGET6SrvPartRevi) && ((Constants.Role.strSrvEngineer).equals(strRoleName) || (Constants.Role.strSrvEngineerManager).equals(strRoleName))){
						CreateGetObsoleteForm CreateGetObsFormObj = new CreateGetObsoleteForm(window, selectedComponents);
						CreateGetObsFormObj.CreateObsoleteForm();
						return null;
		        }
				else {
				//	MessageDialog.openError(window.getShell(), "Error", "Valid Objects are\n	-GET Engineering Part Revision\n \nInvalid Group/Role, Allowed Roles are \n\n	-Services Manager or Services Engineer");
					MessageDialog.openError(window.getShell(), "Error",Constants.ServicesDialogUI.strMsg5 );
					return null;
				}
				
			} 
		} catch(Exception eObj) {
			
			MessageDialog.openError(window.getShell(), "Error", eObj.getMessage());
		}
		return null;
	}
	
}
