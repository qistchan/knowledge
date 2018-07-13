<?xml version="1.0" encoding="utf-8" ?>

<xsl:stylesheet version="1.0"
           xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
           xmlns:plm="http://www.plmxml.org/Schemas/PLMXMLSchema"
           xmlns="urn:schemas-microsoft-com:office:spreadsheet"
           xmlns:o="urn:schemas-microsoft-com:office:office"
           xmlns:x="urn:schemas-microsoft-com:office:excel"
           xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"
           xmlns:html="http://www.w3.org/TR/REC-html40" >


  <!-- Define global parameters -->
  <xsl:param name="primaryOccRef" select="/plm:PLMXML/plm:ProductView/@primaryOccurrenceRef"/>
  <xsl:param name="rootProductID" select="substring-after(/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$primaryOccRef]/@instancedRef,'#')"/>
  <xsl:param name="report_date" select="/plm:PLMXML/@date" />

  <!-- Note: the variable below can be set as "display:all" or "display:none" -->
  <!--       to expand all or none internal links at teh report generation" -->
  <xsl:param name="linkDisplayStatus" select="'display:none'"/>

  <!-- Define key functions -->
  <xsl:key name="product" 	    match="plm:ProductRevision" use="@id"/>
  <xsl:key name="design" 	    match="plm:DesignRevision" use="@id"/>
  <xsl:key name="part" 	        match="plm:PartRevision" use="@id"/>
  <xsl:key name="dataset" 	    match="plm:Dataset" use="@id"/>
  <xsl:key name="form" 		    match="plm:Form" use="@id"/>
  <xsl:key name="folder" 		match="plm:Folder" use="@id"/>
  <xsl:key name="occurrence" 	match="plm:Occurrence" use="@id"/>
  <xsl:key name="unit" 	        match="plm:Unit" use="@id"/>

  <!-- Method for translation -->
  <xsl:output method="xml" version="1.0" indent="yes" />

  <xsl:strip-space elements="*"/>

  <!-- ******************** -->
  <!-- Header and structure -->
  <!-- ******************** -->
  <xsl:template name="BOMReportHeader">
    <xsl:param name="currentElement"/>
    <xsl:param name="parentOccurrenceID"/>
    <xsl:param name="title"/>
    <xsl:processing-instruction name="mso-application">progid="Excel.Sheet"</xsl:processing-instruction>
    
    <Workbook xmlns="urn:schemas-microsoft-com:office:spreadsheet"
        xmlns:o="urn:schemas-microsoft-com:office:office"
        xmlns:x="urn:schemas-microsoft-com:office:excel"
        xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"
        xmlns:html="http://www.w3.org/TR/REC-html40">

      <Styles>
        <Style ss:ID="heading1">
          <Font ss:Color="#000000" ss:Size="20" ss:FontName="Arial" ss:Bold="1"/>
          <Interior ss:Color="#C0C0C0" ss:Pattern="Solid"/>
        </Style>
        <Style ss:ID="heading2">
          <Font ss:Color="#000000" ss:Size="12" ss:FontName="Arial" ss:Bold="1"/>
          <Interior ss:Color="#C0C0C0" ss:Pattern="Solid"/>
        </Style>
        <Style ss:ID="heading3">
          <Alignment ss:Horizontal="Left"/>
          <Font ss:Color="#000000" ss:Size="10" ss:FontName="Arial" ss:Bold="1"/>
          <Interior ss:Color="#CCCCFF" ss:Pattern="Solid"/>
        </Style>
        <Style ss:ID="cell_data">
          <Font ss:Color="#000000"/>
          <Interior ss:Color="#FFFFCC" ss:Pattern="Solid"/>
        </Style>
      </Styles>

      <Worksheet ss:Name="Sheet1">

        <Table>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="60" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="60" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="100" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="100" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
          <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>

          <Row></Row>
          <Row>
            <Cell ss:StyleID="heading1">
              <Data ss:Type="String">
                <xsl:value-of select="$title"/>
              </Data>
            </Cell>
            <Cell ss:StyleID="heading1"></Cell>
          </Row>
          <Row></Row>
          <Row>
            <Cell ss:StyleID="heading2">
              <Data ss:Type="String">
                Revision Rule = <xsl:value-of select="/plm:PLMXML/plm:RevisionRule/@name"/>
              </Data>
            </Cell>
            <Cell ss:StyleID="heading2"></Cell>
          </Row>
          <Row></Row>
          <Row>
            <Cell ss:StyleID="heading2">
              <Data ss:Type="String">
                Date: <xsl:value-of select="$report_date"/>
              </Data>
            </Cell>
            <Cell ss:StyleID="heading2"></Cell>
          </Row>
          <Row></Row>
          <xsl:call-template name="generateReportData">
            <xsl:with-param name="currentElement" select="$currentElement"/>
            <xsl:with-param name="parentOccurrenceID" select="$parentOccurrenceID"/>
          </xsl:call-template>

        </Table>
      </Worksheet>
    </Workbook>

  </xsl:template>


   <!-- **************** Top Level data element **************** -->
  <xsl:template match="/">
    <xsl:variable name="topProductId" select="key('product',$rootProductID)"/>
    <xsl:variable name="topDesignId" select="key('design',$rootProductID)"/>
    <xsl:variable name="topPartId" select="key('part',$rootProductID)"/>
    <xsl:choose>
      <xsl:when test="$topProductId != ''" >
         <xsl:call-template name="generateReportPage">
            <xsl:with-param name="currentElement" select="$topProductId"/>
            <xsl:with-param name="parentOccurrenceID" select="''"/>
          </xsl:call-template>
      </xsl:when>
      <xsl:when test="$topDesignId != ''" >
          <xsl:call-template name="generateReportPage">
            <xsl:with-param name="currentElement" select="$topDesignId"/>
            <xsl:with-param name="parentOccurrenceID" select="''"/>
          </xsl:call-template>
      </xsl:when>
      <xsl:when test="$topPartId != ''" >
          <xsl:call-template name="generateReportPage">
            <xsl:with-param name="currentElement" select="$topPartId"/>
            <xsl:with-param name="parentOccurrenceID" select="''"/>
          </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:template>

  <!-- *** Create seperate page for each process and to be linked from its parent **** -->
  <xsl:template name="generateReportPage">
    <xsl:param name="currentElement"/>
    <xsl:param name="parentOccurrenceID"/>
    <xsl:choose>
      <!-- For the root process, we output to the top level report -->
      <xsl:when test="$rootProductID=$currentElement/@id">
        <xsl:call-template name="BOMReportHeader">
          <xsl:with-param name="currentElement" select="$currentElement"/>
          <xsl:with-param name="parentOccurrenceID" select="$parentOccurrenceID"/>
          <xsl:with-param name="title" select="'PS(BOM) Report'"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
    <!--<xsl:for-each select="$currentElement/plm:Occurrence">
    <xsl:call-template name="generateReportPage">
      <xsl:with-param name="currentElement" select="key('product', @ref)"/>
      <xsl:with-param name="parentOccurrenceID" select="@id"/>
        </xsl:call-template>
  </xsl:for-each>-->
  </xsl:template>

  <!-- ************ generate report data ************* -->
  <xsl:template name="generateReportData">
    <xsl:param name="currentElement"/>
    <xsl:param name="parentOccurrenceID"/>
    <xsl:call-template name="generateCurrentProductData">
      <xsl:with-param name="prtele" select="$currentElement"/>
      <xsl:with-param name="parentID" select="$parentOccurrenceID"/>
    </xsl:call-template>

    <xsl:call-template name="generateChildProduct">
      <xsl:with-param name="currentElement" select="$currentElement"/>
      <xsl:with-param name="parentID" select="$parentOccurrenceID"/>
    </xsl:call-template>
  </xsl:template>

  <!-- ************ generate current product data ************* -->
  <xsl:template name="generateCurrentProductData">
    <xsl:param name="prtele"/>
    <xsl:param name="parentID"/>

    <Row></Row>

    <!--  Modify_Here_Column_Parent -->
    <Row>
		
	<Cell ss:StyleID="heading3">
        <Data ss:Type="String">Level</Data>
      </Cell>
	  
      <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Part Number (Item ID)</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Revision</Data>
      </Cell>
	  
      <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Part Name</Data>
      </Cell>
	  
	   <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Quantity</Data>
      </Cell>
	  
	   <Cell ss:StyleID="heading3">
		  <Data ss:Type="String">FIND_NO</Data>
      </Cell>
	  
	   <Cell ss:StyleID="heading3">
		  <Data ss:Type="String">PACK_COUNT</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">PARENT/Rev-NAME</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">UOM</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">STRUCTURE_CODE</Data>
      </Cell>
	  
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">STOCK_MATERIAL</Data>
      </Cell>
	  
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">STOCK_MATERIAL_NAME</Data>
      </Cell>
	  
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">STOCK_MATERIAL_QTY</Data>
      </Cell>
	  
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Owner</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Item Revision Owning Group</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Last Modifying User</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Last Modified Date</Data>
      </Cell>
	  
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">PROJECT_ID</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">ENG_MAKE_BUY</Data>
      </Cell>
	  
	 <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Release Status</Data>
      </Cell>

	<Cell ss:StyleID="heading3">
        <Data ss:Type="String">Project M/B
		</Data>
      </Cell>
	  
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">ITEM_TYPE
	 </Data>
      </Cell>
    
    </Row>
	
    <xsl:variable name="itemID" select="$prtele/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
    <xsl:variable name="itemRev" select="$prtele/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>
    <xsl:variable name="itemName" select="$prtele/plm:UserData/plm:UserValue[@title='object_name']/@value"/>
    <xsl:variable name="itemDesc" select="$prtele/plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
    <xsl:variable name="creationDate" select="$prtele/plm:UserData/plm:UserValue[@title='creation_date']/@value"/>
    <xsl:variable name="modifiedDate" select="$prtele/plm:UserData/plm:UserValue[@title='last_mod_date']/@value"/>
	<xsl:variable name="itemType" select="$prtele/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
	<xsl:variable name="engMakeBuy" select="$prtele/plm:UserData/plm:UserValue[@title='get6EngMB']/@value"/>
	
	<!--xsl:variable name="uomTag" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='bl_item_uom_tag']/@value" /-->

    <xsl:variable name="releaseStatusRef" select="$prtele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
    <xsl:variable name="releaseStatus" select="/plm:PLMXML/plm:ReleaseStatus[@id=$releaseStatusRef]" />
    <xsl:variable name="releaseStatusName" select="$releaseStatus/@name" />
    <xsl:variable name="releasedDate" select="$releaseStatus/@dateReleased"/>

    <xsl:variable name="userRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
    <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId" />
	
	<xsl:variable name="groupRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
    <xsl:variable name="groupName" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]/@name" />

    <xsl:variable name="modUserRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
    <xsl:variable name="modUserName" select="/plm:PLMXML/plm:User[@id=$modUserRef]/@userId" />

    <xsl:variable name="formRef" select="$prtele/plm:AssociatedForm[@role='IMAN_master_form']/@formRef"/>
    <xsl:variable name="form" select="key('form',substring-after($formRef,'#'))"/>
	<xsl:variable name="projectId" select="$prtele/plm:UserData/plm:UserValue[@title='project_ids']/@value"/>
	
	<!-- getmanufacturing attributes form-->
	<xsl:variable name="itemRef" select="substring-after($prtele/@masterRef,'#')"/>
	<xsl:variable name="ServformItemRef" select="key('form',substring-after(/plm:PLMXML/plm:Design[@id=$itemRef]/plm:AssociatedForm[@role='GET6PartOrgRelation']/@formRef,'#'))"/>
	<xsl:variable name="makeBuyMfg" select="$ServformItemRef/plm:UserData/plm:UserValue[@title='get6MakeBuy']/@value"/>
	<xsl:variable name="strCode" select="$ServformItemRef/plm:UserData/plm:UserValue[@title='get6StructureCode']/@value"/>
	<xsl:variable name="stockMatQuan" select="$ServformItemRef/plm:UserData/plm:UserValue[@title='get6StockMtrlConsumedQty']/@value"/>
	
	<!--get uom tag details-->
	<xsl:variable name="uomTagRef" select="key('unit',substring-after(/plm:PLMXML/plm:Design[@id=$itemRef]/plm:UserData/plm:UserValue[@title='uom_tag']/@dataRef,'#'))"/>
	<xsl:variable name="uomTag" select = "$uomTagRef/plm:UserData/plm:UserValue/@value"/>"
    
	<!-- get stockmaterial type-->
	<xsl:variable name="stockMaterialRef" select="$ServformItemRef/plm:UserData/plm:UserValue[@title='get6StockMaterial']/@dataRef"/>
	<xsl:variable name="stockMaterialRef1" select = "substring-after($stockMaterialRef,'#')"/>
	<xsl:variable name="stockMatlId" select="/plm:PLMXML/plm:Design[@id=$stockMaterialRef1]/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
	<xsl:variable name="stockMatlName" select="/plm:PLMXML/plm:Design[@id=$stockMaterialRef1]/plm:UserData/plm:UserValue[@title='object_name']/@value"/>
	
    <Row>
     
	 <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
         <xsl:text>0</xsl:text>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemID"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemRev"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemName"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:text></xsl:text>
            </Data>
       </Cell>
      <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:text></xsl:text>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:text>1</xsl:text>
			</Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:text></xsl:text>
            </Data>
       </Cell>
	   
	  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:choose>
                  <xsl:when test="$uomTag!=''">
                    <xsl:value-of select="$uomTag"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>Each</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
            </Data>
          </Cell>
		  
		  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:value-of select="$strCode"/>
            </Data>
         </Cell>
		 
		 <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$stockMatlId"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
				<xsl:value-of select="$stockMatlName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$stockMatQuan"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$userName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$groupName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$modUserName"/>
        </Data>
      </Cell>
	  
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$modifiedDate"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$projectId"/>
        </Data>
      </Cell>
	  
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:value-of select="$engMakeBuy"/>
            </Data>
       </Cell>
	   
	    <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$releaseStatusName"/>
        </Data>
      </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$makeBuyMfg"/>
            </Data>
       </Cell>
	   
	    <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$itemType"/>
            </Data>
       </Cell>
	 </Row>

