package com.get.ontrack.session;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.handler.HandlerInterceptorAdapter;
import org.springframework.web.servlet.resource.ResourceHttpRequestHandler;

import com.get.ontrack.common.PLMConstants;
import com.get.ontrack.common.Utils;
import com.get.ontrack.service.GETService;

@Component
public class SessionFailureHandler extends HandlerInterceptorAdapter {
	@Autowired
	private GETService getService;
	
	@Override
	public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
		return isResourceHandler(handler) ? true : doPreHandle(request, response, handler);
	}

	public boolean doPreHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
		Utils utils = new Utils();
		if (null != request) {
			//System.out.println("request.getServletPath()-->"+request.getServletPath());
			if (request.getServletPath().equals("/") || request.getServletPath().equals("/login") || request.getServletPath().equals("/ssoLogin") ||request.getServletPath().equals("/redirect") || request.getServletPath().equals("/checkSession")) {
				return true;
			} else if (request.getSession().getAttribute("user") != null) {
				return true;
			} else {
				HttpSession session = request.getSession(false);
				session.removeAttribute(PLMConstants.Objects.user);
				session.removeAttribute(PLMConstants.Objects.username);
				utils.removeAttributesInSession(session);
				session.invalidate();
				response.sendRedirect(request.getContextPath() + "/");
				return false;
			}
		}
		return false;
	}

	private boolean isResourceHandler(Object handler) {
		return handler instanceof ResourceHttpRequestHandler;
	}

}
