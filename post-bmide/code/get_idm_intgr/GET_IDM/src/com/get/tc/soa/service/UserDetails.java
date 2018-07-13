
//==================================================
// 
//  Copyright 2016 GE Transportation. All Rights Reserved.
//
//==================================================

package com.get.tc.soa.service;

import java.util.Date;
import java.util.List;

/**
 * Utility structure to store the User Details which will be retrieved when information about all active Teamcenter users are collected
 *
 * @author TCS Development Team
 *
 */
public class UserDetails
{
    private boolean activeStatus;

    private Date creationDate;
    private Date modifiedDate;

    private List<String> groupDetails;

    private String userID;
    private String firstName;
    private String lastName;
    private String email;
    private String country;
    private String createdUser;
    private String modifiedUser;

    public String getModifiedUser()
    {
        return modifiedUser;
    }

    public void setModifiedUser(String modifiedUser)
    {
        this.modifiedUser = modifiedUser;
    }

    public boolean isActiveStatus()
    {
        return activeStatus;
    }

    public void setActiveStatus(boolean activeStatus)
    {
        this.activeStatus = activeStatus;
    }

    public String getCreatedUser()
    {
        return createdUser;
    }

    public void setCreatedUser(String createdUser)
    {
        this.createdUser = createdUser;
    }

    public Date getCreationDate()
    {
        return creationDate;
    }

    public void setCreationDate(Date calendar)
    {
        this.creationDate = calendar;
    }

    public Date getModifiedDate()
    {
        return modifiedDate;
    }

    public void setModifiedDate(Date calendar)
    {
        this.modifiedDate = calendar;
    }

    public String getUserID()
    {
        return userID;
    }

    public void setUserID(String userID)
    {
        this.userID = userID;
    }

    public String getFirstName()
    {
        return firstName;
    }

    public void setFirstName(String firstName)
    {
        this.firstName = firstName;
    }

    public String getLastName()
    {
        return lastName;
    }

    public void setLastName(String lastName)
    {
        this.lastName = lastName;
    }

    public String getEmail()
    {
        return email;
    }

    public void setEmail(String email)
    {
        this.email = email;
    }

    public void setCountry(String country)
    {
        this.country = country;
    }

    public String getCountry()
    {
        return country;
    }

    public boolean getIsActive()
    {
        return activeStatus;
    }

    public void setIsActive(boolean isActive)
    {
        this.activeStatus = isActive;
    }

    public List<String> getGroupDetails()
    {
        return groupDetails;
    }

    public void setGroupDetails(List<String> groupDetails)
    {
        this.groupDetails = groupDetails;
    }
}
