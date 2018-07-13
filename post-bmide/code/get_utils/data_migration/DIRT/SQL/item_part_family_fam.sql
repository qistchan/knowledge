SELECT I.PITEM_ID, I2.PITEM_ID item2 FROM infodba.PITEM I, infodba.PITEM I2, infodba.PWORKSPACEOBJECT WS, infodba.PIMANRELATION IR, infodba.PFOLDER F, infodba.PCONTENTS CONT WHERE IR.RPRIMARY_OBJECTU=I.PUID AND IR.RSECONDARY_OBJECTU=WS.PUID AND WS.POBJECT_TYPE='Folder' 
AND WS.POBJECT_NAME='Family Members' AND WS.PUID=F.PUID AND F.PUID=CONT.PUID AND I2.PUID=PVALU_0 AND I.PITEM_ID IN (SELECT DISTINCT I.PITEM_ID FROM infodba.PITEM I, infodba.PWORKSPACEOBJECT WS WHERE I.PITEM_ID LIKE '%FAM%');