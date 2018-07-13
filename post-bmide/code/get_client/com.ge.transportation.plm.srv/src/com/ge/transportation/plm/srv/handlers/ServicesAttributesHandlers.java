package com.ge.transportation.plm.srv.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.srv.constants.Constants;
import com.ge.transportation.plm.srv.ui.CreateGetObsoleteForm;
import com.ge.transportation.plm.srv.ui.CreateGetServiceForm;
import com.ge.transportation.plm.srv.ui.ServicesAttributes;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCComponentItemType;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;

/**
 * Our sample handler extends AbstractHandler, an IHandler base class.
 * @see org.eclipse.core.commands.IHandler
 * @see org.eclipse.core.commands.AbstractHandler
 */
public class ServicesAttributesHandlers extends AbstractHandler {
	
	//private TCComponent comp          				= null ;
	private TCComponentItemRevision rev          				= null ;
	 TCComponent rel[] 								= null;
	/**
	 * The constructor.
	 */
	public ServicesAttributesHandlers() {
	}

	/**
	 * the command has been executed, so extract extract the needed information
	 * from the application context.
	 */
	public Object execute(ExecutionEvent event) throws ExecutionException {
		
		IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked(event);		
		
		InterfaceAIFComponent[] selectedComponents =  SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));

		if(null != selectedComponents) {
				
				try {
					String strRoleName = ((TCSession)AIFUtility.getDefaultSession()).getRole().getRoleName();
					if((Constants.Role.strSrvEngineer).equals(strRoleName) || (Constants.Role.strSrvEngineerManager).equals(strRoleName) || (Constants.Role.strDBA).equals(strRoleName)) {
						if (selectedComponents.length == 1   ){
							if (selectedComponents[0].getType().equals(Constants.BusinessObjects.strGET6MechPartRev)|| selectedComponents[0].getType().equals(Constants.BusinessObjects.strGET6SrvPartRevi)){
								   CreateGetServiceForm CreateGetObsFormObj = new CreateGetServiceForm(window, selectedComponents);	
									//    CreateGetObsFormObj.CreateServiceForm();	
										// Start
									    rev = (TCComponentItemRevision)selectedComponents[0];
										rel = rev.getRelatedComponents( Constants.BusinessObjects.Relations.strServFormRel );
										
										if (rel.length!=0){
											TCComponent srvForm = rev.getRelatedComponent(Constants.BusinessObjects.Relations.strServFormRel);
											CreateGetObsFormObj.openServiceForm(srvForm);
										}else {
											
											CreateGetObsFormObj.CreateServiceForm();	
										}
										// End
									
							}else {
								MessageDialog.openError(window.getShell(), "Error", Constants.ServicesDialogUI.strMsg9);
							}
							return null;
							 	
							
						}else if(null != ((TCSession)AIFUtility.getDefaultSession())) {
							
							final ServicesAttributes ServicesAttributesObj = new ServicesAttributes(window.getShell());
							ServicesAttributesObj.setSelectedComponents(selectedComponents);
							ServicesAttributesObj.open();
							ServicesAttributesObj.close();
							
						}
					} else {
						
						MessageDialog.openError(window.getShell(), "Error",Constants.ServicesDialogUI.strMsg7 );
					}
				} catch (TCException tcObj) {
					
					MessageDialog.openError(window.getShell(), "Error", tcObj.getMessage());
				}
			
		}
		return null;
	}
}
