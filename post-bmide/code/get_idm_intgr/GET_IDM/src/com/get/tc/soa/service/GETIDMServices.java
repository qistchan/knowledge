
//==================================================
// 
//  Copyright 2016 GE Transportation. All Rights Reserved.
//
//==================================================

package com.get.tc.soa.service;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import com.teamcenter.getrans.GETCommon;
import com.teamcenter.getrans.GETConstants;
import com.teamcenter.getrans.GETDataManagement;
import com.teamcenter.getrans.GETProjectData;
import com.teamcenter.getrans.GETProjectManagement;
import com.teamcenter.getrans.GETQuery;
import com.teamcenter.getrans.GETUserAdministration;
import com.teamcenter.getrans.clientx.GETSession;
import com.teamcenter.services.strong.core._2009_10.ProjectLevelSecurity.ProjectInfo;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.ServiceData;
import com.teamcenter.soa.client.model.strong.Group;
import com.teamcenter.soa.client.model.strong.GroupMember;
import com.teamcenter.soa.client.model.strong.Person;
import com.teamcenter.soa.client.model.strong.ProjectTeam;
import com.teamcenter.soa.client.model.strong.Role;
import com.teamcenter.soa.client.model.strong.TC_Project;
import com.teamcenter.soa.client.model.strong.User;

/**
 * This is the main class that has the implementation methods for all the IDM Services
 *
 * @author TCS Development Team
 *
 */
public class GETIDMServices
{
    private static final String groupNameAppend = GETConstants.Symbols.strDot + GroupDetails.transportationGroupName + GETConstants.Symbols.strDot + GroupDetails.GETransportationGroupName;

    private GETSession m_sessionObj = null;

    private String m_host;

    /**
     * Method to set the Teamcenter Server Host
     *
     * @param host - The String Teamcenter Server Host (http://<Machine>:<Port>/<tc_ear_file_name>)
     */
    public void setHost(String host)
    {
        m_host = host;
    }

    /**
     * Method to login to Teamcenter
     *
     * @param m_userID - The Teamcenter User ID to be used for login
     * @param m_password - The Teamcenter Password for the given User
     * @param m_group - The The Teamcenter login group for the given User
     * @throws Exception - Any exceptions that my occur in Teamcenter during this operation
     */
    public void login(String m_userID, String m_password, String m_group) throws Exception
    {
        String strErrorMessage = GETConstants.Symbols.strEmptyString;
        m_sessionObj = new GETSession(m_host);
        strErrorMessage = this.m_sessionObj.login(m_userID, m_password, m_group);
        if (strErrorMessage != null && !strErrorMessage.isEmpty())
        {
            throw new Exception(strErrorMessage);
        }
        setObjectPolicy();
    }

    /**
     * Default no parameter constructor that will be used by the IDM Services
     */
    public GETIDMServices()
    {
    }

    /**
     * Constructor for the GETIDMServices class
     * 
     * @param session - The GETSession to be used for this Teamcenter session
     * @param host - The String Teamcenter Server Host (http://<Machine>:<Port>/<tc_ear_file_name>)
     */
    public GETIDMServices(GETSession session, String host)
    {
        m_sessionObj = session;
        m_host = host;
        setObjectPolicy();
    }

    /**
     * Constructor for the GETIDMServices class
     * 
     * @param session - The GETSession to be used for this Teamcenter session
     */
    public GETIDMServices(GETSession session)
    {
        m_sessionObj = session;
        setObjectPolicy();
    }

    /**
     * Method to set the GETSession to be used for this Teamcenter session
     *
     * @param session - The input GETSession instance corresponding to the current Teamcenter sessoin
     */
    public void setSession(GETSession session)
    {
        m_sessionObj = session;
        setObjectPolicy();
    }

    /**
     * Method to logout of the current Teamcenter session
     */
    public void logout()
    {
        if (m_sessionObj != null)
        {
            m_sessionObj.logout();
            m_sessionObj = null;
        }
    }

    /**
     * Private method to set the Object Property Policy for the current Teamcenter session
     */
    private void setObjectPolicy()
    {
        GETCommon commonObj = GETCommon.getInstance(m_sessionObj.getConnection());

        Map<String, String[]> typePropsMap = new HashMap<String, String[]>();

        typePropsMap.put(GETConstants.BusinessObjects.group, new String[]
        { GETConstants.BusinessObjects.Properties.listOfRoles,
          GETConstants.BusinessObjects.Properties.fullName,
          GETConstants.BusinessObjects.Properties.displayName });
        typePropsMap.put(GETConstants.BusinessObjects.role, new String[]
        { GETConstants.BusinessObjects.Properties.strObjectName });
        typePropsMap.put(GETConstants.BusinessObjects.user, new String[]
        { GETConstants.BusinessObjects.Properties.strUserName,
          GETConstants.BusinessObjects.Properties.ipClearance,
          GETConstants.BusinessObjects.Properties.status,
          GETConstants.BusinessObjects.Properties.strUserName,
          GETConstants.BusinessObjects.Properties.person });
        typePropsMap.put(GETConstants.BusinessObjects.person, new String[]
        { GETConstants.BusinessObjects.Properties.strUserName,
          GETConstants.BusinessObjects.Properties.strPA9,
          GETConstants.BusinessObjects.Properties.strOwningUser,
          GETConstants.BusinessObjects.Properties.strCreationDate,
          GETConstants.BusinessObjects.Properties.strLastModDate,
          GETConstants.BusinessObjects.user,
          GETConstants.BusinessObjects.Properties.strLastModUser,
          GETConstants.BusinessObjects.Properties.strObjectString });
        typePropsMap.put(GETConstants.BusinessObjects.groupMember, new String[]
        { GETConstants.BusinessObjects.Properties.group,
          GETConstants.BusinessObjects.Properties.user,
          GETConstants.BusinessObjects.Properties.status,
          GETConstants.BusinessObjects.Properties.defaultRole,
          GETConstants.BusinessObjects.Properties.strObjectName,
          GETConstants.BusinessObjects.Properties.strUserName,
          GETConstants.BusinessObjects.Properties.role,
          GETConstants.BusinessObjects.Properties.theGroup,
          GETConstants.BusinessObjects.Properties.theRole });

        commonObj.setObjectPolicy(typePropsMap);
    }

    /**
     * Private method to get the Project Name from the IP Classification value and the group name
     * 
     * @param projectGroup - The String Parent Group name
     * @param ipClassification - The String IP Classification attribute value
     * @return The String Project Name constructed from the Parent Group and IP Classification value
     */
    private String getProjectFromIP(String projectGroup, String ipClassification)
    {
        String projectName = null;

        StringBuilder projectNameBuilder = new StringBuilder();

        if (ipClassification.toUpperCase().equals(GETConstants.LOV.IP_CLASS_CONFIDENTIAL_LOV_VALUE.toUpperCase()))
        {
            projectNameBuilder.append(projectGroup).append(" - (C");
        }
        else if (ipClassification.toUpperCase().equals(GETConstants.LOV.IP_CLASS_RESTRICTED_LOV_VALUE.toUpperCase()))
        {
            projectNameBuilder.append(projectGroup).append(" - (R");
        }
        if (!projectNameBuilder.toString().isEmpty())
        {
            projectName = projectNameBuilder.append(")").toString();
        }

        return projectName;
    }

