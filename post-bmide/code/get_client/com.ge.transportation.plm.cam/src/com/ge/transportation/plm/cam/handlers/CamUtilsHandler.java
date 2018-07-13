package com.ge.transportation.plm.cam.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import com.ge.transportation.plm.cam.common.Logger;
import com.ge.transportation.plm.cam.constants.Constants;
import com.ge.transportation.plm.cam.dialogs.CAMItemCreationDialog;
import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.aifrcp.SelectionHelper;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentDatasetType;
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
public class CamUtilsHandler extends AbstractHandler 
{
//03/13/17	GLP Version 11.2.2.1.10035.0.1.2	Fixed Core dump problem
	/**
	 * The constructor.
	 */
	 
	TCSession session = (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
	public static InterfaceAIFComponent[] selectedComponents;
	private TCComponentUser  		user  		 = null ;
	public static TCComponent comp;
	private TCComponentGroup      group		 = null ;
	private TCComponentRole       role       	 = null ;
	private String userName					 = null ;
	private String groupName                 = null ;
	private String roleName					 = null ;

	public CamUtilsHandler() 
	{
		
	}

	/**
	 * the command has been executed, so extract extract the needed information
	 * from the application context.
	 */
	public Object execute(ExecutionEvent event) /*throws ExecutionException*/ 
	{
		Logger.write("INFO - "+"*** Started CAMutils NC Item Creation");	
	
		IWorkbenchWindow window = null;
		
		try
		{
			window = HandlerUtil.getActiveWorkbenchWindowChecked(event);
		
			selectedComponents =  SelectionHelper.getTargetComponents(HandlerUtil.getCurrentSelection(event));
			InterfaceAIFComponent[] HanlderSelected = CamUtilsHandler.selectedComponents;
			comp = (TCComponent)HanlderSelected[0];
			
		}
		catch(Exception ex)
		{
			MessageDialog.openError(window.getShell(), "Error", "No Item/Item Revision selected.\nPlease select one Item");
			//GLP: Version 11.2.2.1.10035.0.1.2
			//DEBUG
			//Logger.write("DEBUG - "+"No item selected::");
			return null;
		}
		
		try
		{
			user       = session.getUser();
			userName   = user.getUserId();
			group      = session.getGroup();
			groupName  = group.getFullName();
			role       = session.getRole();
			roleName   = session.getRole().toString();
				       
			Logger.write("INFO - "+"user from session::"+user);
			Logger.write("INFO - "+"userName from session::"+userName);
			Logger.write("INFO - "+"group from session::"+group);
			Logger.write("INFO - "+"groupName from session::"+groupName);
			Logger.write("INFO - "+"role from session::"+role);
			Logger.write("INFO - "+"roleName from session::"+roleName);
				
		}
		catch(Exception ex)
		{
			MessageDialog.openError(window.getShell(), "Error", "Exception while getting group and role");
			
		}
		
		if( !( groupName.equals( "Operations" ) ) && !( roleName.equals( "Mfg Process Planner" ) ) )
		{
			MessageDialog.openError(window.getShell(), "Error", "You must be under the Opearation group and be an Mfg Process Planner to create a new NC manufacturing item");
			Logger.write("ERROR - "+"You must be under the Operations group and be an Mfg Process Planner to create a new NC manufacturing item");
			
		}
		else if(null == ((TCSession)AIFUtility.getDefaultSession()).getCurrentProject()) 
		{
			MessageDialog.openError(window.getShell(), "Error", "Please select a project for the current session");
			
		}
		else if((null != selectedComponents) && (selectedComponents.length == 1)) 
		{
			if((comp instanceof  TCComponentItem) || (comp instanceof  TCComponentItemRevision)) 
			{
				String strObjectType = comp.getType();
				Logger.write("Logger: Object Type selected: "+ strObjectType );
							
				
				//Modified to execute the tool item rev regardless on Release status //Pradeep-20July2017
				if( strObjectType.equalsIgnoreCase(Constants.BusinessObjects.strGET6MechPartRevision))
				{
					try 
					{	
						String ReleaseStatus = comp.getProperty(Constants.BusinessObjects.Properties.strReleaseStatusList);	
						if(ReleaseStatus.isEmpty())
						{
							//MessageDialog.openError(window.getShell(), "Error", "Please select Items which are released");
							//Warning Message - To indicate the selected item is not released//Pradeep-20July2017
							MessageDialog.openInformation(window.getShell(), "Information - Item Revision Status", "Selected Item Rev is not Released, This Engineering Part dataset can undergo modification by Engineering Team");
						}						
							CAMItemCreationDialog CAMUtilsDialogObj = new CAMItemCreationDialog(window.getShell());
							CAMUtilsDialogObj.create();
							CAMUtilsDialogObj.open();
						
					} 
					catch (TCException e) 
					{
						e.printStackTrace();
					}					
				}
				else
				{					
					//Modified Message  //Pradeep-20July2017
					MessageDialog.openError(window.getShell(), "Error", "Invalid Object selected. Please select Engineering Item Revision to create NC manfacturing Item");
				}				
			} 
			else 
			{	//Modified Message warning for consistent //Pradeep-20July2017
				//MessageDialog.openError(window.getShell(), "Error", "Please select only Item or Item Revision");
				Logger.write("ERROR - "+"Invalid Object selected.Please select only Engineering Item or Engineering Item Revision");				
			}			
		}
		else if(selectedComponents==null || window == null)
		{
			MessageDialog.openError(window.getShell(), "Error", "No Item/Item Revision selected.\nPlease select one Item");
			Logger.write("ERROR - "+"No Item/Item Revision selected.\nPlease select one Item");
			
		}
		else if(selectedComponents.length>1)
		{
			MessageDialog.openError(window.getShell(), "Error", "Multiple Item/Folders selected.\nPlease select only one Item");
			Logger.write("ERROR - "+"Multiple Item/Folders selected.\nPlease select only one Item");
			
		}
		else if(selectedComponents[0] instanceof  TCComponentDatasetType)
		{
			MessageDialog.openError(window.getShell(), "Error", "Invalid Object selected. Please select Engineering Item or Engineering Item Revision");
			Logger.write("ERROR - "+"Please select only Item or Item Revision");
			
		}	
		
		 return null;			
	}
	
}
