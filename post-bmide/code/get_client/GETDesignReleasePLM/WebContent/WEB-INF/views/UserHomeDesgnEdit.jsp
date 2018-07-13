<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<div class="row-content padding-bottom50">
	<div class="col-md-12 ">
		<div class="col-md-1 noPadding" style="width:50px;">
			<label class="labelClass">Project</label>
		</div>
		<div class="col-md-2 noPadding" style="width:150px;">
			<select  data-style="btn-primary" data-live-search="true" id="projectsDesgnDropDownEdit" data-width="130px">
				<option value="-1" selected>Please select</option>
				<c:forEach items="${projectsList}" var="item">
					<option value="${item}">${item}</option>
				</c:forEach>
			</select>
		</div>
		<div class="col-md-3 noPadding">
			&nbsp;<button type="button" class="btn btn-success projectInfoDesgnEditBtn" style="display:none;">Info</button>
			&nbsp; <button type="button" class="btn btn-info btn-sm projectRefresh" style="display:none;">
          <span class="glyphicon glyphicon-refresh"></span>         </button>
		</div>
		<div class="col-md-3 noPadding">
			&nbsp;
		</div>
			<div class="col-md-3 noPadding input-group add-on" style="float:right">
				<input class="form-control widthPercent100" placeholder="Search" name="srch-term" id="designSearchTerm" type="text">
				<div class="input-group-btn"><button class="btn btn-default designsearch-btn" type="submit"><i class="glyphicon glyphicon-search"></i></button></div>
			</div>
	</div>
	<div class="clearfix"></div>
	<div class="col-md-12 padding-top10">
		<form:form action="${saveDesignRelease}" method="POST"  id="designReleaseEditWrapper" modelAttribute="designReleaseEditWrapper">
			<div class="col-md-12 padding-right0 boxShadow888 padding-left0">
			<input type="hidden" id="projectP1DateEditHidden" name="projectP1DateEdit" value=""/>
			<input type="hidden" id="projectIdEditHidden" name="projectId" value=""/><input type="hidden" id="designReleaseEditListEmpty" value="true"/>
				<div class="table-responsive">          
					<!-- <table class="table designReleaseEditTableHead marginBottom0">
						
					</table> -->
					<div class="headerGridEditDive">
						<table class="table designReleaseEditTable" id="dsgnrelease">
							<thead>
								<tr>
									<th  style="vertical-align: middle; width: 2%" >
									<input type="checkbox" id="editdesignallcheckbox" name="editdesignallcheckbox" value=""/>
									
									</th>
									<th style="width: 4%"><label class="designLabelClass">Activity ID</label></th>
									<th style="width: 14%"><label class="designLabelClass">Activity Description</label></th>
									<th style="width: 4%"><label class="designLabelClass">EDOT</label></th>
									<th style="width: 6%"><label class="designLabelClass">Required Date</label></th>
									<th style="width: 6%"><label class="designLabelClass">Promise Date</label></th>
									<th style="width: 6%"><label class="designLabelClass">Actual Date</label></th>
									<th style="width: 10%"><label class="designLabelClass">Main Group</label></th> 
									<th style="width: 10%"><label class="designLabelClass">Design Org Project</label></th>
									<th style="width: 10%"><label class="designLabelClass">Resource</label></th>
									<th style="width: 6%"><label class="designLabelClass">ECR</label></th>
									<th style="width: 6%"><label class="designLabelClass">ECN</label></th>
									<th style="width: 6%"><label class="designLabelClass">TD</label></th>
									<th style="width: 18%"><label class="designLabelClass">Comment</label></th>
									<th style="width: 7%"><label class="designLabelClass">Status</label></th>
									<th style="width: 7%"><label class="designLabelClass">State</label></th>
								</tr>
							</thead>
							<tbody>
								<c:choose>
									<c:when test="${empty projectsDesignList}">
										<script>
											$("#designReleaseEditListEmpty").attr('value','true');
										</script>
 										<c:forEach begin="0" end="12" var="item">
		  									<tr class='<c:if test="${item % 2 == 0}">backGround8FF</c:if>'>
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
		  									</tr>
  										</c:forEach>
  									</c:when>
		  							<c:otherwise>
		  								<script>
											$("#designReleaseEditListEmpty").attr('value','false');
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
				  <button class="btn btn-large btn-primary" id="updateDesignReleaseEdit" data-action="update" type="button">Update</button>
				</p>
			</div>
		</form:form>
	</div>
</div>	
<div class="modal fade" id="projectInfoEdit" role="dialog">
    <div class="modal-dialog modal-lg">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal">&times;</button>
          <h4 class="modal-title headerTextClass">Project Data</h4>
        </div>
        <div class="modal-body projectInfoBody">
        	<div class="col-md-12 width97 borderDDD noPadding">
				<div class="col-md-12 noPadding centerAlign backgroundCCC">
					<label class="labelClass fontClassLarger padding-left5" id="project_edit_id"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Project Name : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectEditProjectName"></label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass fontHeader padding-left5">Engineering Product Line : </label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass" id="engrDesgnProductLine"></label>
				</div>
				<div class="col-md-6 noPadding  backGround8FF">
					<label class="labelClass fontHeader padding-left5">Customer Name : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectEditCustomerName"></label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass fontHeader padding-left5">Order Number :</label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass" id="projectEditOrderNo"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Apparatus Build Reference Date - Primary : </label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectEditP1"></label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass fontHeader padding-left5">Apparatus Build Reference Date-Secondary : </label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass" id="projectEditK1"></label>
				</div>
				<div class="clearfix"></div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Primary Project Number :</label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectEditPrimaryNo"></label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass fontHeader padding-left5">Secondary Project Number :</label>
				</div>
				<div class="col-md-6 noPadding ">
					<label class="labelClass" id="projectEditSecondaryNo"></label>
				</div>
				<div class="clearfix"></div>
				
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass fontHeader padding-left5">Sales Force ID :</label>
				</div>
				<div class="col-md-6 noPadding backGround8FF">
					<label class="labelClass" id="projectEditSalesForceId"></label>
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