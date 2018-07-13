<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>

<div class="row-content padding-bottom50">
	<div class="col-md-12 noPadding">
		<div class="col-md-1 noPadding" style="width:50px;">
			<label class="labelClass">Project</label>
		</div>
		<div class="col-md-2 noPadding" style="width:150px;">
			<select  data-style="btn-primary" data-live-search="true" id="projectsDropDown" data-width="130px">
				<option value="-1" selected>Please select</option>
				<c:forEach items="${projectsList}" var="item">
					<option value="${item}">${item}</option>
				</c:forEach>
			</select>
		</div>
		<div class="col-md-2 noPadding" style="width:15%">
			<button type="button" class="btn btn-large btn-success projectInfoBuildBtn" style="display:none;">Info</button>
			&nbsp;<button type="button" class="btn btn-large btn-primary templateBuildBtn" style="display:none;"> Template </button>
			&nbsp; <button type="button" class="btn btn-info btn-sm projectRefresh" style="display:none;">
          <span class="glyphicon glyphicon-refresh"></span>         </button>
		</div>
		<div class="filterBuildDataClass col-md-2 noPadding" style="display:none;"><label class="labelClass">Filter</label>
			 	<select  data-style="btn-primary" id="dreBuildFilterData" class="dreBuildFilterClass" name="dreBuildFilterData" data-width="120px">
						<option value="-1" selected>Please select</option>
						<option value="Build">Build</option>
						
				</select>
		</div>
		<div class="col-md-3 noPadding" >
			&nbsp;
		</div>
		<div class="col-md-3 noPadding input-group add-on" style="float:right">
			<input class="form-control widthPercent75" placeholder="Search" name="srch-term" id="buildSearchTerm" type="text">
			<div class="input-group-btn"><button class="btn btn-default search-btn" type="submit"><i class="glyphicon glyphicon-search"></i></button></div>
		</div>
	</div>
		<div class="col-md-12  padding-top15 marginBottom10" ></div>
		<form:form action="${saveDesignRelease}" method="POST"  id="designReleaseWrapper" modelAttribute="designReleaseWrapper">
			<div class="col-md-12 padding-right0 boxShadow888 padding-left0">
				<input type="hidden" id="projectP1DateHidden" name="projectP1Date" value=""/>
				<input type="hidden" id="projectIdHidden" name="projectId" value=""/>
				<input type="hidden" id="existingcheckedTemplatesHidden" name="existingCheckedTemplates" value=""/>
				<input type="hidden" id="designReleaseListEmpty" value="true"/>
				<div class="table-responsive">          
					<div class="headerGridDive" >
						<table class="table designReleaseTable marginBottom0"  id="designReleaseBuild" style="white-space: nowrap !important;" width="100%">
									<thead>
										<tr>
											<!-- <th><label class="designLabelClassBuild">EDOT</label></th> -->
											<th><label class="designLabelClassBuild">Activity ID</label></th>
											<th><label class="designLabelClassBuild">Activity Description</label></th>
											<th><label class="designLabelClassBuild">Engr Duration</label></th>
											<th><label class="designLabelClassBuild">Engr Start Date</label></th>
											<th><label class="designLabelClassBuild">Back Off</label></th>
											<th><label class="designLabelClassBuild">Engr Required Date</label></th>
											<th><label class="designLabelClassBuild">Design Duration</label></th>
											<th><label class="designLabelClassBuild">Design Required Date</label></th>
											<!-- <th><label class="designLabelClassBuild">Engr Sub Group</label></th> -->
											<th><label class="designLabelClassBuild">Engr Org Project</label></th>
											<!-- <th><label class="designLabelClassBuild">Design Sub Group</label></th> -->
											<th><label class="designLabelClassBuild">Design Org Project</label></th>
											<th><label class="designLabelClassBuild">Status</label></th>
											<th><label class="designLabelClassBuild">Template Source</label></th>
											<th><label class="designLabelClassBuild">EDOT</label></th>
											<th><label class="designLabelClassBuild">Action</label></th>
										</tr>
									</thead>
									<tbody >
 									<c:choose>
  									<c:when test="${empty projectsDesignList}">
  										<script>
  											$("#designReleaseListEmpty").attr('value','true');
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
		  									</tr>
		  								</c:forEach>
		  							</c:when>
		  							<c:otherwise>
		  								<script>
  											$("#designReleaseListEmpty").attr('value','false');
  										</script>
		  								<c:forEach varStatus="us" items="${projectsDesignList}" var="item">
		  									<tr>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].bomLineItemId" value="${item.bomLineItemId}"/>${item.bomLineItemId}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].description" value="${item.description}"/>${item.description}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].engrStartDate" value="${item.engrStartDate}"/>${item.engrStartDate}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].engrRequiredDate" value="${item.engrRequiredDate}"/>${item.engrRequiredDate}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].designRequiredDate" value="${item.designRequiredDate}"/>${item.designRequiredDate}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].engrComponentNo" value="${item.engrComponentNo}"/>${item.engrComponentNo}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].designComponentNo" value="${item.designComponentNo}"/>${item.designComponentNo}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].backOff" value="${item.backOff}"/>${item.backOff}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].engrDuration" value="${item.engrDuration}"/>${item.engrDuration}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].designDuration" value="${item.designDuration}"/>${item.designDuration}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].designReleaseId" value="${item.designReleaseId}"/>${item.designReleaseId}</td>
		  										<td><input type="hidden" name="designReleaseList[${us.index}].templateName" value="${item.templateName}"/>${item.templateName}</td>
		  										<td>
		  											<span title='Delete' class='glyphicon glyphicon-trash btn-md redColor cursorPointer deleteDesign' id="${item.bomLineItemId}_${item.templateName}"></span>
		  											<input type="hidden" id="designReleaseListEmpty" value="false"/>
		  										</td>
		  									</tr>
		  								</c:forEach>
		  							</c:otherwise>
		  						</c:choose>
		  					</tbody>
						</table>
					</div>
				</div>
			</div>
			<div class="col-md-12 padding-top20 padding-right0 padding-left0">
				<p style="float:right;">
				  <button class="btn btn-large btn-primary" id="saveDesignRelease" type="button">Save</button>
				  <button class="btn btn-large btn-primary" id="cancelDesignRelease" type="button">Reset</button>
				</p>
			</div>
		</form:form>	