    /**
     * Method to find a Teamcenter Group given the full name of the group
     *
     * @param groupName - The String Teamcenter Group ID
     * @return group - The Teamcenter Group object matching the given group name
     * @throws Exception - Any Teamcenter error that may occur during this operation
     */
    private Group findGroup(String groupName) throws Exception
    {
        Group group = null;

        String grpName = null;

        String grpSplit[] = groupName.split("\\.");
        if (grpSplit.length > 0)
        {
            grpName = grpSplit[0];
        }
        else
        {
            grpName = groupName;
        }

        GETQuery queryService = GETQuery.getInstance(m_sessionObj.getConnection());
        ModelObject[] foundGrps = queryService.queryObject(GETConstants.Query.grpByNameQuery,
                                                           new String[] { GETConstants.Query.name },
                                                           new String[] { grpName + GETConstants.Symbols.strSingleStarDelimiter });
        if (foundGrps != null)
        {
            for (ModelObject mo : foundGrps)
            {
                if (((Group)mo).get_full_name().equals(groupName))
                {
                    group = (Group) mo;
                    break;
                }
            }
        }

        return group;
    }

    /**
     * Method to validate the input Group/Role to find out if the group/role names correspond to actual Teamcenter group/role names
     *
     * @param groupName - The String Teamcenter Group ID
     * @param roleName - The String Teamcenter Role name
     * @throws Exception - Any Teamcenter error that may occur during this operation
     */
    private void validateRoleInGroup(String groupName, String roleName) throws Exception
    {
        Group group = findGroup(groupName);
        if (group == null)
        {
            throw new Exception("Given group " + groupName + " with the matching hierarchy does not exist");
        }

        GETQuery queryService = GETQuery.getInstance(m_sessionObj.getConnection());
        ModelObject[] foundRoles = queryService.queryObject(GETConstants.Query.roleByNameQuery,
                                                            new String[] { GETConstants.Query.name },
                                                            new String[] { roleName });

        if (foundRoles == null)
        {
            throw new Exception("Given role " + roleName + " does not exist");
        }

        Role[] rolesInGrp = group.get_list_of_role();
        if (!Arrays.asList(rolesInGrp).contains(foundRoles[0]))
        {
            throw new Exception("Given role " + roleName + " does not exist under the given group " + groupName);
        }
    }

    /**
     * Method to query whether a given Teamcenter User is active or not
     *
     * @param userId - The String Teamcenter User ID whose active status is required
     * @return - A boolean indicating whether the User is active or not (true/false)
     * @throws Exception - Any Teamcenter error that may occur during this operation
     */
    public boolean isUserActive(String userId) throws Exception
    {
        boolean status = false;

        GETDataManagement dataMgmt = GETDataManagement.getDMService(m_sessionObj.getConnection());

        GETUserAdministration usrAdminInst = GETUserAdministration.getService(m_sessionObj.getConnection());
        User user = (User) usrAdminInst.getUser(userId);
        if (user == null)
        {
            throw new Exception("Given user " + userId + " does not exist");
        }
        dataMgmt.getProperties(new ModelObject[] {user},
                               new String[] {GETConstants.BusinessObjects.Properties.status});
        status = (user.get_status() == 0) ? true : false;

        return status;
    }

