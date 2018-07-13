
//==================================================
// 
//  Copyright 2015 GE Transportation. All Rights Reserved.
//
//==================================================

package com.teamcenter.getrans;

import java.lang.reflect.Array;
import java.sql.DriverManager;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.teamcenter.schemas.soa._2011_06.metamodel.PropertyDescriptor;
import com.teamcenter.services.strong.core.SessionService;
import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.PartialErrors;
import com.teamcenter.soa.client.model.ServiceData;
import com.teamcenter.soa.client.model.strong.ListOfValuesTagExtent;
import com.teamcenter.soa.client.model.strong.UnitOfMeasure;
import com.teamcenter.soa.common.ObjectPropertyPolicy;

/**
 * This is a common class for utility methods.
 *
 * @author TCSL
 */
public class GETCommon
{
	private Connection connection;

	private static Map<Connection, GETCommon> instanceMap;
	

	/**
	 * Constructor for the class GETCommon. This is a private constructor that cannot be called from outside this class
	 * 
	 * @param connection - Connection object for the session
	 */
	private GETCommon(Connection connection)
	{
	    this.connection = connection;
	}

	/**
	 * Static Singleton method to return the instance of the class GETCommon.
     *
     * @param connection - Connection object for the session
     * @return an instance of the class GETCommon
	 */
	public static GETCommon getInstance(Connection connection)
	{
	    GETCommon returnInstance = null;

        if(instanceMap == null)
        {
            instanceMap = new HashMap<Connection, GETCommon>();
        }
        if (instanceMap.containsKey(connection))
        {
            returnInstance = instanceMap.get(connection);
        }
        else
        {
            returnInstance = new GETCommon(connection);
            instanceMap.put(connection, returnInstance);
        }

        return returnInstance;
	}

	/**
	 * Method to retrieve FMS_bootstrapURL from preference
	 * 
	 * @return List of values of the FMS_bootstrapURL preference
	 */
	public List<String> getBootStrapURLs()
	{
		List<String> prefValList = null;
		try
		{
			GETPreferenceManager prefService = GETPreferenceManager.getGETPreferenceManagementService(connection);
			prefValList = prefService.getPrefValues(GETConstants.Preferences.strFMSBootStrapURL);
			if(prefValList == null || prefValList.isEmpty())
			{
				throw new Exception();
			}
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}

		return prefValList;
	}

	/**
	 * Method to get error message from service data
	 *
	 * @param serviceData - ServiceData instance of any SOA Response Object 
	 * @return errorMessage - A String containing the consolidated error messages from the Service Data or null if there are no errors
	 */
	public static String getErrorFromServiceData(ServiceData serviceData)
	{
		String errorMessage = null;
		if (serviceData != null && serviceData.sizeOfPartialErrors() > 0)
		{
			StringBuffer messageBuffer = new StringBuffer();
			for (int index = 0; index < serviceData.sizeOfPartialErrors(); index++)
			{
				for (String message : serviceData.getPartialError(index).getMessages())
				{
					messageBuffer.append(message).append("\n");
				}
			}
			errorMessage = messageBuffer.toString();
		}

		return errorMessage;
	}

	   /**
     * Method to get error message from service data
     *
     * @param serviceData - ServiceData instance of any SOA Response Object 
     * @return errorMessage - A String containing the consolidated error messages from the Service Data or null if there are no errors
     */
    public static String getErrorFromPartialError(PartialErrors partialError)
    {
        String errorMessage = null;
        if (partialError != null && partialError.sizeOfPartialErrors() > 0)
        {
            StringBuffer messageBuffer = new StringBuffer();
            for (int index = 0; index < partialError.sizeOfPartialErrors(); index++)
            {
                for (String message : partialError.getPartialError(index).getMessages())
                {
                    messageBuffer.append(message).append("\n");
                }
            }
            errorMessage = messageBuffer.toString();
        }

        return errorMessage;
    }

	/**
	 * Sets object policy for the current session
	 * 
	 * @param typePropsMap - Map of object type and array of properties that are to be loaded by default
	 */
    public void setObjectPolicy(Map<String, String[]> typePropsMap)
    {
	    SessionService session = SessionService.getService(connection);
	    ObjectPropertyPolicy policy = new ObjectPropertyPolicy();

	    for (Map.Entry<String, String[]> entry : typePropsMap.entrySet())
    	{
	    	policy.addType(entry.getKey(), entry.getValue());
    	}

	    session.setObjectPropertyPolicy(policy);
    }

