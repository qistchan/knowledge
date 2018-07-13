
//==================================================
// 
//  Copyright 2015 GE Transportation. All Rights Reserved.
//
//==================================================

package com.teamcenter.getrans.clientx;

import com.teamcenter.getrans.GETCommon;
import com.teamcenter.schemas.soa._2006_03.exceptions.InvalidUserException;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.services.strong.core.SessionService;
import com.teamcenter.services.strong.core._2006_03.Session.LoginResponse;
import com.teamcenter.services.strong.core._2011_06.Session.Credentials;
import com.teamcenter.soa.SoaConstants;
import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.SsoCredentials;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.strong.GroupMember;
import com.teamcenter.soa.client.model.strong.User;


public class GETSession
{
	public static LoginResponse loginResponseObj;

    /**
     * Single instance of the Connection object that is shared throughout
     * the application. This Connection object is needed whenever a Service
     * stub is instantiated.
     */
    private Connection connection;

    /**
     * The credentialManager is used both by the Session class and the Teamcenter
     * Services Framework to get user credentials.
     *
     */
    private GETCredentialManager credentialManager;
    private SsoCredentials ssoCredentials;

    /**
     * Create an instance of the Session with a connection to the specified
     * server.
     *
     * Add implementations of the ExceptionHandler, PartialErrorListener,
     * ChangeListener, and DeleteListeners.
     *
     * @param host      Address of the host to connect to, http://serverName:port/tc
     */
    public GETSession(String host)
    {
        // Create an instance of the GETCredentialManager, this is used
        // by the SOA Framework to get the user's credentials when
        // challenged by the server (session timeout on the web tier).
        credentialManager = new GETCredentialManager();

        String protocol=null;
        String envNameTccs = null;
        if ( host.startsWith("http") )
        {
            protocol   = SoaConstants.HTTP;
        }
        else if ( host.startsWith("tccs") )
        {
            protocol   = SoaConstants.TCCS;
            host = host.trim();
            int envNameStart = host.indexOf('/') + 2;
            envNameTccs = host.substring( envNameStart, host.length() );
            host = "";
        }
        else
        {
            protocol   = SoaConstants.IIOP;
        }

        // Create the Connection object, no contact is made with the server
        // until a service request is made
        connection = new Connection(host, credentialManager, SoaConstants.REST, protocol);

        if( protocol == SoaConstants.TCCS )
        {
           connection.setOption(  Connection.TCCS_ENV_NAME, envNameTccs );
        }

        // Add an ExceptionHandler to the Connection, this will handle any
        // InternalServerException, communication errors, XML marshaling errors
        // .etc
        connection.setExceptionHandler(new GETExceptionHandler());

        // While the above ExceptionHandler is required, all of the following
        // Listeners are optional. Client application can add as many or as few Listeners
        // of each type that they want.

        // Add a Partial Error Listener, this will be notified when ever a
        // a service returns partial errors.
        connection.getModelManager().addPartialErrorListener(new GETPartialErrorListener());

        // Add a Change and Delete Listener, this will be notified when ever a
        // a service returns model objects that have been updated or deleted.
        connection.getModelManager().addModelEventListener(new GETModelEventListener());

        // Add a Request Listener, this will be notified before and after each
        // service request is sent to the server.
        Connection.addRequestListener( new GETRequestListener() );
    }
    