    /**
     * Method to get a list of active Teamcenter Users in a predefined structure
     *
     * @return A List containing UserDetails structure containing information about the active Teamcenter users
     * @throws Exception - Any Teamcenter error that may occur during this operation
     */
    public List<UserDetails> getActiveUsers() throws Exception
    {
        List<UserDetails> userDetailsList = null;

        Map<String, User> userMap = null;

        Map<String, UserDetails> userDetailsMap = null;

        GETDataManagement dataMgmt = GETDataManagement.getDMService(m_sessionObj.getConnection());
        GETUserAdministration usrAdminInst = GETUserAdministration.getService(m_sessionObj.getConnection());

        ModelObject[] modelObjectMembers = usrAdminInst.getUserGroupMembers(GETConstants.Symbols.strSingleStarDelimiter, null, null, "0", "0");
        if (modelObjectMembers != null && modelObjectMembers.length > 0)
        {
            dataMgmt.getProperties(modelObjectMembers, new String[] { GETConstants.BusinessObjects.Properties.group, GETConstants.BusinessObjects.Properties.user });
            for (ModelObject modelObjectMember : modelObjectMembers)
            {
                String firstName = null;
                String lastName = null;
                String groupName = null;
                String group = null;
                String role = null;
                String createdUser = null;
                String modifiedUser = null;

                int status = 0;

                if (modelObjectMember != null)
                {
                    GroupMember grpMember = (GroupMember) modelObjectMember;
                    Group grp = (Group) grpMember.get_group();
                    if (grp instanceof ProjectTeam)
                    {
                        continue;
                    }
                    User user = (User) grpMember.get_user();
                    dataMgmt.getProperties(new ModelObject[] { user },
                                           new String[] { GETConstants.BusinessObjects.Properties.strUserName,
                                                          GETConstants.BusinessObjects.Properties.person,
                                                          GETConstants.BusinessObjects.Properties.status,
                                                          GETConstants.BusinessObjects.Properties.strUserID,
                                                          GETConstants.BusinessObjects.Properties.strObjectString });

                    // If the User Id contains alphabetic characters, skip it
                    try
                    {
                        Integer.parseInt(user.get_user_id());
                    }
                    catch (NumberFormatException nfe)
                    {
                        continue;
                    }
                    Person person = (Person) user.get_person();

                    dataMgmt.getProperties(new ModelObject[] { person },
                                           new String[] { GETConstants.BusinessObjects.Properties.strUserName,
                                                          GETConstants.BusinessObjects.Properties.strPA5,
                                                          GETConstants.BusinessObjects.Properties.strPA9,
                                                          GETConstants.BusinessObjects.Properties.strOwningUser,
                                                          GETConstants.BusinessObjects.Properties.strCreationDate,
                                                          GETConstants.BusinessObjects.Properties.strLastModDate,
                                                          GETConstants.BusinessObjects.user,
                                                          GETConstants.BusinessObjects.Properties.strLastModUser,
                                                          GETConstants.BusinessObjects.Properties.strObjectString });

                    User owningUser = (User) person.get_owning_user();
                    User lastModifiedUser = (User) person.get_last_mod_user();

                    dataMgmt.getProperties(new ModelObject[] { owningUser, lastModifiedUser },
                                           new String[] { GETConstants.BusinessObjects.Properties.strUserName,
                                                          GETConstants.BusinessObjects.Properties.person,
                                                          GETConstants.BusinessObjects.Properties.status,
                                                          GETConstants.BusinessObjects.Properties.strUserID,
                                                          GETConstants.BusinessObjects.Properties.strObjectString });

                    dataMgmt.getProperties(new ModelObject[] { grp },
                                           new String[] { GETConstants.BusinessObjects.Properties.fullName,
                                                          GETConstants.BusinessObjects.Properties.theRole });
                    // String objectName = grpMember.get_object_name();

                    createdUser = owningUser.get_object_string();
                    modifiedUser = lastModifiedUser.get_object_string();
                    String persons[] = person.get_user_name().split(",");
                    if (persons.length > 1)
                    {
                        lastName = persons[0];
                        firstName = persons[1];
                    }
                    else
                    {
                        firstName = person.get_user_name();
                        lastName = "";
                    }

                    status = user.get_status();
                    if (grpMember.get_the_role() != null)
                    {
                        Role roleObject = (Role) grpMember.get_the_role();
                        dataMgmt.getProperties(new ModelObject[] { roleObject },
                                               new String[] { GETConstants.BusinessObjects.Properties.strObjectName });
                        role = roleObject.get_object_name();
                    }
                    group = grp.get_full_name();
                    if (group != null && !group.isEmpty() && group.contains(GroupDetails.GETransportationGroupName))
                    {
                        int ipIndex = 0;

                        String spiltGrp[] = group.split("\\.");
                        if (spiltGrp.length > 1)
                        {
                            groupName = spiltGrp[(spiltGrp.length) - 1];
                            for (int groupCount = ((spiltGrp.length) - 1); groupCount > 0; groupCount--)
                            {
                                ipIndex++;
                                groupName = groupName + GETConstants.Symbols.strColon + spiltGrp[groupCount - 1];
                                if (ipIndex == 3)
                                {
                                    groupName = groupName + GETConstants.Symbols.strColon + "N/A";
                                }
                            }
                        }
                        groupName = groupName.replace(GroupDetails.GETransportationGroupName + GETConstants.Symbols.strColon +
                                GroupDetails.transportationGroupName + GETConstants.Symbols.strColon, "");
                        String[] temp = groupName.split(GETConstants.Symbols.strColon);
                        int groupColonCount = 5 - temp.length;
                        for (int groupCount = 0; groupCount < groupColonCount; groupCount++)
                        {
                            groupName = groupName + GETConstants.Symbols.strColon + "N/A";
                        }

                        groupName = groupName + GETConstants.Symbols.strColon + role;
                    }
                    if (groupName != null)
                    {
                        if (userDetailsMap == null)
                        {
                            userDetailsMap = new HashMap<String, UserDetails>();
                        }
                        if (userDetailsMap.containsKey(user.get_user_id()))
                        {
                            UserDetails userDetail = userDetailsMap.get(user.get_user_id());
                            userDetail.getGroupDetails().add(groupName);
                        }
                        else
                        {
                            // Create the User Details Structure
                            UserDetails userDetails = new UserDetails();
                            userDetails.setUserID(user.get_user_id());
                            userDetails.setFirstName(firstName);
                            userDetails.setLastName(lastName);
                            userDetails.setEmail(person.get_PA9().isEmpty() ? "dummy@info.com" : person.get_PA9());
                            userDetails.setCountry(person.get_PA5().isEmpty() ? "NO VALUE" : person.get_PA5());
                            userDetails.setIsActive((status == 0) ? true : false);
                            List<String> groupDetails = new ArrayList<String>();
                            groupDetails.add(groupName);
                            userDetails.setGroupDetails(groupDetails);
                            userDetails.setCreatedUser(createdUser);
                            userDetails.setModifiedUser(modifiedUser);
                            userDetails.setCreationDate(calendarToDate(person.get_creation_date()));
                            userDetails.setModifiedDate(calendarToDate(person.get_last_mod_date()));

                            // Store the User Details Structure in a Map
                            userDetailsMap.put(user.get_user_id(), userDetails);
                        }

                        // Store the User Map also in a Map
                        if (userMap == null)
                        {
                            userMap = new HashMap<String, User>();
                        }
                        if (!userMap.containsKey(user.get_user_id()))
                        {
                            userMap.put(user.get_user_id(), user);
                        }
                    }
                }
            }
        }

        if (userDetailsMap != null)
        {
            GETProjectManagement projectMgmtService = GETProjectManagement.getProjectManagementService(m_sessionObj.getConnection());

            // Construct the Teamcenter Full Group name for the ENGINEERING group
            StringBuilder enggGroupNameBuilder = new StringBuilder(GroupDetails.engineeringGroupName);
            enggGroupNameBuilder.append(GETConstants.Symbols.strDot).append(GroupDetails.transportationGroupName)
            .append(GETConstants.Symbols.strDot).append(GroupDetails.GETransportationGroupName);

            Set<String> userIDs = userDetailsMap.keySet();
            for (String userID : userIDs)
            {
                ProjectInfo[] projectsInfo = projectMgmtService.getUserProjects(userMap.get(userID), false, false, false);
                if (projectsInfo != null && projectsInfo.length > 0)
                {
                    TC_Project[] projects = new TC_Project[projectsInfo.length];
                    for (int index = 0; index < projectsInfo.length; index++)
                    {
                        projects[index] = projectsInfo[index].project;
                    }
                    dataMgmt.getProperties(projects,
                                           new String[] { GETConstants.BusinessObjects.Properties.projectId });
                    for (TC_Project project : projects)
                    {
                        StringBuilder groupNameBuilder = new StringBuilder();

                        String projectID = project.get_project_id();

                        // Process Supply Chain & Engineering groups separately
                        if (projectID.indexOf("(R)") == -1 && projectID.indexOf("(C)") == -1)
                        {
                            // This is a Supply Chain group
                            StringBuilder scGroupNameBuilder = new StringBuilder(GroupDetails.supplyChainGroupName);
                            scGroupNameBuilder.append(":N/A:N/A:N/A:").append(projectID).append(":N/A");
                            userDetailsMap.get(userID).getGroupDetails().add(scGroupNameBuilder.toString());
                            continue;
                        }

                        // This project corresponds to IP Classification
                        String mainGroupName = projectID.substring(0, projectID.indexOf(" - "));
                        StringBuilder tcGroupNameBuilder = new StringBuilder(mainGroupName);
                        tcGroupNameBuilder.append(GETConstants.Symbols.strDot).append(enggGroupNameBuilder.toString());
                        // Check if this project corresponds to an Engineering Project
                        Group teamcenterGroup = findGroup(tcGroupNameBuilder.toString());
                        if (teamcenterGroup != null)
                        {
                            groupNameBuilder.append(GroupDetails.engineeringGroupName).append(GETConstants.Symbols.strColon)
                            .append(mainGroupName).append(GETConstants.Symbols.strColon);
                        }
                        else
                        {
                            groupNameBuilder.append(mainGroupName).append(":N/A:");
                        }
                        if (projectID.indexOf("(R)") != -1)
                        {
                            groupNameBuilder.append(GETConstants.LOV.IP_CLASS_RESTRICTED_LOV_VALUE);
                        }
                        else
                        {
                            groupNameBuilder.append(GETConstants.LOV.IP_CLASS_CONFIDENTIAL_LOV_VALUE);
                        }
                        groupNameBuilder.append(":N/A:N/A:N/A");
                        userDetailsMap.get(userID).getGroupDetails().add(groupNameBuilder.toString());
                    }
                }
            }
            userDetailsList = new ArrayList<UserDetails>(userDetailsMap.values());
        }

        return userDetailsList;
    }

    /**
     * Private method to get the Date value from the given Calendar instance
     *
     * @param calendar - The input Calendar instance whose Date value is required
     * @return - The Date value of the given Calendar instance
     */
    private Date calendarToDate(Calendar calendar)
    {
        return calendar.getTime();
    }