    /**
     * This method retrieves the Unit Of Measure values defined in Teamcenter as a List
     * @return uomList - A List of String containing the UnitOfMeasure symbols defined in the system
     * @throws Exception - If any unexpected error occurs in Teamcenter
     */
    public List<String> getUOMValues() throws Exception
    {
        List<String> uomList = null;
        SessionService session = SessionService.getService(connection);
        PropertyDescriptor uomPropDescriptor = null;
        List<PropertyDescriptor> propDescriptors = session.getTypeDescriptions(new String[]{GETConstants.BusinessObjects.item}).getTypes().get(0).getPropertyDescriptors();
        for (PropertyDescriptor propDesc : propDescriptors)
        {
            if (propDesc.getName().compareTo(GETConstants.BusinessObjects.Properties.uomTag) == 0)
            {
                uomPropDescriptor = propDesc;
                break;
            }
        }
        if (uomPropDescriptor != null)
        {
            GETDataManagement dmService = GETDataManagement.getDMService(connection);
            String lovUID = uomPropDescriptor.getLovs().get(0).getLovUid();
            ListOfValuesTagExtent lovObject = (ListOfValuesTagExtent) dmService.loadObjects(new String[]{lovUID})[0];
            ModelObject[] values = lovObject.get_lov_values();
            if (values != null)
            {
                uomList = new ArrayList<String>();
                for (ModelObject value : values)
                {
                    UnitOfMeasure uom = (UnitOfMeasure) value;
                    uomList.add(uom.get_symbol());
                }
            }
        }

        return uomList;
    }

    /**
     * Method to merge two arrays of same type
     * 
     * @param array1
     * @param array2
     * @return - Merged resultant array
     */
    @SuppressWarnings("unchecked")
    public static <T> T[] concatenateArrays(T[] array1, T[] array2)
    {
        T[] mergedArray = null;
        int array1Len = 0;
        int array2Len = 0;
        //mergedArray = (T[]) Array.newInstance(array1.getClass().getComponentType(), array1.length + array2.length);
        if(array1 != null)
        {
            array1Len = array1.length;
            if(array2 != null)
            {
                array2Len = array2.length;
            }
            mergedArray = (T[]) Array.newInstance(array1.getClass().getComponentType(), array1Len + array2Len);
            System.arraycopy(array1, 0, mergedArray, 0, array1Len);
        }
        if(array2 != null)
        {
            array2Len = array2.length;
            if(mergedArray == null)
            {
                mergedArray = (T[]) Array.newInstance(array2.getClass().getComponentType(), array2Len);
            }
            System.arraycopy(array2, 0, mergedArray, array1Len, array2Len);
        }

        return mergedArray;
    }
    
    /**
     * Method to establish connection to the given database
     * 
     * @param driverClassName - Name of Driver
     * @param dbType - Database Type
     * @param dbServer - Database Server URL
     * @param portNum - Port number
     * @param dbName - Name of database
     * @param dbUserName - User name
     * @param dbPasswd - Password
     * @param dbSid - Sid of oracle db
     * @return Connection object of established connection
     * @throws Exception
     */
    public static java.sql.Connection establishDBConnection(String driverClassName, String dbType, String dbServer, int portNum, String dbName, String dbUserName, String dbPasswd, String dbSid) throws Exception
    {
        java.sql.Connection connection = null;
        try
        {
            String dbServerURL;
            Class.forName(driverClassName);
            if(driverClassName.contains("Oracle"))
            {
              //jdbc:oracle:thin:@<host>:<port>:<SID>
                dbServerURL = dbType + dbServer + GETConstants.Symbols.strColon + portNum + GETConstants.Symbols.strColon + dbSid;
            }
            else
            {
                dbServerURL = dbType + GETConstants.Symbols.strColon + GETConstants.Symbols.strDoubleForwardSlash + dbServer + GETConstants.Symbols.strColon
                        + portNum + GETConstants.Symbols.strForwardSlash + dbName;
            }
            connection = DriverManager.getConnection(dbServerURL, dbUserName, dbPasswd);
            if(connection == null)
            {
                throw new Exception("Unable to establish connection");
            }
        }
        catch(Exception ex)
        {
            throw ex;
        }
        return connection;
    }
}
