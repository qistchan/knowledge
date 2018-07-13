
package com.teamcenter.getrans;

import java.io.File;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.FileManagementUtility;
import com.teamcenter.soa.client.GetFileResponse;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.strong.ImanFile;

/**
 * Class to perform different operations in the FileManagementService
 *
 *@author TCSL
 */
public class GETFileManagement
{
    private Connection connection;

	private static Map<Connection, GETFileManagement> instanceMap;
	
	/**
	 * Constructor for the class GETFileManagement. This is a private constructor that cannot be called from outside this class
	 * 
	 * @param connection - Connection object of the session
	 */
	private GETFileManagement(Connection connection)
	{
	    this.connection = connection;
	}

	/**
	 * Static Singleton method to return the instance of the class GETFileManagement.
     *
     * @param connection - Connection object of the session
     * @return an instance of the class GETFileManagement
	 */
	public static GETFileManagement getService(Connection connection)
	{
	    GETFileManagement returnInstance = null;

        if(instanceMap == null)
        {
            instanceMap = new HashMap<Connection, GETFileManagement>();
        }
        if (instanceMap.containsKey(connection))
        {
            returnInstance = instanceMap.get(connection);
        }
        else
        {
            returnInstance = new GETFileManagement(connection);
            instanceMap.put(connection, returnInstance);
        }

        return returnInstance;
	}
	
	/**
	 * Gets file from the given imanfile
	 * 
	 * @param imf - ImanFile object
	 * @return File object of the ImanFile
	 */
	public File getFileFromIMF(ImanFile imf)
	{
		File fileObj = null;
		try
		{
			if(imf != null) 
			{
				List<String> bootStrapURLList = GETCommon.getInstance(connection).getBootStrapURLs();
				String bootStrapURL = null;
				if(bootStrapURLList == null || bootStrapURLList.isEmpty())
				{
					throw new Exception("No bootstrap URL found");
				}
				bootStrapURL = bootStrapURLList.get(0);
				FileManagementUtility FileManagementUtilityObj = new FileManagementUtility(connection,  null,  new String[] { bootStrapURL }, new String[] { bootStrapURL }, System.getProperty(GETConstants.Symbols.strJavaTempDir));
				GetFileResponse getFileResponseObj = FileManagementUtilityObj.getFiles(new ModelObject[] { imf });
				if(getFileResponseObj.sizeOfFiles() > 0)
				{
					fileObj = getFileResponseObj.getFile(0);
				}
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}

		return fileObj;
	}
}