    /**
     * Method to deactivate a given Teamcenter User
     *
     * @param userId - The String Teamcenter User ID of the User to be deactivated
     * @throws Exception - Any Teamcenter error that may occur during this operation
     */
    public void deactivateUser(String userId) throws Exception
    {
        // Get the User Object
        GETUserAdministration usrAdminInst = GETUserAdministration.getService(m_sessionObj.getConnection());
        User user = (User) usrAdminInst.getUser(userId);
        if (user == null)
        {
            throw new Exception("User with the given id " + userId + " does not exist");
        }

        GETDataManagement dataMgmtInst = GETDataManagement.getDMService(m_sessionObj.getConnection());
        dataMgmtInst.getProperties(new ModelObject[] {user},
                                   new String[] {GETConstants.BusinessObjects.Properties.status});
        // If the User Status is deactivated, throw error to the user
        if (user.get_status() != 0)
        {
            throw new Exception("User with the given id " + userId + " is already deactivated");
        }

        // Add the user to a dummy group before deactivation
        List<String> arguments = new ArrayList<String>();
        arguments.add(new StringBuffer().append("-user=").append(userId).toString());
        arguments.add(new StringBuffer().append("-group=").append(GETConstants.Groups.strEngineeringGroup).toString());
        arguments.add(new StringBuffer().append("-role=").append(GETConstants.Roles.strDesignerRole).toString());
        if (usrAdminInst.makeUserByArgs(arguments) != 0)
        {
            throw new Exception("Unable to add the user " + userId + " to the dummy group/role "
               + GETConstants.Groups.strEngineeringGroup + "/" + GETConstants.Roles.strDesignerRole + " before deactivation");
        }

        // Update the default group for the user
        arguments.clear();
        arguments.add(new StringBuffer().append("-user=").append(userId).toString());
        arguments.add(new StringBuffer().append("-defaultgroup=").append(GETConstants.Groups.strEngineeringGroup).toString());
        arguments.add(new StringBuffer().append("-update").toString());
        if (usrAdminInst.makeUserByArgs(arguments) != 0)
        {
            throw new Exception("Unable to change the default group to " + GETConstants.Groups.strEngineeringGroup + " for the user " + userId);
        }

        // Refresh the User Object
        dataMgmtInst.refreshObjects(new ModelObject[]{user});

        // Make the User InActive from all the groups and roles
        dataMgmtInst.getProperties(new ModelObject[] { user }, new String[] { GETConstants.BusinessObjects.Properties.defaultGroup });
        ModelObject defaultGroup = (((User) user).get_default_group());
        ModelObject[] groupMembers = usrAdminInst.getUserGroupMembers(userId, null, null, "0", "0");
        if (groupMembers != null && groupMembers.length > 0)
        {
            boolean isRefreshRequired = false;

            // Remove the User from all the Projects
            GETProjectManagement projectMgmtService = GETProjectManagement.getProjectManagementService(m_sessionObj.getConnection());
            ProjectInfo[] projectsInfo = projectMgmtService.getUserProjects(user, false, false, false);
            if (projectsInfo != null && projectsInfo.length > 0)
            {
                for (ProjectInfo projectInfo : projectsInfo)
                {
                    GETProjectData projectData = new GETProjectData(projectInfo.project, groupMembers, null, null);
                    projectMgmtService.updateProjectTeam(projectInfo.project, null, projectData, false);
                    isRefreshRequired = true;
                }
            }

            if (isRefreshRequired)
            {
                // Refresh the User Object prior to Group Member removal
                dataMgmtInst.refreshObjects(new ModelObject[]{user});
            }

            dataMgmtInst.getProperties(groupMembers, new String[] { GETConstants.BusinessObjects.Properties.group, GETConstants.BusinessObjects.Properties.role });
            for (ModelObject mo : groupMembers)
            {
                GroupMember groupMember = (GroupMember) mo;

                ModelObject groupObj = groupMember.get_group();
                if (groupObj.equals(defaultGroup))
                {
                    continue;
                }
                if (groupObj instanceof ProjectTeam)
                {
                    continue;
                }

                // Get the Group Name
                dataMgmtInst.getProperties(new ModelObject[] { groupMember.get_group() }, new String[] { GETConstants.BusinessObjects.Properties.fullName });
                dataMgmtInst.getProperties(new ModelObject[] { groupMember.get_role() }, new String[] { GETConstants.BusinessObjects.Properties.strObjectName });
                // Make the Group Member InActive
                arguments.clear();
                arguments.add(new StringBuffer().append("-user=").append(userId).toString());
                arguments.add(new StringBuffer().append("-group=").append(groupMember.get_group().get_full_name()).toString());
                arguments.add(new StringBuffer().append("-role=").append(groupMember.get_role().get_object_name()).toString());
                arguments.add("-gm_status=1");
                arguments.add("-update");
                if (usrAdminInst.makeUserByArgs(arguments) != 0)
                {
                    throw new Exception("Unable to remove the user " + userId + " from the group/role " +
                    groupMember.get_group().get_full_name() + "/" + groupMember.get_role().get_object_name());
                }
            }
        }

        // Deactivate the User
        usrAdminInst.deactivateUser(user);
    }

    /**
     * Method to reactivate an already deactivated user
     *
     * @param userId - The String Teamcenter User ID of the User to be reactivcated
     * @throws Exception - Any Teamcenter error that may occur during this operation
     */
    public void reactivateUser(String userId) throws Exception
    {
        GETUserAdministration usrAdminInst = GETUserAdministration.getService(m_sessionObj.getConnection());
        User user = (User) usrAdminInst.getUser(userId);
        if (user == null)
        {
            throw new Exception("Given user " + userId + " does not exist");
        }
        usrAdminInst.activateUser(user);
    }

