<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<div class="row-content padding-bottom50">

	<div class="col-md-12 padding-top20">
		<div class="col-md-1 noPadding" style="width:50px;">
			<label class="labelClass">Project</label>
		</div>
		<div class="col-md-2 noPadding" style="width:200px;">
			<select  data-style="btn-primary" data-live-search="true" id="projectsEngECRDropDownEdit" data-width="180px">
				<option value="-1" selected>Please select</option>
				<c:forEach items="${projectsList}" var="item">
					<option value="${item}">${item}</option>
				</c:forEach>
			</select>
		</div>
		<div class="col-md-3 noPadding">
			&nbsp;<button type="button" class="btn btn-success projectInfoEngEditBtn" style="display:none;">Info</button>
		</div>
		<div class="col-md-3 noPadding">
			&nbsp;
		</div>
			
	</div>
	<div class="clearfix"></div>
	<div class="col-md-12 padding-top20">
	 <div class="col-md-6 padding-right0 boxShadow888 padding-left0">
	 	<div class="row padding-right10">
		 	<div class="col-md-1" style="width:180px;">
		 		<br>
		 		<select  data-style="btn-default" data-live-search="true" id="projectsEngECRDropDown" data-width="180px">
						<option value="-1" selected>Please select</option>
						<c:forEach items="${projectsList}" var="item">
							<option value="${item}">${item}</option>
						</c:forEach>
				</select>
					<br><br>
			</div>
		</div>
		<div class="row">
				<div class="col-md-8 table-responsive">      
	    	 		<table class="table designReleaseEditECRTable" id="dsgnengecrrelease">
	    	 			<thead>
								<tr>
									<th style="width: 4%"><label class="designLabelClass">BOM Line</label></th>
									<th style="width: 14%"><label class="designLabelClass">BOM Line Description</label></th>
									<th style="width: 4%"><label class="designLabelClass">EDOT</label></th>
								</tr>
						</thead>
						<tbody>
							<tr>
								<td>ML105</td>
								<td>Consol ASM</td>
								<td>EDOT - 760-95</td>
							</tr>
							<tr>
								<td>ML106</td>
								<td>Consol ASM</td>
								<td>EDOT - 760-96</td>
							</tr>
							<tr>
								<td>ML107</td>
								<td>Consol ASM</td>
								<td>EDOT - 760-97</td>
							</tr>
						</tbody>
	    	 		
	    	 		</table>
	    	 	</div>
	    	 	<div class="col-md-4 noPadding" style="width:200px;">
					<table class="table designReleaseEditECRTable" id="dsgnengecrrelease">
	    	 			<thead>
								<tr>
									<th style="width: 4%"><label class="designLabelClass">Implements</label></th>
								</tr>
						</thead>
						<tbody>
							<tr>							
								<td>EDOT - 760-95</td>
							</tr>
							<tr>
								<td>EDOT - 760-96</td>
							</tr>
							<tr>
								<td>EDOT - 760-97</td>
							</tr>
							<tr>
								<td>EDOT - 760-98</td>
							</tr>
							<tr>
								<td>EDOT - 760-99</td>
							</tr>
							<tr>
								<td>EDOT - 760-95</td>
							</tr>
						</tbody>
	    	 		
	    	 		</table>
				</div>
	    </div>
	    
	    </div>
  		
	</div>
</div>