    /**
     * Create an instance of the Session with a connection to the specified
     * server.
     *
     * Add implementations of the ExceptionHandler, PartialErrorListener,
     * ChangeListener, and DeleteListeners.
     *
     * @param host      Address of the host to connect to, http://serverName:port/tc
     */
    public GETSession(String host, String ssoURL, String ssoAppId)
    {
        // Create an instance of the GETCredentialManager, this is used
        // by the SOA Framework to get the user's credentials when
        // challenged by the server (session timeout on the web tier).
        ssoCredentials = new SsoCredentials(ssoURL, ssoAppId);

        String protocol = null;
        String envNameTccs = null;
        if ( host.startsWith("http") )
        {
            protocol   = SoaConstants.HTTP;
        }
        else if ( host.startsWith("tccs") )
        {
            protocol   = SoaConstants.TCCS;
            host = host.trim();
            int envNameStart = host.indexOf('/') + 2;
            envNameTccs = host.substring( envNameStart, host.length() );
            host = "";
        }
        else
        {
            protocol   = SoaConstants.IIOP;
        }

        // Create the Connection object, no contact is made with the server
        // until a service request is made
        connection = new Connection(host, ssoCredentials, SoaConstants.REST, protocol);

        if( protocol == SoaConstants.TCCS )
        {
           connection.setOption(  Connection.TCCS_ENV_NAME, envNameTccs );
        }

        // Add an ExceptionHandler to the Connection, this will handle any
        // InternalServerException, communication errors, XML marshaling errors
        // .etc
        connection.setExceptionHandler(new GETExceptionHandler());

        // While the above ExceptionHandler is required, all of the following
        // Listeners are optional. Client application can add as many or as few Listeners
        // of each type that they want.

        // Add a Partial Error Listener, this will be notified when ever a
        // a service returns partial errors.
        connection.getModelManager().addPartialErrorListener(new GETPartialErrorListener());

        // Add a Change and Delete Listener, this will be notified when ever a
        // a service returns model objects that have been updated or deleted.
        connection.getModelManager().addModelEventListener(new GETModelEventListener());

        // Add a Request Listener, this will be notified before and after each
        // service request is sent to the server.
        Connection.addRequestListener(new GETRequestListener());
    }

    /**
     * Get the Connection object for the session
     *
     * @return  connection
     */
    public Connection getConnection()
    {
        return connection;
    }

    /**
     * Method to establish session and login to Teamcenter 
     * 
     * @param strUserID
     * @param strPassword
     * @param strGroup
     * @return Login error message
     */
    public String login(String strUserID, String strPassword, String strGroup)
    {
        // Get the service stub
        SessionService sessionService = SessionService.getService(connection);
        String errMsg = "";
        // Prompt for credentials until they are right, or until user
        // cancels
    	credentialManager.setUserPassword(strUserID, strPassword, strUserID);
    	credentialManager.setGroupRole(strGroup, "");
        try
        {
            String[] credentials = credentialManager.promptForCredentials();

            // *****************************
            // Execute the service operation
            // *****************************
            loginResponseObj = sessionService.login(credentials[0], credentials[1], credentials[2], credentials[3], "", credentials[4]);
            if(GETCommon.getErrorFromServiceData(loginResponseObj.serviceData) != null)
            {
                String error = GETCommon.getErrorFromServiceData(loginResponseObj.serviceData);
                if (error != null)
                {
                    throw new Exception(error);
                }
            }
        }
        catch (Exception e)
        {
        	e.printStackTrace();
        	errMsg = e.getMessage();
        }

        return errMsg;
    }

    /**
     * Method to establish session and login to Teamcenter 
     * 
     * @param strUserID
     * @param strPassword
     * @param strGroup
     * @return Login error message
     */
    public User login(String userID, String password, String group, String discriminator) throws Exception
    {
        SessionService sessionService = SessionService.getService(connection);
        User user = null;
        // Prompt for credentials until they are right, or until user
        // cancels
    	credentialManager.setUserPassword(userID, password, userID);
    	credentialManager.setGroupRole(group, "");
        try
        {
            String[] credentials = credentialManager.promptForCredentials();

            // *****************************
            // Execute the service operation
            // *****************************
            loginResponseObj = sessionService.login(credentials[0], credentials[1], credentials[2], credentials[3], "", discriminator);
            if(GETCommon.getErrorFromServiceData(loginResponseObj.serviceData) != null)
            {
                String error = GETCommon.getErrorFromServiceData(loginResponseObj.serviceData);
                if (error != null)
                {
                    throw new Exception(error);
                }
            }
            user = loginResponseObj.user;
        }
        catch (Exception e)
        {
        	e.printStackTrace();
        	throw e;
        }

        return user;
    }

    public String loginSSO(String discriminator)
    {
        String errMsg = "";

        try 
        {
            ssoCredentials.setUserPassword(null, null, discriminator);

            String[] credentials = ssoCredentials.getCredentials(new InvalidUserException());

            SessionService ssoSessionSvc = SessionService.getService(connection);   

            Credentials credentialsInst = new Credentials();
            credentialsInst.user = credentials[0];
            credentialsInst.password = credentials[1];
            credentialsInst.group = credentials[2];
            credentialsInst.role = credentials[3];
            credentialsInst.descrimator = discriminator;

            com.teamcenter.services.strong.core._2011_06.Session.LoginResponse loginResponseObj = ssoSessionSvc.loginSSO(credentialsInst);
            if(loginResponseObj.partialErrors != null)
            {
                String error = GETCommon.getErrorFromPartialError(loginResponseObj.partialErrors);
                if (error != null)
                {
                    throw new Exception(error);
                }
            }
        }
        catch(Exception e) 
        {
            e.printStackTrace();
            errMsg = e.getMessage();
        }

        return errMsg;
    }

