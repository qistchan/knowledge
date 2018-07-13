select distinct i.PITEM_ID, ir.pitem_revision_id, wso.POBJECT_NAME, wso.pobject_type from infodba.pitem i, infodba.pworkspaceobject wso, infodba.pitemrevision ir where  i.puid=wso.puid and i.puid= ir.ritems_tagu  and wso.pobject_type='GET6MechPart' and ( i.PITEM_ID NOT LIKE '%-CTL' AND i.PITEM_ID NOT LIKE '%K_' AND i.PITEM_ID NOT LIKE '%P_' AND i.PITEM_ID NOT LIKE '%P__'AND i.PITEM_ID NOT LIKE '%P___' AND i.PITEM_ID NOT LIKE '%G%' AND i.PITEM_ID NOT LIKE '%-DLIN' AND i.PITEM_ID NOT LIKE '%-FAM');