
package com.teamcenter.getrans;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.teamcenter.services.strong.core.ProjectLevelSecurityService;
import com.teamcenter.services.strong.core._2009_10.ProjectLevelSecurity.ProjectInfo;
import com.teamcenter.services.strong.core._2009_10.ProjectLevelSecurity.UserProjectsInfoInput;
import com.teamcenter.services.strong.core._2009_10.ProjectLevelSecurity.UserProjectsInfoResponse;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.ModifyProjectsInfo;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.ProjectClientId;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.ProjectInformation;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.ProjectOpsResponse;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.ProjectTeamsResponse;
import com.teamcenter.services.strong.core._2012_09.ProjectLevelSecurity.TeamMemberInfo;
import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.strong.Group;
import com.teamcenter.soa.client.model.strong.GroupMember;
import com.teamcenter.soa.client.model.strong.ProjectTeam;
import com.teamcenter.soa.client.model.strong.TC_Project;
import com.teamcenter.soa.client.model.strong.User;

/**
 * Class to perform different operations in the DataManagementService
 *
 *@author TCSL
 */
public class GETProjectManagement
{
    private Connection connection;

	private ProjectLevelSecurityService projectLevelSecurityService;

	private static final String clientID = "GETTransPLMLite";

	private static Map<Connection, GETProjectManagement> m_instance;

	/**
	* Constructor for the class GETOrijectManagement. This is a private constructor that cannot be called from outside this class
	* 
	* @param connection - Connection object for the session
	*/
	private GETProjectManagement(Connection connection)
	{
	    projectLevelSecurityService = ProjectLevelSecurityService.getService(connection);
	    this.connection = connection;
	}

	/**
	* Static Singleton method to return the instance of the class GETProjectManagement.
	*
	* @param connection - Connection object for the session
	* @return an instance of the class GETProjectManagement
	*/
	public static GETProjectManagement getProjectManagementService(Connection connection)
	{
    	GETProjectManagement returnInstance = null;
    	if(m_instance == null)
    	{
        	m_instance = new HashMap<Connection, GETProjectManagement>();
    	}
    	if (m_instance.containsKey(connection))
        {
            returnInstance = m_instance.get(connection);
        }
    	else
    	{
        	returnInstance = new GETProjectManagement(connection);
        	m_instance.put(connection, returnInstance);
    	}

    	return returnInstance;
	}

    /**
    * Method to find TC Projects based on the Project ID
    *
    * @param projectID - The Project ID of the project to be found 
    * @return The ModelObject array for the projects found
    */
	public ModelObject[] findProjectsByID(String projectID) throws Exception
	{
	    GETQuery queryService = GETQuery.getInstance(connection);
        return queryService.queryObject(GETConstants.Query.strProjectsQueryName,
                                                          new String[] { GETConstants.Query.projectId },
                                                          new String[] { projectID });
	}

	/**
	 * Method to Update the Teamcenter Project Team Members
	 *
	 * @param projectID - The String Project ID of the Teamcenter Project to be updated
	 * @param toBeAddedRegularUsers - An array of String user names to be added as regular users
	 * @param toBeRemovedRegularUsers - An array of String user names of regular users to be removed from the given project
	 * @param toBeAddedPrivilegedUsers - An array of String user names to be added as privileged users
	 * @param toBeRemovedPrivilegedUsers - An array of String user names of privileged users to be removed from the given project
	 * @param toBeAddedTeamAdminUsers - An array of String user names to be added as team admin users
	 * @param toBeRemovedTeamAdminUsers - An array of String user names of team admin users to be removed from the given project
	 * @param isOverride - The boolean flag indicating whether to override existing member data in the Project
     * @return - A boolean flag indicating whether the Project information is updated (true) or not (false) during this operation
     * @throws Exception - Any Teamcenter/User error that may occur during the operation
	 */
	public boolean updateProjectTeam(String projectID,
	                                 String[] toBeAddedRegularUsers, String[] toBeRemovedRegularUsers,
	                                 String[] toBeAddedPrivilegedUsers, String[] toBeRemovedPrivilegedUsers,
	                                 String[] toBeAddedTeamAdminUsers, String[] toBeRemovedTeamAdminUsers,
	                                 boolean isOverride) throws Exception
	{

        // Find the Project
        ModelObject[] projects = findProjectsByID(projectID);
        if (projects == null || projects.length == 0)
        {
            throw new Exception("Project with the given id " + projectID + " does not exist");
        }
        TC_Project tcProject = (TC_Project) projects[0];
        return updateProjectTeam(tcProject,
                                 toBeAddedRegularUsers, toBeRemovedRegularUsers,
                                 toBeAddedPrivilegedUsers, toBeRemovedPrivilegedUsers,
                                 toBeAddedTeamAdminUsers, toBeRemovedTeamAdminUsers,
                                 isOverride);
	}

