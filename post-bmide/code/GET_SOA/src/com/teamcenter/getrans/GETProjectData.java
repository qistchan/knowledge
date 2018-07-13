
package com.teamcenter.getrans;

import java.util.Arrays;
import java.util.List;

import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.strong.TC_Project;

/**
 * Class to store data about a Project
 * @author TCS Development Team
 *
 */
public class GETProjectData
{
    private TC_Project tcProject;

    private List<ModelObject> regularMembersList;
    private List<ModelObject> privilegedMembersList;
    private List<ModelObject> teamAdministratorsList;

    public GETProjectData(TC_Project tcProject, List<ModelObject> regularMembersList, List<ModelObject> privilegedMembersList, List<ModelObject> teamAdministratorsList)
    {
        this.tcProject = tcProject;
        this.regularMembersList = regularMembersList;
        this.privilegedMembersList = privilegedMembersList;
        this.teamAdministratorsList = teamAdministratorsList;
    }

    public GETProjectData(TC_Project tcProject, ModelObject[] regularMembers, ModelObject[] privilegedMembers, ModelObject[] teamAdministrators)
    {
        this.tcProject = tcProject;
        if (regularMembers != null)
        {
            this.regularMembersList = Arrays.asList(regularMembers);
        }
        if (privilegedMembers != null)
        {
            this.privilegedMembersList = Arrays.asList(privilegedMembers);
        }
        if (teamAdministrators != null)
        {
            this.teamAdministratorsList = Arrays.asList(teamAdministrators);
        }
    }

    public TC_Project getTCProject()
    {
        return tcProject;
    }

    public List<ModelObject> getRegularMembers()
    {
        return regularMembersList;
    }

    public List<ModelObject> getPrivilegedMembers()
    {
        return privilegedMembersList;
    }

    public List<ModelObject> getTeamAdministrators()
    {
        return teamAdministratorsList;
    }
}
