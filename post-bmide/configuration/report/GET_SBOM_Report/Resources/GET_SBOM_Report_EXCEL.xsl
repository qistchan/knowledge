<?xml version="1.0" encoding="utf-8" ?>

<xsl:stylesheet version="1.0"
           xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
           xmlns:plm="http://www.plmxml.org/Schemas/PLMXMLSchema"
           xmlns="urn:schemas-microsoft-com:office:spreadsheet"
           xmlns:o="urn:schemas-microsoft-com:office:office"
           xmlns:x="urn:schemas-microsoft-com:office:excel"
           xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"
           xmlns:html="http://www.w3.org/TR/REC-html40" 
		   xmlns:crf="http://ExternalFunction.setFile"
		  xmlns:msxsl="urn:schemas-microsoft-com:xslt"
xmlns:VBCustomScript="urn:extra-functions"
xmlns:dt="uuid:C2F41010-65B3-11d1-A29F-00AA00C14882"
 xmlns:s="uuid:BDC6E3F0-6DA3-11d1-A2A3-00AA00C14882"
 xmlns:rs="urn:schemas-microsoft-com:rowset" xmlns:z="#RowsetSchema"
>
			
			
  


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
          <Interior ss:Color="#b3b3cc" ss:Pattern="Solid"/>
        </Style>
        <Style ss:ID="heading2">
          <Font ss:Color="#000000" ss:Size="12" ss:FontName="Arial" ss:Bold="1"/>
          <Interior ss:Color="#b3b3cc" ss:Pattern="Solid"/>
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
      
  <Style ss:ID="Default" ss:Name="Normal">
   <Alignment ss:Vertical="Bottom"/>
   <Borders/>
   <Font ss:FontName="Calibri" x:Family="Swiss" ss:Size="11" ss:Color="#000000"/>
   <Interior/>
   <NumberFormat/>
   <Protection/>
  </Style>
  <Style ss:ID="s59">
   <Alignment ss:Horizontal="Left" ss:Vertical="Bottom" ss:Indent="2"/>
  </Style>
  <Style ss:ID="s60">
   <Alignment ss:Horizontal="Left" ss:Vertical="Bottom" ss:Indent="1"/>
  </Style>
  <Style ss:ID="s61">
   <Alignment ss:Horizontal="Left" ss:Vertical="Bottom"/>
  </Style>
  <Style ss:ID="s62">
   <Alignment ss:Horizontal="Left" ss:Vertical="Bottom"/>
   <Borders/>
   <Font ss:FontName="Arial" ss:Color="#000000" ss:Bold="1"/>
   <Interior ss:Color="#CCCCFF" ss:Pattern="Solid"/>
   <NumberFormat/>
   <Protection/>
  </Style>
  <Style ss:ID="s63">
   <Alignment ss:Vertical="Bottom"/>
   <Borders/>
   <Font ss:FontName="Arial" ss:Color="#000000"/>
   <Interior ss:Color="#FFFFCC" ss:Pattern="Solid"/>
   <NumberFormat/>
   <Protection/>
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

          <Row ></Row>
          <Row>
            <Cell ss:StyleID="heading1">
              <Data ss:Type="String">
                <xsl:value-of select="$title"/>
              </Data>
            </Cell>
            <Cell ss:StyleID="heading1"></Cell>
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
          <xsl:with-param name="title" select="'GET SBOM Report'"/>
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
	<xsl:param name="occid"/>

	<xsl:variable name="itemID" select="$prtele/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
    <xsl:variable name="itemRev" select="$prtele/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>
    <xsl:variable name="itemName" select="$prtele/plm:UserData/plm:UserValue[@title='object_name']/@value"/>
    <xsl:variable name="itemDesc" select="$prtele/plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
    <xsl:variable name="creationDate" select="$prtele/plm:UserData/plm:UserValue[@title='creation_date']/@value"/>
    <xsl:variable name="modifiedDate" select="$prtele/plm:UserData/plm:UserValue[@title='last_mod_date']/@value"/>
    <xsl:variable name="object_type" select="$prtele/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
    <xsl:variable name="releaseStatusRef" select="$prtele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
    <xsl:variable name="releaseStatus" select="/plm:PLMXML/plm:ReleaseStatus[@id=$releaseStatusRef]" />
    <xsl:variable name="releaseStatusName" select="$releaseStatus/@name" />
    <xsl:variable name="releasedDate" select="$releaseStatus/@dateReleased"/>

    <xsl:variable name="userRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
    <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId" />
	<xsl:variable name="quantity" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='Quantity']/@value" />
	<xsl:variable name="uomRef" select="substring-after(/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='bl_uom']/@dataRef,'#')"/>
    <xsl:variable name="uom" select="/plm:PLMXML/plm:Unit[@id=$uomRef]/plm:UserData/plm:UserValue/@value" />
	<xsl:variable name="getEngMakeBuy" select="$prtele/plm:UserData/plm:UserValue[@title='get6EngMB']/@value"/>
	
	<xsl:variable name="itemRef" select="substring-after($prtele/@masterRef,'#')"/>

    <xsl:variable name="modUserRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
    <xsl:variable name="modUserName" select="/plm:PLMXML/plm:User[@id=$modUserRef]/@userId" />

    <xsl:variable name="formRef" select="$prtele/plm:AssociatedForm[@role='IMAN_master_form']/@formRef"/>
    <xsl:variable name="form" select="key('form',substring-after($formRef,'#'))"/>

    <xsl:variable name="userData1" select="$form/plm:UserData/plm:UserValue[@title='user_data_1']/@value"/>
    <xsl:variable name="userData2" select="$form/plm:UserData/plm:UserValue[@title='user_data_2']/@value"/>
    <xsl:variable name="projectId" select="$form/plm:UserData/plm:UserValue[@title='project_id']/@value"/>
	<xsl:variable name="DataModelRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='get6DataModel']/@valueRef,'#')"/>
	<xsl:variable name="DataModel" select="/plm:PLMXML/plm:Text[@id=$DataModelRef]/plm:Item"/>
	<xsl:variable name="ObjWt" select="$prtele/plm:UserData/plm:UserValue[@title='get6ObjWt']/@value"/>
	<xsl:variable name="ObjWtUOM" select="$prtele/plm:UserData/plm:UserValue[@title='get6ObjWtUOM']/@value"/>
	
	<xsl:variable name="ServformRef" select="$prtele/plm:AssociatedForm[@role='GET9ServFormAtt']/@formRef"/>
    <xsl:variable name="Servform" select="key('form',substring-after($ServformRef,'#'))"/>
	<xsl:variable name="ComponentID" select="$Servform/plm:UserData/plm:UserValue[@title='get9ComponentID']/@value"/>
    <xsl:variable name="PositionTracked" select="$Servform/plm:UserData/plm:UserValue[@title='get9PositionTracked']/@value"/>
    <xsl:variable name="Repairable" select="$Servform/plm:UserData/plm:UserValue[@title='get9Repairable']/@value"/>
	<xsl:variable name="Serialized" select="$Servform/plm:UserData/plm:UserValue[@title='get9Serialized']/@value"/>
    <xsl:variable name="ServiceItemType" select="$Servform/plm:UserData/plm:UserValue[@title='get9ServiceItemType']/@value"/>
    <xsl:variable name="Serviceable" select="$Servform/plm:UserData/plm:UserValue[@title='get9Serviceable']/@value"/>
	<xsl:variable name="TierType" select="$Servform/plm:UserData/plm:UserValue[@title='get9TierType']/@value"/>
    <xsl:variable name="EngineFamily" select="$Servform/plm:UserData/plm:UserValue[@title='get9EngineFamily']/@value"/>
    <xsl:variable name="CatalogNo" select="$Servform/plm:UserData/plm:UserValue[@title='get9CatalogNo']/@value"/>
	
    <Row>
	
	 <Cell ss:StyleID="heading2">
              <Data ss:Type="String">
                Item Id : <xsl:value-of select="$itemID"/>
              </Data>
            </Cell>
            <Cell ss:StyleID="heading2"></Cell>
			<Cell ss:StyleID="heading2"></Cell>
	</Row>
	<Row></Row>
	<Row>
	 <Cell ss:StyleID="heading2">
              <Data ss:Type="String">
                Item Name : <xsl:value-of select="$itemName"/>
              </Data>
            </Cell>
            <Cell ss:StyleID="heading2"></Cell>
			<Cell ss:StyleID="heading2"></Cell>
	</Row>
	<Row></Row>
	<Row>
	 <Cell ss:StyleID="heading2">
              <Data ss:Type="String">
                Product Revision : <xsl:value-of select="$itemRev"/>
              </Data>
            </Cell>
            <Cell ss:StyleID="heading2"></Cell>
			<Cell ss:StyleID="heading2"></Cell>
	</Row>
	<Row></Row>

    <!--  Modify_Here_Column_Parent -->
    <Row>
	<Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Level</Data>
      </Cell>
      <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Item Id</Data>
      </Cell>
      
      <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Revision</Data>
      </Cell>
	  <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Item Name</Data>
      </Cell>
	  <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Item Type</Data>
          </Cell>
		  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Release Status</Data>
      </Cell>
      <!--
                      <Cell ss:StyleID="heading3"><Data ss:Type="String">Unit of Measure</Data></Cell>
                      -->
					  <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Has Service Form</Data>
          </Cell>
      <Cell ss:StyleID="heading3" >

        <Data ss:Type="String">Quantity</Data>
      </Cell>
	   <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Effectivity Date Range</Data>
      </Cell>
      <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">UOM</Data>
      </Cell>
      <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Eng Make/Buy</Data>
      </Cell>
     
