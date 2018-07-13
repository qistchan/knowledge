var templeScopeMap = [];
$(document).ready(function() {	

		$('#projectsDropDown').selectpicker();
		$('#templatesDropDown').selectpicker();
		$('#scopesDropDown').selectpicker();
		$('#dreBuildFilterData').selectpicker();
		
		window.getProjectVal;
		/*$(document).tooltip();*/
		
		function getContextPath() {
			   return window.location.pathname.substring(0, window.location.pathname.indexOf("/",2));
			}
		
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
		
		function resetTemplateDropdown(){
			$("#templatesDropDown option:selected").removeAttr("selected");
	    	$("#templatesDropDown option:eq(0)").attr("selected", true);
	    	$('#templatesDropDown').parent().find('button').each(function(){
	    			$(this).children("span:first").empty();
	    			$(this).children("span:first").append('Please Select')
	    	});
	    	$('#templatesDropDown').parent().find('.dropdown-menu').find('li').each(function(){
	    		if($(this).attr('class') == 'selected'){
	    			$(this).removeAttr('class');
	    		}
	    		if($(this).attr('data-original-index')=='0'){
	    			$(this).attr('class','selected')
	    		}
	    	});
		}
		
		function addToDesignExistInModalErrorVal(checkBoxes){
			var designExistInModalErrorVal = $("#designExistInModalErrorHidden").val();
			if("" == designExistInModalErrorVal){
				$('#designExistInModalErrorHidden').attr('value',checkBoxes);
			}else{
				if(designExistInModalErrorVal.indexOf(",") > 0){
					var designExistInModalErrorValArr = designExistInModalErrorVal.split(",");
					$.each(checkBoxes, function (index, value) {
							designExistInModalErrorValArr.push(value);
						});
					$('#designExistInModalErrorHidden').attr('value',designExistInModalErrorValArr);
				}else{
					var designExistInModalErrorValArr = [];
					designExistInModalErrorValArr.push(designExistInModalErrorVal);
					$.each(checkBoxes, function (index, value) {
							designExistInModalErrorValArr.push(value);
						});
					$('#designExistInModalErrorHidden').attr('value',designExistInModalErrorValArr);
				}
			}
		}
		
		function deleteFromDesignExistInModalErrorVal(checkBoxes){
			var designExistInModalErrorVal = $("#designExistInModalErrorHidden").val();
			if("" != designExistInModalErrorVal){
				if(designExistInModalErrorVal.indexOf(",") > 0){
					var designExistInModalErrorValArr = designExistInModalErrorVal.split(",");
					$.each(checkBoxes, function (index, value) {
						var index = $.inArray(value, designExistInModalErrorValArr);
						if (index >= 0) {
							designExistInModalErrorValArr.splice(index, 1);
						}
					});
					$('#designExistInModalErrorHidden').attr('value',designExistInModalErrorValArr);
				}else{
					var designExistInModalErrorValArr = [];
					designExistInModalErrorValArr.push(designExistInModalErrorVal);
					$.each(checkBoxes, function (index, value) {
						var index = $.inArray(value, designExistInModalErrorValArr);
						if (index >= 0) {
							designExistInModalErrorValArr.splice(index, 1);
						}
					});
					$('#designExistInModalErrorHidden').attr('value',designExistInModalErrorValArr);
				}
			}
		}
		
		
		function addToDesignExistInTemplateModalVal(checkBoxes){
			var designExistInModalErrorVal = $("#designExistInTemplateModalHidden").val();
			if("" == designExistInModalErrorVal){
				$('#designExistInTemplateModalHidden').attr('value',checkBoxes);
			}else{
				if(designExistInModalErrorVal.indexOf(",") > 0){
					var designExistInModalErrorValArr = designExistInModalErrorVal.split(",");
					$.each(checkBoxes, function (index, value) {
							designExistInModalErrorValArr.push(value);
						});
					$('#designExistInTemplateModalHidden').attr('value',designExistInModalErrorValArr);
				}else{
					var designExistInModalErrorValArr = [];
					designExistInModalErrorValArr.push(designExistInModalErrorVal);
					$.each(checkBoxes, function (index, value) {
							designExistInModalErrorValArr.push(value);
						});
					$('#designExistInTemplateModalHidden').attr('value',designExistInModalErrorValArr);
				}
			}
		}
		
		function deleteFromDesignExistInTemplateModalVal(checkBoxes){
			var designExistInModalErrorVal = $("#designExistInTemplateModalHidden").val();
			if("" != designExistInModalErrorVal){
				if(designExistInModalErrorVal.indexOf(",") > 0){
					var designExistInModalErrorValArr = designExistInModalErrorVal.split(",");
					$.each(checkBoxes, function (index, value) {
						var index = $.inArray(value, designExistInModalErrorValArr);
						if (index >= 0) {
							designExistInModalErrorValArr.splice(index, 1);
						}
					});
					$('#designExistInTemplateModalHidden').attr('value',designExistInModalErrorValArr);
				}else{
					var designExistInModalErrorValArr = [];
					designExistInModalErrorValArr.push(designExistInModalErrorVal);
					$.each(checkBoxes, function (index, value) {
						var index = $.inArray(value, designExistInModalErrorValArr);
						if (index >= 0) {
							designExistInModalErrorValArr.splice(index, 1);
						}
					});
					$('#designExistInTemplateModalHidden').attr('value',designExistInModalErrorValArr);
				}
			}
		}
		
		function fetchDesignExistInModalErrorArray(){
			var checkBoxes = [];
			var designExistInModalErrorVal = $("#designExistInModalErrorHidden").val();
			if("" == designExistInModalErrorVal){
				return checkBoxes;
			}else{
				if(designExistInModalErrorVal.indexOf(",") > 0){
					var designExistInModalErrorValArr = designExistInModalErrorVal.split(",");
					$.each(designExistInModalErrorValArr, function (index, value) {
						checkBoxes.push(value);
					});
					return checkBoxes;
				}else{
					checkBoxes.push(designExistInModalErrorVal);
					return checkBoxes;
				}
			}
		}
		
		function fetchDesignExistInTemplateModalHiddenArray(){
			var checkBoxes = [];
			var designExistInModalErrorVal = $("#designExistInTemplateModalHidden").val();
			if("" == designExistInModalErrorVal){
				return checkBoxes;
			}else{
				if(designExistInModalErrorVal.indexOf(",") > 0){
					var designExistInModalErrorValArr = designExistInModalErrorVal.split(",");
					$.each(designExistInModalErrorValArr, function (index, value) {
						checkBoxes.push(value);
					});
					return checkBoxes;
				}else{
					checkBoxes.push(designExistInModalErrorVal);
					return checkBoxes;
				}
			}
		}
		
		function fetchDesignNonExistInModal(){
			var checkBoxes = [];
			var designNonExistInTemplateModalVal = $("#designNonExistInTemplateModalHidden").val();
			if("" == designNonExistInTemplateModalVal){
				return checkBoxes;
			}else{
				if(designNonExistInTemplateModalVal.indexOf(",") > 0){
					var designNonExistInTemplateModalValArr = designNonExistInTemplateModalVal.split(",");
					$.each(designNonExistInTemplateModalValArr, function (index, value) {
						checkBoxes.push(value);
					});
					return checkBoxes;
				}else{
					checkBoxes.push(designNonExistInTemplateModalVal);
					return checkBoxes;
				}
			}
		}
		
		window.setInterval(function(){
			$(".designReleaseTableHead").width($(".designReleaseTable").width());
			$(".designReleaseTable tbody tr td").each(function (i){
			       $(this).width($($(".designReleaseTableHead tr:first th")[i]).width());
			});
		}, 100);
		
		$('.templateBuildBtn').click(function(){
			$(".templateHeader").empty();
			$("#templateScopeApply").hide();
	    	$("#templateScopeReset").hide();
	    	$(".templateHeader").append("Template Selection ");
	    	$(".templateBody").empty();
			resetScopeDropdown();
			resetTemplateDropdown();
			//Get template and scope from server
			var projectValue = $('#projectsDropDown').val();
			
			if(projectValue == '-1'){
				getProjectVal = projectValue;
				return;
			}else{
				$("#projectIdHidden").attr('value',projectValue);
				getProjectVal = projectValue;
			}
			var selectOptions = "<option value='-1' selected>Please select</option>";
			templeScopeMap = [];
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getTemplateScopeMap?projectId='+projectValue,
			    success: function(data){
			    	$.each(data, function(key, value) {
			    		templeScopeMap.push({templateKey:key,templateScopeVal: value});
					   selectOptions = selectOptions+ "<option>"+key+"</option>";
					});
			    	$('#templatesDropDown').selectpicker();
			    	 $("#templatesDropDown").html(selectOptions).selectpicker('refresh');
			    	
			    	
			    }
			});
			
			//end
			$("#template").modal('show');
		});
		
		//On change of the template set the select options for scope.
		$('#templatesDropDown').change(function(){
			var selectedECR = $('#templatesDropDown').val();
			var selectOptions = "<option value='-1' selected>Please select</option>";
			$.each(templeScopeMap, function( key, valueLst ) {
				if(valueLst.templateKey == selectedECR){
					var scopeOptionsLst =  valueLst.templateScopeVal;
					$.each( scopeOptionsLst, function( index, scopeValues ){
						selectOptions = selectOptions+ "<option>"+scopeValues+"</option>";
					});
					
				}
			});
			$('#scopesDropDown').selectpicker();
	    	$("#scopesDropDown").html(selectOptions).selectpicker('refresh');
	    	
		});
		
		$('#templateScopeReset').click(function(){
			resetScopeDropdown();
			resetTemplateDropdown();
			$(".templateBody").empty();
			$('#designExistInModalErrorHidden').attr('value',"");
			$('#designExistInTemplateModalHidden').attr('value',"");
			$('.templateScopeParentCheckboxes').each(function(){
				$(this).prop('checked',false);
				$(this).parent().parent().removeClass('existRootActivity');
			});
			$('.templateScopeCheckboxes').each(function(){
				$(this).prop('checked',false);
				$(this).parent().parent().removeClass('existActivity');
			});
			$.ajax({
				method: "POST",
				contentType:"application/json",
			    dataType: "json",
			    url: getContextPath()+'/resetTemplate',
			    success: function(data){
			    	console.log(data);
			    },error: function(data){
			    	console.log(data);
			    }
			});
		});
		
		$('.projectInfoBuildBtn').click(function(){
			$("#project_id").html($("#projectsDropDown").val());
			$('#projectInfoBuild').modal('show');
		});
		
		$('.projectRefresh').click(function(){
			$('#projectsDropDown').change();
		});
		
		$('.dreBuildFilterClass').change(function(){
			var filterValue = $("#dreBuildFilterData").val();
			$("#buildSearchTerm").val("");
			$(".designReleaseTable tr").each(function() 
			{ 
				var edotVal = $(this).find('td').eq(12).text();
				var bomLine = $(this).find('td').eq(0).text();
	               if(bomLine != "" && bomLine != " " && bomLine != undefined && filterValue != -1){
	            	   if(edotVal != "" && edotVal != " " && edotVal != undefined){
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
		
		$('.templateCloseBtn').click(function(){
			resetScopeDropdown();
			$('#designExistInModalErrorHidden').attr('value',"");
			$('#designExistInTemplateModalHidden').attr('value',"");
			$('.templateScopeParentCheckboxes').each(function(){
				$(this).prop('checked',false);
				$(this).parent().parent().removeClass('existRootActivity');
			});
			$('.templateScopeCheckboxes').each(function(){
				$(this).prop('checked',false);
				$(this).parent().parent().removeClass('existActivity');
			});
			$.ajax({
				method: "POST",
				contentType:"application/json",
			    dataType: "json",
			    url: getContextPath()+'/resetTemplate',
			    success: function(data){
			    	console.log(data);
			    },error: function(data){
			    	console.log(data);
			    }
			});
			$("#template").modal('hide');
		});
		
		$('.templateDropDownErrorCloseBtn').click(function(){
			resetScopeDropdown();
			$("#templateDropDownError").modal('hide');
		});
		
		$('.projectDropDownErrorCloseBtn').click(function(){
			resetScopeDropdown();
			$("#projectDropDownError").modal('hide');
		});
		
		$('.rootCollapsedIcon').click(function(){
			var id = $(this).attr('id');
			if($(this).hasClass("tree-collapsed")){
				var key = id.substring(5, id.length);
				$('.child_'+key).show();
				$(this).removeClass("tree-collapsed");
				$(this).addClass("tree-expanded");
			}else{
				var key = id.substring(5, id.length);
				$('.child_'+key).css('display','none');
				$(this).removeClass("tree-expanded");
				$(this).addClass("tree-collapsed");
			}
		});
		
		$(document).on('click', '.deleteDesign', function () { // <-- changes
		     $(this).closest('tr').remove();
		     return false;
		 });
		
		function createDesignReleaseEmptyTableRow(index){
			$("#designReleaseListEmpty").attr('value','true');
			var className = "";
			if(index % 2 == 0){
				className = "backGround8FF";
			}
			var row = $('<tr>');
			row.attr('class',className);
			for(var i=0; i < 14; i++){
				row.append($('<td>').append('&nbsp;'));
			}
			return row;
		}
		
		function createDesignReleaseTableRow(index , value){
			$("#designReleaseListEmpty").attr('value','false');
			var className = "";
			if(index % 2 == 0){
				className = "backGround8FF";
			}
			
			var engrStartDatelabeldateHiddenInput = $("<input type='hidden' id='engrStartDatelabelHiddenInput"+index+"' value='"+value.engrStartDateLabel+"'/>");
			var engrRequiredDatelabeldateHiddenInput = $("<input type='hidden' id='engrRequiredDatelabelHiddenInput"+index+"' value='"+value.engrRequiredDateLabel+"'/>");
			var designRequiredDatelabeldateHiddenInput = $("<input type='hidden' id='designRequiredDatelabelHiddenInput"+index+"' value='"+value.designRequiredDateLabel+"'/>");
			
			var bomLineItemId = value.bomLineItemId;
			var bomLineItemLastcharVal = bomLineItemId.substr((bomLineItemId.length-1), 1).charCodeAt();
			var status = value.status;
			
			var row = $('<tr>');
    		row.attr('class',className);
    		var edotColumn = $('<td>');
    		var edotInput = $("<input type='hidden' class='edotHiddenId' id='edotId"+index+"' name='designReleaseList[" + index +"].edot' value='" + value.edot + "'>"+ value.edot +"</input>");
    		edotColumn.append(edotInput);
    		
    		var bomLineItemIdColumn = $('<td>');
    		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+index+"' name='designReleaseList[" + index +"].bomLineItemId' value='" + value.bomLineItemId +"' data-edot= '"+value.designReleaseId+"' data-index ='"+index+ "'>"+ value.bomLineItemId +"</input>");
    		bomLineItemIdColumn.append(bomLineItemIdInput);
    		
    		var descriptionColumn = $('<td>');
    		var descriptionInput = $("<input type='hidden' name='designReleaseList[" + index +"].description' value='" + value.description + "'>" + value.description +"</input>");
    		descriptionColumn.append(descriptionInput);
    		
    		var engrStartDateColumn = $('<td>');
    		var engrStartDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrStartDate' value='" + value.engrStartDate + "'>" + value.engrStartDateLabel +"</input>");
    		engrStartDateColumn.append(engrStartDateInput);
    		
    		var engrRequiredDateColumn = $('<td>');
    		var engrRequiredDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrRequiredDate'  value='" + value.engrRequiredDate + "'>" + value.engrRequiredDateLabel +"</input>");
    		engrRequiredDateColumn.append(engrRequiredDateInput);
    		
    		var designRequiredDateColumn = $('<td>');
    		var designRequiredDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].designRequiredDate' value='" + value.designRequiredDate + "'>" + value.designRequiredDateLabel +"</input>");
    		designRequiredDateColumn.append(designRequiredDateInput);
    		
    		var engrComponentNoColumn = $('<td>');
    		var engrComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrComponentNo' value='" + value.engrComponentNo + "'>" + value.engrComponentNo +"</input>");
    		engrComponentNoColumn.append(engrComponentNoInput);
    		
    		var designComponentNoColumn = $('<td>');
    		var designComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].designComponentNo' value='" + value.designComponentNo + "'>" + value.designComponentNo +"</input>");
    		designComponentNoColumn.append(designComponentNoInput);
    		
    		var backOffColumn = $('<td>');
    		var backOffInput = $("<input type='hidden' name='designReleaseList[" + index +"].backOff' value='" + value.backOff + "'>" + value.backOff +"</input>");
    		backOffColumn.append(backOffInput);
    		
    		var engrDurationColumn = $('<td>');
    		var engrDurationInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrDuration' value='" + value.engrDuration + "'>" + value.engrDuration +"</input>");
    		engrDurationColumn.append(engrDurationInput);
    		
    		var designDurationColumn = $('<td>');
    		var designDurationInput = $("<input type='hidden' name='designReleaseList[" + index +"].designDuration' value='" + value.designDuration + "'>" + value.designDuration +"</input>");
    		designDurationColumn.append(designDurationInput);
    		
    		var designReleaseIdColumn = $('<td>');
    		var designReleaseIdInput = $("<input type='hidden' id='designReleaseId"+index+"' name='designReleaseList[" + index +"].designReleaseId' value='" + value.designReleaseId + "'>" + value.designReleaseId +"</input>");
    		designReleaseIdColumn.append(designReleaseIdInput);
    		
    		var statusColumn = $('<td>');
    		var statusInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + value.status + "'>" + value.status +"</input>");
    		statusColumn.append(statusInput);
    		
    		var templateNameColumn = $('<td>');
    		var templateNameInput = $("<input type='hidden' name='designReleaseList[" + index +"].templateName' value='" + value.templateName + "'>" + value.templateName +"</input>");
    		templateNameColumn.append(templateNameInput);
    		
    		var actionColumn = $('<td>');
    		var actionButton = $("<span title='Delete' class='glyphicon glyphicon-trash btn-md redColor cursorPointer deleteDesign' id='" + value.bomLineItemId +"_"+value.templateName +"'></span>");
    		var editButton = $("<span title='Create SubTask' class='glyphicon glyphicon-edit btn-md blueColor cursorPointer editDesign' id='" + value.bomLineItemId +"_"+value.templateName + "' data-edot= '"+value.designReleaseId+"' data-index ='"+index+ "'></span>");
    		if(value.designReleaseId.length == 0){
    			actionColumn.append(actionButton);
    		}else{
    			if(!(bomLineItemLastcharVal >= 65 && bomLineItemLastcharVal <= 90) &&  (!status.includes("Sub Task")))
    			{
    				
    				actionColumn.append(editButton);
    			}
    			//actionColumn.append(editButton);
    		}
    		
    		var engrOrgProjectColumn = $('<td>');
    		var engrOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrOrgProject' value='" + value.engrOrgProject+ "'>" +value.engrOrgProject  +"</input>");
    		engrOrgProjectColumn.append(engrOrgProjectInput);
    		
    		var designOrgProjectColumn = $('<td>');
    		var designOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].designOrgProject' value='" + value.designOrgProject + "'>" + value.designOrgProject +"</input>");
    		designOrgProjectColumn.append(designOrgProjectInput);
    		
    		/*row.append(edotColumn);*/
    		row.append(bomLineItemIdColumn);
    		row.append(descriptionColumn);
    		row.append(engrDurationColumn);
    		row.append(engrStartDateColumn);
    		row.append(backOffColumn);
    		row.append(engrRequiredDateColumn);
    		row.append(designDurationColumn);
    		row.append(designRequiredDateColumn);
    		/*row.append(engrComponentNoColumn);
    		row.append(designComponentNoColumn);*/
    		row.append(engrOrgProjectColumn);
    		row.append(designOrgProjectColumn);
    		row.append(statusColumn);
    		row.append(templateNameColumn);
    		row.append(designReleaseIdColumn);
    		row.append(actionColumn);
	    	
    		actionColumn.append(engrStartDatelabeldateHiddenInput);
    		actionColumn.append(engrRequiredDatelabeldateHiddenInput);
    		actionColumn.append(designRequiredDatelabeldateHiddenInput);
    		
    		return row;
		}
		
		$('#templateScopeApply').click(function(){
			var arrCheckBoxes = [];
			var arrBomLineItems = [];
			var arrDesignReleaseBom = 0;
			var returnLoop = false;
			var anyCheckBoxChecked = false;
			var allDesignReleaseIdexist = false;
			var designExistInTemplateModalHidden = $('#designExistInTemplateModalHidden').val();
			$('.bomLineHiddenItemId').each(function(){
				var bomLineItem = $(this).val();
				var id = $(this).attr('id');
				var index = id.substring(6, id.length);
				var designreleaseId = $('#designReleaseId'+index).val();
				arrBomLineItems.push([bomLineItem,designreleaseId]);
			});
			$("#designExistErrorLabel").empty();
			$("#onlyDesignExistErrorLabel").empty();
			/*$('.templateScopeCheckboxes').each(function(){
				var checked = $(this).prop('checked');
				var id =  $(this).attr('id');
				if(checked){
					arrCheckBoxes.push(id);
					anyCheckBoxChecked=true;
				}
			});*/
			arrCheckBoxes = fetchDesignExistInTemplateModalHiddenArray();
			if("" != designExistInTemplateModalHidden){
				anyCheckBoxChecked=true;
			}
			if(!anyCheckBoxChecked){
				$('#noActivitySelectError').modal('show');
				return;
			}
			for(var i=0; i< arrCheckBoxes.length;i++){
				var id = arrCheckBoxes[i];
				for(var j=0; j< arrBomLineItems.length;j++){
					var item = arrBomLineItems[j][0];
					var designId = arrBomLineItems[j][1];
					if(id==item){
						if(designId.length>0){
							$("#designExistErrorLabel").append(id + " ,");
							arrDesignReleaseBom++;
						}else{
							$("#designExistErrorLabel").append(id + " ,");
						}
						returnLoop = true;
					}
				}
			}
			if(arrDesignReleaseBom == arrCheckBoxes.length){
				allDesignReleaseIdexist = true;
			}
			if(returnLoop){
				if(allDesignReleaseIdexist){
					$("#onlyDesignExistErrorLabel").append("All selected templates PR are already created and is attached to Project , please select other templates.");
					$("#onlyDesignIdExistError").modal('show');
				}else{
					$("#designExistErrorLabel").append(" already exists, Please click Yes to update the data.");
					$("#designExistError").modal('show');
				}
				return;
			}
			$("#template").modal('hide');
			var designReleaseListEmptyStr = $("#designReleaseListEmpty").val();
			$.ajax({
				method: "POST",
				contentType:"application/json",
			    dataType: "json",
			    url: getContextPath()+'/applyTemplate?checkedTemplates='+arrCheckBoxes,
			    success: function(data){
			    	if(designReleaseListEmptyStr == 'true'){
			    		$(".designReleaseTable tbody").empty();
			    	}else{
			    		 $("#designReleaseListEmpty").attr('value','false');
			    	}
			    	var i = 0 ; 
			    	$('.designReleaseTable tbody tr').each(function(){
			    		i++;
			    	});
			    	$.each(data, function(index, value){
			    		var row = createDesignReleaseTableRow((index+i) , value);
				    	$(".designReleaseTable tbody").append(row);
				    	resetScopeDropdown();
			    	});
			    	$('#designExistInTemplateModalHidden').attr('value',"");
			    	resetScopeDropdown();
					resetTemplateDropdown();
					$(".templateBody").empty();
					$('#designExistInModalErrorHidden').attr('value',"");
					$('#designExistInTemplateModalHidden').attr('value',"");
					$('.templateScopeParentCheckboxes').each(function(){
						$(this).prop('checked',false);
						$(this).parent().parent().removeClass('existRootActivity');
					});
					$('.templateScopeCheckboxes').each(function(){
						$(this).prop('checked',false);
						$(this).parent().parent().removeClass('existActivity');
					});
					fixedHeaderScroll();
			    }
			});
		});
		
		$('#templateScopeUpdate').click(function(){
			var arrCheckBoxes = [];
			var arrBomLineItems = [];
			var arrExistingItems = [];
			var returnLoop = false;
			$('.bomLineHiddenItemId').each(function(){
				var bomLineItem = $(this).val();
				arrBomLineItems.push(bomLineItem);
			});
			$("#designExistErrorLabel").empty();
			$('.templateScopeCheckboxes').each(function(){
				var checked = $(this).prop('checked');
				var id =  $(this).attr('id');
				if(checked){
					arrCheckBoxes.push(id);
				}
			});
			for(var i=0; i< arrCheckBoxes.length;i++){
				var id = arrCheckBoxes[i];
				for(var j=0; j< arrBomLineItems.length;j++){
					var item = arrBomLineItems[j];
					if(id==item){
						returnLoop = true;
						arrExistingItems.push(id);
					}
				}
			}
			if(returnLoop){
				$("#designExistError").modal('hide');
			}
			$("#checkedTemplatesHidden").attr('value',arrCheckBoxes);
			$("#existingcheckedTemplatesHidden").attr('value',arrExistingItems);
			$("#projectIdHidden").attr('value',$('#projectsDropDown').val());
			var designReleaseListEmptyStr = $("#designReleaseListEmpty").val();
			$.ajax({
				method: "POST",
			    data : $('#designReleaseWrapper').serialize(),
			    url: getContextPath()+'/updateTemplate',
			    success: function(data){
			    	$("#template").modal('hide');
			    	$("#designExistError").modal('hide');
			    	if(designReleaseListEmptyStr == 'true'){
			    		$(".designReleaseTable tbody").empty();
			    	}else{
			    		 $("#designReleaseListEmpty").attr('value','false');
			    	}
			    	$(".designReleaseTable tbody").empty();
			    	$.each(data, function(index, value){
			    		var row = createDesignReleaseTableRow(index , value);
				    	$(".designReleaseTable tbody").append(row);
				    	resetScopeDropdown();
			    	});
			    	$('#designExistInTemplateModalHidden').attr('value',"");
			    	resetScopeDropdown();
					resetTemplateDropdown();
					$(".templateBody").empty();
					$('#designExistInModalErrorHidden').attr('value',"");
					$('#designExistInTemplateModalHidden').attr('value',"");
					$('.templateScopeParentCheckboxes').each(function(){
						$(this).prop('checked',false);
						$(this).parent().parent().removeClass('existRootActivity');
					});
					$('.templateScopeCheckboxes').each(function(){
						$(this).prop('checked',false);
						$(this).parent().parent().removeClass('existActivity');
					});
			    }
			});
		});
		
		$("#saveDesignRelease").click(function(){
			var projectValue = $('#projectsDropDown').val();
			var designReleaseListEmpty = $("#designReleaseListEmpty").val();
			var designReleaseIdListCount = 0;
			$('.bomLineHiddenItemId').each(function(){
				var bomLineItem = $(this).val();
				var id = $(this).attr('id');
				var index = id.substring(6, id.length);
				var designreleaseId = $('#designReleaseId'+index).val();
				if(designreleaseId.length == 0){
					designReleaseIdListCount++;
				}
			});
			if(projectValue == '-1'){
				$("#projectDropDownError").modal('show');
				return;
			}else{
				$("#projectIdHidden").attr('value',projectValue);
			}
			if((designReleaseListEmpty == 'true') || (designReleaseIdListCount == 0)){
				$("#designReleaseListEmptyError").modal('show');
				return;
			}
			$('#loadingModal').modal('show');
			$.ajax({
				method: "POST",
			    data : $('#designReleaseWrapper').serialize(),
			    url: getContextPath()+'/saveDesignRelease',
			    success: function(data){
			    	$('#loadingModal').modal('hide');
			    	$('#designSaveLabel').html('');
			    	if("Design Release attached successfully" == data){
			    		$('#designSaveLabel').css('color','green');
			    	}else{
			    		$('#designSaveLabel').css('color','red');
			    	}
			    	$('#designSaveLabel').html(data);
			    	$('#designSavedModal').modal('show');
			    },
	              error: function (error) {
	            	  $('#loadingModal').modal('hide');
				    	$('#designSaveLabel').html('');
				    	if("Design Release attached successfully" == error.responseText){
				    		$('#designSaveLabel').css('color','green');
				    	}else{
				    		$('#designSaveLabel').css('color','red');
				    	}
				    	$('#designSaveLabel').html(error.responseText);
				    	$('#designSavedModal').modal('show');
	              }
			});
		});
		
		$('.designSaveOk').click(function(){
			$('#designSavedModal').modal('hide');
			$('#projectsDropDown').change();
		});
		
		
		
		
		$('#cancelDesignRelease').click(function(){
			window.location.href= getContextPath()+"/login";
		});
		
		$('#projectsDropDown').change(function(){
			$("#projectIdHidden").attr('value',$(this).val());
			var projectValue = $('#projectsDropDown').val();
			
			if(projectValue == '-1'){
				$("#projectDataProjectName").html('');
		    	$("#projectDataCustomerName").html('');
		    	$("#projectDataP1").html('');
		    	$("#projectDataK1").html('');
		    	$("#projectDataPrimaryNo").html('');
		    	$("#projectDataSecondaryNo").html('');
		    	$("#projectDataOrderNo").html('');
		    	$("#projectDataSalesForceId").html('');
		    	$("#engrProductLine").html('');
		    	$(".designReleaseTable tbody").empty();
		    	$(".projectInfoBuildBtn").hide();
		    	$(".templateBuildBtn").hide();
		    	$(".projectRefresh").hide();
		    	$(".filterBuildDataClass").hide();
		    	for(var i=0 ; i<12 ;i++){
		    		var row = createDesignReleaseEmptyTableRow(i);
			    	$(".designReleaseTable tbody").append(row);
		    	}
		    	getProjectVal = projectValue;
				return;
			}else{
				$("#projectIdHidden").attr('value',projectValue);
				getProjectVal = projectValue;
			}
			$('#loadingModal').modal('show');
			var designReleaseListEmptyStr = $("#designReleaseListEmpty").val();
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getProjectData?projectId='+projectValue,
			    success: function(data){
			    	getProjectVal = projectValue;
			    	$('.projectInfoBuildBtn').show();
			    	$('.templateBuildBtn').show();
			    	$('.projectRefresh').show();
			    	var sVal = $('select[name=dreBuildFilterData] option:first').val();
					$('select[name=dreBuildFilterData]').val(sVal);
					$(".dreBuildFilterClass").selectpicker('refresh');
					$(".filterBuildDataClass").show();
					$("#buildSearchTerm").val("");
			    	$.ajax({
						method: "GET",
					    url: getContextPath()+'/getAssociatedDesignItems?projectId='+projectValue,
					    success: function(associatedDesign){
					    	if(associatedDesign.length > 0){
						    	if(designReleaseListEmptyStr == 'true'){
						    		$(".designReleaseTable tbody").empty();
						    	}else{
						    		$(".designReleaseTable tbody").empty();
						    		 $("#designReleaseListEmpty").attr('value','false');
						    	}
						    	$.each(associatedDesign, function(index, value){
						    		var row = createDesignReleaseTableRow(index , value);
							    	$(".designReleaseTable tbody").append(row);
							    	resetScopeDropdown();
						    	});
					    	}else{
					    		$(".designReleaseTable tbody").empty();
						    	for(var i=0 ; i<12 ;i++){
						    		var row = createDesignReleaseEmptyTableRow(i);
							    	$(".designReleaseTable tbody").append(row);
						    	}
					    	}
					    	$('#loadingModal').modal('hide');
					    	$("#projectDataProjectName").html('');
					    	$("#projectDataCustomerName").html('');
					    	$("#projectDataP1").html('');
					    	$("#projectDataK1").html('');
					    	$("#projectDataPrimaryNo").html('');
					    	$("#projectDataSecondaryNo").html('');
					    	$("#projectDataOrderNo").html('');
					    	$("#projectDataSalesForceId").html('');
					    	$("#engrProductLine").html('');
					    	setProjectInfoData(data);
					    	/*$.each(data, function(key, value){
					    		if(key == 'object_name'){
					    			$("#projectDataProjectName").html(value[0]);
					    		}else if(key == 'get6AppBuildRefDateSecond'){
					    			$("#projectDataK1").html(value[0]);
					    		}else if(key == 'get6AppBuildRefDatePrimary'){
					    			$("#projectDataP1").html(value[0]);
					    			$("#projectP1DateHidden").attr('value',value[0]);
					    		}else if(key == 'get6OrderNumber'){
					    			$("#projectDataOrderNo").html(value[0]);
					    		}else if(key == 'get6CustomerName'){
					    			$("#projectDataCustomerName").html(value[0]);
					    		}else if(key == 'get6PrimaryProjectNumber'){
					    			$("#projectDataPrimaryNo").html(value[0]);
					    		}else if(key == 'get6SalesForceID'){
					    			$("#projectDataSalesForceId").html(value[0]);
					    		}else if(key == 'get6SecondaryProjectNumber'){
					    			$("#projectDataSecondaryNo").html(value[0]);
					    		}else if(key == 'get6EngrProdLine'){
					    			$("#engrProductLine").html(value[0]);
					    		}
					    	});*/
					    	$('.editDesign').click(function(){
					    		var row = $(this);
					    		var index = $(this).data('index');
					    		editBuildDetails(row,index);
							});
					    	//Fixed header scroll.
					    	var table = $('#designReleaseBuild').DataTable( {
					    		
					    		"bPaginate": false,
					    		 "scrollY": 600,
					    	     "scrollX": true,
					    	     "ordering": false,
					    	     "bFilter": false,
					    	     "bInfo": false,
					    	      bRetrieve: true,
					    	     
					    	        /*fixedHeader: {
					    	            header: true
					    				 
					    	        }*/
					    			} );
					    	$('#designReleaseBuild').resize();
					    	table.fixedHeader.adjust();
					    }
			    	});
			    }
			});
		});
		
		
		$('#scopesDropDown').change(function(){
			$(".templateBody").empty();
			var arrCheckBoxes = [];
			var templateValue = $('#templatesDropDown').val();
			var scope = $(this).val();
			if(templateValue == '-1'){
				$("#templateDropDownError").modal('show');
			}else if(scope == '-1'){
				return;
			}else{
				$('.templateScopeCheckboxes').each(function(){
					var checked = $(this).prop('checked');
					var id =  $(this).attr('id');
					if(checked){
						arrCheckBoxes.push(id);
					}
				});
				$("#loadingModal").modal('show');
				$.ajax({
					method: "GET",
					contentType:"application/json",
				    dataType: "json",
				    url: getContextPath()+'/getTemplateScope?template='+templateValue+'&scope='+scope+'&checkedTemplates='+arrCheckBoxes,
				    success: function(data){
				    	$("#loadingModal").modal('hide');
				    	/*$(".templateHeader").empty();
				    	$(".templateHeader").append("Template Selection : "+templateValue + "-" +scope);*/
				    	$("#template").modal('show');
				    	$("#templateScopeApply").show();
				    	$("#templateScopeReset").show();
				    	$(".templateBody").empty();
				    	var html = "";
				    	var rootsCheck = [];
				    	var rootsExist = [];
				    	html = html + "<table class='templateScopeTable'><tr><th class='centerAlign width13 label-primary'>Activity Id</th><th class='centerAlign width27 label-primary'>Description</th><th class='centerAlign width15 label-primary'>Engr <br/>Component No</th><th class='centerAlign width15 label-primary'>Design <br/>Component No</th><th class='centerAlign width10 label-primary'>Back Off</th><th class='centerAlign width10 label-primary'>Engr<br/>Duration</th><th class='centerAlign width10 label-primary'>Design<br/>Duration</th></tr>";
				    	$.each(data, function(key, value){
				    		html = html + "<tr><td><div class='tree-collapsed rootCollapsedIcon' id='root_"+key+"'></div><input type='checkbox' class='templateScopeParentCheckboxes' id='"+ key +"'></input>"+ key +"</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
				    		var size = value.length;
				    		var counterCheck = 0;
				    		var counterExist = 0;
				    		for (j=0; j < size; j++){
			    	    		var object = value[j];
			    	    		if(object.exist){
			    	    			counterExist++;
			    	    			html = html + "<tr  style='display:none' class='child_"+key+" existActivity'><td class='padding-left30'>";
			    	    		}else{
			    	    			html = html + "<tr  style='display:none' class='child_"+key+"'><td class='padding-left30'>";
			    	    		}
			    	    		if(object.checked){
			    	    			counterCheck++;
			    	    			html = html + "<input type='checkbox' checked='checked' class='templateScopeCheckboxes "+ key +"' id='"+ object.activityId +"'></input>"+ object.activityId + "</td>";
			    	    		}else{
			    	    			html = html + "<input type='checkbox' class='templateScopeCheckboxes "+ key +"' id='"+ object.activityId +"'></input>"+ object.activityId + "</td>";
			    	    		}
			    	    		html = html + "<td class='leftAlign'>" + object.description + "</td><td class='centerAlign'>" + object.engrOrgProject + "</td><td class='centerAlign'>"+ object.designOrgProject + "</td><td class='centerAlign'>" + object.backOff + "</td><td class='centerAlign'>" + object.engrDuration + "</td><td class='centerAlign'>" + object.designDuration + "</td></tr>";
			    	    	}
				    		if(counterCheck == size){
				    			rootsCheck.push(key);
				    		}
				    		if(counterExist == size){
				    			rootsExist.push(key);
				    		}
				    	});
				    	
				    	html = html + "</table>";
				    	$('.templateBody').append(html);
				    	if(!$.isEmptyObject(rootsCheck)){
				    		for(var i=0;i<rootsCheck.length;i++){
								$("#"+rootsCheck[i]).prop('checked',true);
							}
				    	}
				    	if(!$.isEmptyObject(rootsExist)){
				    		for(var i=0;i<rootsExist.length;i++){
								$("#"+rootsExist[i]).parent().parent().addClass('existRootActivity');
							}
				    	}
				    	
				    	$('.templateScopeParentCheckboxes').click(function(){
							var checked = $(this).prop('checked');
							var id =  $(this).attr('id');
							$("#loadingModal").modal('show');
				    		var checkBoxes = [];
				    		var checkedList = [];
				    		var nonExistantList = [];
				    		$("#designNonExistInTemplateModalHidden").attr('value',"");
							if(checked){
								$(this).parent().parent().addClass('existRootActivity');
								$('.'+id).prop('checked',true);
								$('.'+id).each(function(){
									var activityId =  $(this).attr('id');
									var alreadyExist = $(this).parent().parent().hasClass('existActivity');
									checkBoxes.push(activityId);
									if(alreadyExist){
										checkedList.push(activityId);
									}else{
										nonExistantList.push(activityId);
									}
									$(this).parent().parent().addClass('existActivity');
								});
								$("#designNonExistInTemplateModalHidden").attr('value',nonExistantList);
								if(!$.isEmptyObject(checkedList)){
									addToDesignExistInModalErrorVal(checkBoxes);
									$("#designExistInModalErrorLabel").empty();
									for(var i=0;i<checkedList.length;i++){
										$("#designExistInModalErrorLabel").append(checkedList[i] + " , ");
									}
									$("#designExistInModalErrorLabel").append(" already exists, Please click Yes to update the data.");
									$("#loadingModal").modal('hide');
									$('#designExistInModalError').modal('show');
									return;
								}else{
									addToDesignExistInTemplateModalVal(nonExistantList);
								}
							}else{
								$(this).parent().parent().removeClass('existRootActivity');
								$('.'+id).attr('checked',false);
								$('.'+id).each(function(){
									var activityId =  $(this).attr('id');
									checkBoxes.push(activityId);
									$(this).parent().parent().removeClass('existActivity');
								});
								deleteFromDesignExistInModalErrorVal(checkBoxes);
								deleteFromDesignExistInTemplateModalVal(checkBoxes);
							}
							$.ajax({
								method: "GET",
								contentType:"application/json",
							    dataType: "text json",
							    url: getContextPath()+'/updateTempDesignTemplate?isChecked='+checked+'&toUpdate='+false+'&checkedTemplates='+checkBoxes,
							    success: function(data){
							    	$("#loadingModal").modal('hide');
							    },
					              error: function (error) {
					            	  $('#loadingModal').modal('hide');
					            	  console.log(error);
					              }
							});
						});
				    	
				    	
				    	$('.templateScopeCheckboxes').click(function(){
				    		$("#loadingModal").modal('show');
				    		var checkBoxes = [];
							var checked = $(this).prop('checked');
							var alreadyExist = $(this).parent().parent().hasClass('existActivity');
							var id =  $(this).attr('id');
							checkBoxes.push(id);
							$("#designNonExistInTemplateModalHidden").attr('value',"");
							if(alreadyExist){
								if(checked){
									addToDesignExistInModalErrorVal(checkBoxes);
									$("#designExistInModalErrorLabel").empty();
									$("#designExistInModalErrorLabel").append(id + " already exists, Please click Yes to update the data.");
									$("#loadingModal").modal('hide');
									$('#designExistInModalError').modal('show');
									return;
								}else{
									deleteFromDesignExistInModalErrorVal(checkBoxes);
									deleteFromDesignExistInTemplateModalVal(checkBoxes);
									$(this).parent().parent().removeClass('existActivity');
								}
							}else{
								if(checked){
									addToDesignExistInTemplateModalVal(checkBoxes);
									$(this).parent().parent().addClass('existActivity');
								}else{
									deleteFromDesignExistInTemplateModalVal(checkBoxes);
									$(this).parent().parent().removeClass('existActivity');
								}
							}
							$.ajax({
								method: "GET",
								contentType:"application/json",
							    dataType: "text json",
							    url: getContextPath()+'/updateTempDesignTemplate?isChecked='+checked+'&toUpdate='+false+'&checkedTemplates='+checkBoxes,
							    success: function(data){
							    	$("#loadingModal").modal('hide');
							    },
					              error: function (error) {
					            	  $('#loadingModal').modal('hide');
					            	  console.log(error);
					              }
							});
						});
				    	$('.rootCollapsedIcon').click(function(){
							var id = $(this).attr('id');
							if($(this).hasClass("tree-collapsed")){
								var key = id.substring(5, id.length);
								$('.child_'+key).show();
								$(this).removeClass("tree-collapsed");
								$(this).addClass("tree-expanded");
							}else{
								var key = id.substring(5, id.length);
								$('.child_'+key).css('display','none');
								$(this).removeClass("tree-expanded");
								$(this).addClass("tree-collapsed");
							}
						});
				    	
				    }
				});
			}
		});
		
		$('#designExistInModalErrorYes').click(function(){
			var id = $('#designExistInModalErrorHidden').val();
			var checkBoxes = fetchDesignExistInModalErrorArray();
			var checkBoxesToAdd = fetchDesignNonExistInModal();
			addToDesignExistInTemplateModalVal(checkBoxesToAdd);
			$('#designExistInModalErrorHidden').attr('value',"");
			$('#designNonExistInTemplateModalHidden').attr('value',"");
			$.ajax({
				method: "GET",
				contentType:"application/json",
			    dataType: "text json",
			    url: getContextPath()+'/updateTempDesignTemplate?isChecked='+true+'&toUpdate='+true+'&checkedTemplates='+checkBoxes,
			    success: function(data){
			    	$.ajax({
						method: "GET",
						contentType:"application/json",
					    dataType: "text json",
					    url: getContextPath()+'/updateTempDesignTemplate?isChecked='+true+'&toUpdate='+false+'&checkedTemplates='+checkBoxesToAdd,
					    success: function(data){
					    	$('#designExistInModalError').modal('hide');
					    },
			              error: function (error) {
			            	  $('#designExistInModalError').modal('hide');
			            	  console.log(error);
			              }
					});
			    	$('#designExistInModalError').modal('hide');
			    },
	              error: function (error) {
	            	  $('#designExistInModalError').modal('hide');
	            	  console.log(error);
	              }
			});
		});
		
		$('.designExistInModalErrorClose').click(function(){
			var id = $('#designExistInModalErrorHidden').val();
			var checkBoxes = fetchDesignExistInModalErrorArray();
			var size = checkBoxes.length;
			$.each(checkBoxes, function (index, value) {
				$('#'+value).prop('checked',false);
			});
			if(size > 1){
				$('#'+$('#'+checkBoxes[0]).attr('id').substring(0,2)).prop('checked',false);
			}
			$('#designExistInModalErrorHidden').attr('value',"");
			$('#designNonExistInTemplateModalHidden').attr('value',"");
			$('#designExistInModalError').modal('hide');
		});
		

		
		$("a[href='#content-Main']").on('shown.bs.tab', function (e) {
			 console.log("main");
			  var buildProjectDropDownVal = getProjectVal;
			  $('#projectsDropDown').val(buildProjectDropDownVal).change();
			});
		
		function checkSession(){
			$.ajax({
				type : 'post',
				url : "checkSession",
				success : function(data) {
					if(data == "true"){
						window.location.href= getContextPath()+"/";
					}
				}
			});
		}
		function FormatResult(item) {
	        var markup = "";
	        if (item.name !== undefined) {
	            markup += "<option value='" + item.id + "'>" + item.name + "</option>";
	        }
	        return markup;
	    }

	    function FormatSelection(item) {
	        return item.name;
	    }
		
		function makeArray(a,b) {
	        var arr = new Array(a)
	        for(var i = 0;i<a;i++)
	            arr[i] = new Array(b)
	        return arr
	    }
          function percentRenderer (instance, td, row, col, prop, value, cellProperties) {
            Handsontable.renderers.NumericRenderer.apply(this, arguments);
            td.style.color = (value < 0) ? 'red' : 'green';
          }
         
          function editBuildDetails(clickedRow,index){
        	  $('#loadingModal').modal('show');
        	 var bomLineId = clickedRow.parent().parent().children("td:eq(0)").children().val();
        	 var bomLineDescription = clickedRow.parent().parent().children("td:eq(1)").children().val();
        	 var engrStartDate = clickedRow.parent().parent().children("td:eq(3)").children().val();
        	 
        	 var engrStartDateVal = $('#engrStartDatelabelHiddenInput'+index).val();
        	 var engrRequiredDate = clickedRow.parent().parent().children("td:eq(5)").children().val();
        	 var engrRequiredDateVal =  $("#engrRequiredDatelabelHiddenInput"+index).val();
        	 var designRequiredDate = clickedRow.parent().parent().children("td:eq(7)").children().val();
        	 var designRequiredDateVal = $("#designRequiredDatelabelHiddenInput"+index).val();
        	/* var engrComponentNo = clickedRow.parent().parent().children("td:eq(8)").children().val();
        	 var designComponentNo = clickedRow.parent().parent().children("td:eq(9)").children().val();*/
        	 var engrOrgProject = clickedRow.parent().parent().children("td:eq(8)").children().val();
        	 var designOrgProject = clickedRow.parent().parent().children("td:eq(9)").children().val();
        	 var backOff = clickedRow.parent().parent().children("td:eq(4)").children().val();
        	 var engrDuration = clickedRow.parent().parent().children("td:eq(2)").children().val();
        	 var designDuration = clickedRow.parent().parent().children("td:eq(6)").children().val();
        	 var designReleaseId = clickedRow.parent().parent().children("td:eq(12)").children().val();
        	 var status = clickedRow.parent().parent().children("td:eq(10)").children().val();
        	 var templateName = clickedRow.parent().parent().children("td:eq(11)").children().val();
        	 
        	 var tableLength = $(".designReleaseTable > tbody > tr").length;
        	 var newIndex = tableLength+1;
        	
        	var row = $("<tr>");
     		
     		
     		
    		var descriptionColumn = $('<td>');
    		var descriptionInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].description' value='" + bomLineDescription + "'>" + bomLineDescription +"</input>");
    		descriptionColumn.append(descriptionInput);
    		
    		var engrStartDateColumn = $('<td>');
    		var engrStartDateInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].engrStartDate' value='" + engrStartDate + "'>" + engrStartDateVal +"</input>");
    		engrStartDateColumn.append(engrStartDateInput);
    		
    		var engrRequiredDateColumn = $('<td>');
    		var engrRequiredDateInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].engrRequiredDate' value='" +engrRequiredDate + "'>" + engrRequiredDateVal+"</input>");
    		engrRequiredDateColumn.append(engrRequiredDateInput);
    		
    		var designRequiredDateColumn = $('<td>');
    		var designRequiredDateInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].designRequiredDate' value='" + designRequiredDate + "'>" + designRequiredDateVal +"</input>");
    		designRequiredDateColumn.append(designRequiredDateInput);
    		
    		var engrOrgProjectColumn = $('<td>');
    		var engrOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].engrOrgProject' value='" + engrOrgProject + "'>" + engrOrgProject +"</input>");
    		engrOrgProjectColumn.append(engrOrgProjectInput);
    		
    		var designOrgProjectColumn = $('<td>');
    		var designOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].designOrgProject' value='" +designOrgProject + "'>" + designOrgProject +"</input>");
    		designOrgProjectColumn.append(designOrgProjectInput);
    		
    		var backOffColumn = $('<td>');
    		var backOffInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].backOff' value='" + backOff + "'>" +backOff +"</input>");
    		backOffColumn.append(backOffInput);
    		
    		var engrDurationColumn = $('<td>');
    		var engrDurationInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].engrDuration' value='" + engrDuration + "'>" + engrDuration +"</input>");
    		engrDurationColumn.append(engrDurationInput);
    		
    		var designDurationColumn = $('<td>');
    		var designDurationInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].designDuration' value='" + designDuration + "'>" + designDuration +"</input>");
    		designDurationColumn.append(designDurationInput);
    		
    		var designReleaseIdColumn = $('<td>');
    		var designReleaseIdInput = $("<input type='hidden' id='designReleaseId"+newIndex+"' name='designReleaseList[" + newIndex +"].designReleaseId' value='" + "" + "'>" + +"</input>");
    		designReleaseIdColumn.append(designReleaseIdInput);
    		
    		var statusColumn = $('<td>');
    		var statusInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].status' value='" + "" + "'>" +  +"</input>");
    		statusColumn.append(statusInput);
    		
    		var templateNameColumn = $('<td>');
    		var templateNameInput = $("<input type='hidden' name='designReleaseList[" + newIndex +"].templateName' value='" + "Sub Task" + "'>" + "Sub Task" +"</input>");
    		templateNameColumn.append(templateNameInput);
    		
    		
    		
    		
    		/*var actionColumn = $('<td>');
    		var actionButton = $("<span title='Delete' class='glyphicon glyphicon-trash btn-md redColor cursorPointer deleteDesign' id='" + value.bomLineItemId +"_"+templateName +"'></span>");
    		actionColumn.append(actionButton);*/
    		//row.append(bomLineItemIdColumn);
    		
    		
    		
	    	//$(".designReleaseTable tbody").append(row);
	    	
	    	var bomLineItemListArray = [];
	    	var  bomLineId;
	    	var bomLineItemList = [];
	    	 $('.bomLineHiddenItemId').each(function(){
					var bomLineItem = $(this).val();
					bomLineItemListArray.push(bomLineItem);
	    	 });
	    	 
	    	 var data = {
        			 bomLineId : bomLineId,
        			 bomLineItemList : bomLineItemListArray
        	 }
        	 $.ajax({
  				method: "POST",
  			    data : data,
  			    url: getContextPath()+'/editDREBuild',
  			    success: function(data){
  			    	
  			    	var bomLineItemIdColumn = $('<td>');
  		     		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+newIndex+"' name='designReleaseList[" + newIndex +"].bomLineItemId' value='" + data + "'>"+ data +"</input>");
  		     		bomLineItemIdColumn.append(bomLineItemIdInput);
  		     		
  		     		row.append(bomLineItemIdColumn);
  		     		
  		     		var actionColumn = $('<td>');
  		    		var actionButton = $("<span title='Delete' class='glyphicon glyphicon-trash btn-md redColor cursorPointer deleteDesign' id='" + data +"_"+templateName +"'></span>");
  		    		actionColumn.append(actionButton);
  		    		
  		    			row.append(bomLineItemIdColumn);
	  		     		row.append(descriptionColumn);
	  		    		row.append(engrDurationColumn);
	  		    		row.append(engrStartDateColumn);
	  		    		row.append(backOffColumn);
	  		    		row.append(engrRequiredDateColumn);
	  		    		row.append(designDurationColumn);
	  		    		row.append(designRequiredDateColumn);
	  		    		row.append(engrOrgProjectColumn);
	  		    		row.append(designOrgProjectColumn);
	  		    		
	  		    		row.append(statusColumn);
	  		    		row.append(templateNameColumn);
	  		    		row.append(designReleaseIdColumn);
	  		    		row.append(actionColumn);
	  		     		$(".designReleaseTable tbody").append(row);
  		     		$(".designReleaseTable tbody").append(row);
  			    	$('#loadingModal').modal('hide');
  			    	
  			    },
  	              error: function (error) {
  	            	  //console.log("error"+error);
  	            	if(error.responseText.indexOf(bomLineId) != -1){
  	            		var bomLineItemIdColumn = $('<td>');
  	  		     		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+newIndex+"' name='designReleaseList[" + newIndex +"].bomLineItemId' value='" + error.responseText + "'>"+ error.responseText +"</input>");
  	  		     		bomLineItemIdColumn.append(bomLineItemIdInput);
  	  		     		
	  	  		     	var actionColumn = $('<td>');
	  		    		var actionButton = $("<span title='Delete' class='glyphicon glyphicon-trash btn-md redColor cursorPointer deleteDesign' id='" + error.responseText +"_"+templateName +"'></span>");
	  		    		actionColumn.append(actionButton);
  		    		
  	  		     		row.append(bomLineItemIdColumn);
  	  		     		row.append(descriptionColumn);
  	  		    		row.append(engrDurationColumn);
  	  		    		row.append(engrStartDateColumn);
  	  		    		row.append(backOffColumn);
  	  		    		row.append(engrRequiredDateColumn);
  	  		    		row.append(designDurationColumn);
  	  		    		row.append(designRequiredDateColumn);
  	  		    		/*row.append(engrComponentNoColumn);
  	  		    		row.append(designComponentNoColumn);*/
  	  		    		row.append(engrOrgProjectColumn);
  	  		    		row.append(designOrgProjectColumn);
  	  		    		row.append(statusColumn);
  	  		    		row.append(templateNameColumn);
  	  		    		row.append(designReleaseIdColumn);
  	  		    		row.append(actionColumn);
  	  		     		$(".designReleaseTable tbody").append(row);
  	            	}else{
  	            		$('#designUpdateLabel').html('');
			    		$('#designUpdateLabel').css('color','red');
			    		$('#designUpdateLabel').html("Not created Successfully");
			    		
			    	}
  	            	
  		     		$('#loadingModal').modal('hide');
  	              }
  			});
        	 
          }
         
          function setProjectInfoData(data){
        	  $.each(data, function(key, value){
		    		if(key == 'object_name'){
		    			$("#projectDataProjectName").html(value[0]);
		    		}else if(key == 'get6AppBuildRefDateSecond'){
		    			$("#projectDataK1").html(value[0]);
		    		}else if(key == 'get6AppBuildRefDatePrimary'){
		    			$("#projectDataP1").html(value[0]);
		    			$("#projectP1DateHidden").attr('value',value[0]);
		    		}else if(key == 'get6OrderNumber'){
		    			$("#projectDataOrderNo").html(value[0]);
		    		}else if(key == 'get6CustomerName'){
		    			$("#projectDataCustomerName").html(value[0]);
		    		}else if(key == 'get6PrimaryProjectNumber'){
		    			$("#projectDataPrimaryNo").html(value[0]);
		    		}else if(key == 'get6SalesForceID'){
		    			$("#projectDataSalesForceId").html(value[0]);
		    		}else if(key == 'get6SecondaryProjectNumber'){
		    			$("#projectDataSecondaryNo").html(value[0]);
		    		}else if(key == 'get6EngrProdLine'){
		    			$("#engrProductLine").html(value[0]);
		    		}
		    	});
          }
          
          $('.search-btn').click(function(){
  			var filterValue = $("#buildSearchTerm").val();
  			
  			$(".designReleaseTable tr").each(function(rowId, row) 
  					{ 
  					var isContentPresent = false;
  					if($(this).css('display') != 'none'){ 
  						 
  					 // if(rowId > 1){
  						  var bomLine = $(this).find('td').eq(1).text();
  							if(bomLine != null && bomLine != " " && bomLine != "" && bomLine != undefined){
  								for(var i=0;i<13;i++){
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
  					  //}
  					}
  						if(isContentPresent || filterValue == "" || filterValue == " " || filterValue == undefined){
  							$(this).show();
  						}
  						
  						
  					});
  			fixedHeaderScroll();
  			
  		});
          function fixedHeaderScroll(){
        	//Fixed header scroll.
  			
  			var table = $('#designReleaseBuild').DataTable( {
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
  	    	$('#designReleaseBuild').resize();
  	    	table.fixedHeader.adjust();
  	    	//$(table).dataTable().fnAdjustColumnSizing();
          }
});