    /**
     * Method to Update the Teamcenter Project Team Members
     *
     * @param projectID - The Teamcenter Project (TC_project) object to be updated
     * @param toBeAddedRegularUsers - An array of String user names to be added as regular users
     * @param toBeRemovedRegularUsers - An array of String user names of regular users to be removed from the given project
     * @param toBeAddedPrivilegedUsers - An array of String user names to be added as privileged users
     * @param toBeRemovedPrivilegedUsers - An array of String user names of privileged users to be removed from the given project
     * @param toBeAddedTeamAdminUsers - An array of String user names to be added as team admin users
     * @param toBeRemovedTeamAdminUsers - An array of String user names of team admin users to be removed from the given project
     * @param isOverride - The boolean flag indicating whether to override existing member data in the Project
     * @return - A boolean flag indicating whether the Project information is updated (true) or not (false) during this operation
     * @throws Exception - Any Teamcenter/User error that may occur during the operation
     */
    public boolean updateProjectTeam(TC_Project tcProject,
                                  String[] toBeAddedRegularUsers, String[] toBeRemovedRegularUsers,
                                  String[] toBeAddedPrivUsers, String[] toBeRemovedPrivUsers,
                                  String[] toBeAddedTeamAdminUsers, String[] toBeRemovedTeamAdminUsers,
                                  boolean isOverride) throws Exception
    {
        GETProjectData toBeAddedData = null;
        GETProjectData toBeRemovedData = null;

        List<ModelObject> toBeAddedRegularMembers = null;
        List<ModelObject> toBeRemovedRegularMembers = null;
        List<ModelObject> toBeAddedPrivilegedMembers = null;
        List<ModelObject> toBeRemovedPrivilegedMembers = null;
        List<ModelObject> toBeAddedTeamAdminMembers = null;
        List<ModelObject> toBeRemovedTeamAdminMembers = null;

        GETDataManagement dataMgmtInst = GETDataManagement.getDMService(connection);
        GETUserAdministration usrAdminInst = GETUserAdministration.getService(connection);

        // Process To Be Added Regular Users
        if (toBeAddedRegularUsers != null && toBeAddedRegularUsers.length > 0)
        {
            for (String userId : toBeAddedRegularUsers)
            {
                // check if user exists
                ModelObject user = usrAdminInst.getUser(userId);
                if (user == null)
                {
                    continue;
                }
                dataMgmtInst.getProperties(new ModelObject[]{user}, new String[]{GETConstants.BusinessObjects.Properties.defaultGroup});
                ModelObject defaultGroup = (((User) user).get_default_group());
                dataMgmtInst.getProperties(new ModelObject[] {defaultGroup},
                                           new String[] {GETConstants.BusinessObjects.Properties.fullName});
                String groupName = ((Group) defaultGroup).get_full_name();
                ModelObject[] groupMembers = usrAdminInst.getUserGroupMembers(userId, groupName, null, null, "0");
                if (groupMembers == null || groupMembers.length == 0)
                {
                    throw new Exception("Unable to retrieve the group member information for the user with id " + userId + ". Please contact the system administrator");
                }
                dataMgmtInst.getProperties(groupMembers,
                                           new String[] { GETConstants.BusinessObjects.Properties.group });
                for (ModelObject groupMember : groupMembers)
                {
                    // If the GroupMember is an instance of project team, skip it
                    ModelObject tempGroupObj = ((GroupMember) groupMember).get_group();
                    if (tempGroupObj instanceof ProjectTeam)
                    {
                        continue;
                    }
                    if (toBeAddedRegularMembers == null)
                    {
                        toBeAddedRegularMembers = new ArrayList<ModelObject>();
                    }
                    toBeAddedRegularMembers.add(groupMember);
                    break;
                }
                if (toBeAddedRegularMembers == null)
                {
                    throw new Exception("User with id " + userId + " is not part of any group/role. Please contact the system administrator");
                }
            }
        }

        // Process To Be Removed Regular Users
        if (toBeRemovedRegularUsers != null && toBeRemovedRegularUsers.length > 0)
        {
            for (String userId : toBeRemovedRegularUsers)
            {
                ModelObject[] groupMembers = usrAdminInst.getUserGroupMembers(userId, null, null, null, "0");
                if (groupMembers == null || groupMembers.length == 0)
                {
                    continue;
                }
                if (toBeRemovedRegularMembers == null)
                {
                    toBeRemovedRegularMembers = new ArrayList<ModelObject>();
                }
                toBeRemovedRegularMembers.addAll(Arrays.asList(groupMembers));
            }
        }

        // Process To Be Added Privilege Users
        if (toBeAddedPrivUsers != null && toBeAddedPrivUsers.length > 0)
        {
            for (String userId : toBeAddedPrivUsers)
            {
                // check if user exists
                ModelObject user = usrAdminInst.getUser(userId);
                if (user == null)
                {
                    continue;
                }
                if (toBeAddedPrivilegedMembers == null)
                {
                    toBeAddedPrivilegedMembers = new ArrayList<ModelObject>();
                }
                toBeAddedPrivilegedMembers.add(user);
            }
        }

        // Process To Be Removed Privilege Users
        if (toBeRemovedPrivUsers != null && toBeRemovedPrivUsers.length > 0)
        {
            for (String userId : toBeRemovedPrivUsers)
            {
                // check if user exists
                ModelObject user = usrAdminInst.getUser(userId);
                if (user == null)
                {
                    continue;
                }
                if (toBeRemovedPrivilegedMembers == null)
                {
                    toBeRemovedPrivilegedMembers = new ArrayList<ModelObject>();
                }
                toBeRemovedPrivilegedMembers.add(user);
            }
        }

        // Process To Be Added Team Admin Users
        if (toBeAddedTeamAdminUsers != null && toBeAddedTeamAdminUsers.length > 0)
        {
            for (String userId : toBeAddedTeamAdminUsers)
            {
                // check if user exists
                ModelObject user = usrAdminInst.getUser(userId);
                if (user == null)
                {
                    continue;
                }
                if (toBeAddedTeamAdminMembers == null)
                {
                    toBeAddedTeamAdminMembers = new ArrayList<ModelObject>();
                }
                toBeAddedTeamAdminMembers.add(user);
            }
        }

        // Process To Be Removed Team Admin Users
        if (toBeRemovedTeamAdminUsers != null && toBeRemovedTeamAdminUsers.length > 0)
        {
            for (String userId : toBeRemovedTeamAdminUsers)
            {
                // check if user exists
                ModelObject user = usrAdminInst.getUser(userId);
                if (user == null)
                {
                    continue;
                }
                if (toBeRemovedTeamAdminMembers == null)
                {
                    toBeRemovedTeamAdminMembers = new ArrayList<ModelObject>();
                }
                toBeRemovedTeamAdminMembers.add(user);
            }
        }

        // Create the Project Data Structures
        toBeAddedData = new GETProjectData(null, toBeAddedRegularMembers, toBeAddedPrivilegedMembers, toBeAddedTeamAdminMembers);
        toBeRemovedData = new GETProjectData(null, toBeRemovedRegularMembers, toBeRemovedPrivilegedMembers, toBeRemovedTeamAdminMembers);

        return updateProjectTeam(tcProject, toBeAddedData, toBeRemovedData, isOverride);
    }

