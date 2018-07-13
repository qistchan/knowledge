SELECT DISTINCT I.PITEM_ID FROM infodba.PITEM I, infodba.PWORKSPACEOBJECT WS, infodba.PIMANRELATION IR, infodba.PFOLDER F, infodba.PCONTENTS CONT WHERE IR.RPRIMARY_OBJECTU=I.PUID AND IR.RSECONDARY_OBJECTU=WS.PUID AND WS.POBJECT_TYPE='Folder' AND WS.POBJECT_NAME='Family Members' AND WS.PUID=F.PUID AND F.PUID NOT IN (SELECT DISTINCT CONT.PUID FROM infodba.PCONTENTS CONT); 