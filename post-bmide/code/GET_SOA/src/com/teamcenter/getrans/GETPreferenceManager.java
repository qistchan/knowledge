
package com.teamcenter.getrans;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.teamcenter.services.strong.administration.PreferenceManagementService;
import com.teamcenter.services.strong.administration._2012_09.PreferenceManagement.GetPreferencesResponse;
import com.teamcenter.soa.client.Connection;

/**
 * Class to perform different operations in the PreferenceManagementService
 *
 */
public class GETPreferenceManager
{
	private PreferenceManagementService prefService;

	private static Map<Connection, GETPreferenceManager> instanceMap;

	/**
	 * Constructor for the class GETPreferenceManager. This is a private constructor that cannot be called from outside this class
	 * @param connection - Connection object of the session
	 */
	private GETPreferenceManager(Connection connection)
	{
		prefService = PreferenceManagementService.getService(connection);
	}

	/**
	 * Static method to return instance of the class GETPreferenceManager
     * 
	 * @param connection - Connection object of the session
	 * @return an instance of the class GETPreferenceManager
	 */
    public static GETPreferenceManager getGETPreferenceManagementService(Connection connection)
    {
        GETPreferenceManager returnInstance = null;

        if(instanceMap == null)
        {
            instanceMap = new HashMap<Connection, GETPreferenceManager>();
        }
        if (instanceMap.containsKey(connection))
        {
            returnInstance = instanceMap.get(connection);
        }
        else
        {
            returnInstance = new GETPreferenceManager(connection);
            instanceMap.put(connection, returnInstance);
        }

        return returnInstance;
    }

	/**
	 * Returns List of values for the given preference
	 * 
	 * @param prefName - Name of preference
	 * @return List of values for the given preference
	 */
	public List<String> getPrefValues(String prefName)
	{
		List<String> prefValList = null;

		try
		{
			GetPreferencesResponse prefResp = prefService.getPreferences(new String[]{prefName}, false);
			if(prefResp == null || GETCommon.getErrorFromServiceData(prefResp.data) != null)
			{
				System.err.println(GETCommon.getErrorFromServiceData(prefResp.data));
				throw new Exception();
			}
			prefValList = Arrays.asList(prefResp.response[0].values.values);
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}

		return prefValList;
	}
}