	/**
	 * Method to update Teamcenter Project Team data
	 *
	 * @param projectID - The Project ID of the Project to be updated
	 * @param toBeAddedData - The GETProjectData structure containing the member information to be added to the Project
	 * @param toBeRemovedData - The GETProjectData structure containing the member information to be removed to the Project
	 * @param isOverride - The boolean flag indicating whether to override existing member data in the Project
     * @return - A boolean flag indicating whether the Project information is updated (true) or not (false) during this operation
     * @throws Exception - Any Teamcenter/User error that may occur during the operation
	 */
    public boolean updateProjectTeam(String projectID, GETProjectData toBeAddedData, GETProjectData toBeRemovedData, boolean isOverride) throws Exception
    {
        // Find the Project
        ModelObject[] projects = findProjectsByID(projectID);
        if (projects == null || projects.length == 0)
        {
            throw new Exception("Project with the given id " + projectID + " does not exist");
        }
        TC_Project tcProject = (TC_Project) projects[0];

        return updateProjectTeam(tcProject, toBeAddedData, toBeRemovedData, isOverride);
    }

    /**
     * Method to update Teamcenter Project Team data
     *
     * @param tcProject - The Teamcenter Project Object to be updated
     * @param toBeAddedData - The GETProjectData structure containing the member information to be added to the Project
     * @param toBeRemovedData - The GETProjectData structure containing the member information to be removed to the Project
     * @param isOverride - The boolean flag indicating whether to override existing member data in the Project
     * @return isUpdated - A boolean flag indicating whether the Project information is updated (true) or not (false) during this operation
     * @throws Exception - Any Teamcenter/User error that may occur during the operation
     */
    public boolean updateProjectTeam(TC_Project tcProject, GETProjectData toBeAddedData, GETProjectData toBeRemovedData, boolean isOverride) throws Exception
    {
        boolean isUpdated = false;

        ModelObject[] regularMembers = null;
        ModelObject[] privilegedMembers = null;
        ModelObject[] teamAdministrators = null;

        List<ModelObject> regularMembersList = null;
        List<ModelObject> privilegedMembersList = null;
        List<ModelObject> teamAdministratorsList = null;

        GETDataManagement dataMgmtInst = GETDataManagement.getDMService(connection);
        dataMgmtInst.getProperties(new ModelObject[] { tcProject },
                                   new String[] { GETConstants.BusinessObjects.Properties.projectId,
                                                  GETConstants.BusinessObjects.Properties.projectName,
                                                  GETConstants.BusinessObjects.Properties.projectDesc,
                                                  GETConstants.BusinessObjects.Properties.isActive,
                                                  GETConstants.BusinessObjects.Properties.isVisible,
                                                  GETConstants.BusinessObjects.Properties.useProgramSecurity});
        String projectID = tcProject.get_project_id();
        String projectName = tcProject.get_project_name();
        String projectDesc = tcProject.get_project_desc();
        boolean isActive = tcProject.get_is_active();
        boolean isVisible = tcProject.get_is_visible();
        boolean useProgramSecurity = tcProject.get_use_program_security();

        // Get the Project Members Data
        GETProjectData projectData = getProjectTeams(tcProject);
        regularMembersList = new ArrayList<ModelObject>();
        privilegedMembersList = new ArrayList<ModelObject>();
        teamAdministratorsList = new ArrayList<ModelObject>();

        if (toBeAddedData != null && toBeAddedData.getRegularMembers() != null)
        {
            regularMembersList.addAll(toBeAddedData.getRegularMembers());
            isUpdated = true;
        }
        if (toBeAddedData != null && toBeAddedData.getPrivilegedMembers() != null)
        {
            privilegedMembersList.addAll(toBeAddedData.getPrivilegedMembers());
            isUpdated = true;
        }
        if (toBeAddedData != null && toBeAddedData.getTeamAdministrators() != null)
        {
            teamAdministratorsList.addAll(toBeAddedData.getTeamAdministrators());
            isUpdated = true;
        }

        if (!isOverride)
        {
            if (projectData.getRegularMembers() != null)
            {
                regularMembersList.addAll(projectData.getRegularMembers());
            }
            if (toBeRemovedData != null && toBeRemovedData.getRegularMembers() != null)
            {
                for (ModelObject modelObject : toBeRemovedData.getRegularMembers())
                {
                    if (regularMembersList.contains(modelObject))
                    {
                        regularMembersList.remove(modelObject);
                        isUpdated = true;
                    }
                }
            }

            if (projectData.getPrivilegedMembers() != null)
            {
                privilegedMembersList.addAll(projectData.getPrivilegedMembers());
            }
            if (toBeRemovedData != null && toBeRemovedData.getPrivilegedMembers() != null)
            {
                for (ModelObject modelObject : toBeRemovedData.getPrivilegedMembers())
                {
                    if (privilegedMembersList.contains(modelObject))
                    {
                        privilegedMembersList.remove(modelObject);
                        isUpdated = true;
                    }
                }
            }

            if (projectData.getTeamAdministrators() != null)
            {
                teamAdministratorsList.addAll(projectData.getTeamAdministrators());
            }
            if (toBeRemovedData != null && toBeRemovedData.getTeamAdministrators() != null)
            {
                for (ModelObject modelObject : toBeRemovedData.getTeamAdministrators())
                {
                    if (teamAdministratorsList.contains(modelObject))
                    {
                        teamAdministratorsList.remove(modelObject);
                        isUpdated = true;
                    }
                }
            }
        }
        else
        {
            isUpdated = true;
        }

        if (regularMembersList.size() > 0)
        {
            regularMembers = regularMembersList.toArray(new ModelObject[regularMembersList.size()]);
        }
        if (privilegedMembersList.size() > 0)
        {
            privilegedMembers = privilegedMembersList.toArray(new ModelObject[privilegedMembersList.size()]);
        }
        if (teamAdministratorsList.size() > 0)
        {
            teamAdministrators = teamAdministratorsList.toArray(new ModelObject[teamAdministratorsList.size()]);
        }

        // Construct the inputs required for modifying the Project
        List<TeamMemberInfo> teamMemberInfoList = new ArrayList<TeamMemberInfo>();
        if (regularMembers != null)
        {
            for (ModelObject regularMember : regularMembers)
            {
                TeamMemberInfo info = new TeamMemberInfo();
                info.teamMember = regularMember;
                info.teamMemberType = 0;
                teamMemberInfoList.add(info);
            }
        }
        if (privilegedMembers != null)
        {
            for (ModelObject privilegedMember : privilegedMembers)
            {
                TeamMemberInfo info = new TeamMemberInfo();
                info.teamMember = privilegedMember;
                info.teamMemberType = 1;
                teamMemberInfoList.add(info);
            }
        }
        if (teamAdministrators != null)
        {
            for (ModelObject teamAdministrator : teamAdministrators)
            {
                TeamMemberInfo info = new TeamMemberInfo();
                info.teamMember = teamAdministrator;
                info.teamMemberType = 2;
                teamMemberInfoList.add(info);
            }
        }
        TeamMemberInfo[] teamMemberInfoArray = teamMemberInfoList.toArray(new TeamMemberInfo[teamMemberInfoList.size()]);
        ProjectInformation projectInfo = new ProjectInformation();
        projectInfo.clientId = clientID;
        projectInfo.projectId = projectID;
        projectInfo.projectName = projectName;
        projectInfo.projectDescription = projectDesc;
        projectInfo.active = isActive;
        projectInfo.visible = isVisible;
        projectInfo.useProgramContext = useProgramSecurity;
        projectInfo.teamMembers = teamMemberInfoArray;
        ModifyProjectsInfo modProjInfo = new ModifyProjectsInfo();
        modProjInfo.clientId = clientID;
        modProjInfo.sourceProject = tcProject;
        modProjInfo.projectInfo = projectInfo;

        // Modify the Project
        ProjectOpsResponse response = projectLevelSecurityService.modifyProjects(new ModifyProjectsInfo[] { modProjInfo });
        if (response != null)
        {
            String errorMsg = GETCommon.getErrorFromServiceData(response.serviceData);
            if (errorMsg != null)
            {
                throw new Exception(errorMsg);
            }
        }

        return isUpdated;
    }

