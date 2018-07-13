package com.ge.transportation.plm.mfg.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.mfg.ui.CreateGetGenericResource;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCSession;

/**
 * Our sample handler extends AbstractHandler, an IHandler base class.
 * 
 * @see org.eclipse.core.commands.IHandler
 * @see org.eclipse.core.commands.AbstractHandler
 */
public class CreateGetGenericResourceHandler extends AbstractHandler {
	/**
	 * The constructor.
	 */
	public CreateGetGenericResourceHandler() {
	}

	/**
	 * the command has been executed, to extract the needed information from the
	 * application context.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException {

		IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked(event);
		
		try {
			InterfaceAIFComponent[] selectedComponents = SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
			if ((null != selectedComponents) && (selectedComponents.length == 1)) {
	
				if ((selectedComponents[0] instanceof TCComponentFolder) || (selectedComponents[0] instanceof TCComponentBOMLine)) {
	
					CreateGetGenericResource createGetGenericResourceObj = new CreateGetGenericResource(window, selectedComponents);
					createGetGenericResourceObj.createGetGenericResource();
				} else {
					selectedComponents = new InterfaceAIFComponent[1];
					selectedComponents[0] = ((TCSession)AIFUtility.getDefaultSession()).getUser().getNewStuffFolder();
					CreateGetGenericResource createGetGenericResourceObj = new CreateGetGenericResource(window, selectedComponents);
					createGetGenericResourceObj.createGetGenericResource();
				}
			} else {
				selectedComponents = new InterfaceAIFComponent[1];
				selectedComponents[0] = ((TCSession)AIFUtility.getDefaultSession()).getUser().getNewStuffFolder();
				CreateGetGenericResource createGetGenericResourceObj = new CreateGetGenericResource(window, selectedComponents);
				createGetGenericResourceObj.createGetGenericResource();
			}
		} catch(Exception eObj) {
			
			MessageDialog.openError(window.getShell(), "Error", eObj.getMessage());
		}
		return null;
	}
}
