package com.get.ontrack.getrans;


//==================================================
//
//Copyright 2012 Siemens Product Lifecycle Management Software Inc. All Rights Reserved.
//
//==================================================



import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.get.ontrack.common.GETConstants;
//import com.teamcenter.getrans.GETCommon;
//import com.teamcenter.getrans.GETQuery;
import com.teamcenter.services.strong.administration.IRMService;
import com.teamcenter.services.strong.administration.UserManagementService;
import com.teamcenter.services.strong.administration._2008_03.IRM;
import com.teamcenter.services.strong.administration._2008_03.IRM.ActivateUserInput;
import com.teamcenter.services.strong.administration._2008_03.IRM.DeactivateUserInput;
import com.teamcenter.services.strong.administration._2014_10.UserManagement.MakeUserResponse;
import com.teamcenter.services.strong.administration._2015_07.UserManagement.CreateOrUpdateUserInputs;
import com.teamcenter.services.strong.administration._2015_07.UserManagement.CreateOrUpdateUserResponse;
import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.ServiceData;

//Include the Data Management Service Interface
//Input and output structures for the service operations
//Note: the different namespace from the service interface

/**
* Perform different operations in the DataManagementService
*
*/
public class GETUserAdministration
{
	private UserManagementService umService;
	private Connection connection;

	private static Map<Connection, GETUserAdministration> m_instance;

	/**
	* Constructor for the class GETDataManagement. This is a private constructor that cannot be called from outside this class
	* 
	* @param connection - Connection object for the session
	*/
	private GETUserAdministration(Connection connection)
	{
		this.connection = connection;
		umService = UserManagementService.getService(connection);
	}
	
	/**
	* Static Singleton method to return the instance of the class GETDataManagement.
	     *
	     * @param connection - Connection object for the session
	     * @return an instance of the class GETDataManagement
	*/
	public static GETUserAdministration getService( Connection connection )
	{
		GETUserAdministration returnInstance = null;
  	if(m_instance == null)
  	{
      	m_instance = new HashMap<Connection, GETUserAdministration>();
      	//m_instance = new GETDataManagement(connection);
  	}
  	if (m_instance.containsKey(connection) )
      {
          returnInstance = m_instance.get(connection);
      }
  	else
  	{
      	returnInstance = new GETUserAdministration(connection);
      	m_instance.put(connection, returnInstance);
  	}

  	return returnInstance;
	}
	
	public class UserProperties
	{
		public String userId = null;
		public String personName = null;
		public String password = null;
		public String defaultGroup = null;
		public String newOwner = null;
		public String newOwningGroup = null;

		public Map<String, String[]> userAddlPropMap = null;
		public Map<String, String[]> userPropMap = null;
	}

	public ModelObject getUser(String userId) throws Exception
	{
		ModelObject user = null;

		try
		{
			GETQuery queryService = GETQuery.getInstance(connection);
			
			ModelObject[] foundObjs = queryService.queryObject(GETConstants.Query.userQuery,
						new String[]{GETConstants.Query.userId}, new String[]{userId});
			
			if ( foundObjs != null && foundObjs.length > 0 )
			{
				user = foundObjs[0];
			}
		} 
		catch (Exception e)
		{
			e.printStackTrace();
			throw e;
		} 

		return user;
	}

  public ModelObject[] createOrUpdateUsers(UserProperties[] usrPropsArr) throws Exception
  {
  	ModelObject[] createdUsers = null;
  	try
  	{
	    	CreateOrUpdateUserInputs[] userInputs = new CreateOrUpdateUserInputs[usrPropsArr.length] ;
	    	for (UserProperties usrProp : usrPropsArr)
	    	{
	    		int index = 0;
	    		userInputs[index] = new CreateOrUpdateUserInputs();

	    		userInputs[index].person = usrProp.personName;
	    		userInputs[index].userId = usrProp.userId;
	    		userInputs[index].password = usrProp.password;
		    	userInputs[index].defaultGroup = usrProp.defaultGroup;
		    	userInputs[index].newOwner = usrProp.newOwner;
		    	userInputs[index].newOwningGroup = usrProp.newOwningGroup;
		    	userInputs[index].userPropertyMap = usrProp.userPropMap;
		    	userInputs[index++].userAddlPropertyMap = usrProp.userAddlPropMap;
	    	}

  		CreateOrUpdateUserResponse createUsrResp = umService.createOrUpdateUser(userInputs); 
  		String errMsg = GETCommon.getErrorFromServiceData(createUsrResp.serviceData);

  		if( errMsg == null )
  		{
  			int createdUserCount = createUsrResp.serviceData.sizeOfCreatedObjects();
  			errMsg = (createdUserCount > 0) ? "Users Created" : "Users not Created";
  		}
  	}
  	catch(Exception ex)
  	{
  		throw ex;
  	}

  	return createdUsers;
  }

