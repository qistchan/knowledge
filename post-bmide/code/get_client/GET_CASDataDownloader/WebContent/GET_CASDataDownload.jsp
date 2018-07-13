<%@ page language="java" contentType="text/html; charset=windows-1256" 
    pageEncoding="windows-1256" %>
<% String message = (String)request.getAttribute("errorMsg");%> 
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd"> 
<html> 
<head> 
<meta http-equiv="Content-Type" content="text/html; charset=windows-1256" > 
<title>CAS Data Disposition</title> 
</head> 
<body bgcolor="#E6E6FA"> <font face = "verdana" size = "25"  >
<center>CAS Data Disposition</center> </font><br />
<style>
div {
    height: 150px;
    width: 50%;
    text-align: center;
}
</style>

<div></div>
<form action="GET_CASDataDownload" style="font-size:20pt;"><center> Item ID  <input type="text" name="ID" size="20" style="font-size:16pt;"/>
</center>
<p></p>
<center> <input type="submit" value="Download" size="25" style="font-size:18pt;"> </center>

</form> 
<script type="text/javascript">
    var msg = "<%=message%>";
    if(msg.length>6) {
    alert(msg);}
</script>
</body> 
</html>