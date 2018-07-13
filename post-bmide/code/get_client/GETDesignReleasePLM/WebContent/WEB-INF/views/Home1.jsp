<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
	<div class="row-content" >
		<div class="col-md-4"></div>
		<div class="col-md-4">
			<div id="login" align="center" style="width: 100%;">
				
				<%-- <table style="width: 100%;" cellspacing="0" cellpadding="4">
				<tr><td>&nbsp;</td></tr>
					<!-- <tr><td>&nbsp;</td></tr>
					<tr><td>&nbsp;</td></tr> -->
					<tr>
						<td align="center">
							<form:form id="loginForm" modelAttribute="GETUser" action="login" method="POST">
							<div class="container">
							
								<div class="row">
								    <div class="col-sm-2" align="right">
								      <label>Group: </label>
								    </div>
								    <div class="col-sm-4" align="left" >
								      <select name="lgngroup" id="lgngroup" style="width: 300px">
											<option value=""></option>
									</select>
									&nbsp;&nbsp;<b id="errorgrpname" style="color:red; font-size:15px;"> </b>
								    </div>
							   </div>
							   <div class="row"></div>
							   <div class="row">
								    <div class="col-sm-2" align="right">
								      <label>Roles: </label>
								    </div>
								    <div class="col-sm-4" align="left">
								      <select name="lgnrole" id="lgnrole" style="width: 300px">
										<option value=""></option>
									</select>
									&nbsp;&nbsp;<b id="errorrolename" style="color:red; font-size:15px;"> </b>
								    </div>
							   </div>
							   <div class="row">
								    <div class="col-sm-6" align="right">
								      <p id="submit">
										<input type="submit" id="loginButton" class="btn btn-large btn-primary" value="Login" />
									</p>
								    </div>
							   </div>
							   </div>
							</form:form>
						</td>
					</tr>
				</table> --%>
				<table style="width: 100%;" cellspacing="0" cellpadding="4">
				<tr><td>&nbsp;</td></tr>
					<!-- <tr><td>&nbsp;</td></tr>
					<tr><td>&nbsp;</td></tr> -->
					<tr>
						<td align="center">
							<form:form id="loginForm1" modelAttribute="GETUser" action="loadRole" method="POST">
								<p id="homeattributes">
									<label>Group: </label>
									<select name="userGroup" id="lgngroup" style="width: 185px">
											<option value=""></option>
									</select>
									
								</p>&nbsp;&nbsp;<b id="errorgrpname" style="color:red;font-size:15px;"> </b><br/><br/>
								
								<p id="homeattributes">
									<label>Roles: </label>
									<select name="role" id="lgnrole" style="width: 185px">
										<option value=""></option>
									</select><br/>
									
								</p>
								
								<b id="errorrolename" style="color:red;font-size:15px;"> </b>
								<br/><br/>
								<p id="homeattributes"><c:if test="${not empty response }"><div style="color:red;font-size:15px;"><c:out value=" ${response}" ></c:out></div></c:if></p>
								<p id="submit">
									<input type="submit" id="loginButton" class="btn btn-large btn-primary" value="Get In" />
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
			
			dao.getGrps();
			//console.log(grps);
			$("#loginButton").click(function() {
				document.getElementById('errorgrpname').innerHTML = '';
				document.getElementById('errorrolename').innerHTML = '';
				if(($("#lgngroup").val() == '') )
				{
						document.getElementById('errorgrpname').innerHTML = 'Group Name cannot be empty';
						document.getElementById('lgngroup').focus();
						return false;
				}
				if(($("#lgnrole").val() == '') )
				{
						document.getElementById('errorrolename').innerHTML = 'Role Name cannot be empty';
						document.getElementById('lgnrole').focus();
						return false;
				}
				
			}); 
		});
	</script>
