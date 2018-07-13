package com.ge.transportation.plm.mfg.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.mfg.constants.Constants;
import com.ge.transportation.plm.mfg.ui.StockMaterialAttributes;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;

/**
 * Our sample handler extends AbstractHandler, an IHandler base class.
 * @see org.eclipse.core.commands.IHandler
 * @see org.eclipse.core.commands.AbstractHandler
 */
public class StockMaterialAttributesHandlers extends AbstractHandler {
	/**
	 * The constructor.
	 */
	public StockMaterialAttributesHandlers() {
	}

	/**
	 * the command has been executed, so extract extract the needed information
	 * from the application context.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException {
		
		IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked(event);
		
		InterfaceAIFComponent[] selectedComponents =  SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
		if((null != selectedComponents) && (selectedComponents.length == 1) && (selectedComponents[0].getType().equals(Constants.BusinessObjects.strGET6Material))) {
			

			try {
				
				String strRoleName = ((TCSession)AIFUtility.getDefaultSession()).getRole().getRoleName();
				if((Constants.Role.strMfgProcessEngineer).equals(strRoleName) || (Constants.Role.strDBA).equals(strRoleName)) {
					
					if(null != ((TCSession)AIFUtility.getDefaultSession()).getCurrentProject()) {
						
						final StockMaterialAttributes StockMaterialAttributesObj = new StockMaterialAttributes(window.getShell());
						StockMaterialAttributesObj.setSelectedComponents(selectedComponents);
						StockMaterialAttributesObj.open();
						StockMaterialAttributesObj.close();
					} else {
						
						MessageDialog.openError(window.getShell(), "Error", "Please select a project for the current session");
					}
				} else {
					
					MessageDialog.openError(window.getShell(), "Error", "Invalid Group/Role, Allowed Roles are \n\n   -Mfg Process Engineer");
				}
			} catch (TCException tcObj) {
				
				MessageDialog.openError(window.getShell(), "Error", tcObj.getMessage());
			}
			
		} else {
			MessageDialog.openError(window.getShell(), "Error", "Invalid Item Type selected.\nPlease select only one GET Material");
		}
		return null;
	}
}
