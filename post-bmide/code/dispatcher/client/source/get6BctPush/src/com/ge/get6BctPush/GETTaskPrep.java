package com.ge.get6BctPush;
/* STARTFILEDOC ***
//===========================================================================
//Filename:   GETTaskPrep.java//
//Purpose:   Code to create dispatcher request and finds the namded ref file of the dataset and
copies to staging location in module
//
//History:
//Who                   Date                 Description
//TCS Development Team     10 July, 2016         Initial creation
//
//============================================================================*/
//==== Package  ================================================================

//==== Imports  ================================================================
import java.io.File;

import com.teamcenter.ets.extract.DefaultTaskPrep;
import com.teamcenter.ets.request.TranslationRequest;
import com.teamcenter.ets.soa.SoaHelper;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.strong.Dataset;
import com.teamcenter.soa.client.model.strong.ImanFile;
import com.teamcenter.soa.client.model.strong.ItemRevision;
import com.teamcenter.translationservice.task.TranslationTask;


public class GETTaskPrep extends DefaultTaskPrep
{
	  
	/**
	* The ETS Extractor service invokes the prepareTask() class method to
	* prepare input data for translation requests. This method does the
	* following.
	* Collects all input files and creates TranslationTask object
	*
	* @return A complete or empty Translation Task object
	*/
   
   public TranslationTask prepareTask() throws Exception
   {
       TranslationTask zTransTask = new TranslationTask();   
       final String txtFileExt = "txt";
//       final String bctInspector = "BctInspector";
       final String dwgRevision = "GET6DrawingRevision";
    
       try
       {
           DataManagementService dms = DataManagementService.getService(SoaHelper.getSoaConnection());
           m_zTaskLogger.info((new StringBuilder()).append( "Inside GETTaskPrep for DRS BCT Push ").toString());
      
           /**
           * Getting primary and secondary object from dispatcher request
           */
           ModelObject primary_objs[] = request.getPropertyObject(TranslationRequest.PRIMARY_OBJS).getModelObjectArrayValue();
           ModelObject secondary_objs[] = request.getPropertyObject(TranslationRequest.SECONDARY_OBJS).getModelObjectArrayValue();
           ItemRevision TcitemRev = (ItemRevision) secondary_objs[0];
           m_zTaskLogger.info((new StringBuilder()).append(primary_objs.length).toString());
           for (int index = 0; index < primary_objs.length; index++)
           {
               /**
               * get primary object
               */            	
           	
               String itemType = TcitemRev.get_object_type();
               m_zTaskLogger.info("itemType name " + itemType );
				
			   if(!(itemType.equalsIgnoreCase( dwgRevision )))
               {
					m_zTaskLogger.info("Item Type not recommended for Dispatcher service get6DrsPush");
					break;
               }
				
               Dataset tcdataset = (Dataset) primary_objs[index];          
               String DatasetName = tcdataset.get_object_name();
			   DatasetName = DatasetName.toUpperCase();
               m_zTaskLogger.info("Dataset name " +DatasetName);
               m_zTaskLogger.info("Dataset Type " +tcdataset.getTypeObject().getName());
             
               dms.getProperties(new ModelObject[]{tcdataset}, new String[]{"ref_list"});
               ModelObject[] contexts = tcdataset.get_ref_list();
               
               /**
               * get named reference list array
               */
               m_zTaskLogger.info("Named Reference length : " + contexts.length);
               if( contexts.length == 0 )
               {
	               	m_zTaskLogger.info("Translation Failed!!! Named Reference is Empty");
	               	break;
               }
               for( int j = 0; j < contexts.length; j++ )
               {
                   /**
                   * get file extension and compare.
                   */
                   
               		if ( contexts[j] instanceof ImanFile )
                    {
                       ImanFile zIFile = (ImanFile) contexts[j];
                       dms.getProperties( new ModelObject[]{zIFile}, new String[]{"file_ext"} );
                       String scFileExt = zIFile.get_file_ext();
                       m_zTaskLogger.info("File extension is :- "+ scFileExt);
                       if ( scFileExt.equalsIgnoreCase(txtFileExt) )
                       {
                       		dms.getProperties( new ModelObject[]{zIFile}, new String[]{"original_file_name"} );
                       		String originalfileName = zIFile.get_original_file_name();
                       		m_zTaskLogger.info("fileName is :- "+ originalfileName);
                       		/**
                       		 * Getting item id and revision id
                       		 */
	                           dms.getProperties( new ModelObject[]{TcitemRev}, new String[]{"item_id", "item_revision_id"} );
	                           String scItemId = TcitemRev.get_item_id();
	                           String scItemRevId = TcitemRev.get_item_revision_id();
	                           m_zTaskLogger.info( "ItemID  : " + scItemId );
	                           m_zTaskLogger.info( "ItemRev  : " + scItemRevId );
	                           
                        	   String dsNewName = scItemId +"_"+ scItemRevId +"_"+ scItemId +"-ALL";
                       	
                        	   m_zTaskLogger.info("dsNewName is :"+ dsNewName );    
                        	   String exportFilename = dsNewName + "." + scFileExt;
	                           m_zTaskLogger.info("ExportFile name :"+exportFilename);
                           
	                           /**
	                            * Adding option for Item
	                            */
                           
	                           zTransTask = addOptions( zTransTask, "ItemID", scItemId );
	                           zTransTask = addOptions( zTransTask, "Revision", scItemRevId );
	                           /**
	                            * Exporting file to staging location
	                            */
	                           File zFile = TranslationRequest.getFileToStaging( zIFile, stagingLoc );
	                           m_zTaskLogger.info("after staging loc :"+zFile.toString());
	                           try
	                           {
	                        	   zFile.renameTo( new File (stagingLoc + File.separatorChar + exportFilename) );
	                        	   m_zTaskLogger.info("after rename toc :"+zFile.toString());
	                           }
	                           catch( Exception zEx )
	                           {
	                        	   m_zTaskLogger.debug( "Rename to " + stagingLoc + File.separatorChar + exportFilename + " failed." );
	                           }
	                           /**
	                            * Preparing task
	                            */
	                           zTransTask = prepTransTask(zTransTask, tcdataset, TcitemRev, exportFilename, true, false,".txt", 0, null);
	                           
	                           m_zTaskLogger.info("after prepTransTask :");

                       		}
                		}
               		}
           		}
	       }
	       catch (ServiceException ex)
	       {
	           m_zTaskLogger.error("Error in prepareTask :ServiceException");
	           m_zTaskLogger.error(ex.getMessage());
	           return null;
	       }
	       catch (Exception ex)
	       {
	           m_zTaskLogger.error("Error in prepareTask :Exception");
	           m_zTaskLogger.error(ex.getMessage());
	           return null;
	       }
	       return addRefIdToTask(zTransTask, 0);
     }
}
