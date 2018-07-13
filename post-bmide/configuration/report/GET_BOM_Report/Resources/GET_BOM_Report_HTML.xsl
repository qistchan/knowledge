<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:plm="http://www.plmxml.org/Schemas/PLMXMLSchema"
        exclude-result-prefixes="plm">


  <!-- Define global parameters -->
  <xsl:param name="primaryOccRef" select="/plm:PLMXML/plm:ProductView/@primaryOccurrenceRef"/>
  <xsl:param name="rootProductID" select="substring-after(/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$primaryOccRef]/@instancedRef,'#')"/>

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
  <xsl:output method="html" indent="yes"/>

  <!-- ******************** -->
  <!-- Header and structure -->
  <!-- ******************** -->
  <xsl:template name="BOMReportHeader">
    <xsl:param name="currentElement"/>
    <xsl:param name="parentOccurrenceID"/>
    <xsl:param name="title"/>
    <html>
      <head>
        <title>
          <xsl:value-of select="$title"/>
        </title>
        <style>
          table {
          width:100%;
          margin:auto;
          font-family:GE Inspira;
          font-size:16px;
          }
          table, th, td {
          border: 1px solid black;
          border-collapse: collapse;
          }
          th, td {
          padding: 5px;
          text-align: center;
          }
          table#bom tr:nth-child(even) {
          background-color: #eee;
          }
          table#bom tr:nth-child(odd) {
          background-color:#fff;
          }
          table#topbom th {
          background-color: #e6f9ff;
          color: black;
          }
          table#bom th {
          background-color: #e6f9ff;
          color: black;
          }
        </style>
        <script type="text/javascript">
          function displayDate()
          {
          var d=new Date();
          var weekday=new Array("Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday");
          var monthname=new Array("Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec");
          document.write(monthname[d.getMonth()] + " ");
          document.write(d.getDate() + ", ");
          document.write(d.getFullYear() + " ");
          document.write(weekday[d.getDay()] + " ");
          }
        </script>

      </head>
      <body BGCOLOR="#FFFFFF" link="#0000FF" vlink="#660066">
        <!-- This table sets up the top level layout of the report -->
        <P align="Center">
          <font size="+2" face="GE Inspira">
            <b>
              <xsl:variable name="spaces"><![CDATA[&nbsp;&nbsp;&nbsp;]]></xsl:variable>
              <xsl:value-of disable-output-escaping="yes" select="$spaces"/>
              <xsl:value-of select="$title"/>
            </b>
          </font>
        </P>
        
        <!--
        <P align="Left">
          <font size="+1" face="GE Inspira">
            Parts List For = <xsl:value-of select="/plm:PLMXML/plm:RevisionRule/@name"/>
            Product Name = <xsl:value-of select="/plm:PLMXML/plm:RevisionRule/@name"/>
            Revision Rule = <xsl:value-of select="/plm:PLMXML/plm:RevisionRule/@name"/>
            Revision Rule = <xsl:value-of select="/plm:PLMXML/plm:RevisionRule/@name"/>

          </font>
        </P>
        <P align="right">
          <font size="2" face="GE Inspira">
            <B>
              <script type="text/javascript">
                displayDate()
              </script>
            </B>
          </font>
        </P>
        -->

        <xsl:call-template name="generateReportData">
          <xsl:with-param name="currentElement" select="$currentElement"/>
          <xsl:with-param name="parentOccurrenceID" select="$parentOccurrenceID"/>
        </xsl:call-template>
      </body>
    </html>
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
          <xsl:with-param name="title" select="'GET BOM Report'"/>
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
    <P align="Left">
      <font size="+1" face="GE Inspira">
        <b>
        Product Id :  <xsl:value-of select="$prtele/plm:UserData/plm:UserValue[@title='item_id']/@value"/>  <br/>
        Product Name: <xsl:value-of select="$prtele/plm:UserData/plm:UserValue[@title='object_name']/@value"/>  <br/>
        Product Revision: <xsl:value-of select="$prtele/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>  <br/>
        Revision Rule: <xsl:value-of select="/plm:PLMXML/plm:RevisionRule/@name"/>  <br/>
        </b>
      </font>
    </P>
    
    <table id="topbom">
      <tr>
        <th colspan="100%">
          <b>Product</b>
        </th>
      </tr>
      <tr>
        <th>Item Id</th>
        <th>Item Name</th>
        <th>Revision</th>
        <th>Quantity</th>
        <th>UOM</th>
        <th>Eng Make/Buy</th>
        <th>Made From Part</th>
        <th>Made From Material</th>
        <th>Release Status</th>
      </tr>

      <xsl:variable name="itemID" select="$prtele/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
      <xsl:variable name="itemName" select="$prtele/plm:UserData/plm:UserValue[@title='object_name']/@value"/>
      <xsl:variable name="itemRev" select="$prtele/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>
      <xsl:variable name="itemDesc" select="$prtele/plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
      <xsl:variable name="creationDate" select="$prtele/plm:UserData/plm:UserValue[@title='creation_date']/@value"/>
      <xsl:variable name="modifiedDate" select="$prtele/plm:UserData/plm:UserValue[@title='last_mod_date']/@value"/>

      <xsl:variable name="itemRef" select="substring-after($prtele/@masterRef,'#')"/>
      <xsl:variable name="item" select="/plm:PLMXML/plm:Design/@id"/>

      <xsl:variable name="getEngMakeBuy" select="$prtele/plm:UserData/plm:UserValue[@title='get6EngMB']/@value"/>

      <xsl:variable name="releaseStatusRef" select="$prtele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
      <xsl:variable name="releaseStatus" select="/plm:PLMXML/plm:ReleaseStatus[@id=$releaseStatusRef]" />
      <xsl:variable name="releaseStatusName" select="$releaseStatus/@name" />
      <xsl:variable name="releasedDate" select="$releaseStatus/@dateReleased"/>

      <xsl:variable name="userRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
      <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId" />

      <xsl:variable name="modUserRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
      <xsl:variable name="modUserName" select="/plm:PLMXML/plm:User[@id=$modUserRef]/@userId" />

      <xsl:variable name="formRef" select="$prtele/plm:AssociatedForm[@role='IMAN_master_form']/@formRef"/>
      <xsl:variable name="form" select="key('form',substring-after($formRef,'#'))"/>

      <xsl:variable name="userData1" select="$form/plm:UserData/plm:UserValue[@title='user_data_1']/@value"/>
      <xsl:variable name="userData2" select="$form/plm:UserData/plm:UserValue[@title='user_data_2']/@value"/>

      <xsl:variable name="projectId" select="$form/plm:UserData/plm:UserValue[@title='project_id']/@value"/>
      <tr></tr>
      <tr>
        <td align="center">
          <font size="2" face="GE Inspira">
            <xsl:value-of select="$itemID"/>
          </font>
        </td>
        <td>
          <font size="2" face="GE Inspira">
            <xsl:value-of select="$itemName"/>
          </font>
        </td>
        <td align="center">
          <font size="2" face="GE Inspira">
            <xsl:value-of select="$itemRev"/>
          </font>
        </td>
        <td align="center">
          <font size="2" face="GE Inspira">1</font>
        </td>
        <td align="center">
          <font size="2" face="GE Inspira">
            <xsl:text>Each</xsl:text>
          </font>
        </td>
        <td align="center">
          <font size="2" face="GE Inspira">
            <xsl:value-of select="$getEngMakeBuy"/>
          </font>
        </td>
        <td align="center">
          <font size="2" face="GE Inspira">
            <xsl:for-each select="/plm:PLMXML/plm:GeneralRelation[@id]">
              <xsl:variable name="relId" select="./@id"/>
              <xsl:variable name="relatedRef" select="/plm:PLMXML/plm:GeneralRelation[@id=$relId]/@relatedRefs"/>
              <xsl:if test="contains($relatedRef, $itemRef)">
              <xsl:variable name="relType" select="/plm:PLMXML/plm:GeneralRelation[@relatedRefs=$relatedRef]/@subType"/>
                <xsl:if test="$relType = 'GET6MadeFromPart'">
                  <xsl:variable name="madeFromPartRef" select="substring-after($relatedRef,' #')"/>
                  <xsl:value-of select="/plm:PLMXML/plm:Design[@id=$madeFromPartRef]/@catalogueId"/>
                </xsl:if>
              </xsl:if>
            </xsl:for-each>
          </font>
        </td>
        <td align="center">
          <font size="2" face="GE Inspira">
            <xsl:for-each select="/plm:PLMXML/plm:GeneralRelation[@id]">
              <xsl:variable name="relId" select="./@id"/>
              <xsl:variable name="relatedRef" select="/plm:PLMXML/plm:GeneralRelation[@id=$relId]/@relatedRefs"/>
              <xsl:if test="contains($relatedRef, $itemRef)">
                <xsl:variable name="relType" select="/plm:PLMXML/plm:GeneralRelation[@relatedRefs=$relatedRef]/@subType"/>
                <xsl:if test="$relType = 'GET6MadeFromMatl'">
                  <xsl:variable name="madeFromMatRef" select="substring-after($relatedRef,' #')"/>
                  <xsl:value-of select="/plm:PLMXML/plm:Product[@id=$madeFromMatRef]/@productId"/>
                </xsl:if>
              </xsl:if>
            </xsl:for-each>
          </font>
        </td>
        <td align="center">
          <font size="2" face="GE Inspira">
            <xsl:value-of select="$releaseStatusName"/>
          </font>
        </td>
      </tr>

      <xsl:choose>
        <xsl:when test="$itemDesc!=''">
          <tr>
            <td colspan="11">
              <font size="1" face="GE Inspira">
                <b>Description: </b>
              </font>
              <font size="2" face="GE Inspira">
                <xsl:value-of select="$itemDesc"/>
              </font>
            </td>
          </tr>
        </xsl:when>
      </xsl:choose>

      <!--<xsl:choose>
        <xsl:when test="$form/plm:UserData/plm:UserValue">
          <tr>
            <td colspan="11">
              <xsl:call-template name="buildFormTable">
                <xsl:with-param name="form" select="$form"/>
                <xsl:with-param name="ID" select="concat($parentID,concat(@id, 'MasterForm'))"/>
                <xsl:with-param name="linkDisplayName" select="'MasterForm(current revision)'"/>
              </xsl:call-template>
            </td>
          </tr>
        </xsl:when>
      </xsl:choose>-->
    </table>
  </xsl:template>

  <!-- *************** Child Product **************** -->
  <xsl:template name="generateChildProduct">
    <xsl:param name="currentElement"/>
    <xsl:param name="parentID"/>
    <xsl:choose>
      <xsl:when test="/plm:PLMXML/plm:ProductView/plm:Occurrence">
        <table id="bom">
          <tr>
            <th colspan="100%">
                <b>Sub-Assembly</b>
            </th>
          </tr>
          <tr>
			<th>Level</th>
            <th>Find No.</th>
            <th>Item Id</th>
            <th>Item Name</th>
            <th>Revision</th>
            <th>Quantity</th>
            <th>UOM</th>
            <th>Eng Make/Buy</th>
            <th>Release Status</th>
          </tr>
          <tr></tr>

          <xsl:variable name="roe" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$primaryOccRef]" />
          <xsl:variable name="occRefs" select="$roe/@occurrenceRefs"/>

          <xsl:call-template name="createCL">
            <xsl:with-param name="occStr" select="$occRefs"/>
            <xsl:with-param name="levelID">1</xsl:with-param>
          </xsl:call-template>

        </table>
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
    <xsl:variable name="getEngMakeBuy" select="$prtele/plm:UserData/plm:UserValue[@title='get6EngMB']/@value"/>

    <xsl:variable name="itemDesc" select="$prtele/plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
    <xsl:variable name="creationDate" select="$prtele/plm:UserData/plm:UserValue[@title='creation_date']/@value"/>
    <xsl:variable name="modifiedDate" select="$prtele/plm:UserData/plm:UserValue[@title='last_mod_date']/@value"/>
    <xsl:variable name="quantity" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='Quantity']/@value" />
    <xsl:variable name="findNo" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='SequenceNumber']/@value" />
    <xsl:variable name="modUserRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
    <xsl:variable name="modUserName" select="/plm:PLMXML/plm:User[@id=$modUserRef]/@userId" />

    <xsl:variable name="notesTitle" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData[@type='InstanceNotes']/plm:UserValue/@title" />
    <xsl:variable name="notesValue" select="/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData[@type='InstanceNotes']/plm:UserValue/@value" />
    <xsl:variable name="releaseStatusRef" select="$prtele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>

    <xsl:variable name="uomRef" select="substring-after(/plm:PLMXML/plm:ProductView/plm:Occurrence[@id=$occid]/plm:UserData/plm:UserValue[@title='bl_uom']/@dataRef,'#')"/>
    <xsl:variable name="uom" select="/plm:PLMXML/plm:Unit[@id=$uomRef]/plm:UserData/plm:UserValue/@value" />

    <xsl:variable name="releaseStatus" select="/plm:PLMXML/plm:ReleaseStatus[@id=$releaseStatusRef]" />
    <xsl:variable name="releaseStatusName" select="$releaseStatus/@name" />
    <xsl:variable name="releasedDate" select="$releaseStatus/@dateReleased"/>

    <xsl:variable name="userRef" select="substring-after($prtele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
    <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId" />

    <xsl:variable name="formRef" select="$prtele/plm:AssociatedForm[@role='IMAN_master_form']/@formRef"/>
    <xsl:variable name="form" select="key('form',substring-after($formRef,'#'))"/>

    <xsl:variable name="userData1" select="$form/plm:UserData/plm:UserValue[@title='user_data_1']/@value"/>
    <xsl:variable name="userData2" select="$form/plm:UserData/plm:UserValue[@title='user_data_2']/@value"/>
    <xsl:variable name="projectId" select="$form/plm:UserData/plm:UserValue[@title='project_id']/@value"/>

      <xsl:choose>
      <xsl:when test="$occRefs!=''">
        <tr >
		  <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$level"/>
            </font>
          </td>
          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$findNo"/>
            </font>
          </td>
          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$itemID"/>
            </font>
          </td>
          <td>
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$itemName"/>
            </font>
          </td>
          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$itemRev"/>
            </font>
          </td>
          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$quantity"/>
            </font>
          </td>

          <td align="center">
            <font size="2" face="GE Inspira">
                <xsl:choose>
                  <xsl:when test="$uom!=''">
                    <xsl:value-of select="$uom"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>Each</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
            </font>
          </td>

          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$getEngMakeBuy"/>
            </font>
          </td>

          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$releaseStatusName"/>
            </font>
          </td>
        </tr>
        <xsl:call-template name="createCL">
          <xsl:with-param name="occStr" select="$occRefs"/>
          <xsl:with-param name="levelID" select="$level + 1"/>
        </xsl:call-template>
      </xsl:when>

      <xsl:otherwise>
        <tr >
		  <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$level"/>
            </font>
          </td>
          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$findNo"/>
            </font>
          </td>
          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$itemID"/>
            </font>
          </td>
          <td>
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$itemName"/>
            </font>
          </td>
          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$itemRev"/>
            </font>
          </td>
          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$quantity"/>
            </font>
          </td>

          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:choose>
                <xsl:when test="$uom!=''">
                  <xsl:value-of select="$uom"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:text>Each</xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </font>
          </td>

          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$getEngMakeBuy"/>
            </font>
          </td>

          <td align="center">
            <font size="2" face="GE Inspira">
              <xsl:value-of select="$releaseStatusName"/>
            </font>
          </td>
        </tr>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>



  <!-- Link for expand/collapse field 
		This style works with Netscape 6 and IE4+.  It does not need the
		onClick statement in the body, or the extra JavaScript within the
		body.
