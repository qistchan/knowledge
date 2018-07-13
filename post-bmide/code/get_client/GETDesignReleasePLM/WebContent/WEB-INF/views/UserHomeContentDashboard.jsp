<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<div class="row-content padding-bottom50">
	<div class="col-md-12 padding-top20">
		<div class="col-md-1 noPadding" style="width:50px;">
			<label class="labelClass">Project</label>
		</div>
		<div class="col-md-2 noPadding" style="width:150px;">
			<select  data-style="btn-primary" data-live-search="true" id="projectsDropDownDashboard" data-width="130px">
				<option value="-1" selected>Please select</option>
				<c:forEach items="${projectsList}" var="item">
					<option value="${item}">${item}</option>
				</c:forEach>
			</select>
		</div>
		<div class="col-md-2 noPadding" style="width:14%">
			&nbsp;<button type="button" class="btn btn-success projectInfoDbBtn" style="display:none;">Info</button>
			&nbsp; <button type="button" class="btn btn-info btn-sm projectDbRefresh" style="display:none;">
          <span class="glyphicon glyphicon-refresh"></span>         </button>
			&nbsp;<button type="button" class="btn btn-success exportDbBtn" style="display:none;">Export</button>
		</div>
		<div class="filterDashboardDataClass col-md-2 noPadding" style="display:none;"><label class="labelClass">Filter</label>
			 	<select  data-style="btn-primary" id="dreDashboardFilterData" class="dreDashboardFilterClass" name="dreDashboardFilterData" data-width="120px">
						<option value="-1" selected>Please select</option>
						<option value="Edit">Edit</option>
						<option value="Review">Review</option>
						<option value="Reassign">Reassign</option>
						<option value="Close">Close</option>
						<option value="Closed">Closed</option>
						<option value="ECR">ECR</option>
						<option value="ECN">ECN</option>
				</select>
		</div>
		<div class="col-md-3 noPadding">
			&nbsp;
		</div>
			<div class="col-md-3 noPadding input-group add-on" style="float:right">
				<input class="form-control widthPercent75" placeholder="Search" name="srch-term" id="dashboardSearchTerm" type="text">
				<div class="input-group-btn"><button class="btn btn-default dashboardSearch-btn" type="submit"><i class="glyphicon glyphicon-search"></i></button></div>
			</div>
	</div>
	<div class="clearfix"></div>
	<div class="col-md-12 padding-top15  ">
		<form:form  method="POST"  id="designReleaseEditWrapper" modelAttribute="designReleaseEditWrapper">
			<div class="col-md-12 padding-right0 boxShadow888 padding-left0">
			<input type="hidden" id="projectP1DateEditHidden" name="projectP1DateEdit" value=""/>
				<div class="table-responsive">          
					<!-- <table class="table designReleaseEditTableHead marginBottom0">
						
					</table> -->
					<div class="headerGridDashboardDive">
						<table class="table designReleaseDashboardTable" id="dsgnreleaseDashboard" style="white-space: nowrap !important;" width="100%">
							<thead>
								<tr>
									<th colspan="7"><label class="designLabelClassTopHeader">General</label></th>
									<th colspan="11"><label class="designLabelClassTopHeader">Engineering</label></th>
									<th colspan="8"><label class="designLabelClassTopHeader">Design</label></th>
									
								</tr>
								<tr>
									<th><label class="designLabelClass">Activity ID</label><input type="hidden" id="projectIdEditHidden" name="projectId" value=""/><input type="hidden" id="designReleaseEditListEmpty" value="true"/></th>
									<th ><label class="designLabelClass">Activity Description</label></th>
									<th ><label class="designLabelClass">EDOT</label></th>
									<th><label class="designLabelClass">Main Group</label></th>
									<th><label class="designLabelClass">Auto Close?</label></th>
									<th><label class="designLabelClass">Status</label></th>
									<th><label class="designLabelClass">State</label></th>
									
									<!-- <th><label class="designLabelClass">Duration</label></th> -->
									<th><label class="designLabelClass">Start Date</label></th>
									<!-- <th><label class="designLabelClass">Back Off</label></th> -->
									<th><label class="designLabelClass">Required Date</label></th>
									<th><label class="designLabelClass">Promise Date</label></th>
									<th><label class="designLabelClass">Actual Date</label></th> 
									<th><label class="designLabelClass">TD Release Date</label></th>
									<th><label class="designLabelClass">Date Change Reason</label></th>
									<!-- <th><label class="designLabelClass">Group</label></th> -->
									<th><label class="designLabelClass">Org Project</label></th>
									<th><label class="designLabelClass">Engineer</label></th>
									<th><label class="designLabelClass">ECR</label></th> 
									<th><label class="designLabelClass">Technical Data</label></th> 
									<th><label class="designLabelClass">Comment</label></th>
									
									
									<th><label class="designLabelClass">Required Date</label></th>
									<th><label class="designLabelClass">Promise Date</label></th>
									<th><label class="designLabelClass">Actual Date</label></th> 
									<th><label class="designLabelClass">Date Change Reason</label></th>
									<!-- <th><label class="designLabelClass">Group</label></th> -->
									<th><label class="designLabelClass">Org Project</label></th>
									<th><label class="designLabelClass">Coordinator</label></th>
									<th><label class="designLabelClass">ECN</label></th> 
									<th><label class="designLabelClass">Comment</label></th>
								</tr>
							</thead>
							<tbody >
								<c:choose>
									<c:when test="${empty projectsDesignList}">
										<script>
											$("#designReleaseEditListEmpty").attr('value','true');
										</script>
 										<c:forEach begin="0" end="12" var="item">
		  									<tr class='<c:if test="${item % 2 == 0}">backGround8FF</c:if>'>
		  										<!-- <td>&nbsp;</td> -->
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<!-- <td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td>
		  										<td>&nbsp;</td> -->
		  									</tr>
  										</c:forEach>
  									</c:when>
		  							<c:otherwise>
		  								<script>
											$("#designReleaseEditListEmpty").attr('value','false');
										</script>
		  								
		  							</c:otherwise>
  								</c:choose>
  							</tbody>
						</table>
					</div>
				</div>
			</div>
			
		</form:form>
	</div>