    /**
     * Method to get the Projects teams of the given Teamcenter Project
     *
     * @param project - The Teamcenter Project object (TC_project) whose team member information is required
     * @return - The GETProjectData structure containing the details of the team members
     * @throws Exception - Any Teamcenter/User error that may occur during the operation
     */
	public GETProjectData getProjectTeams(TC_Project project) throws Exception
	{
	    GETProjectData projectData = null;

	    ProjectClientId[] input = new ProjectClientId[1];
	    input[0] = new ProjectClientId();
	    input[0].clientId = clientID;
	    input[0].tcProject = project;
	    ProjectTeamsResponse response = projectLevelSecurityService.getProjectTeams(input);
	    if (response != null)
	    {
	        String errorMsg = GETCommon.getErrorFromServiceData(response.serviceData);
            if (errorMsg != null)
            {
                throw new Exception(errorMsg);
            }
            if (response.projectTeams != null && response.projectTeams.length > 0)
            {
                projectData = new GETProjectData(response.projectTeams[0].project, response.projectTeams[0].regularMembers,
                                                 response.projectTeams[0].privMembers, response.projectTeams[0].projectTeamAdmins);
            }
	    }

	    return projectData;
	}

	/**
	 * Method to get the Project Member information of the given Teamcenter User
	 *
	 * @param user - The Teamcenter user object (User) whose Project Member information is required
	 * @param activeProjectsOnly - A boolean flag indicating whether we need only active projects or not
	 * @param privilegedProjectsOnly - A boolean flag indicating whether we need only information about projects where the user is a privileged user
	 * @param programsOnly -  - A boolean flag indicating whether we need only information about projects of the type Program
	 * @return - An array of ProjectInfo structure containing the member information for the given Teamcenter User
     * @throws Exception - Any Teamcenter/User error that may occur during the operation
	 */
	public ProjectInfo[] getUserProjects(User user, boolean activeProjectsOnly, boolean privilegedProjectsOnly, boolean programsOnly) throws Exception
	{
	    ProjectInfo[] projectInfo = null;

	    UserProjectsInfoInput[] inputs = new UserProjectsInfoInput[1];
	    inputs[0] = new UserProjectsInfoInput();
	    inputs[0].activeProjectsOnly = activeProjectsOnly;
	    inputs[0].clientId = clientID;
	    inputs[0].privilegedProjectsOnly = privilegedProjectsOnly;
	    inputs[0].programsOnly = programsOnly;
	    inputs[0].user = user;
	    UserProjectsInfoResponse response = projectLevelSecurityService.getUserProjects(inputs);
        if (response != null)
        {
            String errorMsg = GETCommon.getErrorFromServiceData(response.serviceData);
            if (errorMsg != null)
            {
                throw new Exception(errorMsg);
            }
            if (response.userProjectInfos != null && response.userProjectInfos.length > 0 &&
                response.userProjectInfos[0].projectsInfo != null && response.userProjectInfos[0].projectsInfo.length > 0)
            {
                projectInfo = response.userProjectInfos[0].projectsInfo;
            }
        }

        return projectInfo;
	}

