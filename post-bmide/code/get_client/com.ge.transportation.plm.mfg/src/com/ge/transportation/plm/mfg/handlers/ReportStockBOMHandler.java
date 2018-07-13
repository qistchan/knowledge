package com.ge.transportation.plm.mfg.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.mfg.constants.Constants;
import com.ge.transportation.plm.mfg.ui.ReportStockBOMDial;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCSession;

import org.eclipse.jface.dialogs.MessageDialog;

public class ReportStockBOMHandler extends AbstractHandler
{
	public static InterfaceAIFComponent[] selectedComponents;
		
		/**
		 * The constructor.
		 */
		public ReportStockBOMHandler() 
		{
		}
	
		/**
		 * the command has been executed, so extract extract the needed information
		 * from the application context.
		 */
		public Object execute ( ExecutionEvent event ) throws ExecutionException 
		{
			IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindowChecked ( event );
			try
			{
				selectedComponents =  SelectionHelper.getTargetComponents ( HandlerUtil.getCurrentSelection ( event ) );
				if ( ( null != selectedComponents ) && ( selectedComponents.length == 1 ) &&  ( selectedComponents[0] instanceof TCComponentItemRevision ) )
				{
					if ( null != ( ( TCSession )AIFUtility.getDefaultSession() ).getCurrentProject() )
					{
						TCComponentItemRevision itemRevParent = ( TCComponentItemRevision ) selectedComponents[0];
						String parentRevType = itemRevParent.getPropertyDisplayableValue ( Constants.ReportStockBOM.REVTYPE );
						if ( ( parentRevType.equals ( Constants.ReportStockBOM.ENGREVTYPE ) ) || ( parentRevType.equals ( Constants.ReportStockBOM.MFGREVTYPE ) ) )
						{
							ReportStockBOMDial reportDial = new ReportStockBOMDial ( window.getShell(), itemRevParent );
							reportDial.create();
							reportDial.open();
						}
						else
						{
							MessageDialog.openError ( window.getShell(), "Error", "Please select revision of type \""  + Constants.ReportStockBOM.MFGREVTYPE + "\"Or\""
									+ Constants.ReportStockBOM.ENGREVTYPE + "\"" );
						}
					}
					else
					{
						MessageDialog.openError ( window.getShell(), "Error", "Please select a project for the current session" );
					}
				}
				else
				{
					MessageDialog.openError ( window.getShell(), " Error", "Please select single item revision" );
				}
				
			}
			catch ( Exception ex )
			{
				MessageDialog.openError ( window.getShell(), "Error", ex.getMessage() );
				return null;
			}
			
			return null;
		}

}
