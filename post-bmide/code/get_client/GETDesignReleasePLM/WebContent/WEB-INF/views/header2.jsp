<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/functions" prefix="fn" %>
	<div class="row"><!-- class="row row-content" -->
		<div id="headercontent" style="height:35px;">
			<div class="col-md-4" style="height:35px;">
				<h1>
					 <img src="<c:url value="/images/GElectric_transportation_logo.svg.png" />" height="50px" style="padding-bottom:15px;"> 
				</h1>
			</div>
			
			<div class="col-md-4" align="center">
				<label style="font-size: 24px; color: #3b5998; font-weight: 800; font-family:ge-inspira,Arial,sans-serif; text-align: center;">Engineering Design Release - EDOT</label>
			</div>
			
				
			<div class="col-md-4">			
				<c:if test="${null != username}">
					<ul class="nav navbar-nav navbar-right">
						<li style="padding-right:5px;">
				    	   	<c:url value="/logout" var="logoutUrl" />	
				    		<%-- <a class="dernier" href="${logoutUrl}"><span class="glyphicon glyphicon-log-out" style="font-size:22px"></span>
				    		&nbsp;&nbsp;<label style="font-size:16px" color: #ff2300;>Logout</label></a> --%>
				    		<a class="dernier" href="${logoutUrl}"><span class="glyphicon glyphicon-log-out" style="font-size:18px"></span>
     						&nbsp;&nbsp;Logout</a>
				    	</li>
				    </ul>		
				 </c:if> 
			</div>
		</div>
	</div>
	
	