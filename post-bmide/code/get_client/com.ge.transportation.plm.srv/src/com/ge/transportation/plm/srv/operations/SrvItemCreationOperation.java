package com.ge.transportation.plm.srv.operations;

import java.util.List;

import com.ge.transportation.plm.srv.constants.Constants;
import com.ge.transportation.plm.srv.dialogs.ServiceItemCreationDialog;
import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.kernel.ServiceData;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentFolder;
import com.teamcenter.rac.kernel.TCComponentGroup;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCComponentItemType;
import com.teamcenter.rac.kernel.TCComponentRole;
import com.teamcenter.rac.kernel.TCComponentUser;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.services.rac.manufacturing.DataManagementService;
import com.teamcenter.services.rac.manufacturing._2009_10.DataManagement;
import com.teamcenter.services.rac.manufacturing._2009_10.DataManagement.CreateIn;
import com.teamcenter.services.rac.manufacturing._2009_10.DataManagement.CreateInput;
import com.teamcenter.services.rac.manufacturing._2009_10.DataManagement.CreateResponse;
import com.teamcenter.soa.exceptions.NotLoadedException;

/**
* <h1>ServiceAttributesOperation</h1>
* This class implements creation of 
* Services Form Type for Services functionality 
* using the Custom UI
*
* @author  Sudheer Arikere
* @version 1.0
* @since   2017-09-07
*/