-->
  <xsl:template name="writeExpandCollapseLink">
    <xsl:param name="linkID"/>
    <xsl:param name="linkName"/>

    <xsl:variable name="divId" select="concat($linkID,'Child')"/>
    <xsl:variable name="hrefPart1"><![CDATA[ <A title="Click to expand or collapse." HREF="#]]></xsl:variable>
    <xsl:variable name="hrefPart2"><![CDATA["]]></xsl:variable>
    <xsl:variable name="onClickPart1"><![CDATA[ onclick="var div = document.getElementById(']]></xsl:variable>
    <xsl:variable name="onClickPart2"><![CDATA['); if (div.style.display=='none'){div.style.display = 'block';}else{div.style.display = 'none';}return true;">]]></xsl:variable>
    <xsl:variable name="closeLink"><![CDATA[</A>]]></xsl:variable>
    <font size="2" face="GE Inspira">
      <b>
        <i>
          <!-- These value-of calls are placed to make sure that there is no extra 
			 black space in critical areas. -->
          <xsl:value-of select="$hrefPart1" disable-output-escaping="yes"/>
          <xsl:value-of select="$linkID"/>
          <xsl:value-of select="$hrefPart2" disable-output-escaping="yes"/>
          <xsl:value-of select="$onClickPart1" disable-output-escaping="yes"/>
          <xsl:value-of select="$divId"/>
          <xsl:value-of select="$onClickPart2" disable-output-escaping="yes"/>
          <xsl:value-of select="$linkName"/>
          <xsl:value-of select="$closeLink" disable-output-escaping="yes"/>
        </i>
      </b>
    </font>
  </xsl:template>

</xsl:stylesheet>