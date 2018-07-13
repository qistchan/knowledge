
package com.ge.transportation.plm.mfg.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.mfg.constants.Constants;
import com.ge.transportation.plm.mfg.ui.CreateGetProcessItem;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCSession;

/**
 * Our sample handler extends AbstractHandler, an IHandler base class.
 * @see org.eclipse.core.commands.IHandler
 * @see org.eclipse.core.commands.AbstractHandler
 */
public class CreateGetProcessHandler extends AbstractHandler 
{
	/**
	 * The constructor.
	 */
	public CreateGetProcessHandler() 
	{
	}

	/**
	 * the command has been executed, to extract the needed information
	 * from the application context.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException 
	{
		
		IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked(event);
		
		try {
			
			InterfaceAIFComponent[] selectedComponents =  SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
			if((null != selectedComponents) && (selectedComponents.length == 1)) {
				
				if((selectedComponents[0] instanceof  TCComponentFolder) || (selectedComponents[0].getType().equals(Constants.BusinessObjects.strMfg0BvrProcess))) {
					
					CreateGetProcessItem createProcess = new CreateGetProcessItem(window, selectedComponents);
					createProcess.createProcessItem();
				} else {
					
					selectedComponents = new InterfaceAIFComponent[1];
					selectedComponents[0] = ((TCSession)AIFUtility.getDefaultSession()).getUser().getNewStuffFolder();
					CreateGetProcessItem createProcess = new CreateGetProcessItem(window, selectedComponents);
					createProcess.createProcessItem();
				}
			} else {
				selectedComponents = new InterfaceAIFComponent[1];
				selectedComponents[0] = ((TCSession)AIFUtility.getDefaultSession()).getUser().getNewStuffFolder();
				CreateGetProcessItem createProcess = new CreateGetProcessItem(window, selectedComponents);
				createProcess.createProcessItem();
			}
		} catch(Exception eObj) {
			
			MessageDialog.openError(window.getShell(), "Error", eObj.getMessage());
		}

		return null;
	}
}
