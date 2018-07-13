$(document).ready(function() {	
	
		$('#projectsDropDownDashboard').selectpicker();
		$('#templatesDropDownEdit').selectpicker();
		$('#scopesDropDownEdit').selectpicker();
		$('#dreDashboardFilterData').selectpicker();
		window.getProjectVal = $("#projectsDropDown").val();
		//getSubgrouponload();
		//dao.getSubgroup();
		/*$(document).tooltip();*/
		function getContextPath() {
			   return window.location.pathname.substring(0, window.location.pathname.indexOf("/",2));
			}
		
		window.setInterval(function(){
			$(".designReleaseDashboardTableHead").width($(".designReleaseDashboardTable").width());
			$(".designReleaseDashboardTable tbody tr td").each(function (i){
			       $(this).width($($(".designReleaseDashboardTableHead tr:first th")[i]).width());
			});
		}, 100);
		
		
		function resetScopeDropdown(){
			$("#scopesDropDown option:selected").removeAttr("selected");
	    	$("#scopesDropDown option:eq(0)").attr("selected", true);
	    	$('#scopesDropDown').parent().find('button').each(function(){
	    			$(this).children("span:first").empty();
	    			$(this).children("span:first").append('Please Select')
	    	});
	    	$('#scopesDropDown').parent().find('.dropdown-menu').find('li').each(function(){
	    		if($(this).attr('class') == 'selected'){
	    			$(this).removeAttr('class');
	    		}
	    		if($(this).attr('data-original-index')=='0'){
	    			$(this).attr('class','selected')
	    		}
	    	});
		}
		
		
		function createDesignReleaseEditEmptyTableRow(index){
			$("#designReleaseEditListEmpty").attr('value','true');
			var className = "";
			if(index % 2 == 0){
				className = "backGround8FF";
			}
			var row = $('<tr>');
			row.attr('class',className);
			for(var i=0;i<26;i++){
				row.append($('<td>').append('&nbsp;'));
			}
			return row;
		}
		
		function createDesignReleaseEditTableRow(index , value){
			$("#designReleaseEditListEmpty").attr('value','false');
			var className = "";
			if(index % 2 == 0){
				className = "backGround8FF";
			}
			var row = $("<tr>");
    		row.attr('class',className);
    		
    		
    		
    		var edotColumn = $('<td>');
    		var edotInput = $("<input type='hidden' class='edotHiddenId' id='edotId"+index+"' name='designReleaseList[" + index +"].edot' value='" + value.designReleaseId + "'>"+ value.designReleaseId +"</input>");
    		edotColumn.append(edotInput);
    		
    		var statusColumn = $('<td>');
    		var statusInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + value.status + "'>" + value.status +"</input>");
    		statusColumn.append(statusInput);
    		
    		var bomLineItemIdColumn = $('<td>');
    		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+index+"' name='designReleaseList[" + index +"].bomLineItemId' value='" + value.bomLineItemId + "'>"+ value.bomLineItemId +"</input>");
    		bomLineItemIdColumn.append(bomLineItemIdInput);
    		
    		var descriptionColumn = $('<td>',{"style" : "text-align:left"});
    		var descriptionInput = $("<input type='hidden' class='description' id='description"+index+"' name='designReleaseList[" + index +"].description' value='" + value.description + "'>" + value.description +"</input>");
    		descriptionColumn.append(descriptionInput);
    		
    		var engrDurationColumn = $('<td>');
    		var engrDurationInput = $("<input type='hidden' class='engrDurationInput' id=engrDuration_"+index+" name='designReleaseList[" + index +"].engrDuration' value='" + value.engrDuration + "'>" + value.engrDuration +"</input>");
    		engrDurationColumn.append(engrDurationInput);
    		
    		var engrStartDateColumn = $("<td id=engrStartDateTD_"+index+">");
    		var engrStartDateInput = $("<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + value.engrStartDate + "'>" + value.engrStartDateLabel +"</input>");
    		engrStartDateColumn.append(engrStartDateInput);
    		
    		var backOffColumn = $('<td>');
    		var backOffInput = $("<input type='hidden' class='backOffInput' id=backOff_"+index+" name='designReleaseList[" + index +"].backOff' value='" + value.backOff + "'>" + value.backOff +"</input>");
    		backOffColumn.append(backOffInput);
    		
    		var engrRequiredDateColumn = $("<td id=engrRequiredDateTD_"+index+">");
    		var engrRequiredDateInput = $("<input type='hidden' class='engrRequiredDateInput' id=engrRequiredDate_"+index+" name='designReleaseList[" + index +"].engrRequiredDate' value='" + value.engrRequiredDate + "'>" + value.engrRequiredDateLabel +"</input>");
    		engrRequiredDateColumn.append(engrRequiredDateInput);
    		
    		var engrPromiseDateColumn = $('<td>');
    		var engrPromiseDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrPromiseDate' value='" + value.engrPromiseDate + "'>" + value.engrPromiseDateLabel +"</input>");
    		engrPromiseDateColumn.append(engrPromiseDateInput);
    		
    		var engrActualDateColumn = $('<td>');
    		var engrActualDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrActualDate' value='" + value.engrActualDate + "'>" + value.engrActualDateLabel +"</input>");
    		engrActualDateColumn.append(engrActualDateInput);
    		
    		var engrDateChangeReasonColumn = $('<td>');
    		var engrDateChangeReasonInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrDateChangeReason' value='" + value.engrDateChangeReason + "'>" + value.engrDateChangeReason +"</input>");
    		engrDateChangeReasonColumn.append(engrDateChangeReasonInput);
    		
    		var engrComponentNoColumn = $('<td>',{"style" : "text-align:left"});
    		var engrComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrComponentNo' value='" + value.engrComponentNo + "'>" + value.engrComponentNo +"</input>");
    		engrComponentNoColumn.append(engrComponentNoInput);
    		
    		var engrResourceColumn = $('<td id=engresource_'+index+'>');
    		var engrResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrResource' value='" + value.engrResource + "'>" + value.engrResource +"</input>");
    		//var engresourcediv = $("<div id='engresource[" + index +"]'>");
    		engrResourceColumn.append(engrResourceInput);
    		//engrResourceColumn.append(engresourcediv);
    		
    		var engrECRColumn = $('<td>');
    		var engrECRInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrECR' value='" + value.engrECR + "'>" + value.engrECR +"</input>");
    		engrECRColumn.append(engrECRInput);
    		
    		var engrCommentColumn = $('<td>');
    		var engrCommentInput = $("<textarea rows='2' cols='30' style='display:none' name='designReleaseList[" + index +"].engrComment' id=engComments_"+index+">" + value.engrComment +"</textarea><span id=engrcmnt"+index+" class='cmntWrapper' >"+value.engrComment+"</span>");
    		engrCommentColumn.append(engrCommentInput);
    		
    		var designDurationColumn = $('<td>');
    		var designDurationInput = $("<input type='hidden' class='designDurationInput' id=designDuration_"+index+" name='designReleaseList[" + index +"].designDuration' value='" + value.designDuration + "'>" + value.designDuration +"</input>");
    		designDurationColumn.append(designDurationInput);
    		
    		var designRequiredDateColumn = $("<td  id=designRequiredDateTD_"+index+">");
    		var designRequiredDateInput = $("<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + value.designRequiredDate + "'>" + value.designRequiredDateLabel +"</input>");
    		designRequiredDateColumn.append(designRequiredDateInput);
    		
    		var designPromiseDateColumn = $('<td>');
    		var designPromiseDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].designPromiseDate' value='" + value.designPromiseDate + "'>" + value.designPromiseDateLabel +"</input>");
    		designPromiseDateColumn.append(designPromiseDateInput);
    		
    		var designActualDateColumn = $('<td>');
    		var designActualDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].designActualDate' value='" + value.designActualDate + "'>" + value.designActualDateLabel +"</input>");
    		designActualDateColumn.append(designActualDateInput);
    		
    		var designDateChangeReasonColumn = $('<td>');
    		var designDateChangeReasonInput = $("<input type='hidden' name='designReleaseList[" + index +"].designDateChangeReason' value='" + value.designDateChangeReason + "'>" + value.designDateChangeReason +"</input>");
    		designDateChangeReasonColumn.append(designDateChangeReasonInput);
    		
    		var designComponentNoColumn = $('<td>',{"style" : "text-align:left"});
    		var designComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].designComponentNo' value='" + value.designComponentNo + "'>" + value.designComponentNo +"</input>");
    		designComponentNoColumn.append(designComponentNoInput);
    		
    		var designResourceColumn = $('<td id=designresource_'+index+'>');
    		var designResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].designResource' value='" + value.designResource + "'>" + value.designResource +"</input>");
    		designResourceColumn.append(designResourceInput);
    		
    		var designECNColumn = $('<td>');
    		var designECNInput = $("<input type='hidden' name='designReleaseList[" + index +"].designECN' value='" + value.designECN + "'>" + value.designECN +"</input>");
    		designECNColumn.append(designECNInput);
    		
    		var designCommentColumn = $('<td>');
    		var designCommentInput = $("<textarea rows='2' cols='30' style='display:none' name='designReleaseList[" + index +"].designComment' id=dsgnComments_"+index+" >" + value.designComment +"</textarea><span id=dsgncmnt"+index+" class='cmntWrapper'>"+value.designComment+"</span>");
    		designCommentColumn.append(designCommentInput);
    		
    		var autoCloseColumn = $('<td>');
    		if(value.autoClose == true)
			{
    			var autoCloseInput = $("<input type='hidden' class='autoclosecheckbox' id='designautoClose"+index+"' name='designReleaseList[" + index +"].autoClose' value='true' checked  onclick='autoClose(this, "+index+")'   >Yes</input>");
			}
    		
    		else
			{
    			var autoCloseInput = $("<input type='hidden' class='autoclosecheckbox' id='designautoClose"+index+"' name='designReleaseList[" + index +"].autoClose' value='false'  onclick='autoClose(this, "+index+")'  >No</input>");
			}
    		
    		
    		autoCloseColumn.append(autoCloseInput);
    		
    		var designReleaseIdColumn = $('<td>');
    		var designReleaseIdInput = $("<input type='hidden' id='designReleaseId"+index+"' name='designReleaseList[" + index +"].designReleaseId' value='" + value.designReleaseId + "'/>");
    		designReleaseIdColumn.append(designReleaseIdInput);
    		
    		var templateNameColumn = $('<td>');
    		var templateNameInput = $("<input type='hidden' name='designReleaseList[" + index +"].templateName' value='" + value.templateName + "'>" + value.templateName +"</input>");
    		templateNameColumn.append(templateNameInput);
    		
    		var statusColumn = $('<td>');
    		var statusInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + value.status + "'>" + value.status +"</input>");
    		statusColumn.append(statusInput);
    		
    		var actionColumn = $('<td>');
    		var actionButton = $("<span title='Delete' class='glyphicon glyphicon-trash btn-md redColor cursorPointer deleteDesign' id='" + value.bomLineItemId +"_"+value.templateName +"'></span>");
    		var editButton = $("<span title='Edit' class='glyphicon glyphicon-edit btn-md blueColor cursorPointer editDesign' id='" + value.bomLineItemId +"_"+value.templateName +"'></span>");
    		if(value.designReleaseId.length == 0){
    			actionColumn.append(actionButton);
    		}else{
    			actionColumn.append(editButton);
    		}
    		var stateColumn = $('<td>');
    		var stateInput = $("<input type='hidden' name='designReleaseList[" + index +"].state' value='" + value.state + "'>"+  +"</input>");
    		stateColumn.append(stateInput);
    		var divTag = $('<div/>').attr('id', 'circle');
    		divTag.css("background-color",value.state);
    		stateColumn.append(divTag);
    		
    		var engrTdReleaseDateColumn = $('<td>');
    		//var engrTdReleaseDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + + "'>" +  +"</input>");
    		//engrTdReleaseDateColumn.append(engrTdReleaseDateInput);
    		
    		/*var engineerColumn = $('<td>');
    		//var engineerInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + + "'>" +  +"</input>");
    		//engineerColumn.append(engineerInput);
*/    		
    		var engrTechnicalDataColumn = $('<td>');
    		var engrTechnicalDataInput = $("<input type='hidden' name='designReleaseList[" + index +"].technicalData' value='" + value.technicalData+ "'>" + value.technicalData +"</input>");
    		engrTechnicalDataColumn.append(engrTechnicalDataInput);
    		
    		/*var designCoordinatorColumn = $('<td>');
    		//var designCoordinatorInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + + "'>" +  +"</input>");
    		//designCoordinatorColumn.append(designCoordinatorInput);
*/    		
    		//checkBoxColumn.append(designReleaseIdInput);
    		//row.append(checkBoxColumn);
    		
    		var engrOrgProjectColumn = $('<td>');
    		var engrOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrOrgProject' value='" + value.engrOrgProject + "'>" + value.engrOrgProject +"</input>");
    		engrOrgProjectColumn.append(engrOrgProjectInput);
    		
    		var designOrgProjectColumn = $('<td>');
    		var designOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].designOrgProject' value='" + value.designOrgProject + "'>" + value.designOrgProject +"</input>");
    		designOrgProjectColumn.append(designOrgProjectInput);
    		
    		var mainGroupColumn = $('<td>',{"style" : "text-align:left"});
    		var mainGroupInput = $("<input type='hidden' name='designReleaseList[" + index +"].mainGroup' value='" + value.mainGroup + "'>" + value.mainGroup +"</input>");
    		mainGroupColumn.append(mainGroupInput);
    		
    		row.append(bomLineItemIdColumn);
    		row.append(descriptionColumn);
    		row.append(edotColumn);
    		row.append(mainGroupColumn);
    		row.append(autoCloseColumn);
    		row.append(statusColumn);
    		row.append(stateColumn);
    		
    		//row.append(engrDurationColumn);
    		row.append(engrStartDateColumn);
    	//	row.append(backOffColumn);
    		row.append(engrRequiredDateColumn);
    		row.append(engrPromiseDateColumn);
    		row.append(engrActualDateColumn);
    		row.append(engrTdReleaseDateColumn);
    		row.append(engrDateChangeReasonColumn);
    		/*row.append(engrComponentNoColumn);*/
    		//row.append(engineerColumn);
    		row.append(engrOrgProjectColumn);
    		row.append(engrResourceColumn);
    		row.append(engrECRColumn);
    		row.append(engrTechnicalDataColumn);
    		row.append(engrCommentColumn);
    		
    		
    		//row.append(designDurationColumn);
    		row.append(designRequiredDateColumn);
    		row.append(designPromiseDateColumn);
    		row.append(designActualDateColumn);
    		row.append(designDateChangeReasonColumn);
    		/*row.append(designComponentNoColumn);*/
    		row.append(designOrgProjectColumn);
    		row.append(designResourceColumn);
    		row.append(designECNColumn);
    		row.append(designCommentColumn);
    		
    		//row.append(templateNameColumn);
    		
    		return row;
		}
		
		
		
		//$(".autoclosecheckbox").click(autoClose);
		
		
		
		$('.projectInfoDbBtn').click(function(){
			$("#project_dashboard_id").html($("#projectsDropDownDashboard").val());
			$('#projectInfoDbEdit').modal('show');
		});
		$('.projectDbRefresh').click(function(){
			$('#projectsDropDownDashboard').change();
		});
		
		$('.dreDashboardFilterClass').change(function(){
			var filterValue = $("#dreDashboardFilterData").val();
			 $("#dashboardSearchTerm").val("");
			$(".designReleaseDashboardTable tr").each(function() 
			{ 
				var status = $(this).find('td').eq(5).text();
	               if(status != "" && status != " " && status != undefined && filterValue != -1){
	            	   if(!(status.indexOf(filterValue) > -1)){
			    	   $(this).hide();
	                }else{
	                	 $(this).show();
	                }
	               }else if(filterValue == -1){
	            	   $(this).show();
	               }
	               
			});
			fixedHeaderScroll();
	    	
		});
		$('#projectsDropDownDashboard').change(function(){
			$("#projectIdEditHidden").attr('value',$(this).val());
			var projectValue = $(this).val();
			if(projectValue == '-1'){
				$("#projectDbProjectName").html('');
		    	$("#projectDbCustomerName").html('');
		    	$("#projectDbP1").html('');
		    	$("#projectDbK1").html('');
		    	$("#projectDbPrimaryNo").html('');
		    	$("#projectDbSecondaryNo").html('');
		    	$("#projectDbOrderNo").html('');
		    	$("#projectDbSalesForceId").html('');
		    	$("#engrDbProductLine").html('');
		    	$(".projectInfoDbBtn").hide();
		    	$(".projectDbRefresh").hide();
		    	$(".exportDbBtn").hide();
		    	$(".filterDashboardDataClass").hide();
		    	$(".designReleaseDashboardTable tbody").empty();
		    	for(var i=0 ; i<12 ;i++){
		    		var row = createDesignReleaseEditEmptyTableRow(i);
			    	$(".designReleaseDashboardTable tbody").append(row);
		    	}
		    	getProjectVal = projectValue;
				return;
			}else{
				$("#projectIdEditHidden").attr('value',projectValue);
				getProjectVal = projectValue;
			}
			$('#loadingModal').modal('show');
			var designReleaseListEmptyStr = $("#designReleaseEditListEmpty").val();
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getProjectData?projectId='+projectValue,
			    success: function(data){
			    	getProjectVal = projectValue;
			    	$(".projectInfoDbBtn").show();
			    	$(".projectDbRefresh").show();
			    	$(".exportDbBtn").show();
			    	var sVal = $('select[name=dreDashboardFilterData] option:first').val();
					$('select[name=dreDashboardFilterData]').val(sVal);
					$(".dreDashboardFilterClass").selectpicker('refresh');
					$(".filterDashboardDataClass").show();
					 $("#dashboardSearchTerm").val("");
			    	$.ajax({
						method: "GET",
					    url: getContextPath()+'/getAssociatedDesignItems?projectId='+projectValue,
					    success: function(associatedDesign){
					    	if(associatedDesign.length > 0){
						    	if(designReleaseListEmptyStr == 'true'){
						    		$(".designReleaseDashboardTable tbody").empty();
						    	}else{
						    		$(".designReleaseDashboardTable tbody").empty();
						    		 $("#designReleaseEditListEmpty").attr('value','false');
						    	}
						    	//console.log(associatedDesign);
						    	$.each(associatedDesign, function(index, value){
						    		var row = createDesignReleaseEditTableRow(index , value);
							    	$(".designReleaseDashboardTable tbody").append(row);
							    	resetScopeDropdown();
						    	});
					    	}else{
					    		$(".designReleaseDashboardTable tbody").empty();
						    	for(var i=0 ; i<12 ;i++){
						    		var row = createDesignReleaseEditEmptyTableRow(i);
							    	$(".designReleaseDashboardTable tbody").append(row);
						    	}
					    	}
					    	$('#loadingModal').modal('hide');
					    	$("#projectDbProjectName").html('');
					    	$("#projectDbCustomerName").html('');
					    	$("#projectDbP1").html('');
					    	$("#projectDbK1").html('');
					    	$("#projectDbPrimaryNo").html('');
					    	$("#projectDbSecondaryNo").html('');
					    	$("#projectDbOrderNo").html('');
					    	$("#projectDbSalesForceId").html('');
					    	$("#engrDbProductLine").html('');
					    	$.each(data, function(key, value){
					    		if(key == 'object_name'){
					    			$("#projectDbProjectName").html(value[0]);
					    		}else if(key == 'get6AppBuildRefDateSecond'){
					    			$("#projectDbK1").html(value[0]);
					    		}else if(key == 'get6AppBuildRefDatePrimary'){
					    			$("#projectDbP1").html(value[0]);
					    			$("#projectP1DateEditHidden").attr('value',value[0]);
					    		}else if(key == 'get6OrderNumber'){
					    			$("#projectDbOrderNo").html(value[0]);
					    		}else if(key == 'get6CustomerName'){
					    			$("#projectDbCustomerName").html(value[0]);
					    		}else if(key == 'get6PrimaryProjectNumber'){
					    			$("#projectDbPrimaryNo").html(value[0]);
					    		}else if(key == 'get6SalesForceID'){
					    			$("#projectDbSalesForceId").html(value[0]);
					    		}else if(key == 'get6SecondaryProjectNumber'){
					    			$("#projectDbSecondaryNo").html(value[0]);
					    		}else if(key == 'get6EngrProdLine'){
					    			$("#engrDbProductLine").html(value[0]);
					    		}
					    	});
					    	
					    	//Fixed header changes
					    	var table = $('#dsgnreleaseDashboard').DataTable( {
					    		
					    		"bPaginate": false,
					    		 "scrollY": 620,
					    	        "scrollX": true,
					    	        "ordering": false,
					    	        "bFilter": false,
					    	        "bInfo": false,
					    	        bRetrieve: true,
					    	     
					    	       /* fixedHeader: {
					    	            header: true
					    				 
					    	        }*/
					    			} );
					    	$('#dsgnreleaseDashboard').resize();
					    	table.fixedHeader.adjust();
					    	
					    }
			    	});
			    }
			});
		});
		
		
	   
	    
		$('.designUpdateOk').click(function(){
			$('#designUpdatedModal').modal('hide');
			$('#projectsDropDownDashboard').change();
		});
		
		$("a[href='#content-Dashboard']").on('shown.bs.tab', function (e) {
			//console.log("edit");
			  var buildProjectDropDownVal = getProjectVal;
			  $('#projectsDropDownDashboard').val(buildProjectDropDownVal).change();
			});
		
		var groupList =[];
		
		function getSubgrouponload()
		{
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getGroupList',
			    success: function(data){
			    	dao.subgrpdata = data;
			    	
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
		
		}
		
		$('.exportDbBtn').click(function(){
			window.location.href = getContextPath()+'/exportDashboardDataNew';
			/*$.ajax({
				method: "POST",
				
				url: getContextPath()+'/exportDashboardData1',
			    success: function(data){
			    	convertToExcelFile(data,"dashboard","data","xlsx");
			    	
			    },
	              error: function (error) {
	            	  $('#loadingModal').modal('hide');
				    	$('#exportUpdatedModalLabel').html('');
				    	if("Success" != error.responseText){
				    		$('#exportUpdatedModalLabel').css('color','red');
				    		$('#exportUpdatedModalLabel').html(error.responseText);
					    	$('#exportUpdatedModal').modal('show');
				    	}
	            	  convertToExcelFile(error.responseText,"dashboard","data","xlsx");
	              }
			});*/
		});
		
		function fixedHeaderScroll(){
			var table = $('#dsgnreleaseDashboard').DataTable( {
	    		
	    		"bPaginate": false,
	    		 "scrollY": 620,
	    	        "scrollX": true,
	    	        "ordering": false,
	    	        "bFilter": false,
	    	        "bInfo": false,
	    	        bRetrieve: true,
	    	     
	    	       /* fixedHeader: {
	    	            header: true
	    				 
	    	        }*/
	    			} );
	    	$('#dsgnreleaseDashboard').resize();
	    	table.fixedHeader.adjust();
		}
		$('.dashboardSearch-btn').click(function(){
			var filterValue = $("#dashboardSearchTerm").val();
			
			$("#dsgnreleaseDashboard tr").each(function(rowId, row) 
					{ 
					var isContentPresent = false;
					if($(this).css('display') != 'none'){ 
						 
					  //if(rowId > 1){
						  var bomLine = $(this).find('td').eq(1).text();
							if(bomLine != null && bomLine != " " && bomLine != "" && bomLine != undefined){
								for(var i=0;i<26;i++){
									var fieldValue = $(this).find('td').eq(i).text();
						               if(fieldValue != "" && fieldValue != " " && fieldValue != undefined){
						            	   if(fieldValue.toUpperCase().indexOf(filterValue.toUpperCase()) > -1){
						            		isContentPresent = true;
						                }else{
						                	 $(this).hide();
						                }
						               }else if(filterValue == -1){
						            	   $(this).show();
						               }
								}
							}
					 // }
					}
					if(isContentPresent || filterValue == "" || filterValue == " " || filterValue == undefined){
							$(this).show();
							
						}
						
						
					});
			fixedHeaderScroll();
			
		});
});