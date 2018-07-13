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
			
			<div class="col-md-15" style="padding-top: 10px;">
				<div class="col-md-12 container">
					<ul class="nav nav-tabs">
					    <li class="active"><a data-toggle="tab" href="#content-Main" class="dreTabCss">Build</a></li>
					    <li><a data-toggle="tab" href="#content-Edit" class="dreTabCss">Edit</a></li>
					    <li><a data-toggle="tab" href="#content-Publish" class="dreTabCss">Publish / Close</a></li>
					    <li><a data-toggle="tab" href="#content-Dashboard" class="dreTabCss">Dashboard</a></li>
	  				</ul>
	  			</div>
	  			<div class="clearfix"></div>
  				<div class="tab-content">
					<div id="content-Main" class="tab-pane fade in active">
						<jsp:include page="UserHomeContentMain.jsp"/>
					</div>
					<div id="content-Edit" class="tab-pane fade" >
						<jsp:include page="UserHomeContentEdit.jsp"/>
					</div>
					<div id="content-Publish" class="tab-pane fade">
						<jsp:include page="UserHomeContentPublish.jsp"/>
					</div>
					<div id="content-Dashboard" class="tab-pane fade" >
						<jsp:include page="UserHomeContentDashboard.jsp"/>
					</div>
				</div>
			</div>
		</div>
		
		
		<div class="modal fade" data-keyboard=false data-backdrop=static id="template" role="dialog">
		    <div class="modal-dialog modal-lg">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close templateCloseBtn" data-dismiss="modal">&times;</button>
		          <h4 class="modal-title templateHeader headerTextClass">Template Selection</h4>
		        </div>
		        <div class="modal-body">
		        	<div class="col-md-1 noPadding">
						<label class="labelClass">Template</label>
					</div>
					<div class="col-md-3 noPadding">
						<select  data-style="btn-primary" data-live-search="true" id="templatesDropDown" data-width="180px">
							<option value="-1" selected>Please select</option>
						
						</select>
					</div>
					<div class="col-md-1 noPadding">
						<label class="labelClass">Scope</label>
					</div>
					<div class="col-md-3 noPadding">
						<select  data-style="btn-primary" data-live-search="true" id="scopesDropDown"  data-width="180px">
							<option value="-1" selected>Please select</option>
							
						</select>
						<input type="hidden" value="" id="designExistInTemplateModalHidden"/>
						<input type="hidden" value="" id="designNonExistInTemplateModalHidden"/>
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
		
		<div class="modal fade"  data-keyboard=false data-backdrop=static id="templateDropDownError" role="dialog">
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
  		<div class="modal fade"  id="loadingModal" role="dialog">
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
  		<div class="modal fade" data-keyboard=false data-backdrop=static  id="onlyDesignIdExistError" role="dialog">
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
  		<div class="modal fade" data-keyboard=false data-backdrop=static  id="designUpdatedModal" role="dialog">
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