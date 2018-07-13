$(document).ready(function() {	

		$('#projectsDropDownPublish').selectpicker();
		$('#publishallcheckbox').change(function () {
			//console.log("calling");
		    $('.editpublishTableCheckboxes:enabled').prop('checked', $(this).prop('checked'));
		});
		window.getProjectVal = $("#projectsDropDown").val();
		$('.drePublishFilterClass').selectpicker();
		function getContextPath() {
			   return window.location.pathname.substring(0, window.location.pathname.indexOf("/",2));
			}
		
		window.setInterval(function(){
			$(".designReleasePublishTableHead").width($(".designReleasePublishTable").width());
			$(".designReleasePublishTable tbody tr td").each(function (i){
			       $(this).width($($(".designReleasePublishTableHead tr:first th")[i]).width());
			});
		}, 100);
		
		
		$(document).on('click', '.deleteDesign', function () { // <-- changes
		     $(this).closest('tr').remove();
		     return false;
		 });
		
		function createDesignReleasePublishEmptyTableRow(index){
			$("#designReleasePublishListEmpty").attr('value','true');
			var className = "";
			if(index % 2 == 0){
				className = "backGround8FF";
			}
			var row = $('<tr>');
			row.attr('class',className);
			for(var i=0;i<14;i++){
				row.append($('<td>').append('&nbsp;'));
			}
			return row;
		}
		
		function createDesignReleasePublishTableRow(index , value){
			$("#designReleasePublishListEmpty").attr('value','false');
			var className = "";
			var textAlignClassName = "textAlignClass";
			if(index % 2 == 0){
				className = "backGround8FF";
			}
			var row = $("<tr>",{"white-space": "nowrap"});
    		row.attr('class',className);
    		
    		var st="";
    		if(value.status != "In Edit" && (!value.status.includes("EDOT Close")) && (!value.status.includes("Reassign") && value.status != "TD Released" /*(!value.status.includes("Reassign Sub Group")*/))
			{
    			st = "disabled";
			}
    		var checkBoxColumn = $('<td>');
    		var checkBoxInput = $("<input type='checkbox' class='editpublishTableCheckboxes' name='designReleaseList[" + index +"].editChecked' id='check_"+value.bomLineItemId+"' data-bomln= '"+value.bomLineItemId+"' data-edot='"+value.designReleaseId+"' data-subgrp='"+value.engrOrgProject+"'  data-resource='"+value.engrResource+"'  data-engrOrgProject='"+value.engrOrgProject+"'  data-status='"+value.status+"'  "+st+" data-index ='"+index+"'   />");
    		checkBoxColumn.append(checkBoxInput);
    		
    		
    		var bomLineItemIdColumn = $('<td>');
    		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+index+"' name='designReleaseList[" + index +"].bomLineItemId' value='" + value.bomLineItemId + "'>"+ value.bomLineItemId +"</input>");
    		bomLineItemIdColumn.append(bomLineItemIdInput);
    		
    		var descriptionColumn = $('<td>');
    		var descriptionInput = $("<input type='hidden'  name='designReleaseList[" + index +"].description' value='" + value.description + "'>" + value.description +"</input>");
    		descriptionColumn.append(descriptionInput);
    		descriptionColumn.attr('class',textAlignClassName);
    		
    		var statusColumn = $('<td>');
    		var statusInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' id='statusinpt"+index+"' value='" + value.status + "'>" + value.status +"</input>");
    		statusColumn.append(statusInput);
    		
    		var engrStartDateColumn = $('<td>');
    		var engrStartDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrStartDate' value='" + value.engrStartDate + "'>" + value.engrStartDateLabel +"</input>");
    		engrStartDateColumn.append(engrStartDateInput);
    		
    		var engrRequiredDateColumn = $('<td>');
    		var engrRequiredDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrRequiredDate' value='" + value.engrRequiredDate + "'>" + value.engrRequiredDateLabel +"</input>");
    		engrRequiredDateColumn.append(engrRequiredDateInput);
    		
    		var designRequiredDateColumn = $('<td>');
    		var designRequiredDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].designRequiredDate' value='" + value.designRequiredDate + "'>" + value.designRequiredDateLabel +"</input>");
    		designRequiredDateColumn.append(designRequiredDateInput);
    		
    		var engrComponentNoColumn = $('<td>');
    		var engrComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrComponentNo' value='" + value.engrComponentNo + "'>" + value.engrComponentNo +"</input>");
    		engrComponentNoColumn.append(engrComponentNoInput);
    		engrComponentNoColumn.attr('class',textAlignClassName);
    		
    		var designComponentNoColumn = $('<td>');
    		var designComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].designComponentNo' value='" + value.designComponentNo + "'>" + value.designComponentNo +"</input>");
    		designComponentNoColumn.append(designComponentNoInput);
    		designComponentNoColumn.attr('class',textAlignClassName);
    		
    		var designReleaseIdColumn = $('<td>');
    		var designReleaseIdInput = $("<input type='hidden' id='designReleaseId"+index+"' name='designReleaseList[" + index +"].designReleaseId' value='" + value.designReleaseId + "'>" + value.designReleaseId +"</input>");
    		designReleaseIdColumn.append(designReleaseIdInput);
    		
    		/*var templateNameColumn = $('<td>');
    		var templateNameInput = $("<input type='hidden' name='designReleaseList[" + index +"].templateName' value='" + value.templateName + "'>" + value.templateName +"</input>");
    		templateNameColumn.append(templateNameInput);*/
    		
    		/*var engrResourceColumn = $('<td>');
    		var engrResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrResource' id='engresource_"+index+" value='" + value.engrResource + "'>" + value.engrResource +"</input>");
    		engrResourceColumn.append(engrResourceInput);*/
    		
    		/*var engrResourceColumn = $('<td id=engresource_'+index+'>');
    		var engrResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrResource' value='" + value.engrResource + "'>" + value.engrResource +"</input>");
    		//var engresourcediv = $("<div id='engresource[" + index +"]'>");
    		engrResourceColumn.append(engrResourceInput);*/
    		
    		var engrResourceColumn = $('<td id=engPubresource_'+index+'>');
    		var engrResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrResource' value='" + value.engrResource + "'>" + value.engrResource +"</input>");
    		//var engresourcediv = $("<div id='engresource[" + index +"]'>");
    		engrResourceColumn.append(engrResourceInput);
    		
    		var designResourceColumn = $('<td>');
    		var designResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].designResource' value='" + value.designResource + "'>" + value.designResource +"</input>");
    		designResourceColumn.append(designResourceInput);
    		
    		var engrCommentColumn = $('<td>');
    		var engrCommentInput = $("<textarea rows='2' cols='30' style='display:none' name='designReleaseList[" + index +"].engrComment' id=engPublishComments_"+index+">" + value.engrComment +"</textarea><span id=engrPublishcmnt"+index+" class='cmntWrapper'>"+value.engrComment+"</span>");
    		engrCommentColumn.append(engrCommentInput);
    		
    		
    		var eng_subgroupHiddenInput = $("<input type='hidden' id='eng_subgroupHiddenInput"+index+"' value='"+value.engrComponentNo+"'/>");
    		var mainGroupHiddenInput = $("<input type='hidden' id='mainGroupHiddenInput"+index+"' value='"+value.mainGroup+"'/>");
    		var eng_orgProjectHiddenInput = $("<input type='hidden' id='eng_orgProjectHiddenInput"+index+"' value='"+value.engrOrgProject+"'/>");
			//console.log("Eng Subgroup Value"+ eng_subgroupHiddenInput);
			var eng_resourceHiddenInput = $("<input type='hidden' id='eng_resourceHiddenInput"+index+"' value='"+value.engrResource+"'/>");
			
			var engrOrgProjectColumn = $('<td id=engrOrgProject_'+index+'>');
    		var engrOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrOrgProject' value='" + value.engrOrgProject + "'>" + value.engrOrgProject +"</input>");
    		engrOrgProjectColumn.append(engrOrgProjectInput);
    		
    		var designOrgProjectColumn = $('<td id=designOrgProject_'+index+'>');
    		var designOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].designOrgProject' value='" + value.designOrgProject + "'>" + value.designOrgProject +"</input>");
    		designOrgProjectColumn.append(designOrgProjectInput);
    		
    		var mainGroupColumn = $('<td id=mainGrp_'+index+'>',{"style" : "text-align:left"});
    		var mainGroupInput = $("<input type='hidden' name='designReleaseList[" + index +"].mainGroup' value='" + value.mainGroup + "'>" + value.mainGroup +"</input>");
    		mainGroupColumn.append(mainGroupInput);
			
			checkBoxColumn.append(eng_subgroupHiddenInput);
    		checkBoxColumn.append(eng_resourceHiddenInput);
    		checkBoxColumn.append(mainGroupHiddenInput);
    		checkBoxColumn.append(eng_orgProjectHiddenInput);
    		
    		row.append(checkBoxColumn);
    		row.append(bomLineItemIdColumn);
    		row.append(descriptionColumn);
    		row.append(designReleaseIdColumn);
    		row.append(mainGroupColumn);
    		
    		row.append(engrStartDateColumn);
    		row.append(engrRequiredDateColumn);
    		row.append(designRequiredDateColumn);
    		/*row.append(engrComponentNoColumn);*/
    		row.append(engrOrgProjectColumn);
    		row.append(engrResourceColumn);
    		row.append(engrCommentColumn);
    		/*row.append(designComponentNoColumn);*/
    		row.append(designOrgProjectColumn);
    		row.append(designResourceColumn);
    		/*row.append(templateNameColumn);*/
    		row.append(statusColumn);
    		return row;
		}
		
		$('.projectInfoPublishBtn').click(function(){
			$("#project_publish_id").html($("#projectsDropDownPublish").val());
			$('#projectInfoPublish').modal('show');
		});
		
		$('.projectRefresh').click(function(){
			$('#projectsDropDownPublish').change();
		});
		
		
		
		$("#publishDesignReleasePublish").on("click", function()
		{
			var subgrp = [];
			var edot = [];
			var returnst = true;
			
			//if($('input[name="designReleaseList"]:checked').length == 0)
			if($('.editpublishTableCheckboxes:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one checkbox");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			
			$('.editpublishTableCheckboxes:checked').each(function() {
				   subgrp.push($(this).data("subgrp"));
				   edot.push($(this).data("edot"));
				   
				   if(!$(this).data("status").includes( "In Edit"))
				   {
					   //alert("EDOT can be published if the status is In Edit");
					   $('#onlyDesignExistErrorLabel').html("EDOT can not be published if the status is not In Edit");
				       $('#onlyDesignIdExistError').modal('show');
					   returnst =  false;
					   return false;
				   }
			});
			
			if(!returnst)
			{
				return returnst;
			}
			
			$('#loadingModal').modal('show');
			$.ajax({
				method: "POST",
				data :{
			    	"subgrp" : subgrp,
			    	"edot" : edot
			    },
			    url: getContextPath()+'/publishworkflow',
			    success: function(data){
			    	$('#loadingModal').modal('hide');
			    	$('#designUpdateLabel').html('');
			    	if("Success" == data){
			    		$('#designUpdateLabel').css('color','green');
			    		$('#designUpdateLabel').html("EDOTs Published Successfully");
			    	}else{
			    		$('#designUpdateLabel').css('color','red');
			    		$('#designUpdateLabel').html("EDOTs Publish Failed");
			    	}
			    	
			    	$('#designUpdatedModal').modal('show');
			    },
	              error: function (error) {
	            	  //console.log("error"+error);
	            	  $('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Success" == error.responseText){
				    		$('#designUpdateLabel').css('color','green');
				    		$('#designUpdateLabel').html("EDOTs Published Successfully");
				    	}else{
				    		$('#designUpdateLabel').css('color','red');
				    		$('#designUpdateLabel').html("EDOTs Publish Failed");
				    	}
				    	
				    	$('#designUpdatedModal').modal('show');
	              }
			});
			
			
			
		});
		
		
		$("#rejectDesignReleasePublish").on("click", function()
		{
			var subgrp = [];
			var edot = [];
			var engresource = [];
			var engrComments = [];
			var returnst = true;
			
			if($('.editpublishTableCheckboxes:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one EDOT");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			
		   
			
			//$('input[class="editpublishTableCheckboxes"]:checked').each(function() {
			$('.editpublishTableCheckboxes:checked').each(function() {
				   subgrp.push($(this).data("subgrp"));
				   edot.push($(this).data("edot"));
				   engresource.push($(this).data("resource"));
				   engrComments.push($("#engPublishComments_"+$(this).data('index')).val());
				   if(!$(this).data("status").includes( "EDOT Close"))
				   {
					   $('#onlyDesignExistErrorLabel').html("EDOT can be rejected only if the status is EDOT Close");
				       $('#onlyDesignIdExistError').modal('show');
					   returnst =  false;
					   return false;
				   }
			});
			
			if(!returnst)
			{
				return returnst;
			}
			
			
			$('#loadingModal').modal('show');
			var action ="dre_reject";
			var data  ={
		    	"subgrp" : subgrp,
		    	"edot" : edot,
		    	"resource" : engresource,
		    	"comments" : engrComments,
				"action" : action
		    };
								
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/publishReassign',
			    data : data,
			    success: function(data){
			    },
			    error : function(error)
			    {
			    	console.log(error);
			    	if(error.status == 200)
		    		{
			    		updateActions(data, action);
		    		}
			    }
			});
		});
		
		$("#closeDesignReleasePublish").on("click", function()
		{
					var subgrp = [];
					var edot = [];
					var engresource = [];
					var engrComments = [];
					var returnst = true;
					
					if($('.editpublishTableCheckboxes:checked').length == 0)
					{
						 $("#onlyDesignExistErrorLabel").html("Please select atleast one EDOT");
						 $("#onlyDesignIdExistError").modal('show');
						 returnst =  false;
						 return false;
					}
					
					//$('input[class="editpublishTableCheckboxes"]:checked').each(function() {
					$('.editpublishTableCheckboxes:checked').each(function() {
						   subgrp.push($(this).data("subgrp"));
						   edot.push($(this).data("edot"));
						  engresource.push($(this).data("resource"));
						  engrComments.push($("#engPublishComments_"+$(this).data('index')).val());
						   if(!$(this).data("status").includes( "EDOT Close") && !$(this).data("status").includes( "TD Released"))
						   {
							   $('#onlyDesignExistErrorLabel').html("EDOT can be closed only if the status is EDOT Close OR TD Released");
						       $('#onlyDesignIdExistError').modal('show');
							   returnst =  false;
							   return false;
						   }
					});
					
					if(!returnst)
					{
						return returnst;
					}
					
					$('#loadingModal').modal('show');
					var action ="dre_closure";
					var data ={
				    	"subgrp" : subgrp,
				    	"edot" : edot,
				    	"resource" : engresource,
				    	"comments" : engrComments,
						"action" : action
				    };
									
					$.ajax({
						method: "POST",
					    url: getContextPath()+'/publishReassign',
					    data : data,
					    success: function(data){
					    },
					    error : function(error)
					    {
					    	//console.log(error);
					    	if(error.status == 200)
				    		{
					    		updateActions(data, action);
				    		}
					    }
					});
		});
		
		$("#reassignDesignReleasePublish").on("click", function()
		{
							var subgrp = [];
							var edot = [];
							var engresource = [];
							var engrComments = [];
							var returnst = true;
							
							if($('.editpublishTableCheckboxes:checked').length == 0)
							{
								 $("#onlyDesignExistErrorLabel").html("Please select atleast one EDOT");
								 $("#onlyDesignIdExistError").modal('show');
								 returnst =  false;
								 return false;
							}
							
							//$('input[class="editpublishTableCheckboxes"]:checked').each(function() {
							$('.editpublishTableCheckboxes:checked').each(function() {
								   edot.push($(this).data('edot'));
								  // engresource.push($(this).data("resource"));
								   engresource.push($("#engresource"+$(this).data('index')).val());
								   subgrp.push($("#engrOrgProject"+$(this).data('index')).val());
								   //subgrp.push($(this).data("subgrp"));
								   engrComments.push($("#engPublishComments_"+$(this).data('index')).val());
								   
								 //  if(!$(this).data("status").includes( "Reassign Sub Group"))
								   if(!$(this).data("status").includes( "Reassign"))
								   {
									   $('#onlyDesignExistErrorLabel').html("EDOT can be Reassigned only if the status is Reassign Sub Group");
								       $('#onlyDesignIdExistError').modal('show');
									   returnst =  false;
									   return false;
								   }
							});
							
							if(!returnst)
							{
								return returnst;
							}
							
							
							var action ="dreReassign";
							var data ={
									edot : edot,					
									subgrp : subgrp,
									resource : engresource,
									comments : engrComments,
									action : action
							};
							$('#loadingModal').modal('show');
							
							
							$.ajax({
								method: "POST",
								data : data,
							    url: getContextPath()+'/publishReassign',
							    success: function(data){
							    },
							    error : function(error)
							    {
							    	//console.log(error);
							    	if(error.status == 200)
						    		{
							    		updateActions(data, action);
						    		}
							    	
							    }
							});
							
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
					    		if(action == 'dreReassign')
				    			{
					    			res = "Updated Successfully";
				    			}
					    		if(action == 'dre_reject')
				    			{
					    			res = "Rejected Successfully";
				    			}
					    		if(action == 'dre_closure')
				    			{
					    			res = "Closed Successfully";
				    			}
					    		
					    		$('#designUpdateLabel').css('color','green');
				    		}
					    	else
				    		{
					    		if(action == 'dreReassign')
				    			{
					    			res = "Reassigned Failed";
				    			}
					    		if(action == 'dre_reject')
				    			{
					    			res = "Reject Failed";
				    			}
					    		if(action == 'dre_closure')
				    			{
					    			res = "Closure Request Failed";
				    			}
					    		//res = "Not Updated Successfully";
					    		$('#designUpdateLabel').css('color','red');
				    		}
					    	
					    	$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');	
					   
					    }
					});
				}
		
		/*function updateActions(data, action)
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
			    		if(action == 'accept')
			    		{
			    		 res = "Accepted Successfully";
			    		}
			    		if(action == 'eng_reject')
			    		{
			    		 res = "Rejected Successfully";
			    		}
			    		if(action == 'closure')
			    		{
			    		 res = "Closed Successfully";
			    		}
			    		$('#designUpdateLabel').css('color','green');
		    		}
			    	else
		    		{
			    		if(action == 'accept')
			    		{
			    		 res = "Accept Failed";
			    		}
			    		if(action == 'eng_reject')
			    		{
			    		 res = "Not Rejected";
			    		}
			    		if(action == 'closure')
			    		{
			    		 res = "Closure Request Failed";
			    		}
			    		$('#designUpdateLabel').css('color','red');
		    		}
			    	
			    	$('#designUpdateLabel').html(res);
			    	$('#designUpdatedModal').modal('show');
			    }
			});
		}*/
		
		
		$('.designUpdateOk').click(function(){
			$('#designUpdatedModal').modal('hide');
			$('#projectsDropDownPublish').change();
		});
		
		$("a[href='#content-Publish']").on('shown.bs.tab', function (e) {
			//console.log("Publish");
			  var buildProjectDropDownVal = getProjectVal;
			  $('#projectsDropDownPublish').val(buildProjectDropDownVal).change();
			});
		
		$('.drePublishFilterClass').change(function(){
			var filterValue = $("#drePublishFilterData").val();
			$("#publishSearchTerm").val("");
			$(".designReleasePublishTable tr").each(function() 
			{ 
				var status = $(this).find('td').eq(13).text();
	               if(status != "" && status != " " && status != undefined && filterValue != -1){
	            	   if(status.indexOf(filterValue) > -1){
	            		   $(this).show();
		                }else{
		                	$(this).hide();
		                }
	               }else if(filterValue == -1){
	            	   $(this).show();
	               }
	               
			});
			fixedHeaderScroll();
		});
		
		$('#projectsDropDownPublish').change(function(){
			//var projectId = sessionStorage.getItem("projectId");
			$("#projectIdPublishHidden").attr('value',$(this).val());
			
			var projectValue = $(this).val();
			//var projectValue = projectId;
			
			
			if(projectValue == '-1'){
				$("#projectPublishProjectName").html('');
		    	$("#projectPublishCustomerName").html('');
		    	$("#projectPublishP1").html('');
		    	$("#projectPublishK1").html('');
		    	$("#projectPublishPrimaryNo").html('');
		    	$("#projectPublishSecondaryNo").html('');
		    	$("#projectPublishOrderNo").html('');
		    	$("#projectPublishSalesForceId").html('');
		    	$("#engrPubProductLine").html('');
		    	$(".projectInfoPublishBtn").hide();
		    	$(".projectRefresh").hide();
		    	$(".filterDataClass").hide();
		    	$(".designReleasePublishTable tbody").empty();
		    	for(var i=0 ; i<12 ;i++){
		    		var row = createDesignReleasePublishEmptyTableRow(i);
			    	$(".designReleasePublishTable tbody").append(row);
		    	}
		    	getProjectVal = projectValue;
				return;
			}else{
				$("#projectIdPublishHidden").attr('value',projectValue);
				getProjectVal = projectValue;
			}
			$('#loadingModal').modal('show');
			var designReleaseListEmptyStr = $("#designReleasePublishListEmpty").val();
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getProjectData?projectId='+projectValue,
			    success: function(data){
			    	getProjectVal = projectValue;
			    	$(".projectInfoPublishBtn").show();
			    	$(".projectRefresh").show();
			    	var sVal = $('select[name=drePublishFilterData] option:first').val();
					$('select[name=drePublishFilterData]').val(sVal);
					$(".drePublishFilterClass").selectpicker('refresh');
					$(".filterDataClass").show();
					$("#publishSearchTerm").val("");
			    	$.ajax({
						method: "GET",
					    url: getContextPath()+'/getAssociatedDesignItems?projectId='+projectValue,
					    success: function(associatedDesign){
					    	if(associatedDesign.length > 0){
						    	if(designReleaseListEmptyStr == 'true'){
						    		$(".designReleasePublishTable tbody").empty();
						    	}else{
						    		$(".designReleasePublishTable tbody").empty();
						    		 $("#designReleasePublishListEmpty").attr('value','false');
						    	}
						    	$.each(associatedDesign, function(index, value){
						    		var row = createDesignReleasePublishTableRow(index , value);
							    	$(".designReleasePublishTable tbody").append(row);
						    	});
					    	}else{
					    		$(".designReleasePublishTable tbody").empty();
						    	for(var i=0 ; i<12 ;i++){
						    		var row = createDesignReleasePublishEmptyTableRow(i);
							    	$(".designReleaseEditTable tbody").append(row);
						    	}
					    	}
					    	$('#loadingModal').modal('hide');
					    	$("#projectPublishProjectName").html('');
					    	$("#projectPublishCustomerName").html('');
					    	$("#projectPublishP1").html('');
					    	$("#projectPublishK1").html('');
					    	$("#projectPublishPrimaryNo").html('');
					    	$("#projectPublishSecondaryNo").html('');
					    	$("#projectPublishOrderNo").html('');
					    	$("#projectPublishSalesForceId").html('');
					    	$("#engrPubProductLine").html('');
					    	$.each(data, function(key, value){
					    		if(key == 'object_name'){
					    			$("#projectPublishProjectName").html(value[0]);
					    		}else if(key == 'get6AppBuildRefDateSecond'){
					    			$("#projectPublishK1").html(value[0]);
					    		}else if(key == 'get6AppBuildRefDatePrimary'){
					    			$("#projectPublishP1").html(value[0]);
					    		}else if(key == 'get6OrderNumber'){
					    			$("#projectPublishOrderNo").html(value[0]);
					    		}else if(key == 'get6CustomerName'){
					    			$("#projectPublishCustomerName").html(value[0]);
					    		}else if(key == 'get6PrimaryProjectNumber'){
					    			$("#projectPublishPrimaryNo").html(value[0]);
					    		}else if(key == 'get6SalesForceID'){
					    			$("#projectPublishSalesForceId").html(value[0]);
					    		}else if(key == 'get6SecondaryProjectNumber'){
					    			$("#projectPublishSecondaryNo").html(value[0]);
					    		}else if(key == 'get6EngrProdLine'){
					    			$("#engrPubProductLine").html(value[0]);
					    		}
					    	});
					    	$('.editpublishTableCheckboxes').click(function(){
					    		var row = $(this);
					    		editPublishDetails(row,$(this).data('index'));
					    		fixedHeaderScroll();
					    	});
					    	//Fixed header scroll.
					    	var table = $('#designReleasePublish').DataTable( {
					    		
					    		"bPaginate": false,
					    		 "scrollY": 600,
					    	     "scrollX": true,
					    	     "ordering": false,
					    	     "bFilter": false,
					    	     "bInfo": false,
					    	      bRetrieve: true,
					    	     
					    	       /* fixedHeader: {
					    	            header: true
					    				 
					    	        }*/
					    			} );
					    	$('#designReleasePublish').resize();
					    	table.fixedHeader.adjust();
					    }
			    	});
			    }
			});
		});
		
		
		function editPublishDetails(clickedRow,index){
	    	
		    var checked = clickedRow.prop('checked');
	    	var index = index;
	    	var status = $("#statusinpt"+index).val();
	    	//console.log(status);
		if(checked){
			//if($.trim(status) == 'Reassign Sub Group')
			if($.trim(status) == 'Reassign')
			{
				//console.log(status+" Entering");
				/*var eng_subgroup = clickedRow.parent().parent().children("td:eq(7)").html();*/
				var maingroup = clickedRow.parent().parent().children("td:eq(4)").html();
				var eng_orgProject = clickedRow.parent().parent().children("td:eq(8)").html();
				var eng_resource = clickedRow.parent().parent().children("td:eq(9)").html();
				
				/*var eng_subgroupVal = clickedRow.parent().parent().children("td:eq(7)").children().val();*/
				var mainGroupVal = clickedRow.parent().parent().children("td:eq(4)").children().val();
				var eng_orgProjectVal = clickedRow.parent().parent().children("td:eq(8)").children().val();
				var eng_resourceVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
				
				/*eng_subgroup = eng_subgroup.substring(0,eng_subgroup.lastIndexOf(">")+1);*/
				maingroup = maingroup.substring(0,maingroup.lastIndexOf(">")+1);
				eng_orgProject = eng_orgProject.substring(0,eng_orgProject.lastIndexOf(">")+1);
				/*eng_resource = eng_resource.substring(0,eng_subgroup.lastIndexOf(">")+1);*/
				eng_resource = eng_resource.substring(0,eng_resource.lastIndexOf(">")+1);
				
				/*eng_subgroup = eng_subgroup.replace('type="hidden"','type="text"');*/
				maingroup = maingroup.replace('type="hidden"','type="text"');
				eng_orgProject = eng_orgProject.replace('type="hidden"','type="text"');
				eng_resource = eng_resource.replace('type="hidden"','type="text"');
				 
				
				/*clickedRow.parent().parent().children("td:eq(7)").html('');*/
				clickedRow.parent().parent().children("td:eq(4)").html('');
				clickedRow.parent().parent().children("td:eq(8)").html('');
				clickedRow.parent().parent().children("td:eq(9)").html('');
					
				//getSubgroup(index, clickedRow);
				getMainGroup(index, clickedRow);
				/*clickedRow.parent().parent().children("td:eq(7)").append(dao.engSubgrp);*/
				clickedRow.parent().parent().children("td:eq(4)").append(dao.mainGrp);
				clickedRow.parent().parent().children("td:eq(8)").append();
				clickedRow.parent().parent().children("td:eq(9)").append();
					
				/*clickedRow.parent().parent().children("td:eq(7)").children().attr('value',201).css('width','220px');*/
				clickedRow.parent().parent().children("td:eq(4)").children().attr('value',201)/*.css('width','220px')*/;
				clickedRow.parent().parent().children("td:eq(8)").children().attr('value',201)/*.css('width','220px')*/;
				clickedRow.parent().parent().children("td:eq(9)").children().attr('value',201)/*.css('width','100px')*/;
					
				if($("#mainGroupHiddenInput"+index).val() != "")
				{
						$("#maingrp"+index).val($("#mainGroupHiddenInput"+index).val());
						//engsubgrpchange(index, clickedRow);
						mainGrpChange(index, clickedRow)
				}
				$("#engPublishComments_"+index).show();
				$('#engrPublishcmnt'+index).hide();
			}
			else if(status.includes('EDOT Close') || status.includes('TD Released'))
			{
				$("#engPublishComments_"+index).show();
				$('#engrPublishcmnt'+index).hide();
				
			}
			
			
		}else{
			//if($.trim(status) == 'Reassign Sub Group')
			if($.trim(status) == 'Reassign')
			{
				/*var eng_subgroup = clickedRow.parent().parent().children("td:eq(7)").html();*/
				var mainGroup = clickedRow.parent().parent().children("td:eq(4)").html();
				var eng_orgProject = clickedRow.parent().parent().children("td:eq(8)").html();
				var eng_resource = clickedRow.parent().parent().children("td:eq(9)").html();
				
				/*var eng_subgroupVal = clickedRow.parent().parent().children("td:eq(7)").children().val();*/
				var mainGroupVal = clickedRow.parent().parent().children("td:eq(4)").children().val();
				var eng_orgProjectVal = clickedRow.parent().parent().children("td:eq(8)").children().val();
				var eng_resourceVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
				
				/*eng_subgroup = '<input type="hidden" name="designReleaseList['+index+'].engrComponentNo" value="">'+$('#eng_subgroupHiddenInput'+index).val()+"</input>";*/
				mainGroup = '<input type="hidden" name="designReleaseList['+index+'].mainGroup" value="">'+$('#mainGroupHiddenInput'+index).val()+"</input>";
				//eng_orgProject = eng_orgProject.replace('type="text"','type="hidden"')+$('#eng_orgProjectHiddenInput'+index).val()+"</input>";
				//eng_resource = eng_resource.replace('type="text"','type="hidden"')+$('#eng_resourceHiddenInput'+index).val()+"</input>";
				eng_orgProject = '<input type="hidden" name="designReleaseList['+index+'].engrOrgProject" value="">'+$('#eng_orgProjectHiddenInput'+index).val()+"</input>";
				eng_resource = '<input type="hidden" name="designReleaseList['+index+'].engrResource" value="">'+$('#eng_resourceHiddenInput'+index).val()+"</input>";
				
				/*clickedRow.parent().parent().children("td:eq(7)").html('');
				clickedRow.parent().parent().children("td:eq(7)").empty();*/
				clickedRow.parent().parent().children("td:eq(4)").html('');
				clickedRow.parent().parent().children("td:eq(4)").empty();
				clickedRow.parent().parent().children("td:eq(8)").html('');
				clickedRow.parent().parent().children("td:eq(8)").empty();
				clickedRow.parent().parent().children("td:eq(9)").html('');
				clickedRow.parent().parent().children("td:eq(9)").empty();
				
				/*clickedRow.parent().parent().children("td:eq(7)").append(eng_subgroup);*/
				clickedRow.parent().parent().children("td:eq(4)").append(mainGroup);
				clickedRow.parent().parent().children("td:eq(8)").append($('#eng_orgProjectHiddenInput'+index).val());
				clickedRow.parent().parent().children("td:eq(9)").append($("#eng_resourceHiddenInput"+index).val());
				/*clickedRow.parent().parent().children("td:eq(7)").children().attr('value',$('#eng_subgroupHiddenInput'+index).val());*/
				
				clickedRow.parent().parent().children("td:eq(4)").children().attr('value',$('#mainGroupHiddenInput'+index).val());
				
				
			    $("#engPublishComments_"+index).hide();
				$('#engrPublishcmnt'+index).show();
			}
			else if(status.includes('EDOT Close') || status.includes('TD Released'))
			{
				 $("#engPublishComments_"+index).hide();
				 $('#engrPublishcmnt'+index).show();
			}
			
		}
	}
		/*function getSubgroup(index, clickedRow)
		{
			
			
	    	groupList = dao.subgrpdata;
	    	$select = $("<select class='subgrp' id='engsubgrp"+index+"' name='designReleaseList[" + index +"].engrComponentNo'/>");
			$select.on( 'change', function(){ engsubgrpchange(index, clickedRow); } )
			
			$select.append("<option></option>");
			for(var item in groupList){
				$select.append("<option>" + groupList[item] + "</option>");
				
			}

			dao.engSubgrp = $select;
			$("#engsubgrp"+index).selectpicker();  
			
			
		}
		function engsubgrpchange(index, clickedRow)
		{
			getEngResources(index, clickedRow);
		}
		
		
		function getEngResources(index, clickedRow){
			//console.log("Resource change");
			$('#loadingModal').modal('show');
			var resourceList = [];
			$selectEng = "";
			$("#engrComponentNoHiddenVar_"+index).val($("#engsubgrp"+index).val());
			$("#eng_subgroupHiddenInput"+index).val($("#engsubgrp"+index).val());
			$selectEng = $("<select class='resources' name='designReleaseList[" + index +"].engrResource' id=\"engresource"+index+"\">");
			$selectEng.on( 'change', function(){ engresourcechange(index); } )
			$selectEng.css("width","200px");
			
			$selectEng.append("<option></option>");
			
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getResourceList?grpid='+$("#engsubgrp"+index).val()+'&engrole=Engineer',
			    success: function(data){
			    	resourceList = data;
			    	//console.log(resourceList);
					for(var item in resourceList){
						$selectEng.append("<option>" + resourceList[item] + "</option>");
					}
					//engresourcechange(index);
					$("#engPubresource_"+index).selectpicker();  
					$("#engPubresource_"+index).html('');
					$("#engPubresource_"+index).append($selectEng);
					$("#engresource"+index).val($("#eng_resourceHiddenInput"+index).val());
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
			
			
			if($("#engsubgrp"+index).val() == "NWR")
			{
				ifEngNWR(index,clickedRow);
			}
			
			$("#engPublishComments_"+index).show();
			$("#engrPublishcmnt"+index).hide();
			
		}*/
		
		function getMainGroup(index, clickedRow)
		{
			
			
	    	groupList = dao.maingrpdata;
			$select = $("<select class='maingrp' id='maingrp"+index+"' name='designReleaseList[" + index +"].mainGroup'/>");
			$select.on( 'change', function(){ mainGrpChange(index, clickedRow); } )
			$select.append("<option></option>");
	    	
	    	var theWidth = $("#designReleasePublish").eq(0).find("tr > td#mainGrp_0").width();
	    	if(theWidth > 0){
				$select.css("width",theWidth + "px");
			}else{
				theWidth = $("#designReleasePublish").eq(0).find("tr > td#mainGrp_"+index).width();
				$select.css("width",theWidth + "px");
			}
	    	for(var item in groupList){
				$select.append("<option>" + groupList[item] + "</option>");
			
			}

			dao.mainGrp = $select;
		
			$("#maingrp"+index).selectpicker();  
			
		}
		
		function mainGrpChange(index, clickedRow)
		{
			
			getOrgPrjectDetails(index, clickedRow);
			getEngResourcesNew(index, clickedRow);
			
		}
		
		function getOrgPrjectDetails(index, clickedRow){
			var projListData = []
			$selectPublishOrgProject = "";
			//$("#engrComponentNoHiddenVar_"+index).val($("#maingrp"+index).val());
			
			//$("#mainGroupHiddenInput"+index).val($("#maingrp"+index).val());
			//projListData = dao.projListData;
			$selectPublishOrgProject = $("<select class='orgProject' name='designReleaseList[" + index +"].engrOrgProject' id=\"engrOrgProject"+index+"\">");
			$selectPublishOrgProject.on( 'change', function(){ getEngResourcesNew(index, clickedRow); } );
			$selectPublishOrgProject.css("width","70px");
			
			var theWidth = $("#designReleasePublish").eq(0).find("tr > td#engrOrgProject_0").width();
			if(theWidth > 0){
				$selectPublishOrgProject.css("width",theWidth + "px");
			}else{
				theWidth = $("#designReleasePublish").eq(0).find("tr > td#engrOrgProject_"+index).width();
				$selectPublishOrgProject.css("width",theWidth + "px");
			}
			
			//$selectOrgProject.append("<option></option>");
			/*for(var item in projListData){
				
				$selectOrgProject.append("<option>" + projListData[item] + "</option>");
			
			}

			$("#engrOrgProject_"+index).selectpicker();  
			$("#engrOrgProject_"+index).html('');
			$("#engrOrgProject_"+index).append($selectOrgProject);
			$("#engrOrgProject"+index).val($("#eng_orgProjectHiddenInput"+index).val());
			$('#loadingModal').modal('hide');*/
			
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getProjList?mainGrp='+$("#maingrp"+index).val(),
			    success: function(data){
			    	orgProjectList = data;
			    	//console.log(resourceList);
					for(var item in orgProjectList){
						$selectPublishOrgProject.append("<option>" + orgProjectList[item] + "</option>");
					}
					//engresourcechange(index);
					$("#engrOrgProject_"+index).selectpicker();  
					$("#engrOrgProject_"+index).html('');
					$("#engrOrgProject_"+index).append($selectPublishOrgProject);
					//$("#engrOrgProject"+index).val($("#eng_orgProjectHiddenInput"+index).val());
					//$("#engrOrgProject"+index+ " option:contains("+$("#eng_orgProjectHiddenInput"+index).val()+")").attr('selected', 'selected');
					var engrOrgProjectList = $("#eng_orgProjectHiddenInput"+index).val().split('-');
				    var engrOrgProjectID = engrOrgProjectList[0];
					$("#engrOrgProject"+index+ " option:contains("+engrOrgProjectID+")").attr('selected', 'selected');
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});

			
		}
		
		function getEngResourcesNew(index, clickedRow){
			$('#loadingModal').modal('show');
			var resourceList = [];
			$selectEng = "";
			//$("#eng_orgProjectHiddenInput"+index).val($("#engrOrgProject"+index).val());
			$selectEng = $("<select class='resources' name='designReleaseList[" + index +"].engrResource' id=\"engresource"+index+"\">");
			//$selectEng.on( 'change', function(){ engresourcechange(index); } )
			$selectEng.css("width","70px");
			
			var theWidth = $("#designReleasePublish").eq(0).find("tr > td#engPubresource_0").width();
			if(theWidth >0){
				
				$selectEng.css("width",theWidth + "px");
			}else{
				theWidth = $("#designReleasePublish").eq(0).find("tr > td#engPubresource_"+index).width();
				$selectEng.css("width",theWidth + "px");
			}
			$selectEng.append("<option></option>");
			
			var engrOrgProjectVal = $("#engrOrgProject"+index).val();
			
			if($("#engrOrgProject"+index).val() == null || $("#engrOrgProject"+index).val() == undefined){
				engrOrgProjectVal = $("#eng_orgProjectHiddenInput"+index).val();
			}
			
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getEngrResourceList?grpid='+engrOrgProjectVal+'&engrole=Engineer',
			    success: function(data){
			    	resourceList = data;
			    	for(var item in resourceList){
						$selectEng.append("<option>" + resourceList[item] + "</option>");
					}
					$("#engPubresource_"+index).selectpicker();  
					$("#engPubresource_"+index).html('');
					$("#engPubresource_"+index).append($selectEng);
					$("#engresource"+index).val($("#eng_resourceHiddenInput"+index).val());
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
			
		}
		
		function ifEngNWR(index,clickedRow)
		{
			
			var engResources= clickedRow.parent().parent().children("td:eq(8)").html();
			engResources=engResources.substring(0,engResources.indexOf(">")+1);
			engResources = engResources.replace('select','input type="hidden" value=null')+"-"+"</input>";
			clickedRow.parent().parent().children("td:eq(8)").html('');
			clickedRow.parent().parent().children("td:eq(8)").empty();
			clickedRow.parent().parent().children("td:eq(8)").append(engResources);
			
		}
		
		function engresourcechange(index)
		{
			//console.log($("#engresource"+index).val());
			$("#eng_resourceHiddenInput"+index).val($("#engresource"+index).val());
		}
		$('#publishallcheckbox').click(function () {
			 if(this.checked){
		            $('.editpublishTableCheckboxes:enabled').each(function(){
		               this.checked = true;
		               var row = $(this);
		               editPublishDetails(row,$(this).data('index'));
		               fixedHeaderScroll();
		            });
		        }else{
		             $('.editpublishTableCheckboxes:enabled').each(function(){
		                this.checked = false;
		                var row = $(this);
		                editPublishDetails(row,$(this).data('index'));
		                fixedHeaderScroll();
		            });
		        }
			
		});
		
		function fixedHeaderScroll(){
			//Fixed header scroll.
			
			var table = $('#designReleasePublish').DataTable( {
				/*destroy: true,*/
	    		"bPaginate": false,
	    		 "scrollY": 600,
	    	     "scrollX": true,
	    	     "ordering": false,
	    	     "bFilter": false,
	    	     "bInfo": false,
	    	     bRetrieve: true,
	    	       /* fixedHeader: {
	    	            header: true
	    				 
	    	        }*/
	    			} );
	    	$('#designReleasePublish').resize();
	    	table.fixedHeader.adjust();
	    	//$(table).dataTable().fnAdjustColumnSizing();
		}
		
		$('.search-btn').click(function(){
			var filterValue = $("#publishSearchTerm").val();
			
			$(".designReleasePublishTable tr").each(function(rowId, row) 
					{ 
					var isContentPresent = false;
					if($(this).css('display') != 'none'){ 
						 
					 
						  var bomLine = $(this).find('td').eq(1).text();
							if(bomLine != null && bomLine != " " && bomLine != "" && bomLine != undefined){
								for(var i=1;i<14;i++){
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