</xsl:template>

  <!-- *************** Child Product **************** -->
  <xsl:template name="generateChildProduct">
    <xsl:param name="currentElement"/>
    <xsl:param name="parentID"/>
    <xsl:choose>
      <xsl:when test="/plm:PLMXML/plm:ProductView/plm:Occurrence">
		<xsl:variable name="roe" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$primaryOccRef]" />
        <xsl:variable name="occRefs" select="$roe/@occurrenceRefs"/>

		<xsl:call-template name="createCL">
          <xsl:with-param name="occStr" select="$occRefs"/>
          <xsl:with-param name="levelID">1</xsl:with-param>
        </xsl:call-template>

		</xsl:when>
    </xsl:choose>
  </xsl:template>

   <!-- *************** createCL **************** -->
  <xsl:template name="createCL">
    <xsl:param name="occStr"/>
    <xsl:param name="levelID"/>

    <xsl:if test="$occStr!=''">
      <xsl:choose>
        <xsl:when test="contains($occStr,' ')">
          <xsl:variable name="occid" select="substring-before($occStr,' ')"/>

          <xsl:call-template name="createCL">
            <xsl:with-param name="occStr" select="$occid"/>
            <xsl:with-param name="levelID" select="$levelID "/>
          </xsl:call-template>

          <xsl:call-template name="createCL">
            <xsl:with-param name="occStr" select="substring-after($occStr,' ')"/>
            <xsl:with-param name="levelID" select="$levelID "/>
          </xsl:call-template>
        </xsl:when>

        <xsl:otherwise>
          <xsl:call-template name="creCLext">
            <xsl:with-param name="occID" select="$occStr"/>
            <xsl:with-param name="levelid" select="$levelID "/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <!-- *************** creCLext **************** -->
  <xsl:template name="creCLext">
    <xsl:param name="occID"/>
    <xsl:param name="levelid"/>
	<!--xsl:param name="slNo"/-->
	<!--xsl:with-param name="slNo" select="1"/-->
    <xsl:variable name="occele" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occID]"/>
    <xsl:variable name="occRefsId" select="$occele/@occurrenceRefs"/>
    <xsl:variable name="prtid" select="substring-after($occele/@instancedRef,'#')"/>
    <xsl:variable name="prteleProduct" select="/plm:PLMXML/plm:ProductRevision[@id=$prtid]"/>
    <xsl:variable name="prteleDes" select="/plm:PLMXML/plm:DesignRevision[@id=$prtid]"/>
    <xsl:variable name="prtelePart" select="/plm:PLMXML/plm:PartRevision[@id=$prtid]"/>
       <xsl:choose>
          <xsl:when test="$prteleProduct != ''" >
            <xsl:call-template name="ChildComponentsExt">
            <xsl:with-param name="occid" select="$occID"/>
            <xsl:with-param name="level" select="$levelid"/>
            <xsl:with-param name="prtele" select="$prteleProduct"/>
            <xsl:with-param name="occRefs" select="$occRefsId"/>
          </xsl:call-template>
           </xsl:when>
           <xsl:when test="$prteleDes != ''" >
            <xsl:call-template name="ChildComponentsExt">
            <xsl:with-param name="occid" select="$occID"/>
            <xsl:with-param name="level" select="$levelid"/>
            <xsl:with-param name="prtele" select="$prteleDes"/>
            <xsl:with-param name="occRefs" select="$occRefsId"/>
          </xsl:call-template>
           </xsl:when>
           <xsl:when test="$prtelePart != ''" >
            <xsl:call-template name="ChildComponentsExt">
            <xsl:with-param name="occid" select="$occID"/>
            <xsl:with-param name="level" select="$levelid"/>
            <xsl:with-param name="prtele" select="$prtelePart"/>
            <xsl:with-param name="occRefs" select="$occRefsId"/>
          </xsl:call-template>
           </xsl:when>
      </xsl:choose>
      </xsl:template>
      
  <xsl:template name="ChildComponentsExt">
    <xsl:param name="occid"/>  
    <xsl:param name="level"/>
    <xsl:param name="prtele"/>
    <xsl:param name="occRefs"/>

    <xsl:variable name="itemID" select="$prtele/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
    <xsl:variable name="itemRev" select="$prtele/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>
    <xsl:variable name="itemName" select="$prtele/plm:UserData/plm:UserValue[@title='object_name']/@value"/>
    <xsl:variable name="itemDesc" select="$prtele/plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
	<xsl:variable name="itemType" select="$prtele/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
    <xsl:variable name="creationDate" select="$prtele/plm:UserData/plm:UserValue[@title='creation_date']/@value"/>
    <xsl:variable name="modifiedDate" select="$prtele/plm:UserData/plm:UserValue[@title='last_mod_date']/@value"/>
    <xsl:variable name="quantity" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='Quantity']/@value" />
	<xsl:variable name="engMakeBuy" select="$prtele/plm:UserData/plm:UserValue[@title='get6EngMB']/@value"/>
	<xsl:variable name="parentPart" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='bl_formatted_parent_name']/@value" />
    <xsl:variable name="packCount" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='bl_pack_count']/@value" />
	<xsl:variable name="ruleConfigured" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='bl_config_string']/@value" />
    <xsl:variable name="releaseStatusRef" select="$prtele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
    <xsl:variable name="releaseStatus" select="/plm:PLMXML/plm:ReleaseStatus[@id=$releaseStatusRef]" />
    <xsl:variable name="releaseStatusName" select="$releaseStatus/@name" />
    <xsl:variable name="releasedDate" select="$releaseStatus/@dateReleased"/>
	<xsl:variable name="projectId" select="$prtele/plm:UserData/plm:UserValue[@title='project_ids']/@value"/>
	
	<xsl:variable name="userRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
    <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId" />
	
	<xsl:variable name="groupRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
    <xsl:variable name="groupName" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]/@name" />

    <xsl:variable name="modUserRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
    <xsl:variable name="modUserName" select="/plm:PLMXML/plm:User[@id=$modUserRef]/@userId" />

    <xsl:variable name="formRef" select="$prtele/plm:AssociatedForm[@role='IMAN_master_form']/@formRef"/>
    <xsl:variable name="form" select="key('form',substring-after($formRef,'#'))"/>

    <xsl:variable name="notesTitle" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData[@type='InstanceNotes']/plm:UserValue/@title" />
    <xsl:variable name="notesValue" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData[@type='InstanceNotes']/plm:UserValue/@value" />
	
    <!-- get details from manufacturing attributes form-->
	<xsl:variable name="itemRef" select="substring-after($prtele/@masterRef,'#')"/>
	<xsl:variable name="ServformItemRef" select="key('form',substring-after(/plm:PLMXML/plm:Design[@id=$itemRef]/plm:AssociatedForm[@role='GET6PartOrgRelation']/@formRef,'#'))"/>
	<xsl:variable name="makeBuyMfg" select="$ServformItemRef/plm:UserData/plm:UserValue[@title='get6MakeBuy']/@value"/>
	<xsl:variable name="strCode" select="$ServformItemRef/plm:UserData/plm:UserValue[@title='get6StructureCode']/@value"/>
	<xsl:variable name="stockMatQuan" select="$ServformItemRef/plm:UserData/plm:UserValue[@title='get6StockMtrlConsumedQty']/@value"/>
	
	<!--get uom tag details-->
	<xsl:variable name="uomTagRef" select="key('unit',substring-after(/plm:PLMXML/plm:Design[@id=$itemRef]/plm:UserData/plm:UserValue[@title='uom_tag']/@dataRef,'#'))"/>
	<xsl:variable name="uomTag" select = "$uomTagRef/plm:UserData/plm:UserValue/@value"/>"
	
	<!-- get stockmaterial -->
	<xsl:variable name="stockMaterialRef" select="$ServformItemRef/plm:UserData/plm:UserValue[@title='get6StockMaterial']/@dataRef"/>
	<xsl:variable name="stockMaterialRef1" select = "substring-after($stockMaterialRef,'#')"/>
	<xsl:variable name="stockMatlId" select="/plm:PLMXML/plm:Design[@id=$stockMaterialRef1]/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
	<xsl:variable name="stockMatlName" select="/plm:PLMXML/plm:Design[@id=$stockMaterialRef1]/plm:UserData/plm:UserValue[@title='object_name']/@value"/>
	
	<!-- get details of find no-->
	<xsl:variable name="findNo" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='SequenceNumber']/@value" />
	<xsl:variable name="slNo" select="1"/>
	
	<xsl:choose>
	<!--xsl:with-param name="slNo" select="$slNo + 1"/-->
      <xsl:when test="$occRefs!=''">
	  
    <Row>
		
		<Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$level"/>
            </Data>
          </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemID"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemRev"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemName"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$quantity"/>
        </Data>
      </Cell>
	  
      <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$findNo"/>
        </Data>
      </Cell>
	   
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$packCount"/>
        </Data>
      </Cell>
	   
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$parentPart"/>
        </Data>
      </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:choose>
                  <xsl:when test="$uomTag!=''">
                    <xsl:value-of select="$uomTag"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>Each</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
            </Data>
          </Cell>
		  
		  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:value-of select="$strCode"/>
            </Data>
         </Cell>
		 
		 <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$stockMatlId"/>
            </Data>
       </Cell>
	   
	  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
				<xsl:value-of select="$stockMatlName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$stockMatQuan"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$userName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$groupName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$modUserName"/>
        </Data>
      </Cell>
	  
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$modifiedDate"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$projectId"/>
        </Data>
      </Cell>
	  
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:value-of select="$engMakeBuy"/>
            </Data>
       </Cell>
	   
	    <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$releaseStatusName"/>
        </Data>
      </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$makeBuyMfg"/>
            </Data>
       </Cell>
	   
	    <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$itemType"/>
            </Data>
       </Cell>
	  </Row>
        <xsl:call-template name="createCL">
          <xsl:with-param name="occStr" select="$occRefs"/>
          <xsl:with-param name="levelID" select="$level + 1"/>
        </xsl:call-template>
      </xsl:when>

      <xsl:otherwise>
        <Row>
        
		<Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$level"/>
            </Data>
          </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemID"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemRev"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemName"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$quantity"/>
        </Data>
      </Cell>
	  
      <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$findNo"/>
        </Data>
      </Cell>
	   
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$packCount"/>
        </Data>
      </Cell>
	   
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$parentPart"/>
        </Data>
      </Cell>
	   
	  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:choose>
                  <xsl:when test="$uomTag!=''">
                    <xsl:value-of select="$uomTag"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>Each</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
            </Data>
          </Cell>
		  
		  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:value-of select="$strCode"/>
            </Data>
         </Cell>
		 
		 <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$stockMatlId"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
				<xsl:value-of select="$stockMatlName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$stockMatQuan"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$userName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
                <xsl:value-of select="$groupName"/>
            </Data>
       </Cell>
	   
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$modUserName"/>
        </Data>
      </Cell>
	  
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$modifiedDate"/>
        </Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$projectId"/>
        </Data>
      </Cell>
	  
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:value-of select="$engMakeBuy"/>
            </Data>
       </Cell>
	   
	    <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$releaseStatusName"/>
        </Data>
      </Cell>
	   
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$makeBuyMfg"/>
            </Data>
       </Cell>
	   
	    <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$itemType"/>
            </Data>
       </Cell>
	  </Row>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>