public class SrvItemCreationOperation {
	int CreateResponse = 0;
	CreateResponse resp = null;
	TCSession m_session 	= (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
	private TCComponentUser  		user  		 = null ;
	private TCComponentFolder  		userFolder  		 = null ;
	private TCComponentGroup      group		 = null ;
	private String userName					 = null ;
	private String groupName                 = null ;
	public static TCComponent tcc;

	public void createGetSrvItem() throws ServiceException, TCException{

		String id;
		DataManagement dmService = DataManagementService.getService(m_session);
		String itemid = ServiceItemCreationDialog.textModel.getText();
		String itemname = ServiceItemCreationDialog.Nametitle.getText();

		CreateIn createIn = new CreateIn();

		createIn.clientId = "Test";
		createIn.context = null;
		createIn.relationName = null;
		createIn.target = null;

		createIn.data.type = Constants.BusinessObjects.strGET6SrvPart;
		createIn.data.stringProps.put("item_id", itemid);
		createIn.data.stringProps.put("object_name", itemname);
		createIn.data.stringProps.put("object_desc", "Service Object Desc");

		CreateInput revCreateIn = new CreateInput();

		revCreateIn.type = Constants.BusinessObjects.strGET6SrvPartRev;
		revCreateIn.stringProps.put("item_revision_id", 0);
		revCreateIn.stringProps.put("object_desc", "Service Desc for ItemRev");


		resp = dmService.createObjects(new CreateIn[]{createIn});

		ServiceData sd = resp.serviceData;

		if(sd.sizeOfPartialErrors() > 0)
		{
			for (int i=0; i <= sd.sizeOfPartialErrors(); i++)
			{
				System.out.println(sd.getPartialError(i).getMessages());
			}
		}
		if (sd!=null)
		{
			tcc= sd.getCreatedObject(0);
			try
			{
				id = tcc.getProperty("item_id");
				newstuffoldertem(tcc);

			} catch (TCException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		CreateResponse = resp.output.length;

	}

	public void newstuffoldertem(TCComponent comp) {

		try
		{

			user       = m_session.getUser();
			userName   = user.getUserId();
			group      = m_session.getGroup();
			groupName  = group.getFullName();

			userFolder = user.getNewStuffFolder();
			userFolder.add("contents", comp);

		}
		catch(Exception ex)
		{
			System.out.println("Exception while getting group and role");

		}


	}
	/**
	 * Defect 1407
	 * The stringManupulate Method.
	 * This method takes the string as input and the prepares the output string 
	 * for the TypeTier Attribute on the GET Service Form
	 * output string format : "Tier 0+,Tier 1+C"
	 */
	
	public String stringManupulate(String str){
		String T="Tier ";
		String s1 = null,s2 = null,s3 = null,s4 = null,s5 = null,s6= null,s7= null,s8= null,s9= null,s10= null,s11 = null,s12,s13,s14;
		String strnw = str.replace(" ", "");
		String [] ary=strnw.split(",");
		if (ary.length>1){
			for (int ii = 0;ii<ary.length;ii++){
			if (ary[ii].toString().equals("0"))
				 s1=T.concat(ary[ii]); 	
			else if  (ary[ii].toString().equals("0+"))
				s2=T.concat(ary[ii]); 	
			else if (ary[ii].toString().equals("1"))
				s3=T.concat(ary[ii]); 	
			else if (ary[ii].toString().equals("1+"))
				s4=T.concat(ary[ii]); 	
			else if (ary[ii].toString().equals("1+C"))
				s5=T.concat(ary[ii]); 
			else if (ary[ii].toString().equals("2"))
				s6=T.concat(ary[ii]); 
			else if (ary[ii].toString().equals("2+"))
				s7=T.concat(ary[ii]); 
			else if (ary[ii].toString().equals("3"))
				s8=T.concat(ary[ii]); 
			else if (ary[ii].toString().equals("4C"))
				s9=T.concat(ary[ii]); 
			else if (ary[ii].toString().equals("4T"))
				s10=T.concat(ary[ii]); 
			else if (ary[ii].toString().equals("NA"))
				s11="NA";
		  }
			s12=s1+","+s2+","+s3+","+s4+","+s5+s6+","+s7+","+s8+","+s9+","+s10+","+s11;
			s13=s12.replace("null,", "");
			s14=s13.replace("null", "");
			if (s14.endsWith(",")) {
				s14 = s14.substring(0, s14.length()-1);
				}
			return  s14;
	
	   }else
	   {
		   if (ary[0].toString().equals("NA")){
			   return ary[0];   
		   }else {
			   return T.concat(ary[0]);
		   }
	   }
		  
	}
	
	public void propertiesUpdate(TCComponent sele) {

		try {
			//Item attribute Update
			String attr1 = sele.getProperty(Constants.BusinessObjects.Properties.strEngrProdLine);
			String attr2 = sele.getProperty(Constants.BusinessObjects.Properties.strECC);
			String attr3 = sele.getProperty(Constants.BusinessObjects.Properties.strECCN);
			String attr4 = sele.getProperty(Constants.BusinessObjects.Properties.strECCNSource);
			String attr6 = sele.getProperty(Constants.BusinessObjects.Properties.strCCC);
			String attr7 = sele.getProperty(Constants.BusinessObjects.Properties.strIPClassification);
			String itemattr1 = sele.getProperty(Constants.BusinessObjects.Properties.strCriticalPart);
			String itemattr2 = sele.getProperty(Constants.BusinessObjects.Properties.strObjEvidence);
			String itemattr3 = sele.getProperty(Constants.BusinessObjects.Properties.strHomologation);
			
			if (!attr1.isEmpty()){
				tcc.setProperty(Constants.BusinessObjects.Properties.strEngrProdLine, attr1.toString());	//get6EngrProdLine
			}
			if (!attr2.isEmpty()){
				if (attr2.toString().equals("ECC-No")){
				tcc.setProperty(Constants.BusinessObjects.Properties.strECC, "No"); 
				}
				if (attr2.toString().equals("ECC-EU Loco")){
					tcc.setProperty(Constants.BusinessObjects.Properties.strECC, "EUL"); 
					}
				if (attr2.toString().equals("ECC-US Marine")){
					tcc.setProperty(Constants.BusinessObjects.Properties.strECC, "USM"); 
					}
				if (attr2.toString().equals("ECC-US Marpol Marine")){
					tcc.setProperty(Constants.BusinessObjects.Properties.strECC, "USMM"); 
					}
				if (attr2.toString().equals("ECC-US EPA Loco")){
					tcc.setProperty(Constants.BusinessObjects.Properties.strECC, "USL"); 
					}
			}
			if (!attr3.isEmpty()){
				tcc.setProperty(Constants.BusinessObjects.Properties.strECCN, attr3.toString());	//get6ECCN
			}
			if (!attr4.isEmpty()){
				if (attr4.toString().equals("EC 1.1 - EC Guidance Document")){
					tcc.setProperty(Constants.BusinessObjects.Properties.strECCNSource, "ECDoc"); 			// get6ECCNSource
				}else if (attr4.toString().equals("EC Tagger")) {
					tcc.setProperty(Constants.BusinessObjects.Properties.strECCNSource, "ECTagger");
				}	
			}
			if (!attr6.isEmpty()){
				if (attr6.toString().equals("CCC-No")){
					tcc.setProperty(Constants.BusinessObjects.Properties.strCCC, "No");
				}else if (attr6.toString().equals("CCC-AAR S580-2005")) {
					tcc.setProperty(Constants.BusinessObjects.Properties.strCCC, "AAR");
				}
			}
			if (!itemattr1.isEmpty()){
				tcc.setProperty(Constants.BusinessObjects.Properties.strCriticalPart, itemattr1.toString());
			}
			if (!itemattr2.isEmpty()){
				tcc.setProperty(Constants.BusinessObjects.Properties.strObjEvidence, itemattr2.toString());
			}
			if (!itemattr3.isEmpty()){
				tcc.setProperty(Constants.BusinessObjects.Properties.strHomologation, itemattr3.toString());
			}
			if (!attr7.isEmpty()){
				tcc.setProperty(Constants.BusinessObjects.Properties.strIPClassification, attr7.toString());	// ip_classification
			}

			// Item Revision attribute Update
			TCComponentItemRevision rev = ((TCComponentItem)sele).getLatestItemRevision();

			String attrIr = rev.getProperty(Constants.BusinessObjects.Properties.strCTQ);			// get6CTQ
			String attrIr1 = rev.getProperty(Constants.BusinessObjects.Properties.strDataModel);		//get6DataModel
			String attrIr2 = rev.getProperty(Constants.BusinessObjects.Properties.strEngMB);			//get6EngMB
			String attrIr3 = rev.getProperty(Constants.BusinessObjects.Properties.strObjWt);
			String attrIr4 = rev.getProperty(Constants.BusinessObjects.Properties.strObjWtUOM);
			String attrIr5 = rev.getProperty(Constants.BusinessObjects.Properties.strOverallHeight);
			String attrIr6 = rev.getProperty(Constants.BusinessObjects.Properties.strOverallLength);
			String attrIr7 = rev.getProperty(Constants.BusinessObjects.Properties.strOverallWidth);
			String attrIr8 = rev.getProperty(Constants.BusinessObjects.Properties.strvOerallUOM);

			TCComponentItemRevision srev = ((TCComponentItem)tcc).getLatestItemRevision();
			if (!attrIr.isEmpty()){
				srev.setProperty(Constants.BusinessObjects.Properties.strCTQ, attrIr.toString());	
			}

			if (!attrIr1.isEmpty()){
				if (attrIr1.toString().equals("Model Centric (Model + Drawing)")){
					srev.setProperty(Constants.BusinessObjects.Properties.strDataModel, "MC");
				}else if (attrIr1.toString().equals("Model Based (PMI)")) {
					srev.setProperty(Constants.BusinessObjects.Properties.strDataModel, "MB");
				}
			}

			if (!attrIr2.isEmpty()){
				srev.setProperty(Constants.BusinessObjects.Properties.strEngMB, attrIr2.toString());	
			}
			if (!attrIr3.isEmpty()){
				srev.setProperty(Constants.BusinessObjects.Properties.strObjWt, attrIr3.toString());
			}
            if (!attrIr4.isEmpty()){
            	srev.setProperty(Constants.BusinessObjects.Properties.strObjWtUOM, attrIr4.toString());
 
			}
            if (!attrIr5.isEmpty()){
            	srev.setProperty(Constants.BusinessObjects.Properties.strOverallHeight, attrIr5.toString());
			}
            if (!attrIr6.isEmpty()){
            	srev.setProperty(Constants.BusinessObjects.Properties.strOverallLength, attrIr6.toString());
            }
            if (!attrIr7.isEmpty()){
            	srev.setProperty(Constants.BusinessObjects.Properties.strOverallWidth, attrIr7.toString());
            }
            if (!attrIr8.isEmpty()){
            	srev.setProperty(Constants.BusinessObjects.Properties.strvOerallUOM, attrIr8.toString());
            }
 		 
			//Update the Service Form
			TCComponent srvForm = rev.getRelatedComponent(Constants.BusinessObjects.Relations.strServFormRel);
			String frmEngineFamily = srvForm.getProperty(Constants.BusinessObjects.Properties.strEngineFamily);	//get9EngineFamily
			String frm2 = srvForm.getProperty(Constants.BusinessObjects.Properties.strCompID);		//get9ComponentID
			String frm3 = srvForm.getProperty(Constants.BusinessObjects.Properties.strPositionTracked);	//get6PositionTracked
			String frm4 = srvForm.getProperty(Constants.BusinessObjects.Properties.strRepairable);		//get6Repairable
			String frm5 = srvForm.getProperty(Constants.BusinessObjects.Properties.strSerialized);		//get6Serialized
			String frm6 = srvForm.getProperty(Constants.BusinessObjects.Properties.strServiceable);		//get6Serviceable
			String frm7 = srvForm.getProperty(Constants.BusinessObjects.Properties.strServiceItemType);		//get6ServiceItemType
			String frm8 = srvForm.getProperty(Constants.BusinessObjects.Properties.strTierType);    
		//	property pr = srvForm.getPropertyObject(Constants.BusinessObjects.Properties.strTierType);
			TCComponent srvFrm = srev.getRelatedComponent(Constants.BusinessObjects.Relations.strServFormRel);

			if (!frmEngineFamily.isEmpty()){
				srvFrm.setProperty(Constants.BusinessObjects.Properties.strEngineFamily, frmEngineFamily.toString());	
			}
			if (!frm2.isEmpty()){
			//	System.out.println("frm2"+frm2);
				srvFrm.setProperty(Constants.BusinessObjects.Properties.strCompID, frm2.toString()); 
			}
			if (!frm3.isEmpty()){
				srvFrm.setProperty(Constants.BusinessObjects.Properties.strPositionTracked, frm3.toString());	
			}
			if (!frm4.isEmpty()){
				srvFrm.setProperty(Constants.BusinessObjects.Properties.strRepairable, frm4.toString());	
			}
			if (!frm5.isEmpty()){
				srvFrm.setProperty(Constants.BusinessObjects.Properties.strSerialized, frm5.toString());	
			}
			if (!frm6.isEmpty()){
				srvFrm.setProperty(Constants.BusinessObjects.Properties.strServiceable, frm6.toString());	
			}
			if (!frm7.isEmpty()){
				srvFrm.setProperty(Constants.BusinessObjects.Properties.strServiceItemType, frm7.toString());	
			}
			if (!frm8.isEmpty()){
				System.out.println("frm8..."+frm8);
				// Defect 1407
				String updatestr = stringManupulate(frm8);
				System.out.println("finally string..."+updatestr);
				srvFrm.setProperty(Constants.BusinessObjects.Properties.strTierType,updatestr);
				}

		} catch (TCException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


	}

}