</div>
<div class="modal fade" id="projectInfoBuild" role="dialog">
    <div class="modal-dialog modal-lg">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal">&times;</button>
          <h4 class="modal-title headerTextClass">Project Data</h4>
        </div>
        <div class="modal-body projectInfoBody">
        	<div class="col-md-12 width97 borderDDD noPadding">
				<div class="col-md-12 noPadding centerAlign backgroundCCC">
					<label class="labelClass fontClassLarger padding-left5" id="project_id"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Project Name : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDataProjectName"></label>
				</div>
				<div class="col-md-6 noPadding">
					<label class="labelClass fontHeader padding-left5">Engineering Product Line : </label>
				</div>
				<div class="col-md-6 noPadding">
					<label class="labelClass" id="engrProductLine"></label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Customer Name : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDataCustomerName"></label>
				</div>
				<div class="col-md-6 noPadding">
					<label class="labelClass fontHeader padding-left5">Order Number :</label>
				</div>
				<div class="col-md-6 noPadding">
					<label class="labelClass" id="projectDataOrderNo"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Apparatus Build Reference Date - Primary : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDataP1"></label>
				</div>
				<div class="col-md-6 noPadding">
					<label class="labelClass fontHeader padding-left5">Apparatus Build Reference Date-Secondary : </label>
				</div>
				<div class="col-md-6 noPadding">
					<label class="labelClass" id="projectDataK1"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Primary Project Number :</label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDataPrimaryNo"></label>
				</div>
				
				<div class="col-md-6 noPadding ">
					<label class="labelClass fontHeader padding-left5">Secondary Project Number :</label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass" id="projectDataSecondaryNo"></label>
				</div>
				<div class="clearfix"></div>
				
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Sales Force ID :</label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectDataSalesForceId"></label>
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