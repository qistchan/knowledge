package com.ge.transportation.plm.srv.ui;

import java.util.HashMap;
import java.util.Map;

import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;

import com.ge.transportation.plm.srv.constants.Constants;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.ui.commands.handlers.GenericItemHandler;
import com.teamcenter.rac.ui.commands.handlers.NewBOHandler;

/**
* <h1>CreateGetFunctionalItem</h1>
* This class implements creation of 
* Zonal Level Item Type for Services functionality 
* using the Custom UI
*
* @author  Sudheer Arikere
* @version 1.0
* @since   2017-09-07
*/

public class CreateGetZonalPart {
	
	private IWorkbenchWindow m_IWorkbenchWindowObj = null;
	private InterfaceAIFComponent[] m_InterfaceAIFComponentObj = null;
	
	public CreateGetZonalPart(IWorkbenchWindow p_IWorkbenchWindow, InterfaceAIFComponent[] p_InterfaceAIFComponentObj) {
		
		this.m_IWorkbenchWindowObj = p_IWorkbenchWindow;
		this.m_InterfaceAIFComponentObj = p_InterfaceAIFComponentObj;
	}
	
	/**
	   * This method is used to call the NewBOHandler for the 
	   * creation of the Zonal Level Item type in Teamcenter
	   * This is a part of the sBOM implementation for Services. 
	   * @param None
	   */
	
	public void createZonal() {
		
		try {
			
			Map<Object, Object> mapParameters = new HashMap<Object, Object>();
			mapParameters.put(Constants.BusinessObjects.Properties.strObjectTypeVal, Constants.BusinessObjects.strGET6ZonalPart);
			mapParameters.put(Constants.BusinessObjects.Properties.strSelectionVal, this.m_InterfaceAIFComponentObj);
			final ExecutionEvent ExecutionEventObj = new ExecutionEvent(null, mapParameters, null, null);
			final GenericItemHandler GenericItemHandlerObj = new GenericItemHandler();
			GenericItemHandlerObj.execute(ExecutionEventObj);
			
		} catch (ExecutionException eObj) {
			
			MessageDialog.openError(this.m_IWorkbenchWindowObj.getShell(), "Error", eObj.getMessage());
		}
	}
}