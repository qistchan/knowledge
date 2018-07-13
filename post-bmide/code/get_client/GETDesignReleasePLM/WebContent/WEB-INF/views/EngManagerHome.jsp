<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
	
<c:url var="saveDesignRelease" value="/saveDesignRelease" />
	<div id="body">
		<div class="row-content">
			<!-- <div class="col-md-1 padding-left0">
				<div id="mySidenav" class="sidenav">
				  <a href="javascript:void(0)" class="closebtn" onclick="closeNav()">X</a>
				  <a href="#">About</a>		
				</div>
				<i class="fa fa-bars" style="font-size:32px;cursor:pointer;padding-left: 35px;padding-top: 15px;" onclick="openNav()"></i>
				<span style="font-size:30px;cursor:pointer" >open</span>
			</div> -->
			<br>
			<div class="col-md-15">
					
						<jsp:include page="UserHomeEngManEdit.jsp"/>
					
			</div>
		</div>
		
		
		<div class="modal fade" data-keyboard=false data-backdrop=static id="template" role="dialog">
		    <div class="modal-dialog modal-lg">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close templateCloseBtn" data-dismiss="modal">&times;</button>
		          <h4 class="modal-title templateHeader ">Template Selection</h4>
		        </div>
		        <div class="modal-body">
		        	<div class="col-md-1 noPadding">
						<label class="labelClass headerTextClass">Template</label>
					</div>
					<div class="col-md-3 noPadding">
						<select  data-style="btn-primary" data-live-search="true" id="templatesDropDown" data-width="180px">
							<option value="-1" selected>Please select</option>
							<option value="Locomotive">Locomotive</option>
							<option value="Engine">Engine</option>
						</select>
					</div>
					<div class="col-md-1 noPadding">
						<label class="labelClass">Scope Level</label>
					</div>
					<div class="col-md-3 noPadding">
						<select  data-style="btn-primary" data-live-search="true" id="scopesDropDown"  data-width="180px">
							<option value="-1" selected>Please select</option>
							<option value="Low">Low</option>
							<option value="Medium">Medium</option>
							<option value="High">High</option>
						</select>
						<input type="hidden" value="" id="designExistInTemplateModalHidden"/>
						<input type="hidden" value="" id="designNonExistInTemplateModalHidden"/>
					</div>
					<div class="col-md-4 noPadding input-group add-on">
						<input class="form-control widthPercent95" placeholder="Search" name="srch-term" id="srch-term" type="text">
						<div class="input-group-btn"><button class="btn btn-default search-btn" type="submit"><i class="glyphicon glyphicon-search"></i></button></div>
					</div>
					<div class="clearfix"></div>
					<div class="templateBody"></div>
		        </div>
		        <div class="modal-footer">
		        	<button type="button" id="templateScopeApply" class="btn btn-primary" style="display:none">Add</button>
		        	<button type="button" id="templateScopeReset" class="btn btn-primary" style="display:none">Reset</button>
				    <button type="button" class="btn btn-primary templateCloseBtn">Close</button>
				    
				</div>
		      </div>
		    </div>
  		</div>
		
		<div class="modal fade" data-keyboard=false data-backdrop=static  id="templateDropDownError" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close templateDropDownErrorCloseBtn">&times;</button>
		          <h4 class="modal-title">Warning</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red">Please select template!</label>
		        </div>
		        <div class="modal-footer">
				    <button type="button" class="btn btn-default templateDropDownErrorCloseBtn">Close</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade"  data-keyboard=false data-backdrop=static id="projectDropDownError" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close templateDropDownErrorCloseBtn">&times;</button>
		          <h4 class="modal-title">Warning</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red">Please select project!</label>
		        </div>
		        <div class="modal-footer">
				    <button type="button" class="btn btn-default projectDropDownErrorCloseBtn">Close</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade"  data-keyboard=false data-backdrop=static id="designReleaseListEmptyError" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close" data-dismiss="modal">&times;</button>
		          <h4 class="modal-title">Warning</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red">Please select templates to attach to project!</label>
		        </div>
		        <div class="modal-footer">
				    <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade"  data-keyboard=false data-backdrop=static id="noActivitySelectError" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close templateDropDownErrorCloseBtn">&times;</button>
		          <h4 class="modal-title">Warning</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red">Please select at least one activity to apply!</label>
		        </div>
		        <div class="modal-footer">
				    <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade" id="loadingModal" role="dialog">
  			<div class="vertical-alignment-helper centerAlign">
			    <div class="modal-dialog modal-sm vertical-align-center">
			      <div class="modal-content">
			        <div class="modal-body centerAlign">
			        	<img src="<c:url value="/images/spin80.gif" />"/>
			        </div>
			      </div>
			    </div>
			</div>
  		</div>
  		<div class="modal fade"  data-keyboard=false data-backdrop=static id="designExistError" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close" data-dismiss="modal">&times;</button>
		          <h4 class="modal-title">Warning</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red" id="designExistErrorLabel"></label>
		        </div>
		        <div class="modal-footer">
		         	<button type="button" id="templateScopeUpdate" class="btn btn-primary">Yes</button>
				    <button type="button" data-dismiss="modal" class="btn btn-default">No</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade"  data-keyboard=false data-backdrop=static id="onlyDesignIdExistError" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close" data-dismiss="modal">&times;</button>
		          <h4 class="modal-title">Warning</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red" id="onlyDesignExistErrorLabel"></label>
		        </div>
		        <div class="modal-footer">
				    <button type="button" data-dismiss="modal" class="btn btn-default">Ok</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade" data-keyboard=false data-backdrop=static  id="designSavedModal" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close designSaveOk">&times;</button>
		          <h4 class="modal-title">Message</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red" id="designSaveLabel"></label>
		        </div>
		        <div class="modal-footer">
		         	<button type="button" class="designSaveOk btn btn-primary">Close</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade"  data-keyboard=false data-backdrop=static id="designUpdatedModal" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close designUpdateOk">&times;</button>
		          <h4 class="modal-title">Message</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red" id="designUpdateLabel"></label>
		        </div>
		        <div class="modal-footer">
		         	<button type="button" class="designUpdateOk btn btn-primary">Close</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade"  data-keyboard=false data-backdrop=static id="designExistInModalError" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close designExistInModalErrorClose">&times;</button>
		          <h4 class="modal-title">Warning</h4>
		        </div>
		        <div class="modal-body projectInfoBody overFlowY">
		        	<label style="color:red" id="designExistInModalErrorLabel"></label>
		        	<input type="hidden" value="" id="designExistInModalErrorHidden"/>
		        </div>
		        <div class="modal-footer">
		         	<button type="button" id="designExistInModalErrorYes" class="btn btn-primary">Yes</button>
				    <button type="button" class="btn btn-default designExistInModalErrorClose">No</button>
				</div>
		      </div>
		    </div>
  		</div>
  		<div class="modal fade"  data-keyboard=false data-backdrop=static id="deleteConfirmationDialog" role="dialog">
		    <div class="modal-dialog modal-sm vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close" data-dismiss="modal">&times;</button>
		          <h4 class="modal-title">Message</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red" id="deleteConfirmationDialogLabel"></label>
		        </div>
		        <div class="modal-footer">
		         	<button type="button" id="deleteConfirmationDialogUpdate" class="btn btn-primary">Yes</button>
				    <button type="button" data-dismiss="modal" class="btn btn-primary">No</button>
				</div>
		      </div>
		    </div>
  		</div>
	</div>
<script>
	function openNav() {
		$("#mySidenav").css('width','150px');
		/* $("#content-Main").css('margin-left','150px'); */
	}
	
	function closeNav() {
		$("#mySidenav").css('width','0px');
		/* $("#content-Main").css('margin-left','0px'); */
	}
</script>