<Cell ss:StyleID="heading3">
        <Data ss:Type="String">Owning Group</Data>
      </Cell>

<Cell ss:StyleID="heading3">
        <Data ss:Type="String">IP Classification</Data>
      </Cell>
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Serviceable</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Repairable</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Serialized</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Position Tracked</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Service Item Type</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Tier Type</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Engine Family</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Catalog Item</Data>
      </Cell>
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Component Id</Data>
      </Cell>
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Global Alternate Parts</Data>
      </Cell>
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Preferred Alternate Part</Data>
      </Cell>
    </Row>

    


    <Row>
	<Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          0
        </Data>
      </Cell>
      <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemID"/>
        </Data>
      </Cell>
     
      <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$prtele/@revision"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$itemName"/>
        </Data>
      </Cell>
	  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
			<xsl:if test=" $object_type = 'GET9ZnlLvlRevision'">GET Zonal Level</xsl:if>
		    <xsl:if test="$object_type = 'GET9FnctLvlRevision'">GET Functional Level</xsl:if>
	        <xsl:if test=" $object_type= 'GET6MechPartRevision'">GET Engineering Part</xsl:if>
		    <xsl:if test="$object_type = 'GET9SrvPartRevision'">GET Service Part</xsl:if>              
            </Data>
          </Cell>
		 <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$primaryOccRef]/plm:UserData/plm:UserValue[@title='bl_rev_last_release_status']/@value"/>
            </Data>
          </Cell>
      <!-- was used for 'Unit of Measure'
                                <Cell ss:StyleID="cell_data"><Data ss:Type="String"></Data></Cell>
                                 -->
								 <Cell ss:StyleID="cell_data">
        <Data ss:Type="String"></Data>
      </Cell>
      <Cell ss:StyleID="cell_data">
        <Data ss:Type="String"></Data>
      </Cell>
	  
	  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$primaryOccRef]/plm:UserData/plm:UserValue[@title='bl_occ_date_range']/@value"/>
            </Data>
          </Cell>
      <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:choose>
                  <xsl:when test="$uom!=''">
                    <xsl:value-of select="$uom"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>Each</xsl:text>
                  </xsl:otherwise>
          </xsl:choose>
        </Data>
      </Cell>
      <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
          <xsl:value-of select="$getEngMakeBuy"/>
        </Data>
      </Cell>
     
     
	 

      <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
		  <xsl:variable name="owninggroupRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
          <xsl:variable name="owninggroup" select="/plm:PLMXML/plm:Organisation[@id=$owninggroupRef]/@name" />
          <xsl:value-of select="$owninggroup"/>
        </Data>
      </Cell>
	  
	<Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
		
         
	   <xsl:variable name="ipclassificationRef" select="substring-after(/plm:PLMXML/plm:Design[@id=$itemRef]/plm:UserData/plm:UserValue[@title='ip_classification']/@valueRef,'#')"/>
	   <xsl:variable name="ipclassification" select="/plm:PLMXML/plm:Text[@id=$ipclassificationRef]/plm:Item"/>
         <xsl:value-of select="$ipclassification"/>
        </Data>
      </Cell>
	  
	  
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Serviceable"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Repairable"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Serialized"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$PositionTracked"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$ServiceItemType"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
	   <Data ss:Type="String">	
	   
	    <xsl:for-each select="$TierType/plm:UserList/plm:Item">
	    <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
     </xsl:for-each>        
        
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         
		 <xsl:for-each select="$EngineFamily/plm:UserList/plm:Item">
	   
      <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
        
		 <xsl:for-each select="$CatalogNo/plm:UserList/plm:Item">
	   
      <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         
		 <xsl:for-each select="$ComponentID/plm:UserList/plm:Item">
	   
      <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$primaryOccRef]/plm:UserData/plm:UserValue[@title='bl_item_global_alt_list']/@value"/>
            </Data>
          </Cell>
		   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$primaryOccRef]/plm:UserData/plm:UserValue[@title='bl_item_preferred_global_alt']/@value"/>
            </Data>
          </Cell>
	   
    </Row>


    <xsl:choose>
      <xsl:when test="$itemDesc!=''">
        <Row></Row>
        <Row>
          <Cell>
            <Data ss:Type="String">
              Description: <xsl:value-of select="$itemDesc"/>
            </Data>
          </Cell>
        </Row>
        <Row></Row>
      </xsl:when>
    </xsl:choose>

  </xsl:template>

  <!-- *************** Child Product **************** -->
  <xsl:template name="generateChildProduct">
    <xsl:param name="currentElement"/>
    <xsl:param name="parentID"/>
    <xsl:choose>
      <xsl:when test="/plm:PLMXML/plm:ProductView/plm:Occurrence">

        <Row>
          <Cell ss:StyleID="heading2">
            <Data ss:Type="String">Sub-Assembly/Part</Data>
          </Cell>
          <Cell ss:StyleID="heading2"></Cell>
        </Row>

        <Row>
          <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Level</Data>
          </Cell>
          <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Item Id</Data>
          </Cell>
		   <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Revision</Data>
          </Cell>
          <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Item Name</Data>
          </Cell>
		  <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Item Type</Data>
          </Cell>
		  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Release Status</Data>
      </Cell>
		  <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Has Service Form</Data>
          </Cell>
         
          <!-- was used for 'Unit of Measure
                                <Cell ss:StyleID="heading3"><Data ss:Type="String">Unit of Measure</Data></Cell>
                                -->
          <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Quantity</Data>
          </Cell>
		  <Cell ss:StyleID="heading3" >
        <Data ss:Type="String">Effectivity Date Range</Data>
      </Cell>
          <Cell ss:StyleID="heading3">
            <Data ss:Type="String">UOM</Data>
          </Cell>
                 
		  <Cell ss:StyleID="heading3">
            <Data ss:Type="String">Eng Make/Buy</Data>
          </Cell>
            
