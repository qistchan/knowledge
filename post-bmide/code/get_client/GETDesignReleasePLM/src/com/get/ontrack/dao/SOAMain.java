package com.get.ontrack.dao;

import java.util.Map;

import org.apache.commons.httpclient.HttpState;

import com.teamcenter.schemas.soa._2006_03.exceptions.InvalidCredentialsException;
import com.teamcenter.schemas.soa._2006_03.exceptions.InvalidUserException;
import com.teamcenter.services.strong.core.SessionService;
import com.teamcenter.services.strong.core._2011_06.Session.Credentials;
import com.teamcenter.soa.SoaConstants;
import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.SsoCredentials;
import com.teamcenter.soa.client.model.strong.User;
import com.teamcenter.soa.exceptions.CanceledOperationException;

public class SOAMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		GETDao dao = new GETDao();
		try {
			
	//		dao.ssoLogin(null);
			
			/*SOAMain main= new SOAMain();
			SSOLogin ssoLog = main.new SSOLogin();
			ssoLog.loginthruSSO();*/
			//loginthruSSO();
			
			//dao.login_test("502533437","502533437");//("502561438","502561438");


		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/*	public static void main(String[] args)
    {
        try
        {
        	GETDao dao = new GETDao();
        	dao.setUserID("826350");
        	dao.setPassword("826350");
        	dao.setHost("http://3.234.162.199:8180/drspoc");

            String ssoAppId = "TCDRS";
            String lSSOURL = "http://01HW749901:8180/ssols";
            //drsMain.login();
            drsMain.ssoLogin(ssoAppId, lSSOURL, "test");
            System.out.println(drsMain.getDrawingRevInfo("84A201748/0", "GET9DrawingRevision")); //"000027/D", "GET4DrawingImageRevision", "000028/C", "GET4PartListRevision"
            //System.out.println(drsMain.getPrevRevInfo("000027/D", "GET4DrawingImageRevision"));
            drsMain.logout();
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }*/
	public class SSOLogin 
	{
		String ssoLoginURL = "http://vdcald04459.ics.cloud.ge.com/tc_sso_login";
		String ssoAppID = "Teamcenter";
		String serverAddress = "http://vdcald04459.ics.cloud.ge.com:8080/tc";

		Connection   ssoConnection = null;
		Map mapp = null;

		/*public SSOLogin()
		{		
		}*/

		public Map loginthruSSO()
		{
			try 
			{
				SsoCredentials	ssoCredentials = new SsoCredentials(ssoLoginURL, ssoAppID 	);

				ssoCredentials.setUserPassword(null, null,	"test1");
				ssoCredentials.setGroupRole("", "");

				String[] credentials =	ssoCredentials.getCredentials(new 	InvalidUserException());

				ssoConnection = new Connection(serverAddress, new	HttpState(), ssoCredentials, SoaConstants.REST, "HTTP", false);

				SessionService ssoSessionSvc =	SessionService.getService( ssoConnection );   

				

		            Credentials credentialsInst = new Credentials();
		            credentialsInst.user = credentials[0];
		            credentialsInst.password = credentials[1];
		            //credentialsInst.group = credentials[2];
		            //credentialsInst.role = credentials[3];
		            credentialsInst.descrimator = "test12";

		          //  com.teamcenter.services.strong.core._2006_03.Session.LoginResponse loginResponseObj = ssoSessionSvc.loginSSO(credentials[0], credentials[1], credentials[2], credentials[3], credentials[4]);
				com.teamcenter.services.strong.core._2011_06.Session.LoginResponse out =	ssoSessionSvc.loginSSO(credentialsInst);
				//com.teamcenter.services.strong.core._2006_03.Session.LoginResponse out =	ssoSessionSvc.loginSSO(credentials[0], credentials[1], credentials[2], credentials[3], credentials[4]);
				mapp = out.serverInfo;
				

				//getProperties();
			}
			catch(CanceledOperationException e1) 
			{
				e1.printStackTrace();
			}
			catch (InvalidCredentialsException e) 
			{
				e.printStackTrace();
			}

			return mapp;
		}

	}

}

