<%@taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<%@taglib uri="http://www.springframework.org/tags" prefix="spring"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/functions" prefix="fn" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>

<html>
<head>
<title>TRANSPLM</title>


<script type="text/javascript">
	
		$(function() {
			$(document).ready(function(){
					 var agree= 'Agree';
					 var disagree ='Disagree';
			    		
				    	$("#dialog").dialog({
					    	 resizable: true,
					     	 width: '100%',
					     	 modal: true,
					     	open: function(event, ui) {
					            $('#agreeDialog').focus();
					        },
					        buttons:
					            [
					                {
					                    text: agree,
					                    click: function () {
					                    	$(this).dialog('close');
					                    	block();
								        
								        submitform();
											
					                    },
					                    id: 'agreeDialog'
					                },
					                {
					                    text: disagree,
					                    click: function () {
					                      	$( this ).dialog( "close" );
					                      	setTimeout (window.close, 100);
					                      	window.close();
								       		//setTimeout (window.close, 100);
								          }
					                }
					            ]
				    });

					var screenHeight = $('#screenWindowLogin').height();
					var finalheight = (screenHeight * 83) / 100;
					$('#dialog').css('min-height', finalheight);
			 }); 
	});
	function submitform()
	{
		document.loginform.submit();
	}
</script>
</head>
<body>

<form name="loginform" action="loginSSO" method="POST">
<div id="dialog" title="title">
  <p><div>
	
	</p>
</div>
</div>
</form>
</body>
</html>