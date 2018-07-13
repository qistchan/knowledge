
//==================================================
// 
//  Copyright 2016 GE Transportation. All Rights Reserved.
//
//==================================================

package war.src.com.get.tc.Restservice;

import java.util.ArrayList;
import java.util.List;

import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import com.get.tc.soa.service.GETIDMServices;

/**
 * The Spring Boot Controller class for GET IDM Teamcenter Integration
 *
 * @author TCS Development Team
 */
@RestController
@RequestMapping("/plm_service")
// @EnableAutoConfiguration(exclude={DataSourceAutoConfiguration.class})
public class IdmController
{
    private GETIDMServices idmService;

    //private static final org.slf4j.Logger logger = LoggerFactory.getLogger(IdmController.class);

    /**
     * Restful Service method for establishing Teamcenter Session using Teamcenter login.
     * The HTTP Request type of this method is POST
     *
     * @param login - The LoginUser Structure containing the User credentials along with the Teamcenter Server Host Information
     * @return - The ResponseVo Service Response Object containing the Service Result (Pass/Fail) and the Service Resultant message
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/login", method = RequestMethod.POST, consumes = " application/json")
    @ResponseBody
    public ResponseVo login(@RequestBody LoginUser login) throws Exception
    {
        ResponseVo result = new ResponseVo();

        try
        {
            idmService.setHost(login.getM_host());
            idmService.login(login.getM_userID(), login.getM_password(), login.getM_group());
            result.setStatus(true);
            result.setMessage("Teamcenter Login Successfull");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            result.setStatus(false);
            result.setMessage(e.getMessage());
        }

        return result;
    }

    /**
     * Restful Service method for terminating an already existing Teamcenter Session
     * The HTTP Request type of this method is POST
     *
     * @return - The ResponseVo Service Response Object containing the Service Result (Pass/Fail) and the Service Resultant message
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/logout", method = RequestMethod.POST, consumes = " application/json")
    @ResponseBody
    public ResponseVo logout() throws Exception
    {
        ResponseVo result = new ResponseVo();

        try
        {
            idmService.logout();
            result.setStatus(true);
            result.setMessage("Teamcenter Logout Successfull");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            result.setStatus(false);
            result.setMessage(e.getMessage());
        }

        return result;
    }

    /**
     * Restful Service method for creating the given User in Teamcenter
     * The HTTP Request type of this method is POST
     *
     * @param user - The CreateUser Structure containing the User/Group-Role Information
     * @return - The ResponseVo Service Response Object containing the Service Result (Pass/Fail) and the Service Resultant message
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/create", method = RequestMethod.POST, consumes = " application/json")
    @ResponseBody
    public ResponseVo create(@RequestBody CreateUser user) throws Exception
    {
        ResponseVo result = new ResponseVo();

        try
        {
            idmService.createUser(user.getFirstName(), user.getLastName(), user.getUserID(),
                                  user.isActiveStatus(), user.getGroupDetails(),
                                  user.getEmail(), user.getCountry());
            result.setStatus(true);
            result.setMessage("User creation successfull");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            result.setStatus(false);
            result.setMessage(e.getMessage());
        }

        return result;
    }

    /**
     * Restful Service method for deactivating the given User in Teamcenter
     * The HTTP Request type of this method is POST
     *
     * @param user - The CreateUser Structure containing the User/Group-Role Information
     * @return - The ResponseVo Service Response Object containing the Service Result (Pass/Fail) and the Service Resultant message
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/deactivate", method = RequestMethod.POST, consumes = " application/json")
    @ResponseBody
    public ResponseVo deActivate(@RequestBody CreateUser user) throws Exception
    {
        ResponseVo result = new ResponseVo();

        try
        {
            idmService.deactivateUser(user.getUserID());
            result.setStatus(true);
            result.setMessage("User deactivated");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            result.setStatus(false);
            result.setMessage(e.getMessage());
        }

        return result;
    }

    /**
     * Restful Service method for adding a User to the given Group-Role Structure
     * The HTTP Request type of this method is POST
     *
     * @param user - The CreateUser Structure containing the User/Group-Role Information
     * @return - The ResponseVo Service Response Object containing the Service Result (Pass/Fail) and the Service Resultant message
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/addrole", method = RequestMethod.POST, consumes = " application/json")
    @ResponseBody
    public ResponseVo addRole(@RequestBody CreateUser user) throws Exception
    {
        ResponseVo result = new ResponseVo();

        try
        {
            idmService.addUserToGroup(user.getUserID(), user.getGroupDetails());
            result.setStatus(true);
            result.setMessage("User added to the given role(s)");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            result.setStatus(false);
            result.setMessage(e.getMessage());
        }

        return result;
    }

    /**
     * Restful Service method for removing a User frmo the given Group-Role Structure in Teamcenter
     * The HTTP Request type of this method is POST
     *
     * @param user - The CreateUser Structure containing the User/Group-Role Information
     * @return - The ResponseVo Service Response Object containing the Service Result (Pass/Fail) and the Service Resultant message
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/removerole", method = RequestMethod.POST, consumes = " application/json")
    @ResponseBody
    public ResponseVo removeRole(@RequestBody CreateUser user) throws Exception
    {
        ResponseVo result = new ResponseVo();

        try
        {
            idmService.removeUserFromGroup(user.getUserID(), user.getGroupDetails());
            result.setStatus(true);
            result.setMessage("User removed from the given role(s)");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            result.setStatus(false);
            result.setMessage(e.getMessage());
        }

        return result;
    }

    /**
     * Restful Service method for reactivating the given User in Teamcenter
     * The HTTP Request type of this method is POST
     *
     * @param user - The CreateUser Structure containing the User/Group-Role Information
     * @return - The ResponseVo Service Response Object containing the Service Result (Pass/Fail) and the Service Resultant message
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/reactivate", method = RequestMethod.POST, consumes = " application/json")
    @ResponseBody
    public ResponseVo reActivate(@RequestBody CreateUser user) throws Exception
    {
        ResponseVo result = new ResponseVo();

        try
        {
            idmService.reactivateUser(user.getUserID());
            result.setStatus(true);
            result.setMessage("User reactivated");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            result.setStatus(false);
            result.setMessage(e.getMessage());
        }

        return result;
    }

    /**
     * Restful Service method for identifying the User Status of the given User in Teamcenter
     * The HTTP Request type of this method is POST
     *
     * @param user - The CreateUser Structure containing the User Information
     * @return - The ResponseVo Service Response Object containing the Service Result (Pass/Fail) and the Service Resultant message
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/userStatus", method = RequestMethod.POST, consumes = " application/json")
    @ResponseBody
    public ResponseVo userStatus(@RequestBody CreateUser user) throws Exception
    {
        ResponseVo result = new ResponseVo();

        try
        {
            boolean status = idmService.isUserActive(user.getUserID());
            if (status)
            {
                result.setMessage("Active");
                result.setStatus(true);
            }
            else
            {
                result.setMessage("InActive");
                result.setStatus(true);
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
            result.setStatus(false);
            result.setMessage(e.getMessage());
        }

        result.getMessage();

        return result;
    }

    /**
     * Restful Service method for Information about all active Users in Teamcenter
     * The HTTP Request type of this method is GET
     *
     * @return - A List containing Information about all active Users in Teamcenter
     * @throws Exception - Any Teamcenter Exception thrown from the Teamcenter Server
     */
    @RequestMapping(value = "/getActiveUser", method = RequestMethod.GET, produces = " application/json")
    @ResponseBody
    public List<Object> getAllActiveUsers() throws Exception
    {
        ResponseVo resultVo = new ResponseVo();
        List<Object> listOfActiveUsers = new ArrayList<Object>();

        try
        {
            // listOfActiveUsers.putAll(idmService.getActiveUsers());
            listOfActiveUsers.addAll(idmService.getActiveUsers());
            resultVo.setStatus(true);
        }
        catch (Exception e)
        {
            e.printStackTrace();
            resultVo.setStatus(false);
            resultVo.setMessage(e.getMessage());
        }

        return listOfActiveUsers; // do not use Response object because this
                                  // causes issues when generating XML
                                  // automatically
    }

    /**
     * Getter method for retrieving the IDM Service instance for communicating with Teamcenter
     *
     * @return - The GETIDMServices instance mapped with this IDM Controller
     */
    public GETIDMServices getIdmService()
    {
        return idmService;
    }

    /**
     * Setter method for setting the IDM Service instance for communicating with Teamcenter
     *
     * @param idmService - The GETIDMServices instance to be mapped with this IDM Controller
     */
    public void setIdmService(GETIDMServices idmService)
    {
        this.idmService = idmService;
    }
}
