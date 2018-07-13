function getContextPath() {
		   dao.path = window.location.pathname.substring(0, window.location.pathname.indexOf("/",2));
		}


$(function()
{
	//$('#group').selectpicker();
	//$('#role').selectpicker();
	getContextPath();
	
	$('#roles').click(function(){
		//console.log($(this).data("groupid")+"------"+$(this).data("roleid"));
		dao.getGroups($(this).data("groupid"), $(this).data("roleid"));
	});
	
	$('#update').click(function(){
		dao.updateGrouproles();
	});
	
});


var dao = {
	path : "",
	grproles : "",
	getGrps : function()
	{
		$.ajax({
		method: "GET",
		    url: dao.path+'/getRoles',
		    success: function(data){
		     //console.log("success");
		     //console.log(data);
		     dao.grproles = data;
		     //console.log(data);
		     $select = $("#lgngroup");
		     $select.change(dao.getRole);
		     $(data).each(function(i, e)
		     {
			     $option = $("<option>", {"value" : e["group"], "text": e["group"]});
			     $select.append($option);
			     //console.log(e.group);
		     });
		     dao.getRole();
		    },
              error: function (error) {
               //console.log("failure");
               //console.log(error);
              }
		});
	},
	getRole : function()
	{
		$select = $("#lgnrole");
		$("#lgnrole option").remove();
		$(dao.grproles).each(function(i, e)
		{
		    if(e["group"] == $("#lgngroup").val())
			{
			     var roles = e["roles"];
			     //console.log(roles);
			     //roles = roles.split(",");
			     
			     $(roles).each(function(j, e1)
			     {
			    	 $option = $("<option>", {"value" : e1, "text": e1});
			         $select.append($option);
			             //console.log(e1);
			     });
			     
			}
		     
		});
	},
	getGroups :function($grpid, $roleid)
	{
		//console.log($grpid+"------"+$roleid);
		$('#loadingModal').modal('show');
		$("#group option").remove();
		$.ajax({
			method: "GET",
		    url: dao.path+'/getRoles',
		    success: function(data){
		    	//console.log("success");
		    	dao.grproles = data;
		    	//console.log(data);
		    	$select = $("#group");
		    	$select.change(dao.getRoles);
		    	$(data).each(function(i, e)
    			{
		    		$option = $("<option>", {"value" : e["group"], "text": e["group"]});
		    		$select.append($option);
		    		//console.log(e.group);
    			});
		    	$("#group").val($grpid);
		    	dao.getRoles();
		    	$("#role").val($roleid);
		    	/*$roleselect = $("#role");
				$("#role option").remove();
				$roleoption = $("<option>", {"value" : $roleid, "text": $roleid});
				$roleselect.append($roleoption);*/
				
		    	$('#loadingModal').modal('hide');
		    	$('#roledetails').modal('show');
		    },
              error: function (error) {
            	  //console.log("failure");
            	  //console.log(error);
              }
		});
	},
	getRoles : function()
	{
		//console.log("role change");
		$select = $("#role");
		$("#role option").remove();
    	$(dao.grproles).each(function(i, e)
		{
    		if(e["group"] == $("#group").val())
			{
    			var roles = e["roles"];
    			//console.log(roles);
    			//roles = roles.split(",");
    			
    			$(roles).each(function(j, e1)
    			{
    				$option = $("<option>", {"value" : e1, "text": e1});
            		$select.append($option);
            		//console.log(e1);
    			});
    			
			}
    		
		});
	},
	updateGrouproles : function()
	{
		$('#loadingModal').modal('show');
		$.ajax({
			method: "POST",
		    url: dao.path+'/updateGrouproles',
		    data : {
		    	"group" : $("#group").val(),
		    	"roles" : $("#role").val()
		    },
		    success: function(data){
		    	
		    	$('#roledetails').modal('show');
		    	$('#loadingModal').modal('hide');
		    },
              error: function (error) {
            	  //console.log("failure");
            	  $('#roleUpdateLabel').html("");
            	  if(error.responseText == "Success")
        		  {
            		  $('#roleUpdateLabel').html("Roles updated successfully");
            		  $('#rolesuccess').modal('show');
            		  
            		  
            			$.ajax({
	            				method: "POST",
	            			    url: dao.path+'/updateRoleGroupsession',
	            			    data : {
	            			    	"group" : $("#group").val(),
	            			    	"roles" : $("#role").val()
	            			    },
	            			    success: function(data){
	
	            			    },
	            	              error: function (error) {
	            	            	 // console.log("error");
	            	            	  if(error.responseText == "success")
	            	        		  {
	            	            		  window.location.reload();
	            	        		  }
	            	              }
            	              });
            			    
        		  }
            	  else
        		  {
            		  $('#roleUpdateLabel').html("Roles not changed");
            		  $('#rolesuccess').modal('show');
        		  }
            	  $('#loadingModal').modal('hide');
            	  //console.log(error);
              }
		});
	}
};