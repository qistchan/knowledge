function autoClose(obj, index) {
			if(obj.checked)
			{
				//console.log("checked");
				$("#designautoClose"+index).val('true');
			}
			else
			{
				//console.log("un checked");
				$("#designautoClose"+index).val('false');
			}
		}

$(document).ready(function() {	
	
	
		$('#projectsDropDownEdit').selectpicker();
		$('#templatesDropDownEdit').selectpicker();
		$('#scopesDropDownEdit').selectpicker();
		
		$('.dreEditFilterClass').selectpicker();
		window.getProjectVal = $("#projectsDropDown").val();
		getMainGroupOnload();
		//getProjectListOnload();
		//dao.getSubgroup();
		/*$(document).tooltip();*/
		/*$(".designReleaseEditTable").stickyTableHeaders({ scrollableArea: $(".scrollable-area")[0], "fixedOffset": 2 });*/
		
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
			for(var i=0;i<21;i++){
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
    		
    		
    		//onclick=\"edittablecheckboxes("+index+")\"
    		var st="";
    		var status = value.status;
    		if(status.includes( "EDOT Close"))
    		{
    		     st = "disabled";
    		}
    		var checkBoxColumn = $('<td>');
    		var checkBoxInput = $("<input type='checkbox' class='editMainTableCheckboxes' name='designReleaseList[" + index +"].editChecked' id='check_"+value.bomLineItemId+"' data-edot= '"+value.designReleaseId+"' data-status='"+value.status+"' data-index ='"+index+"'   "+st+"  />" );
    		var bomlndescriptionHiddenInput = $("<input type='hidden' id='bomlndescriptionHiddenInput"+index+"' value='"+value.description+"'/>");
    		var engrDurationHiddenInput = $("<input type='hidden' id='engrDurationHiddenInput"+index+"' value='"+value.engrDuration+"'/>");
    		var backOffHiddenInput = $("<input type='hidden' id='backOffHiddenInput"+index+"' value='"+value.backOff+"'/>");
    		var designDurationHiddenInput = $("<input type='hidden' id='designDurationHiddenInput"+index+"' value='"+value.designDuration +"'/>");
    		var engrStartDateHiddenInput = $("<input type='hidden' id='engrStartDateHiddenInput"+index+"' value='"+value.engrStartDateLabel+"'/>");
    		var engrRequiredDateHiddenInput = $("<input type='hidden' id='engrRequiredDateHiddenInput"+index+"' value='"+value.engrRequiredDateLabel+"'/>");
    		var designRequiredDateHiddenInput = $("<input type='hidden' id='designRequiredDateHiddenInput"+index+"' value='"+value.designRequiredDateLabel +"'/>");
    		
    		var eng_datechangeHiddenInput = $("<input type='hidden' id='eng_datechangeHiddenInput"+index+"' value='"+value.engrDateChangeReason+"'/>");
		/*	var eng_subgroupHiddenInput = $("<input type='hidden' id='eng_subgroupHiddenInput"+index+"' value='"+value.engrComponentNo+"'/>");*/
			
			var mainGroupHiddenInput = $("<input type='hidden' id='mainGroupHiddenInput"+index+"' value='"+value.mainGroup+"'/>");
			//console.log("Eng Subgroup Value"+ eng_subgroupHiddenInput);
			var eng_resourceHiddenInput = $("<input type='hidden' id='eng_resourceHiddenInput"+index+"' value='"+value.engrResource+"'/>");
			var eng_commentHiddenInput = $("<input type='hidden' id='eng_commentHiddenInput"+index+"' value='"+value.engrComment+"'/>");
			var design_datechangeHiddenInput = $("<input type='hidden' id='design_datechangeHiddenInput"+index+"' value='"+value.designDateChangeReason+"'/>");
			/*var design_subgroupHiddenInput = $("<input type='hidden' id='design_subgroupHiddenInput"+index+"' value='"+value.designComponentNo+"'/>");*/
			var design_resourceHiddenInput = $("<input type='hidden' id='design_resourceHiddenInput"+index+"' value='"+value.designResource+"'/>");
			var design_commentHiddenInput = $("<input type='hidden' id='design_commentHiddenInput"+index+"' value='"+value.designComment+"'/>");
			var autocloseHiddenInput = $("<input type='hidden' id='autocloseHiddenInput"+index+"' value='"+value.autoClose+"'/>");
			var StatusHiddenInput = $("<input type='hidden' id='StatusHiddenInput"+index+"' value='"+value.status+"'/>");
			var eng_orgProjectHiddenInput = $("<input type='hidden' id='eng_orgProjectHiddenInput"+index+"' value='"+value.engrOrgProject+"'/>");
			var design_orgProjectHiddenInput = $("<input type='hidden' id='design_orgProjectHiddenInput"+index+"' value='"+value.designOrgProject+"'/>");
    		
    		checkBoxColumn.append(checkBoxInput);
    		checkBoxColumn.append(bomlndescriptionHiddenInput);
    		checkBoxColumn.append(engrDurationHiddenInput);
    		checkBoxColumn.append(backOffHiddenInput);
    		checkBoxColumn.append(designDurationHiddenInput);
    		checkBoxColumn.append(engrStartDateHiddenInput);
    		checkBoxColumn.append(engrRequiredDateHiddenInput);
    		checkBoxColumn.append(designRequiredDateHiddenInput);
    		
    		checkBoxColumn.append(eng_datechangeHiddenInput);
    		/*checkBoxColumn.append(eng_subgroupHiddenInput);*/
    		checkBoxColumn.append(mainGroupHiddenInput);
    		checkBoxColumn.append(eng_resourceHiddenInput);
    		checkBoxColumn.append(eng_commentHiddenInput);
    		checkBoxColumn.append(design_datechangeHiddenInput);
    		/*checkBoxColumn.append(design_subgroupHiddenInput);*/
    		checkBoxColumn.append(design_resourceHiddenInput);
    		checkBoxColumn.append(design_commentHiddenInput);
    		checkBoxColumn.append(autocloseHiddenInput);
    		checkBoxColumn.append(StatusHiddenInput);
    		checkBoxColumn.append(eng_orgProjectHiddenInput);
    		checkBoxColumn.append(design_orgProjectHiddenInput);
    		/*checkBoxColumn.css('width','2%');
    		checkBoxColumn.css('padding-top','0px');
    		checkBoxColumn.css('padding-bottom','0px');
    		checkBoxColumn.css('padding-left','0px');
    		checkBoxColumn.css('padding-right','0px');*/
    		
    		var edotColumn = $('<td>');
    		var edotInput = $("<input type='hidden' class='edotHiddenId' id='edotId"+index+"' name='designReleaseList[" + index +"].edot' value='" + value.designReleaseId + "'>"+ value.designReleaseId +"</input>");
    		edotColumn.append(edotInput);
    		/*edotColumn.css('width','4%');
    		edotColumn.css('padding-top','0px');
    		edotColumn.css('padding-bottom','0px');
    		edotColumn.css('padding-left','0px');
    		edotColumn.css('padding-right','0px');*/
    		
    		var statusColumn = $('<td>');
    		var statusInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + value.status + "'>" + value.status +"</input>");
    		statusColumn.append(statusInput);
    		/*statusColumn.css('width','5%');
    		statusColumn.css('padding-top','0px');
    		statusColumn.css('padding-bottom','0px');
    		statusColumn.css('padding-left','0px');
    		statusColumn.css('padding-right','0px');
    		*/
    		var bomLineItemIdColumn = $('<td>');
    		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+index+"' name='designReleaseList[" + index +"].bomLineItemId' value='" + value.bomLineItemId + "'>"+ value.bomLineItemId +"</input>");
    		bomLineItemIdColumn.append(bomLineItemIdInput);
    		/*bomLineItemIdColumn.css('width','5%');
    		bomLineItemIdColumn.css('padding-top','0px');
    		bomLineItemIdColumn.css('padding-bottom','0px');
    		bomLineItemIdColumn.css('padding-left','0px');
    		bomLineItemIdColumn.css('padding-right','0px');*/
    		
    		var descriptionColumn = $('<td>',{"style" : "text-align:left"});
    		var descriptionInput = $("<input type='hidden' class='description' id='description"+index+"' name='designReleaseList[" + index +"].description' value='" + value.description + "'>" + value.description +"</input>");
    		descriptionColumn.append(descriptionInput);
    		/*descriptionColumn.css('width','7%');
    		descriptionColumn.css('padding-top','0px');
    		descriptionColumn.css('padding-bottom','0px');
    		descriptionColumn.css('padding-left','0px');
    		descriptionColumn.css('padding-right','0px');*/
    		
    		var engrDurationColumn = $('<td>');
    		var engrDurationInput = $("<input type='hidden' class='engrDurationInput' id=engrDuration_"+index+" name='designReleaseList[" + index +"].engrDuration' value='" + value.engrDuration + "'>" + value.engrDuration +"</input>");
    		engrDurationColumn.append(engrDurationInput);
    		/*engrDurationColumn.css('width','3%');
    		engrDurationColumn.css('padding-top','0px');
    		engrDurationColumn.css('padding-bottom','0px');
    		engrDurationColumn.css('padding-left','0px');
    		engrDurationColumn.css('padding-right','0px');*/
    		
    		var engrStartDateColumn = $("<td id=engrStartDateTD_"+index+">");
    		var engrStartDateInput = $("<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + value.engrStartDate + "'>" + value.engrStartDateLabel +"</input>");
    		engrStartDateColumn.append(engrStartDateInput);
    	/*	engrStartDateColumn.css('width','5%');
    		engrStartDateColumn.css('padding-top','0px');
    		engrStartDateColumn.css('padding-bottom','0px');
    		engrStartDateColumn.css('padding-left','0px');
    		engrStartDateColumn.css('padding-right','0px');*/
    		
    		
    		var backOffColumn = $('<td>');
    		var backOffInput = $("<input type='hidden' class='backOffInput' id=backOff_"+index+" name='designReleaseList[" + index +"].backOff' value='" + value.backOff + "'>" + value.backOff +"</input>");
    		backOffColumn.append(backOffInput);
    		/*backOffColumn.css('width','3%');
    		backOffColumn.css('padding-top','0px');
    		backOffColumn.css('padding-bottom','0px');
    		backOffColumn.css('padding-left','0px');
    		backOffColumn.css('padding-right','0px');*/
    		
    		var engrRequiredDateColumn = $("<td id=engrRequiredDateTD_"+index+">");
    		var engrRequiredDateInput = $("<input type='hidden' class='engrRequiredDateInput' id=engrRequiredDate_"+index+" name='designReleaseList[" + index +"].engrRequiredDate' value='" + value.engrRequiredDate + "'>" + value.engrRequiredDateLabel +"</input>");
    		engrRequiredDateColumn.append(engrRequiredDateInput);
    		/*engrRequiredDateColumn.css('width','5%');
    		engrRequiredDateColumn.css('padding-top','0px');
    		engrRequiredDateColumn.css('padding-bottom','0px');
    		engrRequiredDateColumn.css('padding-left','0px');
    		engrRequiredDateColumn.css('padding-right','0px');*/
    		
    		var engrPromiseDateColumn = $('<td>');
    		var engrPromiseDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrPromiseDate' value='" + value.engrPromiseDate + "'>" + value.engrPromiseDateLabel +"</input>");
    		engrPromiseDateColumn.append(engrPromiseDateInput);
    		/*engrPromiseDateColumn.css('padding-top','0px');
    		engrPromiseDateColumn.css('padding-bottom','0px');
    		engrPromiseDateColumn.css('padding-left','0px');
    		engrPromiseDateColumn.css('padding-right','0px');*/
    		
    		var engrActualDateColumn = $('<td>');
    		var engrActualDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrActualDate' value='" + value.engrActualDate + "'>" + value.engrActualDateLabel +"</input>");
    		engrActualDateColumn.append(engrActualDateInput);
    		
    		var engrDateChangeReasonColumn = $('<td>');
    		var engrDateChangeReasonInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrDateChangeReason' value='" + value.engrDateChangeReason + "'>" + value.engrDateChangeReason +"</input>");
    		engrDateChangeReasonColumn.append(engrDateChangeReasonInput);
    		/*engrDateChangeReasonColumn.css('width','2%');
    		engrDateChangeReasonColumn.css('padding-top','0px');
    		engrDateChangeReasonColumn.css('padding-bottom','0px');
    		engrDateChangeReasonColumn.css('padding-left','0px');
    		engrDateChangeReasonColumn.css('padding-right','0px');*/
    		
    		var engrComponentNoColumn = $('<td>',{"style" : "text-align:left"});
    		var engrComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrComponentNo' value='" + value.engrComponentNo + "'>" + value.engrComponentNo +"</input>");
    		engrComponentNoColumn.append(engrComponentNoInput);
    		/*engrComponentNoColumn.css('width','5%');
    		engrComponentNoColumn.css('padding-top','0px');
    		engrComponentNoColumn.css('padding-bottom','0px');
    		engrComponentNoColumn.css('padding-left','0px');
    		engrComponentNoColumn.css('padding-right','0px');*/
    		
    		var engrResourceColumn = $('<td id=engresource_'+index+'>');
    		var engrResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrResource' class='resourceSelectOptionClass' value='" + value.engrResource + "'>" + value.engrResource +"</input>");
    		//var engresourcediv = $("<div id='engresource[" + index +"]'>");
    		engrResourceColumn.append(engrResourceInput);
    		//engrResourceColumn.attr('class','setResourceWidth');
    		//engrResourceColumn.addClass('setResourceWidth');
    		//engrResourceColumn.append(engresourcediv);
    		/*engrResourceColumn.css('width','5%');
    		engrResourceColumn.css('padding-top','0px');
    		engrResourceColumn.css('padding-bottom','0px');
    		engrResourceColumn.css('padding-left','0px');
    		engrResourceColumn.css('padding-right','0px');*/
    		
    		var engrECRColumn = $('<td>');
    		var engrECRInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrECR' value='" + value.engrECR + "'>" + value.engrECR +"</input>");
    		engrECRColumn.append(engrECRInput);
    		
    		var engrCommentColumn = $('<td>');
    		var engrCommentInput = $("<textarea rows='2' cols='30' style='display:none' name='designReleaseList[" + index +"].engrComment' id=engComments_"+index+">" + value.engrComment +"</textarea><span id=engrcmnt"+index+" class='cmntWrapper' >"+value.engrComment+"</span>");
    		engrCommentColumn.append(engrCommentInput);
    		/*engrCommentColumn.css('width','10%');
    		engrCommentColumn.css('padding-top','0px');
    		engrCommentColumn.css('padding-bottom','0px');
    		engrCommentColumn.css('padding-left','0px');
    		engrCommentColumn.css('padding-right','0px');*/
    		
    		var designDurationColumn = $('<td>');
    		var designDurationInput = $("<input type='hidden' class='designDurationInput' id=designDuration_"+index+" name='designReleaseList[" + index +"].designDuration' value='" + value.designDuration + "'>" + value.designDuration +"</input>");
    		designDurationColumn.append(designDurationInput);
    		/*designDurationColumn.css('width','2%');
    		designDurationColumn.css('padding-top','0px');
    		designDurationColumn.css('padding-bottom','0px');
    		designDurationColumn.css('padding-left','0px');
    		designDurationColumn.css('padding-right','0px');*/
    		
    		var designRequiredDateColumn = $("<td  id=designRequiredDateTD_"+index+">");
    		var designRequiredDateInput = $("<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + value.designRequiredDate + "'>" + value.designRequiredDateLabel +"</input>");
    		designRequiredDateColumn.append(designRequiredDateInput);
    		/*designRequiredDateColumn.css('width','5%');
    		designRequiredDateColumn.css('padding-top','0px');
    		designRequiredDateColumn.css('padding-bottom','0px');
    		designRequiredDateColumn.css('padding-left','0px');
    		designRequiredDateColumn.css('padding-right','0px');*/
    		
    		var designPromiseDateColumn = $('<td>');
    		var designPromiseDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].designPromiseDate' value='" + value.designPromiseDate + "'>" + value.designPromiseDateLabel +"</input>");
    		designPromiseDateColumn.append(designPromiseDateInput);
    		
    		
    		var designActualDateColumn = $('<td>');
    		var designActualDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].designActualDate' value='" + value.designActualDate + "'>" + value.designActualDateLabel +"</input>");
    		designActualDateColumn.append(designActualDateInput);
    		
    		var designDateChangeReasonColumn = $('<td>');
    		var designDateChangeReasonInput = $("<input type='hidden' name='designReleaseList[" + index +"].designDateChangeReason' value='" + value.designDateChangeReason + "'>" + value.designDateChangeReason +"</input>");
    		designDateChangeReasonColumn.append(designDateChangeReasonInput);
    		/*designDateChangeReasonColumn.css('width','2%');
    		designDateChangeReasonColumn.css('padding-top','0px');
    		designDateChangeReasonColumn.css('padding-bottom','0px');
    		designDateChangeReasonColumn.css('padding-left','0px');
    		designDateChangeReasonColumn.css('padding-right','0px');*/
    		
    		var designComponentNoColumn = $('<td>',{"style" : "text-align:left"});
    		var designComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].designComponentNo' value='" + value.designComponentNo + "'>" + value.designComponentNo +"</input>");
    		designComponentNoColumn.append(designComponentNoInput);
    		/*designComponentNoColumn.css('width','10%');
    		designComponentNoColumn.css('padding-top','0px');
    		designComponentNoColumn.css('padding-bottom','0px');
    		designComponentNoColumn.css('padding-left','0px');
    		designComponentNoColumn.css('padding-right','0px');*/
    		
    		var designResourceColumn = $('<td id=designresource_'+index+'>');
    		var designResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].designResource' class='resourceSelectOptionClass' value='" + value.designResource + "'>" + value.designResource +"</input>");
    		designResourceColumn.append(designResourceInput);
    		/*designResourceColumn.css('width','6%');
    		designResourceColumn.css('width','10%');
    		designResourceColumn.css('padding-top','0px');
    		designResourceColumn.css('padding-bottom','0px');
    		designResourceColumn.css('padding-left','0px');
    		designResourceColumn.css('padding-right','0px');*/
    		
    		var designECNColumn = $('<td>');
    		var designECNInput = $("<input type='hidden' name='designReleaseList[" + index +"].designECN' value='" + value.designECN + "'>" + value.designECN +"</input>");
    		designECNColumn.append(designECNInput);
    		
    		var designCommentColumn = $('<td>');
    		var designCommentInput = $("<textarea rows='2' cols='30' style='display:none' name='designReleaseList[" + index +"].designComment' id=dsgnComments_"+index+" >" + value.designComment +"</textarea><span id=dsgncmnt"+index+" class='cmntWrapper'>"+value.designComment+"</span>");
    		designCommentColumn.append(designCommentInput);
    		/*designCommentColumn.css("width","10%");
    		designCommentColumn.css('padding-top','0px');
    		designCommentColumn.css('padding-bottom','0px');
    		designCommentColumn.css('padding-left','0px');
    		designCommentColumn.css('padding-right','0px');*/
    		
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
    		
    		var engrOrgProjectColumn = $('<td id=engrOrgProject_'+index+'>');
    		var engrOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrOrgProject'  value='" + value.engrOrgProject+ "'>" + value.engrOrgProject +"</input>");
    		engrOrgProjectColumn.append(engrOrgProjectInput);
    		
    		var designOrgProjectColumn = $('<td id=designOrgProject_'+index+'>');
    		var designOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].designOrgProject' value='" + value.designOrgProject + "'>" + value.designOrgProject +"</input>");
    		designOrgProjectColumn.append(designOrgProjectInput);
    		
    		var mainGroupColumn = $('<td id=mainGrp_'+index+'>',{"style" : "text-align:left"});
    		var mainGroupInput = $("<input type='hidden' name='designReleaseList[" + index +"].mainGroup'  value='" + value.mainGroup + "'>" + value.mainGroup +"</input>");
    		mainGroupColumn.append(mainGroupInput);
    		
    		checkBoxColumn.append(designReleaseIdInput);
    		row.append(checkBoxColumn);
    		row.append(bomLineItemIdColumn);
    		row.append(descriptionColumn);
    		row.append(edotColumn);
    		row.append(mainGroupColumn);
    		//row.append(statusColumn);
    		row.append(engrDurationColumn);
    		row.append(engrStartDateColumn);
    		row.append(backOffColumn);
    		row.append(engrRequiredDateColumn);
    		//row.append(engrPromiseDateColumn);
    		//row.append(engrActualDateColumn);
    		row.append(engrDateChangeReasonColumn);
    		/*row.append(engrComponentNoColumn);*/
    		row.append(engrOrgProjectColumn);
    		row.append(engrResourceColumn);
    		//row.append(engrECRColumn);
    		row.append(engrCommentColumn);
    		row.append(designDurationColumn);
    		row.append(designRequiredDateColumn);
    		//row.append(designPromiseDateColumn);
    		//row.append(designActualDateColumn);
    		row.append(designDateChangeReasonColumn);
    		/*row.append(designComponentNoColumn);*/
    		row.append(designOrgProjectColumn);
    		row.append(designResourceColumn);
    		//row.append(designECNColumn);
    		row.append(designCommentColumn);
    		row.append(autoCloseColumn);
    		row.append(statusColumn);
    		//row.append(templateNameColumn);
    		
    		return row;
		}
		
		
		
		//$(".autoclosecheckbox").click(autoClose);
		$('.search-btn').click(function(){
			var filterValue = $("#srchTerm").val();
			
			$(".designReleaseEditTable tr").each(function(rowId, row) 
					{ 
					var isContentPresent = false;
					if($(this).css('display') != 'none'){ 
						 
					 
						  var bomLine = $(this).find('td').eq(1).text();
							if(bomLine != null && bomLine != " " && bomLine != "" && bomLine != undefined){
								for(var i=1;i<21;i++){
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
		
		$('.projectInfoEditBtn').click(function(){
			$("#project_edit_id").html($("#projectsDropDownEdit").val());
			$('#projectInfoEdit').modal('show');
		});
		$('.projectRefresh').click(function(){
			$('#projectsDropDownEdit').change();
		});
		$('.dreEditFilterClass').change(function(){
			var filterValue = $("#dreEditFilterData").val();
			$("#srchTerm").val("");
			$(".designReleaseEditTable tr").each(function() 
			{ 
				var status = $(this).find('td').eq(20).text();
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
		
		$('#projectsDropDownEdit').change(function(){
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
		    	$("#engrEditProductLine").html('');
		    	$(".projectInfoEditBtn").hide();
		    	$(".projectRefresh").hide();
		    	$(".filterDataClass").hide();
		    	$(".designReleaseEditTable tbody").empty();
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
			    	getProjectVal = projectValue;
			    	$(".projectInfoEditBtn").show();
			    	$(".projectRefresh").show();
			    	/*$('.dreEditFilterClass').removeAttr('disabled');
			    	$(".dreEditFilterClass").selectpicker('refresh');*/
			    	var sVal = $('select[name=dreEditFilterData] option:first').val();
					$('select[name=dreEditFilterData]').val(sVal);
					$(".dreEditFilterClass").selectpicker('refresh');
					$(".filterDataClass").show();
					$("#srchTerm").val("");
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
							    	$(".designReleaseEditTable tbody").append(row);
							    	resetScopeDropdown();
						    	});
					    	}else{
					    		$(".designReleaseEditTable tbody").empty();
						    	for(var i=0 ; i<12 ;i++){
						    		var row = createDesignReleaseEditEmptyTableRow(i);
							    	$(".designReleaseEditTable tbody").append(row);
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
					    	$("#engrEditProductLine").html('');
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
					    			$("#engrEditProductLine").html(value[0]);
					    		}
					    	});
					    	$(document).on('blur',"input.backOffInput", function() {
							    var id = $(this).attr('id');
							    var indexList = id.split('_');
							    var index = indexList[1];
							    var engrDurationInputVal = $("#engrDuration_"+index).val();
							    var backoffVal = $("#backOff_"+index).val();
							    
							    var designDurationInputVal = $("#designDuration_"+index).val();
							    //Testing
							   if(backoffVal != "" && backoffVal != undefined){
								   var data = {
								    		engrDuration : engrDurationInputVal,
								    		backOffInput : backoffVal,
								    		designDurationInput : designDurationInputVal
								    };
								    $.ajax({
										method: "POST",
									    url: getContextPath()+'/getBackOffChangeDetails',
									    data : data,
									    success: function(data){
									    	var designRelease =data;
									    	
									    	 $("#engrStartDateTD_"+index).empty();
											    $("#engrRequiredDateTD_"+index).empty();
											    $("#designRequiredDateTD_"+index).empty();
									    	
									    	 var engrRequiredDateHTML = "<input type='hidden' class='engrRequiredDateInput' id=engrRequiredDate_"+index+" name='designReleaseList[" + index +"].engrRequiredDate' value='" +designRelease.engrRequiredDate  + "'>" + designRelease.engrRequiredDateLabel +"</input>";
											 var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + designRelease.designRequiredDate + "'>" + designRelease.designRequiredDateLabel +"</input>";
											 $("#engrRequiredDateTD_"+index).append(engrRequiredDateHTML);
									    	 $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
											    /*if( $("#mainGroupHiddenInput"+index).val() != "NWR" )
									    		{
											    	 $("#engrRequiredDateTD_"+index).append(engrRequiredDateHTML);
											    	 $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
											       
									    		}*/
											    /*if( $("#design_subgroupHiddenInput"+index).val() != "NWR" )
											    {
											        $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
											        
											    }*/
											    if(engrDurationInputVal != 0){
										    		var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" +designRelease.engrStartDate  + "'>" + designRelease.engrStartDateLabel +"</input>";
										    		/*if( $("#eng_subgroupHiddenInput"+index).val() != "NWR" )*/
										    		$("#engrStartDateTD_"+index).append(engrStartDateHTML);
										    		/*if( $("#mainGroupHiddenInput"+index).val() != "NWR" )
										    		{
										    			$("#engrStartDateTD_"+index).append(engrStartDateHTML);
										    		}*/
										    	}
									    },
									    error : function(error)
									    {
									    	 
									    }
									    
									});
							   }
							    
							    
							    //Testing
							   /* engrDurationInputVal = -Math.abs(engrDurationInputVal.substring(0,engrDurationInputVal.length));
							    designDurationInputVal = -Math.abs(designDurationInputVal.substring(0,designDurationInputVal.length-1));
							    var weeks = -Math.abs($(this).val());
							    var projectP1Date = $("#projectP1DateEditHidden").val();
							    var engrStartDate = moment(projectP1Date, 'DD-MMM-YYYY');
							    var engrRequiredDate = moment(projectP1Date, 'DD-MMM-YYYY');
							    var designRequiredDate = moment(projectP1Date, 'DD-MMM-YYYY');
							    var startOfEngrStartDate = moment("01-Jan-"+engrStartDate.year(), 'DD-MMM-YYYY');
							    var startOfEngrRequiredDate = moment("01-Jan-"+engrRequiredDate.year(), 'DD-MMM-YYYY');
							    var startOfDesignRequiredDate = moment("01-Jan-"+designRequiredDate.year(), 'DD-MMM-YYYY');
							    engrStartDate.add((weeks+engrDurationInputVal),'weeks');
							    engrRequiredDate.add(weeks,'weeks' );
							    designRequiredDate.add((weeks-designDurationInputVal),'weeks');
							    var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + engrStartDate.format('MM/DD/YYYY') + "'>" + engrStartDate.format('MM/DD/YYYY') +" (W"+ moment(engrStartDate.format('MM/DD/YYYY')).diff(moment(startOfEngrStartDate), 'weeks') +")" +"</input>";
							    var engrRequiredDateHTML = "<input type='hidden' class='engrRequiredDateInput' id=engrRequiredDate_"+index+" name='designReleaseList[" + index +"].engrRequiredDate' value='" + engrRequiredDate.format('MM/DD/YYYY') + "'>" + engrRequiredDate.format('MM/DD/YYYY') +" (W"+ moment(engrRequiredDate.format('MM/DD/YYYY')).diff(moment(startOfEngrRequiredDate), 'weeks') +")" +"</input>";
							    var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + designRequiredDate.format('MM/DD/YYYY') + "'>" + designRequiredDate.format('MM/DD/YYYY') +" (W"+ moment(designRequiredDate.format('MM/DD/YYYY')).diff(moment(startOfDesignRequiredDate), 'weeks') +")" +"</input>";
							    $("#engrStartDateTD_"+index).empty();
							    $("#engrRequiredDateTD_"+index).empty();
							    $("#designRequiredDateTD_"+index).empty();
							    if( $("#eng_subgroupHiddenInput"+index).val() != "NWR" )
					    		{
							        $("#engrStartDateTD_"+index).append(engrStartDateHTML);
							        $("#engrRequiredDateTD_"+index).append(engrRequiredDateHTML);
							        var engrstartValHid = engrStartDate.format('MM/DD/YYYY') +" (W"+ moment(engrStartDate.format('MM/DD/YYYY')).diff(moment(startOfEngrStartDate), 'weeks') +")";
							        var engrendValHid = engrRequiredDate.format('MM/DD/YYYY') +" (W"+ moment(engrRequiredDate.format('MM/DD/YYYY')).diff(moment(startOfEngrRequiredDate), 'weeks') +")" ;
							        $('#engrStartDateHiddenInput'+index).val(engrstartValHid);
							        $('#engrRequiredDateHiddenInput'+index).val(engrendValHid);

					    		}
							    if( $("#design_subgroupHiddenInput"+index).val() != "NWR" )
							    {
							        $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
							        //$("#designRequiredDateHiddenInput"+index).val(designRequiredDate.format('MM/DD/YYYY'));
							    }*/
							});
					    	
					    	$(document).on('blur',"input.engrDurationInput", function() {
					    		/*if( $("#eng_subgroupHiddenInput"+index).val() != "NWR" )*/
					    		//if( $("#mainGroupHiddenInput"+index).val() != "NWR" )
					    		//{
							    var id = $(this).attr('id');
							    var indexList = id.split('_');
							    var index = indexList[1];
							    var engrDurationValue =$("#engrDuration_"+index).val();
							    var backOffInputVal = $("#backOff_"+index).val();
							    
							    if(engrDurationValue == "")
						    	{
							    	$("#engrStartDateTD_"+index).empty();
							    	var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value=''></input>";
							    	$("#engrStartDateTD_"+index).append(engrStartDateHTML);
						    	}
							    //Testing
							    if(engrDurationValue != "" && engrDurationValue != undefined){
							    	//console.log(engrDurationValue);
							    	var data = {
								    		engrDuration : engrDurationValue,
								    		backOffInput : backOffInputVal
								    };
								    $("#engrStartDateTD_"+index).empty();
								    if(engrDurationValue != 0){
							    		 $.ajax({
												method: "POST",
											    url: getContextPath()+'/getStartDate',
											    data : data,
											    success: function(data){
											    	var designRelease =data;
											    	$("#engrStartDateTD_"+index).empty();
											    	var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + designRelease.engrStartDate + "'>" + designRelease.engrStartDateLabel +"</input>";
											    	$("#engrStartDateTD_"+index).append(engrStartDateHTML);
											    	 
											    },
											    error : function(error)
											    {
											    	/* $('#loadingModal').modal('hide');
												    	
												    	var designRelease = error.responseText;
												    	
												    	 var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + designRelease.engrStartDate + "'>" + designRelease.engrStartDateLabel +"</input>";
												    	 $("#engrStartDateTD_"+index).append(engrStartDateHTML);*/
											    }
											    
											});
								    }
							    }
							    /*else{
							    	var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + "" + "'>" + +"</input>";
							    	 $("#engrStartDateTD_"+index).append(engrStartDateHTML);
							    }*/
							    
							   //Testing
							    /*backOffInputVal = -Math.abs(backOffInputVal.substring(0,backOffInputVal.length));
							    var weeks = -Math.abs($(this).val());
							    var projectP1Date = $("#projectP1DateEditHidden").val();
							    var engrStartDate = moment(projectP1Date, 'DD-MMM-YYYY');
							    var startOfEngrStartDate = moment("01-Jan-"+engrStartDate.year(), 'DD-MMM-YYYY');
							    engrStartDate.add((weeks+backOffInputVal),'weeks');
							    var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + engrStartDate.format('MM/DD/YYYY') + "'>" + engrStartDate.format('MM/DD/YYYY') +" (W"+ moment(engrStartDate.format('MM/DD/YYYY')).diff(moment(startOfEngrStartDate), 'weeks') +")" +"</input>";
							    $("#engrStartDateTD_"+index).empty();
							    if(engrDurationValue != 0){
							    	 $("#engrStartDateTD_"+index).append(engrStartDateHTML);
							    }*/
							   
					    		//}
							});
					    	
					    	$(document).on('keyup',"input.backOffInput", function() {
					    	    var val = $(this).val()
					    	    var reg = /^0/gi;
					    	    if (val.match(reg)) {
					    	        $(this).val(val.replace(reg, ''));
					    	    }
					    	    else
				    	    	{
					    	    	 $(this).val($.trim(val));
				    	    	}
					    	});
					    	
					    	$(document).on('blur',"input.designDurationInput", function() {
					    		if( $("#design_subgroupHiddenInput"+index).val() != "NWR" )
					    		{
							    var id = $(this).attr('id');
							    var indexList = id.split('_');
							    var index = indexList[1];
							    var backOffInputVal = $("#backOff_"+index).val();
							    var designDurationValue = $("#designDuration_"+index).val();
							    //Testing
							    if(designDurationValue == "")
						    	{
							    	$("#designRequiredDateTD_"+index).empty();
							    	var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' ></input>";
							    	$("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
							    	
						    	}
							    
							    if(designDurationValue != "" && designDurationValue != undefined){
							    	 var data = {
									    		designDuration : designDurationValue,
									    		backOffInput : backOffInputVal
									    };
							    	   $("#designRequiredDateTD_"+index).empty();	
							    	   if(designDurationValue != 0)
							    	   {
										    $.ajax({
												method: "POST",
											    url: getContextPath()+'/getDesignRequiredDate',
											    data : data,
											    success: function(data){
											    	var designRelease =data;
											    	$("#designRequiredDateTD_"+index).empty();	
											    	 var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + designRelease.designRequiredDate+ "'>" + designRelease.designRequiredDateLabel +"</input>";
											    	 $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
											    },
											    error : function(error)
											    {
											    	 $('#loadingModal').modal('hide');
												    	
												    	var designRelease = error.responseText;
												    	
												    	var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + designRelease.designRequiredDate+ "'>" + designRelease.designRequiredDateLabel +"</input>";
												    	 $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
											    }
											    
											});
							    	   }
							    }
							   
							    
							    //Testing
							   /* backOffInputVal = -Math.abs(backOffInputVal.substring(0,backOffInputVal.length));
							    var weeks = -Math.abs($(this).val());
							    var projectP1Date = $("#projectP1DateEditHidden").val();
							    var designRequiredDate = moment(projectP1Date, 'DD-MMM-YYYY');
							    var startOfDesignRequiredDate = moment("01-Jan-"+designRequiredDate.year(), 'DD-MMM-YYYY');
							    designRequiredDate.add((backOffInputVal-weeks),'weeks');
							    var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + designRequiredDate.format('MM/DD/YYYY') + "'>" + designRequiredDate.format('MM/DD/YYYY') +" (W"+ moment(designRequiredDate.format('MM/DD/YYYY')).diff(moment(startOfDesignRequiredDate), 'weeks') +")" +"</input>";
							    $("#designRequiredDateTD_"+index).empty();	
							    $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);*/
					    		}
							});
					    	
					    	$('.editMainTableCheckboxes').click(function(){
					    		
					    		var row = $(this);
					    		/*var checked = $(this).prop('checked');
					    		var id = $(this).parent().parent().children("td:eq(5)").children().attr('id');
							    var indexList = id.split('_');
							    var index = indexList[1];
							    console.log(checked);*/
					    		editDetails(row,$(this).data('index'));
					    		fixedHeaderScroll();
					    	});

					    	//Fixed header scroll.
					    	var table = $('#dsgnEditrelease').DataTable( {
					    		
					    		"bPaginate": false,
					    		 "scrollY": 510,
					    	     "scrollX": true,
					    	     
					    	     "ordering": false,
					    	     "bFilter": false,
					    	     "bInfo": false,
					    	      bRetrieve: true,
					    	     
					    	       
					    			} );
					    	$('#dsgnEditrelease').resize();
					    	table.fixedHeader.adjust();
					    }
			    	});
			    }
			});
		});
		
		
	    function editDetails(clickedRow,index){
	    	console.log(clickedRow);
	    	/*var checked = clickedRow.prop('checked');
	    	var id = clickedRow.parent().parent().children("td:eq(7)").children().attr('id');
		    var indexList = id.split('_');
		    var index = indexList[1];*/
	    	var checked = clickedRow.prop('checked');
		if(checked){
			var bomlndescription = clickedRow.parent().parent().children("td:eq(2)").html();
			var engDuration = clickedRow.parent().parent().children("td:eq(5)").html();
			var backOff = clickedRow.parent().parent().children("td:eq(7)").html();
			var designDuration = clickedRow.parent().parent().children("td:eq(13)").html();
			var eng_datechange = clickedRow.parent().parent().children("td:eq(9)").html();
			
			var eng_subgroup = clickedRow.parent().parent().children("td:eq(4)").html();
			
			var eng_orgProject = clickedRow.parent().parent().children("td:eq(10)").html();
			var eng_resource = clickedRow.parent().parent().children("td:eq(11)").html();
			//var eng_comment = clickedRow.parent().parent().children("td:eq(11)").html();
			var design_datechange = clickedRow.parent().parent().children("td:eq(15)").html();
	/*		var design_subgroup = clickedRow.parent().parent().children("td:eq(16)").html();*/
			//console.log("subgroup" +  eng_subgroup);
			var design_orgProject = clickedRow.parent().parent().children("td:eq(16)").html();
			var design_resource = clickedRow.parent().parent().children("td:eq(17)").html();
			//var design_comment = clickedRow.parent().parent().children("td:eq(17)").html();
			var autoclose = clickedRow.parent().parent().children("td:eq(19)").html();
			
			var bomlndescriptionVal = clickedRow.parent().parent().children("td:eq(2)").children().val();
			var engDurationVal = clickedRow.parent().parent().children("td:eq(5)").children().val();
			var backOffVal = clickedRow.parent().parent().children("td:eq(7)").children().val();
			var designDurationVal = clickedRow.parent().parent().children("td:eq(13)").children().val();
			var eng_datechangeVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
			
			var eng_subgroupVal = clickedRow.parent().parent().children("td:eq(4)").children().val();
			
			var eng_orgProjectVal = clickedRow.parent().parent().children("td:eq(10)").children().val();
			var eng_resourceVal = clickedRow.parent().parent().children("td:eq(11)").children().val();
			//var eng_commentVal = clickedRow.parent().parent().children("td:eq(11)").children().val();
			var design_datechangeVal = clickedRow.parent().parent().children("td:eq(15)").children().val();
/*			var design_subgroupVal = clickedRow.parent().parent().children("td:eq(16)").children().val();*/
			var design_orgProjectVal = clickedRow.parent().parent().children("td:eq(16)").children().val();
			var design_resourceVal = clickedRow.parent().parent().children("td:eq(17)").children().val();
			//var design_commentVal = clickedRow.parent().parent().children("td:eq(17)").children().val();
			var autocloseVal = clickedRow.parent().parent().children("td:eq(19)").children().val();
			bomlndescription = bomlndescription.substring(0,bomlndescription.lastIndexOf(">")+1);
			engDuration = engDuration.substring(0,engDuration.lastIndexOf(">")+1);
			backOff = backOff.substring(0,backOff.lastIndexOf(">")+1);
			designDuration = designDuration.substring(0,designDuration.lastIndexOf(">")+1);
			eng_datechange = eng_datechange.substring(0,eng_datechange.lastIndexOf(">")+1);
			eng_subgroup = eng_subgroup.substring(0,eng_subgroup.lastIndexOf(">")+1);
			eng_resource = eng_resource.substring(0,eng_resource.lastIndexOf(">")+1);
			eng_orgProject = eng_orgProject.substring(0,eng_orgProject.lastIndexOf(">")+1);
			//eng_comment = eng_comment.substring(0,eng_comment.lastIndexOf(">")+1);
			design_datechange = design_datechange.substring(0,design_datechange.lastIndexOf(">")+1);
			/*design_subgroup = design_subgroup.substring(0,design_subgroup.lastIndexOf(">")+1);*/
			design_orgProject = design_orgProject.substring(0,design_orgProject.lastIndexOf(">")+1);
			design_resource = design_resource.substring(0,design_resource.lastIndexOf(">")+1);
			//design_comment = design_comment.substring(0,design_comment.lastIndexOf(">")+1);
			autoclose = autoclose.substring(0,autoclose.lastIndexOf(">")+1);
			
			bomlndescription = bomlndescription.replace('type="hidden"','type="text"');
			engDuration = engDuration.replace('type="hidden"','type="text"');
			backOff = backOff.replace('type="hidden"','type="text"');
			designDuration = designDuration.replace('type="hidden"','type="text"');
			eng_datechange = eng_datechange.replace('type="hidden"','type="text"');
			eng_subgroup = eng_subgroup.replace('type="hidden"','type="text"');
			eng_resource = eng_resource.replace('type="hidden"','type="text"');
			eng_orgProject = eng_orgProject.replace('type="hidden"','type="text"');
			//eng_comment = eng_comment.replace('style="display:none"','style="display:inline"');
			design_datechange = design_datechange.replace('type="hidden"','type="text"');
		/*	design_subgroup = design_subgroup.replace('type="hidden"','type="text"');*/
			design_resource = design_resource.replace('type="hidden"','type="text"');
			design_orgProject = design_orgProject.replace('type="hidden"','type="text"');
			//design_comment = design_comment.replace('style="display:none"','style="display:inline"');
			autoclose = autoclose.replace('type="hidden"','type="checkbox"');
			engDurationVal = engDurationVal.substring(0,engDurationVal.length-1);
			backOffVal = backOffVal.substring(0,backOffVal.length-1);
			designDurationVal = designDurationVal.substring(0,designDurationVal.length-1);
			//bomlndescriptionVal = bomlndescriptionVal.substring(0,bomlndescriptionVal.length-1);
			/*engDurationVal = engDurationVal.substring(0,engDurationVal.length-1);
			backOffVal = backOffVal.substring(0,backOffVal.length-1);
			designDurationVal = designDurationVal.substring(0,designDurationVal.length-1);
			
			clickedRow.parent().parent().children("td:eq(2)").html('');
			clickedRow.parent().parent().children("td:eq(4)").html('');
			clickedRow.parent().parent().children("td:eq(6)").html('');
			clickedRow.parent().parent().children("td:eq(12)").html('');
			
			clickedRow.parent().parent().children("td:eq(9)").html('');
			clickedRow.parent().parent().children("td:eq(10)").html('');
			//clickedRow.parent().parent().children("td:eq(11)").html('');
			
			clickedRow.parent().parent().children("td:eq(15)").html('');
			clickedRow.parent().parent().children("td:eq(16)").html('');
			//clickedRow.parent().parent().children("td:eq(17)").html('');
			clickedRow.parent().parent().children("td:eq(18)").html('');
			//clickedRow.parent().parent().children("td:eq(19)").html('');
			getSubgroup(index, clickedRow);
			
			//console.log($("#StatusHiddenInput"+index).val());
			if($("#StatusHiddenInput"+index).val() != "In Edit")
			{
				getDatechangereason(index, clickedRow);
				clickedRow.parent().parent().children("td:eq(8)").html('');
				clickedRow.parent().parent().children("td:eq(8)").append(dao.engdtchnge);
				clickedRow.parent().parent().children("td:eq(8)").children().attr('value',eng_datechangeVal).css('width','70px');
				
				clickedRow.parent().parent().children("td:eq(14)").html('');
				clickedRow.parent().parent().children("td:eq(14)").append(dao.designdtchnge);
				clickedRow.parent().parent().children("td:eq(14)").children().attr('value',design_datechangeVal).css('width','70px');
			}
			
			
			clickedRow.parent().parent().children("td:eq(2)").append(bomlndescription);
			clickedRow.parent().parent().children("td:eq(4)").append(engDuration);
			clickedRow.parent().parent().children("td:eq(6)").append(backOff);
			clickedRow.parent().parent().children("td:eq(12)").append(designDuration);
			//clickedRow.parent().parent().children("td:eq(8)").append(eng_datechange);
			
			clickedRow.parent().parent().children("td:eq(9)").append(dao.engSubgrp);
			//clickedRow.parent().parent().children("td:eq(11)").append(eng_comment);
			//clickedRow.parent().parent().children("td:eq(14)").append(design_datechange);
			
			clickedRow.parent().parent().children("td:eq(15)").append(dao.designSubgrp);
			//clickedRow.parent().parent().children("td:eq(17)").append(design_comment);
			clickedRow.parent().parent().children("td:eq(18)").append(autoclose);
			
			clickedRow.parent().parent().children("td:eq(10)").append();
			//clickedRow.parent().parent().children("td:eq(10)").append();
			clickedRow.parent().parent().children("td:eq(16)").append(dao.designResource);
			//console.log(design_commentVal);
			clickedRow.parent().parent().children("td:eq(2)").children().attr('value',bomlndescriptionVal).css('width','100px');
			clickedRow.parent().parent().children("td:eq(4)").children().attr('value',engDurationVal).css('width','40px');
			clickedRow.parent().parent().children("td:eq(6)").children().attr('value',backOffVal).css('width','40px');
			clickedRow.parent().parent().children("td:eq(12)").children().attr('value',designDurationVal).css('width','40px');
			clickedRow.parent().parent().children("td:eq(9)").children().attr('value',201).css('width','220px');
			clickedRow.parent().parent().children("td:eq(10)").children().attr('value',201).css('width','100px');
			//clickedRow.parent().parent().children("td:eq(11)").children().attr('value',eng_commentVal).css('width','40px');
			clickedRow.parent().parent().children("td:eq(15)").children().attr('value',201).css('width','220px');
			clickedRow.parent().parent().children("td:eq(16)").children().attr('value',201).css('width','100px');
			//clickedRow.parent().parent().children("td:eq(17)").children().attr('value',design_commentVal).css('width','40px');
			clickedRow.parent().parent().children("td:eq(18)").children().attr('value',autocloseVal).css('width','40px');
			//console.log("Design"+$("#design_subgroupHiddenInput"+index).val());
			if($("#eng_subgroupHiddenInput"+index).val() != "")
			{
				$("#engsubgrp"+index).val($("#eng_subgroupHiddenInput"+index).val());
				engsubgrpchange(index, clickedRow);
				
				$("#engrDateChangeReason"+index).val($("#eng_datechangeHiddenInput"+index).val());
				
				
			}
			if($("#design_subgroupHiddenInput"+index).val() != "")
			{
				$("#designsubgrp"+index).val($("#design_subgroupHiddenInput"+index).val());
				designsubgrpchange(index, clickedRow);
				$("#designDateChangeReason"+index).val($("#design_datechangeHiddenInput"+index).val());
			}*/
			
			if($("#StatusHiddenInput"+index).val() == "In Edit")
			{
				
				clickedRow.parent().parent().children("td:eq(2)").html('');
				clickedRow.parent().parent().children("td:eq(5)").html('');
				clickedRow.parent().parent().children("td:eq(7)").html('');
				clickedRow.parent().parent().children("td:eq(13)").html('');
				
				clickedRow.parent().parent().children("td:eq(4)").html('');
				clickedRow.parent().parent().children("td:eq(10)").html('');
				clickedRow.parent().parent().children("td:eq(11)").html('');
				//clickedRow.parent().parent().children("td:eq(11)").html('');
				
				/*clickedRow.parent().parent().children("td:eq(16)").html('');*/
				clickedRow.parent().parent().children("td:eq(16)").html('');
				clickedRow.parent().parent().children("td:eq(17)").html('');
				//clickedRow.parent().parent().children("td:eq(17)").html('');
				clickedRow.parent().parent().children("td:eq(19)").html('');
				//clickedRow.parent().parent().children("td:eq(19)").html('');
				getMainGroup(index, clickedRow);
				
				//console.log($("#StatusHiddenInput"+index).val());
				
				clickedRow.parent().parent().children("td:eq(2)").append(bomlndescription);
				clickedRow.parent().parent().children("td:eq(5)").append(engDuration);
				clickedRow.parent().parent().children("td:eq(7)").append(backOff);
				clickedRow.parent().parent().children("td:eq(13)").append(designDuration);
				//clickedRow.parent().parent().children("td:eq(8)").append(eng_datechange);
				
				clickedRow.parent().parent().children("td:eq(4)").append(dao.mainGrp);
				//clickedRow.parent().parent().children("td:eq(11)").append(eng_comment);
				//clickedRow.parent().parent().children("td:eq(14)").append(design_datechange);
				
				/*clickedRow.parent().parent().children("td:eq(16)").append(dao.designSubgrp);*/
				//clickedRow.parent().parent().children("td:eq(17)").append(design_comment);
				clickedRow.parent().parent().children("td:eq(19)").append(autoclose);
				
				clickedRow.parent().parent().children("td:eq(10)").append();
				clickedRow.parent().parent().children("td:eq(11)").append();
				//clickedRow.parent().parent().children("td:eq(10)").append();
				clickedRow.parent().parent().children("td:eq(17)").append();
				//clickedRow.parent().parent().children("td:eq(17)").append(dao.designResource);
				//console.log(design_commentVal);
				clickedRow.parent().parent().children("td:eq(2)").children().attr('value',bomlndescriptionVal).css('width','100px');
				clickedRow.parent().parent().children("td:eq(5)").children().attr('value',engDurationVal).css({'width':'40px','text-align':'center'});
				clickedRow.parent().parent().children("td:eq(7)").children().attr('value',backOffVal).css({'width':'40px','text-align':'center'});
				clickedRow.parent().parent().children("td:eq(13)").children().attr('value',designDurationVal).css('width','40px');
				clickedRow.parent().parent().children("td:eq(4)").children().attr('value',201).css('width','100px')/*.css('width','220px')*/;
				clickedRow.parent().parent().children("td:eq(10)").children().attr('value',201).css('width','50px')/*.css('width','100px')*/;
				clickedRow.parent().parent().children("td:eq(11)").children().attr('value',201).css('width','50px')/*.css('width','100px')*/;
				//clickedRow.parent().parent().children("td:eq(11)").children().attr('value',eng_commentVal).css('width','40px');
				/*clickedRow.parent().parent().children("td:eq(16)").children().attr('value',201).css('width','50px').css('width','220px');*/
				clickedRow.parent().parent().children("td:eq(16)").children().attr('value',201).css('width','50px')/*.css('width','100px')*/;
				clickedRow.parent().parent().children("td:eq(17)").children().attr('value',201).css('width','50px')/*.css('width','100px')*/;
				//clickedRow.parent().parent().children("td:eq(17)").children().attr('value',design_commentVal).css('width','40px');
				clickedRow.parent().parent().children("td:eq(19)").children().attr('value',autocloseVal).css('width','40px');
				//console.log("Design"+$("#design_subgroupHiddenInput"+index).val());
				/*if($("#eng_subgroupHiddenInput"+index).val() != "")*/
				if($("#mainGroupHiddenInput"+index).val() != "")
				{
					$("#maingrp"+index).val($("#mainGroupHiddenInput"+index).val());
					//mainGrpChange(index, clickedRow);
					mainGrpChange(index, clickedRow);
					$("#engrDateChangeReason"+index).val($("#eng_datechangeHiddenInput"+index).val());
					$("#designDateChangeReason"+index).val($("#design_datechangeHiddenInput"+index).val());
					
				}
				
				/*if($("#design_subgroupHiddenInput"+index).val() != "")
				{
					$("#designsubgrp"+index).val($("#design_subgroupHiddenInput"+index).val());
					designsubgrpchange(index, clickedRow);
					$("#designDateChangeReason"+index).val($("#design_datechangeHiddenInput"+index).val());
				}*/
			}else{
				clickedRow.parent().parent().children("td:eq(7)").html('');
				clickedRow.parent().parent().children("td:eq(5)").html('');
				
				clickedRow.parent().parent().children("td:eq(13)").html('');
				
				clickedRow.parent().parent().children("td:eq(5)").append(engDuration);
				clickedRow.parent().parent().children("td:eq(7)").append(backOff);
				//clickedRow.parent().parent().children("td:eq(11)").append(eng_comment);
				clickedRow.parent().parent().children("td:eq(13)").append(designDuration);
				//clickedRow.parent().parent().children("td:eq(17)").append(design_comment);
				
				clickedRow.parent().parent().children("td:eq(5)").children().attr('value',engDurationVal).css({'width':'40px','text-align':'center'});
				clickedRow.parent().parent().children("td:eq(7)").children().attr('value',backOffVal).css({'width':'40px','text-align':'center'});
				clickedRow.parent().parent().children("td:eq(13)").children().attr('value',designDurationVal).css('width','40px');
				
				getDatechangereason(index, clickedRow);
				
				clickedRow.parent().parent().children("td:eq(9)").html('');
				clickedRow.parent().parent().children("td:eq(9)").append(dao.engdtchnge);
				clickedRow.parent().parent().children("td:eq(9)").children().attr('value',eng_datechangeVal).css('width','70px');
			
				clickedRow.parent().parent().children("td:eq(15)").html('');
				clickedRow.parent().parent().children("td:eq(15)").append(dao.designdtchnge);
				clickedRow.parent().parent().children("td:eq(15)").children().attr('value',design_datechangeVal).css('width','70px');
				datachangeReasonUpdforNonEdit(clickedRow,index);
				$("#engrDateChangeReason"+index).val($("#eng_datechangeHiddenInput"+index).val());
				$("#designDateChangeReason"+index).val($("#design_datechangeHiddenInput"+index).val());
				
				
			}
			$("#engComments_"+index).show();
			$("#dsgnComments_"+index).show();
			$('#engrcmnt'+index).hide();
			$('#dsgncmnt'+index).hide();

		}else{
			
			if($("#StatusHiddenInput"+index).val() == "In Edit")
			{
				var bomlndescription = clickedRow.parent().parent().children("td:eq(2)").html();
				bomlndescription = bomlndescription.substring(0,bomlndescription.lastIndexOf(">")+1);
				var engDuration = clickedRow.parent().parent().children("td:eq(5)").html();
				engDuration = engDuration.substring(0,engDuration.lastIndexOf(">")+1);
				var backOff = clickedRow.parent().parent().children("td:eq(7)").html();
				var designDuration = clickedRow.parent().parent().children("td:eq(13)").html();
				var eng_datechange = clickedRow.parent().parent().children("td:eq(9)").html();
				eng_datechange = eng_datechange.substring(0,eng_datechange.lastIndexOf(">")+1);
				var eng_subgroup = clickedRow.parent().parent().children("td:eq(4)").html();
				var eng_orgProject = clickedRow.parent().parent().children("td:eq(10)").html();
				var eng_resource = clickedRow.parent().parent().children("td:eq(11)").html();
				//var eng_comment = clickedRow.parent().parent().children("td:eq(11)").html();
				//eng_comment = eng_comment.substring(0,eng_comment.lastIndexOf(">")+1);
				var design_datechange = clickedRow.parent().parent().children("td:eq(15)").html();
				design_datechange = design_datechange.substring(0,design_datechange.lastIndexOf(">")+1);
			/*	var design_subgroup = clickedRow.parent().parent().children("td:eq(16)").html();*/
				var design_orgProject = clickedRow.parent().parent().children("td:eq(16)").html();
				var design_resource = clickedRow.parent().parent().children("td:eq(17)").html();
				//var design_comment = clickedRow.parent().parent().children("td:eq(17)").html();
				//design_comment = design_comment.substring(0,design_comment.lastIndexOf(">")+1);
				var autoclose = clickedRow.parent().parent().children("td:eq(19)").html();
				var bomlndescriptionVal = clickedRow.parent().parent().children("td:eq(2)").children().val();
				var engDurationVal = clickedRow.parent().parent().children("td:eq(5)").children().val();
				var backOffVal = clickedRow.parent().parent().children("td:eq(7)").children().val();
				var designDurationVal = clickedRow.parent().parent().children("td:eq(13)").children().val();
				var eng_datechangeVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
				var eng_subgroupVal = clickedRow.parent().parent().children("td:eq(4)").children().val();
				var eng_orgProjectVal = clickedRow.parent().parent().children("td:eq(10)").children().val();
				var eng_resourceVal = clickedRow.parent().parent().children("td:eq(11)").children().val();
				//var eng_commentVal = clickedRow.parent().parent().children("td:eq(11)").children().val();
				var design_datechangeVal = clickedRow.parent().parent().children("td:eq(15)").children().val();
			/*	var design_subgroupVal = clickedRow.parent().parent().children("td:eq(16)").children().val();*/
				var design_orgProjectVal = clickedRow.parent().parent().children("td:eq(16)").children().val();
				var design_resourceVal = clickedRow.parent().parent().children("td:eq(17)").children().val();
				//var design_commentVal = clickedRow.parent().parent().children("td:eq(17)").children().val();
				var autocloseVal = clickedRow.parent().parent().children("td:eq(19)").children().val();
				
				bomlndescription = bomlndescription.replace('type="text"','type="hidden"')+$('#bomlndescriptionHiddenInput'+index).val()+"</input>";
				engDuration = engDuration.replace('type="text"','type="hidden"')+$('#engrDurationHiddenInput'+index).val()+"</input>";
				backOff = backOff.replace('type="text"','type="hidden"')+$('#backOffHiddenInput'+index).val()+"</input>";
				designDuration = designDuration.replace('type="text"','type="hidden"')+$('#designDurationHiddenInput'+index).val()+"</input>";
				
				eng_datechange = eng_datechange.replace('type="text"','type="hidden"')+$('#eng_datechangeHiddenInput'+index).val()+"</input>";
				eng_subgroup = '<input type="hidden" name="designReleaseList['+index+'].mainGroup" value="">'+$('#mainGroupHiddenInput'+index).val()+"</input>";
				eng_orgProject = eng_orgProject.replace('type="text"','type="hidden"')+$('#eng_orgProjectHiddenInput'+index).val()+"</input>";
				eng_resource = eng_resource.replace('type="text"','type="hidden"')+$('#eng_resourceHiddenInput'+index).val()+"</input>";
				//eng_comment = eng_comment.replace('style="display:inline"','style="display:none"')+$('#eng_commentHiddenInput'+index).val()+"</textarea>";
				design_datechange = design_datechange.replace('type="text"','type="hidden"')+$('#design_datechangeHiddenInput'+index).val()+"</input>";
				/*design_subgroup = design_subgroup.replace('type="text"','type="hidden"')+$('#design_subgroupHiddenInput'+index).val()+"</input>";*/
				//design_subgroup = '<input type="hidden" name="designReleaseList['+index+'].designComponentNo" value="">'+$('#design_subgroupHiddenInput'+index).val()+"</input>";
				design_orgProject = design_orgProject.replace('type="text"','type="hidden"')+$('#design_orgProjectHiddenInput'+index).val()+"</input>";
				design_resource = design_resource.replace('type="text"','type="hidden"')+$('#design_resourceHiddenInput'+index).val()+"</input>";
				//design_comment = design_comment.replace('style="display:inline"','style="display:none"')+$('#design_commentHiddenInput'+index).val()+"</textarea>";
				//console.log($('#autocloseHiddenInput'+index).val());
				if($('#autocloseHiddenInput'+index).val()=="true")
					{
						//console.log("true");
						autoclose = autoclose.replace('type="checkbox"','type="hidden"')+"Yes"+"</input>";
					}
					else if($('#autocloseHiddenInput'+index).val()=="false")
					{
						autoclose = autoclose.replace('type="checkbox"','type="hidden"')+"No"+"</input>";
					}
				
				clickedRow.parent().parent().children("td:eq(2)").html('');
				clickedRow.parent().parent().children("td:eq(2)").empty();
				clickedRow.parent().parent().children("td:eq(5)").html('');
				clickedRow.parent().parent().children("td:eq(5)").empty();
				clickedRow.parent().parent().children("td:eq(7)").html('');
				clickedRow.parent().parent().children("td:eq(7)").empty();
				clickedRow.parent().parent().children("td:eq(13)").html('');
				clickedRow.parent().parent().children("td:eq(13)").empty();
				clickedRow.parent().parent().children("td:eq(9)").html('');
				clickedRow.parent().parent().children("td:eq(9)").empty();
				clickedRow.parent().parent().children("td:eq(4)").html('');
				clickedRow.parent().parent().children("td:eq(4)").empty();
				clickedRow.parent().parent().children("td:eq(10)").html('');
				clickedRow.parent().parent().children("td:eq(10)").empty();
				clickedRow.parent().parent().children("td:eq(11)").html('');
				clickedRow.parent().parent().children("td:eq(11)").empty();
				//clickedRow.parent().parent().children("td:eq(11)").html('');
				//clickedRow.parent().parent().children("td:eq(11)").empty();
				clickedRow.parent().parent().children("td:eq(15)").html('');
				clickedRow.parent().parent().children("td:eq(15)").empty();
			/*	clickedRow.parent().parent().children("td:eq(16)").html('');
				clickedRow.parent().parent().children("td:eq(16)").empty();*/
				clickedRow.parent().parent().children("td:eq(16)").html('');
				clickedRow.parent().parent().children("td:eq(16)").empty();
				clickedRow.parent().parent().children("td:eq(17)").html('');
				clickedRow.parent().parent().children("td:eq(17)").empty();
				//clickedRow.parent().parent().children("td:eq(17)").html('');
				/*clickedRow.parent().parent().children("td:eq(18)").empty();*/
				clickedRow.parent().parent().children("td:eq(19)").html('');
				//clickedRow.parent().parent().children("td:eq(18)").empty();
				//console.log("bomlndescription" +  bomlndescription);
				clickedRow.parent().parent().children("td:eq(2)").append(bomlndescription);
				clickedRow.parent().parent().children("td:eq(5)").append(engDuration);
				clickedRow.parent().parent().children("td:eq(7)").append(backOff);
				clickedRow.parent().parent().children("td:eq(13)").append(designDuration);
				//clickedRow.parent().parent().children("td:eq(8)").append(eng_datechange);
				clickedRow.parent().parent().children("td:eq(9)").append($("#eng_datechangeHiddenInput"+index).val());
				//getSubgroup(index);
				//console.log("subgroup" +  eng_subgroup);
				clickedRow.parent().parent().children("td:eq(4)").append(eng_subgroup);
				//clickedRow.parent().parent().children("td:eq(10)").append(eng_resource);
				clickedRow.parent().parent().children("td:eq(10)").append($("#eng_orgProjectHiddenInput"+index).val());
				clickedRow.parent().parent().children("td:eq(11)").append($("#eng_resourceHiddenInput"+index).val());
				//clickedRow.parent().parent().children("td:eq(11)").append(eng_comment);
				//clickedRow.parent().parent().children("td:eq(14)").append(design_datechange);
				clickedRow.parent().parent().children("td:eq(15)").append($("#design_datechangeHiddenInput"+index).val());
		/*		clickedRow.parent().parent().children("td:eq(16)").append(design_subgroup);*/
				//clickedRow.parent().parent().children("td:eq(16)").append(design_resource);
				clickedRow.parent().parent().children("td:eq(16)").append($("#design_orgProjectHiddenInput"+index).val());
				clickedRow.parent().parent().children("td:eq(17)").append($("#design_resourceHiddenInput"+index).val());
				//clickedRow.parent().parent().children("td:eq(17)").append(design_comment);
				clickedRow.parent().parent().children("td:eq(19)").append(autoclose);
				clickedRow.parent().parent().children("td:eq(4)").find('#maingrp'+index).remove();
				/*clickedRow.parent().parent().children("td:eq(16)").find('#designsubgrp'+index).remove();*/
				//clickedRow.parent().parent().children("td:eq(10)").find('#engresource'+index).remove();
				//clickedRow.parent().parent().children("td:eq(10)").append($("#eng_resourceHiddenInput"+index).val());
				clickedRow.parent().parent().children("td:eq(17)").find('#designresource'+index).remove();
				
				clickedRow.parent().parent().children("td:eq(2)").children().attr('value',$('#bomlndescriptionHiddenInput'+index).val());
				clickedRow.parent().parent().children("td:eq(5)").children().attr('value',$('#engrDurationHiddenInput'+index).val());
				clickedRow.parent().parent().children("td:eq(7)").children().attr('value',$('#backOffHiddenInput'+index).val());
				clickedRow.parent().parent().children("td:eq(13)").children().attr('value',$('#designDurationHiddenInput'+index).val());

				//clickedRow.parent().parent().children("td:eq(8)").children().attr('value',$('#eng_datechangeHiddenInput'+index).val());
			/*	clickedRow.parent().parent().children("td:eq(4)").children().attr('value',$('#eng_subgroupHiddenInput'+index).val());*/
				clickedRow.parent().parent().children("td:eq(4)").children().attr('value',$('#mainGroupHiddenInput'+index).val());
				//clickedRow.parent().parent().children("td:eq(11)").children().attr('value',$('#eng_commentHiddenInput'+index).val());
				//clickedRow.parent().parent().children("td:eq(14)").children().attr('value',$('#design_datechangeHiddenInput'+index).val());
				//clickedRow.parent().parent().children("td:eq(15)").children().attr('value',$('#design_subgroupHiddenInput'+index).val());
				//clickedRow.parent().parent().children("td:eq(17)").children().attr('value',$('#design_commentHiddenInput'+index).val());
				clickedRow.parent().parent().children("td:eq(19)").children().attr('value',$('#autocloseHiddenInput'+index).val());
				
				
				//console.log($('#eng_datechangeHiddenInput'+index).val());
				
				var engrStartDateLabel = $('#engrStartDateHiddenInput'+index).val();
				var engrRequiredDateLabel = $('#engrRequiredDateHiddenInput'+index).val();
				var designRequiredDateLabel = $('#designRequiredDateHiddenInput'+index).val();
				var engrStartDateVal = engrStartDateLabel.split(' ');
				var engrRequiredDateVal = engrRequiredDateLabel.split(' ');
				var designRequiredDateVal = designRequiredDateLabel.split(' ');
				
				var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + engrStartDateVal[0] + "'>" + engrStartDateLabel +"</input>";
			    var engrRequiredDateHTML = "<input type='hidden' class='engrRequiredDateInput' id=engrRequiredDate_"+index+" name='designReleaseList[" + index +"].engrRequiredDate' value='" + engrRequiredDateVal[0] + "'>" + engrRequiredDateLabel +"</input>";
			    var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + designRequiredDateVal[0] + "'>" + designRequiredDateLabel +"</input>";
			    $("#engrStartDateTD_"+index).empty();
			    $("#engrRequiredDateTD_"+index).empty();
			    $("#designRequiredDateTD_"+index).empty();	
			    $("#engrStartDateTD_"+index).append(engrStartDateHTML);
			    $("#engrRequiredDateTD_"+index).append(engrRequiredDateHTML);
			    $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
			}else{
				var engDuration = clickedRow.parent().parent().children("td:eq(5)").html();
				engDuration = engDuration.substring(0,engDuration.lastIndexOf(">")+1);
				var backOff = clickedRow.parent().parent().children("td:eq(7)").html();
				var designDuration = clickedRow.parent().parent().children("td:eq(13)").html();
				var eng_datechange = clickedRow.parent().parent().children("td:eq(9)").html();
				eng_datechange = eng_datechange.substring(0,eng_datechange.lastIndexOf(">")+1);
				var design_datechange = clickedRow.parent().parent().children("td:eq(15)").html();
				design_datechange = design_datechange.substring(0,design_datechange.lastIndexOf(">")+1);
				var engDurationVal = clickedRow.parent().parent().children("td:eq(5)").children().val();
				var backOffVal = clickedRow.parent().parent().children("td:eq(7)").children().val();
				var designDurationVal = clickedRow.parent().parent().children("td:eq(13)").children().val();
				var eng_datechangeVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
				var design_datechangeVal = clickedRow.parent().parent().children("td:eq(15)").children().val();
				
				engDuration = engDuration.replace('type="text"','type="hidden"')+$('#engrDurationHiddenInput'+index).val()+"</input>";
				designDuration = designDuration.replace('type="text"','type="hidden"')+$('#designDurationHiddenInput'+index).val()+"</input>";
				backOff = backOff.replace('type="text"','type="hidden"')+$('#backOffHiddenInput'+index).val()+"</input>";
				eng_datechange = eng_datechange.replace('type="text"','type="hidden"')+$('#eng_datechangeHiddenInput'+index).val()+"</input>";
				design_datechange = design_datechange.replace('type="text"','type="hidden"')+$('#design_datechangeHiddenInput'+index).val()+"</input>";
				
				
				clickedRow.parent().parent().children("td:eq(5)").html('');
				clickedRow.parent().parent().children("td:eq(5)").empty();
				clickedRow.parent().parent().children("td:eq(7)").html('');
				clickedRow.parent().parent().children("td:eq(7)").empty();
				clickedRow.parent().parent().children("td:eq(13)").html('');
				clickedRow.parent().parent().children("td:eq(13)").empty();
				clickedRow.parent().parent().children("td:eq(9)").html('');
				clickedRow.parent().parent().children("td:eq(9)").empty();
				clickedRow.parent().parent().children("td:eq(15)").html('');
				clickedRow.parent().parent().children("td:eq(15)").empty();
				
				clickedRow.parent().parent().children("td:eq(5)").append(engDuration);
				clickedRow.parent().parent().children("td:eq(7)").append(backOff);
				clickedRow.parent().parent().children("td:eq(13)").append(designDuration);
				//clickedRow.parent().parent().children("td:eq(8)").append(eng_datechange);
				clickedRow.parent().parent().children("td:eq(9)").append($("#eng_datechangeHiddenInput"+index).val());
				clickedRow.parent().parent().children("td:eq(15)").append($("#design_datechangeHiddenInput"+index).val());
				
				
				clickedRow.parent().parent().children("td:eq(5)").children().attr('value',$('#engrDurationHiddenInput'+index).val());
				clickedRow.parent().parent().children("td:eq(7)").children().attr('value',$('#backOffHiddenInput'+index).val());
				clickedRow.parent().parent().children("td:eq(13)").children().attr('value',$('#designDurationHiddenInput'+index).val());
			}
			/*var bomlndescription = clickedRow.parent().parent().children("td:eq(2)").html();
			bomlndescription = bomlndescription.substring(0,bomlndescription.lastIndexOf(">")+1);
			var engDuration = clickedRow.parent().parent().children("td:eq(4)").html();
			engDuration = engDuration.substring(0,engDuration.lastIndexOf(">")+1);
			var backOff = clickedRow.parent().parent().children("td:eq(6)").html();
			var designDuration = clickedRow.parent().parent().children("td:eq(12)").html();
			var eng_datechange = clickedRow.parent().parent().children("td:eq(8)").html();
			eng_datechange = eng_datechange.substring(0,eng_datechange.lastIndexOf(">")+1);
			var eng_subgroup = clickedRow.parent().parent().children("td:eq(9)").html();
			var eng_resource = clickedRow.parent().parent().children("td:eq(10)").html();
			//var eng_comment = clickedRow.parent().parent().children("td:eq(11)").html();
			//eng_comment = eng_comment.substring(0,eng_comment.lastIndexOf(">")+1);
			var design_datechange = clickedRow.parent().parent().children("td:eq(14)").html();
			design_datechange = design_datechange.substring(0,design_datechange.lastIndexOf(">")+1);
			var design_subgroup = clickedRow.parent().parent().children("td:eq(15)").html();
			var design_resource = clickedRow.parent().parent().children("td:eq(16)").html();
			//var design_comment = clickedRow.parent().parent().children("td:eq(17)").html();
			//design_comment = design_comment.substring(0,design_comment.lastIndexOf(">")+1);
			var autoclose = clickedRow.parent().parent().children("td:eq(18)").html();
			var bomlndescriptionVal = clickedRow.parent().parent().children("td:eq(2)").children().val();
			var engDurationVal = clickedRow.parent().parent().children("td:eq(4)").children().val();
			var backOffVal = clickedRow.parent().parent().children("td:eq(6)").children().val();
			var designDurationVal = clickedRow.parent().parent().children("td:eq(12)").children().val();
			var eng_datechangeVal = clickedRow.parent().parent().children("td:eq(8)").children().val();
			var eng_subgroupVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
			var eng_resourceVal = clickedRow.parent().parent().children("td:eq(10)").children().val();
			//var eng_commentVal = clickedRow.parent().parent().children("td:eq(11)").children().val();
			var design_datechangeVal = clickedRow.parent().parent().children("td:eq(14)").children().val();
			var design_subgroupVal = clickedRow.parent().parent().children("td:eq(15)").children().val();
			var design_resourceVal = clickedRow.parent().parent().children("td:eq(16)").children().val();
			//var design_commentVal = clickedRow.parent().parent().children("td:eq(17)").children().val();
			var autocloseVal = clickedRow.parent().parent().children("td:eq(18)").children().val();
			
			bomlndescription = bomlndescription.replace('type="text"','type="hidden"')+$('#bomlndescriptionHiddenInput'+index).val()+"</input>";
			engDuration = engDuration.replace('type="text"','type="hidden"')+$('#engrDurationHiddenInput'+index).val()+"</input>";
			backOff = backOff.replace('type="text"','type="hidden"')+$('#backOffHiddenInput'+index).val()+"</input>";
			designDuration = designDuration.replace('type="text"','type="hidden"')+$('#designDurationHiddenInput'+index).val()+"</input>";
			
			eng_datechange = eng_datechange.replace('type="text"','type="hidden"')+$('#eng_datechangeHiddenInput'+index).val()+"</input>";
			eng_subgroup = '<input type="hidden" name="designReleaseList['+index+'].engrComponentNo" value="">'+$('#eng_subgroupHiddenInput'+index).val()+"</input>";
			eng_resource = eng_resource.replace('type="text"','type="hidden"')+$('#eng_resourceHiddenInput'+index).val()+"</input>";
			//eng_comment = eng_comment.replace('style="display:inline"','style="display:none"')+$('#eng_commentHiddenInput'+index).val()+"</textarea>";
			design_datechange = design_datechange.replace('type="text"','type="hidden"')+$('#design_datechangeHiddenInput'+index).val()+"</input>";
			//design_subgroup = design_subgroup.replace('type="text"','type="hidden"')+$('#design_subgroupHiddenInput'+index).val()+"</input>";
			design_subgroup = '<input type="hidden" name="designReleaseList['+index+'].designComponentNo" value="">'+$('#design_subgroupHiddenInput'+index).val()+"</input>";
			design_resource = design_resource.replace('type="text"','type="hidden"')+$('#design_resourceHiddenInput'+index).val()+"</input>";
			//design_comment = design_comment.replace('style="display:inline"','style="display:none"')+$('#design_commentHiddenInput'+index).val()+"</textarea>";
			//console.log($('#autocloseHiddenInput'+index).val());
			if($("#StatusHiddenInput"+index).val() == "In Edit")
			{
				if($('#autocloseHiddenInput'+index).val()=="true")
				{
					//console.log("true");
					autoclose = autoclose.replace('type="checkbox"','type="hidden"')+"Yes"+"</input>";
				}
				else if($('#autocloseHiddenInput'+index).val()=="false")
				{
					autoclose = autoclose.replace('type="checkbox"','type="hidden"')+"No"+"</input>";
				}
			}	
			
			
			
			
			clickedRow.parent().parent().children("td:eq(2)").html('');
			clickedRow.parent().parent().children("td:eq(2)").empty();
			clickedRow.parent().parent().children("td:eq(4)").html('');
			clickedRow.parent().parent().children("td:eq(4)").empty();
			clickedRow.parent().parent().children("td:eq(6)").html('');
			clickedRow.parent().parent().children("td:eq(6)").empty();
			clickedRow.parent().parent().children("td:eq(12)").html('');
			clickedRow.parent().parent().children("td:eq(12)").empty();
			clickedRow.parent().parent().children("td:eq(8)").html('');
			clickedRow.parent().parent().children("td:eq(8)").empty();
			clickedRow.parent().parent().children("td:eq(9)").html('');
			clickedRow.parent().parent().children("td:eq(9)").empty();
			clickedRow.parent().parent().children("td:eq(10)").html('');
			clickedRow.parent().parent().children("td:eq(10)").empty();
			//clickedRow.parent().parent().children("td:eq(11)").html('');
			//clickedRow.parent().parent().children("td:eq(11)").empty();
			clickedRow.parent().parent().children("td:eq(14)").html('');
			clickedRow.parent().parent().children("td:eq(14)").empty();
			clickedRow.parent().parent().children("td:eq(15)").html('');
			clickedRow.parent().parent().children("td:eq(15)").empty();
			clickedRow.parent().parent().children("td:eq(16)").html('');
			clickedRow.parent().parent().children("td:eq(16)").empty();
			//clickedRow.parent().parent().children("td:eq(17)").html('');
			clickedRow.parent().parent().children("td:eq(17)").empty();
			clickedRow.parent().parent().children("td:eq(18)").html('');
			//clickedRow.parent().parent().children("td:eq(18)").empty();
			//console.log("bomlndescription" +  bomlndescription);
			clickedRow.parent().parent().children("td:eq(2)").append(bomlndescription);
			clickedRow.parent().parent().children("td:eq(4)").append(engDuration);
			clickedRow.parent().parent().children("td:eq(6)").append(backOff);
			clickedRow.parent().parent().children("td:eq(12)").append(designDuration);
			//clickedRow.parent().parent().children("td:eq(8)").append(eng_datechange);
			clickedRow.parent().parent().children("td:eq(8)").append($("#eng_datechangeHiddenInput"+index).val());
			//getSubgroup(index);
			//console.log("subgroup" +  eng_subgroup);
			clickedRow.parent().parent().children("td:eq(9)").append(eng_subgroup);
			//clickedRow.parent().parent().children("td:eq(10)").append(eng_resource);
			clickedRow.parent().parent().children("td:eq(10)").append($("#eng_resourceHiddenInput"+index).val());
			//clickedRow.parent().parent().children("td:eq(11)").append(eng_comment);
			//clickedRow.parent().parent().children("td:eq(14)").append(design_datechange);
			clickedRow.parent().parent().children("td:eq(14)").append($("#design_datechangeHiddenInput"+index).val());
			clickedRow.parent().parent().children("td:eq(15)").append(design_subgroup);
			//clickedRow.parent().parent().children("td:eq(16)").append(design_resource);
			clickedRow.parent().parent().children("td:eq(16)").append($("#design_resourceHiddenInput"+index).val());
			//clickedRow.parent().parent().children("td:eq(17)").append(design_comment);
			clickedRow.parent().parent().children("td:eq(18)").append(autoclose);
			clickedRow.parent().parent().children("td:eq(9)").find('#engsubgrp'+index).remove();
			clickedRow.parent().parent().children("td:eq(15)").find('#designsubgrp'+index).remove();
			//clickedRow.parent().parent().children("td:eq(10)").find('#engresource'+index).remove();
			//clickedRow.parent().parent().children("td:eq(10)").append($("#eng_resourceHiddenInput"+index).val());
			clickedRow.parent().parent().children("td:eq(16)").find('#designresource'+index).remove();
			
			clickedRow.parent().parent().children("td:eq(2)").children().attr('value',$('#bomlndescriptionHiddenInput'+index).val());
			clickedRow.parent().parent().children("td:eq(4)").children().attr('value',$('#engrDurationHiddenInput'+index).val());
			clickedRow.parent().parent().children("td:eq(6)").children().attr('value',$('#backOffHiddenInput'+index).val());
			clickedRow.parent().parent().children("td:eq(12)").children().attr('value',$('#designDurationHiddenInput'+index).val());

			//clickedRow.parent().parent().children("td:eq(8)").children().attr('value',$('#eng_datechangeHiddenInput'+index).val());
			clickedRow.parent().parent().children("td:eq(9)").children().attr('value',$('#eng_subgroupHiddenInput'+index).val());
			//clickedRow.parent().parent().children("td:eq(11)").children().attr('value',$('#eng_commentHiddenInput'+index).val());
			//clickedRow.parent().parent().children("td:eq(14)").children().attr('value',$('#design_datechangeHiddenInput'+index).val());
			//clickedRow.parent().parent().children("td:eq(15)").children().attr('value',$('#design_subgroupHiddenInput'+index).val());
			//clickedRow.parent().parent().children("td:eq(17)").children().attr('value',$('#design_commentHiddenInput'+index).val());
			clickedRow.parent().parent().children("td:eq(18)").children().attr('value',$('#autocloseHiddenInput'+index).val());
			
			
			//console.log($('#eng_datechangeHiddenInput'+index).val());
			
			var engrStartDateLabel = $('#engrStartDateHiddenInput'+index).val();
			var engrRequiredDateLabel = $('#engrRequiredDateHiddenInput'+index).val();
			var designRequiredDateLabel = $('#designRequiredDateHiddenInput'+index).val();
			var engrStartDateVal = engrStartDateLabel.split(' ');
			var engrRequiredDateVal = engrRequiredDateLabel.split(' ');
			var designRequiredDateVal = designRequiredDateLabel.split(' ');
			
			var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='" + engrStartDateVal[0] + "'>" + engrStartDateLabel +"</input>";
		    var engrRequiredDateHTML = "<input type='hidden' class='engrRequiredDateInput' id=engrRequiredDate_"+index+" name='designReleaseList[" + index +"].engrRequiredDate' value='" + engrRequiredDateVal[0] + "'>" + engrRequiredDateLabel +"</input>";
		    var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + designRequiredDateVal[0] + "'>" + designRequiredDateLabel +"</input>";
		    $("#engrStartDateTD_"+index).empty();
		    $("#engrRequiredDateTD_"+index).empty();
		    $("#designRequiredDateTD_"+index).empty();	
		    $("#engrStartDateTD_"+index).append(engrStartDateHTML);
		    $("#engrRequiredDateTD_"+index).append(engrRequiredDateHTML);
		    $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);*/
			$("#engrStartDateTD_"+index).empty();
			$("#designRequiredDateTD_"+index).empty();
			var engrStartDateHTML = "<input type='hidden' class='engrStartDateInput' id=engrStartDate_"+index+" name='designReleaseList[" + index +"].engrStartDate' value='"+$("#engrStartDateHiddenInput"+index).val()+"'>"+$("#engrStartDateHiddenInput"+index).val()+"</input>";
	    	$("#engrStartDateTD_"+index).append(engrStartDateHTML);
	    	var designRequiredDateHTML = "<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='"+$("#engrRequiredDateHiddenInput"+index).val()+"'>"+$("#engrRequiredDateHiddenInput"+index).val()+"</input>";
	    	 $("#designRequiredDateTD_"+index).append(designRequiredDateHTML);
	    	 
		    $("#engComments_"+index).hide();
			$("#dsgnComments_"+index).hide();
			$('#engrcmnt'+index).show();
			$('#dsgncmnt'+index).show();
		}
	}
	    function datachangeReasonUpdforNonEdit(clickedRow,index){
			if($("#maingrp"+index).val() == "NWR")
			{
				clickedRow.parent().parent().children("td:eq(9)").html('');
				clickedRow.parent().parent().children("td:eq(9)").empty();
				clickedRow.parent().parent().children("td:eq(9)").append('-');
			}
			else
			{
				clickedRow.parent().parent().children("td:eq(9)").html(dao.engdtchnge);
			}
			
			
			if($("#designsubgrp"+index).val() == "NWR")
			{
				clickedRow.parent().parent().children("td:eq(15)").html('');
				clickedRow.parent().parent().children("td:eq(15)").empty();
				clickedRow.parent().parent().children("td:eq(15)").append('-');
			}
			else
			{
				clickedRow.parent().parent().children("td:eq(15)").html(dao.designdtchnge);
			}
		}
	    $("#cancelDesignReleaseEdit").click(function(){
	    	
	    	var edot = [];
	    	var returnst = true;
	    	
	    	if($('.editMainTableCheckboxes:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one checkbox");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			$('input[class="editMainTableCheckboxes"]:checked').each(function() {
				edot.push($(this).data("edot"));
				if($(this).data("status").includes( "In ECR"))
				   {
					   $('#onlyDesignExistErrorLabel').html("EDOT can not be deleted if the status is In ECR");
				       $('#onlyDesignIdExistError').modal('show');
					   returnst =  false;
					   return false;
				   }
				   
			});
			
			if(!returnst)
			{
				return returnst;
			}
			//console.log(edot);
			//Delete confirmation Dialog
			$("#deleteConfirmationDialogLabel").empty();
			$("#deleteConfirmationDialogLabel").append("Do you want to delete selected EDOTs?");
			$('#deleteConfirmationDialog').modal('show');
			return;
			//End
	    	
	    	/*$.ajax({
				method: "POST",
			    data : {
			    	"edot" : edot
			    },
			    url: getContextPath()+'/deleteEdot',
			    success: function(data){
			    	$('#loadingModal').modal('hide');
			    	$('#designUpdateLabel').html('');
			    	if("Design Release deleted successfully" == data){
			    		$('#designUpdateLabel').css('color','green');
			    	}else{
			    		$('#designUpdateLabel').css('color','red');
			    	}
			    	$('#designUpdateLabel').html(data);
			    	$('#designUpdatedModal').modal('show');
			    },
	              error: function (error) {
	            	  //console.log("error"+error);
	            	  $('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Design Release updated successfully" == error.responseText){
				    		$('#designUpdateLabel').css('color','green');
				    	}else{
				    		$('#designUpdateLabel').css('color','red');
				    	}
				    	$('#designUpdateLabel').html(error.responseText);
				    	$('#designUpdatedModal').modal('show');
	              }
			});*/
	    });
		
		$("#saveDesignReleaseEdit").click(function(){
			var projectValue = $('#projectsDropDownEdit').val();
			var returnst = true;
			if(projectValue == '-1'){
				$("#projectDropDownError").modal('show');
				return;
			}else{
				$("#projectIdEditHidden").attr('value',projectValue);
			}
			if($('.editMainTableCheckboxes:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one checkbox");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			
			if(!returnst)
			{
				return returnst;
			}
			
			$('#loadingModal').modal('show');
			$.ajax({
				method: "POST",
			    data : $('#designReleaseEditWrapper').serialize(),
			    url: getContextPath()+'/updateDesignRelease',
			    success: function(data){
			    	$('#loadingModal').modal('hide');
			    	$('#designUpdateLabel').html('');
			    	if("Design Release attached successfully" == data){
			    		$('#designUpdateLabel').css('color','green');
			    	}else{
			    		$('#designUpdateLabel').css('color','red');
			    	}
			    	$('#designUpdateLabel').html(data);
			    	$('#designUpdatedModal').modal('show');
			    },
	              error: function (error) {
	            	  //console.log("error"+error);
	            	  $('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Design Release updated successfully" == error.responseText){
				    		$('#designUpdateLabel').css('color','green');
				    	}else{
				    		$('#designUpdateLabel').css('color','red');
				    	}
				    	$('#designUpdateLabel').html(error.responseText);
				    	$('#designUpdatedModal').modal('show');
	              }
			});
		});
		
		$('.designUpdateOk').click(function(){
			$('#designUpdatedModal').modal('hide');
			$('#projectsDropDownEdit').change();
		});
		
		$("a[href='#content-Edit']").on('shown.bs.tab', function (e) {
			//console.log("edit");
			  var buildProjectDropDownVal = getProjectVal;
			  $('#projectsDropDownEdit').val(buildProjectDropDownVal).change();
			});
		
		var groupList =[];
		
		function getMainGroupOnload()
		{
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getMainGrpList',
			    success: function(data){
			    	dao.maingrpdata = data;
			    	
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
		
		}
		
		function getProjectListOnload()
		{
			/*$.ajax({
				method: "GET",
				url: getContextPath()+'/getProjList',
				success: function(data){
			    	dao.projListData = data;
			    	
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});*/
			
			$.ajax({
				method: "GET",
				 Async:false,
			    url: getContextPath()+'/getProjList?mainGrp='+$("#maingrp"+index).val(),
			   
			    success: function(data){
			    	//$('#loadingModal').modal('hide');
			    	var projList = [];
			    	projList = data;
			    	//console.log(resourceList);
					for(var item in projList){
						$selectEng.append("<option>" + projList[item] + "</option>");
					}
					//engresourcechange(index);
					$("#engrOrgProject_"+index).selectpicker();  
					$("#engrOrgProject_"+index).html('');
					$("#engrOrgProject_"+index).append($selectOrgProject);
					$("#engrOrgProject"+index).val($("#eng_orgProjectHiddenInput"+index).val());
					$('#loadingModal').modal('hide');
						
			    },
	              error: function (error) {
	            	 // $('#loadingModal').modal('hide');
	            	  console.log("error"+error);
	              } 
			    
			});
		
		}
		
		function getResources(index, clickedRow)
		{
			
			var groupList = [];
	    	groupList = dao.maingrpdata;
			//var groupList = [];
	    	/*$select = $("<select class='maingrp' id='maingrp"+index+"' name='designReleaseList[" + index +"].mainGroup'/>");*/
	    //	$select =$("<select class='maingrp' name='designReleaseList[" + index +"].mainGroup' id=\"maingrp"+index+"\">");
		//	$selectDes = $("<select class='maingrp' id='designsubgrp"+index+"' name='designReleaseList[" + index +"].designComponentNo'/>");
	    	$selectOrgProject = $("<select class='orgProject' name='designReleaseList[" + index +"].engrOrgProject' id=\"engrOrgProject"+index+"\">");
	    	$select.on( 'change', function(){ onProjChange(index, clickedRow); } )
			//$selectDes.on( 'change', function(){ designsubgrpchange(index,clickedRow); } )
			
			$select.append("<option></option>");
	    	
	    	/*var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#mainGrp_0").width();
	    	$select.css("width",theWidth + "px");*/
	    	
	    	var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#mainGrp_0").width();
			if(theWidth > 0){
				$select.css("width",theWidth + "px");
			}else{
				theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#mainGrp_"+index).width();
				$select.css("width",theWidth + "px");
			}
			
		//	$selectDes.append("<option></option>");
			for(var item in groupList){
				//console.log(groupList[item]);
				$select.append("<option>" + groupList[item] + "</option>");
			//	$selectDes.append("<option>" + groupList[item] + "</option>");
			}
		}
		
		function getMainGroup(index, clickedRow)
		{
			
			var groupList = [];
	    	groupList = dao.maingrpdata;
			//var groupList = [];
	    	/*$select = $("<select class='maingrp' id='maingrp"+index+"' name='designReleaseList[" + index +"].mainGroup'/>");*/
	    	$select =$("<select class='maingrp' name='designReleaseList[" + index +"].mainGroup' id=\"maingrp"+index+"\">");
		//	$selectDes = $("<select class='maingrp' id='designsubgrp"+index+"' name='designReleaseList[" + index +"].designComponentNo'/>");
	    	$select.on( 'change', function(){ mainGrpChange(index, clickedRow); } )
			//$selectDes.on( 'change', function(){ designsubgrpchange(index,clickedRow); } )
			
			$select.append("<option></option>");
	    	
	    	/*var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#mainGrp_0").width();
	    	$select.css("width",theWidth + "px");*/
	    	
	    	var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#mainGrp_0").width();
			if(theWidth > 0){
				$select.css("width",theWidth + "px");
			}else{
				theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#mainGrp_"+index).width();
				$select.css("width",theWidth + "px");
			}
			
		//	$selectDes.append("<option></option>");
			for(var item in groupList){
				//console.log(groupList[item]);
				$select.append("<option>" + groupList[item] + "</option>");
			//	$selectDes.append("<option>" + groupList[item] + "</option>");
			}
/*
			dao.mainGrp = $select;*/
		//	dao.designSubgrp = $selectDes;
	/*		$("#maingrp"+index).selectpicker();  */
			
			//$("#designsubgrp"+index).selectpicker();  
			//console.log(groupList);
			//dao.mainGrp = $select;
			$("#mainGrp_"+index).selectpicker();  
			$("#mainGrp_"+index).html('');
			$("#mainGrp_"+index).append($select);
			$("#mainGroup"+index).val($("#mainGroupHiddenInput"+index).val());
		}
		
		
		function getDatechangereason(index, clickedRow)
		{
			$engselect = $("<select class='datechange' id='engrDateChangeReason"+index+"' name='designReleaseList[" + index +"].engrDateChangeReason' style='width: 70px;' />");
			$designselect = $("<select class='datechange' id='designDateChangeReason"+index+"' name='designReleaseList[" + index +"].designDateChangeReason' style='width: 70px;'/>");
			
			$engselect.append("<option>ENG</option>");
			$engselect.append("<option>DFG</option>");
			$engselect.append("<option>MFG</option>");
			$engselect.append("<option>PURCH</option>");
			
			$designselect.append("<option>ENG</option>");
			$designselect.append("<option>DFG</option>");
			$designselect.append("<option>MFG</option>");
			$designselect.append("<option>PURCH</option>");
			
			dao.engdtchnge = $engselect;
			dao.designdtchnge = $designselect;
		}
		
		function mainGrpChange(index, clickedRow)
		{
			
			getOrgPrjectDetails(index, clickedRow);
			getDesignOrgProject(index, clickedRow);
			getEngResourcesNew(index, clickedRow);
			designorgProjectchange(index, clickedRow);
			//getEngResources(index, clickedRow);
			//fixedHeaderScroll();
		}
		//New Functions
		function getOrgPrjectDetails(index, clickedRow){
			//console.log("project change");
			//$('#loadingModal').modal('show');
			/*var orgProjectList = [];*/
			var projListData = []
			$selectOrgProject = "";
			$("#engrComponentNoHiddenVar_"+index).val($("#maingrp"+index).val());
			/*$("#mainGroupHiddenInput"+index).val($("#maingrp"+index).val());
			$selectOrgProject = $("<select class='orgProject' name='designReleaseList[" + index +"].engrOrgProject' id=\"engrOrgProject"+index+"\">");
			$selectOrgProject.on( 'change', function(){ getEngResourcesNew(index, clickedRow); } );
			$selectOrgProject.css("width","70px");
			
			$selectOrgProject.append("<option></option>");*/
			
			//$("#mainGroupHiddenInput"+index).val($("#maingrp"+index).val());
			projListData = dao.projListData;
			$selectOrgProject = $("<select class='orgProject' name='designReleaseList[" + index +"].engrOrgProject' id=\"engrOrgProject"+index+"\">");
			$selectOrgProject.on( 'change', function(){ getEngResourcesNew(index, clickedRow); } );
			$selectOrgProject.css("width","70px");
			//$select.on( 'change', function(){ mainGrpChange(index, clickedRow); } )
			//getEngResourcesNew(index, clickedRow);
			
			var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#engrOrgProject_0").width();
			if(theWidth > 0){
				$selectOrgProject.css("width",theWidth + "px");
			}else{
				theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#engrOrgProject_"+index).width();
				$selectOrgProject.css("width",theWidth + "px");
			}
			
			
			//$selectOrgProject.append("<option></option>");
						
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getProjList?mainGrp='+$("#maingrp"+index).val(),
			    success: function(data){
			    	orgProjectList = data;
			    	//console.log(resourceList);
					for(var item in orgProjectList){
						$selectOrgProject.append("<option>" + orgProjectList[item] + "</option>");
					}
					//engresourcechange(index);
					$("#engrOrgProject_"+index).selectpicker();  
					$("#engrOrgProject_"+index).html('');
					$("#engrOrgProject_"+index).append($selectOrgProject);
					//$("#engrOrgProject"+index).val($("#eng_orgProjectHiddenInput"+index).val());
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
			console.log("Resource change");
			$('#loadingModal').modal('show');
			//var engrresourceList = [];
			$selectEng = "";
			//$("#eng_orgProjectHiddenInput"+index).val($("#engrOrgProject"+index).val());
			$selectEng = $("<select class='resources' name='designReleaseList[" + index +"].engrResource' id=\"engresource"+index+"\">");
			//$selectEng.on( 'change', function(){ engresourcechange(index); } )
			$selectEng.css("width","70px");
			
			var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#engresource_0").width();
			if(theWidth >0){
				
				$selectEng.css("width",theWidth + "px");
			}else{
				var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#engresource_"+index).width();
				$selectEng.css("width",theWidth + "px");
			}
			var engrOrgProjectVal = $("#engrOrgProject"+index).val();
			
			if($("#engrOrgProject"+index).val() == null || $("#engrOrgProject"+index).val() == undefined){
				engrOrgProjectVal = $("#eng_orgProjectHiddenInput"+index).val();
			}
			$selectEng.append("<option></option>");
			$.ajax({
				method: "GET",
				 Async:false,
			    url: getContextPath()+'/getEngrResourceList?grpid='+engrOrgProjectVal+'&engrole=Engineer',
			   
			    success: function(data){
			    	//$('#loadingModal').modal('hide');
			    	var engrresourceList = [];
			    	engrresourceList = data;
			    	//console.log(resourceList);
					for(var item in engrresourceList){
						$selectEng.append("<option>" + engrresourceList[item] + "</option>");
					}
					//engresourcechange(index);
					$("#engresource_"+index).selectpicker();  
					$("#engresource_"+index).html('');
					$("#engresource_"+index).append($selectEng);
					$("#engresource"+index).val($("#eng_resourceHiddenInput"+index).val());
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	 // $('#loadingModal').modal('hide');
	            	  console.log("error"+error);
	              } 
			    
			});
			//$('#loadingModal').modal('hide');
			
			/*if($("#maingrp"+index).val() == "NWR")
			{
				ifEngNWR(index,clickedRow);
			}
			else
			{
				notEngNWR(index,clickedRow)
			}*/
			
		}
		//New functions end
		function getEngResources(index, clickedRow){
			//console.log("Resource change");
			$('#loadingModal').modal('show');
			var resourceList = [];
			$selectEng = "";
			$("#engrComponentNoHiddenVar_"+index).val($("#maingrp"+index).val());
			$("#mainGroupHiddenInput"+index).val($("#maingrp"+index).val());
			$selectEng = $("<select class='resources' name='designReleaseList[" + index +"].engrResource' id=\"engresource"+index+"\">");
			$selectEng.on( 'change', function(){ engresourcechange(index); } )
			$selectEng.css("width","200px");
			
			$selectEng.append("<option></option>");
			
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getResourceList?grpid='+$("#maingrp"+index).val()+'&engrole=Engineer',
			    success: function(data){
			    	resourceList = data;
			    	//console.log(resourceList);
					for(var item in resourceList){
						$selectEng.append("<option>" + resourceList[item] + "</option>");
					}
					//engresourcechange(index);
					$("#engresource_"+index).selectpicker();  
					$("#engresource_"+index).html('');
					$("#engresource_"+index).append($selectEng);
					$("#engresource"+index).val($("#eng_resourceHiddenInput"+index).val());
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
			
			
			if($("#maingrp"+index).val() == "NWR")
			{
				ifEngNWR(index,clickedRow);
			}
			else
			{
				notEngNWR(index,clickedRow)
			}
			
		}
		
		//Testing New function
		function getDesignOrgProject(index,clickedRow){
			//console.log("design change");
			//$('#loadingModal').modal('show');
			var projListData = [];
			//$selectDesgn = "";
		//	$("#design_subgroupHiddenInput"+index).val($("#designsubgrp"+index).val());
			$selectDesgnOrgProject = $("<select class='designOrgProject' name='designReleaseList[" + index +"].designOrgProject' id=\"designOrgProject"+index+"\">" );
			$selectDesgnOrgProject.on( 'change', function(){ designorgProjectchange(index,clickedRow); } )
			$selectDesgnOrgProject.css("width","70px");
			//$selectDesgnOrgProject.append("<option></option>");
			
			var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#designOrgProject_0").width();
			if(theWidth >0){
				$selectDesgnOrgProject.css("width",theWidth + "px");
			}else{
				theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#designOrgProject_"+index).width();
				$selectDesgnOrgProject.css("width",theWidth + "px");
			}
			
			
			/*projListData = dao.projListData;
	    	
    		for(var item in projListData){
    			$selectDesgnOrgProject.append("<option>" + projListData[item] + "</option>");
				
			}*/
		
		//designresourcechange(index);
		//$("#designOrgProject_"+index).html('');
		
		//$("#designOrgProject_"+index).append($selectDesgnOrgProject);
		//$("#designOrgProject"+index).val($("#design_oHiddenInput"+index).val());
		/*if($("#designsubgrp"+index).val() == "NWR")
		{
			$("#designresource"+index).val($("#engresource"+index).val());
		}*/
		
		
			$.ajax({
				method: "GET",
				//url: getContextPath()+'/getResourceList?grpid='+$("#designsubgrp"+index).val()+'&engrole=Design Coordinator',
//			    url: getContextPath()+'/getResourceList?grpid=38510&engrole=Design Coordinator',
				url: getContextPath()+'/getProjList?mainGrp='+$("#maingrp"+index).val(),
			    success: function(data){
			    	orgProjectList = data;
			    	
			    		for(var item in orgProjectList){
			    			$selectDesgnOrgProject.append("<option>" + orgProjectList[item] + "</option>");
							
						}
		    		
					//designresourcechange(index);
					$("#designOrgProject_"+index).selectpicker();  
					$("#designOrgProject_"+index).html('');
					
					$("#designOrgProject_"+index).append($selectDesgnOrgProject);
					//$("#designOrgProject"+index).val($("#design_orgProjectHiddenInput"+index).val());
					var designOrgProjectList = $("#design_orgProjectHiddenInput"+index).val().split('-');
				    var designOrgProjectID = designOrgProjectList[0];
					$("#designOrgProject"+index+ " option:contains("+designOrgProjectID+")").attr('selected', 'selected');


					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
			
			
			/*if($("#designsubgrp"+index).val() == "NWR")
			{
				ifdesignNWR(index,clickedRow);
			}
			else
			{
				notdesignNWR(index,clickedRow);
			}*/
			//console.log("Design Resource"+$("#design_resourceHiddenInput"+index).val()+"---"+$("#designresource"+index))
			//$("#designOrgProject"+index).val($.trim($("#design_orgProjectHiddenInput"+index).val()));
		}
		
		function designorgProjectchange(index,clickedRow){
			//console.log("design change");
			$('#loadingModal').modal('show');
			//var resourceList = [];
			$selectDesgn = "";
		//	$("#design_orgProjectHiddenInput"+index).val($("#designOrgProject"+index).val());
			$selectDesgn = $("<select class='resources' name='designReleaseList[" + index +"].designResource' id=\"designresource"+index+"\">" );
			//$selectDesgn.on( 'change', function(){ designresourcechange(index); } )
			$selectDesgn.css("width","70px");
			$selectDesgn.append("<option></option>");
			
			var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#designresource_0").width();
			if(theWidth >0){
				$selectDesgn.css("width",theWidth + "px");
			}else{
				var theWidth = $("#dsgnEditrelease").eq(0).find("tr > td#designresource_"+index).width();
				$selectDesgn.css("width",theWidth + "px");
			}
			
			var designOrgProjectVal = $("#designOrgProject"+index).val();
			
			if($("#designOrgProject"+index).val() == null || $("#designOrgProject"+index).val() == undefined){
				designOrgProjectVal = $("#design_orgProjectHiddenInput"+index).val();
			}
			$.ajax({
				method: "GET",
				//url: getContextPath()+'/getResourceList?grpid='+$("#designsubgrp"+index).val()+'&engrole=Design Coordinator',
//			    url: getContextPath()+'/getResourceList?grpid=38510&engrole=Design Coordinator',
				url: getContextPath()+'/getDesignResourceList?grpid='+designOrgProjectVal+'&engrole=Design Coordinator',
			    success: function(data){
			    	var designResourceList = [];
			    	designResourceList = data;
			    	/*if($("#designsubgrp"+index).val() == "NWR")
					{
			    		$selectDesgn.find('option').remove();
						$selectDesgn.append("<option selected>"+$("#engresource"+index).val()+"</option>");
						$selectDesgn.attr('selected', 'selected');
					}
			    	else
		    		{*/
			    		for(var item in designResourceList){
							$selectDesgn.append("<option>" + designResourceList[item] + "</option>");
							
						}
		    		//}
					
					//designresourcechange(index);
					$("#designresource_"+index).html('');
					
					$("#designresource_"+index).append($selectDesgn);
					$("#designresource"+index).val($("#design_resourceHiddenInput"+index).val());
					/*if($("#designsubgrp"+index).val() == "NWR")
					{
						$("#designresource"+index).val($("#engresource"+index).val());
					}*/
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
			
			
			/*if($("#designsubgrp"+index).val() == "NWR")
			{
				ifdesignNWR(index,clickedRow);
			}
			else
			{
				notdesignNWR(index,clickedRow);
			}*/
			//console.log("Design Resource"+$("#design_resourceHiddenInput"+index).val()+"---"+$("#designresource"+index))
			//$("#designresource"+index).val($.trim($("#design_resourceHiddenInput"+index).val()));
		}
		
		//Testing end
		function designsubgrpchangeOld(index,clickedRow){
			//console.log("design change");
			$('#loadingModal').modal('show');
			var resourceList = [];
			$selectDesgn = "";
			$("#design_subgroupHiddenInput"+index).val($("#designsubgrp"+index).val());
			$selectDesgn = $("<select class='resources' name='designReleaseList[" + index +"].designResource' id=\"designresource"+index+"\">" );
			//$selectDesgn.on( 'change', function(){ designresourcechange(index); } )
			$selectDesgn.css("width","200px");
			$selectDesgn.append("<option></option>");
			console.log($selectDesgn);
			$.ajax({
				method: "GET",
				//url: getContextPath()+'/getResourceList?grpid='+$("#designsubgrp"+index).val()+'&engrole=Design Coordinator',
//			    url: getContextPath()+'/getResourceList?grpid=38510&engrole=Design Coordinator',
				url: getContextPath()+'/getDesignResourceList?grpid='+$("#designsubgrp"+index).val()+'&engrole=Design Coordinator',
			    success: function(data){
			    	resourceList = data;
			    	if($("#designsubgrp"+index).val() == "NWR")
					{
			    		$selectDesgn.find('option').remove();
						$selectDesgn.append("<option selected>"+$("#engresource"+index).val()+"</option>");
						$selectDesgn.attr('selected', 'selected');
					}
			    	else
		    		{
			    		for(var item in resourceList){
							$selectDesgn.append("<option>" + resourceList[item] + "</option>");
							
						}
		    		}
					
					//designresourcechange(index);
					$("#designresource_"+index).html('');
					
					$("#designresource_"+index).append($selectDesgn);
					$("#designresource"+index).val($("#design_resourceHiddenInput"+index).val());
					if($("#designsubgrp"+index).val() == "NWR")
					{
						$("#designresource"+index).val($("#engresource"+index).val());
					}
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
			
			
			if($("#designsubgrp"+index).val() == "NWR")
			{
				ifdesignNWR(index,clickedRow);
			}
			else
			{
				notdesignNWR(index,clickedRow);
			}
			//console.log("Design Resource"+$("#design_resourceHiddenInput"+index).val()+"---"+$("#designresource"+index))
			$("#designresource"+index).val($.trim($("#design_resourceHiddenInput"+index).val()));
		}
		function ifEngNWR(index,clickedRow)
		{
			var engDuration = clickedRow.parent().parent().children("td:eq(4)").html();
			var engDurationval = clickedRow.parent().parent().children("td:eq(4)").children().val();
			engDuration = engDuration.replace('type="text"','type="hidden"').replace('value="'+engDurationval+'"','value=0')+"-"+"</input>";
			clickedRow.parent().parent().children("td:eq(4)").html('');
			clickedRow.parent().parent().children("td:eq(4)").append(engDuration);
			
			var engStartDate = clickedRow.parent().parent().children("td:eq(5)").html();
			engStartDate=engStartDate.substring(0,engStartDate.lastIndexOf(">")+1);
			var engStartDateVal = clickedRow.parent().parent().children("td:eq(5)").children().val();
			engStartDate = engStartDate.replace('value="'+engStartDateVal+'"','value=')+"-"+"</input>";
			clickedRow.parent().parent().children("td:eq(5)").html('');
			clickedRow.parent().parent().children("td:eq(5)").append(engStartDate);
			
			var engRequiredDate = clickedRow.parent().parent().children("td:eq(7)").html();
			engRequiredDate=engRequiredDate.substring(0,engRequiredDate.lastIndexOf(">")+1);
			var engRequiredDateVal = clickedRow.parent().parent().children("td:eq(7)").children().val();
			engRequiredDate = engRequiredDate.replace('value="'+engRequiredDateVal+'"','value=')+"-"+"</input>";
			clickedRow.parent().parent().children("td:eq(7)").html('');
			clickedRow.parent().parent().children("td:eq(7)").append(engRequiredDate);
			
			/*var engDateChangeReason = clickedRow.parent().parent().children("td:eq(8)").html();
			console.log(engDateChangeReason);
			engDateChangeReason = engDateChangeReason.replace('type="text"','type="hidden"');
			var engDateChangeReasonVal = clickedRow.parent().parent().children("td:eq(8)").children().val();
			console.log(engDateChangeReasonVal);
			engDateChangeReason = engDateChangeReason.replace('value="'+engDateChangeReasonVal+'"','value=')+"-"+"</input>";
			console.log(engDateChangeReason);*/
			clickedRow.parent().parent().children("td:eq(8)").html('');
			clickedRow.parent().parent().children("td:eq(8)").empty();
			clickedRow.parent().parent().children("td:eq(8)").append('-');
			
			/*var engComments = clickedRow.parent().parent().children("td:eq(11)").html();
			engComments = engComments.replace('type="text"','type="hidden"');
			console.log(engComments);
			clickedRow.parent().parent().children("td:eq(11)").html('');
			clickedRow.parent().parent().children("td:eq(11)").empty();
			clickedRow.parent().parent().children("td:eq(11)").append(engComments);*/
			
			var engResources= clickedRow.parent().parent().children("td:eq(11)").html();
			engResources=engResources.substring(0,engResources.indexOf(">")+1);
			engResources = engResources.replace('select','input type="hidden" value=null')+"-"+"</input>";
			clickedRow.parent().parent().children("td:eq(11)").html('');
			clickedRow.parent().parent().children("td:eq(11)").empty();
			clickedRow.parent().parent().children("td:eq(11)").append(engResources);
			$("#engComments_"+index).show();
			$("#engrcmnt"+index).hide();
		}
		
		function notEngNWR(index,clickedRow)
		{
			
			var engDuration = clickedRow.parent().parent().children("td:eq(4)").html();
			engDuration=engDuration.substring(0,engDuration.lastIndexOf(">")+1);
			var engDurationval = clickedRow.parent().parent().children("td:eq(4)").children().val();
			var engDurationPreVal = $('#engrDurationHiddenInput'+index).val();
			engDuration = engDuration.replace('type="hidden"','type="text"').replace('value="'+engDurationval+'"','value="'+engDurationPreVal.substring(0,engDurationPreVal.length-1)+'"');
			clickedRow.parent().parent().children("td:eq(4)").html('');
			clickedRow.parent().parent().children("td:eq(4)").empty();
			clickedRow.parent().parent().children("td:eq(4)").append(engDuration);
			
			var engStartDate = clickedRow.parent().parent().children("td:eq(5)").html();
			engStartDate=engStartDate.substring(0,engStartDate.lastIndexOf(">")+1);
			var engStartDateval = clickedRow.parent().parent().children("td:eq(5)").children().val();
			engStartDate = engStartDate.replace('value="'+engStartDateval+'"','value="'+$('#engrStartDateHiddenInput'+index).val()+'"')+$('#engrStartDateHiddenInput'+index).val()+"</input>";
			clickedRow.parent().parent().children("td:eq(5)").html('');
			clickedRow.parent().parent().children("td:eq(5)").empty();
			clickedRow.parent().parent().children("td:eq(5)").append(engStartDate);
			
			var engReqDate = clickedRow.parent().parent().children("td:eq(7)").html();
			engReqDate=engReqDate.substring(0,engReqDate.lastIndexOf(">")+1);
			var eengReqDateval = clickedRow.parent().parent().children("td:eq(7)").children().val();
			engReqDate = engReqDate.replace('value="'+eengReqDateval+'"','value="'+$('#engrRequiredDateHiddenInput'+index).val()+'"')+$('#engrRequiredDateHiddenInput'+index).val()+"</input>";
			clickedRow.parent().parent().children("td:eq(7)").html('');
			clickedRow.parent().parent().children("td:eq(7)").empty();
			clickedRow.parent().parent().children("td:eq(7)").append(engReqDate);
			
			/*var eng_datechange = clickedRow.parent().parent().children("td:eq(8)").html();
			eng_datechange=eng_datechange.substring(0,eng_datechange.lastIndexOf(">")+1);
			var eng_datechangeval = clickedRow.parent().parent().children("td:eq(8)").children().val();
			//eng_datechange = eng_datechange.replace('type="hidden"','type="text"').replace('value="'+eng_datechangeval+'"','value="'+$('#eng_datechangeHiddenInput'+index).val()+'"');
			clickedRow.parent().parent().children("td:eq(8)").html('');
			clickedRow.parent().parent().children("td:eq(8)").empty();
			clickedRow.parent().parent().children("td:eq(8)").append('-');*/
			if($("#StatusHiddenInput"+index).val() != "In Edit")
			{
				clickedRow.parent().parent().children("td:eq(8)").html(dao.engdtchnge);
			}
			/*var engComment = clickedRow.parent().parent().children("td:eq(11)").html();
			engComment=engComment.substring(0,engComment.lastIndexOf(">")+1);
			var engCommentval = clickedRow.parent().parent().children("td:eq(11)").children().val();
			engComment = engComment.replace('type="hidden"','type="text"').replace('value="'+engCommentval+'"','value="'+$('#eng_commentHiddenInput'+index).val()+'"');
			
			//console.log(engComment);
			clickedRow.parent().parent().children("td:eq(11)").html('');
			clickedRow.parent().parent().children("td:eq(11)").empty();
			clickedRow.parent().parent().children("td:eq(11)").append(engComment);*/
			$("#engComments_"+index).show();
			$("#engrcmnt"+index).hide();
			
		}
		
		function ifdesignNWR(index,clickedRow)
		{
			var designDuration = clickedRow.parent().parent().children("td:eq(13)").html();
			var designDurationval = clickedRow.parent().parent().children("td:eq(13)").children().val();
			designDuration = designDuration.replace('type="text"','type="hidden"').replace('value="'+designDurationval+'"','value=""')+"-"+"</input>";
			clickedRow.parent().parent().children("td:eq(13)").html('');
			clickedRow.parent().parent().children("td:eq(13)").append(designDuration);
			
			var designReqDate = clickedRow.parent().parent().children("td:eq(14)").html();
			designReqDate=designReqDate.substring(0,designReqDate.lastIndexOf(">")+1);
			var designReqDateVal = clickedRow.parent().parent().children("td:eq(14)").children().val();
			designReqDate = designReqDate.replace('value="'+designReqDateVal+'"','value=""')+"-"+"</input>";
			clickedRow.parent().parent().children("td:eq(14)").html('');
			clickedRow.parent().parent().children("td:eq(14)").append(designReqDate);
			
			/*var designDateChangeReason = clickedRow.parent().parent().children("td:eq(14)").html();
			designDateChangeReason = designDateChangeReason.replace('type="text"','type="hidden"');
			var designDateChangeReasonVal = clickedRow.parent().parent().children("td:eq(14)").children().val();
			designDateChangeReason = designDateChangeReason.replace('value="'+designDateChangeReasonVal+'"','value=""')+"-"+"</input>";*/
			clickedRow.parent().parent().children("td:eq(15)").html('');
			clickedRow.parent().parent().children("td:eq(15)").empty();
			clickedRow.parent().parent().children("td:eq(15)").append('-');
			
			var designResources= clickedRow.parent().parent().children("td:eq(17)").html();
			designResources=designResources.substring(0,designResources.indexOf(">")+1);
			designResources = designResources.replace('select','input type="hidden"')+$('#eng_resourceHiddenInput'+index).val()+"</input>";
			clickedRow.parent().parent().children("td:eq(17)").html('');
			clickedRow.parent().parent().children("td:eq(17)").empty();
			clickedRow.parent().parent().children("td:eq(17)").append(designResources);
			
			/*var designComments = clickedRow.parent().parent().children("td:eq(17)").html();
			designComments = designComments.replace('type="text"','type="hidden"');
			clickedRow.parent().parent().children("td:eq(17)").html('');
			clickedRow.parent().parent().children("td:eq(17)").empty();
			clickedRow.parent().parent().children("td:eq(17)").append(designComments);*/
			$("#dsgnComments_"+index).show();
			$("#dsgncmnt"+index).hide();
		}
		
		function notdesignNWR(index,clickedRow)
		{
			var designDuration = clickedRow.parent().parent().children("td:eq(13)").html();
			designDuration=designDuration.substring(0,designDuration.lastIndexOf(">")+1);
			var designDurationval = clickedRow.parent().parent().children("td:eq(13)").children().val();
			var designDurationPreval = $('#designDurationHiddenInput'+index).val();
			designDuration = designDuration.replace('type="hidden"','type="text"').replace('value="'+designDurationval+'"','value="'+ designDurationPreval.substring(0,designDurationPreval.length-1) +'"');
			clickedRow.parent().parent().children("td:eq(13)").html('');
			clickedRow.parent().parent().children("td:eq(13)").empty();
			clickedRow.parent().parent().children("td:eq(13)").append(designDuration);
			
			var designReqDate = clickedRow.parent().parent().children("td:eq(14)").html();
			designReqDate=designReqDate.substring(0,designReqDate.lastIndexOf(">")+1);
			var designReqDateVal = clickedRow.parent().parent().children("td:eq(14)").children().val();
			designReqDate = designReqDate.replace('value="'+designReqDateVal+'"','value="'+$('#designRequiredDateHiddenInput'+index).val()+'"')+$('#designRequiredDateHiddenInput'+index).val()+"</input>";
			clickedRow.parent().parent().children("td:eq(14)").html('');
			clickedRow.parent().parent().children("td:eq(14)").append(designReqDate);
			
			/*var designDateChangeReason = clickedRow.parent().parent().children("td:eq(14)").html();
			designDateChangeReason=designDateChangeReason.substring(0,designDateChangeReason.lastIndexOf(">")+1);
			designDateChangeReason = designDateChangeReason.replace('type="hidden"','type="text"');
			var designDateChangeReasonVal = clickedRow.parent().parent().children("td:eq(14)").children().val();
			//designDateChangeReason = designDateChangeReason.replace('value="'+designDateChangeReasonVal+'"','value="'+$('#design_datechangeHiddenInput'+index).val()+'"');
			clickedRow.parent().parent().children("td:eq(14)").html('');
			clickedRow.parent().parent().children("td:eq(14)").empty();*/
			//console.log(designDateChangeReason);
			//clickedRow.parent().parent().children("td:eq(14)").append(designDateChangeReason);
			if($("#StatusHiddenInput"+index).val() != "In Edit")
			{
				clickedRow.parent().parent().children("td:eq(15)").html(dao.designdtchnge);
			}
			
			/*var designComments = clickedRow.parent().parent().children("td:eq(17)").html();
			designComments = designComments.replace('type="hidden"','type="text"').replace('value="'+$('#design_commentHiddenInput'+index).val()+'"','value="'+$('#design_commentHiddenInput'+index).val()+'"');
			//designComments = designComments.replace('type="hidden"','type="text"')+$('#design_commentHiddenInput'+index).val()+"</input>";
			console.log(designComments);
			clickedRow.parent().parent().children("td:eq(17)").html('');
			clickedRow.parent().parent().children("td:eq(17)").empty();
			clickedRow.parent().parent().children("td:eq(17)").append(designComments);*/
			$("#dsgnComments_"+index).show();
			$("#dsgncmnt"+index).hide();
		}
		
		function engresourcechange(index)
		{
			//console.log($("#engresource"+index).val());
			$("#eng_resourceHiddenInput"+index).val($("#engresource"+index).val());
		}
		
		function designresourcechange(index)
		{
			$("#design_resourceHiddenInput"+index).val($("#designresource"+index).val());
		}
		
		function fixedHeaderScroll(){
			//Fixed header scroll.
			
			var table = $('#dsgnEditrelease').DataTable( {
				/*destroy: true,*/
	    		"bPaginate": false,
	    		 "scrollY": 510,
	    	     "scrollX": true,
	    	     "ordering": false,
	    	     "bFilter": false,
	    	     "bInfo": false,
	    	     bRetrieve: true,
	    	       /* fixedHeader: {
	    	            header: true
	    				 
	    	        }*/
	    			} );
	    	$('#dsgnEditrelease').resize();
	    	table.fixedHeader.adjust();
	    	//$(table).dataTable().fnAdjustColumnSizing();
		}
		
		
		
		$('#editallcheckbox').change(function () {
		    $('.editMainTableCheckboxes:enabled').prop('checked', $(this).prop('checked'));
		});
		
		$('#editallcheckbox').click(function () {
			 if(this.checked){
		            $('.editMainTableCheckboxes:enabled').each(function(){
		               this.checked = true;
		               var row = $(this);
		               editDetails(row,$(this).data('index'));
		              fixedHeaderScroll();
		            });
		        }else{
		             $('.editMainTableCheckboxes:enabled').each(function(){
		                this.checked = false;
		                var row = $(this);
			            editDetails(row,$(this).data('index'));
			          fixedHeaderScroll();
		            });
		        }
			
		});
		 $('#deleteConfirmationDialogUpdate').click(function(){
		    	$('#deleteConfirmationDialog').modal('hide');
		    	var edot = [];
		    	$('input[class="editMainTableCheckboxes"]:checked').each(function() {
					edot.push($(this).data("edot"));
		    	});	
		    	$.ajax({
					method: "POST",
				    data : {
				    	"edot" : edot
				    },
				    url: getContextPath()+'/deleteEdot',
				    success: function(data){
				    	$('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Design Release deleted successfully" == data){
				    		$('#designUpdateLabel').css('color','green');
				    	}else{
				    		$('#designUpdateLabel').css('color','red');
				    	}
				    	$('#designUpdateLabel').html(data);
				    	$('#designUpdatedModal').modal('show');
				    },
		              error: function (error) {
		            	  //console.log("error"+error);
		            	  $('#loadingModal').modal('hide');
					    	$('#designUpdateLabel').html('');
					    	if("Design Release updated successfully" == error.responseText){
					    		$('#designUpdateLabel').css('color','green');
					    	}else{
					    		$('#designUpdateLabel').css('color','red');
					    	}
					    	$('#designUpdateLabel').html(error.responseText);
					    	$('#designUpdatedModal').modal('show');
		              }
				});
		    });
});

/*$(".orgProject").on("change", function()
		{
			           console.log(this);
		});*/

   var dao ={
		getMainGroup : function()
		{
			$select = $("<select class='maingrp' >");
			var arr = [{"id":"200", "name": "test"},{"id":"201", "name": "test1"}, {"id": "202", "name": "test2"}];
			
			$option1 = $("<option>", {"value": "", "text": ""});
			$select.append($option1);
			$(arr).each(function(i, e)
			{
				//console.log(e["name"]);
				$option = $("<option>", {"value": e["id"], "text": e["name"]});
				$select.append($option);
					
			});
			//console.log($select);
			dao.mainGrp = $select;
			$(".maingrp").selectpicker();
			
		},
		mainGrp : '',
		maingrpdata : '',
		engdtchnge : '',
		designdtchnge : '',
		projListData : ''
	};