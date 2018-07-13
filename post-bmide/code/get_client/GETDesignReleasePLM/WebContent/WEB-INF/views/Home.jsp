<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
	<div class="row-content" >
		<div class="col-md-4"></div>
		<div class="col-md-4">
			<div id="login" align="center">
				<table style="width: 100.5%;" cellspacing="0" cellpadding="4">
					<tr style="background-color: #337ab7;height: 80px;">
						<td>
							<h3>Login</h3>
						</td>
					</tr>
					<tr><td>&nbsp;</td></tr>
					<tr><td>&nbsp;</td></tr>
					<tr><td>&nbsp;</td></tr>
					<tr>
						<td align="center">
							<form:form id="loginForm" modelAttribute="GETUser" action="login" method="POST">
								<p id="homeattributes">
									<form:label path="userID">
										Username
									</form:label>
									<form:input path="userID"  class="form-control" name ="username" id="ssoid" style="width:185px;height:30px;color:black;" /><font color="red"> <form:errors path="userID"></form:errors></font>
								</p>&nbsp;&nbsp;<b id="errorusername" style="color:red;font-size:15px;"> </b><br/><br/>
								
								<p id="homeattributes">
									<form:label path="userPassword">
										Password
									</form:label>
									<form:password path="userPassword" class="form-control" name ="password" id="password" style="width:185px;height:30px;color:black;" /><font color="red"> <form:errors path="userPassword"></form:errors></font><br/>
								</p>
								<b id="errorpassword" style="color:red;font-size:15px;"> </b>
								<br/><br/>
								<p id="homeattributes"><c:if test="${not empty response }"><div style="color:red;font-size:15px;"><c:out value=" ${response}" ></c:out></div></c:if></p>
								<p id="submit">
									<input type="submit" id="loginButton" class="btn btn-large btn-primary" value="Login" />
								</p>
							</form:form>
						</td>
					</tr>
				</table>
			</div>
		</div>
		<div class="col-md-4"></div>
	</div>
	<script>
		$(document).ready(function() {
			
			
			$("#loginButton").click(function() {
				document.getElementById('errorusername').innerHTML = '';
				document.getElementById('errorpassword').innerHTML = '';
				if(($("#ssoid").val() == '') )
				{
						document.getElementById('errorusername').innerHTML = 'User Name cannot be empty';
						document.getElementById('ssoid').focus();
						return false;
				}
				if(($("#password").val() == '') )
				{
						document.getElementById('errorpassword').innerHTML = 'Password cannot be empty';
						document.getElementById('password').focus();
						return false;
				}
				
			}); 
		});
	</script>
