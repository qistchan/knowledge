
//==== Package  =================================================================
package com.ge.get6BctPush;

//==== Imports  =================================================================
import com.teamcenter.ets.load.DatabaseOperation;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.strong.DispatcherRequest;

//==== Class ====================================================================
/**
 * /**
 * This custom class is the DBOperation class for BCTPush translator.
 */
 
public class GETDBOperation extends DatabaseOperation 
{
    /**
    * Custom load method overriding the super class method
    */
   @Override
   public void load() throws Exception 
   {
       m_zTaskLogger.debug("Entering GETDBOperation.load() method ...");
       m_zTaskLogger.debug("Exiting GETDBOperation.load() method ...");
   }

   /**
    * Custom query method overriding the super class method
    */
   @Override
   public void query() throws Exception
   {
       m_zTaskLogger.debug("Entering GETDBOperation.query() method ...");

       this.primaryObj = null;
       this.secondaryObj = null;

       ModelObject[] primObjects = ((DispatcherRequest)request).get_primaryObjects();
       if (primObjects != null && primObjects.length > 0)
       {
           this.primaryObj = primObjects[0];
       }
       ModelObject[] secObjects = ((DispatcherRequest)request).get_secondaryObjects();
       if (secObjects != null && secObjects.length > 0)
       {
           this.secondaryObj = secObjects[0];
       }

       if (this.primaryObj == null)
       {
           throw new Exception("Primary Object is not set.");
       }
       if (this.secondaryObj == null)
       {
           throw new Exception("Secondary Object is not set.");
       }

       m_zTaskLogger.debug("Exiting GETDBOperation.query() method ...");
   }
}