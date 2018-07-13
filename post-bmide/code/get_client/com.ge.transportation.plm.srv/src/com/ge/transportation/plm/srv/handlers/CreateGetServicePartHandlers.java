package com.ge.transportation.plm.srv.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.srv.ui.CreateGetServicePart;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCSession;

/**
 * Our sample handler extends AbstractHandler, an IHandler base class.
 * @see org.eclipse.core.commands.IHandler
 * @see org.eclipse.core.commands.AbstractHandler
 */
/**
* <h1>CreateGetServicePartHandlers</h1>
* This class implements of the Handler for creation 
* Service Part Item Type for Services functionality 
* using the Custom UI
*
* @author  Sudheer Arikere
* @version 1.0
* @since   2017-09-07
*/

public class CreateGetServicePartHandlers extends AbstractHandler {
	/**
	 * The constructor.
	 */
	public CreateGetServicePartHandlers() {
	}

	/**
	 * the command has been executed, so extract extract the needed information
	 * from the application context.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException {
		
		IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked(event);
		
		try {
						
			InterfaceAIFComponent[] selectedComponents =  SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
			if((null != selectedComponents) && (selectedComponents.length == 1)) {
				
				if((selectedComponents[0] instanceof  TCComponentFolder) || (selectedComponents[0] instanceof  TCComponentBOMLine)) {
					
					CreateGetServicePart CreateGetServicePartObj = new CreateGetServicePart(window, selectedComponents);
					CreateGetServicePartObj.CreateGetServicesPart();
				} else {
					
					selectedComponents = new InterfaceAIFComponent[1];
					selectedComponents[0] = ((TCSession)AIFUtility.getDefaultSession()).getUser().getNewStuffFolder();
					CreateGetServicePart CreateGetServicePartObj = new CreateGetServicePart(window, selectedComponents);
					CreateGetServicePartObj.CreateGetServicesPart();
				}
			} else {
				selectedComponents = new InterfaceAIFComponent[1];
				selectedComponents[0] = ((TCSession)AIFUtility.getDefaultSession()).getUser().getNewStuffFolder();
				CreateGetServicePart CreateGetServicePartObj = new CreateGetServicePart(window, selectedComponents);
				CreateGetServicePartObj.CreateGetServicesPart();
			}
		} catch(Exception eObj) {
			
			MessageDialog.openError(window.getShell(), "Error", eObj.getMessage());
		}
		return null;
	}
}
