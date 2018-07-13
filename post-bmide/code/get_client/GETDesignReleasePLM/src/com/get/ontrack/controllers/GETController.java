package com.get.ontrack.controllers;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Properties;
import java.util.TreeMap;

import javax.annotation.Resource;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.i18n.LocaleContextHolder;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.ui.ModelMap;
import org.springframework.util.CollectionUtils;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.i18n.SessionLocaleResolver;

import com.get.ontrack.common.GETDesignReleaseCommonOperations;
import com.get.ontrack.common.GETDesignReleaseConstants;
import com.get.ontrack.common.GETOnTrackConstants;
import com.get.ontrack.common.PLMConstants;
import com.get.ontrack.common.Utils;

import com.get.ontrack.dao.GETDao;
import com.get.ontrack.model.DesignRelease;
import com.get.ontrack.model.DesignReleaseWrapper;
import com.get.ontrack.model.EdotLinkedData;
import com.get.ontrack.model.GETUser;
import com.get.ontrack.model.LinkECRData;
import com.get.ontrack.model.TaskData;
import com.get.ontrack.service.GETService;
/**
 * This Controller class is manages request and response of user.
 * @author 750263
 */

@Controller
public class GETController {
	@Resource(name="configProperties")
	private Properties configProperties;
	@Autowired
	GETService getService;
	private ServletContext context;
	private static String IS_TCSSO_APP_TOKEN = "IS_TCSSO_APP_TOKEN";
	private static String TCSSO_SESSION_KEY = "TCSSO_SESSION_KEY";
	private static String TCSSO_APP_USER_ID = "TCSSO_APP_USER_ID";

	Utils utils = new Utils();
	GETDesignReleaseCommonOperations commonOp = new GETDesignReleaseCommonOperations();
	GETDao dao = new GETDao();

	public void setServletContext(ServletContext servletConfig)
	{
		this.context = servletConfig;
	}

	public ServletContext getServletContext()
	{
		return context;
	}
	/**
	 * **************************************************************************
	 * Description : Method to initialize the bean
	 * @param request
	 * @param response
	 * @param session
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/", method = RequestMethod.GET)
	public ModelAndView register(HttpServletRequest request, HttpServletResponse response,HttpSession session)throws Exception {
		if(null != session)
		{
			if(null == session.getAttribute(PLMConstants.Objects.user))
			{
				response.sendRedirect(request.getContextPath() + "/redirect");
			}
		}else{
			session = request.getSession(false);
			session.removeAttribute(PLMConstants.Objects.user);
			session.removeAttribute(PLMConstants.Objects.username);
			utils.removeAttributesInSession(session);
			session.invalidate();
			return new ModelAndView(PLMConstants.Objects.home, PLMConstants.Objects.GETUser, new GETUser());
		}
		return new ModelAndView(PLMConstants.Objects.home,PLMConstants.Objects.GETUser, new GETUser());
	}
	/**
	 * **************************************************************************
	 * Description : Method to redirect to the login
	 * @param request
	 * @param session
	 * @param response
	 * @throws IOException
	 ***************************************************************************
	 */
	@RequestMapping(value = "/redirect")
	public  void redirect(HttpServletRequest request, HttpSession session,HttpServletResponse response) throws IOException
	{
		session.setAttribute("url", "");
		if(configProperties != null && configProperties.containsKey(GETOnTrackConstants.Constants.hostConstant))
		{
			//String serverName = request.getServerName();
			session.setAttribute("url", configProperties.get(GETOnTrackConstants.Constants.hostConstant));
			if(configProperties.containsKey(GETOnTrackConstants.Constants.SSOAppIdConstant) && configProperties.containsKey( GETOnTrackConstants.Constants.SSOUrlConstant))
			{
				session.setAttribute("ssoAppId", configProperties.get(GETOnTrackConstants.Constants.SSOAppIdConstant).toString());
				session.setAttribute("ssoLURL", configProperties.get( GETOnTrackConstants.Constants.SSOUrlConstant).toString());
				response.sendRedirect(request.getContextPath() + "/ssoLogin");
			}
			else
			{
				response.sendRedirect(request.getContextPath() + "/login");	
			}
		}
	}
	/**
	 * **************************************************************************
	 * Description :Method to decide the home page
	 * @param role
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */

