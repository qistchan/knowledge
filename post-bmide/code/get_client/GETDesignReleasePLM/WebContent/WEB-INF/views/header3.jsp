<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/functions" prefix="fn" %>
	<div class="row " style="height:30px;"><!-- row-content -->
		<div id="headercontent" style="height:35px">				
			<div  style="padding-right:5px;">
				<c:if test="${null != username}">
					<ul class="nav navbar-nav navbar-right">
				        <li style="padding-left:5px;padding-top: 0px;">
				        	<a href="#" id="roles" data-groupid = "${group}" data-roleid="${role}" style="padding-top: 5px;padding-bottom: 5px;padding-left: 25px;">
				        	<span class="glyphicon glyphicon-user" style="font-size:18px"></span>
				        	<label style="font-size:14px">${username}</label>
				        	<label style="font-size:14px;">- ${group} / </label>
				        	<label style="font-size:14px;">${role}</label></a>
				        </li>	
			      	</ul> 
				 </c:if> 
			</div>
			<%-- <div>			
				<c:if test="${null != username}">
					<ul class="nav navbar-nav navbar-right">
						<li style="padding-right:5px;">
				    	   	<c:url value="/logout" var="logoutUrl" />	
				    		
				    		<a class="dernier" href="${logoutUrl}" style="padding-top:5px;padding-bottom:5px"><span class="glyphicon glyphicon-log-out" style="font-size:18px;"></span>
     						&nbsp;&nbsp;Logout</a>
				    	</li>
				    </ul>		
				 </c:if> 
			</div> --%>
		</div>
	</div>
	
	<div class="modal fade" id="roledetails" role="dialog">
	    <div class="modal-dialog modal-lg">
	      <div class="modal-content" style="height:250px; width: 600px;">
	        <div class="modal-header">
	          <button type="button" class="close" data-dismiss="modal">&times;</button>
	          <h4 class="modal-title headerTextClass">Change Group / Role</h4>
	        </div>
	        <div class="modal-body" style="height:120px;  width: 600px;">
	        <div class="row">
			    <div class="col-sm-3" >
			      <p>Group: </p>
			    </div>
			    <div class="col-sm-9" >
			      <select name="group" id="group" style="width: 300px">
						<option value=""></option>
				</select>
			    </div>
		   </div>
		   <div class="row">
			    <div class="col-sm-3" >
			      <p>Roles: </p>
			    </div>
			    <div class="col-sm-9" >
			      <select name="role" id="role" style="width: 300px">
					<option value=""></option>
				</select>
			    </div>
		   </div>
		        	
	        </div>
	        <div class="modal-footer" style="height:25px; width: 600px;">
	        	<button type="button" class="btn btn-primary" id="update">OK</button>
			    <button type="button" class="btn btn-primary" data-dismiss="modal">Cancel</button>
			</div>
	      </div>
	    </div>
	</div>
	
	<div class="modal fade" id="rolesuccess" role="dialog">
	    <div class="modal-dialog modal-sm">
	      <div class="modal-content" >
	        <div class="modal-header">
	          <button type="button" class="close" data-dismiss="modal">&times;</button>
	          <h4 class="modal-title headerTextClass">Roles</h4>
	        </div>
	        <div class="modal-body" >
		        	<div id="roleUpdateLabel">
		        	</div>
	        </div>
	        <div class="modal-footer">
			    <button type="button" class="btn btn-primary" data-dismiss="modal">Close</button>
			</div>
	      </div>
	    </div>
	</div>