    /**
     * Method to create a new user or activate an existing user and provide him with the required group/roles
     *
     * @param firstName - The String first name of the User
     * @param lastName - The String last name of the User
     * @param userId - The String ID of the User
     * @param IsActive - The boolean active status of the user
     * @param groupRoles - A List of Strings containing the group/role information
     * @param emailId - The String Email ID of the User
     * @param country - The String Geographic Location of the User
     * @throws Exception - Any Teamcenter error that can occur while executing this operation
     */
    public void createUser(String firstName, String lastName, String userId,
                           boolean IsActive, List<String> groupRoles, String emailId,
                           String country) throws Exception
    {
        boolean isFirstGroup = true;

        GroupMember toBeDeletedGroupMember = null;

        int noOfBasicRequests = 0;
        int noOfOtherAdvRequests = 0;
        int noOfSCBasicRequests = 0;
        int noOfSCAdvRequests = 0;

        String personName = null;

        if (lastName != null && !(lastName.isEmpty()) && lastName != "")
        {
            personName = lastName + "," + firstName;
        }
        else
        {
            personName = firstName;
        }

        GETUserAdministration usrAdminInst = GETUserAdministration.getService(m_sessionObj.getConnection());
        GETDataManagement dataMgmtInst = GETDataManagement.getDMService(m_sessionObj.getConnection());
        GETProjectManagement projMgmtInst = GETProjectManagement.getProjectManagementService(m_sessionObj.getConnection());

        List<GroupDetails> requestsList = new ArrayList<GroupDetails>();

        // Check if the user already exists
        ModelObject user = usrAdminInst.getUser(userId);
        if (user != null)
        {
            dataMgmtInst.getProperties(new ModelObject[] {user},
                                       new String[] {GETConstants.BusinessObjects.Properties.status});
            // If the User Status is Active, throw error to the user
            if (((User)user).get_status() == 0)
            {
                throw new Exception("User with given id " + userId + " already exists in Teamcenter");
            }

            // Get the User Group Member
            ModelObject[] gmMO = usrAdminInst.getUserGroupMembers(userId, GETConstants.Groups.strEngineeringGroup, GETConstants.Roles.strDesignerRole, null, null);
            if (gmMO != null && gmMO.length > 0)
            {
                toBeDeletedGroupMember = (GroupMember) gmMO[0];
            }
        }

        // Process Group/Role additions
        for (String groupRole : groupRoles)
        {
            String groups[] = groupRole.split(GETConstants.Symbols.strColon);
            if (groups.length != 6)
            {
                throw new Exception ("The Group Role string " + groupRole + " is not in valid format");
            }

            String group = groups[3] + "." + groups[1] + "." + groups[0];
            group = group.replace("N/A.", "");
            GroupDetails groupDetails = new GroupDetails(groupRole, groups[1], group, groups[2].trim(), groups[4].trim(), groups[5].trim());
            if (groupDetails.isBasicRequest())
            {
                // validate role in group
                validateRoleInGroup(groupDetails.getGroupName() + groupNameAppend, groupDetails.getRoleName());
                if (groupDetails.isSupplyChainRequest())
                {
                    noOfSCBasicRequests++;
                }
                noOfBasicRequests++;
            }
            else
            {
                ModelObject[] projects = null;

                String projectName = null;

                if (groupDetails.isSupplyChainRequest())
                {
                    if (groupDetails.getPlantValue() == null || groupDetails.getPlantValue().isEmpty() || groupDetails.getPlantValue().equalsIgnoreCase("N/A"))
                    {
                        throw new Exception("Plant value cannot be empty or N/A in " + groupDetails.getInputGroupRole() + " as this line corresponds to Plant only update");
                    }
                    projectName = groupDetails.getPlantValue();
                    noOfSCAdvRequests++;
                }
                else
                {
                    if (groupDetails.getIPClassificationValue() == null || groupDetails.getIPClassificationValue().isEmpty() || groupDetails.getIPClassificationValue().equalsIgnoreCase("N/A"))
                    {
                        throw new Exception("IP Classification value cannot be empty or N/A in " + groupDetails.getInputGroupRole() + " as this line corresponds to IP Classification only update");
                    }
                    projectName = getProjectFromIP(groupDetails.getMainGroupName(), groupDetails.getIPClassificationValue());
                    noOfOtherAdvRequests++;
                }

                // Validate the Teamcenter Project value
                if (projectName != null)
                {
                    projects = projMgmtInst.findProjectsByID(projectName);
                }
                if (projects == null || projects.length == 0)
                {
                    throw new Exception("There is no TC Project corresponding to the IP Classification/Plant value as mentioned in the line " + groupDetails.getInputGroupRole());
                }
                groupDetails.setTcProject((TC_Project)projects[0]);
            }
            requestsList.add(groupDetails);
        }

        // Validate the user requests
        if (noOfOtherAdvRequests > 0 && noOfBasicRequests == 0)
        {
            throw new Exception("User must request at least one role under \'Basic\' access type when requesting access for IP-Classification");
        }
        if ((noOfSCBasicRequests > 0 && noOfSCAdvRequests == 0) || (noOfSCAdvRequests > 0 && noOfSCBasicRequests == 0))
        {
            throw new Exception("User must request at least one role under \'Basic\' access type AND at least one plant access under \'Advanced\' access type");
        }

        // Sort the requests to make sure that Basic requests are available first
        Collections.sort(requestsList, new Comparator<GroupDetails>()
        {
            /**
             * Runtime Comparator method to compare the GroupDetails instance.
             */
            @Override
            public int compare(GroupDetails g1, GroupDetails g2)
            {
                int retValue = 0;

                if (g1.isBasicRequest())
                {
                    retValue = -1;
                }
                else if (g2.isBasicRequest())
                {
                    retValue = 1;
                }

                return retValue;
            }
        });

        // Parse the input requests and provide access as required
        for (GroupDetails groupDetails : requestsList)
        {
            // Process basic requests
            if (groupDetails.isBasicRequest())
            {
                List<String> arguments = new ArrayList<String>();
                arguments.add(new StringBuffer().append("-user=").append(userId).toString());
                arguments.add(new StringBuffer().append("-group=").append(groupDetails.getGroupName() + groupNameAppend).toString());
                arguments.add(new StringBuffer().append("-role=").append(groupDetails.getRoleName()).toString());
                arguments.add("-gm_status=0");
                if (user != null)
                {
                    arguments.add("-update");
                }
                else
                {
                    arguments.add(new StringBuffer().append("-person=").append(personName).toString());
                    arguments.add(new StringBuffer().append("-password=").append(userId).toString());
                    if (country != null && !country.isEmpty())
                    {
                        arguments.add(new StringBuffer().append("-PA5=").append(country).toString());
                    }
                    if (emailId != null && !emailId.isEmpty())
                    {
                        arguments.add(new StringBuffer().append("-PA9=").append(emailId).toString());
                    }
                }
                if (usrAdminInst.makeUserByArgs(arguments) != 0)
                {
                    throw new Exception("User creation failed");
                }

                // Refresh the User, if already existing in the system
                if (user != null)
                {
                    dataMgmtInst.refreshObjects(new ModelObject[]{user});
                }
                else
                {
                    // If the user is created for the first time, get the User object
                    user = usrAdminInst.getUser(userId);
                }

                if (isFirstGroup)
                {
                    // Update the default group for the user
                    arguments.clear();
                    arguments.add(new StringBuffer().append("-user=").append(userId).toString());
                    arguments.add(new StringBuffer().append("-defaultgroup=").append(groupDetails.getGroupName() + groupNameAppend).toString());
                    int iIsActive = (IsActive == true) ? 0 : 1;
                    arguments.add(new StringBuffer().append("-status=").append(iIsActive).toString());
                    arguments.add("-update");
                    if (usrAdminInst.makeUserByArgs(arguments) != 0)
                    {
                        throw new Exception("Unable to set the default group to " + groupDetails.getInputGroupRole() + " for the user " + userId);
                    }
                    // Refresh the user after setting the default group
                    dataMgmtInst.refreshObjects(new ModelObject[]{user});
                    isFirstGroup = false;
                }
            }

            // Process the Project addition requests for IP Classification/Plant
            if (groupDetails.getTcProject() != null)
            {
                String[] toBeAddedUsers = new String[] { userId };
                projMgmtInst.updateProjectTeam(groupDetails.getTcProject(), toBeAddedUsers, null, null, null, null, null, false);
                if (groupDetails.isSupplyChainRequest())
                {
                    projMgmtInst.updateProjectTeam(groupDetails.getTcProject(), null, null, toBeAddedUsers, null, null, null, false);
                }
            }
        }

        // Delete the user from the dummy default group
        if (toBeDeletedGroupMember != null)
        {
            ServiceData serviceData = dataMgmtInst.deleteObjects(new ModelObject[]{toBeDeletedGroupMember});
            String errorMsg = GETCommon.getErrorFromServiceData(serviceData);
            if (errorMsg != null)
            {
                throw new Exception(errorMsg);
            }
        }
    }