  public String makeUserByArgs(List<String> arguments) throws Exception
  {
  	String result = null;
		MakeUserResponse makeUserResponse= umService.makeUser(arguments.toArray(new String[0]), null, true, true);

		int status = makeUserResponse.commandStatus;

		result = (status == 0) ? "Success" : "Failure";

  	return result;
  }

  public boolean activateUser(String userId) throws Exception
  {
  	boolean isUserActivated = false;
  	ModelObject user = getUser(userId);

		if(user != null)
		{
		    // Get the service stub
			IRMService getTcIRMService = IRMService.getService(connection);

          //Activating User in Teamcenter
          ActivateUserInput UserInput[] = new ActivateUserInput[1];			

          UserInput[0] = new ActivateUserInput();

          UserInput[0].licenseLevel = 0;
          UserInput[0].targetUser = user;

          IRM.LicenseStatusResponse UserActivationResult = getTcIRMService.activateUsers(UserInput);

          //Check if Size of Updated Objects is Equal to 1
          if(UserActivationResult.serviceData.sizeOfUpdatedObjects() == 1)
          {
          	isUserActivated = true;
          }
		}

		return isUserActivated;
  }

  public boolean deactivateUser(String userId) throws Exception
  {
  	boolean isUserdeactivated = false;
  	ModelObject user = getUser(userId);

		if(user != null)
		{
		    // Get the service stub
			IRMService irmService = IRMService.getService(connection);

          // De-Activating User in Teamcenter
          DeactivateUserInput DEActivateUserInput[] = new DeactivateUserInput[1];
          DEActivateUserInput[0] = new DeactivateUserInput();
          DEActivateUserInput[0].targetUser = user;

          ServiceData licResponse = irmService.deactivateUsers(DEActivateUserInput);

          // Check if Size of Updated Objects is Equal to 1
          if (licResponse.sizeOfUpdatedObjects() == 1)
          {
          	isUserdeactivated = true;
          }
		}

		return isUserdeactivated;
  }

	public String resetUserPassword(String userId, String password) throws Exception
	{
		String retMsg = null;

		//Check if the user already exists
		ModelObject user = getUser(userId);

		if ( user == null )
		{
			retMsg = "User does not exist in Teamcenter";
			return retMsg;
		}

		List<String> arguments = new ArrayList<String>();
		arguments.add(new StringBuffer().append("-user=").append(userId).toString());
		arguments.add(new StringBuffer().append("-password=").append(password).toString());
		arguments.add(new StringBuffer().append("-update").toString());

		makeUserByArgs(arguments);

		return retMsg;
	}
  /**
   * 
   * @param userId
   * @param group
   * @param role
   * @param status - Pass null, to get both active and inactive users, False to get Active, True to get inactive
   * @param userStatus - Pass null to get both active and inactive, "0" to get active, "1" to get inactive
   * @return
   * @throws Exception
   */
  public ModelObject getUserGroupMember(String userId, String group, String role, String status,
  		String userStatus) throws Exception
  {
  	ModelObject userGroupMember = null;
  	GETQuery queryService = GETQuery.getInstance(connection);
  	
  	List<String> entries = new ArrayList<String>();
  	List<String> values = new ArrayList<String>();
  	if(userId != null && !userId.isEmpty())
  	{
  		entries.add(GETConstants.Query.user);
  		values.add(userId);
  	}
  	if(group != null && !group.isEmpty())
  	{
  		entries.add(GETConstants.Query.group);
  		values.add(group);
  	}
  	if(role != null && !role.isEmpty())
  	{
  		entries.add(GETConstants.Query.role);
  		values.add(role);
  	}
  	if(status != null && !status.isEmpty())
  	{
  		entries.add(GETConstants.Query.status);
  		values.add(status);
  	}
  	if(userStatus != null && !userStatus.isEmpty())
  	{
  		entries.add(GETConstants.Query.userStatus);
  		values.add(userStatus);
  	}
  	
		ModelObject[] foundObjs = queryService.queryObject(GETConstants.Query.activeGrpMemberQuery,
				entries.toArray(new String[0]), values.toArray(new String[0]));

		if ( foundObjs != null && foundObjs.length > 0 )
		{
			userGroupMember = foundObjs[0];
		}

  	return userGroupMember;
  }
}
