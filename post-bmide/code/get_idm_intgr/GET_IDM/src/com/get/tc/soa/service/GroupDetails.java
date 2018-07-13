
//==================================================
// 
//  Copyright 2016 GE Transportation. All Rights Reserved.
//
//==================================================
package com.get.tc.soa.service;

import com.teamcenter.soa.client.model.strong.TC_Project;

/**
 * Class to store the Group Details
 *
 * @author TCS Development Team
 */
public class GroupDetails
{
    private boolean isSupplyChainRequest;
    private boolean isBasicRequest;

    private String groupName;
    private String inputGroupRole;
    private String ipClassificationValue;
    private String mainGroupName;
    private String plantValue;
    private String roleName;

    private TC_Project tcProject;

    public static final String engineeringGroupName = "ENGINEERING";
    public static final String supplyChainGroupName = "SUPPLY CHAIN";
    public static final String transportationGroupName = "TRANSPORTATION";
    public static final String GETransportationGroupName = "GE TRANSPORTATION";

    /**
     * Constructor for the class GroupDetails
     *
     * @param inputGroupRole - The String input Group Role
     * @param mainGroupName - The String main group name
     * @param gGroupName - The String group name
     * @param ipClassificationValue - The String IP Classification value
     * @param groupName - The String group name
     * @param plantValue - The String Plant value
     * @param roleName - The String role name
     */
    public GroupDetails(String inputGroupRole, String mainGroupName, String groupName, String ipClassificationValue, String plantValue, String roleName)
    {
        this.tcProject = null;
        this.inputGroupRole = inputGroupRole;
        if (mainGroupName != null && !mainGroupName.isEmpty())
        {
            if (mainGroupName.equalsIgnoreCase("N/A"))
            {
                this.mainGroupName = groupName;
            }
            else
            {
                this.mainGroupName = mainGroupName;
            }
        }
        this.groupName = groupName;
        this.ipClassificationValue = ipClassificationValue;
        this.plantValue = plantValue;
        this.roleName = roleName;

        // Check if this is an Engineering request or Supply Chain
        if (groupName.toUpperCase().endsWith(GroupDetails.supplyChainGroupName))
        {
            isSupplyChainRequest = true;
        }

        // Check if this is a basic request or advanced
        if (roleName != null && !roleName.isEmpty() && !roleName.equalsIgnoreCase("N/A"))
        {
            isBasicRequest = true;
        }
    }

    /**
     * Method to return the input Group Role
     *
     * @return inputGroupRole - The String input Group Role
     */
    public String getInputGroupRole()
    {
        return inputGroupRole;
    }

    /**
     * Method to return the main group name
     *
     * @return mainGroupName - The String main group name
     */
    public String getMainGroupName()
    {
        return mainGroupName;
    }

    /**
     * Method to return the group name
     *
     * @return groupName - The String group name
     */
    public String getGroupName()
    {
        return groupName;
    }

    /**
     * Method to return the IP Classification value
     *
     * @return ipClassificationValue - The String IP Classification value
     */
    public String getIPClassificationValue()
    {
        return ipClassificationValue;
    }

    /**
     * Method to return the Plant value
     *
     * @return plantValue - The String Plant value
     */
    public String getPlantValue()
    {
        return plantValue;
    }

    /**
     * Method to return the role name
     *
     * @return roleName - The String role name
     */
    public String getRoleName()
    {
        return roleName;
    }

    /**
     * Method to check whether this request corresponds to a Supply Chain request or not
     *
     * @return isSupplyChainRequest - A boolean indicating whether this request corresponds to a Supply Chain request or not
     */
    public boolean isSupplyChainRequest()
    {
        return isSupplyChainRequest;
    }

    /**
     * Method to check whether this request corresponds to a basic request or not
     *
     * @return isBasicRequest - A boolean indicating whether this request corresponds to a basic request or not
     */
    public boolean isBasicRequest()
    {
        return isBasicRequest;
    }

    /**
     * Returns the TC_Project instance for this line. Returns null if not applicable for this line
     *
     * @return tcProject - The TC_Project instance corresponding to this line
     */
    public TC_Project getTcProject()
    {
        return tcProject;
    }

    /**
     * Setter method for setting the TC_Project instance for this line
     *
     * @param tcProject - The TC_Project instance corresponsing to this line
     */
    public void setTcProject(TC_Project tcProject)
    {
        this.tcProject = tcProject;
    }
}