    /**
     * Method to add the given user to the given Teamcenter Group/Role and also update the IP Classification/Plant based project memberships
     *
     * @param userId - The String Teamcenter User ID to be added
     * @param groupRoles - A List of Strings containing the Group/Role/IP Classification/Plant information
     * @throws Exception - Any Teamcenter error that may occur during this operation
     */
    public void addUserToGroup(String userId, List<String> groupRoles) throws Exception
    {
        int noOfBasicRequests = 0;
        int noOfOtherAdvRequests = 0;
        int noOfSCBasicRequests = 0;
        int noOfSCAdvRequests = 0;

        GETUserAdministration usrAdminInst = GETUserAdministration.getService(m_sessionObj.getConnection());
        GETProjectManagement projectMgmtService = GETProjectManagement.getProjectManagementService(m_sessionObj.getConnection());

        List<GroupDetails> requestsList = new ArrayList<GroupDetails>();

        // Check if user exists
        ModelObject user = usrAdminInst.getUser(userId);
        if (user == null)
        {
            throw new Exception("User with the given id " + userId + " does not exist");
        }
        if (!isUserActive(userId))
        {
            throw new Exception("User with the given id " + userId + " is not active in the system");
        }

        // Loop through the request and store them in corresponding list
        for (String groupRole : groupRoles)
        {
            String groups[] = groupRole.split(GETConstants.Symbols.strColon);
            if (groups.length != 6)
            {
                throw new Exception ("The Group Role string " + groupRole + " is not in valid format");
            }

            String group = groups[3] + "." + groups[1] + "." + groups[0];
            group = group.replace("N/A.", "");
            GroupDetails groupDetails = new GroupDetails(groupRole, groups[1], group, groups[2].trim(), groups[4].trim(), groups[5].trim());
            if (groupDetails.isBasicRequest())
            {
                // validate role in group
                validateRoleInGroup(groupDetails.getGroupName() + groupNameAppend, groupDetails.getRoleName());

                // check if user is already a group member
                ModelObject[] grpMembers = usrAdminInst.getUserGroupMembers(userId, groupDetails.getGroupName() + groupNameAppend, groupDetails.getRoleName(), "0", "0");
                if (grpMembers != null && grpMembers.length > 0)
                {
                    throw new Exception("User with the given id " + userId + " is already a member of the group/role " + groupDetails.getInputGroupRole());
                }

                if (groupDetails.isSupplyChainRequest())
                {
                    noOfSCBasicRequests++;
                }
                noOfBasicRequests++;
            }
            else
            {
                ModelObject[] projects = null;

                String projectName = null;

                if (groupDetails.isSupplyChainRequest())
                {
                    if (groupDetails.getPlantValue() == null || groupDetails.getPlantValue().isEmpty() || groupDetails.getPlantValue().equalsIgnoreCase("N/A"))
                    {
                        throw new Exception("Plant value cannot be empty or N/A in " + groupDetails.getInputGroupRole() + " as this line corresponds to Plant only update");
                    }
                    projectName = groupDetails.getPlantValue();
                    noOfSCAdvRequests++;
                }
                else
                {
                    if (groupDetails.getIPClassificationValue() == null || groupDetails.getIPClassificationValue().isEmpty() || groupDetails.getIPClassificationValue().equalsIgnoreCase("N/A"))
                    {
                        throw new Exception("IP Classification value cannot be empty or N/A in " + groupDetails.getInputGroupRole() + " as this line corresponds to IP Classification only update");
                    }
                    projectName = getProjectFromIP(groupDetails.getMainGroupName(), groupDetails.getIPClassificationValue());
                    noOfOtherAdvRequests++;
                }

                // Validate the Teamcenter Project value
                if (projectName != null)
                {
                    projects = projectMgmtService.findProjectsByID(projectName);
                }
                if (projects == null || projects.length == 0)
                {
                    throw new Exception("There is no TC Project corresponding to the IP Classification/Plant value as mentioned in the line " + groupDetails.getInputGroupRole());
                }
                groupDetails.setTcProject((TC_Project)projects[0]);
            }
            requestsList.add(groupDetails);
        }

        // Get the existing entitlements for the current user
        UserAccessDetails userAccessDetails = getExistingEntitlementsForUser(userId);

        // Validate the user requests along with the existing entitlements
        if (noOfOtherAdvRequests > 0 && noOfBasicRequests == 0 && userAccessDetails.enggBasicGroupNames.size() == 0 &&
            userAccessDetails.scBasicGroupNames.size() == 0 && userAccessDetails.otherBasicGroupNames.size() == 0)
        {
            throw new Exception("User must request/have at least one role under \'Basic\' access type when requesting access for IP-Classification");
        }
        if ((noOfSCBasicRequests > 0 && noOfSCAdvRequests == 0 && userAccessDetails.scAdvProjNames.size() == 0) ||
            (noOfSCAdvRequests > 0 && noOfSCBasicRequests == 0 && userAccessDetails.scBasicGroupNames.size() == 0))
        {
            throw new Exception("User must request/have at least one role under \'Basic\' access type AND at least one plant access under \'Advanced\' access type");
        }

        // Parse the input requests and provide access as required
        for (GroupDetails groupDetails : requestsList)
        {
            // Process only if group/role details are provided
            if (groupDetails.isBasicRequest())
            {
                // Add user to group
                List<String> arguments = new ArrayList<String>();
                arguments.add(new StringBuffer().append("-user=").append(userId).toString());
                arguments.add(new StringBuffer().append("-group=").append(groupDetails.getGroupName() + groupNameAppend).toString());
                arguments.add(new StringBuffer().append("-role=").append(groupDetails.getRoleName()).toString());
                arguments.add("-gm_status=0");
                arguments.add("-update");
                if (usrAdminInst.makeUserByArgs(arguments) != 0)
                {
                    throw new Exception("Unable to add the user " + userId + " to the given group/role " + groupDetails.getInputGroupRole());
                }
            }

            // Add code to manage Projects based on the IP Classification/Plant value
            if (groupDetails.getTcProject() != null)
            {
                String[] toBeAddedUsers = new String[] { userId };
                projectMgmtService.updateProjectTeam(groupDetails.getTcProject(), toBeAddedUsers, null, null, null, null, null, false);
                if (groupDetails.isSupplyChainRequest())
                {
                    projectMgmtService.updateProjectTeam(groupDetails.getTcProject(), null, null, toBeAddedUsers, null, null, null, false);
                }
            }
        }
    }