    public String loginSSOWithKey(String ssoAppUserId, String ssoSessionKey)
    {
        String errMsg = "";

        try 
        {
            SessionService ssoSessionSvc = SessionService.getService(connection);   

            Credentials credentialsInst = new Credentials();
            credentialsInst.user = ssoAppUserId;
            credentialsInst.password = ssoSessionKey;

            ssoCredentials.setUserPassword(ssoAppUserId, ssoSessionKey, null);
            com.teamcenter.services.strong.core._2011_06.Session.LoginResponse loginResponseObj = ssoSessionSvc.loginSSO(credentialsInst);
            if(loginResponseObj.partialErrors != null)
            {
                String error = GETCommon.getErrorFromPartialError(loginResponseObj.partialErrors);
                if (error != null)
                {
                    throw new Exception(error);
                }
            }
        }
        catch(Exception e) 
        {
            e.printStackTrace();
            errMsg = e.getMessage();
        }

        return errMsg;
    }
    
    /**
     * Terminate the session with the Teamcenter Server
     *
     */
    public void logout()
    {
        // Get the service stub
        SessionService sessionService = SessionService.getService(connection);
        try
        {
            // *****************************
            // Execute the service operation
            // *****************************
            sessionService.logout();
        }
        catch (ServiceException e){}
    }

    /**
     * This method returns the currently logged-in User
     * @return user - The currently logged-in User instance
     */
    public User getCurrentUser()
    {
        User user = null;

        if (loginResponseObj != null)
        {
            user = loginResponseObj.user;
        }

        return user;
    }

    /**
     * This method returns the currently logged-in Group Member
     * @return groupMember - The currently logged-in GroupMember instance
     */
    public GroupMember getCurrentGroupMember()
    {
        GroupMember groupMember = null;

        if (loginResponseObj != null)
        {
            groupMember = loginResponseObj.groupMember;
        }

        return groupMember;
    }

    /**
     * This function returns the currently logged-in user's user name
     * @return userName - The String User Name of the currently logged-in User
     */
	public String getCurrentUserName()
	{
		String userName = "";
		SessionService sessionService = SessionService.getService(connection);
		try 
		{
			if(sessionService != null) 
			{
			    DataManagementService dmService = DataManagementService.getService(connection);
			    dmService.getProperties(new ModelObject[]{sessionService.getTCSessionInfo().user}, new String[]{"user_name"});
			    userName = sessionService.getTCSessionInfo().user.get_user_name();
			}
		}
		catch (Exception ex) 
		{
			ex.printStackTrace();
		} 
		return userName;
	}

	/**
     * This function returns the role of currently logged-in user
     * @return role - The String role of the currently logged-in User
     */
    public String getCurrentRole()
    {
        String role = "";
        SessionService sessionService = SessionService.getService(connection);
        try 
        {
            if(sessionService != null) 
            {
                role = sessionService.getTCSessionInfo().role.get_role_name();
            }
        } 
        catch (Exception ex) 
        {
            ex.printStackTrace();
        } 
        return role;
    }

    /**
     * This function returns the group of currently logged-in user
     * @return role - The String group of the currently logged-in User
     */
    public String getCurrentGroup()
    {
        String group = "";
        SessionService sessionService = SessionService.getService(connection);
        try 
        {
            if(sessionService != null) 
            {
                group = sessionService.getTCSessionInfo().group.get_name();
            }
        } 
        catch (Exception ex) 
        {
            ex.printStackTrace();
        } 
        return group;
    }

	/**
	 * This function returns the site id
	 * @return
	 */
	public String getSiteID()
	{
		String strSiteID = "";
		SessionService sessionService = SessionService.getService(connection);
		try 
		{
			if(sessionService != null) 
			{
				strSiteID = sessionService.getTCSessionInfo().site.get_name();
			}
		} 
		catch (Exception ex) 
		{
			ex.printStackTrace();
		}
		return strSiteID;
	}
}
