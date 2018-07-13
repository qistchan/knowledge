
package war.src.com.get.tc.Restservice;

import com.fasterxml.jackson.annotation.JsonProperty;

public class LoginUser
{
    @JsonProperty
    String m_host;
    String m_userID;
    String m_password;
    String m_group;

    public String getM_host()
    {
        return m_host;
    }

    public void setM_host(String m_host)
    {
        this.m_host = m_host;
    }

    public String getM_userID()
    {
        return m_userID;
    }

    public void setM_userID(String m_userID)
    {
        this.m_userID = m_userID;
    }

    public String getM_password()
    {
        return m_password;
    }

    public void setM_password(String m_password)
    {
        this.m_password = m_password;
    }

    public String getM_group()
    {
        return m_group;
    }

    public void setM_group(String m_group)
    {
        this.m_group = m_group;
    }
}