<Cell ss:StyleID="heading3">
        <Data ss:Type="String">Owning Group</Data>
      </Cell>

<Cell ss:StyleID="heading3">
        <Data ss:Type="String">IP Classification</Data>
      </Cell>

	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Serviceable</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Repairable</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Serialized</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Position Tracked</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Service Item Type</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Tier Type</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Engine Family</Data>
      </Cell>
	   <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Catalog Item</Data>
      </Cell>
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Component Id</Data>
      </Cell>
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Global Alternate Parts</Data>
      </Cell>
	  <Cell ss:StyleID="heading3">
        <Data ss:Type="String">Preferred Alternate Part</Data>
      </Cell>
	  		  
    </Row>

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
			<xsl:with-param name="occur" select="$occele"/>
          </xsl:call-template>
           </xsl:when>
           <xsl:when test="$prteleDes != ''" >
            <xsl:call-template name="ChildComponentsExt">
            <xsl:with-param name="occid" select="$occID"/>
            <xsl:with-param name="level" select="$levelid"/>
            <xsl:with-param name="prtele" select="$prteleDes"/>
            <xsl:with-param name="occRefs" select="$occRefsId"/>
			<xsl:with-param name="occur" select="$occele"/>
          </xsl:call-template>
           </xsl:when>
           <xsl:when test="$prtelePart != ''" >
            <xsl:call-template name="ChildComponentsExt">
            <xsl:with-param name="occid" select="$occID"/>
            <xsl:with-param name="level" select="$levelid"/>
            <xsl:with-param name="prtele" select="$prtelePart"/>
            <xsl:with-param name="occRefs" select="$occRefsId"/>
			<xsl:with-param name="occur" select="$occele"/>
          </xsl:call-template>
           </xsl:when>
      </xsl:choose>
      </xsl:template>
      
  <xsl:template name="ChildComponentsExt">
    <xsl:param name="occid"/>  
    <xsl:param name="level"/>
    <xsl:param name="prtele"/>
    <xsl:param name="occRefs"/>
	<xsl:param name="occur"/>

    <xsl:variable name="itemID" select="$prtele/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
    <xsl:variable name="itemRev" select="$prtele/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>
    <xsl:variable name="itemName" select="$prtele/plm:UserData/plm:UserValue[@title='object_name']/@value"/>
    <xsl:variable name="itemDesc" select="$prtele/plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
    <xsl:variable name="creationDate" select="$prtele/plm:UserData/plm:UserValue[@title='creation_date']/@value"/>
    <xsl:variable name="modifiedDate" select="$prtele/plm:UserData/plm:UserValue[@title='last_mod_date']/@value"/>
    <xsl:variable name="quantity" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='Quantity']/@value" />
    <xsl:variable name="object_type" select="$prtele/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
    <xsl:variable name="releaseStatusRef" select="$prtele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
    <xsl:variable name="releaseStatus" select="/plm:PLMXML/plm:ReleaseStatus[@id=$releaseStatusRef]" />
    <xsl:variable name="releaseStatusName" select="$releaseStatus/@name" />
    <xsl:variable name="releasedDate" select="$releaseStatus/@dateReleased"/>
	
	<xsl:variable name="uomRef" select="substring-after(/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='bl_uom']/@dataRef,'#')"/>
    <xsl:variable name="uom" select="/plm:PLMXML/plm:Unit[@id=$uomRef]/plm:UserData/plm:UserValue/@value" />
	<xsl:variable name="findNo" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='SequenceNumber']/@value" />
    <xsl:variable name="userRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
    <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId" />
	<xsl:variable name="getEngMakeBuy" select="$prtele/plm:UserData/plm:UserValue[@title='get6EngMB']/@value"/>
	
    <xsl:variable name="modUserRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
    <xsl:variable name="modUserName" select="/plm:PLMXML/plm:User[@id=$modUserRef]/@userId" />

    <xsl:variable name="formRef" select="$prtele/plm:AssociatedForm[@role='IMAN_master_form']/@formRef"/>
    <xsl:variable name="form" select="key('form',substring-after($formRef,'#'))"/>

    <xsl:variable name="notesTitle" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData[@type='InstanceNotes']/plm:UserValue/@title" />
    <xsl:variable name="notesValue" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData[@type='InstanceNotes']/plm:UserValue/@value" />

    <xsl:variable name="userData1" select="$form/plm:UserData/plm:UserValue[@title='user_data_1']/@value"/>
    <xsl:variable name="userData2" select="$form/plm:UserData/plm:UserValue[@title='user_data_2']/@value"/>
    <xsl:variable name="projectId" select="$form/plm:UserData/plm:UserValue[@title='project_id']/@value"/>
	<xsl:variable name="itemRef" select="substring-after($prtele/@masterRef,'#')"/>
	<xsl:variable name="DataModelRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='get6DataModel']/@valueRef,'#')"/>
	<xsl:variable name="DataModel" select="/plm:PLMXML/plm:Text[@id=$DataModelRef]/plm:Item"/>
	<xsl:variable name="ObjWt" select="$prtele/plm:UserData/plm:UserValue[@title='get6ObjWt']/@value"/>
	<xsl:variable name="ObjWtUOM" select="$prtele/plm:UserData/plm:UserValue[@title='get6ObjWtUOM']/@value"/>
	<xsl:variable name="ServformRef" select="$prtele/plm:AssociatedForm[@role='GET9ServFormAtt']/@formRef"/>
    <xsl:variable name="Servform" select="key('form',substring-after($ServformRef,'#'))"/>
	<xsl:variable name="ComponentID" select="$Servform/plm:UserData/plm:UserValue[@title='get9ComponentID']"/>
    <xsl:variable name="PositionTracked" select="$Servform/plm:UserData/plm:UserValue[@title='get9PositionTracked']/@value"/>
    <xsl:variable name="Repairable" select="$Servform/plm:UserData/plm:UserValue[@title='get9Repairable']/@value"/>
	<xsl:variable name="Serialized" select="$Servform/plm:UserData/plm:UserValue[@title='get9Serialized']/@value"/>
    <xsl:variable name="ServiceItemType" select="$Servform/plm:UserData/plm:UserValue[@title='get9ServiceItemType']/@value"/>
    <xsl:variable name="Serviceable" select="$Servform/plm:UserData/plm:UserValue[@title='get9Serviceable']/@value"/>
	<xsl:variable name="TierType" select="$Servform/plm:UserData/plm:UserValue[@title='get9TierType']"/>
    <xsl:variable name="EngineFamily" select="$Servform/plm:UserData/plm:UserValue[@title='get9EngineFamily']"/>
    <xsl:variable name="CatalogNo" select="$Servform/plm:UserData/plm:UserValue[@title='get9CatalogNo']"/>
	
	

    <xsl:choose>
      <xsl:when test="$occRefs!='' and $object_type != 'GET6MechPartRevision'">
	  
        <Row>
          <Cell ss:StyleID="cell_data">
		  
		  
            <Data ss:Type="String">
              <xsl:value-of select="$level"/>
            </Data>
          </Cell>
          <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
			<xsl:call-template name="WriteSpaces">
			<xsl:with-param name="count" select="$level"/>
			 
			</xsl:call-template>
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
			<xsl:if test=" $object_type = 'GET9ZnlLvlRevision'">GET Zonal Level</xsl:if>
		    <xsl:if test="$object_type = 'GET9FnctLvlRevision'">GET Functional Level</xsl:if>
	        <xsl:if test=" $object_type= 'GET6MechPartRevision'">GET Engineering Part</xsl:if>
		    <xsl:if test="$object_type = 'GET9SrvPartRevision'">GET Service Part</xsl:if>              
            </Data>
          </Cell>
		<Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
			<xsl:value-of select="$occur/plm:UserData/plm:UserValue[@title='bl_rev_last_release_status']/@value"/>
            </Data>
          </Cell>
		   <Cell ss:StyleID="cell_data">
			   <xsl:if test="$ServformRef != ''">
				<Data ss:Type="String">          
				 YES                
				</Data>
				</xsl:if>
      </Cell>
          <!-- was used for 'Unit of Measure
                                           <Cell ss:StyleID="cell_data"><Data ss:Type="String"></Data></Cell>
                                           -->
          <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="$quantity"/>
            </Data>
          </Cell>
		  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="$occur/plm:UserData/plm:UserValue[@title='bl_occ_date_range']/@value"/>
            </Data>
          </Cell>
          <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:choose>
                  <xsl:when test="$uom!=''">
                    <xsl:value-of select="$uom"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>Each</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
            </Data>
          </Cell>
         
          <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$getEngMakeBuy"/>
            </Data>
          </Cell>
           
<Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
		  <xsl:variable name="owninggroupRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
          <xsl:variable name="owninggroup" select="/plm:PLMXML/plm:Organisation[@id=$owninggroupRef]/@name" />
          <xsl:value-of select="$owninggroup"/>
        </Data>
      </Cell>
	  
	<Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
		
         
	   <xsl:variable name="ipclassificationRef" select="substring-after(/plm:PLMXML/plm:Design[@id=$itemRef]/plm:UserData/plm:UserValue[@title='ip_classification']/@valueRef,'#')"/>
	   <xsl:variable name="ipclassification" select="/plm:PLMXML/plm:Text[@id=$ipclassificationRef]/plm:Item"/>
         <xsl:value-of select="$ipclassification"/>
        </Data>
      </Cell>
	   
	  <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Serviceable"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Repairable"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Serialized"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$PositionTracked"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$ServiceItemType"/>
        </Data>
      </Cell>
	  <Cell ss:StyleID="cell_data">
	   <Data ss:Type="String">	
	    <xsl:for-each select="$TierType/plm:UserList/plm:Item">
	   
       <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>        
        
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         
		 <xsl:for-each select="$EngineFamily/plm:UserList/plm:Item">
	   
      <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
        
		 <xsl:for-each select="$CatalogNo/plm:UserList/plm:Item">
	   
    <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         
		 <xsl:for-each select="$ComponentID/plm:UserList/plm:Item">
	   
      <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="$occur/plm:UserData/plm:UserValue[@title='bl_item_global_alt_list']/@value"/>
            </Data>
          </Cell>
		   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="$occur/plm:UserData/plm:UserValue[@title='bl_item_preferred_global_alt']/@value"/>
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
			<xsl:call-template name="WriteSpaces">
			<xsl:with-param name="count" select="$level"/>
			
			</xsl:call-template>
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
			<xsl:if test=" $object_type = 'GET9ZnlLvlRevision'">GET Zonal Level</xsl:if>
		    <xsl:if test="$object_type = 'GET9FnctLvlRevision'">GET Functional Level</xsl:if>
	        <xsl:if test=" $object_type= 'GET6MechPartRevision'">GET Engineering Part</xsl:if>
		    <xsl:if test="$object_type = 'GET9SrvPartRevision'">GET Service Part</xsl:if>              
            </Data>
          </Cell>
		 <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="$occur/plm:UserData/plm:UserValue[@title='bl_rev_last_release_status']/@value"/>
            </Data>
          </Cell>
		   <Cell ss:StyleID="cell_data">
			   <xsl:if test="$ServformRef != ''">
				<Data ss:Type="String">          
				 YES                
				</Data>
				</xsl:if>
      </Cell>
          
          <!-- was used for 'Unit of Measure
                                           <Cell ss:StyleID="cell_data"><Data ss:Type="String"></Data></Cell>
                                           -->
          <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$quantity"/>
            </Data>
          </Cell>
		  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="$occur/plm:UserData/plm:UserValue[@title='bl_occ_date_range']/@value"/>
            </Data>
          </Cell>
          <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
               <xsl:choose>
                  <xsl:when test="$uom!=''">
                    <xsl:value-of select="$uom"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>Each</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
            </Data>
          </Cell>
         
          <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
              <xsl:value-of select="$getEngMakeBuy"/>
            </Data>
          </Cell>
          
 <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
		  <xsl:variable name="owninggroupRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
          <xsl:variable name="owninggroup" select="/plm:PLMXML/plm:Organisation[@id=$owninggroupRef]/@name" />
          <xsl:value-of select="$owninggroup"/>
        </Data>
      </Cell>
	  
	<Cell ss:StyleID="cell_data">
        <Data ss:Type="String">
		
         
	   <xsl:variable name="ipclassificationRef" select="substring-after(/plm:PLMXML/plm:Design[@id=$itemRef]/plm:UserData/plm:UserValue[@title='ip_classification']/@valueRef,'#')"/>
	   <xsl:variable name="ipclassification" select="/plm:PLMXML/plm:Text[@id=$ipclassificationRef]/plm:Item"/>
         <xsl:value-of select="$ipclassification"/>
        </Data>
      </Cell>
	  
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Serviceable"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Repairable"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$Serialized"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$PositionTracked"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         <xsl:value-of select="$ServiceItemType"/>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
	   <Data ss:Type="String">	
	    <xsl:for-each select="$TierType/plm:UserList/plm:Item">
	   
    <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>        
        
        </Data>
      </Cell>
	     <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         
		 <xsl:for-each select="$EngineFamily/plm:UserList/plm:Item">
	   
     
       <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
     </xsl:for-each>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
        
		 <xsl:for-each select="$CatalogNo/plm:UserList/plm:Item">
	   
      <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>
        </Data>
      </Cell>
	   <Cell ss:StyleID="cell_data">
        <Data ss:Type="String">	
         
		 <xsl:for-each select="$ComponentID/plm:UserList/plm:Item">
	   
     <xsl:if test=" position()!= last()">
        <xsl:value-of select="concat(@value, ',' )"/>
        </xsl:if>
		<xsl:if test="position() = last()">
        <xsl:value-of select="@value"/>
      </xsl:if>
       
     </xsl:for-each>
        </Data>
      </Cell>
	  <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="$occur/plm:UserData/plm:UserValue[@title='bl_item_global_alt_list']/@value"/>
            </Data>
          </Cell>
		   <Cell ss:StyleID="cell_data">
            <Data ss:Type="String">
            <xsl:value-of select="$occur/plm:UserData/plm:UserValue[@title='bl_item_preferred_global_alt']/@value"/>
            </Data>
          </Cell>
	  
	  
        </Row>
		
	  
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <xsl:template name="WriteSpaces">
   <xsl:param name="count" />
   
   
   
   
  
   <xsl:if test="$count &gt; 1">
     <xsl:text>    </xsl:text>
     <xsl:call-template name="WriteSpaces">
       <xsl:with-param name="count" select="$count - 1" />
	   
     </xsl:call-template>
   </xsl:if>
   
</xsl:template>

</xsl:stylesheet>