	/**
	 * Method to find whether the user is a member of the given Teamcenter Project
	 *
	 * @param user - The Teamcenter User instance of the user to be checked
	 * @param projectID - The String ID of the Teamcenter Project to be checked
	 * @return boolean indicating whether the user is a member (true) or not (false)
     * @throws Exception - Any Teamcenter/User error that may occur during the operation
	 */
	public boolean isUserProjectMember(User user, String projectID) throws Exception
	{
	    boolean isUserProjectMember = false;

	    ProjectInfo[] projectsInfo = getUserProjects(user, false, false, false);
	    if (projectsInfo != null && projectsInfo.length > 0)
	    {
	        TC_Project[] projectsArray = new TC_Project[projectsInfo.length];

	        for (int index = 0; index < projectsInfo.length; index++)
	        {
	            projectsArray[index] = projectsInfo[index].project;
	        }
	        GETDataManagement dataMgmtInst = GETDataManagement.getDMService(connection);
	        dataMgmtInst.getProperties(projectsArray,
	                                   new String[] { GETConstants.BusinessObjects.Properties.projectId });
	        for (TC_Project tcProject : projectsArray)
	        {
	            if (tcProject.get_project_id().equals(projectID))
	            {
	                isUserProjectMember = true;
	                break;
	            }
	        }
	    }

	    return isUserProjectMember;
	}
}
