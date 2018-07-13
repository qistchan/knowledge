<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
           xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
           xmlns:plm="http://www.plmxml.org/Schemas/PLMXMLSchema"
           xmlns:crf="http://ExternalFunction.setFile"
           xmlns:GET="Lookup table for Display Names">

  <!-- 
     List of External Functions 
     1. getDisplayName(key) // Given a key returns the display name from textserver
     2. getPropertyDisplayName( typeName, propertyName, locale) // Returns the display value of the property in the given locale
  -->

  <xsl:param name="report_locale" />

  <GET:DisplayNames>
    <object actual_value="GET6ECNRevision" display_value="Engr Change Notice Revision"/>
    <object actual_value="GET6ECRRevision" display_value="Engr Change Request Revision"/>
    <object actual_value="GET6MCNRevision" display_value="Manufacturing Change Notice Revision"/>
    <object actual_value="GET6MechPartRevision" display_value="GET Engineering Part Revision"/>
    <object actual_value="GET6MfgPartRevision" display_value="GET Manufacturing Part Revision"/>
    <object actual_value="GET6DrawingRevision" display_value="GET Drawing Revision"/>
    <object actual_value="GET6DocumentRevision" display_value="GET Document Revision"/>
    <object actual_value="GET6SpecsRevision" display_value="GET Purchase Specification Revision"/>
    <object actual_value="GET6MaterialRevision" display_value="GET Material Revision"/>
    <object actual_value="GET6Released" display_value="Released"/>
    <object actual_value="GET6Canceled" display_value="Canceled"/>
    <object actual_value="GET6Closed" display_value="Closed"/>
    <object actual_value="GET6Baselined" display_value="Baselined"/>
    <object actual_value="GET6Preliminary" display_value="Preliminary"/>
    <object actual_value="True" display_value="Yes"/>
    <object actual_value="False" display_value="No"/>
  </GET:DisplayNames>

  <xsl:output method="html" doctype-system="about:legacy-compat" indent="yes"/>

  <xsl:variable name="trvrootref" select="/plm:PLMXML/plm:Header/@traverseRootRefs"/>

  <xsl:template match="/">
    <xsl:call-template name="genDataforMultTrvRootRefs">
      <xsl:with-param name="occStr" select="$trvrootref"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template name="genDataforMultTrvRootRefs">
    <xsl:param name="occStr"/>
    <html>
      <head>
        <title>Engineering Change Request Report</title>
        <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
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

          function dateFormat( dateValue)
          {
          var m_names = new Array("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec");
          var d = new Date("2018-03-07T17:23:32Z");
          var curr_date = ((d.getDate())>=10)? (d.getDate()) : '0' + (d.getDate());
          var curr_month = d.getMonth();
          var curr_year = d.getFullYear();
          var curr_hour =  ((d.getHours())>=10)? (d.getHours()) : '0' + (d.getHours());
          var curr_minute = d.getMinutes();
          document.write(curr_date + "-" + m_names[curr_month] + "-" + curr_year + " " + curr_hour + ":" + curr_minute );
          }

          function printpage() {
          //Get the print button and put it into a variable
          var printButton = document.getElementById("printpagebutton");
          //Set the print button visibility to 'hidden'
          printButton.style.visibility = 'hidden';
          //Print the page content
          window.print()
          //Set the print button to 'visible' again
          //[Delete this line if you want it to stay hidden after printing]
          printButton.style.visibility = 'visible';
          }

          $(document).ready(function(){
          $('td.AppRej').each(function(){
          if ($(this).text() == 'Approved') {
          $(this).css('color','green');
          } else if($(this).text() == 'Released') {
          $(this).css('color','green');
          } else if($(this).text() == 'Rejected') {
          $(this).css('color','red');
          } else if($(this).text() == 'Saved') {
          $(this).css('color','balck');
          } else if($(this).text() == 'Submitted') {
          $(this).css('color','black');
          } else if($(this).text() == 'Re-Submitted') {
          $(this).css('color','black');
          } else if($(this).text() == 'Disapproved') {
          $(this).css('color','red');
          }else if($(this).text() == 'Canceled') {
          $(this).css('color','red');
          }else if($(this).text() == 'Modify') {
          $(this).css('color','black');
          }else if($(this).text() == 'Investigating') {
          $(this).css('color','black');
          }
          });
          });
        </script>
      </head>
      <body>
        <style>

          table {
          width:700px;
          table-layout: fixed;
          margin:auto;
          margin-left:0px;
          margin-right:auto;
          margin-top: 5px;
          margin-bottom: 5px;
          vertical-align: center;
          font-family:GE Inspira Sans;
          font-size:12px;
          }

          table, th, td {
          padding: 2px;
          border: 1px solid #f2f2f2;
          border-collapse: collapse;
          }
          th {
          background-color: #e6e6e6;
          color: black;
          text-align: center;
          font-weight: bold;
          font-size:12px;
          }
          td {
          text-align: left;
          color: black;
          }
          td:nth-child(odd) {
          <!-- 			  font-weight: bold;
				  width:1px;
				  white-space:nowrap; -->
          }
          td:nth-child(even) {
          }

          tr:hover
          {
          <!-- background-color: yellow; -->
          }

          table.NoBorder {
          width:700px;
          table-layout: fixed;
          margin:auto;
          margin-left:0px;
          margin-right:auto;
          margin-top: 5px;
          margin-bottom: 5px;
          vertical-align: center;
          font-family:GE Inspira Sans;
          font-size:12px;
          border: none;
          border-collapse: collapse;
          }

          table.NoBorder, th.NoBorder, td.NoBorder {
          padding: 2px;
          border: none;
          border-collapse: collapse;

          }

          h1 {color: #007acc; font-family:GE Inspira Sans; font-weight: bold; margin-left:100px;}
          h2 {color: #007acc; font-family:GE Inspira Sans; font-weight: bold; }
          h3 {color: #007acc; font-family:GE Inspira Sans; font-weight: bold; margin-top:2px;margin-bottom:2px; font-size:14px;}
          h4 {color: #007acc; font-family:GE Inspira Sans; font-weight: normal; margin-top:2px;margin-bottom:2px; font-size:13px; }
          h5 { font-family:GE Inspira Sans; font-weight: bold; }
          p { color: #007acc; font-family:GE Inspira Sans; font-weight: bold; }


          #Properties th {
          background-color: #e6e6e6;
          color: black;
          text-align: center;
          font-weight: bold;
          font-size:12px;
          }
          #Properties td {
          text-align: left;
          color: black;
          }

          #Properties td:nth-child(odd) {
          font-weight: bold;
          width:20%;
          white-space:nowrap;
          }

          #Properties td:nth-child(even)
          {
          <!-- background-color: #f2f2f2; -->
          width:30%;
          }

          #Properties tr:hover
          {
          <!-- background-color: yellow; -->
          }

          <!-- No Border Properties-->
          #NoBorderProperties th {
          background-color: #e6e6e6;
          color: black;
          text-align: center;
          font-weight: bold;
          font-size:12px;
          border: none;
          border-collapse: collapse;
          word-wrap:normal;
          word-wrap: break-word;

          }
          #NoBorderProperties td {
          text-align: left;
          vertical-align:top;
          color: black;
          font-size:12px;
          border: none;
          border-collapse: collapse;
          word-wrap:normal;
          word-wrap: break-word;

          }

          #NoBorderProperties td:nth-child(odd) {
          font-weight: bold;

          }

          #NoBorderProperties td:nth-child(even)
          {
          <!-- background-color: #f2f2f2; -->
          font-weight: normal;

          }

          #NoBorderProperties tr:hover
          {
          <!-- background-color: yellow; -->
          }


          <!-- Link-->
          a:link {
          }
          a:hover {
          <!-- background-color: yellow; -->
          }
          a:active {
          color: blue;
          }
          a:visited {
          color: blue;
          }

          .myButton {
          position: absolute;
          padding: 5px;
          display:block;
          float:right;
          background-color: #3399ff;
          color: black;
          font-weight: bold;
          text-align:center;
          <!-- 			align: right; 
					top: 57px; -->
          left: 310px;
          width:80px;
          height:30px;
          }
        </style>

        <!--<input class="myButton" id="printpagebutton" type="button"  value="PRINT" onclick="printpage()"/>-->

        <table style="width:700px;margin-top:30px;vertical-align:center;font-family:GE Inspira Sans;">
          <tbody>
            <tr>
              <th style="background-color:#e6e6e6;color:#007acc;text-align:center;font-size:20px;font-weight:bold;width:1px;white-space:nowrap;">Engineering Change Request Report</th>
            </tr>
          </tbody>
        </table>

        <xsl:call-template name="createCL">
          <xsl:with-param name="occStr" select="$occStr"/>
        </xsl:call-template>

        <div>
          <h5  style="position:absolute;left:300px;font-weight:normal;">&#169; GE Transportation</h5>
          <h5  style="font-weight:normal;">
            DATE PRINTED: <script type="text/javascript">displayDate()</script>
          </h5>
          <input class="myButton" id="printpagebutton" type="button"  value="PRINT" onclick="printpage()"/>

        </div>
      </body>
    </html>
  </xsl:template>

  <xsl:template name="createCL">
    <xsl:param name="occStr"/>

    <xsl:if test="$occStr!=''">
      <xsl:choose>
        <xsl:when test="contains($occStr,' ')">
          <xsl:variable name="occid" select="substring-before($occStr,' ')"/>
          <xsl:call-template name="createCL">
            <xsl:with-param name="occStr" select="$occid"/>
          </xsl:call-template>

          <xsl:call-template name="createCL">
            <xsl:with-param name="occStr" select="substring-after($occStr,' ')"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <!-- inside createCL otherwise occStr <xsl:value-of select="$occStr"/> -->
          <xsl:call-template name="creCLext">
            <xsl:with-param name="occid" select="$occStr"/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>

    </xsl:if>
  </xsl:template>

  <xsl:template name="creCLext">
    <xsl:param name="occid"/>
    <xsl:variable name="occrid" select="substring-after($occid,'#')"/>
    <xsl:call-template name="creCLext1">
      <xsl:with-param name="occid" select="$occrid"/>
    </xsl:call-template>
  </xsl:template>

  <xsl:template name="creCLext1">
    <xsl:param name="occid"/>
    <xsl:variable name="occele" select="/plm:PLMXML/*[@id=$occid]"/>
    <xsl:if test="string-length($occele/@subType) > 0">

      <xsl:choose>
        <xsl:when test="($occele/@subType)='GET6ECRRevision'">

          <xsl:variable name="subType" select="$occele/@subType"/>
          <xsl:variable name="masterRef" select="$occele/@masterRef"/>
          <xsl:variable name="Synopsis" select="$occele/@name"/>
          <xsl:variable name="occrid" select="substring-after($masterRef,'#')"/>
          <xsl:variable name="Descriptionid" select="$occele/plm:Description"/>
          <xsl:variable name="productid" select="/plm:PLMXML/plm:Product[@id=$occrid]/@productId" />
          <xsl:variable name="objectName" select="$occele/plm:UserData/plm:UserValue[@title='object_name']/@value"/>
          <xsl:variable name="itemRev" select="$occele/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>
          <xsl:variable name="object" select="$occele/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
          <xsl:variable name="revisionname" select="$occele/@revision"/>
          <xsl:variable name="owningUserRef" select="substring-after($occele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
          <xsl:variable name="owningUserId" select="/plm:PLMXML/plm:User[@id=$owningUserRef]/@userId"/>
          <xsl:variable name="owningUserName" select="/plm:PLMXML/plm:User[@id=$owningUserRef]/plm:UserData/plm:UserValue[@title='user_name']/@value"/>

          <xsl:variable name="objectDesc" select="$occele/plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
          <xsl:variable name="objectType" select="$occele/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
          <xsl:variable name="ipClassification" select="$occele/plm:UserData/plm:UserValue[@title='ip_classification']/@value"/>
          <xsl:variable name="maturity" select="$occele/plm:UserData/plm:UserValue[@title='CMMaturity']/@value"/>
          <xsl:variable name="disposition" select="$occele/plm:UserData/plm:UserValue[@title='CMDisposition']/@value"/>
          <xsl:variable name="closure" select="$occele/plm:UserData/plm:UserValue[@title='CMClosure']/@value"/>

          <xsl:variable name="effectivity" select="$occele/plm:UserData/plm:UserValue[@title='effectivity_trext']/@value"/>
          <xsl:variable name="daterelease" select="$occele/plm:UserData/plm:UserValue[@title='date_released']/@value"/>
          <xsl:variable name="releasestatus" select="$occele/plm:UserData/plm:UserValue[@title='release_status_list']/@value"/>
          <!-- <xsl:variable name="dateReleased" select="substring-before($occele/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/> -->
          <xsl:variable name="dateReleased" select="$occele/plm:UserData/plm:UserValue[@title='date_released']/@value"/>

          <!--<xsl:variable name="requestoruser" select="substring-after($occele/plm:UserData/plm:UserValue[@title='cm0Requestor']/@dataRef,'#')"/>
          <xsl:variable name="Role" select="substring-after(/plm:PLMXML/plm:OrganisationMember[@id=$requestoruser]/@roleRef,'#')" />
          <xsl:variable name="Role_user" select="/plm:PLMXML/plm:Role[@id=$Role]/@name" />
          <xsl:variable name="Organization" select="substring-after(/plm:PLMXML/plm:OrganisationMember[@id=$requestoruser]/@organizationRef,'#')" />
          <xsl:variable name="Organization_user" select="/plm:PLMXML/plm:Organization[@id=$Organization]/@name" />


          <xsl:variable name="Member" select="substring-after(/plm:PLMXML/plm:OrganizationMember[@id=$requestoruser]/@memberRef,'#')" />
          <xsl:variable name="Member_user" select="/plm:PLMXML/plm:User[@id=$Member]/@userId" />

          <xsl:variable name="Requestor" select="concat($Organization_user,'/',$Role_user,'/',$Member_user)"/>
          <xsl:variable name="Change_Specialist" select="substring-after($occele/plm:UserData/plm:UserValue[@title='ChangeSpecialist1']/@dataRef,'#')"/>
          <xsl:variable name="ChangeCpecialist" select="substring-after(/plm:PLMXML/plm:ResourcePool[@id=$Change_Specialist]/@organizationRef,'#')" />
          <xsl:variable name="ChangeCpecialist_org" select="/plm:PLMXML/plm:Organization[@id=$ChangeCpecialist]/@name" /> -->

          <!-- Custom Properties -->

          <xsl:variable name="productLine" select="$occele/plm:UserData/plm:UserValue[@title='get6EngrProdLine']/@value"/>
          <xsl:variable name="customers" select="$occele/plm:UserData/plm:UserValue[@title='get6Customers']/@value"/>
          <xsl:variable name="ontrackItems" select="$occele/plm:UserData/plm:UserValue[@title='get6OnTrackItems']/@value"/>
          <xsl:variable name="orderNo" select="$occele/plm:UserData/plm:UserValue[@title='get6OrderNo']/@value"/>
          <xsl:variable name="copies" select="$occele/plm:UserData/plm:UserValue[@title='get6Copies']/@value"/>

          <xsl:variable name="fastTrack" select="$occele/plm:UserData/plm:UserValue[@title='get6FastTrack']/@value"/>
          <xsl:variable name="redMarkDesign" select="$occele/plm:UserData/plm:UserValue[@title='get6RedMarkDesign']/@value"/>
          <xsl:variable name="primaryProjectNo" select="$occele/plm:UserData/plm:UserValue[@title='get6PriPrjNo']/@value"/>
          <xsl:variable name="secondaryProjectNo" select="$occele/plm:UserData/plm:UserValue[@title='get6SecPrjNo']/@value"/>
          <xsl:variable name="estimatedHours" select="$occele/plm:UserData/plm:UserValue[@title='get6EstHours']/@value"/>
          <xsl:variable name="dateRequired" select="substring-before($occele/plm:UserData/plm:UserValue[@title='get6DateReqd']/@value, 'T')"/>

          <xsl:variable name="serviceImpact" select="$occele/plm:UserData/plm:UserValue[@title='get6ServiceImpact']/@value"/>
          <xsl:variable name="reasonCode" select="$occele/plm:UserData/plm:UserValue[@title='get6ReasonCode']/@value"/>
          <xsl:variable name="changeReason" select="$occele/plm:UserData/plm:UserValue[@title='get6ChangeReason']/@value"/>
          <xsl:variable name="engrDisposition" select="$occele/plm:UserData/plm:UserValue[@title='get6EngrDisp']/@value"/>

          <xsl:variable name="reasonForChange" select="$occele/plm:UserData/plm:UserValue[@title='get6ReasonForChg']/@value"/>
          <xsl:variable name="changeDescription" select="$occele/plm:UserData/plm:UserValue[@title='get6ChgDesc']/@value"/>

          <xsl:variable name="engrInUSA" select="$occele/plm:UserData/plm:UserValue[@title='get6EngrInUSA']/@value"/>
          <xsl:variable name="expControl" select="$occele/plm:UserData/plm:UserValue[@title='get6ExpControl']/@value"/>
          <xsl:variable name="ECCNSource" select="$occele/plm:UserData/plm:UserValue[@title='get6ECCNSource']/@value"/>
          <xsl:variable name="objEvidence" select="$occele/plm:UserData/plm:UserValue[@title='get6ObjEvidence']/@value"/>


          <xsl:variable name="ECC" select="$occele/plm:UserData/plm:UserValue[@title='get6ECC']/@value"/>
          <xsl:variable name="CCC" select="$occele/plm:UserData/plm:UserValue[@title='get6CCC']/@value"/>
          <xsl:variable name="criticalPart" select="$occele/plm:UserData/plm:UserValue[@title='get6CriticalPart']/@value"/>
          <xsl:variable name="HML" select="$occele/plm:UserData/plm:UserValue[@title='get6Homologation']/@value"/>
          <xsl:variable name="addlComments" select="$occele/plm:UserData/plm:UserValue[@title='get6AddlCompComments']/@value"/>

          <xsl:variable name="appliedPractice" select="$occele/plm:UserData/plm:UserValue[@title='get6AppliedPractice']/@value"/>
          <xsl:variable name="applAppliedPractice" select="$occele/plm:UserData/plm:UserValue[@title='get6ApplAppPractice']/@value"/>
          <xsl:variable name="defaultToleranceIdentifier" select="$occele/plm:UserData/plm:UserValue[@title='get6DefTolIden']/@value"/>

          <!-- Header Section -->

          <table class="NoBorder" id="NoBorderProperties">
            <tbody>
              <tr>
                <!--<td colspan="2" rowspan="1" >
                  <xsl:value-of select="$object"/>
                </td> -->
                <td style="width:15%;">
                  <xsl:value-of select="$productid"/>/
                  <xsl:value-of select="$itemRev"/>
                </td>
                <td style="width:35%;">
                  <xsl:value-of select="$objectName"/>
                </td>
                <td style="width:10%;">Status: </td>
                <td style="width:40%;" class="NoBorder AppRej">
                  <xsl:call-template name="processConsolidatedStatus">
                    <xsl:with-param name="curoccele" select="$occele"/>
                  </xsl:call-template>
                </td>
              </tr>
              <tr>
                <td style="width:15%;">Group ID:</td>
                <td style="width:35%;">
                  <xsl:call-template name="processGroups">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>

                <td style="width:10%;">IP: </td>
                <td style="width:40%;">
                  <xsl:value-of select="$ipClassification"/>
                </td>
              </tr>
              <tr>
                <td style="width:15%;">Owner: </td>
                <td style="width:35%;">
                  <xsl:value-of select="$owningUserName"/>[<xsl:value-of select="$owningUserId"/>]
                </td>
                <td></td>
                <td></td>

              </tr>
            </tbody>
          </table>

          <h3>Details and Description</h3>
          <table class="NoBorder" id="NoBorderProperties">
            <tbody>
              <tr>
                <td style="width:15%;">Reason Code:</td>
                <td style="width:35%;">
                  <xsl:value-of select="$reasonCode"/>
                </td>
                <td style="width:10%;">Reason: </td>
                <td style="width:40%;">
                  <xsl:value-of select="$changeReason"/>
                </td>
              </tr>
            </tbody>
          </table>

          <table class="NoBorder" id="NoBorderProperties" >
            <tbody>
              <tr>
                <td>Reason For Change: </td>
              </tr>
              <tr>
                <td>
                  <div style="font-weight:normal;display:block; word-wrap: break-word;">
                    <xsl:value-of select="$reasonForChange" disable-output-escaping="yes"/>
                  </div>
                </td>
              </tr>
            </tbody>
          </table>

          <table class="NoBorder" id="NoBorderProperties" >
            <tbody>
              <tr>
                <td>Description of Change: </td>
              </tr>
              <tr>
                <td>
                  <div style="font-weight:normal;display:block; word-wrap: break-word;">
                    <xsl:value-of select="$changeDescription" disable-output-escaping="yes"/>
                  </div>
                </td>
              </tr>
            </tbody>
          </table>

          <table class="NoBorder" id="NoBorderProperties" >
            <tbody>
              <tr>
                <td>Engineering Disposition Recommendation: </td>
              </tr>
              <tr>
                <td>
                  <div style="font-weight:normal;display:block; word-wrap: break-word;">
                    <xsl:value-of select="$engrDisposition"/>
                  </div>
                </td>
              </tr>
            </tbody>
          </table>

          <table class="NoBorder" id="NoBorderProperties" >
            <tbody>
              <tr>
                <td>Engineering Product Line: </td>
                <td>
                  <xsl:value-of select="$productLine"/>
                </td>
                <td>Primary Project Number: </td>
                <td>
                  <xsl:value-of select="$primaryProjectNo"/>
                </td>
              </tr>

              <tr>
                <td>Fast Track ECR: </td>
                <td>
                  <!--<xsl:value-of select="$fastTrack"/>-->
                  <xsl:call-template name="processBoolean">
                    <xsl:with-param name="boolValue" select="$fastTrack"></xsl:with-param>
                  </xsl:call-template>
                </td>
                <td>Secondary Project Number: </td>
                <td>
                  <xsl:value-of select="$secondaryProjectNo"/>
                </td>
              </tr>

              <tr>
                <td>Red Mark Design ECR: </td>
                <td>
                  <!--<xsl:value-of select="$redMarkDesign"/>-->
                  <xsl:call-template name="processBoolean">
                    <xsl:with-param name="boolValue" select="$redMarkDesign"></xsl:with-param>
                  </xsl:call-template>
                </td>
                <td>Est Hours: </td>
                <td>
                  <xsl:value-of select="$estimatedHours"/>
                </td>
              </tr>

              <tr>
                <td>Services Impact: </td>
                <td>
                  <xsl:call-template name="processBoolean">
                    <xsl:with-param name="boolValue" select="$serviceImpact"></xsl:with-param>
                  </xsl:call-template>
                </td>
                <td>Date Required: </td>
                <td>
                  <xsl:value-of select="$dateRequired"/>
                </td>
              </tr>
            </tbody>
          </table>

          <table class="NoBorder" id="NoBorderProperties">
            <tbody>
              <tr>
                <td>Customers: </td>
                <td style="width:75%">
                  <xsl:call-template name="processCustomers">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>

              <tr>
                <td>Order Numbers: </td>
                <td style="width:75%">
                  <xsl:call-template name="processPOs">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>

              <tr>
                <td>OnTrack Item(s): </td>
                <td style="width:75%">
                  <xsl:call-template name="processOnTrackItems">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>

              <tr>
                <td>Copies: </td>
                <td style="width:75%">
                  <xsl:call-template name="processCopies">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>
            </tbody>
          </table>

          <h3>United States Export Control, Compliance, Applied Practice</h3>

          <table class="NoBorder" id="NoBorderProperties">
            <tbody>
              <tr>
                <td>Engg Activity done outside USA: </td>
                <td>
                  <!-- <xsl:value-of select="$engrInUSA"/> -->
                  <xsl:call-template name="processBoolean">
                    <xsl:with-param name="boolValue" select="$engrInUSA"></xsl:with-param>
                  </xsl:call-template>
                </td>
                <td>ECR affects ECC Comps: </td>
                <td>
                  <!--<xsl:value-of select="$ECC"/> -->
                  <xsl:call-template name="processBoolean">
                    <xsl:with-param name="boolValue" select="$ECC"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>

              <tr>
                <td>Export Control: </td>
                <td>
                  <xsl:value-of select="$expControl"/>
                </td>
                <td>ECR affects CCC Comps: </td>
                <td>
                  <!--<xsl:value-of select="$CCC"/> -->
                  <xsl:call-template name="processBoolean">
                    <xsl:with-param name="boolValue" select="$CCC"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>

              <tr>
                <td>ECCN Source: </td>
                <td>
                  <xsl:value-of select="$ECCNSource"/>
                </td>
                <td>ECR affects CP Comps: </td>
                <td>
                  <!-- <xsl:value-of select="$criticalPart"/> -->
                  <xsl:call-template name="processBoolean">
                    <xsl:with-param name="boolValue" select="$criticalPart"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>

              <tr>
                <td>ECCN Objective Evidence: </td>
                <td>
                  <xsl:value-of select="$objEvidence"/>
                </td>
                <td>ECR affects HML Comps: </td>
                <td>
                  <!-- <xsl:value-of select="$HML"/> -->
                  <xsl:call-template name="processBoolean">
                    <xsl:with-param name="boolValue" select="$HML"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>

              <tr>
                <td></td>
                <td></td>
                <td>Addl Compliance Comments: </td>
                <td>
                  <xsl:value-of select="$addlComments"/>
                </td>
              </tr>

            </tbody>
          </table>

          <table class="NoBorder" id="NoBorderProperties" >
            <tbody>
              <tr>
                <td>Applied Practice: </td>
                <td style="width:75%">
                  <xsl:value-of select="$appliedPractice"/>
                </td>
              </tr>

              <tr>
                <td>Applicable Applied Practice: </td>
                <td style="width:75%">
                  <xsl:value-of select="$applAppliedPractice"/>
                </td>
              </tr>

              <tr>
                <td>Default Tolerance Identifier: </td>
                <td style="width:75%">
                  <xsl:value-of select="$defaultToleranceIdentifier"/>
                </td>
              </tr>
            </tbody>
          </table>

          <xsl:variable name="DesignerParticipant" select= "/plm:PLMXML/plm:Participant[@userDefinedType='GET6Designer']"/>
          <xsl:if test="count($DesignerParticipant) > 0 ">
            <h3>Design Team</h3>
            <table>
              <tbody>
                <tr>
                  <th width="20%">User</th>
                  <th width="60%">Group</th>
                  <th width="20%">Role</th>
                </tr>
                <xsl:for-each select="$DesignerParticipant">
                  <xsl:variable name="Designer" select="substring-after(./@assigneeRef,'#')" />
                  <xsl:variable name="Role" select="substring-after(/plm:PLMXML/plm:OrganisationMember[@id=$Designer]/@roleRef,'#')" />
                  <xsl:variable name="Role_user" select="/plm:PLMXML/plm:Role[@id=$Role]/@name" />
                  <xsl:variable name="Organisation" select="substring-after(/plm:PLMXML/plm:OrganisationMember[@id=$Designer]/@organisationRef,'#')" />
                  <xsl:variable name="Organisation_user" select="/plm:PLMXML/plm:Organisation[@id=$Organisation]/@name" />
                  <xsl:variable name="Member" select="substring-after(/plm:PLMXML/plm:OrganisationMember[@id=$Designer]/@memberRef,'#')" />
                  <xsl:variable name="Member_user" select="/plm:PLMXML/plm:User[@id=$Member]/@userId" />
                  <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$Member]/plm:UserData/plm:UserValue[@title='user_name']/@value"/>
                  <xsl:variable name="user" select="concat($userName, ' (',$Member_user,')')"/>

                  <tr>
                    <td>
                      <xsl:value-of select="$user"/>
                    </td>
                    <td>
                      <xsl:value-of select="$Organisation_user"/>
                    </td>
                    <td>
                      <xsl:value-of select="$Role_user"/>
                    </td>
                  </tr>
                </xsl:for-each>
              </tbody>
            </table>
          </xsl:if>

          <h3>References</h3>

          <!-- Impacted Items -->
          <xsl:call-template name="processImpactedItems">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

          <!-- Implements Items (EDOT) -->
          <xsl:call-template name="processImplementsItems">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

          <!-- Implemented By (ECN) -->
          <xsl:call-template name="processImplementedByItems">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

          <!--Attachments -->
          <xsl:call-template name="processAttachments">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

          <!-- Workflow -->
          <xsl:call-template name="processWorkflowReviews">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

        </xsl:when>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <xsl:template name="processImpactedItems">
    <xsl:param name="primaryObjectID"/>
    <xsl:variable name="general_relation" select="/plm:PLMXML/plm:GeneralRelation[@subType='CMHasImpactedItem'][substring(substring-before(@relatedRefs,' '),2)=$primaryObjectID]"/>
    <xsl:if test="count($general_relation) > 0 ">
      <h4>Impacted Items</h4>
      <table>
        <tbody>
          <tr>
            <th>ID/Revision-Name</th>
            <th width="20%">Type</th>
            <th width="10%">Status</th>
            <th width="10%">Date</th>
            <th>Owner</th>
          </tr>
          <xsl:for-each select="$general_relation">
            <xsl:variable name="relatedRefs" select="./@relatedRefs"/>
            <xsl:variable name="relationImpactedItem" select="substring(substring-after($relatedRefs,' '),2)"/>
            <xsl:variable name="impactedItem" select="/plm:PLMXML/*[@id=$relationImpactedItem]"/>
            <xsl:variable name="object" select="$impactedItem/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
            <xsl:variable name="SubType" select="$impactedItem/@subType"/>
            <xsl:variable name="realeaseStatusRef" select="$impactedItem/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
            <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
            <xsl:variable name="dateReleased" select="substring-before($impactedItem/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>
            <xsl:variable name="dateReleasedValue" select="translate($dateReleased,'T',' ')"/>
            <xsl:variable name="userRef" select="substring-after($impactedItem/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
            <xsl:variable name="owningUser" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId"/>
            <xsl:variable name="groupRef" select="substring-after($impactedItem/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
            <xsl:variable name="owningGroup" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]/plm:UserData/plm:UserValue[@title='name']/@value"/>

            <tr>
              <td>
                <xsl:value-of select="$object"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <!--<td>
                <xsl:value-of select="$SubType"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td>
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$SubType]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$SubType"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <!-- <td>
                <xsl:value-of select="$ReleaseStatusName" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td style="width:1px;white-space:nowrap;">
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$ReleaseStatusName]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$ReleaseStatusName"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <td>
                <xsl:value-of select="$dateReleasedValue" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <td>
                <xsl:call-template name="processOwner">
                  <xsl:with-param name="curoccele" select="$impactedItem"></xsl:with-param>
                </xsl:call-template>
              </td>
            </tr>
          </xsl:for-each>

        </tbody>
      </table>
    </xsl:if>
  </xsl:template>

  <xsl:template name="processImplementsItems">
    <xsl:param name="primaryObjectID"/>
    <xsl:variable name="general_relation" select="/plm:PLMXML/plm:GeneralRelation[@subType='CMImplements'][substring(substring-before(@relatedRefs,' '),2)=$primaryObjectID]"/>
    <xsl:if test="count($general_relation) > 0 ">
      <h4>Implements</h4>
      <table>
        <tbody>
          <tr>
            <th>ID/Revision-Name</th>
            <th width="20%">Type</th>
            <th width="10%">Status</th>
            <th width="10%">Date</th>
            <th>Owner</th>
          </tr>
          <xsl:for-each select="$general_relation">
            <xsl:variable name="relatedRefs">
              <xsl:value-of select="@relatedRefs"/>
            </xsl:variable>
            <xsl:variable name="general_test_id" select="substring(substring-after($relatedRefs,' '),2)"/>
            <xsl:variable name="implementItem" select="/plm:PLMXML/plm:ProductRevision[@id=$general_test_id]"/>
            <xsl:variable name="objectName" select="$implementItem/@name"/>
            <xsl:variable name="object" select="$implementItem/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
            <xsl:variable name="revision" select="$implementItem/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>
            <xsl:variable name="last_mod_date" select="$implementItem/plm:UserData/plm:UserValue[@title='last_mod_date']/@value"/>
            <xsl:variable name="last_date_value" select="translate($last_mod_date,'T',' ')"/>
            <xsl:variable name="realeaseStatusRef" select="$implementItem/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
            <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
            <xsl:variable name="dateReleased" select="substring-before($implementItem/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>
            <xsl:variable name="dateReleasedValue" select="translate($dateReleased,'T',' ')"/>
            <xsl:variable name="SubType" select="$implementItem/@subType"/>
            <xsl:variable name="userRef" select="substring-after($implementItem/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
            <xsl:variable name="owning_user" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId"/>
            <xsl:variable name="groupRef" select="substring-after($implementItem/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
            <xsl:variable name="owningGroup" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]/plm:UserData/plm:UserValue[@title='name']/@value"/>

            <tr>
              <td>
                <xsl:value-of select="$object"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <!--<td>
                <xsl:value-of select="$SubType"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td>
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$SubType]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$SubType"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <!--<td>
                <xsl:value-of select="$ReleaseStatusName" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td style="width:1px;white-space:nowrap;">
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$ReleaseStatusName]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$ReleaseStatusName"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <td>
                <xsl:value-of select="$dateReleasedValue" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <td>
                <xsl:call-template name="processOwner">
                  <xsl:with-param name="curoccele" select="$implementItem"></xsl:with-param>
                </xsl:call-template>
              </td>
            </tr>
          </xsl:for-each>

        </tbody>
      </table>
    </xsl:if>
  </xsl:template>

  <xsl:template name="processImplementedByItems">
    <xsl:param name="primaryObjectID"/>
    <xsl:variable name="implementedByItems" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]/plm:UserData/plm:UserValue[@title='CMImplementedBy']/plm:UserList/plm:Item"/>
    <xsl:if test="count($implementedByItems) > 0 ">
      <h4>Implemented By</h4>
      <table>
        <tbody>
          <tr>
            <th>ID/Revision-Name</th>
            <th width="20%">Type</th>
            <th width="10%">Status</th>
            <th width="10%">Date</th>
            <th>Owner</th>
          </tr>
          <xsl:for-each select="$implementedByItems">
            <xsl:variable name="implementedByRef" select="./@value"/>
            <xsl:variable name="implementedByItem" select="/plm:PLMXML/plm:ProductRevision[@id=$implementedByRef]"/>
            <xsl:variable name="object" select="$implementedByItem/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
            <xsl:variable name="SubType" select="$implementedByItem/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
            <xsl:variable name="realeaseStatusRef" select="$implementedByItem/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
            <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
            <xsl:variable name="dateReleased" select="substring-before($implementedByItem/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>

            <tr>
              <td>
                <xsl:value-of select="$object"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <!--<td>
                <xsl:value-of select="$SubType"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td>
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$SubType]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$SubType"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <!--<td>
                <xsl:value-of select="$ReleaseStatusName" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td style="width:1px;white-space:nowrap;">
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$ReleaseStatusName]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$ReleaseStatusName"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <td>
                <xsl:value-of select="$dateReleased" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <td>
                <xsl:call-template name="processOwner">
                  <xsl:with-param name="curoccele" select="$implementedByItem"></xsl:with-param>
                </xsl:call-template>
              </td>
            </tr>

          </xsl:for-each>
        </tbody>
      </table>
    </xsl:if>
  </xsl:template>

  <xsl:template name="processAttachments">
    <xsl:param name="primaryObjectID"/>
    <xsl:variable name="associated_refAttachment" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]/plm:AssociatedDataSet[@role='CMReferences']"/>
    <xsl:variable name="associated_refItem" select="/plm:PLMXML/plm:GeneralRelation[@subType='CMReferences'][substring(substring-before(@relatedRefs,' '),2)=$primaryObjectID]"/>

    <xsl:if test="count($associated_refAttachment) or count($associated_refItem) > 0 ">
      <h4>Attachments</h4>
      <table>
        <tbody>
          <tr>
            <th>ID/Revision-Name</th>
            <th width="20%">Type</th>
            <th width="10%">Status</th>
            <th width="10%">Date</th>
            <th>Owner</th>
          </tr>
          <xsl:for-each select="$associated_refAttachment">
            <xsl:variable name="dataSetRef" select="./@dataSetRef"/>
            <xsl:variable name="attachmentId" select="substring-after($dataSetRef,'#')"/>
            <xsl:variable name="attachments" select="/plm:PLMXML/*[@id=$attachmentId]"/>
            <xsl:variable name="object" select="$attachments/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
            <xsl:variable name="SubType" select="$attachments/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
            <xsl:variable name="realeaseStatusRef" select="$attachments/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
            <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
            <xsl:variable name="dateReleased" select="substring-before($attachments/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>
            <xsl:variable name="dateReleasedValue" select="translate($dateReleased,'T',' ')"/>
            <xsl:variable name="userRef" select="substring-after($attachments/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
            <xsl:variable name="owningUser" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId"/>
            <xsl:variable name="groupRef" select="substring-after($attachments/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
            <xsl:variable name="owningGroup" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]/plm:UserData/plm:UserValue[@title='name']/@value"/>

            <tr>
              <td>
                <xsl:value-of select="$object"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <!--<td>
                <xsl:value-of select="$SubType"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td>
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$SubType]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$SubType"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <!-- <td>
                <xsl:value-of select="$ReleaseStatusName" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td style="width:1px;white-space:nowrap;">
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$ReleaseStatusName]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$ReleaseStatusName"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <td>
                <xsl:value-of select="$dateReleasedValue" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <td>
                <xsl:call-template name="processOwner">
                  <xsl:with-param name="curoccele" select="$attachments"></xsl:with-param>
                </xsl:call-template>
              </td>
            </tr>
          </xsl:for-each>

          <xsl:for-each select="$associated_refItem">
            <xsl:variable name="relatedRefs" select="./@relatedRefs"/>
            <xsl:variable name="relationReferenceItem" select="substring(substring-after($relatedRefs,' '),2)"/>
            <xsl:variable name="referenceItem" select="/plm:PLMXML/*[@id=$relationReferenceItem]"/>
            <xsl:variable name="object" select="$referenceItem/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
            <xsl:variable name="SubType" select="$referenceItem/@subType"/>
            <xsl:variable name="realeaseStatusRef" select="$referenceItem/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
            <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
            <xsl:variable name="dateReleased" select="substring-before($referenceItem/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>
            <xsl:variable name="dateReleasedValue" select="translate($dateReleased,'T',' ')"/>
            <xsl:variable name="userRef" select="substring-after($referenceItem/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
            <xsl:variable name="owningUser" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId"/>
            <xsl:variable name="groupRef" select="substring-after($referenceItem/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
            <xsl:variable name="owningGroup" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]/plm:UserData/plm:UserValue[@title='name']/@value"/>

            <tr>
              <td>
                <xsl:value-of select="$object"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <!--<td>
                <xsl:value-of select="$SubType"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>-->
              <td>
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$SubType]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$SubType"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <!--<td>
                <xsl:value-of select="$ReleaseStatusName" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td> -->
              <td style="width:1px;white-space:nowrap;">
                <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$ReleaseStatusName]"/>
                <xsl:choose>
                  <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                    <xsl:value-of select="$valueObj/@display_value"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$ReleaseStatusName"/>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <td>
                <xsl:value-of select="$dateReleasedValue" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <td>
                <xsl:call-template name="processOwner">
                  <xsl:with-param name="curoccele" select="$referenceItem"></xsl:with-param>
                </xsl:call-template>
              </td>
            </tr>
          </xsl:for-each>

        </tbody>
      </table>
    </xsl:if>
  </xsl:template>

  <xsl:template name="processWorkflowReviews">
    <xsl:param name="primaryObjectID"/>
    <!-- <xsl:variable name="ECR" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]"/> -->
    <xsl:variable name="ECRWorkFlows" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]/plm:UserData/plm:UserValue[@title='fnd0AllWorkflows']/plm:UserList/plm:Item"/>
    <xsl:if test="count($ECRWorkFlows) > 0 ">

      <h3>ECR Review/Approval</h3>

      <xsl:for-each select="$ECRWorkFlows">
        <xsl:variable name="ECRWorkFlowID" select="./@value"/>
        <xsl:variable name="ECRWorkflowProcesses" select="/plm:PLMXML/plm:WorkflowProcess[@templateName='Submit ECR for Review' or @templateName='Submit ECR for Modification']"/>
        <xsl:for-each select="$ECRWorkflowProcesses">
          <xsl:variable name="dataRef" select="./plm:UserData/plm:UserValue/@dataRef"/>
          <xsl:if test="substring-after($dataRef,'#')=$ECRWorkFlowID">
            <!-- Workflow Header -->
            <xsl:variable name="processName" select="./plm:UserData/plm:UserValue[@title='object_name']/@value"/>
            <xsl:variable name="processDesc" select="./plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
            <xsl:variable name="submissionDate" select="./plm:Task/plm:UserData/plm:UserValue[@title='creation_date']/@value"/>
            <table class="NoBorder" id="NoBorderProperties">
              <tbody>
                <tr>
                  <td style="width:80px;">Process Name: </td>
                  <td>
                    <xsl:value-of select="concat($processName, ' (Submitted on: ' , $submissionDate , ')')"/>
                  </td>
                </tr>
                <tr>
                  <td style="width:80px;">Description: </td>
                  <td>
                    <xsl:value-of select="$processDesc"/>
                  </td>
                </tr>
              </tbody>
            </table>
            <!-- Workflow Process -->
            <table>
              <tbody>
                <tr>
                  <th width="20%">Task</th>
                  <th width="20%">Reviewer</th>
                  <th width="10%">Status</th>
                  <th width="10%">Date</th>
                  <th>Comments</th>
                </tr>
                <!-- ECR Tasks -->
                <xsl:variable name="ECRTasks" select="./plm:Task"/>
                <xsl:for-each select="$ECRTasks">
                  <xsl:variable name="UserDataRef" select="./plm:UserData"/>
                  <xsl:variable name="TaskType" select="$UserDataRef/plm:UserValue[@title='task_type']/@value"/>

                  <xsl:if test="($TaskType='EPMPerformSignoffTask' or 'EPMSelectSignoffTask')">

                    <xsl:variable name="TaskName" select="$UserDataRef/plm:UserValue[@title='fnd0AliasTaskName']/@value"/>
                    <xsl:variable name="creationDate" select="$UserDataRef/plm:UserValue[@title='creation_date']/@value"/>
                    <xsl:variable name="PerformerRef" select="substring-after($UserDataRef/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
                    <xsl:variable name="Performer" select=" concat(/plm:PLMXML/plm:User[@id=$PerformerRef]/plm:UserData/plm:UserValue[@title='user_name']/@value, ' (', /plm:PLMXML/plm:User[@id=$PerformerRef]/plm:UserData/plm:UserValue[@title='user_id']/@value, ')') "/>
                    <xsl:variable name="StartDate" select="substring-before($UserDataRef/plm:UserValue[@title='fnd0StartDate']/@value,'T')"/>
                    <xsl:variable name="EndDate" select="substring-before($UserDataRef/plm:UserValue[@title='fnd0EndDate']/@value,'T')"/>
                    <xsl:variable name="DueDate" select="substring-before($UserDataRef/plm:UserValue[@title='due_date']/@value,'T')"/>
                    <xsl:variable name="Comments" select="$UserDataRef/plm:UserValue[@title='comments']/@value"/>
                    <xsl:variable name="TaskResult" select="$UserDataRef/plm:UserValue[@title='task_result']/@value"/>

                    <xsl:variable name="signoff" select="./plm:Signoff"/>
                    <xsl:for-each select="$signoff">
                      <xsl:variable name="signofOrgRef" select="substring-after(./@organisationMemberRef,'#')"/>
                      <xsl:variable name="decision" select="./@decision"/>
                      <xsl:variable name="decisionDate" select="substring-before(./@decisionDate,'T')"/>
                      <xsl:variable name="comment" select="./plm:Description"/>

                      <tr>
                        <td>
                          <xsl:call-template name="processTaskName">
                            <xsl:with-param name="taskName" select="$TaskName"/>
                          </xsl:call-template>
                          <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                        </td>
                        <td>
                          <!--<xsl:value-of select="$Performer" /> -->
                          <xsl:call-template name="processOrgUser">
                            <xsl:with-param name="orgRef" select="$signofOrgRef"/>
                          </xsl:call-template>
                          <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                        </td>
                        <!-- <td style="text-align:left;">
							<xsl:if test="$TaskResult != 'Unset'">
							  <xsl:value-of select="$TaskResult" />
							  <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
							</xsl:if>
						  </td> -->
                        <td class="AppRej">
                          <xsl:if test="$decision != 'Unset'">
                            <xsl:value-of select="$decision" />
                          </xsl:if>
                        </td>
                        <td>
                          <xsl:value-of select="$decisionDate" />
                          <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                        </td>
                        <td>
                          <xsl:value-of select="$comment" />
                          <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                        </td>
                      </tr>

                    </xsl:for-each>

                  </xsl:if>
                  <xsl:if test="($TaskType='EPMDoTask' ) and ($ECRTasks[@name='Assign Design Team'] or $ECRTasks[@name='Modify ECR'])">

                    <xsl:variable name="TaskName" select="$UserDataRef/plm:UserValue[@title='fnd0AliasTaskName']/@value"/>
                    <xsl:variable name="creationDate" select="$UserDataRef/plm:UserValue[@title='creation_date']/@value"/>
                    <xsl:variable name="PerformerRef" select="substring-after($UserDataRef/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
                    <xsl:variable name="Performer" select=" concat(/plm:PLMXML/plm:User[@id=$PerformerRef]/plm:UserData/plm:UserValue[@title='user_name']/@value, ' (', /plm:PLMXML/plm:User[@id=$PerformerRef]/plm:UserData/plm:UserValue[@title='user_id']/@value, ')') "/>
                    <xsl:variable name="StartDate" select="substring-before($UserDataRef/plm:UserValue[@title='fnd0StartDate']/@value,'T')"/>
                    <xsl:variable name="EndDate" select="substring-before($UserDataRef/plm:UserValue[@title='fnd0EndDate']/@value,'T')"/>
                    <xsl:variable name="DueDate" select="substring-before($UserDataRef/plm:UserValue[@title='due_date']/@value,'T')"/>
                    <xsl:variable name="Comments" select="$UserDataRef/plm:UserValue[@title='comments']/@value"/>
                    <xsl:variable name="TaskResult" select="$UserDataRef/plm:UserValue[@title='task_result']/@value"/>

                    <tr>
                      <td>
                        <xsl:call-template name="processTaskName">
                          <xsl:with-param name="taskName" select="$TaskName"/>
                        </xsl:call-template>
                        <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                      </td>
                      <td>
                        <xsl:value-of select="$Performer" />
                        <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                      </td>
                      <td style="text-align:left;">
                        <xsl:if test="$TaskResult != 'Unset'">
                          <xsl:value-of select="$TaskResult" />
                          <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                        </xsl:if>
                      </td>
                      <td>
                        <xsl:value-of select="$EndDate" />
                        <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                      </td>
                      <td>
                        <xsl:value-of select="$Comments" />
                        <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                      </td>
                    </tr>

                  </xsl:if>
                </xsl:for-each>
              </tbody>
            </table>
          </xsl:if>
        </xsl:for-each>
      </xsl:for-each>
    </xsl:if>
  </xsl:template>

  <!-- Process attribute Templates -->

  <xsl:template name="processTaskName">
    <xsl:param name="taskName"></xsl:param>
    <xsl:choose>
      <xsl:when test="contains($taskName,':')">
        <xsl:value-of select="substring-before($taskName,':')"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$taskName"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>


  <xsl:template name="processReleaseStatusName">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:for-each select ="$curoccele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item" >
      <xsl:variable name="releaseStatusID" select="@value" />
      <xsl:variable name="statusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$releaseStatusID]/@name" />
      <xsl:value-of select="$statusName"/>
    </xsl:for-each>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processConsolidatedStatus">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:variable name="StatusList" select="$curoccele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item"/>
    <xsl:choose>
      <xsl:when test="count($StatusList)=0">
        <xsl:variable name="ECRReviewProcesses" select="/plm:PLMXML/plm:WorkflowProcess[@templateName='Submit ECR for Review']"/>
        <xsl:variable name="ECRModifyProcesses" select="/plm:PLMXML/plm:WorkflowProcess[@templateName='Submit ECR for Modification']"/>
        <xsl:choose>

          <xsl:when test="count($ECRModifyProcesses)>0 and ($curoccele/plm:UserData/plm:UserValue[@title='fnd0InProcess']/@value)='True' and
						($curoccele/plm:UserData/plm:UserValue[@title='CMClosure']/@value)='Open' and 
							($curoccele/plm:UserData/plm:UserValue[@title='CMDisposition']/@value)='None' and 
								($curoccele/plm:UserData/plm:UserValue[@title='CMMaturity']/@value)='Elaborating'">
            <xsl:variable name="conStatus" select="'Modify'"/>
            <xsl:value-of select="$conStatus"/>
          </xsl:when>

          <xsl:when test="($curoccele/plm:UserData/plm:UserValue[@title='CMClosure']/@value)='Open' and 
							($curoccele/plm:UserData/plm:UserValue[@title='CMDisposition']/@value)='None' and 
								($curoccele/plm:UserData/plm:UserValue[@title='CMMaturity']/@value)='Elaborating'">
            <xsl:variable name="conStatus" select="'Saved'"/>
            <xsl:value-of select="$conStatus"/>
          </xsl:when>

          <xsl:when test="($curoccele/plm:UserData/plm:UserValue[@title='CMClosure']/@value)='Open' and 
							($curoccele/plm:UserData/plm:UserValue[@title='CMDisposition']/@value)='None' and 
								($curoccele/plm:UserData/plm:UserValue[@title='CMMaturity']/@value)='Reviewing'">
            <xsl:variable name="conStatus" select="'Submitted'"/>
            <xsl:value-of select="$conStatus"/>
          </xsl:when>

          <xsl:when test="($curoccele/plm:UserData/plm:UserValue[@title='CMClosure']/@value)='Open' and 
							($curoccele/plm:UserData/plm:UserValue[@title='CMDisposition']/@value)='Disapproved' and 
								($curoccele/plm:UserData/plm:UserValue[@title='CMMaturity']/@value)='Elaborating'">
            <xsl:variable name="conStatus" select="'Disapproved'"/>
            <xsl:value-of select="$conStatus"/>
          </xsl:when>

          <xsl:when test="($curoccele/plm:UserData/plm:UserValue[@title='CMClosure']/@value)='Open' and 
							($curoccele/plm:UserData/plm:UserValue[@title='CMDisposition']/@value)='Disapproved' and 
								($curoccele/plm:UserData/plm:UserValue[@title='CMMaturity']/@value)='Reviewing'">
            <xsl:variable name="conStatus" select="'Re-Submitted'"/>
            <xsl:value-of select="$conStatus"/>
          </xsl:when>

          <xsl:when test="($curoccele/plm:UserData/plm:UserValue[@title='CMClosure']/@value)='Open' and 
							($curoccele/plm:UserData/plm:UserValue[@title='CMDisposition']/@value)='Investigate' and 
								($curoccele/plm:UserData/plm:UserValue[@title='CMMaturity']/@value)='Elaborating'">
            <xsl:variable name="conStatus" select="'Investigate'"/>
            <xsl:value-of select="$conStatus"/>
          </xsl:when>

          <xsl:otherwise>
            <xsl:variable name="conStatus" select="'Saved'"/>
            <xsl:value-of select="$conStatus"/>
          </xsl:otherwise>

        </xsl:choose>
      </xsl:when>
      <xsl:otherwise>
        <xsl:for-each select ="$StatusList" >
          <xsl:variable name="statusID" select="./@value" />
          <xsl:variable name="status" select="/plm:PLMXML/plm:ReleaseStatus[@id=$statusID]/@name" />
          <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$status]"/>
          <xsl:choose>
            <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
              <xsl:value-of select="$valueObj/@display_value"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:value-of select="$status"/>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:for-each>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="processOwner">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:variable name="ownerRef" select="substring-after($curoccele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
    <xsl:variable name="userId" select="/plm:PLMXML/plm:User[@id=$ownerRef]/plm:UserData/plm:UserValue[@title='user_id']/@value"/>
    <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$ownerRef]/plm:UserData/plm:UserValue[@title='user_name']/@value"/>
    <xsl:variable name="user" select="concat($userName, ' (',$userId,')')"/>
    <!-- 	<xsl:variable name="user" select="concat(' (',$userId,')')"/>
		<xsl:value-of select="$userName"/> -->
    <xsl:value-of select="$user"/>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processOwningGroup">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:variable name="groupRef" select="substring-after($curoccele/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
    <xsl:variable name="orgRef" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]"/>
    <xsl:variable name="groupName" select="$orgRef/plm:UserData/plm:UserValue[@title='name']/@value"/>
    <xsl:value-of select="$groupName"/>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processUsers">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:variable name="userRef" select="substring-after($curoccele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
    <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$userRef]/plm:UserData/plm:UserValue[@title='user_name']/@value"/>
    <xsl:value-of select="$userName"/>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processOrgUser">
    <xsl:param name="orgRef"></xsl:param>
    <xsl:if test="$orgRef!=''">
      <xsl:variable name="orgMemberRef" select="substring-after(/plm:PLMXML/plm:OrganisationMember[@id=$orgRef]/@memberRef,'#')"/>
      <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$orgMemberRef]/plm:UserData/plm:UserValue[@title='user_name']/@value"/>
      <xsl:variable name="userId" select="/plm:PLMXML/plm:User[@id=$orgMemberRef]/plm:UserData/plm:UserValue[@title='user_id']/@value"/>
      <xsl:variable name="user" select="concat($userName, ' (',$userId,')')"/>
      <xsl:value-of select="$user"/>
    </xsl:if>
  </xsl:template>

  <xsl:template name="processGroups">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:variable name="groupRef" select="substring-after($curoccele/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
    <xsl:variable name="org" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]"/>
    <!-- <xsl:variable name="groupName" select="$org/@name"/> -->
    <xsl:variable name="groupName" select="$org/plm:UserData/plm:UserValue[@title='name']/@value"/>
    <xsl:value-of select="$groupName"/>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processCustomers">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:for-each select ="$curoccele/plm:UserData/plm:UserValue[@title='get6Customers']/plm:UserList/plm:Item" >
      <xsl:variable name="customerName" select="@value" />
      <xsl:value-of select="$customerName"/>
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processPOs">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:for-each select ="$curoccele/plm:UserData/plm:UserValue[@title='get6OrderNo']/plm:UserList/plm:Item">
      <xsl:variable name="orderNo" select="@value" />
      <xsl:value-of select="$orderNo"/>
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processOnTrackItems">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:for-each select ="$curoccele/plm:UserData/plm:UserValue[@title='get6OnTrackItems']/plm:UserList/plm:Item">
      <xsl:variable name="onTrackItems" select="@value" />
      <xsl:value-of select="$onTrackItems"/>
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processCopies">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:for-each select ="$curoccele/plm:UserData/plm:UserValue[@title='get6Copies']/plm:UserList/plm:Item">
      <xsl:variable name="copies" select="@value" />
      <xsl:value-of select="$copies"/>
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processBoolean">
    <xsl:param name="boolValue"></xsl:param>
    <xsl:variable name="boolVal" select="$boolValue"/>
    <xsl:if test='$boolVal = "True"'>
      <xsl:text>Yes</xsl:text>
    </xsl:if>
    <xsl:if test='$boolVal = "False"'>
      <xsl:text>No</xsl:text>
    </xsl:if>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

</xsl:stylesheet>
