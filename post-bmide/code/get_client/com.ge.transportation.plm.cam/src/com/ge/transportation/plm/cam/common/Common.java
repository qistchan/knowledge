package com.ge.transportation.plm.cam.common;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import javax.xml.bind.DatatypeConverter;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.swt.widgets.Shell;

import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentQuery;
import com.teamcenter.rac.kernel.TCComponentQueryType;
import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.kernel.TCTextService;

public class Common {	
	
	static TCSession m_session = (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
		
	public static TCComponent itemQuery(String Itemid) throws TCException
	{
		TCComponentItem dummyItem = null;
		TCComponentQueryType queryType = null;
		TCComponent[] dummyCompItem = null;
		if (Itemid != null)
		{
			try
			{
				queryType =	(TCComponentQueryType) m_session.getTypeComponent("ImanQuery");
				
			}
			catch (TCException ex)
			{
				ex.printStackTrace();
				Logger.write(ex);
				
			}
			
			if (queryType != null)
			{
				try
				{
					TCTextService textService = (TCTextService)m_session.getTextService();
					String query = textService.getTextValue("k_find_item_name");
					TCComponentQuery itemQuery =(TCComponentQuery) queryType.find(query);
					
					String entryNames[] = { "ItemID" };
					String values[] = { Itemid };
					
					dummyCompItem =	(TCComponent[]) itemQuery.execute(textService.getTextValues(entryNames), values);
					
				}
				catch (TCException ex)
				{
					ex.printStackTrace();
					Logger.write(ex);
					
				}
				
				if ((dummyCompItem != null && dummyCompItem.length != 0))
				{
					dummyItem = (TCComponentItem) dummyCompItem[0];
					
				}
				else
				{
					System.out.println("Unable to get ItemTag from Teamcenter");
					Logger.write("ERROR -"+"Unable to get ItemTag from Teamcenter");
					
				}
				
			}
			
		}
		return dummyItem;
		
	}

	public static boolean containsWhiteSpace(String testCode)
    {
        if(testCode != null)
        {
            for(int i = 0; i < testCode.length(); i++)
            {
                if(Character.isWhitespace(testCode.charAt(i)))
                {
                	return true;
                }
            }
        }
        return false;
    }
	
	public static void showError( String errorMessage )
	{			
		MessageBox messageBox1 = new MessageBox( getShell(), SWT.ERROR|SWT.OK);
		messageBox1.setText("Error");
		messageBox1.setMessage( errorMessage );
		messageBox1.open();
	}
  
    public static void showError( int errorCode, String errorMessage, String errorTitle  )
	{
		String mainMessage = null;
		mainMessage = "Error Message " + errorCode + " " + errorMessage;
		MessageBox messageBox1 = new MessageBox( getShell(), SWT.ERROR|SWT.OK);
		messageBox1.setText("Error");
		messageBox1.setMessage( mainMessage );
		messageBox1.open();		
	}
    
	public static Shell getShell() 
	{
		return null;
	}

	/*
	 * Check if dataset exists in DB.
	 * If yes then 0.
	 * Else return -1 if dataset item doesn't exists.
	 * Currently search is based on dataset_Name sequence.
	 */	
	/*Return the connection objects */
	public static Connection connectDB()
	{
		String URL = null;
		String USER = null ;
		String PASS = null;
		//apps:VzBybGRfQzBw:tsimdev1
		String PrefVal = m_session.getPreferenceService().getStringValue("GET.CAM.RIN.CREDENTIALS");
		if(!PrefVal.isEmpty())
		{
			String[] PrefValue = PrefVal.split(":");
			//Base64.Decoder decoder = Base64.getDecoder();
			String decoded = new String(DatatypeConverter.parseBase64Binary(PrefValue[1]));
		
			byte[] decodedByteArray = decoded.getBytes();
			//byte[] decodedByteArray = decoder.decode(PrefValue[1]);

			//Verify the decoded string

			if(PrefValue[2].trim().equalsIgnoreCase("tsimdev1"))
			{
				URL = "jdbc:oracle:thin:@tsimdev1.tsg.ge.com:1521:tsimdev1 ";
				USER = PrefValue[0].trim();
				PASS = new String(decodedByteArray).trim();
    	   
			}
			else
			{
				URL = "jdbc:oracle:thin:@tsimprd1.tsg.ge.com:1521:tsimprd1 ";
				USER = PrefValue[0].trim();
				PASS = new String(decodedByteArray).trim();
				
			}
		}
		else
		{
			Logger.write("ERROR - "+"Unable to get GET.CAM.RIN.CREDENTIALS Preference value");
		}		

		Connection conn = null;
		try 
		{
			conn = DriverManager.getConnection( URL, USER, PASS );
		}
		catch (SQLException e) 
		{
			com.ge.transportation.plm.cam.common.Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
			e.printStackTrace();
			Logger.write(e);
		}
		
		return conn;
	}
	
	public static void checkDriver()
	{
		try 
		{
			Class.forName("oracle.jdbc.driver.OracleDriver");
			
		}
		catch (ClassNotFoundException e) 
		{
			com.ge.transportation.plm.cam.common.Common.showError( -1, e.getMessage(), e.getClass().getName() );
			e.printStackTrace();
			Logger.write(e);
		}
	}
}
