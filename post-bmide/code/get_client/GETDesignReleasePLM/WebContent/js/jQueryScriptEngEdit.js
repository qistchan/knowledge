$(document).ready(function() {	

		$('#projectsEngDropDownEdit').selectpicker();
		$('#templatesDropDownEdit').selectpicker();
		$('#scopesDropDownEdit').selectpicker();
		$("#EditECRImplementstBody").empty();
		$('#projectsEngECRDropDownECR').empty();
		$('#projectsEngDropDownEditECN1').empty();
		$('#projectsEngDropDownEditECN2').empty();
		$('#projectsEngDropDownEditECN2').selectpicker();
		$('#engFilterData').selectpicker();
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
				className = "backGround8FF editMainTableCheckboxesTR";
			}
			var row = $("<tr>");
    		row.attr('class',className);
    		
    		var st="";
    		//onclick=\"edittablecheckboxes("+index+")\"
    		if(value.status != "Engineer Review")
			{
    			st = "disabled";
			}
			
    		var checkBoxColumn = $('<td>');
    		var checkBoxInput = $("<input type='checkbox' class='editMainTableCheckboxes' name='designReleaseList[" + index +"].editChecked' id='check_"+value.bomLineItemId+"' data-edot= '"+value.designReleaseId+"' data-index ='"+index+"' "+st+" />" );
    		var edotHiddenInput = $("<input type='hidden' id='edotHiddenInput"+index+"' value='"+value.designReleaseId+"'/>");
    		var promisedateHiddenInput = $("<input type='hidden' id='promiseHiddenInput"+index+"' value='"+value.engrPromiseDate+"'/>");
    		var promiselabeldateHiddenInput = $("<input type='hidden' id='promiselabelHiddenInput"+index+"' value='"+value.engrPromiseDateLabel+"'/>");
    		var resourceHiddenInput = $("<input type='hidden' id='resourceHiddenInput"+index+"' value='"+value.engrResource+"'/>");
    		var commentHiddenInput = $("<input type='hidden' id='commentHiddenInput"+index+"' value='"+value.engrComment+"'/>");
    		
    		
    		checkBoxColumn.append(checkBoxInput);
    		checkBoxColumn.append(edotHiddenInput);
    		checkBoxColumn.append(promiselabeldateHiddenInput);
    		checkBoxColumn.append(promisedateHiddenInput);
    		checkBoxColumn.append(resourceHiddenInput);
    		checkBoxColumn.append(commentHiddenInput);
    		
    		var bomLineItemIdColumn = $('<td>');
    		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+index+"' name='designReleaseList[" + index +"].bomLineItemId' value='" + value.bomLineItemId + "'>"+ value.bomLineItemId +"</input>");
    		bomLineItemIdColumn.append(bomLineItemIdInput);
    		
    		var descriptionColumn = $('<td>');
    		var descriptionInput = $("<input type='hidden' name='designReleaseList[" + index +"].description' id='itemDescription"+index+"' value='" + value.description + "'>" + value.description +"</input>");
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
    		var engrPromiseDateInput = $("<input type='hidden' readonly name='designReleaseList[" + index +"].engrPromiseDate' id=engPromiseDate_"+index+" value='" + value.engrPromiseDate + "'>" + value.engrPromiseDateLabel +"</input>");
    		engrPromiseDateColumn.append(engrPromiseDateInput);
    		
    		/*var engrActualDateColumn = $('<td>');
    		var engrActualDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrActualDate' value='" + value.engrActualDate + "'>" + value.engrActualDateLabel +"</input>");
    		engrActualDateColumn.append(engrActualDateInput);
    		*/
    		//Subgrp
    	/*	var subgrps = value.engrComponentNo;
    		//subgrps = subgrps.split(".");
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
    		
    		var engrCommentColumn = $('<td>');
    		var engrCommentInput = $("<textarea rows='2' cols='30' style='display:none' name='designReleaseList[" + index +"].engrComment' id=engComments_"+index+" >" + value.engrComment +"</textarea><span id=engcmnt"+index+" class='cmntWrapper'>"+value.engrComment+"</span>");
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
    		
    		var mainGroupColumn = $('<td>',{"style" : "text-align:left"});
    		var mainGroupInput = $("<input type='hidden' name='designReleaseList[" + index +"].mainGroup' value='" + value.mainGroup + "'>" + value.mainGroup +"</input>");
    		mainGroupColumn.append(mainGroupInput);
    		
    		checkBoxColumn.append(designReleaseIdInput);
    		row.append(checkBoxColumn);
    		row.append(bomLineItemIdColumn);
    		row.append(descriptionColumn);
    		row.append(edotColumn);
    		row.append(engrStartDateColumn);
    		row.append(engrRequiredDateColumn);
    		row.append(engrPromiseDateColumn);
    		/*row.append(engrActualDateColumn);*/
    		/*row.append(engrComponentNoColumn);*/
    		row.append(mainGroupColumn);
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
		
		$('.projectInfoEngEditBtn').click(function(){
			$("#project_edit_id").html($("#projectsEngDropDownEdit").val());
			$('#projectInfoEdit').modal('show');
		});
		$('.projectRefresh').click(function(){
			$('#projectsEngDropDownEdit').change();
		});
		
		$('.engFilterClass').change(function(){
			var filterValue = $("#engFilterData").val();
			$("#engSearchTerm").val("");
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
		$('#projectsEngDropDownEdit').change(function(){
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
		    	$("#engrEngProductLine").html('');
		    	$(".projectInfoEditBtn").hide();
		    	$(".projectInfoEngEditBtn").hide();
		    	$(".projectRefresh").hide();
		    	$(".assignECR").hide();
		    	$(".linkTD").hide();
		    	$(".filterEngDataClass").hide();
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
			    	$(".projectInfoEngEditBtn").show();
			    	$(".projectRefresh").show();
			    	$(".assignECR").show();
			    	$(".linkTD").show();
			    	var sVal = $('select[name=engFilterData] option:first').val();
					$('select[name=engFilterData]').val(sVal);
					$(".engFilterClass").selectpicker('refresh');
					$(".filterEngDataClass").show();
					$("#engSearchTerm").val("");
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
							    	$("#dsgnengrelease tbody").append(row);
							    	resetScopeDropdown();
						    	});
					    	}else{
					    		
					    		$("#dsgnengrelease tbody").empty();
						    	for(var i=0 ; i<11 ;i++){
						    		var row = createDesignReleaseEditEmptyTableRow(i);
							    	$("#dsgnengrelease tbody").append(row);
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
					    	$("#engrEngProductLine").html('');
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
					    			$("#engrEngProductLine").html(value[0]);
					    		}
					    	});
					    	
					    	
					    	$('.editMainTableCheckboxes').click(function(){
					    		
					    		var row = $(this);
					    		//console.log($(this).index());
					    		editEngDetails(row, $(this).data('index'));
					    		fixedHeaderScroll();
					    	});

					    	//Fixed header scroll.
					    	var table = $('#dsgnengrelease').DataTable( {
					    		
					    		"bPaginate": false,
					    		 "scrollY": 585,
					    	     "scrollX": true,
					    	     
					    	     "ordering": false,
					    	     "bFilter": false,
					    	     "bInfo": false,
					    	      bRetrieve: true,
					    	     
					    	       
					    			} );
					    	$('#dsgnengrelease').resize();
					    	table.fixedHeader.adjust();
					    }
			    	});
			    }
			});
		});
		
		
		
		function editEngDetails(clickedRow, index){
			    	
			//console.log(clickedRow);
		    	var checked = clickedRow.prop('checked');
		    	var index = index;
		    	
			    //console.log(index);
	    		if(checked){
					
					var design_resource = clickedRow.parent().parent().children("td:eq(9)").html();
					var design_resourceVal = clickedRow.parent().parent().children("td:eq(9)").children().val();
					design_resource = design_resource.substring(0,design_resource.lastIndexOf(">")+1);
					//console.log($("input[name='designReleaseList[1].engrComponentNo'].val()"));
					engsubgrp(index);
					design_resource = design_resource.replace('type="hidden"','type="text"');
					
					$("#engComments_"+index).show();
					
					/*var design_comment = clickedRow.parent().parent().children("td:eq(11)").html();
					var design_commentVal = clickedRow.parent().parent().children("td:eq(11)").children().val();
					design_comment = design_comment.substring(0,design_comment.lastIndexOf(">")+1);
					design_comment = design_comment.replace('style="display:none"','style="display:inline"');
					design_commentVal = design_commentVal.substring(0,design_commentVal.length-1);
					clickedRow.parent().parent().children("td:eq(11)").html('');
					clickedRow.parent().parent().children("td:eq(11)").append(design_comment);
					clickedRow.parent().parent().children("td:eq(11)").children().attr('value',design_commentVal);*/
					
					
					
					
					
					
					var design_promisedate = clickedRow.parent().parent().children("td:eq(6)").html();
					var design_promisedateVal = clickedRow.parent().parent().children("td:eq(6)").children().val();
					design_promisedate = design_promisedate.substring(0,design_promisedate.lastIndexOf(">")+1);
					design_promisedate = design_promisedate.replace('type="hidden"','type="text"');
					design_promisedateVal = design_promisedateVal.substring(0,design_promisedateVal.length-1);
					var design_requiredDate = clickedRow.parent().parent().children("td:eq(5)").html();
					var design_requiredDateVal = clickedRow.parent().parent().children("td:eq(5)").children().val();
					
					clickedRow.parent().parent().children("td:eq(6)").html('');
					clickedRow.parent().parent().children("td:eq(6)").append(design_promisedate);
					clickedRow.parent().parent().children("td:eq(6)").children().attr('value',$('#promiseHiddenInput'+index).val()).css('width','100px');
					/*var SelectedDates = {};
					 SelectedDates[new Date(design_requiredDateVal)] = new Date(design_requiredDateVal);*/
					 console.log(new Date(design_requiredDateVal));
					/*$('#engPromiseDate_'+index).datepicker({changeMonth: true, changeYear: true, dateFormat: 'mm/dd/yy' , beforeShowDay: function(newDate) {
			            var Highlight = SelectedDates[newDate];
			            if (Highlight) {
			                return [true, "Highlighted", Highlight];
			            }
			            else {
			                return [true, '', ''];
			            }
			        }});*/
					 $('#engPromiseDate_'+index).datepicker({changeMonth: true, changeYear: true, dateFormat: 'mm/dd/yy', defaultDate: new Date(design_requiredDateVal)});
					// $('#engPromiseDate_'+index).datepicker('setDate', design_requiredDateVal);
					$('#engcmnt'+index).hide();
		
				}else{
					
					
					var design_resource = clickedRow.parent().parent().children("td:eq(9)").html();
					var design_resourceVal = clickedRow.parent().parent().children("td:eq(9)").children().val();				
					clickedRow.parent().parent().children("td:eq(9)").html('');				
					clickedRow.parent().parent().children("td:eq(9)").html($('#resourceHiddenInput'+index).val());
					
					$("#engComments_"+index).hide();
					/*var design_comment = clickedRow.parent().parent().children("td:eq(11)").html();
					var design_commentVal = clickedRow.parent().parent().children("td:eq(11)").children().val();
					design_comment = design_comment.replace('style="display:inline"','style="display:none"')+$('#commentHiddenInput'+index).val()+"</textarea>";
					clickedRow.parent().parent().children("td:eq(11)").html('');
					clickedRow.parent().parent().children("td:eq(11)").append(design_comment);
					clickedRow.parent().parent().children("td:eq(11)").children().attr('value',$('#commentHiddenInput'+index).val());*/
					
					

					var design_promisedate = clickedRow.parent().parent().children("td:eq(6)").html();
					var design_promisedateVal = clickedRow.parent().parent().children("td:eq(6)").children().val();
					design_promisedate = design_promisedate.replace('type="text"','type="hidden"')+$('#promiselabelHiddenInput'+index).val()+"</input>";
					clickedRow.parent().parent().children("td:eq(6)").html('');
					clickedRow.parent().parent().children("td:eq(6)").append(design_promisedate);
					clickedRow.parent().parent().children("td:eq(6)").children().attr('value',$('#promiseHiddenInput'+index).val());
					$('#engPromiseDate_'+index).removeClass('hasDatepicker');
					$('#engcmnt'+index).show();
				}
			}
		
		$('#editEngnallcheckbox').change(function () {
			console.log("engineer");
		    $('.editMainTableCheckboxes:enabled').prop('checked', $(this).prop('checked'));
		});
		
		$('#editEngnallcheckbox').click(function () {
			 if(this.checked){
		            $('.editMainTableCheckboxes:enabled').each(function(){
		               this.checked = true;
		               var row = $(this);
		               $('#engPromiseDate_'+$(this).data('index')).removeClass('hasDatepicker');
		               editEngDetails(row, $(this).data('index'));
		               fixedHeaderScroll();
		            });
		        }else{
		             $('.editMainTableCheckboxes:enabled').each(function(){
		                this.checked = false;
		                var row = $(this);
		                $('#engPromiseDate_'+$(this).data('index')).removeClass('hasDatepicker');
		                editEngDetails(row, $(this).data('index'));
		                fixedHeaderScroll();
		            });
		        }
			
		});
		
		
		$("#engacceptDesignReleaseEdit,#engreassignDesignReleaseEdit,#engclosureDesignReleaseEdit").on("click", function()
		{
			//console.log($(this).data('action'));
			var edot=[], resource = [], subgrp=[], promisedt=[], comments=[];
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
					//console.log($(this).data('index'));
					edot.push($(this).data('edot'));
					resource.push($("#engresource"+$(this).data('index')).val());
					//subgrp.push($("#subgroup_"+$(this).data('index')).val());
					subgrp.push($("#engrOrgProject_"+$(this).data('index')).val());
					promisedt.push($("#engPromiseDate_"+$(this).data('index')).val());
					comments.push($("#engComments_"+$(this).data('index')).val());
					
					
					if(action == "accept")
		    		{
						if(($("#engPromiseDate_"+$(this).data('index')).val() == "") || ($("#engPromiseDate_"+$(this).data('index')).val() == null))
						{
							//alert("Please fill the Promise Date");
							$("#onlyDesignExistErrorLabel").html("Please fill the Promise Date");
							$("#engPromiseDate_"+$(this).data('index')).focus();
							$("#onlyDesignIdExistError").modal('show');
							returnst =  false;
							return false;
						}
		    		}
					if(action == "reassign")
		    		{
						if(($("#engresource"+$(this).data('index')).val() == "") || ($("#engresource"+$(this).data('index')).val() == null))
						{
							//alert("Please fill the Resource");
							$("#onlyDesignExistErrorLabel").html("Please fill the Resource");
							$("#engresource"+$(this).data('index')).focus();
							$("#onlyDesignIdExistError").modal('show');
							returnst =  false;
							return false;
						}
						
						if(($("#resourceHiddenInput"+$(this).data('index')).val() == $("#engresource"+$(this).data('index')).val()))
						{
							//alert("Please Reassign to New Resource");
							$("#onlyDesignExistErrorLabel").html("Please Reassign to New Resource");
							$("#engresource"+$(this).data('index')).focus();
							$("#onlyDesignIdExistError").modal('show');
							returnst =  false;
							return false;
						}
		    		}
					if(action == "eng_reject")
		    		{
						if(($("#engComments_"+$(this).data('index')).val() == "") || ($("#engComments_"+$(this).data('index')).val() == null))
						{
							//alert("Please fill the Comments");
							$("#onlyDesignExistErrorLabel").html("Please fill the Comments");
							$("#engComments_"+$(this).data('index')).focus();
							$("#onlyDesignIdExistError").modal('show');
							returnst =  false;
							return false;
						}
		    		}
					
			});
			//console.log(returnst);
			if(!returnst)
			{
				return returnst;
			}
			
			//console.log("Exit");
			var data ={
					edot : edot,					
					subgrp : subgrp,
					resource : resource,
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
			if($.trim($(this).data('action')) == "reassign" || $.trim($(this).data('action')) == "accept" || $.trim($(this).data('action')) == "eng_reject")
			{
				//console.log($(this).data('action'));
				$.ajax({
					method: "POST",
				    url: getContextPath()+'/updateDesign',
				    data : up_data,
				    success: function(data){
				    },
				    error : function(error)
				    {
				    	/*console.log(error);
				    	if(error.status == 200)
			    		{
				    		updateActions(data, action);
			    		}*/
				    	//Populate server error messages
				    	var res = "";
				    	$('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if(error.responseText == 'Success')
			    		{
				    		updateActions(data, action);
				    		
			    		}
				    	else if("not updated" == error.responseText)
			    		{
				    		if(action == 'accept')
				    		{
				    		 res = "Accept Failed";
				    		}
				    		if(action == 'reassign')
				    		{
				    		 res = "Reassign Failed";
				    		}
				    		if(action == 'eng_reject')
				    		{
				    		 res = "Closure Request Failed";
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
				    	//end
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
			    		if(action == 'accept')
			    		{
			    		 res = "Accepted Successfully";
			    		}
			    		if(action == 'reassign')
			    		{
			    		 res = "Delegated to Another Engineer Successfully";
			    		}
			    		if(action == 'eng_reject')
			    		{
			    		 res = "Closure Request Submitted Successfully";
			    		}
			    		$('#designUpdateLabel').css('color','green');
		    		}
			    	else
		    		{
			    		if(action == 'accept')
			    		{
			    		 res = "Accept Failed";
			    		}
			    		if(action == 'reassign')
			    		{
			    		 res = "Reassign Failed";
			    		}
			    		if(action == 'eng_reject')
			    		{
			    		 res = "Closure Request Failed";
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
			$('#projectsEngDropDownEdit').change();
		});
		
		function engsubgrp(index){
			$('#loadingModal').modal('show');
			//var grpid = $("#subgroup_"+index).val();
			var grpid = $("#engrOrgProject_"+index).val();
			/*
			grpid = grpid.split("(");
			grpid = $.trim(grpid[0]);*/
			//console.log(index);		
			var resourceList = [];
			var org_engresource = $("#resourceHiddenInput"+index).val();
			$("#engresource"+index+" option").remove();
			$select = $("<select class='resources' name='designReleaseList[" + index +"].engResource' id=\"engresource"+index+"\">" );
			$select.append("<option></option>");
			
			var theWidth = $("#dsgnengrelease").eq(0).find("tr > td#engresource_0").width();
			if(theWidth >0){
				$select.css("width",theWidth + "px");
			}else{
				theWidth = $("#dsgnengrelease").eq(0).find("tr > td#engresource_"+index).width();
				$select.css("width",theWidth + "px");
			}
			
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getEngrResourceList?grpid='+grpid+'&engrole=Engineer',
			    success: function(data){
			    	resourceList = data;
					for(var item in resourceList){
						$select.append("<option>" + resourceList[item] + "</option>");
						
					}
					//console.log($select);
					$("#engresource_"+index).html('');
					$("#engresource_"+index).append($select);
					$("#engresource"+index).val(org_engresource);
					$('#loadingModal').modal('hide');
			    },
	              error: function (error) {
	            	  console.log("error"+error);
	              } 
			});
			
			
		}
		$('.assignECR').click(function(){
			
			var row ="";
			var index = 1;
			$("#EditECRImplementstBody").empty();
			$('#projectsEngECRDropDownECR').empty();
			$('#editEngECRcheckbox').prop('checked', false); 
			/*$("#dsgnengrelease tr").each(function() 
			{ 
				//console.log($(this).find('td').eq(13).text());
			       var status = $(this).find('td').eq(13).text();
	               // if(status == "create or  assign ECR"){ 
			       if(status.indexOf("ECR") > -1){
						var className = "";
						if(index % 2 == 0){
							className = "backGround8FF";
						}
	                	row = row + "<tr class="+className+">";
	    				row = row + "<td><input type='checkbox' class='ECRtemplateTableCheckboxes ' id='ECRIndex_"+index +"' data-index ='"+index+ "' data-edot= '"+$(this).find('td').eq(3).text()+"'></input></td>";
	    				row = row + "<td class='centerAlign'>" + $(this).find('td').eq(1).text() + "</td><td class='centerAlign'>" + $(this).find('td').eq(2).text()+ "</td><td class=' ECRAssEDOT centerAlign'>"+ $(this).find('td').eq(3).text() + "</td></tr>";
	    				index = index+1;
	                }
			});*/
			
			populateAssignECREDOts();
			/*$.ajax({
				method: "GET",
			    url: getContextPath()+'/getAssignECRData',
			    success: function(data){
			    	$.each(data, function(index, value){
			    		var className = "";
						if(index % 2 == 0){
							className = "backGround8FF";
						}
	                	row = row + "<tr class="+className+">";
	    				row = row + "<td><input type='checkbox' class='ECRtemplateTableCheckboxes' id='ECRIndex_"+value.bomLineItemId +"' data-index ='"+index+ "' data-edot= '"+value.designReleaseId+"'></input></td>";
	    				row = row + "<td class='centerAlign'>" + value.bomLineItemId + "</td><td class='centerAlign'>" + value.description+ "</td><td class=' ECRAssEDOT centerAlign'>"+ value.designReleaseId + "</td></tr>";
			    	});
			    	$("#designReleaseEditECRtBody").empty().append(row);
					createDummyEdotsContent();
					createDummyImplementsContent();
			    },
			    error : function(error)
			    {
			    	 $("#onlyDesignExistErrorLabel").html("There is an error in getting the EDOT list");
					 $("#onlyDesignIdExistError").modal('show');
					 return false;
			    }
			});*/
			
			
			//End of first table
			//Second table
			var selectOptions = "<option value='-1' selected>Please select</option>";
			
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/getECRList',
			    success: function(data){
			    	$.each(data, function(index, value){
			    		selectOptions = selectOptions+ "<option>"+value+"</option>";
			    	});
			    	$('#projectsEngECRDropDownECR').selectpicker();
					 $("#projectsEngECRDropDownECR")
				       .html(selectOptions)
				       .selectpicker('refresh');
			    },
			    error : function(error)
			    {
			    	
						 $("#onlyDesignExistErrorLabel").html("There is an error in getting the ECR list");
						 $("#onlyDesignIdExistError").modal('show');
						 return false;
					
			    }
			});
			 //End of second table
	    	$("#ECRTemplate").modal('show');
		});
		
		
		$('#projectsEngECRDropDownECR').change(function(){
			var selectedECR = $('#projectsEngECRDropDownECR').val();
			var ecrID = "";
			var data = {
					ecrID : $('#projectsEngECRDropDownECR').val()
			};
			var row ="";
			var index = 1;
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/listEdotForSelectedECR',
			    data : data,
			    success: function(data){
			    	$.each(data, function(index, value){
			    		var className = "";
						if(index % 2 == 0){
							className = "backGround8FF";
						}
	                	row = row + "<tr class="+className+" id=tr_"+value +">";
	                	row = row + "<td><input type='checkbox' class='ECRImplementsTableCheckboxes ' id='ECRImpIndex_"+index +"' data-index ='"+index+ "' data-edot= '"+value+"'></input></td>";
	    				row = row + "<td>"+ value+"</td></tr>";
	    				index = index +1;
			    	});
			    	$("#EditECRImplementstBody").empty().append(row);
			    	createDummyImplementsContent();
			    },
			    error : function(error)
			    {
			    	 $("#onlyDesignExistErrorLabel").html("There is an error in getting the EDOT list corresponding to ECR");
					 $("#onlyDesignIdExistError").modal('show');
					 return false;
			    }
			});
		});
		
		$('#ECRTemplateAssign').click(function(){
		
			var edotArray=[];
			var edot = [];
			if($('.ECRtemplateTableCheckboxes:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one checkbox");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			if($('#projectsEngECRDropDownECR').val() == -1 || $('#projectsEngECRDropDownECR').val() == undefined){
				 $("#onlyDesignExistErrorLabel").html("Please select ECR");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			$(".ECRtemplateTableCheckboxes:checked").each(function()
			{
				edot.push($(this).data('edot'));
			});
			var ECRImplementsLength = "";
			var data = {
				edot : edot,
				ecrID : $('#projectsEngECRDropDownECR').val()
			};
			var row = "";
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/assignEDOTstoECR',
			    data : data,
			    success: function(data){
			    	var res = "";
			    	$('#loadingModal').modal('hide');
			    	$('#designUpdateLabel').html('');
			    	if("Success" == data){
			    		$('#designUpdateLabel').css('color','green');
			    		res = "Assigned Successfully";
			    		var className = "";
			    		//$("#dsgnengecrrelease input[type='checkbox']:checked").parent().parent().remove();
			    		 
			    		 createNewImplementsTable();
			    		 ECRImplementsLength = $('#EditECRImplementstBody tr').length;
			    		
			    		 $.each( edot, function( index, value ){
			    			if(ECRImplementsLength % 2 == 0){
								className = "backGround8FF";
							}
			    			row = row + "<tr class="+className+" id=tr_"+value +">";
				    		row = row + "<td><input type='checkbox' class='ECRImplementsTableCheckboxes ' id='ECRImpIndex_"+ECRImplementsLength +"' data-index ='"+ECRImplementsLength+ "' data-edot= '"+value+"'></input></td>";
		    				row = row + "<td>"+ value+"</td></tr>";
		    				ECRImplementsLength = ECRImplementsLength + 1;
			    		});
			    		$("#EditECRImplementstBody").empty().append(row);
			    		createDummyImplementsContent();
			    		$('#designUpdateLabel').html(res);
				    	$('#designUpdatedModal').modal('show');
				    	populateAssignECREDOts();
			    	}else{
			    		$('#designUpdateLabel').css('color','red');
			    		res = data;
			    		$('#designUpdateLabel').html(res);
				    	$('#designUpdatedModal').modal('show');
			    	}
			    	
			    },
			    error : function(error)
			    {
			    	var res="";
			    	 $('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Success" == error.responseText){
				    		$('#designUpdateLabel').css('color','green');
				    		res = "Assigned Successfully";
				    		var className = "";
				    		 console.log("ECRImplementsLength1"+ECRImplementsLength);
				    		//$("#dsgnengecrrelease input[type='checkbox']:checked").parent().parent().remove();
				    		 createNewImplementsTable();
				    		 ECRImplementsLength = $('#EditECRImplementstBody tr').length;
				    		$.each( edot, function( index, value ){
				    			if(ECRImplementsLength % 2 == 0){
									className = "backGround8FF";
								}
				    			row = row + "<tr class="+className+" id=tr_"+value +">";
					    		row = row + "<td><input type='checkbox' class='ECRImplementsTableCheckboxes ' id='ECRImpIndex_"+ECRImplementsLength +"' data-index ='"+ECRImplementsLength+ "' data-edot= '"+value+"'></input></td>";
			    				row = row + "<td>"+ value+"</td></tr>";
			    				ECRImplementsLength = ECRImplementsLength + 1;
				    		});
				    		$("#EditECRImplementstBody").append(row);
				    		createDummyImplementsContent();
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
					    	populateAssignECREDOts();
				    	}
				    	else{
				    		$('#designUpdateLabel').css('color','red');
				    		res = error.responseText;
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
					    	
				    	}
				    
			    }
			});
		});
		
		function populateAssignECREDOts(){
			
			var row ="";
			
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getAssignECRData',
			    success: function(data){
			    	$.each(data, function(index, value){
			    		var className = "";
						if(index % 2 == 0){
							className = "backGround8FF";
						}
	                	row = row + "<tr class="+className+">";
	    				row = row + "<td><input type='checkbox' class='ECRtemplateTableCheckboxes' id='ECRIndex_"+value.bomLineItemId +"' data-index ='"+index+ "' data-edot= '"+value.designReleaseId+"'></input></td>";
	    				row = row + "<td class='centerAlign'>" + value.bomLineItemId + "</td><td class='centerAlign'>" + value.description+ "</td><td class=' ECRAssEDOT centerAlign'>"+ value.designReleaseId + "</td></tr>";
	    				
			    	});
			    	$("#designReleaseEditECRtBody").empty().append(row);
					createDummyEdotsContent();
					createDummyImplementsContent();
			    },
			    error : function(error)
			    {
			    	 $("#onlyDesignExistErrorLabel").html("There is an error in getting the EDOT list");
					 $("#onlyDesignIdExistError").modal('show');
					 return false;
			    }
			});
			
			
			//End of first table
		}
		function createNewImplementsTable(){
			var row = "";
			var index = 1;
			$("#dsgnengecrImplementsrelease tr").each(function() 
					{ 
						 var value = $(this).find('td').eq(1).text();
			                
					       if(value != "" && value != " " && value.indexOf("EDOT") >-1){
								var className = "";
								if(index % 2 == 0){
									className = "backGround8FF";
								}
			                	row = row + "<tr class="+className+">";
			    				row = row + "<td><input type='checkbox' class='ECRImplementsTableCheckboxes' id='ECRIndex_"+index +"' data-index ='"+index+ "' data-edot= '"+$(this).find('td').eq(1).text()+"'></input></td>";
			    				row = row + "<td class='centerAlign'>" + $(this).find('td').eq(1).text() + "</td></tr>";
			    				index = index+1;
			                }
					});
			$("#EditECRImplementstBody").empty().append(row);
					
		}
		$('#ECRTemplateRemove').click(function(){
			var edot = [];
			if($('.ECRImplementsTableCheckboxes:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one checkbox from Implements Table");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			
			$(".ECRImplementsTableCheckboxes:checked").each(function()
			{
				edot.push($(this).data('edot'));
			});
			
			var data = {
					edot : edot,
					ecrID : $('#projectsEngECRDropDownECR').val()
			};
			
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/removeEdotFromECR',
			    data : data,
			    success: function(data){
			    	var res="";
			    	 $('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Success" == error.responseText){
				    		$('#designUpdateLabel').css('color','green');
				    		res = "Removed Successfully";
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
					    	$("#dsgnengecrImplementsrelease input[type='checkbox']:checked").parent().parent().remove();
				    		createDummyImplementsContent();
				    		populateAssignECREDOts();
				    	}else{
				    		$('#designUpdateLabel').css('color','red');
				    		res = data;
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
				    	}
				    	
			    },error : function(error){
			    	var res="";
			    	 $('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Success" == error.responseText){
				    		$('#designUpdateLabel').css('color','green');
				    		res = "Removed Successfully";
				    		
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
					    	
				    		$("#dsgnengecrImplementsrelease input[type='checkbox']:checked").parent().parent().remove();
							createDummyImplementsContent();
							populateAssignECREDOts();
				    	}
				    	else if(error.responseText == "Fail"){
				    		$('#designUpdateLabel').css('color','red');
				    		res = "Remove action Failed";
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
				    		
				    	}else{
				    		$('#designUpdateLabel').css('color','red');
				    		res = error.responseText;
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
				    	}
				    
			    }
			    
			});
			
		});
		
		function createDummyImplementsContent(){
			var ECRImplementsLengthAftAdd = $('#EditECRImplementstBody tr').length;
    		if(ECRImplementsLengthAftAdd < 7){
    			for(var k=ECRImplementsLengthAftAdd ; k<7 ; k++){
    				var className = "";
					if(k % 2 == 0){
						className = "backGround8FF";
					}
    				var row = $('<tr>');
					row.attr('class',className);
					for(var i=0; i < 2; i++){
						row.append($('<td>').append('&nbsp;'));
					}
					$("#EditECRImplementstBody").append(row);
    			}
    			
    		}
		}
		
		function createDummyEdotsContent(){
			var ECRImplementsLengthAftAdd = $('#designReleaseEditECRtBody tr').length;
			if(ECRImplementsLengthAftAdd < 9){
    			for(var k=ECRImplementsLengthAftAdd ; k<9 ; k++){
    				var className = "";
					if(k % 2 != 0){
						className = "backGround8FF";
					}
					var row = $('<tr>');
					row.attr('class',className);
					for(var i=0; i < 4; i++){
						row.append($('<td>').append('&nbsp;'));
					}
					$("#designReleaseEditECRtBody").append(row);
    			}
    			
    		}
		}
		
		$('.linkTD').click(function(){
			
			$('#projectsEngDropDownEditECN1').selectpicker();
			//$('#projectsEngDropDownEditECN2').selectpicker();
			$("#designReleaseTechDatatbody").empty();
			$("#designReleaseECNtbody").empty();
			$("#designReleaseEcnEdottBody").empty();
			$('#projectsEngDropDownEditECN2').empty();
			$('#projectsEngDropDownEditECN1').empty();
			
			
			var selectOptions = "<option value='-1' selected>Please select</option>";
			var selectOptions2 = "<option value='-1' selected>Please select</option>";
			$("#projectsEngDropDownEditECN2")
		       .html(selectOptions2)
		       .selectpicker('refresh');
			
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/getECRList',
			    success: function(data){
			    	$.each(data, function(index, value){
			    		selectOptions = selectOptions+ "<option>"+value+"</option>";
			    	});
			    	$('#projectsEngDropDownEditECN1').selectpicker();
					 $("#projectsEngDropDownEditECN1")
				       .html(selectOptions)
				       .selectpicker('refresh');
			    },
			    error : function(error)
			    {
			    	 $("#onlyDesignExistErrorLabel").html("There is an error in getting the ECR list");
					 $("#onlyDesignIdExistError").modal('show');
					 return false;
			    }
			});
			var ecnTableLength = $('#designReleaseECNtbody tr').length;
			
			if(ecnTableLength < 7){
    			for(var tableIndex = ecnTableLength ; tableIndex < 7 ; tableIndex++){
					var table1rows = createDummyRowContent(tableIndex);
					$("#designReleaseECNtbody").append(table1rows);
    			}
			}
			
			var techDataTableLength = $('#designReleaseTechDatatbody tr').length;
			if(techDataTableLength < 7){
    			for(var tableIndex = techDataTableLength  ; tableIndex < 7 ; tableIndex++){
					var table2rows = createDummyRowContent(tableIndex);
					$("#designReleaseTechDatatbody").append(table2rows);
    			}
			}
			var ecnEdotTableLength = $('#designReleaseEcnEdottBody tr').length;
			if(ecnEdotTableLength < 9){
    			for(var tableIndex = ecnEdotTableLength  ; tableIndex < 9 ; tableIndex++){
					var table3rows = createDummyECNEDOTContent(tableIndex);
					$("#designReleaseEcnEdottBody").append(table3rows);
    			}
			}
			
			
			$("#ECNTemplate").modal('show');
		});
		
		function createDummyRowContent(tableIndex){
				var className = "";
					if(tableIndex % 2 != 0){
						className = "backGround8FF dummyClass";
					}
					var row = $('<tr>');
					row.attr('class',className);
					for(var i=0; i < 2; i++){
						row.append($('<td>').append('&nbsp;'));
					}
				
    		return row;
		}
		
		function createDummyECNEDOTContent(tableIndex){
					var className = "";
					if(tableIndex % 2 != 0){
						className = "backGround8FF dummyClass";
					}
					var row = $('<tr>');
					row.attr('class',className);
					for(var i=0; i < 4; i++){
						row.append($('<td>').append('&nbsp;'));
						
					}
				
    		return row;
		}
		$('#projectsEngDropDownEditECN1').change(function(){
			var selectedECR = $('#projectsEngDropDownEditECN1').val();
			var ecrID = "";
			var data = {
					ecrID : $('#projectsEngDropDownEditECN1').val()
			};
			var row ="";
			var selectOptions = "<option value='-1' selected>Please select</option>";
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/listEdotForSelectedECR',
			    data : data,
			    success: function(data){
			    	
			    	$.each(data, function(index, value){
			    		selectOptions = selectOptions+ "<option>"+value+"</option>";
			    	});
			    	$('#projectsEngDropDownEditECN2').selectpicker();
					 $("#projectsEngDropDownEditECN2")
				       .html(selectOptions)
				       .selectpicker('refresh');
					 
			    	
			    },
			    error : function(error)
			    {
			    	 $("#onlyDesignExistErrorLabel").html("There is an error in getting the EDOT list corresponding to ECR");
					 $("#onlyDesignIdExistError").modal('show');
					 return false;
			    }
			});
			
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/listECNForSelectedECR',
			    data : data,
			    success: function(data){
			    	$("#designReleaseECNtbody").empty();
			    	$.each(data, function(index, value){
			    		var className = "";
						if(index % 2 == 0){
							className = "backGround8FF";
						}
	                	row = row + "<tr class="+className+" id=tr_"+value +">";
	                	row = row + "<td><input type='radio' name='ecnRadioBtn' class='ecnTableCheckboxes' id='ECNImpIndex_"+value +"'  data-index ='"+index+ "' data-ecn= '"+value+"'></input></td>";
	    				row = row + "<td>"+ value+"</td></tr>";
			    		
				    	
			    	});
			    	$("#designReleaseECNtbody").empty().append(row);
			    	
			    	var ecnTableLength = $('#designReleaseECNtbody tr').length;
					
					if(ecnTableLength < 7){
		    			for(var tableIndex = ecnTableLength ; tableIndex < 7 ; tableIndex++){
							var table1rows = createDummyRowContent(tableIndex);
							$("#designReleaseECNtbody").append(table1rows);
		    			}
					}
					
					$('.ecnTableCheckboxes').click(function(){
						
						var row = $(this);
			    		populateTechData(row,$(this).data('ecn'));
		    	});
				
			    	
			    },
			    error : function(error)
			    {
			    	 $("#onlyDesignExistErrorLabel").html(error.responseText);
					 $("#onlyDesignIdExistError").modal('show');
					 return false;
			    }
			});
		});
		
		function populateTechData(row,ecnID){
			
    		var data = {
    				ecnID  :ecnID
    		};
    		$.ajax({
				method: "POST",
			    url: getContextPath()+'/listTDForSelectedECN',
			    data : data,
			    success: function(data){
			    	
			    	$.each(data, function(index, value){
			    		var className = "";
						if(index % 2 != 0){
							className = "backGround8FF";
						}
	                	row = row + "<tr class="+className+" id=tr_"+value +">";
	                	row = row + "<td><input type='radio' name='techData' class='TechDataTableRadioBtn' id='TechDataIndex_"+value +"' data-index ='"+index+ "' data-techdata= '"+value+"'></input></td>";
	    				row = row + "<td>"+ value+"</td></tr>";
	    				
			    	});
			    	
			    	$("#designReleaseTechDatatbody").empty().append(row);
			    	
			    	var ecnTableLength = $('#designReleaseTechDatatbody tr').length;
					
					if(ecnTableLength < 7){
		    			for(var tableIndex = ecnTableLength ; tableIndex < 7 ; tableIndex++){
							var table1rows = createDummyRowContent(tableIndex);
							$("#designReleaseTechDatatbody").append(table1rows);
		    			}
					}
			    	
			    },
			    error : function(error)
			    {
			    	 $("#onlyDesignExistErrorLabel").html("There is an error in getting the Technical Data corresponding to ECN");
					 $("#onlyDesignIdExistError").modal('show');
					 return false;
			    }
			});
		}
		
		$('#projectsEngDropDownEditECN2').change(function(){
			var selectedECR = $('#projectsEngDropDownEditECN2').val();
			var ecrID = "";
			var data = {
					edot : $('#projectsEngDropDownEditECN2').val()
			};
			var row ="";
			var index = 1;
			$.ajax({
				method: "GET",
			    url: getContextPath()+'/getLinkedECNandTD',
			    data : data,
			    success: function(data){
			    	$.each(data, function(index, value){
			    	
			    		var isRowalreadyExists = createNewEDOTECNTable(value.edotId,value.techData,value.ecnId);
			    		if(isRowalreadyExists == false){
			    			var ecnEdotTableLength = $('#designReleaseEcnEdottBody tr').length;
				    		var className = "";
							if(ecnEdotTableLength % 2 == 0){
								className = "backGround8FF";
							}
		                	row = row + "<tr class="+className+" id=tr_"+value.edotId  +">";
		                	row = row + "<td><input type='checkbox' class='ECNEDOTtemplateTableCheckboxes' id='ECREDOTIndex_"+value.edotId +"' data-index ='"+ecnEdotTableLength+ "' data-edot= '"+value.edotId+"' data-ecn= '"+value.ecnId+"' data-techdata= '"+value.techData+"'></input></td>";
							row = row + "<td class='centerAlign'>" + value.edotId + "</td><td class='centerAlign'>" +value.techData + "</td><td class='centerAlign'>"+ value.ecnId  + "</td></tr>";
			    		}
						
						
			    	});
			    	$("#designReleaseEcnEdottBody").append(row);
			    	
			    	var ecnEdotTableLength = $('#designReleaseEcnEdottBody tr').length;
					if(ecnEdotTableLength < 9){
		    			for(var tableIndex = ecnEdotTableLength  ; tableIndex < 9 ; tableIndex++){
							var table3rows = createDummyECNEDOTContent(tableIndex);
							$("#designReleaseEcnEdottBody").append(table3rows);
		    			}
					}
			    },
			    error : function(error)
			    {
			    	 $("#onlyDesignExistErrorLabel").html("There is an error in getting the ECR list");
					 $("#onlyDesignIdExistError").modal('show');
					 return false;
			    }
			});
		});
		
		$('#ECNTemplateLink').click(function(){
			var edot = $('#projectsEngDropDownEditECN2').val();
			var ecnID = "";
			var techData = "";
			
			if($('.ecnTableCheckboxes:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select ECN from ECN Table");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			if($('.TechDataTableRadioBtn:checked').length == 0)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select Techincal data from Technical Table");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			
			if(edot == -1)
			{
				 $("#onlyDesignExistErrorLabel").html("Please select EDOT from the dropdown");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			
			
			$(".ecnTableCheckboxes:checked").each(function()
			{
				ecnID = $(this).data('ecn');
			});
			
			$(".TechDataTableRadioBtn:checked").each(function()
			{
				techData = $(this).data('techdata');
			});
			var isRowExists = createNewEDOTECNTable(edot,techData,ecnID);
			if(isRowExists == false){
				var ecnEdotTableLength = $('#designReleaseEcnEdottBody tr').length;
				var className = "";
				if(ecnEdotTableLength % 2 != 0){
					className = "backGround8FF";
				}
				var row= "";
	        	row = row + "<tr class="+className+">";
				row = row + "<td><input type='checkbox' class='ECNEDOTtemplateTableCheckboxes' id='ECREDOTIndex_"+edot +"' data-index ='"+ecnEdotTableLength+ "' data-edot= '"+edot+"' data-ecn= '"+ecnID+"' data-techdata= '"+techData+"'></input></td>";
				row = row + "<td class='centerAlign'>" + edot + "</td><td class='centerAlign'>" +ecnID+ "</td><td class='centerAlign'>"+ techData + "</td></tr>";
				$("#designReleaseEcnEdottBody").append(row);
			}
			
			
			var ecnEdotTableLength = $('#designReleaseEcnEdottBody tr').length;
			if(ecnEdotTableLength < 9){
    			for(var tableIndex = ecnEdotTableLength  ; tableIndex < 9 ; tableIndex++){
					var table3rows = createDummyECNEDOTContent(tableIndex);
					$("#designReleaseEcnEdottBody").append(table3rows);
    			}
			}
		});
		
		function createNewEDOTECNTable(oldEdot,oldTechData,oldEcnId){
			var row = "";
			var index = 1;
			var isRowExists = false;
			$("#dsgnengEditEcnEdotRelease tr").each(function() 
					{ 
							var edot = $(this).find('td').eq(1).text();
					       var ecnId = $(this).find('td').eq(2).text();
					       var techData = $(this).find('td').eq(3).text();
			               
					       if(edot != "" && edot != " " && edot.indexOf("EDOT") > -1 ){
								var className = "";
								if(index % 2 != 0){
									className = "backGround8FF";
								}
			                	row = row + "<tr class="+className+">";
			    				row = row + "<td><input type='checkbox' class='ECNEDOTtemplateTableCheckboxes' id='ECRIndex_"+edot +"' data-index ='"+index+ "' data-edot= '"+edot+"' data-ecn= '"+ecnId+"' data-techdata= '"+techData+"'></input></td>";
			    				row = row + "<td class='centerAlign'>" + edot + "</td><td class='centerAlign'>" +ecnId+ "</td><td class='centerAlign'>"+ techData + "</td></tr>";
			    				index = index+1;
			                }
					       if(oldEdot == edot && oldTechData == techData && oldEcnId == ecnId){
					    	   isRowExists = true;
					       }
					});
			$("#designReleaseEcnEdottBody").empty().append(row);
				return isRowExists;	
		}
		
		$('#ECNTemplateUpdate').click(function(){
			var edot = [];
			var ecnID = [];
			var techData = [];
			
			if($('.ECNEDOTtemplateTableCheckboxes:checked').length ==0){
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one checkbox EDOT table");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			$(".ECNEDOTtemplateTableCheckboxes:checked").each(function(){
				edot.push($(this).data('edot'));
				ecnID.push($(this).data('ecn'));
				techData.push($(this).data('techdata'));
			});
			
			var data = {
					edot:edot,
					ecnID : ecnID,
					techData  :techData
					
			};
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/linkTDandEDOTtoECN',
			    data : data,
			    success: function(data){
			    	
			    	var res = "";
			    	$('#loadingModal').modal('hide');
			    	$('#designUpdateLabel').html('');
			    	if("Success" == data){
			    		$('#designUpdateLabel').css('color','green');
			    		res = "Updated Successfully";
			    	}else if("not updated" == data){
			    		$('#designUpdateLabel').css('color','red');
			    		res = "Not updated Successfully";
			    	}
			    	else{
			    		$('#designUpdateLabel').css('color','red');
			    		res = data;
			    	}
			    	$('#designUpdateLabel').html(res);
			    	$('#designUpdatedModal').modal('show');
			    },
			    error : function(error)
			    {
			    	var res="";
			    	 $('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Success" == error.responseText){
				    		$('#designUpdateLabel').css('color','green');
				    		res = "Updated Successfully";
				    	}else if("not updated" == error.responseText){
				    		$('#designUpdateLabel').css('color','red');
				    		res = "Not updated Successfully";
				    	}
				    	else{
				    		$('#designUpdateLabel').css('color','red');
				    		res = error.responseText;
				    	}
				    	
				    	$('#designUpdateLabel').html(res);
				    	$('#designUpdatedModal').modal('show');
			    
			    }
			});
		});
		
		$("#ECNTemplateRemove").click(function(){
			if($('.ECNEDOTtemplateTableCheckboxes:checked').length ==0){
				 $("#onlyDesignExistErrorLabel").html("Please select atleast one checkbox EDOT table");
				 $("#onlyDesignIdExistError").modal('show');
				 returnst =  false;
				 return false;
			}
			
			var edot = [];
			var ecnID = [];
			var techData = [];
			
			
			$(".ECNEDOTtemplateTableCheckboxes:checked").each(function(){
				edot.push($(this).data('edot'));
				ecnID.push($(this).data('ecn'));
				techData.push($(this).data('techdata'));
				
			});
			
			var data = {
					edot:edot,
					ecnID : ecnID,
					techData  :techData
					
			};
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/removeTDandEDOTtoECN',
			    data : data,
			    success: function(data){
			    	
			    	var res = "";
			    	$('#loadingModal').modal('hide');
			    	$('#designUpdateLabel').html('');
			    	if("Success" == data){
			    		
			    		$('#designUpdateLabel').css('color','green');
			    		res = "Removed Successfully";
			    		$('#designUpdateLabel').html(res);
				    	$('#designUpdatedModal').modal('show');
				    	
			    		$("#dsgnengEditEcnEdotRelease input[type='checkbox']:checked").parent().parent().remove();
						var ecnEdotTableLength = $('#designReleaseEcnEdottBody tr').length;
						if(ecnEdotTableLength < 9){
			    			for(var tableIndex = ecnEdotTableLength  ; tableIndex < 9 ; tableIndex++){
								var table3rows = createDummyECNEDOTContent(tableIndex);
								$("#designReleaseEcnEdottBody").append(table3rows);
			    			}
						}
			    	}else if("not updated" == data){
			    		$('#designUpdateLabel').css('color','red');
			    		res = "Remove Operation Failed";
			    		$('#designUpdateLabel').html(res);
				    	$('#designUpdatedModal').modal('show');
			    	}
			    	else{
			    		$('#designUpdateLabel').css('color','red');
			    		res = data;
			    		$('#designUpdateLabel').html(res);
				    	$('#designUpdatedModal').modal('show');
			    	}
			    	
			    },
			    error : function(error)
			    {
			    	var res="";
			    	 $('#loadingModal').modal('hide');
				    	$('#designUpdateLabel').html('');
				    	if("Success" == error.responseText){
				    		
				    		$('#designUpdateLabel').css('color','green');
				    		res = "Removed Successfully";
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
					    	
				    		$("#dsgnengEditEcnEdotRelease input[type='checkbox']:checked").parent().parent().remove();
							var ecnEdotTableLength = $('#designReleaseEcnEdottBody tr').length;
							if(ecnEdotTableLength < 9){
				    			for(var tableIndex = ecnEdotTableLength  ; tableIndex < 9 ; tableIndex++){
									var table3rows = createDummyECNEDOTContent(tableIndex);
									$("#designReleaseEcnEdottBody").append(table3rows);
				    			}
							}
				    	}else if("not updated" == error.responseText){
				    		$('#designUpdateLabel').css('color','red');
				    		res = "Remove Operation Failed";
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
				    	}
				    	else{
				    		$('#designUpdateLabel').css('color','red');
				    		res = error.responseText;
				    		$('#designUpdateLabel').html(res);
					    	$('#designUpdatedModal').modal('show');
				    	}
				    	
				    	
			    
			    }
			});
			
			/*$("#dsgnengEditEcnEdotRelease input[type='checkbox']:checked").parent().parent().remove();
			var ecnEdotTableLength = $('#designReleaseEcnEdottBody tr').length;
			if(ecnEdotTableLength < 9){
    			for(var tableIndex = ecnEdotTableLength  ; tableIndex < 9 ; tableIndex++){
					var table3rows = createDummyECNEDOTContent(tableIndex);
					$("#designReleaseEcnEdottBody").append(table3rows);
    			}
			}*/
		});
		$('#editEngECRcheckbox').click(function () {
			 if(this.checked){
		            $('.ECRtemplateTableCheckboxes:enabled').each(function(){
		              this.checked = true;
		            });
		        }else{
		             $('.ECRtemplateTableCheckboxes:enabled').each(function(){
		            	 this.checked = false;
		            });
		        }
			
		});
		
		function fixedHeaderScroll(){
			//Fixed header scroll.
			
			var table = $('#dsgnengrelease').DataTable( {
				/*destroy: true,*/
	    		"bPaginate": false,
	    		 "scrollY": 520,
	    	     "scrollX": true,
	    	     "ordering": false,
	    	     "bFilter": false,
	    	     "bInfo": false,
	    	     bRetrieve: true,
	    	       /* fixedHeader: {
	    	            header: true
	    				 
	    	        }*/
	    			} );
	    	$('#dsgnengrelease').resize();
	    	table.fixedHeader.adjust();
	    	//$(table).dataTable().fnAdjustColumnSizing();
		}
		
		$('.engsearch-btn').click(function(){
			var filterValue = $("#engSearchTerm").val();
			
			$("#dsgnengrelease tr").each(function(rowId, row) 
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

