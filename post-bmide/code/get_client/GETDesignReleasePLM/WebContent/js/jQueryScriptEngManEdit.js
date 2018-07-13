$(document).ready(function() {	

		$('#projectsEngManDropDownEdit').selectpicker();
		$('#templatesDropDownEdit').selectpicker();
		$('#scopesDropDownEdit').selectpicker();
		$('#engMagrFilterData').selectpicker();
		window.getProjectVal = $("#projectsDropDown").val();

		function getContextPath() {
			   return window.location.pathname.substring(0, window.location.pathname.indexOf("/",2));
			}
		
		window.setInterval(function(){
			$(".designReleaseEditTableHead").width($(".designReleaseEditTable").width());
			$(".designReleaseEditTable tbody tr td").each(function (i){
			       $(this).width($($(".designReleaseEditTableHead tr:first th")[i]).width());
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
		
		$(document).on('click', '.deleteDesign', function () { // <-- changes
		     $(this).closest('tr').remove();
		     return false;
		 });
		
		function createDesignReleaseEditEmptyTableRow(index){
			$("#designReleaseEditListEmpty").attr('value','true');
			var className = "";
			if(index % 2 == 0){
				className = "backGround8FF";
			}
			var row = $('<tr>');
			row.attr('class',className);
			for(var i=0;i<16;i++){
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
    		var prdt = "";
    		if(value.engrPromiseDateLabel == "-")
			{
    			prdt = "";
			}else{
				prdt = value.engrPromiseDateLabel;
			}
    		 
    		
    		//onclick=\"edittablecheckboxes("+index+")\"
    		
    		var checkBoxColumn = $('<td>');
    		var st="";
    		if(value.status != "Engr Manager Review")
			{
    			st = "disabled";
			}
    		/*var subgrps = value.engrComponentNo;
    		subgrps = subgrps.split(".");*/
    		
    		var checkBoxInput = $("<input type='checkbox' class='editMainTableCheckboxes' name='designReleaseList[" + index +"].editChecked' id='check_"+value.bomLineItemId+"'  data-edot= '"+value.designReleaseId+"' data-index ='"+index+"'  "+st+"  />" );
    		var edotHiddenInput = $("<input type='hidden' id='edotHiddenInput"+index+"' value='"+value.designReleaseId+"'/>");
    		var promisedateHiddenInput = $("<input type='hidden' id='promiseHiddenInput"+index+"' value='"+value.engrPromiseDate+"'/>");
    		var resourceHiddenInput = $("<input type='hidden' id='resourceHiddenInput"+index+"' value='"+value.engrResource+"'/>");
    		var commentHiddenInput = $("<input type='hidden' id='commentHiddenInput"+index+"' value='"+value.engrComment+"'/>");
    		
    	//	var subgroupHiddenInput = $("<input type='hidden' id='subgrpHiddenInput"+index+"' value='"+subgrps[0]+"'/>");
    		
    		
    		checkBoxColumn.append(checkBoxInput);
    		checkBoxColumn.append(edotHiddenInput);
    		checkBoxColumn.append(promisedateHiddenInput);
    		checkBoxColumn.append(resourceHiddenInput);
    		checkBoxColumn.append(commentHiddenInput);
    	//	checkBoxColumn.append(subgroupHiddenInput);
    		
    		var bomLineItemIdColumn = $('<td>');
    		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+index+"' name='designReleaseList[" + index +"].bomLineItemId' value='" + value.bomLineItemId + "'>"+ value.bomLineItemId +"</input>");
    		bomLineItemIdColumn.append(bomLineItemIdInput);
    		
    		var descriptionColumn = $('<td>');
    		var descriptionInput = $("<input type='hidden' name='designReleaseList[" + index +"].description' value='" + value.description + "'>" + value.description +"</input>");
    		descriptionColumn.append(descriptionInput);
    		
    		var edotColumn = $('<td>');
    		var edotInput = $("<input type='hidden' class='edotHiddenId' id='edotId"+index+"' name='designReleaseList[" + index +"].edot' value='" + value.designReleaseId + "'>"+ value.designReleaseId +"</input>");
    		edotColumn.append(edotInput);
    		
    		var engrStartDateColumn = $("<td id=engrStartDateTD_"+index+">");
    		var engrStartDateInput = $("<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + value.engrStartDate + "'>" + value.engrStartDateLabel +"</input>");
    		engrStartDateColumn.append(engrStartDateInput);
    		
    		var engrRequiredDateColumn = $("<td id=engrRequiredDateTD_"+index+">");
    		var engrRequiredDateInput = $("<input type='hidden' class='engrRequiredDateInput' id=engrRequiredDate_"+index+" name='designReleaseList[" + index +"].engrRequiredDate' value='" + value.engrRequiredDate + "'>" + value.engrRequiredDateLabel +"</input>");
    		engrRequiredDateColumn.append(engrRequiredDateInput);
    		
    		var engrPromiseDateColumn = $('<td>');
    		var engrPromiseDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrPromiseDate' id=engPromiseDate_"+index+" value='" + value.engrPromiseDate + "'>" + prdt +"</input>");
    		engrPromiseDateColumn.append(engrPromiseDateInput);
    		
    		var engrActualDateColumn = $('<td>');
    		var engrActualDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrActualDate' value='" + value.engrActualDate + "'>" + value.engrActualDateLabel +"</input>");
    		engrActualDateColumn.append(engrActualDateInput);
    		
    		//Subgrp
    		/*var subgrps = value.engrComponentNo;
    		subgrps = subgrps.split(".");
    		var engrComponentNoColumn = $('<td>');
    		var engrComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrComponentNo' id=subgroup_"+index+" value='" + subgrps[0] + "'>" + subgrps[0] +"</input>");
    		engrComponentNoColumn.append(engrComponentNoInput);*/
    		
    		
    		//Resource
    		var engrResourceColumn = $('<td id=engresource_'+index+'>');
    		var engrResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrResource' value='" + value.engrResource + "'>" + value.engrResource +"</input>");
    		engrResourceColumn.append(engrResourceInput);
    		
    		var engrECRColumn = $('<td>');
    		var engrECRInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrECR' value='" + value.engrECR + "'>" + value.engrECR +"</input>");
    		engrECRColumn.append(engrECRInput);
    		
    		var engrCommentColumn = $('<td >');
    		var engrCommentInput = $("<textarea rows='2' cols='30' style='display:none' name='designReleaseList[" + index +"].engrComment' id=engComments_"+index+" >" + value.engrComment +"</textarea><span id=cmnt"+index+" class='cmntWrapper'>"+value.engrComment+"</span>");
    		engrCommentColumn.append(engrCommentInput);
    		
    		var statusColumn = $('<td>');
    		var statusInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + value.status + "'>" + value.status +"</input>");
    		statusColumn.append(statusInput);
    		
    		var stateColumn = $('<td>');
    		var stateInput = $("<input type='hidden' name='designReleaseList[" + index +"].state' value='" + value.state + "'>"+  +"</input>");
    		stateColumn.append(stateInput);
    		var divTag = $('<div/>').attr('id', 'circle');
    		divTag.css("background-color",value.state);
    		stateColumn.append(divTag);
    		
    		var designReleaseIdColumn = $('<td>');
    		var designReleaseIdInput = $("<input type='hidden' id='designReleaseId"+index+"' name='designReleaseList[" + index +"].designReleaseId' value='" + value.designReleaseId + "'/>");
    		designReleaseIdColumn.append(designReleaseIdInput);
    		
    		var engrECNColumn = $('<td>');
    		var engrECNInput = $("<input type='hidden' name='designReleaseList[" + index +"].designECN' value='" + value.designECN + "'>" + value.designECN +"</input>");
    		engrECNColumn.append(engrECNInput);
    		
    		var engrTDColumn = $('<td>');
    		var engrTDInput = $("<input type='hidden' name='designReleaseList[" + index +"].technicalData' value='" + value.technicalData + "'>" + value.technicalData +"</input>");
    		engrTDColumn.append(engrTDInput);
    		
    		var engrOrgProjectColumn = $('<td>');
    		var engrOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrOrgProject' id=engrOrgProject_"+index+" value='" + value.engrOrgProject + "'>" + value.engrOrgProject +"</input>");
    		engrOrgProjectColumn.append(engrOrgProjectInput);
    		
    		checkBoxColumn.append(designReleaseIdInput);
    		row.append(checkBoxColumn);
    		row.append(bomLineItemIdColumn);
    		row.append(descriptionColumn);
    		row.append(edotColumn);
    		row.append(engrStartDateColumn);
    		row.append(engrRequiredDateColumn);
    		row.append(engrPromiseDateColumn);
    		row.append(engrActualDateColumn);
    		/*row.append(engrComponentNoColumn);*/
    		row.append(engrOrgProjectColumn);
    		row.append(engrResourceColumn);
    		row.append(engrECRColumn);
    		row.append(engrECNColumn);
    		row.append(engrTDColumn);
    		row.append(engrCommentColumn);
    		row.append(statusColumn);
    		row.append(stateColumn);
    		
    		return row;
		}
		$('.projectInfoEngManEditBtn').click(function(){
			$("#project_edit_id").html($("#projectsEngManDropDownEdit").val());
			$('#projectInfoEdit').modal('show');
		});
		
		$('.projectRefresh').click(function(){
			$('#projectsEngManDropDownEdit').change();
		});
		
		$('.engMagrFilterClass').change(function(){
			var filterValue = $("#engMagrFilterData").val();
			$("#engMangrSearchTerm").val("");
			$(".designReleaseEditTable tr").each(function() 
			{ 
				var status = $(this).find('td').eq(14).text();
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
		
		$('#projectsEngManDropDownEdit').change(function(){
			//console.log("Edit");
			$("#projectIdEditHidden").attr('value',$(this).val());
			var projectValue = $(this).val();
			if(projectValue == '-1'){
				$("#projectEditProjectName").html('');
		    	$("#projectEditCustomerName").html('');
		    	$("#projectEditP1").html('');
		    	$("#projectEditK1").html('');
		    	$("#projectEditPrimaryNo").html('');
		    	$("#projectEditSecondaryNo").html('');
		    	$("#projectEditOrderNo").html('');
		    	$("#projectEditSalesForceId").html('');
		    	$("#engrEngMgrProductLine").html('');
		    	$(".projectInfoEditBtn").hide();
		    	$(".projectInfoEngManEditBtn").hide();
		    	$(".filterEngMagrDataClass").hide();
		    	$(".projectRefresh").hide();
		    	$(".designReleaseEditTable tbody").empty();
		    	$("#engMangrSearchTerm").val("");
		    	for(var i=0 ; i<12 ;i++){
		    		var row = createDesignReleaseEditEmptyTableRow(i);
			    	$(".designReleaseEditTable tbody").append(row);
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
			    	$(".projectInfoEngManEditBtn").show();
			    	$(".projectRefresh").show();
			    	var sVal = $('select[name=engMagrFilterData] option:first').val();
					$('select[name=engMagrFilterData]').val(sVal);
					$(".engMagrFilterClass").selectpicker('refresh');
					$(".filterEngMagrDataClass").show();
					
			    	AssociatedProjDetails(projectValue, designReleaseListEmptyStr, data);
			    }
			});
		});
		
		function AssociatedProjDetails(projectValue, designReleaseListEmptyStr, data)
		{
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getAssociatedDesignItems?projectId='+projectValue,
			    success: function(associatedDesign){
			    	if(associatedDesign.length > 0){
				    	if(designReleaseListEmptyStr == 'true'){
				    		$(".designReleaseEditTable tbody").empty();
				    	}else{
				    		$(".designReleaseEditTable tbody").empty();
				    		 $("#designReleaseEditListEmpty").attr('value','false');
				    	}
				    	//console.log(associatedDesign);
				    	$.each(associatedDesign, function(index, value){
				    		var row = createDesignReleaseEditTableRow(index , value);
					    	$("#dsgnengmanrelease tbody").append(row);
					    	resetScopeDropdown();
				    	});
			    	}else{
			    		//console.log("empty");
			    		$("#dsgnengmanrelease tbody").empty();
				    	for(var i=0 ; i<11 ;i++){
				    		var row = createDesignReleaseEditEmptyTableRow(i);
					    	$("#dsgnengmanrelease tbody").append(row);
				    	}
			    	}
			    	$('#loadingModal').modal('hide');
			    	$("#projectEditProjectName").html('');
			    	$("#projectEditCustomerName").html('');
			    	$("#projectEditP1").html('');
			    	$("#projectEditK1").html('');
			    	$("#projectEditPrimaryNo").html('');
			    	$("#projectEditSecondaryNo").html('');
			    	$("#projectEditOrderNo").html('');
			    	$("#projectEditSalesForceId").html('');
			    	$("#engrEngMgrProductLine").html('');
			    	$.each(data, function(key, value){
			    		if(key == 'object_name'){
			    			$("#projectEditProjectName").html(value[0]);
			    		}else if(key == 'get6AppBuildRefDateSecond'){
			    			$("#projectEditK1").html(value[0]);
			    		}else if(key == 'get6AppBuildRefDatePrimary'){
			    			$("#projectEditP1").html(value[0]);
			    			$("#projectP1DateEditHidden").attr('value',value[0]);
			    		}else if(key == 'get6OrderNumber'){
			    			$("#projectEditOrderNo").html(value[0]);
			    		}else if(key == 'get6CustomerName'){
			    			$("#projectEditCustomerName").html(value[0]);
			    		}else if(key == 'get6PrimaryProjectNumber'){
			    			$("#projectEditPrimaryNo").html(value[0]);
			    		}else if(key == 'get6SalesForceID'){
			    			$("#projectEditSalesForceId").html(value[0]);
			    		}else if(key == 'get6SecondaryProjectNumber'){
			    			$("#projectEditSecondaryNo").html(value[0]);
			    		}else if(key == 'get6EngrProdLine'){
			    			$("#engrEngMgrProductLine").html(value[0]);
			    		}
			    	});
			    	
			    	
			    	$('.editMainTableCheckboxes').click(function(){
			    		
			    		var row = $(this);
			    		//console.log($(this).index());
			    		editEngManDetails(row, $(this).data('index'));
			    		fixedHeaderScroll();
			    	});
			    	
			    	//Fixed header scroll.
			    	var table = $('#dsgnengmanrelease').DataTable( {
			    		
			    		"bPaginate": false,
			    		 "scrollY": 555,
			    	     "scrollX": true,
			    	     
			    	     "ordering": false,
			    	     "bFilter": false,
			    	     "bInfo": false,
			    	      bRetrieve: true,
			    	     
			    	       
			    			} );
			    	$('#dsgnengmanrelease').resize();
			    	table.fixedHeader.adjust();
			    }
	    	});
		}
		
		function editEngManDetails(clickedRow, index){
			    	
			//console.log(clickedRow);
		    	var checked = clickedRow.prop('checked');
		    	var index = index;
		    	
			    //console.log(index);
	    		if(checked){
					
					
	    			$("#engComments_"+index).show();
					
					if($("#resourceHiddenInput"+index).val() == "")
					{
						var design_resource = clickedRow.parent().parent().children("td:eq(9)").html();
						var design_resourceVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
						design_resource = design_resource.substring(0,design_resource.lastIndexOf(">")+1);
						engMansubgrp(index);
						design_resource = design_resource.replace('type="hidden"','type="text"');
					}
					$('#cmnt'+index).hide();
		
				}else{
					
					
					$("#engComments_"+index).hide();
					
					if($("#resourceHiddenInput"+index).val() == "")
					{
						var design_resource = clickedRow.parent().parent().children("td:eq(9)").html();
						var design_resourceVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
						clickedRow.parent().parent().children("td:eq(9)").html('');
						clickedRow.parent().parent().children("td:eq(9)").html($('#resourceHiddenInput'+index).val());
					}
					$('#cmnt'+index).show();
				}
			}
		
		$('#editEngMannallcheckbox').change(function () {
			console.log("engineer manager");
		    //$('tbody tr td input[type="checkbox"]:enabled').prop('checked', $(this).prop('checked'));
			 $('.editMainTableCheckboxes:enabled').prop('checked', $(this).prop('checked'));
			 
		});
		
		$('#editEngMannallcheckbox').click(function () {
			 if(this.checked){
		            $('.editMainTableCheckboxes:enabled').each(function(){
		               this.checked = true;
		               var row = $(this);
		               $('#engPromiseDate_'+$(this).data('index')).removeClass('hasDatepicker');
		               editEngManDetails(row, $(this).data('index'));
		               fixedHeaderScroll();
		            });
		        }else{
		             $('.editMainTableCheckboxes:enabled').each(function(){
		                this.checked = false;
		                var row = $(this);
		                $('#engPromiseDate_'+$(this).data('index')).removeClass('hasDatepicker');
		                editEngManDetails(row, $(this).data('index'));
		                fixedHeaderScroll();
		            });
		        }
			
		});
		
		
		$("#assignDesignReleaseEdit,#closureDesignReleaseEdit,#rejectDesignReleaseEdit").on("click", function()
		{
			//console.log($(this).data('action'));
			var edot=[], resource = [], subgrp=[], promisedt=[], comments=[], engresource=[];
			var action = $(this).data('action');
			var returnst = true;
			
			if($('.editMainTableCheckboxes:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one checkbox");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			
			$(".editMainTableCheckboxes:checked").each(function()
			{
				edot.push($(this).data('edot'));
				//subgrp.push($(this).data('subgrp'));
				subgrp.push($("#engrOrgProject_"+$(this).data('index')).val());
				promisedt.push($("#engPromiseDate_"+$(this).data('index')).val());
				comments.push($("#engComments_"+$(this).data('index')).val());
				if(typeof $("#engresource"+$(this).data('index')).val() == "undefined")
				{
					resource.push($("#resourceHiddenInput"+$(this).data('index')).val());
					//console.log($("#engresource"+$(this).data('index')).val());
				}
				else
				{
					resource.push($("#engresource"+$(this).data('index')).val());
				}
				//console.log(action);	
				if(action == "closure" || action == "reject")
	    		{
					if(($("#engComments_"+$(this).data('index')).val() == "") || ($("#engComments_"+$(this).data('index')).val() == null) || ($("#engComments_"+$(this).data('index')).val() == "null"))
					{
						//alert("Please fill the comments");
						$("#onlyDesignExistErrorLabel").html("Please fill the comments");
						$("#engComments_"+$(this).data('index')).focus();
						$("#onlyDesignIdExistError").modal('show');
						returnst =  false;
						return false;
					}
	    		}
				
				if(action == "assign")
	    		{
					if(($("#engresource"+$(this).data('index')).val() == "") || ($("#engresource"+$(this).data('index')).val() == null) || resource.length == 0)
					//if(resource.length == 0)
					{
						//alert("Please fill the Resource");
						$("#onlyDesignExistErrorLabel").html("Please fill the Resource");
						$("#engresource"+$(this).data('index')).focus();
						$("#onlyDesignIdExistError").modal('show');
						returnst =  false;
						return false;
					}
	    		}
				
				
			});
			if(!returnst)
			{
				return returnst;
			}
			
			//console.log("Exit");
			
			engresource.push($("#eng_resource").val());
			$('#loadingModal').modal('show');
			
			/*var data ={
					edot : edot,					
					subgrp : subgrp,
					resource : engresource,
					action : $(this).data('action')
			};
			
			var up_data ={
					edot : edot,					
					subgrp : subgrp,
					resource : resource,
					promisedt : promisedt,
					comments : comments,
					action : $(this).data('action')
			};*/
			var data ={
					edot : edot,					
					subgrp : subgrp,
					resource : engresource,
					action : $(this).data('action')
			};
			
			var up_data ={
					edot : edot,					
					resource : resource,
					promisedt : promisedt,
					comments : comments,
					action : $(this).data('action')
			};
			
			
			
			//console.log($(this).data('action'));
			if($.trim($(this).data('action')) == "assign" || $.trim($(this).data('action')) == "closure" || $.trim($(this).data('action')) == "reject")
			{
				//alert("calling");
				//console.log($(this).data('action'));
				$.ajax({
					method: "POST",
				    url: getContextPath()+'/updateDesign',
				    data : up_data,
				    success: function(data){
				    },
				    error : function(error)
				    {
				    	//console.log(error);
				    	//console.log(error);
				    	/*if(error.status == 200)
			    		{
				    		updateActions(data, action);
			    		}*/
				    	//Server error changes
				    	
				    	var res = "";
				    	$('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if(error.responseText == 'Success')
			    		{
				    		updateActions(data, action);
				    		
			    		}
				    	else if("not updated" == error.responseText)
			    		{
				    		if(action == 'assign')
				    		{
				    		 res = "Reassigned Failed";
				    		}
				    		if(action == 'closure')
				    		{
				    		 res = "Closure Request Failed";
				    		}
				    		if(action == 'reject')
				    		{
				    		 res = "Reject Failed";
				    		}
				    		$('#designUpdateLabel').css('color','red');
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');	
			    		}else{
			    			res = error.responseText;
			    			$('#designUpdateLabel').css('color','red');
			    			$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');	
			    		}
				    
				    	//End
				    	
				    }
				});
			}
			else
			{
				updateActions(data, action);
			}
			
			
			
		});
		
		function updateActions(data, action)
		{
			var action = action;
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/updateActions',
			    data : data,
			    success: function(data){
			    	
			    },
			    error : function(error)
			    {
			    	//console.log(error);
			    	var res = "";
			    	$('#loadingModal').modal('hide');
			    	$('#designUpdateLabel').html('');
			    	if(error.responseText == 'Success')
		    		{
			    		//res = action
			    		if(action == 'assign')
			    		{
			    		 res = "Engineer Assigned Successfully";
			    		}
			    		if(action == 'closure')
			    		{
			    		 res = "Closure Request Submitted Successfully";
			    		}
			    		if(action == 'reject')
			    		{
			    		 res = "Rejected Successfully";
			    		}
			    		$('#designUpdateLabel').css('color','green');
		    		}
			    	else
		    		{
			    		if(action == 'assign')
			    		{
			    		 res = "Reassigned Request Failed";
			    		}
			    		if(action == 'closure')
			    		{
			    		 res = "Closure Request Failed";
			    		}
			    		if(action == 'reject')
			    		{
			    		 res = "Rejection Failed";
			    		}
			    		$('#designUpdateLabel').css('color','red');
		    		}
			    	
			    	$('#designUpdateLabel').html(res);
			    	$('#designUpdatedModal').modal('show');	
			   
			    }
			});
		}
		
		$('.designUpdateOk').click(function(){
			$('#designUpdatedModal').modal('hide');
			$('#projectsEngManDropDownEdit').change();
		});
		
		function engMansubgrp(index){
			$('#loadingModal').modal('show');
			//var grpid = $("#subgroup_"+index).val();
			/*var grpid = $("#subgrpHiddenInput"+index).val();
			
			grpid = grpid.split("(");
			grpid = $.trim(grpid[0]);*/
			var grpid = $("#engrOrgProject_"+index).val();
			
			//console.log(index);		
			var resourceList = [];
			
			
			
			$("#engresource"+index+" option").remove();
			$select = $("<select class='resources' name='designReleaseList[" + index +"].engResource' id=\"engresource"+index+"\">" );
			$select.append("<option></option>");
			
			var theWidth = $("#dsgnengmanrelease").eq(0).find("tr > td#engresource_0").width();
			if(theWidth >0){
				$select.css("width",theWidth + "px");
			}else{
				theWidth = $("#dsgnengmanrelease").eq(0).find("tr > td#engresource_"+index).width();
				$select.css("width",theWidth + "px");
			}
			
			
			$.ajax({
				method: "GET",
		       // async: false,
			    url: getContextPath()+'/getEngrResourceList?grpid='+grpid+'&engrole=Engineer',
			    success: function(data){
			    	resourceList = data;
					for(var item in resourceList){
						$select.append("<option>" + resourceList[item] + "</option>");
						
					}
					//console.log($select);
					$("#engresource_"+index).html('');
					$("#engresource_"+index).append($select);
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
			
			
		}
		function fixedHeaderScroll(){
			//Fixed header scroll.
			
			var table = $('#dsgnengmanrelease').DataTable( {
				/*destroy: true,*/
	    		"bPaginate": false,
	    		 "scrollY": 585,
	    	     "scrollX": true,
	    	     "ordering": false,
	    	     "bFilter": false,
	    	     "bInfo": false,
	    	     bRetrieve: true,
	    	       /* fixedHeader: {
	    	            header: true
	    				 
	    	        }*/
	    			} );
	    	$('#dsgnengmanrelease').resize();
	    	table.fixedHeader.adjust();
	    	//$(table).dataTable().fnAdjustColumnSizing();
		}
		
		$('.engMgrsearch-btn').click(function(){
			var filterValue = $("#engMangrSearchTerm").val();
			
			$("#dsgnengmanrelease tr").each(function(rowId, row) 
					{ 
					var isContentPresent = false;
					if($(this).css('display') != 'none'){ 
						 
					  
						  var bomLine = $(this).find('td').eq(1).text();
							if(bomLine != null && bomLine != " " && bomLine != "" && bomLine != undefined){
								for(var i=1;i<16;i++){
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
					
					}
						if(isContentPresent || filterValue == "" || filterValue == " " || filterValue == undefined){
							$(this).show();
						}
						
						
					});
			fixedHeaderScroll();
			
		});
		
});