    /**
     * Method to remove the given user from the given Teamcenter Group/Role and also update the IP Classification/Plant based project memberships
     *
     * @param userId - The String Teamcenter User ID to be removed
     * @param groupRoles - A List of Strings containing the Group/Role/IP Classification/Plant information
     * @throws Exception - Any Teamcenter error that may occur during this operation
     */
    public void removeUserFromGroup(String userId, List<String> groupRoles) throws Exception
    {
        int noOfSCBasicRequests = 0;
        int noOfSCAdvRequests = 0;

        GETDataManagement dmService = GETDataManagement.getDMService(m_sessionObj.getConnection());
        GETUserAdministration userService = GETUserAdministration.getService(m_sessionObj.getConnection());
        GETProjectManagement projMgmtService = GETProjectManagement.getProjectManagementService(m_sessionObj.getConnection());

        Map<String, ModelObject[]> groupMembersMap = new HashMap<String, ModelObject[]>();

        List<GroupDetails> requestsList = new ArrayList<GroupDetails>();

        // check if user exists
        User user = (User) userService.getUser(userId);
        if (user == null)
        {
            throw new Exception("User with the given id " + userId + " does not exist");
        }

        for (String groupRole : groupRoles)
        {
            String groups[] = groupRole.split(GETConstants.Symbols.strColon);
            if (groups.length != 6)
            {
                throw new Exception ("The Group Role string " + groupRole + " is not in valid format");
            }
            String group = groups[3] + "." + groups[1] + "." + groups[0];
            group = group.replace("N/A.", "");
            GroupDetails groupDetails = new GroupDetails(groupRole, groups[1], group, groups[2].trim(), groups[4].trim(), groups[5].trim());
            if (groupDetails.isBasicRequest())
            {
                // Check if user is a member in the given group
                ModelObject[] grpMembersToDelete = userService.getUserGroupMembers(userId, groupDetails.getGroupName() + groupNameAppend, groupDetails.getRoleName(), "0", "0");
                if (grpMembersToDelete == null || grpMembersToDelete.length == 0)
                {
                    throw new Exception("User " + userId + " is not a member of the given group/role " + groupDetails.getInputGroupRole());
                }
                groupMembersMap.put(groupDetails.getGroupName() + groupNameAppend + "/" + groupDetails.getRoleName(), grpMembersToDelete);
                if (groupDetails.isSupplyChainRequest())
                {
                    noOfSCBasicRequests++;
                }
            }
            else
            {
                ModelObject[] projects = null;

                String projectName = null;

                if (groupDetails.isSupplyChainRequest())
                {
                    if (groupDetails.getPlantValue() == null || groupDetails.getPlantValue().isEmpty() || groupDetails.getPlantValue().equalsIgnoreCase("N/A"))
                    {
                        throw new Exception("Plant value cannot be empty or N/A in " + groupDetails.getInputGroupRole() + " as this line corresponds to Plant only update");
                    }
                    projectName = groupDetails.getPlantValue();
                    noOfSCAdvRequests++;
                }
                else
                {
                    if (groupDetails.getIPClassificationValue() == null || groupDetails.getIPClassificationValue().isEmpty() || groupDetails.getIPClassificationValue().equalsIgnoreCase("N/A"))
                    {
                        throw new Exception("IP Classification value cannot be empty or N/A in " + groupDetails.getInputGroupRole() + " as this line corresponds to IP Classification only update");
                    }
                    projectName = getProjectFromIP(groupDetails.getMainGroupName(), groupDetails.getIPClassificationValue());
                }

                // Validate the Teamcenter Project value
                if (projectName != null)
                {
                    projects = projMgmtService.findProjectsByID(projectName);
                }
                if (projects == null || projects.length == 0)
                {
                    throw new Exception("There is no TC Project corresponding to the IP Classification/Plant value as mentioned in the line " + groupDetails.getInputGroupRole());
                }
                groupDetails.setTcProject((TC_Project)projects[0]);
            }
            requestsList.add(groupDetails);
        }

        // Get the existing entitlements for the current user
        UserAccessDetails userAccessDetails = getExistingEntitlementsForUser(userId);

        // Validate the user requests along with the existing entitlements
        if ((noOfSCBasicRequests > 0 && noOfSCBasicRequests >= userAccessDetails.scBasicGroupNames.size()) ||
            (noOfSCAdvRequests > 0 && noOfSCAdvRequests >= userAccessDetails.scAdvProjNames.size()))
        {
            throw new Exception("User must have at least one basic role AND one plant associated under " + GroupDetails.supplyChainGroupName +
                    " group to continue to have supply chain access in PLM");
        }

        // Process the remove requests
        for (GroupDetails groupDetails : requestsList)
        {
            // Process only if group/role details are provided
            if (groupDetails.isBasicRequest())
            {
                boolean isRefreshRequired = false;
                boolean isRefreshBeforeDelete = false;
                boolean userHasMultipleGroupMembers = false;

                ModelObject newProjectGroupMember = null;

                // Get the group member to be deleted
                ModelObject[] grpMembersToDelete = groupMembersMap.get(groupDetails.getGroupName() + groupNameAppend + "/" + groupDetails.getRoleName());

                // Check if the group is the default group for the user
                dmService.getProperties(new ModelObject[] { grpMembersToDelete[0] },
                                                            new String[] { GETConstants.BusinessObjects.Properties.group });
                ModelObject groupObj = ((GroupMember) grpMembersToDelete[0]).get_group();
                dmService.getProperties(new ModelObject[] { user }, new String[] { GETConstants.BusinessObjects.Properties.defaultGroup });
                ModelObject defaultGroup = (((User) user).get_default_group());
                if (groupObj == defaultGroup)
                {
                    ModelObject[] userGrpMemberObjs = userService.getUserGroupMembers(userId, null, null, "0", "0");
                    if (userGrpMemberObjs != null && userGrpMemberObjs.length > 1)
                    {
                        dmService.getProperties(userGrpMemberObjs,
                                                new String[] { GETConstants.BusinessObjects.Properties.group });
                        for (ModelObject grpMember : userGrpMemberObjs)
                        {
                            if (grpMember == grpMembersToDelete[0])
                            {
                                continue;
                            }
                            ModelObject tempGroupObj = ((GroupMember) grpMember).get_group();

                            // If the GroupMember is an instance of project team, skip it
                            if (tempGroupObj instanceof ProjectTeam)
                            {
                                continue;
                            }

                            // If the code reaches this line, it means the user is a member of more than one group/role
                            userHasMultipleGroupMembers = true;

                            // This GroupMember can be added to Projects
                            newProjectGroupMember = grpMember;

                            if (groupObj == tempGroupObj)
                            {
                                // in this case, the user is in multiple roles under
                                // the same group,
                                // hence no need to change the default group
                                break;
                            }
                            dmService.getProperties(new ModelObject[] { tempGroupObj },
                                                    new String[] { GETConstants.BusinessObjects.Properties.fullName });

                            String tempGroup = ((Group) tempGroupObj).get_full_name();

                            List<String> arguments = new ArrayList<String>();
                            arguments.add("-user=" + userId);
                            arguments.add("-defaultgroup=" + tempGroup);
                            arguments.add("-update");
                            if (userService.makeUserByArgs(arguments) != 0)
                            {
                                throw new Exception("Unable to set the default group to " + tempGroup + " for the user " + userId);
                            }
                            isRefreshRequired = true;
                            break;
                        }
                    }
                    else
                    {
                        throw new Exception("Cannot delete user from default group and role");
                    }

                    // If the User is not a member of more than one group/role, return error
                    if (!userHasMultipleGroupMembers)
                    {
                        throw new Exception("Cannot delete user from default group and role");
                    }
                }

                // In case the Default Group is updated, then we need to refresh the group member information
                if (isRefreshRequired)
                {
                    dmService.refreshObjects(new ModelObject[]{user});
                }

                // Remove the Group Member from all the Projects
                //ModelObject[] groupMembers = userService.getUserGroupMembers(userId, group + groupNameAppend, null, null, null);
                ProjectInfo[] projectsInfo = projMgmtService.getUserProjects(user, false, false, false);
                if (projectsInfo != null && projectsInfo.length > 0)
                {
                    for (ProjectInfo projectInfo : projectsInfo)
                    {
                        GETProjectData projectData = new GETProjectData(projectInfo.project, grpMembersToDelete, null, null);
    
                        if (projMgmtService.updateProjectTeam(projectInfo.project, null, projectData, false))
                        {
                            if (newProjectGroupMember != null)
                            {
                                GETProjectData newProjectData = new GETProjectData(projectInfo.project, new ModelObject[]{newProjectGroupMember}, null, null);
                                projMgmtService.updateProjectTeam(projectInfo.project, newProjectData, null, false);
                            }
                            else
                            {
                                projMgmtService.updateProjectTeam(projectInfo.project, new String[]{userId}, null, null, null, null, null, false);
                            }
                            if (projectInfo.isUserPrivileged)
                            {
                                GETProjectData newPrivilegedProjectData = new GETProjectData(projectInfo.project, null, new ModelObject[]{user}, null);
                                projMgmtService.updateProjectTeam(projectInfo.project, newPrivilegedProjectData, null, false);
                            }
                        }
                        isRefreshBeforeDelete = true;
                    }
                }
                // Refresh the User prior to deleting the Group Member
                if (isRefreshBeforeDelete)
                {
                    dmService.refreshObjects(new ModelObject[]{user});
                }

                // Make the Group Member InActive
                List<String> arguments = new ArrayList<String>();
                arguments.add(new StringBuffer().append("-user=").append(userId).toString());
                arguments.add(new StringBuffer().append("-group=").append(groupDetails.getGroupName() + groupNameAppend).toString());
                arguments.add(new StringBuffer().append("-role=").append(groupDetails.getRoleName()).toString());
                arguments.add("-gm_status=1");
                arguments.add("-update");
                if (userService.makeUserByArgs(arguments) != 0)
                {
                    throw new Exception("Unable to remove the user " + userId + " from the given group/role " + groupDetails.getInputGroupRole());
                }
            }

            // Process Projects only for advanced requests
            if (!groupDetails.isBasicRequest() && groupDetails.getTcProject() != null)
            {
                String[] toBeRemovedUsers = new String[] { userId };
                projMgmtService.updateProjectTeam(groupDetails.getTcProject(), null, toBeRemovedUsers, null, null, null, null, false);
            }
        }
    }