</div>	
<div class="modal fade" id="projectInfoDbEdit" role="dialog">
    <div class="modal-dialog modal-lg">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal">&times;</button>
          <h4 class="modal-title headerTextClass">Project Data</h4>
        </div>
        <div class="modal-body projectInfoBody">
        	<div class="col-md-12 width97 borderDDD noPadding">
				<div class="col-md-12 noPadding centerAlign backgroundCCC">
					<label class="labelClass fontClassLarger padding-left5" id="project_dashboard_id"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Project Name : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDbProjectName"></label>
				</div>
				
				<div class="col-md-6 noPadding ">
					<label class="labelClass fontHeader padding-left5">Engineering Product Line : </label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass" id="engrDbProductLine"></label>
				</div>
				
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Customer Name : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDbCustomerName"></label>
				</div>
				<div class="col-md-6 noPadding">
					<label class="labelClass fontHeader padding-left5">Order Number :</label>
				</div>
				<div class="col-md-6 noPadding">
					<label class="labelClass" id="projectDbOrderNo"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Apparatus Build Reference Date - Primary : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDbP1"></label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass fontHeader padding-left5">Apparatus Build Reference Date-Secondary : </label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass" id="projectDbK1"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Primary Project Number :</label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDbPrimaryNo"></label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass fontHeader padding-left5">Secondary Project Number :</label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass" id="projectDbSecondaryNo"></label>
				</div>
				<div class="clearfix"></div>
				
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Sales Force ID :</label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDbSalesForceId"></label>
				</div>
				
				<div class="clearfix"></div>
			</div>
        </div>
        <div class="modal-footer">
		    <button type="button" class="btn btn-primary" data-dismiss="modal">Close</button>
		</div>
      </div>
    </div>
</div>


  		
 <div class="modal fade" data-keyboard=false data-backdrop=static  id="exportUpdatedModal" role="dialog">
		    <div class="modal-dialog  vertical-align-center">
		      <div class="modal-content">
		        <div class="modal-header">
		          <button type="button" class="close exportUpdatedOk">&times;</button>
		          <h4 class="modal-title">Message</h4>
		        </div>
		        <div class="modal-body">
		        	<label style="color:red" id="exportUpdatedModalLabel"></label>
		        </div>
		        <div class="modal-footer">
		         	<button type="button" data-dismiss="modal" class="exportUpdatedOk btn btn-primary">Close</button>
				</div>
		      </div>
		    </div>
 </div>
