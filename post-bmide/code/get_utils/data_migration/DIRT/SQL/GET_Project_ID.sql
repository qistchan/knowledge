select distinct i.PITEM_ID, ir.pitem_revision_id, wso.POBJECT_NAME, wso.pobject_type from infodba.pitem i, infodba.pworkspaceobject wso, infodba.pitemrevision ir where  i.puid=wso.puid and i.puid= ir.ritems_tagu and wso.pobject_type='GET6Project' and i.PITEM_ID NOT LIKE '%-SYSTEM';