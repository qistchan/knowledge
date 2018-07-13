<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:plm="http://www.plmxml.org/Schemas/PLMXMLSchema"
    xmlns:crf="http://ExternalFunction.setFile"
    xmlns:GET="Lookup table for Display Names">

  <!-- 
  exclude-result-prefixes="GET"
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

  <xsl:key name='TcDisplayName' match='object' use='@actual_value' />

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
        <title>Engineering Change Notice Report</title>
        <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
        <script type="text/javascript">
          function displayDate_bak()
          {
          var d=new Date();
          var weekday=new Array("Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday");
          var monthname=new Array("Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec");
          document.write(monthname[d.getMonth()] + " ");
          document.write(d.getDate() + ", ");
          document.write(d.getFullYear() + " ");
          document.write(weekday[d.getDay()] + " ");
          }

          function displayDate()
          {
          var d=new Date();
          var week_days = new Array("Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday");
          var month_names = new Array("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec");
          var curr_date = ((d.getDate())>=10)? (d.getDate()) : '0' + (d.getDate());
          var curr_month = d.getMonth();
          var curr_year = d.getFullYear();
          var curr_hour =  ((d.getHours())>=10)? (d.getHours()) : '0' + (d.getHours());
          var curr_minute = ((d.getMinutes())>=10)? (d.getMinutes()) : '0' + (d.getMinutes());
          document.write(week_days[d.getDay()] + ", " + curr_date + "-" + month_names[curr_month] + "-" + curr_year + " " + curr_hour + ":" + curr_minute );
          }

          function dateFormat( dateValue)
          {
          var m_names = new Array("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec");
          var d = new Date("2018-03-07T17:23:32Z");
          var curr_date = ((d.getDate())>=10)? (d.getDate()) : '0' + (d.getDate());
          var curr_month = d.getMonth();
          var curr_year = d.getFullYear();
          var curr_hour =  ((d.getHours())>=10)? (d.getHours()) : '0' + (d.getHours());
          var curr_minute = ((d.getMinutes())>=10)? (d.getMinutes()) : '0' + (d.getMinutes());
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

          #border {
          width:700px;
          margin:auto;
          margin-left:0px;
          margin-right:auto;
          margin-top: 5px;
          margin-bottom: 5px;
          vertical-align: center;
          border-collapse: collapse;
          font-size:11px;
          font-family:"GE Inspira Sans", "GE Inspira", "Trebuchet MS", Arial, Helvetica, sans-serif;
          }

          #border th, #border td {
          font-family:"GE Inspira Sans", "GE Inspira", "Trebuchet MS", Arial, Helvetica, sans-serif;
          color: black;
          padding: 2px;
          border: 1px solid #f2f2f2;
          }
          #border th {
          background-color: #e6e6e6;
          text-align: center;
          font-weight: bold;
          }
          #border td {
          text-align:left;
          }
          td:nth-child(odd) {
          <!--               font-weight: bold;
              width:1px;
              white-space:nowrap; -->
          }
          td:nth-child(even) {
          }

          tr:hover
          {
          <!-- background-color: yellow; -->
          }

          td:hover {
          <!-- background-color: #ddd; -->
          }

          #borderless{
          width:700px;
          margin:auto;
          margin-left:0px;
          margin-right:auto;
          margin-top: 10px;
          margin-bottom: auto;
          vertical-align: center;
          border-collapse: collapse;
          font-size:11px;
          font-family:"GE Inspira Sans", "GE Inspira", "Trebuchet MS", Arial, Helvetica, sans-serif;
          }

          #borderless th, #borderless td {
          font-family:"GE Inspira Sans", "GE Inspira", "Trebuchet MS", Arial, Helvetica, sans-serif;
          color: black;
          border: none;
          padding: 2px;
          }

          #borderless td {
          text-align:left;
          }



          h1 {color: #007acc; font-family:GE Inspira Sans; font-weight: bold; margin-left:100px;}
          h2 {color: #007acc; font-family:GE Inspira Sans; font-weight: bold; }
          h3 {color: #007acc; font-family:GE Inspira Sans; font-weight: bold; }
          h4 {color: #007acc; font-family:GE Inspira Sans; font-weight: bold; }
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
          width:1px;
          white-space:nowrap;
          }

          #Properties td:nth-child(even)
          {
          <!-- background-color: #f2f2f2; -->
          width:50%;
          }

          #Properties tr:hover
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
          left: 310px;
          width:80px;
          height:30px;
          background-color: #3399ff;
          border: none;
          color: white;
          <!-- padding: 15px 32px; -->
          text-align: center;
          text-decoration: none;
          display: inline-block;
          font-size: 12px;
          font-weight: bold;
          margin: 4px 2px;
          cursor: pointer;

          }

        </style>

        <!--         <P style="position:absolute;left:500px;font-weight:bold;">
            <script type="text/javascript">displayDate()</script>
        </P> -->


        <table style="width:700px;margin-top:30px;vertical-align:center;font-family:GE Inspira Sans;">
          <tbody>
            <tr>
              <th style="background-color:#e6e6e6;color:#007acc;text-align:center;font-size:20px;font-weight:bold;width:1px;white-space:nowrap;">Engineering Change Notice Report</th>
            </tr>
          </tbody>
        </table>

        <xsl:call-template name="createCL">
          <xsl:with-param name="occStr" select="$occStr"/>
        </xsl:call-template>

        <div>
          <h5  style="position:absolute;left:300px;font-weight:normal;">&#169; GE Transportation</h5>
          <h5  style="font-weight:normal;">
            Date Printed: <script type="text/javascript">displayDate()</script>
          </h5>
          <p>
            <input class="myButton" id="printpagebutton" type="button"  value="PRINT" onclick="printpage()"/>
          </p>

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
        <xsl:when test="($occele/@subType)='GET6ECNRevision'">

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

          <xsl:variable name="requestoruser" select="substring-after($occele/plm:UserData/plm:UserValue[@title='cm0Requestor']/@dataRef,'#')"/>
          <xsl:variable name="Role" select="substring-after(/plm:PLMXML/plm:OrganisationMember[@id=$requestoruser]/@roleRef,'#')" />
          <xsl:variable name="Role_user" select="/plm:PLMXML/plm:Role[@id=$Role]/@name" />
          <xsl:variable name="Organization" select="substring-after(/plm:PLMXML/plm:OrganisationMember[@id=$requestoruser]/@organizationRef,'#')" />
          <xsl:variable name="Organization_user" select="/plm:PLMXML/plm:Organization[@id=$Organization]/@name" />

          <xsl:variable name="Member" select="substring-after(/plm:PLMXML/plm:OrganizationMember[@id=$requestoruser]/@memberRef,'#')" />
          <xsl:variable name="Member_user" select="/plm:PLMXML/plm:User[@id=$Member]/@userId" />

          <xsl:variable name="Requestor" select="concat($Organization_user,'/',$Role_user,'/',$Member_user)"/>
          <xsl:variable name="Change_Specialist" select="substring-after($occele/plm:UserData/plm:UserValue[@title='ChangeSpecialist1']/@dataRef,'#')"/>
          <xsl:variable name="ChangeCpecialist" select="substring-after(/plm:PLMXML/plm:ResourcePool[@id=$Change_Specialist]/@organizationRef,'#')" />
          <xsl:variable name="ChangeCpecialist_org" select="/plm:PLMXML/plm:Organization[@id=$ChangeCpecialist]/@name" />
          <xsl:variable name="namedRef" select="/plm:PLMXML/plm:ExternalFile[@format='xlsx']/@locationRef" />

          <!-- Custom Properties -->

          <xsl:variable name="productLine" select="$occele/plm:UserData/plm:UserValue[@title='get6EngrProdLine']/@value"/>

          <xsl:variable name="materialAtMfgLoc" select="$occele/plm:UserData/plm:UserValue[@title='get6IsMatlAtMfgLocn']/@value"/>
          <xsl:variable name="materialAtServiceLoc" select="$occele/plm:UserData/plm:UserValue[@title='get6IsMatlAtServiceLocn']/@value"/>
          <xsl:variable name="changeToExistDesign" select="$occele/plm:UserData/plm:UserValue[@title='get6ModDesignCutIn']/@value"/>
          <xsl:variable name="weightImpactNo" select="$occele/plm:UserData/plm:UserValue[@title='get6WtImpactNo']/@value"/>
          <xsl:variable name="partsCatalogs" select="$occele/plm:UserData/plm:UserValue[@title='get6PartsCatalogs']/@value"/>
          <xsl:variable name="CAMCMM" select="$occele/plm:UserData/plm:UserValue[@title='get6PatToolsNC']/@value"/>
          <xsl:variable name="CASECNNo" select="$occele/plm:UserData/plm:UserValue[@title='get6CASECNNumber']/@value"/>


          <xsl:variable name="bypassValidation" select="$occele/plm:UserData/plm:UserValue[@title='get6BypassCheckmate']/@value"/>
          <xsl:variable name="bypassComments" select="$occele/plm:UserData/plm:UserValue[@title='get6BypassComments']/@value"/>
          <xsl:variable name="bypassReason" select="$occele/plm:UserData/plm:UserValue[@title='get6BypassReason']/@value"/>

          <xsl:variable name="reasonCode" select="$occele/plm:UserData/plm:UserValue[@title='get6ReasonCode']/@value"/>
          <xsl:variable name="reason" select="$occele/plm:UserData/plm:UserValue[@title='get6ChangeReason']/@value"/>
          <xsl:variable name="reasonBackground" select="$occele/plm:UserData/plm:UserValue[@title='get6ReasonForChg']/@value"/>


          <!-- Header Section -->
          <!--<xsl:call-template name="HeaderSection">
            <xsl:with-param name="Synopsis" select="$Synopsis"/>
            <xsl:with-param name="productId" select="$productid"/>
            <xsl:with-param name="revisionName" select="$revisionname"/>
            <xsl:with-param name="subType" select="$subType"/>
         </xsl:call-template> -->

          <!-- Header Details -->

          <table id="borderless" style="width:600px;">
            <tbody>
              <tr>
                <td colspan="2" rowspan="1" style="width:99%;font-weight:bold;width:1px;white-space:nowrap;">
                  <xsl:value-of select="$object"/>
                </td>
                <td style="font-weight:bold;width:1px;white-space:nowrap;">ECN Status: </td>
                <td class="AppRej" style="width:1px;white-space:nowrap;">
                  <xsl:call-template name="StatusConsolidated">
                    <xsl:with-param name="curoccele" select="$occele"/>
                  </xsl:call-template>
                </td>
              </tr>
              <tr>
                <td style="font-weight: bold;width:1px;white-space:nowrap;">Group ID:</td>
                <td>
                  <xsl:call-template name="processGroups">
                    <xsl:with-param name="curoccele" select="$occele"/>
                  </xsl:call-template>
                </td>
                <td style="font-weight: bold;width:1px;white-space:nowrap;">ECN IP:</td>
                <td style="width:1px;white-space:nowrap;">
                  <xsl:value-of select="$ipClassification"/>
                </td>
              </tr>
              <tr>
                <td style="width:80px;font-weight: bold;">Owner: </td>
                <td>
                  <xsl:value-of select="$owningUserName"/>[<xsl:value-of select="$owningUserId"/>]
                </td>
                <td></td>
                <td></td>
              </tr>
            </tbody>
          </table>

          <!-- Solution Items -->
          <xsl:call-template name="SolutionItemsProcess">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

          <!-- ECN Reason For Change -->
          <table id="borderless">
            <tbody>
              <tr>
                <td style="font-weight:bold;width:1px;white-space:nowrap;">Reason Code:</td>
                <td style="width:50%;">
                  <xsl:value-of select="$reasonCode"/>
                </td>
                <td style="font-weight:bold;width:1px;white-space:nowrap;">Reason: </td>
                <td style="width:50%;">
                  <xsl:value-of select="$reason"/>
                </td>
              </tr>
              <tr>
                <td colspan="4" rowspan="1" style="font-weight:bold;width:1px;white-space:nowrap;">ECN Summary:</td>
              </tr>
              <tr>
                <td colspan="4" rowspan="1" >
                  <xsl:value-of select="$reasonBackground"/>
                </td>
              </tr>
            </tbody>
          </table>

          <!-- ECN Material Disposition -->
          <xsl:call-template name="EngrDisposition">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

          <table id="border">
            <tbody>
              <tr>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Engineering Product Line</td>
                <td>
                  <xsl:value-of select="$productLine"/>
                </td>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Material at any Mfg Location</td>
                <td>
                  <xsl:value-of select="$materialAtMfgLoc"/>
                </td>
              </tr>
              <tr>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Change to an existing design?</td>
                <td>
                  <xsl:value-of select="$changeToExistDesign"/>
                </td>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Material at any Service Location</td>
                <td>
                  <xsl:value-of select="$materialAtServiceLoc"/>
                </td>
              </tr>
              <tr>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">CAS ECN No.</td>
                <td>
                  <xsl:value-of select="$CASECNNo"/>
                </td>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Parts Catalogs</td>
                <td>
                  <xsl:value-of select="$partsCatalogs"/>
                </td>
              </tr>
              <tr>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Weight Impact Number</td>
                <td>
                  <xsl:value-of select="$weightImpactNo"/>
                </td>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">CAM / CMM</td>
                <td>
                  <xsl:value-of select="$CAMCMM"/>
                </td>
              </tr>
            </tbody>
          </table>


          <table id="border">
            <tbody>
              <tr>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Customers</td>
                <td>
                  <xsl:call-template name="processCustomers">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>
              <tr>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Order Numbers</td>
                <td>
                  <xsl:call-template name="processPOs">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>
              <tr>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Planner Codes</td>
                <td>
                  <xsl:call-template name="processPlannerCodes">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>
              <tr>
                <td style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">Copies</td>
                <td>
                  <xsl:call-template name="processCopies">
                    <xsl:with-param name="curoccele" select="$occele"></xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>

            </tbody>
          </table>


          <!-- ECN Approval -->
          <xsl:call-template name="ECNApprovalProcess">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

          <!-- All ECN references -->
          <xsl:call-template name="ReferenceItems">
            <xsl:with-param name="primaryObjectID" select="$occid"/>
          </xsl:call-template>

        </xsl:when>
      </xsl:choose>
    </xsl:if>
  </xsl:template>



  <xsl:template name="EngrDisposition">
    <xsl:param name="primaryObjectID"/>
    <xsl:variable name="ecn" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]"/>
    <xsl:variable name="TableRows" select="$ecn/plm:UserData/plm:UserValue[@title='get6ECNEngrDisp']/plm:UserList/plm:Item"/>
    <xsl:if test="count($TableRows) > 0 ">
      <h4>Recommended Engineering Material Disposition And Detailed Change Description</h4>
    </xsl:if>
    <xsl:for-each select="$TableRows">
      <xsl:variable name="TableRowId">
        <xsl:value-of select="@value"/>
      </xsl:variable>

      <table id="borderless">
        <tbody>
          <xsl:variable name="Tablecolumns" select="/plm:PLMXML/plm:ProductRevision/plm:TableRow[@id=$TableRowId]/plm:TableColumn"/>
          <xsl:for-each select="$Tablecolumns">

            <xsl:variable name="tableColumnName" select="./@title"/>
            <xsl:if test="$tableColumnName='get6PartNo'">
              <tr>
                <td style="font-weight:bold;width:1px;white-space:nowrap;">Part Number:</td>
                <td style="width:99%;">
                  <xsl:value-of select="./@value"/>
                </td>
              </tr>
            </xsl:if>

            <xsl:if test="$tableColumnName='get6Disposition'">
              <tr>
                <td style="font-weight:bold;width:1px;white-space:nowrap;">Material Disposition:</td>
                <td style="width:99%;">
                  <xsl:value-of select="./@value"/>
                </td>
              </tr>
            </xsl:if>

            <xsl:if test="$tableColumnName='get6ChangeDesc'">
              <tr>
                <td colspan="2" rowspan="1" style="font-weight: bold;width:1px;white-space:nowrap;">Description:</td>
              </tr>
              <tr>
                <td colspan="2" rowspan="1">
                  <xsl:value-of select="./@value"/>
                </td>
              </tr>

            </xsl:if>
          </xsl:for-each>
        </tbody>
      </table>

    </xsl:for-each>
  </xsl:template>



  <xsl:template name="SolutionItemsProcess">
    <xsl:param name="primaryObjectID"/>
    <!-- <h3>Solution Items</h3> -->
    <table id="border">
      <tbody>
        <tr>
          <th>ID/Revision-Name</th>
          <th>Type</th>
          <th>Status</th>
          <th>Date</th>
          <th>Owner</th>
        </tr>

        <xsl:variable name="general_relation" select="/plm:PLMXML/plm:GeneralRelation[@subType='CMHasSolutionItem'][substring(substring-before(@relatedRefs,' '),2)=$primaryObjectID]"/>
        <xsl:for-each select="$general_relation">
          <xsl:variable name="relatedRefs" select="./@relatedRefs"/>
          <xsl:variable name="relationSolnItem" select="substring(substring-after($relatedRefs,' '),2)"/>
          <xsl:variable name="solutionItem" select="/plm:PLMXML/*[@id=$relationSolnItem]"/>

          <xsl:variable name="itemId" select="$solutionItem/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
          <xsl:variable name="revision" select="$solutionItem/plm:UserData/plm:UserValue[@title='item_revision_id']/@value"/>
          <xsl:variable name="object" select="$solutionItem/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
          <xsl:variable name="objectName" select="$solutionItem/@name"/>
          <xsl:variable name="SubType" select="$solutionItem/@subType"/>
          <xsl:variable name="realeaseStatusRef" select="$solutionItem/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
          <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
          <xsl:variable name="dateReleased" select="substring-before($solutionItem/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>
          <xsl:variable name="dateReleasedValue" select="translate($dateReleased,'T',' ')"/>
          <xsl:variable name="userRef" select="substring-after($solutionItem/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
          <xsl:variable name="owningUser" select="/plm:PLMXML/plm:User[@id=$userRef]/@userId"/>
          <xsl:variable name="groupRef" select="substring-after($solutionItem/plm:UserData/plm:UserValue[@title='owning_group']/@dataRef,'#')"/>
          <xsl:variable name="owningGroup" select="/plm:PLMXML/plm:Organisation[@id=$groupRef]/plm:UserData/plm:UserValue[@title='name']/@value"/>

          <tr>
            <td style="width:1px;white-space:nowrap;">
              <xsl:value-of select="$object"/>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td style="width:1px;white-space:nowrap;">
              <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$SubType]"/>
              <xsl:choose>
                <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                  <xsl:value-of select="$valueObj/@display_value"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$SubType"/>
                </xsl:otherwise>
              </xsl:choose>
              <!-- <xsl:value-of select="crf:getReportDisplayText($SubType,$report_locale)"/>  -->
            </td>
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
            <td style="text-align:center;width:1px;white-space:nowrap;">
              <xsl:value-of select="$dateReleasedValue" />
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td style="width:1px;white-space:nowrap;">
              <xsl:call-template name="processOwner">
                <xsl:with-param name="curoccele" select="$solutionItem"></xsl:with-param>
              </xsl:call-template>
            </td>
          </tr>
        </xsl:for-each>

      </tbody>
    </table>

  </xsl:template>


  <xsl:template name="ImplementsItemTask">
    <xsl:param name="primaryObjectID"/>

    <xsl:variable name="general_relation" select="/plm:PLMXML/plm:GeneralRelation[@subType='CMImplements'][substring(substring-before(@relatedRefs,' '),2)=$primaryObjectID]"/>

    <xsl:if test="count($general_relation) > 0 ">
      <h3>Implements</h3>
      <table id="border">
        <tbody>
          <tr>
            <th>ECR</th>
            <th>Revision</th>
            <th>Name</th>
            <th>Owner</th>
            <th>Group</th>
            <th>Status</th>
            <th>Date</th>
          </tr>
          <xsl:for-each select="$general_relation">
            <xsl:variable name="relatedRefs">
              <xsl:value-of select="@relatedRefs"/>
            </xsl:variable>
            <xsl:variable name="general_test_id" select="substring(substring-after($relatedRefs,' '),2)"/>
            <xsl:variable name="implementItem" select="/plm:PLMXML/plm:ProductRevision[@id=$general_test_id]"/>
            <xsl:variable name="objectName" select="$implementItem/@name"/>
            <xsl:variable name="ecrId" select="$implementItem/plm:UserData/plm:UserValue[@title='item_id']/@value"/>
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
              <td style="width:1px;white-space:nowrap;">
                <xsl:value-of select="$ecrId"/>
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <td style="text-align:center;width:1px;white-space:nowrap;">
                <xsl:value-of select="$revision" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <td style="width:1px;white-space:nowrap;">
                <xsl:value-of select="$objectName" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
              <td style="width:1px;white-space:nowrap;">
                <xsl:call-template name="processOwner">
                  <xsl:with-param name="curoccele" select="$implementItem"></xsl:with-param>
                </xsl:call-template>
              </td>
              <td style="width:1px;white-space:nowrap;">
                <xsl:call-template name="processOwningGroup">
                  <xsl:with-param name="curoccele" select="$implementItem"></xsl:with-param>
                </xsl:call-template>
              </td>
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
              <td style="text-align:center;width:1px;white-space:nowrap;">
                <xsl:value-of select="$dateReleasedValue" />
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
              </td>
            </tr>
          </xsl:for-each>

        </tbody>
      </table>
    </xsl:if>
  </xsl:template>


  <xsl:template name="ECNApprovalProcess">
    <xsl:param name="primaryObjectID"/>

    <!-- <xsl:variable name="ecn" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]"/> -->
    <xsl:variable name="ECNWorkFlows" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]/plm:UserData/plm:UserValue[@title='fnd0AllWorkflows']/plm:UserList/plm:Item"/>
    <h4>ECN Review/Approval</h4>
    <xsl:for-each select="$ECNWorkFlows">
      <xsl:variable name="ECNWorkFlowID" select="./@value"/>
      <xsl:variable name="ECNWorkflowProcesses" select="/plm:PLMXML/plm:WorkflowProcess[@templateName='Submit ECN for Review']"/>
      <xsl:for-each select="$ECNWorkflowProcesses">
        <xsl:variable name="dataRef" select="./plm:UserData/plm:UserValue[@title='root_task']/@dataRef"/>
        <xsl:if test="substring-after($dataRef,'#')=$ECNWorkFlowID">
          <!-- Workflow Header -->
          <xsl:variable name="processName" select="./plm:UserData/plm:UserValue[@title='object_name']/@value"/>
          <xsl:variable name="processDesc" select="./plm:UserData/plm:UserValue[@title='object_desc']/@value"/>
          <table id="borderless">
            <tbody>
              <tr>
                <td style="font-weight: bold;width:1px;white-space:nowrap;">Process Name:</td>
                <td>
                  <xsl:value-of select="$processName"/>
                </td>
              </tr>
              <tr>
                <td style="font-weight:bold;width:1px;white-space:nowrap;">Description:</td>
                <td>
                  <xsl:value-of select="$processDesc"/>
                </td>
              </tr>
            </tbody>
          </table>
          <!-- Workflow Process -->
          <table id="border">
            <tbody>
              <tr>
                <th>Task</th>
                <th width="20%">Reviewer</th>
                <th width="10%">Decision</th>
                <th width="10%">Date</th>
                <th>Comments</th>
              </tr>
              <!-- ECN Tasks -->
              <xsl:variable name="ecnTasks" select="./plm:Task"/>
              <xsl:for-each select="$ecnTasks">
                <xsl:variable name="UserDataRef" select="./plm:UserData"/>
                <xsl:variable name="TaskType" select="$UserDataRef/plm:UserValue[@title='task_type']/@value"/>

                <xsl:if test="($TaskType='EPMPerformSignoffTask')">

                  <xsl:variable name="TaskName" select="$UserDataRef/plm:UserValue[@title='fnd0AliasTaskName']/@value"/>
                  <xsl:variable name="PerformerRef" select="substring-after($UserDataRef/plm:UserValue[@title='last_mod_user']/@dataRef,'#')"/>
                  <xsl:variable name="Performer" select=" concat(/plm:PLMXML/plm:User[@id=$PerformerRef]/plm:UserData/plm:UserValue[@title='user_name']/@value, ' (', /plm:PLMXML/plm:User[@id=$PerformerRef]/plm:UserData/plm:UserValue[@title='user_id']/@value, ')') "/>
                  <xsl:variable name="StartDate" select="substring-before($UserDataRef/plm:UserValue[@title='fnd0StartDate']/@value,'T')"/>
                  <xsl:variable name="EndDate" select="substring-before($UserDataRef/plm:UserValue[@title='fnd0EndDate']/@value,'T')"/>
                  <xsl:variable name="DueDate" select="substring-before($UserDataRef/plm:UserValue[@title='due_date']/@value,'T')"/>
                  <xsl:variable name="Comments" select="$UserDataRef/plm:UserValue[@title='comments']/@value"/>
                  <xsl:variable name="TaskResult" select="$UserDataRef/plm:UserValue[@title='task_result']/@value"/>

                  <xsl:variable name="signoff" select="./plm:Signoff"/>
                  <xsl:variable name="signofOrgRef" select="substring-after($signoff/@organisationMemberRef,'#')"/>
                  <xsl:variable name="decision" select="$signoff/@decision"/>
                  <xsl:variable name="decisionDate" select="substring-before($signoff/@decisionDate,'T')"/>
                  <xsl:variable name="comment" select="$signoff/plm:Description"/>

                  <tr>
                    <td style="width:1px;white-space:nowrap;">
                      <xsl:value-of select="$TaskName"/>
                    </td>
                    <td>
                      <xsl:call-template name="processOrgUser">
                        <xsl:with-param name="orgRef" select="$signofOrgRef"/>
                      </xsl:call-template>
                    </td>
                    <td class="AppRej" style="text-align:center;">
                      <xsl:if test="$decision != 'Unset'">
                        <xsl:value-of select="$decision" />
                      </xsl:if>
                    </td>
                    <td style="text-align:center;">
                      <xsl:value-of select="$decisionDate" />
                    </td>
                    <td>
                      <xsl:value-of select="$comment" />
                    </td>
                  </tr>
                </xsl:if>
              </xsl:for-each>
            </tbody>
          </table>
        </xsl:if>
      </xsl:for-each>
    </xsl:for-each>


    <!-- <xsl:variable name="WorkflowProcess" select="/plm:PLMXML/plm:WorkflowProcess[@templateName='Submit ECN for Review']"/> -->



    <!--     <xsl:if test="count($WorkflowTasks) > '0'">
        <tr>
        <td valign="top"  style="text-align:left;font-weight: bold;width:1px;white-space:nowrap;">
          <xsl:value-of select="count($WorkflowTasks)"/>
          <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
        </td>
        </tr>
    </xsl:if> -->
  </xsl:template>

  <!-- Process All References ECR, MCN & Datasets-->
  <xsl:template name="ReferenceItems">
    <xsl:param name="primaryObjectID"/>


    <!-- <xsl:if test="count($implementsRelation) > 0 "> -->
    <h4>References</h4>
    <table id="border">
      <tbody>
        <tr>
          <th>ID/Revision-Name</th>
          <th>Type</th>
          <th>Status</th>
          <th>Date</th>
          <th>Owner</th>
        </tr>

        <!-- Process Implements (ECR)-->
        <xsl:variable name="implementsRelation" select="/plm:PLMXML/plm:GeneralRelation[@subType='CMImplements'][substring(substring-before(@relatedRefs,' '),2)=$primaryObjectID]"/>
        <xsl:for-each select="$implementsRelation">
          <xsl:variable name="relatedRefs" select="./@relatedRefs"/>

          <xsl:variable name="ecrRefID" select="substring(substring-after($relatedRefs,' '),2)"/>
          <xsl:variable name="implementItem" select="/plm:PLMXML/plm:ProductRevision[@id=$ecrRefID]"/>
          <xsl:variable name="object" select="$implementItem/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
          <xsl:variable name="type" select="$implementItem/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
          <xsl:variable name="realeaseStatusRef" select="$implementItem/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
          <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
          <xsl:variable name="dateReleased" select="substring-before($implementItem/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>

          <tr>
            <td>
              <xsl:value-of select="$object"/>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td style="width:1px;white-space:nowrap;">
              <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$type]"/>
              <xsl:choose>
                <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                  <xsl:value-of select="$valueObj/@display_value"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$type"/>
                </xsl:otherwise>
              </xsl:choose>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
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
            <td style="text-align:center;width:1px;white-space:nowrap;">
              <xsl:value-of select="$dateReleased" />
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td>
              <xsl:call-template name="processOwner">
                <xsl:with-param name="curoccele" select="$implementItem"></xsl:with-param>
              </xsl:call-template>
            </td>
          </tr>
        </xsl:for-each>

        <!-- Process Implemented By (MCN)-->
        <xsl:variable name="implementedByItems" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]/plm:UserData/plm:UserValue[@title='CMImplementedBy']/plm:UserList/plm:Item"/>
        <xsl:for-each select="$implementedByItems">
          <xsl:variable name="implementedByRef" select="./@value"/>
          <xsl:variable name="implementedByItem" select="/plm:PLMXML/plm:ProductRevision[@id=$implementedByRef]"/>

          <xsl:variable name="object" select="$implementedByItem/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
          <xsl:variable name="type" select="$implementedByItem/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
          <xsl:variable name="realeaseStatusRef" select="$implementedByItem/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
          <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
          <xsl:variable name="dateReleased" select="substring-before($implementedByItem/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>

          <tr>
            <td style="width:1px;white-space:nowrap;">
              <xsl:value-of select="$object"/>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td style="width:1px;white-space:nowrap;">
              <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$type]"/>
              <xsl:choose>
                <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                  <xsl:value-of select="$valueObj/@display_value"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$type"/>
                </xsl:otherwise>
              </xsl:choose>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
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
            <td style="text-align:center;width:1px;white-space:nowrap;">
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

        <!-- Process CM Reference Items -->
        <xsl:variable name="referencesRelation" select="/plm:PLMXML/plm:GeneralRelation[@subType='CMReferences'][substring(substring-before(@relatedRefs,' '),2)=$primaryObjectID]"/>
        <xsl:for-each select="$referencesRelation">
          <xsl:variable name="relatedRefs" select="./@relatedRefs"/>

          <xsl:variable name="ecrRefID" select="substring(substring-after($relatedRefs,' '),2)"/>
          <xsl:variable name="referenceItem" select="/plm:PLMXML/*[@id=$ecrRefID]"/>
          <xsl:variable name="object" select="$referenceItem/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
          <xsl:variable name="type" select="$referenceItem/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
          <xsl:variable name="realeaseStatusRef" select="$referenceItem/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
          <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
          <xsl:variable name="dateReleased" select="substring-before($referenceItem/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>

          <tr>
            <td style="width:1px;white-space:nowrap;">
              <xsl:value-of select="$object"/>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td style="width:1px;white-space:nowrap;">
              <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$type]"/>
              <xsl:choose>
                <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                  <xsl:value-of select="$valueObj/@display_value"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$type"/>
                </xsl:otherwise>
              </xsl:choose>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
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
            <td style="text-align:center;width:1px;white-space:nowrap;">
              <xsl:value-of select="$dateReleased" />
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td>
              <xsl:call-template name="processOwner">
                <xsl:with-param name="curoccele" select="$referenceItem"></xsl:with-param>
              </xsl:call-template>
            </td>
          </tr>
        </xsl:for-each>

        <!-- Process Dataset Attachments directly to ECN -->
        <xsl:variable name="associatedDatasets" select="/plm:PLMXML/plm:ProductRevision[@id=$primaryObjectID]/plm:AssociatedDataSet[@role!='HasParticipant']"/>
        <xsl:for-each select="$associatedDatasets">
          <xsl:variable name="datasetID" select="substring-after(./@dataSetRef,'#')"/>
          <xsl:variable name="dataset" select="/plm:PLMXML/plm:DataSet[@id=$datasetID]"/>
          <xsl:variable name="object" select="$dataset/plm:UserData/plm:UserValue[@title='object_string']/@value"/>
          <xsl:variable name="type" select="$dataset/plm:UserData/plm:UserValue[@title='object_type']/@value"/>
          <xsl:variable name="realeaseStatusRef" select="$dataset/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item/@value"/>
          <xsl:variable name="ReleaseStatusName" select="/plm:PLMXML/plm:ReleaseStatus[@id=$realeaseStatusRef]/@name" />
          <xsl:variable name="dateReleased" select="substring-before($dataset/plm:UserData/plm:UserValue[@title='date_released']/@value,'T')"/>

          <tr>
            <td style="width:1px;white-space:nowrap;">
              <xsl:value-of select="$object"/>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td style="width:1px;white-space:nowrap;">
              <xsl:variable name="valueObj" select="document('')/*/GET:DisplayNames/child::object[@actual_value=$type]"/>
              <xsl:choose>
                <xsl:when test="not(normalize-space($valueObj/@actual_value)='')">
                  <xsl:value-of select="$valueObj/@display_value"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$type"/>
                </xsl:otherwise>
              </xsl:choose>
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
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
            <td style="text-align:center;width:1px;white-space:nowrap;">
              <xsl:value-of select="$dateReleased" />
              <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
            </td>
            <td>
              <xsl:call-template name="processOwner">
                <xsl:with-param name="curoccele" select="$dataset"></xsl:with-param>
              </xsl:call-template>
            </td>
          </tr>

        </xsl:for-each>
      </tbody>
    </table>
    <!-- </xsl:if> -->
  </xsl:template>

  <xsl:template name="StatusConsolidated">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:variable name="StatusList" select="$curoccele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item"/>
    <xsl:choose>
      <xsl:when test="count($StatusList)=0">
        <xsl:variable name="ECNWorkflowProcesses" select="/plm:PLMXML/plm:WorkflowProcess[@templateName='Submit ECN for Review']"/>
        <xsl:choose>

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


  <xsl:template name="StatusName">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:variable name="StatusList" select="$curoccele/plm:UserData/plm:UserValue[@title='release_status_list']/plm:UserList/plm:Item"/>
    <xsl:for-each select="$StatusList" >
      <xsl:variable name="statusID" select="./@value" />
      <xsl:variable name="status" select="/plm:PLMXML/plm:ReleaseStatus[@id=$statusID]/@name" />
      <xsl:value-of select="$status"/>
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
  </xsl:template>


  <xsl:template name="processOwner">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:variable name="ownerRef" select="substring-after($curoccele/plm:UserData/plm:UserValue[@title='owning_user']/@dataRef,'#')"/>
    <xsl:variable name="userId" select="/plm:PLMXML/plm:User[@id=$ownerRef]/plm:UserData/plm:UserValue[@title='user_id']/@value"/>
    <xsl:variable name="userName" select="/plm:PLMXML/plm:User[@id=$ownerRef]/plm:UserData/plm:UserValue[@title='user_name']/@value"/>
    <xsl:variable name="user" select="concat($userName, ' (',$userId,')')"/>
    <!--<xsl:variable name="user" select="concat(' (',$userId,')')"/>
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
    <xsl:for-each select="$curoccele/plm:UserData/plm:UserValue[@title='get6Customers']/plm:UserList/plm:Item" >
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

  <xsl:template name="processPlannerCodes">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:for-each select="$curoccele/plm:UserData/plm:UserValue[@title='get6PlannerCode']/plm:UserList/plm:Item" >
      <xsl:variable name="plannerCode" select="@value" />
      <xsl:value-of select="$plannerCode"/>
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

  <xsl:template name="processCopies">
    <xsl:param name="curoccele"></xsl:param>
    <xsl:for-each select="$curoccele/plm:UserData/plm:UserValue[@title='get6Copies']/plm:UserList/plm:Item" >
      <xsl:variable name="copy" select="@value" />
      <xsl:value-of select="$copy"/>
      <xsl:if test="position() != last()">
        <xsl:text>, </xsl:text>
      </xsl:if>
    </xsl:for-each>
    <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
  </xsl:template>

</xsl:stylesheet>