    /**
     * Method to get the existing entitlements for the given user
     *
     * @param userId - The String User ID of the user whose entitlements are required
     * @return UserAccessDetails - A structure containing the User Entitlement details
     */
    public UserAccessDetails getExistingEntitlementsForUser(String userId) throws Exception
    {
        UserAccessDetails userAccessDetails = new UserAccessDetails();

        GETDataManagement dataMgmtService = GETDataManagement.getDMService(m_sessionObj.getConnection());
        GETUserAdministration usrAdminInst = GETUserAdministration.getService(m_sessionObj.getConnection());
        GETProjectManagement projectMgmtService = GETProjectManagement.getProjectManagementService(m_sessionObj.getConnection());

        User user = (User) usrAdminInst.getUser(userId);

        ModelObject[] modelObjectMembers = usrAdminInst.getUserGroupMembers(userId, null, null, "0", "0");
        if (modelObjectMembers != null && modelObjectMembers.length > 0)
        {
            for (ModelObject modelObjectMember : modelObjectMembers)
            {
                GroupMember grpMember = (GroupMember) modelObjectMember;
                Group grp = (Group) grpMember.get_group();
                if (grp instanceof ProjectTeam)
                {
                    continue;
                }
                dataMgmtService.getProperties(new ModelObject[] { grp }, new String[] { GETConstants.BusinessObjects.Properties.fullName });
                String group = grp.get_full_name().toUpperCase().trim();
                if (group == null || group.isEmpty() || !group.contains(GroupDetails.GETransportationGroupName))
                {
                    continue;
                }
                if (group.contains(GroupDetails.engineeringGroupName))
                {
                    userAccessDetails.enggBasicGroupNames.add(group);
                }
                else if (group.contains(GroupDetails.supplyChainGroupName))
                {
                    userAccessDetails.scBasicGroupNames.add(group);
                }
                else
                {
                    userAccessDetails.otherBasicGroupNames.add(group);
                }
            }
        }
        ProjectInfo[] projectsInfo = projectMgmtService.getUserProjects((User)user, false, false, false);
        if (projectsInfo != null && projectsInfo.length > 0)
        {
            // Construct the Teamcenter Full Group name for the ENGINEERING group
            StringBuilder enggGroupNameBuilder = new StringBuilder(GroupDetails.engineeringGroupName);
            enggGroupNameBuilder.append(GETConstants.Symbols.strDot).append(GroupDetails.transportationGroupName)
            .append(GETConstants.Symbols.strDot).append(GroupDetails.GETransportationGroupName);

            TC_Project[] projects = new TC_Project[projectsInfo.length];
            for (int index = 0; index < projectsInfo.length; index++)
            {
                projects[index] = projectsInfo[index].project;
            }
            dataMgmtService.getProperties(projects,
                                   new String[] { GETConstants.BusinessObjects.Properties.projectId });
            for (TC_Project project : projects)
            {
                String projectID = project.get_project_id();

                // Process Supply Chain & Engineering groups separately
                if (projectID.indexOf("(R)") == -1 && projectID.indexOf("(C)") == -1)
                {
                    // This is a Supply Chain group
                    userAccessDetails.scAdvProjNames.add(projectID);
                    continue;
                }

                // This project corresponds to IP Classification
                String mainGroupName = projectID.substring(0, projectID.indexOf(" - "));
                StringBuilder tcGroupNameBuilder = new StringBuilder(mainGroupName);
                tcGroupNameBuilder.append(GETConstants.Symbols.strDot).append(enggGroupNameBuilder.toString());
                // Check if this project corresponds to an Engineering Project
                Group teamcenterGroup = findGroup(tcGroupNameBuilder.toString());
                if (teamcenterGroup != null)
                {
                    userAccessDetails.enggAdvProjNames.add(projectID);
                }
                else
                {
                    userAccessDetails.otherAdvProjNames.add(projectID);
                }
            }
        }

        return userAccessDetails;
    }

    /**
     * Utility class to store a user's current entitlements
     *
     * @author TCS Development Team
     */
    public class UserAccessDetails
    {
        public List<String> enggBasicGroupNames = new ArrayList<String>();
        public List<String> enggAdvProjNames = new ArrayList<String>();
        public List<String> scBasicGroupNames = new ArrayList<String>();
        public List<String> scAdvProjNames = new ArrayList<String>();
        public List<String> otherBasicGroupNames = new ArrayList<String>();
        public List<String> otherAdvProjNames = new ArrayList<String>();
    }
}
