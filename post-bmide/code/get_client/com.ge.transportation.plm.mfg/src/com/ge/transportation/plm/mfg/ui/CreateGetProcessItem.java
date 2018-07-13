package com.ge.transportation.plm.mfg.ui;

import java.util.HashMap;
import java.util.Map;

import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;

import com.ge.transportation.plm.mfg.constants.Constants;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.ui.commands.handlers.NewBOHandler;

public class CreateGetProcessItem {
	private IWorkbenchWindow m_IWorkbenchWindowObj = null;
	private InterfaceAIFComponent[] m_InterfaceAIFComponentObj = null;

	public CreateGetProcessItem(IWorkbenchWindow p_IWorkbenchWindow,
			InterfaceAIFComponent[] p_InterfaceAIFComponentObj) {
		this.m_IWorkbenchWindowObj = p_IWorkbenchWindow;
		this.m_InterfaceAIFComponentObj = p_InterfaceAIFComponentObj;
	}

	public void createProcessItem() {

		try {

			Map<Object, Object> mapParameters = new HashMap<Object, Object>();
			mapParameters.put(Constants.BusinessObjects.Properties.strObjectTypeVal, Constants.BusinessObjects.strGET6Process);
			mapParameters.put(Constants.BusinessObjects.Properties.strSelectionVal,  this.m_InterfaceAIFComponentObj);
			final ExecutionEvent ExecutionEventObj = new ExecutionEvent(null, mapParameters, null, null);
			final NewBOHandler NewBOHandlerObj = new NewBOHandler();
			NewBOHandlerObj.execute(ExecutionEventObj);

		} catch (ExecutionException eObj) {

			MessageDialog.openError(this.m_IWorkbenchWindowObj.getShell(), "Error", eObj.getMessage());
		}
	}
}
