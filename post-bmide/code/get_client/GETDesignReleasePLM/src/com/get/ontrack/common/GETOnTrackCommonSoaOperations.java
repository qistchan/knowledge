package com.get.ontrack.common;

import java.util.ArrayList;
import java.util.List;


/*import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentPerson;
import com.teamcenter.rac.kernel.TCComponentUser;
import com.teamcenter.soa.client.model.TCCredentials;
import com.teamcenter.soa.client.model.TCException;
import com.teamcenter.soa.client.model.TCSession;*/
import com.teamcenter.soa.client.model.ServiceData;


public class GETOnTrackCommonSoaOperations {
	

	
/*	//Get TCComponent Object
	
	public static TCComponent getTcCompfromUid ( TCSession tcSession,  String uid ){
		
		TCComponent tcComp = null;
		DataManagementService dmService = null;
		
		try {
			dmService = DataManagementService.getService(tcSession);
			ServiceData sData = dmService.loadObjects(new String[] { uid });
			tcComp = sData.getPlainObject(0);
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return tcComp;
		}
		return tcComp;
	}
	
	public static String getItemIdfromUid ( TCSession tcSession,  String uid ){
		
		TCComponent tcComp = null;
		String itemId = null;
		DataManagementService dmService = null;
		
		try {
			dmService = DataManagementService.getService(tcSession);
			ServiceData sData = dmService.loadObjects(new String[] { uid });
			tcComp = sData.getPlainObject(0);
			if ( tcComp instanceof TCComponentItem ){
				TCComponentItem item = (TCComponentItem) tcComp;
				itemId = item.getProperty("item_id");
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return itemId;
		}
		return itemId;
	}
	
	

	//Get the current User Credentials
	public static String[] getCredentials( TCSession tcSession ){
			
			String[] userCredetials = null;
			String userName = null;
			String password = null;
			String group = null;

			try {
				
				userCredetials = new String[3];
				
				TCComponentUser user = tcSession.getUser();
				TCCredentials credentials = tcSession.getCredentials();
//				String userId = user.getUserId();
				
				userName = credentials.getUserName();
				
				if ( userName != null && userName.length() > 0 ){
					password = credentials.getPassword();
					group = user.getLoginGroup().getGroupName();
					
					userCredetials[0] = userName;
					userCredetials[1] = password;
					userCredetials[2] = group;
					
				}

				System.out.println( "User Id / Password / Group : " + userCredetials[0] + " / " +
						userCredetials[1] + " / " + userCredetials[2] );
				
			} catch (TCException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return userCredetials;
			}
			
			return userCredetials;
		}
	
	
public static String[] getPreferences( TCSession tcSession, String prefScope, String prefName ) {
		
	SessionService seService = null;
	String[] prefNamesList = null;
	
		try {
			seService = SessionService.getService(tcSession);
			
			ScopedPreferenceNames scopedPrefs = new ScopedPreferenceNames();
			if ( prefScope == null || prefScope.length() == 0 ){
				prefScope = "all";
			}
			scopedPrefs.scope = prefScope;
			scopedPrefs.names = new String[]{ prefName };
			

			MultiPreferencesResponse mPrefResp = seService.getPreferences( new ScopedPreferenceNames[]{ scopedPrefs } );	
			ReturnedPreferences[] preferences = mPrefResp.preferences;

			for (int inx = 0; inx < preferences.length; inx++) {
				prefNamesList = preferences[inx].values;
			}

		} catch (ServiceException e) {
			e.printStackTrace();
		}
		return prefNamesList;

	}
		
		
		//Get the user mail address
		public static String getUserMail(TCSession tcSession) {

			String mailAddress = null;

			try {

				TCComponentUser user = tcSession.getUser();
				List userInfoList = user.getUserInformation();

				for (int inx = 0; inx < userInfoList.size(); inx++) {
					if (userInfoList.get(inx) instanceof TCComponentPerson) {
						TCComponentPerson person = (TCComponentPerson) userInfoList.get(inx);
						mailAddress = person.getProperty("PA8")+"@"+ person.getProperty("PA10");
						System.out.println("Mail Address : " + mailAddress );
						
						System.out.println("PA1 : " + person.getProperty("PA1") );
							
					}
				}

			} catch (TCException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return mailAddress;
			}
			return mailAddress;
		}
		
		public static  boolean getWsObjProperties( final TCSession tcSession, final TCComponent obj, final String[] properties ){
			
			Boolean getPropertyStatus = true;
			DataManagementService dmService = null;
			
			dmService = DataManagementService.getService( tcSession );
			ServiceData sData = dmService.getProperties((TCComponent[]) new ModelObject[]{obj}, properties );
			if ( !ServiceDataError( sData ) ) {
				getPropertyStatus = false;
			}
			return getPropertyStatus;
		}
		*/
		//Error Verification Functionality		
		
		public static boolean ServiceDataError(final ServiceData data)
		{
			
				if(data.sizeOfPartialErrors() > 0)
				{
					for(int i = 0; i < data.sizeOfPartialErrors(); i++)
					{
						for(String msg :data.getPartialError(i).getMessages())
							System.out.println(msg);
					}
					return true;
				}
			

			return false;
		}
		
		public static  String ServiceDataErrorMsg(final ServiceData data)
		{
			List<String> strList = new ArrayList<String>();
			
				if(data.sizeOfPartialErrors() > 0)
				{
					for(int i = 0; i < data.sizeOfPartialErrors(); i++)
					{
						for(String msg :data.getPartialError(i).getMessages())
							strList.add(msg);
					}
				}
			
			return strList.toString();
		}

}
