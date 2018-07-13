select distinct i.pitem_id, u.pos_username, g.pname from infodba.pitem i, infodba.ppom_application_object aom, infodba.ppom_group g, infodba.pworkspaceobject wso, infodba.puser u where i.puid=aom.puid and i.puid=wso.puid and wso.pobject_type like 'GET6%' and aom.rowning_groupu=g.puid and aom.rowning_useru=u.puid and g.pname not in ('ADMIN','EXTERNAL SUPPLIERS','TRANSPORTATION','ENGINEERING', 'PRODUCT MANAGEMENT MAIN', 'PROGRAM MANAGEMENT MAIN','Application Administrator','Data Administrator','Compliance','Digital Engineering','Electrical COE','Engine','Engineering Admin','Engineering Support','GETSA Engineering','Global Lab','Mechanical COE','Off Highway Vehicle (OHV)','Principal Engineering',' Safety',' and Cyber Security','Product Definition','Propulsion','Services Technologies','Software','Technical Publications','Transportation Systems','Underground Mining','Product Management','Program Management', 'SUPPLY CHAIN','Advance Manufacturing', 'Operations','SERVICES','Global Producibility','Methods','Operations');