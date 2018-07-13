$(document).ready(function() {	

		$('#projectsDesgnDropDownEdit').selectpicker();
		$('#templatesDropDownEdit').selectpicker();
		$('#scopesDropDownEdit').selectpicker();
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
    		
    		var checkBoxColumn = $('<td>');
    		var checkBoxInput = $("<input type='checkbox' class='editMainTableCheckboxes' name='designReleaseList[" + index +"].editChecked' id='check_"+value.bomLineItemId+"' data-edot= '"+value.designReleaseId+"' data-index ='"+index+"'  />" );
    		
    		var edotHiddenInput = $("<input type='hidden' id='edotHiddenInput"+index+"' value='"+value.designReleaseId+"'/>");
    		var promisedateHiddenInput = $("<input type='hidden' id='promiseHiddenInput"+index+"' value='"+value.designPromiseDate+"'/>");
    		var resourceHiddenInput = $("<input type='hidden' id='resourceHiddenInput"+index+"' value='"+value.designResource+"'/>");
    		var commentHiddenInput = $("<input type='hidden' id='commentHiddenInput"+index+"' value='"+value.designComment+"'/>");
    		
    		
    		checkBoxColumn.append(checkBoxInput);
    		checkBoxColumn.append(edotHiddenInput);
    		checkBoxColumn.append(promisedateHiddenInput);
    		checkBoxColumn.append(resourceHiddenInput);
    		checkBoxColumn.append(commentHiddenInput);
    		
    		
    		var bomLineItemIdColumn = $('<td>');
    		var bomLineItemIdInput = $("<input type='hidden' class='bomLineHiddenItemId' id='itemId"+index+"' name='designReleaseList[" + index +"].bomLineItemId' value='" + value.bomLineItemId + "'>"+ value.bomLineItemId +"</input>");
    		bomLineItemIdColumn.append(bomLineItemIdInput);
    		
    		var descriptionColumn = $('<td>', {"align" : "left"});
    		var descriptionInput = $("<input type='hidden' name='designReleaseList[" + index +"].description' value='" + value.description + "'>" + value.description +"</input>");
    		descriptionColumn.append(descriptionInput);
    		
    		var edotColumn = $('<td>');
    		var edotInput = $("<input type='hidden' class='edotHiddenId' id='edotId"+index+"' name='designReleaseList[" + index +"].edot' value='" + value.designReleaseId + "'>"+ value.designReleaseId +"</input>");
    		edotColumn.append(edotInput);
    	
    		
    		var designRequiredDateColumn = $("<td  id=designRequiredDateTD_"+index+">");
    		var designRequiredDateInput = $("<input type='hidden' class='designRequiredDateInput' id=designRequiredDate_"+index+" name='designReleaseList[" + index +"].designRequiredDate' value='" + value.designRequiredDate + "'>" + value.designRequiredDateLabel +"</input>");
    		designRequiredDateColumn.append(designRequiredDateInput);
    		
    		var designPromiseDateColumn = $('<td>');
    		var designPromiseDateInput = $("<input type='hidden' readonly name='designPromiseDate' id=designPromiseDate_"+index+" value='" + value.designPromiseDate + "'>" + value.designPromiseDateLabel +"</input>");
    		designPromiseDateColumn.append(designPromiseDateInput);
    		
    		var designActualDateColumn = $('<td>');
    		var designActualDateInput = $("<input type='hidden' name='designReleaseList[" + index +"].designActualDate' value='" + value.designActualDate + "'>" + value.designActualDateLabel +"</input>");
    		designActualDateColumn.append(designActualDateInput);
    		
    		/*var subgrps = value.designComponentNo;
    		subgrps = subgrps.split(".");
    		
    		var designComponentNoColumn = $('<td>');
    		var designComponentNoInput = $("<input type='hidden' name='designReleaseList[" + index +"].designComponentNo' id=subgroup_"+index+" value='" + subgrps[0] + "'>" + subgrps[0] +"</input>");
    		designComponentNoColumn.append(designComponentNoInput);*/
    		
    		var designResourceColumn = $('<td id=designresource_'+index+'>');
    		var designResourceInput = $("<input type='hidden' name='designReleaseList[" + index +"].designResource' id=designResource_"+index+" value='" + value.designResource + "'>" + value.designResource +"</input>");
    		designResourceColumn.append(designResourceInput);
    		
    		var designECNColumn = $('<td>');
    		var designECNInput = $("<input type='hidden' name='designReleaseList[" + index +"].designECN' value='" + value.designECN + "'>" + value.designECN +"</input>");
    		designECNColumn.append(designECNInput);
    		
    		var designCommentColumn = $('<td>');
    		var designCommentInput = $("<textarea rows='2' cols='35' style='display:none' name='designReleaseList[" + index +"].designComment' id=designcomment_"+index+" >" + value.designComment +"</textarea><span id=descmnt"+index+" class='cmntWrapper'>"+ value.designComment+"</span>");
    		designCommentColumn.append(designCommentInput);
    		
    		var statusColumn = $('<td>');
    		var statusInput = $("<input type='hidden' name='designReleaseList[" + index +"].status' value='" + value.status + "'>" + value.status +"</input>");
    		statusColumn.append(statusInput);
    		
    		var stateColumn = $('<td>');
    		var stateInput = $("<input type='hidden' name='designReleaseList[" + index +"].state' value='" + value.state + "'>"+ +"</input>");
    		stateColumn.append(stateInput);
    		var divTag = $('<div/>').attr('id', 'circle');
    		divTag.css("background-color",value.state);
    		stateColumn.append(divTag);
    		
    		var designReleaseIdColumn = $('<td>');
    		var designReleaseIdInput = $("<input type='hidden' id='designReleaseId"+index+"' name='designReleaseList[" + index +"].designReleaseId' value='" + value.designReleaseId + "'/>");
    		designReleaseIdColumn.append(designReleaseIdInput);
    		
    		var designECRColumn = $('<td>');
    		var designECRInput = $("<input type='hidden' name='designReleaseList[" + index +"].engrECR' value='" + value.engrECR + "'>" + value.engrECR +"</input>");
    		designECRColumn.append(designECRInput);
    		
    		var designTDColumn = $('<td>');
    		var designTDInput = $("<input type='hidden' name='designReleaseList[" + index +"].technicalData' value='" + value.technicalData + "'>" + value.technicalData +"</input>");
    		designTDColumn.append(designTDInput);
    		
    		var designOrgProjectColumn = $('<td>');
    		var designOrgProjectInput = $("<input type='hidden' name='designReleaseList[" + index +"].designOrgProject' value='" + value.designOrgProject + "'>" +  +"</input>");
    		designOrgProjectColumn.append(designOrgProjectInput);
    		
    		var mainGroupColumn = $('<td>',{"style" : "text-align:left"});
    		var mainGroupInput = $("<input type='hidden' name='designReleaseList[" + index +"].mainGroup' value='" + value.mainGroup + "'>" + value.mainGroup +"</input>");
    		mainGroupColumn.append(mainGroupInput);
    		
    		checkBoxColumn.append(designReleaseIdInput);
    		row.append(checkBoxColumn);
    		row.append(bomLineItemIdColumn);
    		row.append(descriptionColumn);
    		row.append(edotColumn);
    		row.append(designRequiredDateColumn);
    		row.append(designPromiseDateColumn);
    		row.append(designActualDateColumn);
    		/*row.append(designComponentNoColumn);*/
    		row.append(mainGroupColumn);
    		row.append(designOrgProjectColumn);
    		row.append(designResourceColumn);
    		row.append(designECRColumn);
    		row.append(designECNColumn);
    		row.append(designTDColumn);
    		row.append(designCommentColumn);
    		row.append(statusColumn);
    		row.append(stateColumn);
    		
    		
    		
    		return row;
		}
		
		$('.projectInfoDesgnEditBtn').click(function(){
			$("#project_edit_id").html($("#projectsDesgnDropDownEdit").val());
			$('#projectInfoEdit').modal('show');
		});
		$('.projectRefresh').click(function(){
			$('#projectsDesgnDropDownEdit').change();
		});
		
		$("#updateDesignReleaseEdit").on("click", function()
		{
			var edot=[], promisedt=[], comments = [], resource = []/*,subgrp = []*/;
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
					promisedt.push($("#designPromiseDate_"+$(this).data('index')).val());
					comments.push($("#designcomment_"+$(this).data('index')).val()); 
					resource.push($("#designResource_"+$(this).data('index')).val());
					
					if(($("#designPromiseDate_"+$(this).data('index')).val() == "") || ($("#designPromiseDate_"+$(this).data('index')).val() == null))
					{
						//alert("Please fill the Comments");
						$("#onlyDesignExistErrorLabel").html("Please fill the Promise date");
						$("#onlyDesignIdExistError").modal('show');
						returnst =  false;
						return false;
					}
					
			});
			
			
			
			if(!returnst)
			{
				return returnst;
			}
			
			var data ={
					edot : edot,
					promisedt : promisedt,
					comments : comments,
					resource : resource,
					action : "updateDC"
			};
			
			//console.log(data);
			$.ajax({
				method: "POST",
			    url: getContextPath()+'/updateDesign',
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
				    		//$('#designUpdateLabel').html("Updated Successfully");
				    		res = "Updated Successfully";
				    	}else if("not updated" == error.responseText){
				    		$('#designUpdateLabel').css('color','red');
				    		res = "Not updated Successfully";
				    	}
				    	else{
				    		$('#designUpdateLabel').css('color','red');
				    		res = error.responseText;
				    	}
				    	/*else{
				    		$('#designUpdateLabel').css('color','red');
				    		$('#designUpdateLabel').html("Not updated Successfully");
				    	}*/
				    	$('#designUpdateLabel').html(res);
				    	$('#designUpdatedModal').modal('show');
			    }
			});
		});
		
		$('.designUpdateOk').click(function(){
			$('#designUpdatedModal').modal('hide');
			$('#projectsDesgnDropDownEdit').change();
		});
		
		$('#projectsDesgnDropDownEdit').change(function(){
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
		    	$("#engrDesgnProductLine").html('');
		    	$(".projectInfoEditBtn").hide();
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
			    	$(".projectInfoDesgnEditBtn").show();
			    	$(".projectRefresh").show();
			    	$("#designSearchTerm").val("");
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
							    	$("#dsgnrelease tbody").append(row);
							    	resetScopeDropdown();
						    	});
					    	}else{
					    		console.log("empty");
					    		$("#dsgnrelease tbody").empty();
						    	for(var i=0 ; i<11 ;i++){
						    		var row = createDesignReleaseEditEmptyTableRow(i);
							    	$("#dsgnrelease tbody").append(row);
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
					    	$("#engrDesgnProductLine").html('');
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
					    			$("#engrDesgnProductLine").html(value[0]);
					    		}
					    	});
					    	
					    	
					    	$('.editMainTableCheckboxes').click(function(){
					    		
					    		var row = $(this);
					    		//console.log($(this).data('index'));
					    		editDesgnDetails(row, $(this).data('index'));
					    		fixedHeaderScroll();
					    	});

					    	//Fixed header scroll.
					    	var table = $('#dsgnrelease').DataTable( {
					    		
					    		"bPaginate": false,
					    		 "scrollY": 585,
					    	     "scrollX": true,
					    	     
					    	     "ordering": false,
					    	     "bFilter": false,
					    	     "bInfo": false,
					    	      bRetrieve: true,
					    	     
					    	       
					    			} );
					    	$('#dsgnrelease').resize();
					    	table.fixedHeader.adjust();
					    }
			    	});
			    }
			});
		});
		
		
		
		function editDesgnDetails(clickedRow, index){
			    	
				//console.log(clickedRow);
		    	var checked = clickedRow.prop('checked');
		    	var index = index;
			    //console.log(checked);
		    	
				if(checked){
					
					var design_requiredDate = clickedRow.parent().parent().children("td:eq(4)").html();
					var design_requiredDateVal = clickedRow.parent().parent().children("td:eq(4)").children().val();
					
					var design_promisedate = clickedRow.parent().parent().children("td:eq(5)").html();
					
					//var design_comment = clickedRow.parent().parent().children("td:eq(10)").html();
					var design_promisedateVal = clickedRow.parent().parent().children("td:eq(5)").children().val();
					//var design_commentVal = clickedRow.parent().parent().children("td:eq(10)").children().val();
					
					$("#designcomment_"+index).show();
					//design_comment = design_comment.substring(0,design_comment.lastIndexOf(">")+1);
					design_promisedate = design_promisedate.substring(0,design_promisedate.lastIndexOf(">")+1);
					
					
					//design_comment = design_comment.replace('style="display:none"','style="display:inline"');
					design_promisedate = design_promisedate.replace('type="hidden"','type="text"');										
					design_promisedateVal = design_promisedateVal.substring(0,design_promisedateVal.length);
					
					
					//design_commentVal = design_commentVal.substring(0,design_commentVal.length-1);
					clickedRow.parent().parent().children("td:eq(5)").html('');
					//clickedRow.parent().parent().children("td:eq(10)").html('');
					
					
					clickedRow.parent().parent().children("td:eq(5)").append(design_promisedate);
					//clickedRow.parent().parent().children("td:eq(10)").append(design_comment);
					
					
					clickedRow.parent().parent().children("td:eq(5)").children().attr('value',design_promisedateVal).css('width','100px');
					//clickedRow.parent().parent().children("td:eq(10)").children().attr('value',design_commentVal).css('width','40px');
					$('#designPromiseDate_'+index).datepicker({changeMonth: true, changeYear: true, dateFormat: 'mm/dd/yy', defaultDate: new Date(design_requiredDateVal)});
					$('#descmnt'+index).hide();
				}else{
					var design_promisedate = clickedRow.parent().parent().children("td:eq(5)").html();
					//var design_comment = clickedRow.parent().parent().children("td:eq(10)").html();
					var design_promisedateVal = clickedRow.parent().parent().children("td:eq(5)").children().val();
					//var design_commentVal = clickedRow.parent().parent().children("td:eq(10)").children().val();
					$("#designcomment_"+index).hide();
					design_promisedate = design_promisedate.replace('type="text"','type="hidden"')+$('#promiseHiddenInput'+index).val()+"</input>";
					//design_comment = design_comment.replace('style="display:inline"','style="display:none"')+$('#commentHiddenInput'+index).val()+"</textarea>";
					
					
					clickedRow.parent().parent().children("td:eq(5)").html('');
					//clickedRow.parent().parent().children("td:eq(10)").html('');
					
					clickedRow.parent().parent().children("td:eq(5)").append(design_promisedate);
					//clickedRow.parent().parent().children("td:eq(10)").append(design_comment);

					
					
					clickedRow.parent().parent().children("td:eq(5)").children().attr('value',$('#promiseHiddenInput'+index).val());
					//clickedRow.parent().parent().children("td:eq(10)").children().attr('value',$('#commentHiddenInput'+index).val());
					
					$('#designPromiseDate_'+index).removeClass('hasDatepicker');
					$('#descmnt'+index).show();
				}
				
			}
		
			$('#editdesignallcheckbox').change(function () {
				//console.log("design");
			    $('tbody tr td input[type="checkbox"]').prop('checked', $(this).prop('checked'));
			});
			
			$('#editdesignallcheckbox').click(function () {
				
				 if(this.checked){
			            $('.editMainTableCheckboxes').each(function(){
			               
			               this.checked = true;
			               var row = $(this);
			               $('#designPromiseDate_'+$(this).data('index')).removeClass('hasDatepicker');
			               editDesgnDetails(row, $(this).data('index'));
			               fixedHeaderScroll();
			            });
			        }else{
			             $('.editMainTableCheckboxes').each(function(){
			                this.checked = false;
			                var row = $(this);
			                $('#designPromiseDate_'+$(this).data('index')).removeClass('hasDatepicker');
			                editDesgnDetails(row, $(this).data('index'));
			                fixedHeaderScroll();
			            });
			        }
				
			});
			
			
			$('.designsearch-btn').click(function(){
				var filterValue = $("#designSearchTerm").val();
				
				$("#dsgnrelease tr").each(function(rowId, row) 
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
			
			function fixedHeaderScroll(){
				//Fixed header scroll.
				
				var table = $('#dsgnrelease').DataTable( {
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
		    	$('#dsgnrelease').resize();
		    	table.fixedHeader.adjust();
		    	
			}
	    
});

