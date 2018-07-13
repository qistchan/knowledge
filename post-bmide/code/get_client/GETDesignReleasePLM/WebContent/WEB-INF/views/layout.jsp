<%@ taglib uri="http://tiles.apache.org/tags-tiles" prefix="tiles"%>  
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html>
<html>  
	<head>
		<meta http-equiv="X-UA-Compatible" content="IE=EDGE" />
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<link rel="stylesheet" href="<c:url value="/js/jquery-ui.css" />" > 
		<link href="<c:url value="/css/home.css" />" rel="stylesheet">
		<link href="<c:url value="/css/bootstrap/bootstrap.min.css" />" rel="stylesheet">
		<link href="<c:url value="/css/font-awesome.min.css" />" rel="stylesheet">
		<link href="<c:url value="/css/bootstrap/bootstrap-select.min.css" />" rel="stylesheet" />
		<link href="<c:url value="/css/easyui.css" />" rel="stylesheet">
		
		<link href="<c:url value="/css/datatables/jquery.dataTables.min.css" />" rel="stylesheet">
	<%-- 	<link href="<c:url value="/css/datatables/fixedHeader.dataTables.scss" />" rel="stylesheet"> --%>
		<link href="<c:url value="/css/datatables/fixedHeader.dataTables.min.css" />" rel="stylesheet">
	</head>  
	<body>  
		<!-- <script src="http://ajax.microsoft.com/ajax/jquery.validate/1.7/jquery.validate.js" type="text/javascript"></script> -->
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script> 
		<script src="<c:url value="/js/jquery.js" />"></script>
		<script src="<c:url value="/js/jqueryui.js" />"></script>
		<script src="<c:url value="/js/bootstrap/bootstrap.min.js" />"></script>
		<script src="<c:url value="/js/bootstrap/bootstrap-select.min.js" />"></script>
		<script src="<c:url value="/js/jQueryScript.js" />"></script>
		<script src="<c:url value="/js/jQueryScriptEdit.js" />"></script>
		<script src="<c:url value="/js/jQueryScriptEngEdit.js" />"></script>
		<script src="<c:url value="/js/jQueryScriptEngManEdit.js" />"></script>
		<script src="<c:url value="/js/jQueryScriptDesgnEdit.js" />"></script>
		<script src="<c:url value="/js/jQueryScriptPublish.js" />"></script>
		<script src="<c:url value="/js/jquery.qubit.js" />"></script>
		<script src="<c:url value="/js/moment.min.js" />"></script> 
		<script src="<c:url value="/js/gen-jquery.js" />"></script> 
		<script src="<c:url value="/js/jQueryScriptEngECRAss.js" />"></script>
		<script src="<c:url value="/js/jQueryScriptDashboard.js" />"></script>
		
		<script src="<c:url value="/js/datatables/jquery.dataTables.min.js" />"></script>
		<script src="<c:url value="/js/datatables/dataTables.fixedHeader.js" />"></script>
		<%-- <script src="<c:url value="/js/paging.js" /> "></script> --%>
		
        <div id="headercontainer" ><tiles:insertAttribute name="header2" /></div>
        <c:if test="${null != username}">
        	<div id="headercontainer" style="height: 30px;"><tiles:insertAttribute name="header" /></div>
         </c:if> 
        <div id="bodycontainer" style="height: 850px; vertical-align: middle;"><tiles:insertAttribute name="body" /></div>  
        <div style="clear:both"></div>
        <div id="footercontainer"><tiles:insertAttribute name="footer" /></div>  
	</body>  
</html>  