
package com.get.ontrack.getrans;

import java.util.HashMap;
import java.util.Map;

import com.teamcenter.services.strong.query.SavedQueryService;
import com.teamcenter.services.strong.query._2006_03.SavedQuery.GetSavedQueriesResponse;
import com.teamcenter.services.strong.query._2007_09.SavedQuery.QueryResults;
import com.teamcenter.services.strong.query._2007_09.SavedQuery.SavedQueriesResponse;
import com.teamcenter.services.strong.query._2008_06.SavedQuery.QueryInput;
import com.teamcenter.soa.client.Connection;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.strong.ImanQuery;

/**
 * Class to perform different operations in the QueryService
 *
 */
public class GETQuery
{
    private Connection connection;

	private GETDataManagement dmInstance = null;

	private static Map<Connection, GETQuery> instanceMap;

	/**
     * Constructor for the class GETQuery. This is a private constructor that cannot be called from outside this class
     *  
	 * @param connection - Connection object for the session
	 */
	private GETQuery(Connection connection)
	{
		this.dmInstance = GETDataManagement.getDMService(connection);
		this.connection = connection;
	}

	/**
     * Static method to return instance of the class GETQuery
     * 
     * @return an instance of the class GETQuery
     */
	public static GETQuery getInstance(Connection connection)
	{
	    GETQuery returnInstance = null;

        if(instanceMap == null)
        {
            instanceMap = new HashMap<Connection, GETQuery>();
        }
        if (instanceMap.containsKey(connection))
        {
            returnInstance = instanceMap.get(connection);
        }
        else
        {
            returnInstance = new GETQuery(connection);
            instanceMap.put(connection, returnInstance);
        }

        return returnInstance;
	}
	
	/**
	 * Returns resultant objects of the query
	 * 
	 * @param strQueryName - name of the saved query to execute
	 * @param strQueryEntrys - Array of query entries
	 * @param strQueryValues - Array of values corresponding to query entries
	 * @return - array of resultant objects of query
	 */
	public ModelObject[] queryObject(String strQueryName, String[] strQueryEntrys, String[] strQueryValues) throws Exception
    {
    	ModelObject[] foundObjs = null;

    	ImanQuery ImanQueryObj = null;
        SavedQueryService SavedQueryServiceObj = SavedQueryService.getService(connection);
        GetSavedQueriesResponse GetSavedQueriesResponseObj = SavedQueryServiceObj.getSavedQueries();

        for (int inx = 0; inx < GetSavedQueriesResponseObj.queries.length; inx++)
        {
            if (GetSavedQueriesResponseObj.queries[inx].name.equals(strQueryName))
            {
                ImanQueryObj = GetSavedQueriesResponseObj.queries[inx].query;
                break;
            }
        }

        QueryInput savedQueryInput[] = new QueryInput[1];
        savedQueryInput[0] = new QueryInput();
        savedQueryInput[0].query = ImanQueryObj;
        savedQueryInput[0].maxNumToReturn = 10000;
        savedQueryInput[0].limitList = new ModelObject[0];
        savedQueryInput[0].entries = strQueryEntrys;
        savedQueryInput[0].values = strQueryValues;
        SavedQueriesResponse SavedQueriesResponseObj = SavedQueryServiceObj.executeSavedQueries(savedQueryInput);
        QueryResults QueryResultsObj = SavedQueriesResponseObj.arrayOfResults[0];
        foundObjs = dmInstance.loadObjects(QueryResultsObj.objectUIDS);

        return foundObjs;
    }

	/**
     * Returns resultant objects of the query
     * 
     * @param strQueryName - name of the saved query to execute
     * @param strQueryEntrys - Array of query entries
     * @param strQueryValues - Array of values corresponding to query entries
     * @return - array of resultant objects of query
     */
    public QueriedObjects getQueriedObjs(String strQueryName, String[] strQueryEntrys, String[] strQueryValues) throws Exception
    {
        QueriedObjects queriedObjs = null;
        ModelObject[] foundObjs = null;

        ImanQuery ImanQueryObj = null;
        SavedQueryService SavedQueryServiceObj = SavedQueryService.getService(connection);
        GetSavedQueriesResponse GetSavedQueriesResponseObj = SavedQueryServiceObj.getSavedQueries();

        for (int inx = 0; inx < GetSavedQueriesResponseObj.queries.length; inx++)
        {
            if (GetSavedQueriesResponseObj.queries[inx].name.equals(strQueryName))
            {
                ImanQueryObj = GetSavedQueriesResponseObj.queries[inx].query;
                break;
            }
        }

        QueryInput savedQueryInput[] = new QueryInput[1];
        savedQueryInput[0] = new QueryInput();
        savedQueryInput[0].query = ImanQueryObj;
        savedQueryInput[0].maxNumToReturn = 10000;
        savedQueryInput[0].limitList = new ModelObject[0];
        savedQueryInput[0].entries = strQueryEntrys;
        savedQueryInput[0].values = strQueryValues;
        SavedQueriesResponse SavedQueriesResponseObj = SavedQueryServiceObj.executeSavedQueries(savedQueryInput);
        QueryResults QueryResultsObj = SavedQueriesResponseObj.arrayOfResults[0];
        foundObjs = dmInstance.loadObjects(QueryResultsObj.objectUIDS);

        if ( QueryResultsObj.objectUIDS.length > 0 )
        {
            queriedObjs = new QueriedObjects();
            queriedObjs.loadedObjects = foundObjs;
            if ( foundObjs == null || foundObjs.length < QueryResultsObj.objectUIDS.length )
            {
                queriedObjs.hasRestrictedObjects = true;
            }
        }

        return queriedObjs;
    }

    public class QueriedObjects
    {
        public ModelObject[] loadedObjects;
        public boolean hasRestrictedObjects;
    }
}
