package com.ge.transportation.plm.mfg.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.mfg.ui.CreateGetManufacturingChangeNotice;
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
public class CreateGetManufacturingChangeNoticeHandler extends AbstractHandler {
	/**
	 * The constructor.
	 */
	public CreateGetManufacturingChangeNoticeHandler() {
	}

	/**
	 * the command has been executed, so extract extract the needed information
	 * from the application context.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException 
	{
		IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked(event);
		
			try 
			{
				if ( null != ( ( TCSession )AIFUtility.getDefaultSession() ).getCurrentProject() )
				{
					InterfaceAIFComponent[] selectedComponents =  SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
					if((null != selectedComponents) && (selectedComponents.length == 1)) 
					{
						
						if((selectedComponents[0] instanceof  TCComponentFolder) || (selectedComponents[0] instanceof  TCComponentBOMLine)) 
						{
							
							CreateGetManufacturingChangeNotice CreateGetManufacturingChangeNoticeObj = new CreateGetManufacturingChangeNotice(window, selectedComponents);
							CreateGetManufacturingChangeNoticeObj.createManufacturingChangeNotice();
						}  
						else 
						{
							selectedComponents = new InterfaceAIFComponent[1];
							selectedComponents[0] = ((TCSession)AIFUtility.getDefaultSession()).getUser().getNewStuffFolder();
							CreateGetManufacturingChangeNotice CreateGetManufacturingChangeNoticeObj = new CreateGetManufacturingChangeNotice(window, selectedComponents);
							CreateGetManufacturingChangeNoticeObj.createManufacturingChangeNotice();
						}
					} 
					else 
					{
						selectedComponents = new InterfaceAIFComponent[1];
						selectedComponents[0] = ((TCSession)AIFUtility.getDefaultSession()).getUser().getNewStuffFolder();
						CreateGetManufacturingChangeNotice CreateGetManufacturingChangeNoticeObj = new CreateGetManufacturingChangeNotice(window, selectedComponents);
						CreateGetManufacturingChangeNoticeObj.createManufacturingChangeNotice();
					}
				}
				else
				{
					MessageDialog.openError ( window.getShell(), "Error", "Please select a project for the current session" );
				}
			} 
			catch(Exception eObj) 
			{
				
				MessageDialog.openError(window.getShell(), "Error", eObj.getMessage());
			}
		
		return null;
	}
}