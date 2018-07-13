
package com.ge.transportation.plm.srv.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.srv.constants.Constants;
import com.ge.transportation.plm.srv.dialogs.ServiceItemCreationDialog;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCComponentGroup;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCComponentRole;
import com.teamcenter.rac.kernel.TCComponentUser;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
/**
 * Our sample handler extends AbstractHandler, an IHandler base class.
 * @see org.eclipse.core.commands.IHandler
 * @see org.eclipse.core.commands.AbstractHandler
 */

public class CreateGetSrvItemHandler extends AbstractHandler 
{
	
	 TCSession session = (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
	 public static InterfaceAIFComponent[] selectedComponents;
	 private TCComponent comp          				= null ;
	 String itemId 									= null;
	 TCComponent rel[] 								= null;
	/**
	 * The constructor.
	 */
	public CreateGetSrvItemHandler() 
	{
	}

	/**
	 * the command has been executed, to extract the needed information
	 * from the application context.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException 
	{
		
		IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked(event);
		selectedComponents =  SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
		
		
		try {
			String strRoleName = ((TCSession)AIFUtility.getDefaultSession()).getRole().getRoleName();
			if(!(Constants.Role.strSrvEngineer).equals(strRoleName) && !(Constants.Role.strSrvEngineerManager).equals(strRoleName)) {

				MessageDialog.openError(window.getShell(), "Error", Constants.ServicesDialogUI.strMsg7);
				return null;
			}
			InterfaceAIFComponent[] selectedComponents =  SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
			if((null != selectedComponents) && (selectedComponents.length == 1)) {
				if((selectedComponents[0] instanceof  TCComponentBOMLine)|| selectedComponents[0].getType().equals(Constants.BusinessObjects.strGET6MechPart)){
					// Check for the missing service form - Start
						comp = (TCComponent)selectedComponents[0];
						TCComponentItemRevision rev = ((TCComponentItem)comp).getLatestItemRevision();
						rel = rev.getRelatedComponents( Constants.BusinessObjects.Relations.strServFormRel );
						if(rel.length==0){
							
							MessageDialog.openError(window.getShell(), "Error", Constants.ServicesDialogUI.strMsg4);
							return null;
						}   

			    	// - End
					ServiceItemCreationDialog ServiceItemDialogObj = new ServiceItemCreationDialog(window.getShell());
					ServiceItemDialogObj.create();
					ServiceItemDialogObj.open();
		
				} else {
					MessageDialog.openError(window.getShell(), "Error", Constants.ServicesDialogUI.strMsg8);
				}
			} else {
				MessageDialog.openError(window.getShell(), "Error", Constants.ServicesDialogUI.strMsg8);
			}
		} catch(Exception eObj) {
			
			MessageDialog.openError(window.getShell(), "Error", eObj.getMessage());
		}
		return null;
	}
	
}