	public ModelAndView handleRoles(String role) throws Exception
	{
		ModelAndView modelView = null;

		if(null != role && role.length() > 0)
		{
			if(role.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE))
			{
				modelView = new ModelAndView(PLMConstants.Objects.userHome);
			}
			else if(role.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager))
			{
				modelView = new ModelAndView(PLMConstants.Objects.engManageruserHome);
			}
			else if(role.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer))
			{
				modelView = new ModelAndView(PLMConstants.Objects.enguserHome);
			}
			else if(role.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDesignCoordinator))
			{
				modelView = new ModelAndView(PLMConstants.Objects.designcorduserHome);
			}
			else
			{
				modelView = new ModelAndView(PLMConstants.Objects.userHome);
			}
		}
		else
		{
			modelView = new ModelAndView(PLMConstants.Objects.home1);
		}
		return modelView;
	}
	/**
	 * **************************************************************************
	 * Description :Method to SSO Login
	 * @param getUser
	 * @param result
	 * @param model
	 * @param request
	 * @param session
	 * @param responses
	 * @return
	 ***************************************************************************
	 */


	@RequestMapping(value = "/ssoLogin")
	public ModelAndView ssoLogin(@ModelAttribute("get5User") GETUser getUser, BindingResult result, Model model, HttpServletRequest request,
			HttpSession session,HttpServletResponse responses)  {
		String response = "";
		String userName = "";
		boolean isValidRole = false;
		getUser.setSessionId(session.getId());
		String strRole = null;
		List<Object> lists = null;

		if(result.hasErrors())
		{
			return new ModelAndView(PLMConstants.Objects.home);
		}

		if(null != getUser && (null == getUser.getUserID() || null == getUser.getUserPassword())){	
			try {

				session.setAttribute("url", "");
				if(configProperties != null && configProperties.containsKey(GETOnTrackConstants.Constants.hostConstant))
				{
					session.setAttribute("url", configProperties.get(GETOnTrackConstants.Constants.hostConstant));
				}
				Locale locale = LocaleContextHolder.getLocale();
				session.setAttribute(SessionLocaleResolver.LOCALE_SESSION_ATTRIBUTE_NAME, locale);
				String serverURL = (String)session.getAttribute("url");
				if(session.getAttribute("ssoAppId").toString() != null && session.getAttribute("ssoLURL").toString() != null)
				{
					String isSSOAppToken = request.getParameter(IS_TCSSO_APP_TOKEN);
					if(isSSOAppToken != null && isSSOAppToken.equalsIgnoreCase("true"))
					{
						session.setAttribute("ssoLogin", "true");
						String appUserID = request.getParameter(TCSSO_APP_USER_ID);
						String ssoSessionKey = request.getParameter(TCSSO_SESSION_KEY);
						lists = getService.ssoLoginWithSessionKey(serverURL, appUserID, ssoSessionKey,getUser,session.getAttribute("ssoAppId").toString(), session.getAttribute("ssoLURL").toString());
					}
					else
					{
						lists = getService.ssoLogin(serverURL, getUser, session.getAttribute("ssoAppId").toString(), session.getAttribute("ssoLURL").toString());
					}
				}
				strRole = getUser.getRole();
				if(strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE) ||
						strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager) ||
						strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer) ||
						strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDesignCoordinator))
				{
					isValidRole = true;
				}
				ModelAndView userHome = null;
				if(isValidRole)
				{
					userHome = handleRoles(getUser.getRole());
					userHome.addObject(PLMConstants.Objects.projectsList, lists.get(0));
				}
				else
				{
					userHome = handleRoles(null);
				}
				userName =getUser.getUserName()+" ("+ getUser.getUserID()+")";
				userHome.addObject(PLMConstants.Objects.username, userName);
				session.setAttribute(PLMConstants.Objects.user, getUser);
				session.setAttribute(PLMConstants.Objects.username, userName);
				userHome.addObject(PLMConstants.Objects.group, getUser.getuserGroup());
				userHome.addObject(PLMConstants.Objects.role, getUser.getRole());
				utils.removeAttributesInSession(session);
				return userHome;

			} catch (Exception e) {
				response = e.getMessage();
				ModelAndView home = new ModelAndView(PLMConstants.Objects.home);
				home.addObject(PLMConstants.Objects.response, response);
				home.addObject(PLMConstants.Objects.GETUser, new GETUser());
				return home;
			}
		}
		return new ModelAndView(PLMConstants.Objects.home);
	}
	/**
	 * **************************************************************************
	 * Description :Method to general Login
	 * @param getUser
	 * @param result
	 * @param model
	 * @param request
	 * @param session
	 * @param responses
	 * @return
	 ***************************************************************************
	 */

	@RequestMapping(value = "/login")
	public ModelAndView login(@ModelAttribute("get5User") GETUser getUser, BindingResult result, Model model, HttpServletRequest request,
			HttpSession session,HttpServletResponse responses)  {
		String response = "";
		String userName = "";
		boolean isValidRole = false;
		getUser.setSessionId(session.getId());
		String strRole = null;
		List<Object> lists = null;
		if(result.hasErrors())
		{
			return new ModelAndView(PLMConstants.Objects.home);
		}
		if(null != session && null != session.getAttribute(PLMConstants.Objects.user)){
			getUser = (GETUser)session.getAttribute(PLMConstants.Objects.user);
			ModelAndView userHome = null;
			try {
				if(isValidRole)
				{
					userHome = handleRoles(getUser.getRole());
				}
				else
				{
					userHome = handleRoles(null);
				}
				userHome.addObject(PLMConstants.Objects.projectsList, getService.getProjects(session.getId()));
				userName =getUser.getUserName()+" ("+ getUser.getUserID()+")";
				userHome.addObject(PLMConstants.Objects.username, userName);
				userHome.addObject(PLMConstants.Objects.group, getUser.getuserGroup());
				userHome.addObject(PLMConstants.Objects.role, getUser.getRole());
				utils.removeAttributesInSession(session);
				return userHome;
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		else if(null != getUser && (null == getUser.getUserID() || null == getUser.getUserPassword())){
			ModelAndView home = new ModelAndView(PLMConstants.Objects.home);
			home.addObject(PLMConstants.Objects.response, response);
			home.addObject(PLMConstants.Objects.GETUser, new GETUser());
			return home;}
		try
		{
			session.setAttribute("url", "");
			if(configProperties != null && configProperties.containsKey(GETOnTrackConstants.Constants.hostConstant))
			{
				session.setAttribute("url", configProperties.get(GETOnTrackConstants.Constants.hostConstant));
			}
			Locale locale = LocaleContextHolder.getLocale();
			session.setAttribute(SessionLocaleResolver.LOCALE_SESSION_ATTRIBUTE_NAME, locale);
			String serverURL = (String)session.getAttribute("url");

			lists = getService.login(getUser,serverURL);
			strRole = getUser.getRole();
			if(null != strRole && strRole.length() > 0)
			{
				if(strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE) ||
						strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager) ||
						strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer) ||
						strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDesignCoordinator))
				{
					isValidRole = true;
				}
			}
		}
		catch(Exception e)
		{
			response = e.getMessage();
		}
		if(response.length() > 0 && response.indexOf(PLMConstants.Objects.error) > -1)
		{
			ModelAndView home = new ModelAndView(PLMConstants.Objects.home);
			home.addObject(PLMConstants.Objects.response, response);
			home.addObject(PLMConstants.Objects.GETUser, new GETUser());
			return home;
		}
		else 
		{
			try {
				ModelAndView userHome = null;
				if(isValidRole)
				{
					userHome = handleRoles(getUser.getRole());
					userHome.addObject(PLMConstants.Objects.projectsList, lists.get(0));
				}
				else
				{
					userHome = handleRoles(null);
				}
				userName =getUser.getUserName()+" ("+ getUser.getUserID()+")";
				userHome.addObject(PLMConstants.Objects.username, userName);
				session.setAttribute(PLMConstants.Objects.user, getUser);
				session.setAttribute(PLMConstants.Objects.username, userName);
				userHome.addObject(PLMConstants.Objects.group, getUser.getuserGroup());
				userHome.addObject(PLMConstants.Objects.role, getUser.getRole());
				utils.removeAttributesInSession(session);
				return userHome;
			} catch (Exception e) {
				response = e.getMessage();
				ModelAndView home = new ModelAndView(PLMConstants.Objects.home);
				home.addObject(PLMConstants.Objects.response, response);
				home.addObject(PLMConstants.Objects.GETUser, new GETUser());
				return home;
			}
		}
	}
	/**
	 * **************************************************************************
	 * Description :Method to load the roles in intermediate page
	 * @param getUser
	 * @param result
	 * @param model
	 * @param session
	 * @return
	 ***************************************************************************
	 */
	@RequestMapping(value = "/loadRole")
	public ModelAndView loadRole(@ModelAttribute("get5User") GETUser getUser, BindingResult result, Model model,
			HttpSession session)
	{
		String userName = "";
		String response = "";
		List<Object> lists ;
		ModelAndView userHome = null;
		boolean isValidRole = false;
		try {
			if(null != session && null != session.getAttribute(PLMConstants.Objects.user)){
				GETUser getUser1;
				String strRole = null;
				getUser1 = (GETUser)session.getAttribute(PLMConstants.Objects.user);
				getUser1.setRole(getUser.getRole());
				session.setAttribute(PLMConstants.Objects.user, getUser1);
				lists =  getService.getGETProject(getUser1);
				strRole = getUser1.getRole();
				if(null != strRole && strRole.length() > 0)
				{
					if(strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDRE) ||
							strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngrManager) ||
							strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strEngineer) ||
							strRole.equalsIgnoreCase(GETDesignReleaseConstants.Role.strDesignCoordinator))
					{
						isValidRole = true;
					}
				}
				if(!isValidRole)
				{
					throw new Exception(GETOnTrackConstants.Messages.userNotAuthorized);
				}
				userHome = handleRoles(getUser1.getRole());
				userHome.addObject(PLMConstants.Objects.projectsList, lists.get(0));
				userName =getUser1.getUserName()+" ("+ getUser1.getUserID()+")";
				userHome.addObject(PLMConstants.Objects.username, userName);
				session.setAttribute(PLMConstants.Objects.user, getUser1);
				session.setAttribute(PLMConstants.Objects.username, userName);
				userHome.addObject(PLMConstants.Objects.group, getUser1.getuserGroup());
				userHome.addObject(PLMConstants.Objects.role, getUser1.getRole());
				utils.removeAttributesInSession(session);
				return userHome;
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			response = e.getMessage();
			ModelAndView home = new ModelAndView(PLMConstants.Objects.home1);
			home.addObject(PLMConstants.Objects.response, response);
			home.addObject(PLMConstants.Objects.GETUser, new GETUser());
			return home;
		}
		return userHome;
	}

	/**
	 * **************************************************************************
	 * Description :Method to update role and group sessions
	 * @param session
	 * @param group
	 * @param roles
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/updateRoleGroupsession",  method = RequestMethod.POST, params = {"group", "roles"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> updateRoleGroupsession(HttpSession session, @RequestParam(value = "group") String group, @RequestParam(value = "roles") String roles) throws Exception
	{
		if(null != session && null != session.getAttribute(PLMConstants.Objects.user)){
			GETUser getUser;
			getUser = (GETUser)session.getAttribute(PLMConstants.Objects.user);
			getUser.setRole(roles);
			getUser.setuserGroup(group);
			session.setAttribute(PLMConstants.Objects.user, getUser);
			ModelAndView userHome = handleRoles(getUser.getRole());
			userHome.addObject(PLMConstants.Objects.group, group);
			userHome.addObject(PLMConstants.Objects.role, roles);
		}
		return new ResponseEntity<String>("success", HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to get projects
	 * @param session
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/getProjects", method = RequestMethod.GET)
	public @ResponseBody Map<String, String> getProjects(HttpSession session) throws Exception
	{
		List<String> getProjects;
		Map<String,String> getProjectsMap = new HashMap<>();
		try{
			getProjects = getService.getProjects(session.getId());
		}catch(Exception e){
			throw new Exception(e);
		}
		getProjectsMap.put(PLMConstants.Objects.pleaseSelectValue, PLMConstants.Objects.pleaseSelect);
		for(String s : getProjects){
			getProjectsMap.put(s, s);
		}
		return getProjectsMap;
	}

	/**
	 * **************************************************************************
	 * Description :Method to get project data
	 * @param session
	 * @param projectId
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/getProjectData", method = RequestMethod.GET)
	public ResponseEntity<Map<String,List<String>>> getProjectData(HttpSession session,@RequestParam(value = "projectId") String projectId) throws Exception
	{
		Map<String,List<String>> projectDataMap;
		try{
			projectDataMap = getService.getProjectData(session.getId(),projectId);
		}catch(Exception e){
			throw new Exception(e);
		}
		session.setAttribute(PLMConstants.Objects.projectsDataMap, projectDataMap);
		return new ResponseEntity<Map<String,List<String>>>(projectDataMap, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to get template scope map
	 * @param session
	 * @param projectId
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/getTemplateScopeMap", method = RequestMethod.GET)
	public ResponseEntity<Map<String,ArrayList<String>>> getTemplateScopeMap(HttpSession session,@RequestParam(value = "projectId") String projectId) throws Exception
	{
		Map<String, ArrayList<String>> tempScopeMap;// = new HashMap<>();
		try{
			tempScopeMap = dao.getTemplateScopeMap (PLMConstants.item, PLMConstants.designReleaseTemplateID );
		}catch(Exception e){
			throw new Exception(e);
		}
		return new ResponseEntity<Map<String,ArrayList<String>>>(tempScopeMap, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to get associated design items
	 * @param session
	 * @param projectId
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@SuppressWarnings("unchecked")
	@RequestMapping(value = "/getAssociatedDesignItems", method = RequestMethod.GET)
	public ResponseEntity<List<DesignRelease>> getAssociatedDesignItems( HttpSession session, @RequestParam(value = "projectId") String projectId) 	throws Exception 
	{
		List<DesignRelease> designReleaseList ;
		List<DesignRelease> sortedEdotList = new ArrayList<DesignRelease>();
		Map<String, DesignRelease> mapBomLineEdotData = new HashMap<String, DesignRelease>();
		Map<String, List<String>> projectDataMap = (Map<String, List<String>>) session.getAttribute(PLMConstants.Objects.projectsDataMap);
		try {
			GETUser getUser = (GETUser)session.getAttribute(PLMConstants.Objects.user);
			designReleaseList = getService.getAssociatedDesignItems( session.getId(), projectId, projectDataMap.get(GETDesignReleaseConstants.Properties.P1Date),getUser);
			for (int designCount = 0; designCount < designReleaseList.size(); designCount++) {
				mapBomLineEdotData.put(designReleaseList.get(designCount).getBomLineItemId(), designReleaseList.get(designCount));
			}
			Map<String, DesignRelease> treeMap = new TreeMap<String, DesignRelease>(mapBomLineEdotData);
			Iterator<?> it = treeMap.entrySet().iterator();
			while ( it.hasNext() ) {
				Map.Entry entry = (Map.Entry) it.next();
				DesignRelease edotObj = (DesignRelease) entry.getValue();
				sortedEdotList.add(edotObj);
			}
		} catch (Exception e)
		{
			e.printStackTrace();
		}
		return new ResponseEntity<List<DesignRelease>>(sortedEdotList,HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to get Assigned ECR Data
	 * @param session
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/getAssignECRData", method = RequestMethod.GET)
	public ResponseEntity<List<LinkECRData>> getAssignECRData( HttpSession session) 	throws Exception 
	{
		List<LinkECRData> assignECRList;// = new ArrayList<LinkECRData>();
		List<LinkECRData> sortedEdotList = new ArrayList<LinkECRData>();
		Map<String, LinkECRData> mapBomLineEdotData = new HashMap<String, LinkECRData>();
		try {
			assignECRList = getService.getEdotData(session.getId());
			for (int designCount = 0; designCount < assignECRList.size(); designCount++) {
				mapBomLineEdotData.put(assignECRList.get(designCount).getBomLineItemId(), assignECRList.get(designCount));
			}
			Map<String, LinkECRData> treeMap = new TreeMap<String, LinkECRData>(mapBomLineEdotData);
			Iterator<?> it = treeMap.entrySet().iterator();
			while ( it.hasNext() ) {
				Map.Entry entry = (Map.Entry) it.next();
				LinkECRData edotObj = (LinkECRData) entry.getValue();
				sortedEdotList.add(edotObj);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return new ResponseEntity<List<LinkECRData>>(sortedEdotList,HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to get linked ECN and TD
	 * @param request
	 * @param edot
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/getLinkedECNandTD", method = RequestMethod.GET,  params = {"edot"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<List<EdotLinkedData>> getLinkedECNandTD(HttpServletRequest request, @RequestParam(value = "edot") String edot) throws Exception 
	{
		List<EdotLinkedData> ecnTDList = new ArrayList<EdotLinkedData>();
		List<EdotLinkedData> sortedEdotList = new ArrayList<EdotLinkedData>();
		Map<String, EdotLinkedData> mapBomLineEdotData = new HashMap<String, EdotLinkedData>();
		try {
			ecnTDList = getService.getLinkedECNAndTD(edot);
			for (int designCount = 0; designCount < ecnTDList.size(); designCount++) {
				mapBomLineEdotData.put(ecnTDList.get(designCount).getEdotId(), ecnTDList.get(designCount));
			}
			Map<String, EdotLinkedData> treeMap = new TreeMap<String, EdotLinkedData>(mapBomLineEdotData);
			Iterator<?> it = treeMap.entrySet().iterator();
			while ( it.hasNext() ) {
				Map.Entry entry = (Map.Entry) it.next();
				EdotLinkedData edotObj = (EdotLinkedData) entry.getValue();
				sortedEdotList.add(edotObj);
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
		return new ResponseEntity<List<EdotLinkedData>>(sortedEdotList,HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to get template scope
	 * @param session
	 * @param template
	 * @param scope
	 * @param checkedTemplates
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@SuppressWarnings({ "unchecked"})
	@RequestMapping(value = "/getTemplateScope", method = RequestMethod.GET)
	public ResponseEntity<Map<String,List<TaskData>>> getTemplateScope(HttpSession session,@RequestParam(value = "template") String template,@RequestParam(value = "scope") String scope,@RequestParam(value = "checkedTemplates") String[] checkedTemplates) throws Exception
	{
		Map<String,Map<String,List<TaskData>>> getTemplatesFile = new HashMap<>();
		Map<String,List<TaskData>> getTemplatesMap = new HashMap<>();
		String templateScope = template+"-"+scope;
		List<DesignRelease> tempDesignRelease = new ArrayList<DesignRelease>();
		if(null != session.getAttribute(PLMConstants.Objects.templatesFiles)){
			getTemplatesFile = (Map<String, Map<String, List<TaskData>>>) session.getAttribute(PLMConstants.Objects.templatesFiles);
		}else{
			try{
				getTemplatesFile = getService.getTemplateScopeFiles(session.getId(),template,scope); 
			}catch(Exception e){
				throw new Exception(e);
			}
			session.setAttribute(PLMConstants.Objects.templatesFiles, getTemplatesFile);
		}
		if(!CollectionUtils.isEmpty(getTemplatesFile)){
			for(Map.Entry<String,Map<String,List<TaskData>>> entry: getTemplatesFile.entrySet()){
				String key = entry.getKey();
				if(key.equalsIgnoreCase(templateScope)){
					getTemplatesMap = entry.getValue();
				}
			}
		}
		if(null !=  session.getAttribute(PLMConstants.Objects.tempDesignReleaseList)){
			tempDesignRelease = (List<DesignRelease>) session.getAttribute(PLMConstants.Objects.tempDesignReleaseList);
			List<String> tempDesignReleaseStrList = new ArrayList<String>();
			List<String> tempDesignReleaseScopeList = new ArrayList<String>();
			for(DesignRelease tData : tempDesignRelease){
				tempDesignReleaseStrList.add(tData.getBomLineItemId());
				if(templateScope.equalsIgnoreCase(tData.getTemplateName())){
					tempDesignReleaseScopeList.add(tData.getBomLineItemId());
				}
			}
			utils.updateTemplatesMap(getTemplatesMap , tempDesignReleaseStrList , tempDesignReleaseScopeList);
		}

		session.setAttribute(PLMConstants.Objects.templatesName, templateScope);
		session.setAttribute(PLMConstants.Objects.templatesMap, getTemplatesMap);
		return new ResponseEntity<Map<String,List<TaskData>>>(getTemplatesMap, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to update Temp Design ReleaseList
	 * @param session
	 * @param isChecked
	 * @param toUpdate
	 * @param checkedTemplates
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@SuppressWarnings({ "deprecation", "unchecked" })
	@RequestMapping(value = "/updateTempDesignTemplate", method = RequestMethod.GET)
	public ResponseEntity<List<DesignRelease>> updateTempDesignReleaseList(HttpSession session,@RequestParam(value = "isChecked") boolean isChecked,@RequestParam(value = "toUpdate") boolean toUpdate,@RequestParam(value = "checkedTemplates") String[] checkedTemplates) throws Exception
	{
		Map<String,List<TaskData>> getTemplatesMap = (Map<String, List<TaskData>>) session.getAttribute(PLMConstants.Objects.templatesMap);
		String templateScope = (String) session.getAttribute(PLMConstants.Objects.templatesName);
		List<DesignRelease> tempDesignRelease = new ArrayList<DesignRelease>();
		Date p1Date = new Date(PLMConstants.Objects.p1Date);
		Map<String,List<String>> projectDataMap = new HashMap<>();
		if(null != session.getAttribute(PLMConstants.Objects.projectsDataMap)){
			projectDataMap = (Map<String, List<String>>) session.getAttribute(PLMConstants.Objects.projectsDataMap);
		}
		if(!CollectionUtils.isEmpty(projectDataMap)){
			List<String> p1 =  projectDataMap.get(GETDesignReleaseConstants.Properties.P1Date);
			if(!CollectionUtils.isEmpty(p1)){
				if(!"".equalsIgnoreCase(p1.get(0))){
					p1Date = new Date(p1.get(0));
				}
			}
		}
		if(null !=  session.getAttribute(PLMConstants.Objects.tempDesignReleaseList)){
			tempDesignRelease = (List<DesignRelease>) session.getAttribute(PLMConstants.Objects.tempDesignReleaseList);
			if(toUpdate){
				utils.updateDesignReleaseList(tempDesignRelease, checkedTemplates , getTemplatesMap , templateScope , p1Date);
			}else{
				if(isChecked){
					utils.addToDesignReleaseList(tempDesignRelease, checkedTemplates , getTemplatesMap , templateScope , p1Date);
				}else{
					utils.deleteFromDesignReleaseList(tempDesignRelease, checkedTemplates);
				}
			}
		}else{
			utils.createDesignReleaseList(tempDesignRelease, checkedTemplates , getTemplatesMap , templateScope , p1Date);
			session.setAttribute(PLMConstants.Objects.tempDesignReleaseList,tempDesignRelease);
		}

		return new ResponseEntity<List<DesignRelease>> (tempDesignRelease,HttpStatus.OK);
	}

	@SuppressWarnings({ "unchecked"})
	@RequestMapping(value = "/applyTemplate", method = RequestMethod.POST, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<List<DesignRelease>>  applyTemplate(HttpSession session,@RequestParam(value = "checkedTemplates") String[] checkedTemplates) throws Exception
	{
		List<DesignRelease> designReleaseList = (List<DesignRelease>) session.getAttribute(PLMConstants.Objects.tempDesignReleaseList);
		utils.removeAttributesInSession(session);
		return new ResponseEntity<List<DesignRelease>>(designReleaseList, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description : Method to update template
	 * @param request
	 * @param designReleaseWrapper
	 * @param bindResult
	 * @param model
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */

	@SuppressWarnings({ "unchecked"})
	@RequestMapping(value = "/updateTemplate", method = RequestMethod.POST, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<List<DesignRelease>>  updateTemplate(HttpServletRequest request,@ModelAttribute(value = "designReleaseWrapper") DesignReleaseWrapper designReleaseWrapper,BindingResult bindResult, ModelMap model/*,@RequestParam(value = "checkedTemplates") String[] checkedTemplates,@RequestParam(value = "existingCheckedTemplates") String[] existingCheckedTemplates*/) throws Exception
	{
		HttpSession session = request.getSession(false);
		List<DesignRelease> designReleaseList = updateDesignReleaseList(designReleaseWrapper.getDesignReleaseList(),designReleaseWrapper.getProjectId());
		List<DesignRelease> tempDesignReleaseList = (List<DesignRelease>) session.getAttribute(PLMConstants.Objects.tempDesignReleaseList);
		Map<String,DesignRelease> tempDesignReleaseMap = new HashMap<String,DesignRelease>();
		int tempDesignReleaseListSize = null != tempDesignReleaseList ? tempDesignReleaseList.size():0;
		ArrayList<String> existingTemplates = new ArrayList<String>();
		ArrayList<String> checkedTemplates = new ArrayList<String>();
		String[] checkedTemplatesArr = new String[tempDesignReleaseListSize];
		int j=0;
		for(DesignRelease dRelease : designReleaseList){
			existingTemplates.add(dRelease.getBomLineItemId());
			dRelease.setEngrStartDateLabel(dRelease.getEngrStartDate()+" ("+commonOp.getFW(dRelease.getEngrStartDate())+")");
			dRelease.setEngrRequiredDateLabel(dRelease.getEngrRequiredDate()+" ("+commonOp.getFW(dRelease.getEngrRequiredDate())+")");
			dRelease.setDesignRequiredDateLabel(dRelease.getDesignRequiredDate()+" ("+commonOp.getFW(dRelease.getDesignRequiredDate())+")");
		}
		for(DesignRelease dRelease : tempDesignReleaseList){
			checkedTemplates.add(dRelease.getBomLineItemId());
			checkedTemplatesArr[j] = dRelease.getBomLineItemId();
			tempDesignReleaseMap.put(dRelease.getBomLineItemId(), dRelease);
			j++;
		}
		ArrayList<String> checkedTemplatesList = new ArrayList<String>();
		for(String tempChecked : checkedTemplates){
			checkedTemplatesList.add(tempChecked);
		}

		for(DesignRelease dRelease : designReleaseList){
			String designReleaseId = dRelease.getDesignReleaseId();
			String bomLineItemId = dRelease.getBomLineItemId();
			boolean designReleaseIdExist = null != designReleaseId?designReleaseId.length()>0?true:false:false;
			if(designReleaseIdExist){
				checkedTemplatesList.remove(bomLineItemId);
				continue;
			}else{
				int a =  Arrays.binarySearch(checkedTemplatesArr, bomLineItemId);
				if(a > -1 ){
					if(!CollectionUtils.isEmpty(tempDesignReleaseMap) && null != tempDesignReleaseMap.get(bomLineItemId)){
						utils.cloneDesignReleaseObject(tempDesignReleaseMap.get(bomLineItemId), dRelease);
					}
					checkedTemplatesList.remove(bomLineItemId);
				}
			}
		}
		for(String template : checkedTemplatesList){
			if(!CollectionUtils.isEmpty(tempDesignReleaseMap) && null != tempDesignReleaseMap.get(template)){
				designReleaseList.add(tempDesignReleaseMap.get(template));
			}
		}

		utils.removeAttributesInSession(session);
		return new ResponseEntity<List<DesignRelease>>(designReleaseList, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to reset template
	 * @param request
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */

	@RequestMapping(value = "/resetTemplate", method = RequestMethod.POST, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String>  resetTemplate(HttpServletRequest request) throws Exception
	{
		String response = PLMConstants.designAttachSuccess;
		HttpSession session = request.getSession(false);
		utils.removeAttributesInSession(session);
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description : Method to save design release object to teamcenter
	 * @param request
	 * @param designReleaseWrapper
	 * @param bindResult
	 * @param model
	 * @return
	 ***************************************************************************
	 */

	@RequestMapping(value = "/saveDesignRelease", method = RequestMethod.POST, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String>  saveDesignRelease(HttpServletRequest request,@ModelAttribute(value = "designReleaseWrapper") DesignReleaseWrapper designReleaseWrapper,BindingResult bindResult, ModelMap model) 
	{
		String response = PLMConstants.designAttachSuccess;
		HttpSession session = request.getSession(false);
		String projectId = designReleaseWrapper.getProjectId();
		List<DesignRelease> designReleaseList = updateDesignReleaseListToSave(designReleaseWrapper.getDesignReleaseList(),projectId);
		try{
			response = getService.saveDesignRelease(projectId,designReleaseList,session.getId());
		}catch(Exception e){
			return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to get ECR list
	 * @param request
	 * @return
	 ***************************************************************************
	 */
	@RequestMapping(value = "/getECRList", method = RequestMethod.POST,  produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<List<String>> getECRList(HttpServletRequest request) 

	{
		String response = PLMConstants.success;
		HttpSession session = request.getSession(false);
		List<String> ecrList = new ArrayList<>();
		GETUser getUser = (GETUser)(session).getAttribute(PLMConstants.Objects.user);

		try{
			String sessionUserId = getUser.getUserID(); // Session User Id
			String[] entries ={ "ECR No.", "Owning User", "Closure", "Disposition", "Maturity" };
			String[] values = { "*", sessionUserId, "Open", "None", "Elaborating" };

			ecrList = dao.getECRList( entries, values ) ;

		}catch(Exception e){
			e.printStackTrace();
		}
		return new ResponseEntity<List<String>>(ecrList, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to  list EDOT for selected ECR
	 * @param request
	 * @param ecrID
	 * @return
	 ***************************************************************************
	 */

	@RequestMapping(value = "/listEdotForSelectedECR", method = RequestMethod.POST,  params = {"ecrID"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<List<String>> listEdotForSelectedECR(HttpServletRequest request, @RequestParam(value = "ecrID") String ecrID) 
	{
		List<String> edotList = new ArrayList<>();
		try{
			edotList = dao.getEdotsForSelectedECR(ecrID) ;

		}catch(Exception e){
			e.printStackTrace();
		}
		return new ResponseEntity<List<String>>(edotList, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to list ECN for selected ECR
	 * @param request
	 * @param ecrID
	 * @return
	 ***************************************************************************
	 */
	@RequestMapping(value = "/listECNForSelectedECR", method = RequestMethod.POST,  params = {"ecrID"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<List<String>> listECNForSelectedECR(HttpServletRequest request, @RequestParam(value = "ecrID") String ecrID) 
	{
		List<String> ecnList = new ArrayList<>();
		try{
			{
				ecnList = dao.getECNList(ecrID) ;
			}
		}catch(Exception e){
			e.printStackTrace();
		}
		return new ResponseEntity<List<String>>(ecnList, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to list TD for selected ECN
	 * @param request
	 * @param ecnID
	 * @return
	 ***************************************************************************
	 */
	@RequestMapping(value = "/listTDForSelectedECN", method = RequestMethod.POST,  params = {"ecnID"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<List<String>> listTDForSelectedECN(HttpServletRequest request, @RequestParam(value = "ecnID") String ecnID) 
	{	
		List<String> TDList = null;
		try{
			TDList = dao.getTDForSelectedECN(ecnID) ;

		}catch(Exception e){
			e.printStackTrace();
		}
		return new ResponseEntity<List<String>>(TDList, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to link TD and EDOT with ECN
	 * @param request
	 * @param edot
	 * @param ecnID
	 * @param techData
	 * @return
	 ***************************************************************************
	 */
	@RequestMapping(value = "/linkTDandEDOTtoECN", method = RequestMethod.POST,  params = {"ecnID[]","edot[]","techData[]"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> linkTDandEDOTtoECN(HttpServletRequest request, @RequestParam(value = "edot[]") String edot[],  @RequestParam(value = "ecnID[]") String ecnID[],  @RequestParam(value = "techData[]") String techData[]) 
	{
		String response = PLMConstants.success;
		try{
			for(int i=0;i<ecnID.length;i++)
			{
				response = dao.linkTDandECNtoEDOt(edot[i],ecnID[i],techData[i]) ;	
			}
		}catch(Exception e){
			response=e.getMessage();
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to remove TD and EDOT from ECN
	 * @param request
	 * @param edot
	 * @param ecnID
	 * @param techData
	 * @return
	 ***************************************************************************
	 */
	@RequestMapping(value = "/removeTDandEDOTtoECN", method = RequestMethod.POST,  params = {"ecnID[]","edot[]","techData[]"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> removeTDandEDOTtoECN(HttpServletRequest request, @RequestParam(value = "edot[]") String edot[],  @RequestParam(value = "ecnID[]") String ecnID[],  @RequestParam(value = "techData[]") String techData[]) 
	{
		String response = PLMConstants.success;
		try{

			for(int i=0;i<ecnID.length;i++)
			{
				response = dao.removeTDandECNtoEDOt(edot[i],ecnID[i],techData[i]) ;	
			}

		}catch(Exception e){
			response=e.getMessage();
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to assign edot to ecr
	 * @param request
	 * @param edot
	 * @param ecrID
	 * @return
	 ***************************************************************************
	 */

	@RequestMapping(value = "/assignEDOTstoECR", method = RequestMethod.POST,  params = {"ecrID","edot[]"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> assignEDOTstoECR(HttpServletRequest request, @RequestParam(value = "edot[]") String edot[],  @RequestParam(value = "ecrID") String ecrID) 
	{
		String response = PLMConstants.success;
		try{
			response = dao.assignEDOTstoECR(edot,ecrID) ;

		}catch(Exception e){
			response=e.getMessage();
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to remove edot from ecr
	 * @param request
	 * @param edot
	 * @param ecrID
	 * @return
	 ***************************************************************************
	 */

	@RequestMapping(value = "/removeEdotFromECR", method = RequestMethod.POST,  params = {"ecrID","edot[]"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> removeEdotFromECR(HttpServletRequest request, @RequestParam(value = "edot[]") String edot[],  @RequestParam(value = "ecrID") String ecrID) 
	{
		String response = PLMConstants.success;
		try{

			response = dao.removeEdotFromECR(edot, ecrID) ;

		}catch(Exception e){
			return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to update design release
	 * @param request
	 * @param designReleaseWrapper
	 * @param bindResult
	 * @param model
	 * @return
	 ***************************************************************************
	 */
	@RequestMapping(value = "/updateDesignRelease", method = RequestMethod.POST, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String>  updateDesignRelease(HttpServletRequest request,@ModelAttribute(value = "designReleaseWrapper") DesignReleaseWrapper designReleaseWrapper,BindingResult bindResult, ModelMap model) 
	{
		String response = PLMConstants.designUpdateSuccess;
		HttpSession session = request.getSession(false);
		String projectId = designReleaseWrapper.getProjectId();
		List<DesignRelease> designReleaseList = filterDesignReleaseListToSave(designReleaseWrapper.getDesignReleaseList(),projectId);
		try{
			response = getService.updateDesignRelease(projectId,designReleaseList,session.getId());
		}catch(Exception e){
			return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to trigger workflow
	 * @param request
	 * @param subgrp
	 * @param edot
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */

	@RequestMapping(value = "/publishworkflow", method = RequestMethod.POST, params = {"subgrp[]", "edot[]"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> publishworkflow(HttpServletRequest request, @RequestParam(value = "subgrp[]") String subgrp[], @RequestParam(value = "edot[]") String edot[]) throws Exception
	{
		String response = PLMConstants.success;
		HttpSession session = request.getSession(false);
		boolean res = false;
		GETUser getuser;
		getuser = (GETUser)(session).getAttribute(PLMConstants.Objects.user);
		for(int i = 0; i < subgrp.length; i++ )
		{
			try{
				res = dao.executePublishWorkFlow(edot[i], subgrp[i], getuser, null);
				if(!res)
				{
					response = "failure";
				}

			}catch(Exception e){
				return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);
			}
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to delete edot.
	 * @param request
	 * @param edot
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/deleteEdot", method = RequestMethod.POST, params = {"edot[]"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> deleteEdot(HttpServletRequest request, @RequestParam(value = "edot[]") String edot[]) throws Exception
	{
		String response = PLMConstants.designRelease;
		boolean res = false;
		try{
			res = dao.deleteSelectedEDOTs( edot );
			if(!res)
			{
				response = PLMConstants.designReleaseError;//designReleaseError
			}
		}catch(Exception e){
			return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);
		}

		return new ResponseEntity<String>(response, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to get project list
	 * @param session
	 * @param mainGroup
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@SuppressWarnings("unchecked")
	@RequestMapping(value = "/getProjList",  params={"mainGrp"}, method = RequestMethod.GET)
	public ResponseEntity<List<String>> getProjList(HttpSession session,@RequestParam(value = "mainGrp") String mainGroup) throws Exception
	{
		List<String> grouplist = null;
		try{
			grouplist = getService.getMainGroupList(session.getId(),mainGroup);
			Collections.sort(grouplist);
		}catch(Exception e){
			e.printStackTrace();
		}
		return new ResponseEntity<List<String>>(grouplist, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to get main grp list
	 * @param session
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */

	@SuppressWarnings("unchecked")
	@RequestMapping(value = "/getMainGrpList", method = RequestMethod.GET)
	public ResponseEntity<List<String>> getMainGrpList(HttpSession session) throws Exception
	{
		List<String> mainGrplist = null;
		try{
			mainGrplist = getService.getMainGroupList(session.getId(),null);
			Collections.sort(mainGrplist);
		}catch(Exception e){
			e.printStackTrace();
		}
		return new ResponseEntity<List<String>>(mainGrplist, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to  get engg resource list
	 * @param session
	 * @param orgProject
	 * @param role
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@SuppressWarnings("unchecked")
	@RequestMapping(value = "/getEngrResourceList", params={"grpid", "engrole"}, method = RequestMethod.GET)
	public ResponseEntity<List<String>> getEngrResourceList(HttpSession session,@RequestParam(value = "grpid") String orgProject,@RequestParam(value = "engrole") String role) throws Exception
	{
		List<String> resourceList = new ArrayList<>();
		try{
			resourceList = getService.getResourceList(session.getId(), orgProject.trim(), role);
			Collections.sort(resourceList);
		}catch(Exception e){
			e.printStackTrace();
		}
		return new ResponseEntity<List<String>>(resourceList, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to get design resource list
	 * @param session
	 * @param orgProject
	 * @param role
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@SuppressWarnings("unchecked")
	@RequestMapping(value = "/getDesignResourceList", params={"grpid", "engrole"}, method = RequestMethod.GET)
	public ResponseEntity<List<String>> getDesignResourceList(HttpSession session,@RequestParam(value = "grpid") String orgProject,@RequestParam(value = "engrole") String role) throws Exception
	{
		List<String> listDesignResources = new ArrayList<String>();
		try{
			listDesignResources = getService.getResourceList(session.getId(), orgProject.trim(), role);
			/*List<String> listEngineer = getService.getResourceList(session.getId(), orgProject.trim(), GETDesignReleaseConstants.Role.strEngineer);
			if ( listEngineer != null && listEngineer.size() > 0 ) {
				for (String engineer : listEngineer) {
					if ( !listDesignResources.contains(engineer)){
						listDesignResources.add(engineer);
					}
				}
			}*/
			Collections.sort(listDesignResources);

		}catch(Exception e){
			throw new Exception(e);
		}
		return new ResponseEntity<List<String>>(listDesignResources, HttpStatus.OK);
	}

	/*@RequestMapping(value = "/getRoles", method = RequestMethod.GET)
	public ResponseEntity<List> getRoles(HttpSession session) throws Exception
	{
		Map grprole = new HashMap();
		//Map<String, List<String>> = 
		GETUser getUser;
		List group = null;
		try {
			getUser = (GETUser)session.getAttribute(PLMConstants.Objects.user);
			grprole = dao.getUserGroupAndRole(getUser.getUserID());
			group = new ArrayList();
			Map grp;

			Map<String, List<Object>> hm = new HashMap<String, List<Object>>();
			hm = grprole;

			for (Map.Entry<String, List<Object>> entry : hm.entrySet()) {
				//	System.out.println(entry.getKey()+"//"+entry.getValue());
				grp = new HashMap();
				grp.put("group", entry.getKey());
				grp.put("roles", entry.getValue());
				group.add(grp);
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			//return new ResponseEntity<List>(e.getMessage(), HttpStatus.OK);
		}

		return new ResponseEntity<List>(group, HttpStatus.OK);
	}*/
	/**
	 * **************************************************************************
	 * Description :Method to get roles
	 * @param session
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/getRoles", method = RequestMethod.GET)
	public ResponseEntity<List> getRoles(HttpSession session) throws Exception
	{
		Map<String, List<String>> grprole ;		
		GETUser getUser;
		List group = null;
		try {
			getUser = (GETUser)session.getAttribute(PLMConstants.Objects.user);
			grprole = dao.getUserGroupAndRole(getUser.getUserID());
			group = new ArrayList<String>();
			Map grp;
			for (Map.Entry<String, List<String>> entry : grprole.entrySet()) {
				grp = new HashMap();
				grp.put("group", entry.getKey());
				grp.put("roles", entry.getValue());
				group.add(grp);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return new ResponseEntity<List>(group, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to update group and role
	 * @param request
	 * @param group
	 * @param roles
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	@RequestMapping(value = "/updateGrouproles", method = RequestMethod.POST, params = {"group", "roles"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> updateGrouproles(HttpServletRequest request, @RequestParam(value = "group") String group, @RequestParam(value = "roles") String roles) throws Exception
	{
		String response = PLMConstants.success;
		HttpSession session = request.getSession(false);
		boolean res = false;
		String UserId = (String) session.getAttribute(PLMConstants.Objects.username);
		if ( UserId.contains("(") && UserId.contains(")") ){
			UserId =  UserId.substring(UserId.indexOf("(") + 1, UserId.indexOf(")"));
		}
		try{
			res = dao.setSessionGroupAndRole(UserId, group, roles);
			if(!res)
			{
				response = "failure";
			}
		}catch(Exception e){
			return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to update design release
	 * @param request
	 * @param edot
	 * @param resource
	 * @param promisedt
	 * @param comments
	 * @param actions
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */

	/*This method will update the attributes on EDOT based on button selection from UI*/
	@RequestMapping(value = "/updateDesign", method = RequestMethod.POST, params = {"edot[]", "promisedt[]", "comments[]", "resource[]", "action" }, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String>  updateDesign(HttpServletRequest request, @RequestParam(value = "edot[]") String edot[], @RequestParam(value = "resource[]") String resource[], @RequestParam(value = "promisedt[]") String promisedt[], @RequestParam(value = "comments[]") String comments[], @RequestParam(value = "action") String actions) throws Exception
	{
		String response = PLMConstants.success;
		//HttpSession session = request.getSession(false);
		String resourceName = null;
		String promiseDate  = null;
		String comment = null;
		boolean resp = false;
		Map<String, List<String>> mapRevDataList = new HashMap<String, List<String>>();
		List<String> edotsDataList = null;

		for(int count = 0; count < edot.length; count++ )
		{
			edotsDataList = new ArrayList<String>();
			try
			{
				if((actions.equalsIgnoreCase("accept")) || (actions.equalsIgnoreCase("updateDC") ))
				{

					//Promise date must be assigned, Should not be Null
					if(promisedt!= null && promisedt.length>0 )
					{
						promiseDate = promisedt[count];
						if( promiseDate != null && promiseDate.length() > 0)
						{
							edotsDataList.add(promiseDate);
						}
					}  else {
						edotsDataList.add(null);
					}

					if(comments != null && comments.length>0)
					{
						comment = getNewString(comments);
						if(comment != null &&  comment.length() > 0)
						{
							edotsDataList.add(comment);
						} 
					} else {
						edotsDataList.add(null);
					}

					//Set value for Resource Null, But don't update EDOT
					edotsDataList.add(null);

				} else if(actions.equalsIgnoreCase("reassign")) {

					//Make Promise Date Null
					edotsDataList.add(null);

					if(comments != null && comments.length>0)
					{
						comment = getNewString(comments);
						if(comment != null &&  comment.length() > 0)
						{
							edotsDataList.add(comment);
						}
					}  else {
						edotsDataList.add(null);
					}

					//Resource must be assigned
					if(resource != null && resource.length>0)
					{
						resourceName = getNewString(resource);
						if( resourceName != null && resourceName.length() > 0)
						{
							edotsDataList.add(resourceName);
						}
					} else 	{
						edotsDataList.add(null);
					}
				}
				else if(actions.equalsIgnoreCase("closure") || actions.equalsIgnoreCase("eng_reject") || actions.equalsIgnoreCase("reject")) //eng_reject reject
				{
					//Set value for Promise Date Null, But don't update EDOT
					edotsDataList.add(null);
					if(comments != null && comments.length>0)
					{
						comment = comments[count];
						//comment = getNewString(comments);
						if(comment != null &&  comment.length() > 0)
						{
							edotsDataList.add(comment);
						}
					}  else {
						edotsDataList.add(null);
					}
					//Set value for Resource Null, But don't update EDOT
					edotsDataList.add(null);
				}
				else   //Assign Action updates all 3 attributes
				{
					//Set value for Promise Date Null, But don't update EDOT
					edotsDataList.add(null);

					if(comments != null && comments.length>0)
					{
						comment = getNewString(comments);
						if(comment != null &&  comment.length() > 0)
						{
							edotsDataList.add(comment);
						} 
					} else {
						edotsDataList.add(null);
					}

					//Resource must be assigned
					if(resource != null && resource.length>0)
					{
						resourceName = getNewString(resource);
						if( resourceName != null && resourceName.length() > 0)
						{
							edotsDataList.add(resourceName);
						}

					} else {
						edotsDataList.add(null);
					}
				}
			}
			catch(ArrayIndexOutOfBoundsException e)
			{
				e.printStackTrace();
			}
			mapRevDataList.put(edot[count], edotsDataList);
		}
		try {
			resp = dao.updateBasedOnRole( mapRevDataList, actions);
			if(resp == false)
			{
				response = "not updated";
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);//"Unable to update-: "+ e.getMessage();
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	private String getNewString(String[] stringArr)
	{
		StringBuilder builder = new StringBuilder();
		for(String s : stringArr) {
			builder.append(s);
		}
		return builder.toString();
	}

	/**
	 * **************************************************************************
	 * Description :Method for Reassign on Publish page
	 * @param request
	 * @param edot
	 * @param resource
	 * @param subgrps
	 * @param comments
	 * @param actions
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	/*This method will update the attributes on EDOT based on button selection from UI*/
	@RequestMapping(value = "/publishReassign", method = RequestMethod.POST, params = {"edot[]", "subgrp[]", "comments[]", "resource[]", "action" }, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> publishReassign(HttpServletRequest request, @RequestParam(value = "edot[]") String edot[], @RequestParam(value = "resource[]") String resource[],  @RequestParam(value = "subgrp[]") String subgrps[], @RequestParam(value = "comments[]") String comments[], @RequestParam(value = "action") String actions) throws Exception
	{
		String response = PLMConstants.success;
		String resourceName = null;
		String orgProject  = null;
		String comment = null;
		boolean resp = false;
		Map<String, List<String>> mapRevDataList = new HashMap<String, List<String>>();
		List<String> edotsDataList = null;
		for(int count = 0; count < edot.length; count++ )
		{
			edotsDataList = new ArrayList<String>();
			try
			{
				if(actions.equalsIgnoreCase("dreReassign")) {
					//Make Promise Date Null
					//edotsDataList.add(null);
					if(subgrps != null && subgrps.length>0)
					{
						orgProject = subgrps[count];
						if(orgProject != null &&  orgProject.length() > 0)
						{
							edotsDataList.add(orgProject);
						} 
					} else {
						edotsDataList.add(null);
					}

					if(comments != null && comments.length>0)
					{
						//comment = comments[count];
						comment = getNewString(comments);
						if(comment != null &&  comment.length() > 0)
						{
							edotsDataList.add(comment);
						} 
					} else {
						edotsDataList.add(null);
					}

					//Resource must be assigned
					if(resource != null && resource.length>0)
					{
						resourceName = getNewString(resource);
						if( resourceName != null && resourceName.length() > 0)
						{
							edotsDataList.add(resourceName);
						}
					} else 	{
						edotsDataList.add(null);
					}
				}
				else if(actions.equalsIgnoreCase("dre_closure") || actions.equalsIgnoreCase("dre_reject")) //eng_reject reject
				{

					//Set value for Promise Date Null, But don't update EDOT
					edotsDataList.add(null);

					if(comments != null && comments.length>0)
					{
						//comment = comments[count];
						comment = getNewString(comments);
						if(comment != null &&  comment.length() > 0)
						{
							edotsDataList.add(comment);
						} 
					} else {
						edotsDataList.add(null);
					}

					//Set value for Resource Null, But don't update EDOT
					edotsDataList.add(null);
				}
			}
			catch(ArrayIndexOutOfBoundsException e)
			{
				e.printStackTrace();
			}
			mapRevDataList.put(edot[count], edotsDataList);
		}
		try {
			resp = dao.updateBasedOnRole( mapRevDataList, actions);
			if(resp == false)
			{
				response = "not updated";
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);
		}

		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to edit dre build page
	 * @param request
	 * @param bomLineItemList
	 * @param bomLineId
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	/*This method will update the attributes on EDOT based on button selection from UI*/
	@RequestMapping(value = "/editDREBuild", method = RequestMethod.POST, params = { "bomLineItemList[]", "bomLineId" }, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> editDREBuild(HttpServletRequest request, @RequestParam(value = "bomLineItemList[]") String bomLineItemList[], @RequestParam(value = "bomLineId") String bomLineId) throws Exception
	{
		ArrayList<String> bomLineList = new ArrayList<String>();
		String finalBomLine = "";

		for(int count = 0; count < bomLineItemList.length; count++ )
		{
			if(bomLineItemList != null && bomLineItemList.length>0)
			{
				bomLineList.add(bomLineItemList[count]);
			}

		}
		finalBomLine = dao.getEditDREBuild(bomLineList, bomLineId);
		return new ResponseEntity<String>(finalBomLine, HttpStatus.OK);

	}

	/**
	 * **************************************************************************
	 * Description :Method to update UI actions.
	 * @param request
	 * @param edot
	 * @param resource
	 * @param subgrp
	 * @param actions
	 * @return
	 * @throws Exception
	 ***************************************************************************
	 */
	/*This method will call the workflow process*/
	@RequestMapping(value = "/updateActions", method = RequestMethod.POST, params = {"edot[]", "subgrp[]", "resource[]", "action"}, produces=MediaType.APPLICATION_JSON_VALUE)
	public ResponseEntity<String> updateActions(HttpServletRequest request, @RequestParam(value = "edot[]") String edot[], @RequestParam(value = "resource[]") String resource[], @RequestParam(value = "subgrp[]") String subgrp[], @RequestParam(value = "action") String actions) throws Exception
	{
		String response = PLMConstants.success;
		HttpSession session = request.getSession(false);
		boolean res = false;
		String  edot_status[];
		edot_status = edot;
		GETUser getuser;
		getuser = (GETUser)(session).getAttribute(PLMConstants.Objects.user);
		for(int i = 0; i < subgrp.length; i++ )
		{
			try{
				res = dao.executePublishWorkFlow(edot_status[i], subgrp[i],  getuser, actions);

				if(!res)
				{
					response = "failure";
				}
			}catch(Exception e){
				return new ResponseEntity<String>(e.getMessage(), HttpStatus.OK);
			}
		}
		return new ResponseEntity<String>(response, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to update design release
	 * @param designReleaseList
	 * @param projectId
	 * @return
	 ***************************************************************************
	 */
	public List<DesignRelease> updateDesignReleaseList(List<DesignRelease> designReleaseList, String projectId){
		List<DesignRelease> newDesignReleaseList = new ArrayList<DesignRelease>();
		try {
			for(DesignRelease designRelease: designReleaseList){
				if(null != designRelease.getBomLineItemId()){
					designRelease.setProjectId(projectId);
					newDesignReleaseList.add(designRelease);
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return newDesignReleaseList;
	}

	/**
	 * **************************************************************************
	 * Description :Method to update design release
	 * @param designReleaseList
	 * @param projectId
	 * @return
	 ***************************************************************************
	 */
	public List<DesignRelease> updateDesignReleaseListToSave(List<DesignRelease> designReleaseList, String projectId){
		List<DesignRelease> newDesignReleaseList = new ArrayList<DesignRelease>();
		try {
			for(DesignRelease designRelease: designReleaseList){
				String designReleaseId = designRelease.getDesignReleaseId();
				boolean designReleaseIdExist = null != designReleaseId?designReleaseId.length()>0?true:false:false;
				if(null != designRelease.getBomLineItemId() && !designReleaseIdExist){
					designRelease.setProjectId(projectId);
					newDesignReleaseList.add(designRelease);
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return newDesignReleaseList;
	}

	/**
	 * **************************************************************************
	 * Description :method to filter design release
	 * @param designReleaseList
	 * @param projectId
	 * @return
	 ***************************************************************************
	 */

	public List<DesignRelease> filterDesignReleaseListToSave(List<DesignRelease> designReleaseList,String projectId){
		List<DesignRelease> newDesignReleaseList = new ArrayList<DesignRelease>();
		try {
			for(DesignRelease designRelease: designReleaseList){
				String designReleaseId = designRelease.getDesignReleaseId();
				boolean designReleaseIdExist = null != designReleaseId?designReleaseId.length()>0?true:false:false;
				if(designReleaseIdExist && designRelease.isEditChecked()){
					designRelease.setProjectId(projectId);
					newDesignReleaseList.add(designRelease);
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return newDesignReleaseList;
	}

	/**
	 * **************************************************************************
	 * Description : Method to log out
	 * @param session
	 * @return
	 ***************************************************************************
	 */
	@RequestMapping(value = "/logout", method = RequestMethod.GET)
	public ModelAndView logOut(HttpSession session)
	{
		try {
			getService.logOut(session.getId());
			session.removeAttribute(PLMConstants.Objects.user);
			session.removeAttribute(PLMConstants.Objects.username);
			utils.removeAttributesInSession(session);
			session.invalidate();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return new ModelAndView(PLMConstants.Objects.home, PLMConstants.Objects.GETUser, new GETUser());
	}

	public GETService getGetService() {
		return getService;
	}

	public void setGetService(GETService getService) {
		this.getService = getService;
	}

	/**
	 * **************************************************************************
	 * Description :Method to calculate start date
	 * @param session
	 * @param engrDuration
	 * @param backOffInput
	 * @return
	 ***************************************************************************
	 */

	@RequestMapping(value = "/getStartDate", method = RequestMethod.POST)
	public ResponseEntity<DesignRelease>  getStartDate(HttpSession session,@RequestParam(value = "engrDuration") String engrDuration,@RequestParam(value = "backOffInput") String backOffInput)
	{
		DesignRelease dRelease = new DesignRelease();
		Map<String,List<String>> projectDataMap = new HashMap<>();
		SimpleDateFormat dateFormatter = new SimpleDateFormat("dd-MMM-yyyy");
		try {
			if(null != session.getAttribute(PLMConstants.Objects.projectsDataMap)){
				projectDataMap = (Map<String, List<String>>) session.getAttribute(PLMConstants.Objects.projectsDataMap);
			}
			if(!CollectionUtils.isEmpty(projectDataMap)){
				List<String> p1 =  projectDataMap.get(GETDesignReleaseConstants.Properties.P1Date);
				if(!CollectionUtils.isEmpty(p1)){
					String piDateValue= p1.get(0);
					if ( piDateValue != null && piDateValue.length() > 0 ){
						Date p1Date = dateFormatter.parse(piDateValue);
						String sEnggStartDate = commonOp.getStartDate(p1Date,backOffInput, engrDuration);
						dRelease.setEngrStartDate(sEnggStartDate);
						dRelease.setEngrStartDateLabel(dRelease.getEngrStartDate()+" ("+commonOp.getFW(dRelease.getEngrStartDate())+")");
					}
				}
			}

		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return new ResponseEntity<DesignRelease>(dRelease, HttpStatus.OK);
	}
	/**
	 * **************************************************************************
	 * Description :Method to get the updated design required date
	 * @param session
	 * @param designDuration
	 * @param backOffInput
	 * @return
	 ***************************************************************************
	 */

	@RequestMapping(value = "/getDesignRequiredDate", method = RequestMethod.POST)
	public ResponseEntity<DesignRelease>  getDesignRequiredDate(HttpSession session,@RequestParam(value = "designDuration") String designDuration,@RequestParam(value = "backOffInput") String backOffInput)
	{
		DesignRelease dRelease = new DesignRelease();
		Map<String,List<String>> projectDataMap = new HashMap<>();
		SimpleDateFormat dateFormatter = new SimpleDateFormat("dd-MMM-yyyy");
		try {
			if(null != session.getAttribute(PLMConstants.Objects.projectsDataMap)){
				projectDataMap = (Map<String, List<String>>) session.getAttribute(PLMConstants.Objects.projectsDataMap);
			}
			if(!CollectionUtils.isEmpty(projectDataMap)){
				List<String> p1 =  projectDataMap.get(GETDesignReleaseConstants.Properties.P1Date);
				if(!CollectionUtils.isEmpty(p1)){
					String piDateValue= p1.get(0);
					if ( piDateValue != null && piDateValue.length() > 0 ){
						Date p1Date = dateFormatter.parse(piDateValue);
						String sDesgReqDate = commonOp.getDesignRequiredtDate(p1Date, backOffInput, designDuration);
						dRelease.setDesignRequiredDate(sDesgReqDate);
						dRelease.setDesignRequiredDateLabel(dRelease.getDesignRequiredDate()+" ("+ commonOp.getFW(dRelease.getDesignRequiredDate())+")");
					}
				}
			}

		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return new ResponseEntity<DesignRelease>(dRelease, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to update the fields on changing Backoff field
	 * @param session
	 * @param engrDuration
	 * @param backOffInput
	 * @param designDurationInput
	 * @return
	 ***************************************************************************
	 */

	@RequestMapping(value = "/getBackOffChangeDetails", method = RequestMethod.POST)
	public ResponseEntity<DesignRelease>  getBackOffChangeDetails(HttpSession session,@RequestParam(value = "engrDuration") String engrDuration,@RequestParam(value = "backOffInput") String backOffInput,@RequestParam(value = "designDurationInput") String designDurationInput)
	{
		DesignRelease dRelease = new DesignRelease();
		Map<String,List<String>> projectDataMap = new HashMap<>();
		SimpleDateFormat dateFormatter = new SimpleDateFormat("dd-MMM-yyyy");
		try {
			if(null != session.getAttribute(PLMConstants.Objects.projectsDataMap)){
				projectDataMap = (Map<String, List<String>>) session.getAttribute(PLMConstants.Objects.projectsDataMap);
			}
			if(!CollectionUtils.isEmpty(projectDataMap)){
				List<String> p1 =  projectDataMap.get(GETDesignReleaseConstants.Properties.P1Date);
				if(!CollectionUtils.isEmpty(p1)){
					String piDateValue= p1.get(0);
					if ( piDateValue != null && piDateValue.length() > 0 ){
						Date p1Date = dateFormatter.parse(piDateValue);
						String sEnggReqDate = commonOp.getEngrRequiredtDate(p1Date,backOffInput);
						String sEnggStartDate = commonOp.getStartDate(p1Date,backOffInput, engrDuration);
						String sDesgReqDate = commonOp.getDesignRequiredtDate(p1Date, backOffInput, designDurationInput);
						dRelease.setEngrRequiredDate(sEnggReqDate);
						dRelease.setDesignRequiredDate(sDesgReqDate);
						dRelease.setEngrStartDate(sEnggStartDate);
						dRelease.setEngrStartDateLabel(dRelease.getEngrStartDate()+" ("+commonOp.getFW(dRelease.getEngrStartDate())+")");
						dRelease.setEngrRequiredDateLabel(dRelease.getEngrRequiredDate()+" ("+commonOp.getFW(dRelease.getEngrRequiredDate())+")");
						dRelease.setDesignRequiredDateLabel(dRelease.getDesignRequiredDate()+" ("+commonOp.getFW(dRelease.getDesignRequiredDate())+")");
					}
				}
			}

		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return new ResponseEntity<DesignRelease>(dRelease, HttpStatus.OK);
	}

	/**
	 * **************************************************************************
	 * Description :Method to export the dashboard data to excel
	 * @param request
	 * @param res
	 * @throws IOException
	 ***************************************************************************
	 */

	@RequestMapping(value = "/exportDashboardDataNew")
	public void exportDashboardData1(HttpServletRequest request,HttpServletResponse res) throws IOException  
	{
		HSSFWorkbook workbook = new HSSFWorkbook(); 
		try{
			workbook = getService.exportDashboardNew( ) ;
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			workbook.write(baos);
			byte[] xls = baos.toByteArray();
			res.setContentType("application/vnd.ms-excel");
			res.setHeader("Content-disposition", "attachment;filename=\"Dashboard_"+new SimpleDateFormat("yyyy_MM_dd").format(Calendar.getInstance().getTime())+".xls\"");
			res.getOutputStream().write(xls);
		}catch(Exception e){

		}
	}
}
