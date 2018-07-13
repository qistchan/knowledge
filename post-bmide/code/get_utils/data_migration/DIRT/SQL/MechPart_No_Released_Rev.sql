select distinct i.PITEM_ID, wso.POBJECT_NAME, u.pos_username, g.pname from infodba.pitem i, infodba.pworkspaceobject wso, infodba.ppom_application_object aom, infodba.ppom_group g,infodba.puser u 
where i.puid=wso.puid 
and wso.POBJECT_TYPE='GET6MechPart'
and i.puid=aom.puid and aom.rowning_groupu=g.puid and aom.rowning_useru=u.puid
and i.puid NOT IN (
select distinct i.PUID 
from infodba.pitem i, infodba.pworkspaceobject wso, infodba.pitemrevision ir, infodba.prelease_status_list rsl,infodba.preleasestatus rs 
where i.puid=wso.puid 
and i.puid=ir.ritems_tagu
and wso.pobject_type='GET6MechPart'
and ir.puid=rsl.puid 
and rsl.pvalu_0=rs.puid 
and rs.pname in ( 'GET6Released', 'Approved', 'GET6Baselined' )
);