/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GETTaskPrep.java//
//    Purpose:   Code to create dispatcher request and finds the namded ref file of the dataset and
     copies to staging location in module
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     10 July, 2016         Initial creation
//
//   ============================================================================*/
//==== Package  ================================================================
package com.ge.get6DrsPush;


//==== Imports  ================================================================
import java.io.File;
import java.util.ArrayList;
import java.util.List;

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

//==== Class ====================================================================
/**
 * This class is sub class of DefaultTaskPrep to extract dataset to
 * staging directory location and create translation task object.
 */
    
public class GETTaskPrep extends DefaultTaskPrep
{
    /**STARTFUNCDOC *
    ===========================================================================
     * Method to get root Item ID from Item ID taken as input
     * 
     * @param inputItemID - InputItemID in string 
     * @return File - Returns Folder/File to be used to keep Fetched dataset  /**
             * Method to get root number of given item ID.
             *
             * @param partsListID - Item Id whose root number is to be retrieved
             * @return the drg id from part list
             
     ===========================================================================    
    ENDFUNCDOC   **/
    
    public static String getFilename (String sheetName, String scFileExt)
    {
        sheetName = sheetName.toLowerCase();
        String exportFilename = sheetName + "." + scFileExt;
        return exportFilename;
    }
    
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
        final String pdfFileExt = "pdf";
        final String drawingSheet = "DrawingSheet";
        final String raster = "ras";
        final String elecPartRevision = "GET6ElectPartRevision";
        final String mechPartRevision = "GET6MechPartRevision";
        final String psRevision = "GET6SpecsRevision";
        final String docRevision = "GET6DocumentRevision";
        final String dwgRevision = "GET6DrawingRevision";
     
        try
        {
            DataManagementService dms = DataManagementService.getService(SoaHelper.getSoaConnection());
            m_zTaskLogger.info((new StringBuilder()).append( "Inside GETTaskPrep for DRS PDF Push ").toString());
            List<String> fileExtList = new ArrayList<String>();
            fileExtList.add( pdfFileExt );
            fileExtList.add( raster );
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
                
                if(!((itemType.equalsIgnoreCase( dwgRevision )) || (itemType.equalsIgnoreCase( docRevision )) || (itemType.equalsIgnoreCase( psRevision )) || (itemType.equalsIgnoreCase( elecPartRevision )) || (itemType.equalsIgnoreCase( mechPartRevision ))))
                {
                    m_zTaskLogger.info("Item Type not recommended for Dispatcher service get6DrsPush");
                    break;
                }
                
                Dataset tcdataset = (Dataset) primary_objs[index];          
                String DatasetName = tcdataset.get_object_name();
                DatasetName = DatasetName.toUpperCase();
                m_zTaskLogger.info("Dataset name " +DatasetName);
                m_zTaskLogger.info("Dataset Type " +tcdataset.getTypeObject().getName());                         
                             
                              
                /**
                * Get Item rev
                */               
                //push only rasters file to DRS in case of GETDrawing revision(Model centric drawings)
                if( itemType.equalsIgnoreCase( dwgRevision ) && (!tcdataset.getTypeObject().getName().equalsIgnoreCase( drawingSheet )))
                {
                    continue;
                }
                //push only PDF files to DRS in case of GETDocument revision
                else if( itemType.equalsIgnoreCase( docRevision ) && (!tcdataset.getTypeObject().getName().equalsIgnoreCase( pdfFileExt )))
                {
                    continue;
                }
                //push only PDFs file to DRS in case of GETSpecification revision
                else if( itemType.equalsIgnoreCase( psRevision ) && (!tcdataset.getTypeObject().getName().equalsIgnoreCase( pdfFileExt )))
                {
                    continue;
                }
                //push only 3DPDF file to DRS in case of GETElectrical revision and GETMech Item revisions(Model Based drawings)
                else if( itemType.equalsIgnoreCase( elecPartRevision ) && ( !tcdataset.getTypeObject().getName().equalsIgnoreCase( pdfFileExt ) ))
                {
                    continue;
                }
                //push only 3DPDF file to DRS in case of GETMechanical revision and GETMech Item revisions(Model Based drawings)
                else if( itemType.equalsIgnoreCase( mechPartRevision ) && ( !tcdataset.getTypeObject().getName().equalsIgnoreCase( pdfFileExt ) ))
                {
                    continue;
                }
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
                        scFileExt = scFileExt.toLowerCase();
                        if ( fileExtList.contains( scFileExt ) )
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
                            
                            String exportFilename="";
                            
                            if( itemType.equalsIgnoreCase( dwgRevision ) )
                            {                           
                                String sheetName = DatasetName.substring( DatasetName.lastIndexOf("S") );
                                exportFilename = getFilename ( sheetName, scFileExt );
                            }
                            else if ( itemType.equalsIgnoreCase( psRevision ) || (itemType.equalsIgnoreCase( docRevision ) ))
                            {
                                String namedRefName = "PS";
                                exportFilename = getFilename ( namedRefName, scFileExt ); 
                            }
                            else if ( itemType.equalsIgnoreCase( elecPartRevision ) || ( itemType.equalsIgnoreCase( mechPartRevision ) ))
                            {
                                String sheetName = scItemId;
                                String substringToBeRemoved = com.ge.get6DrgIDFromPartlist.Get6DrgIDFromPartlist.getDrgIDFromPartList( sheetName );
                                m_zTaskLogger.info("root from getDrgIDFromPartList :"+ substringToBeRemoved );

                                if (substringToBeRemoved.substring(0, 1).equalsIgnoreCase("T") || (substringToBeRemoved.substring(0, 1).equalsIgnoreCase("D") || ( substringToBeRemoved.substring(0, 1).equalsIgnoreCase("F") )) )
                                {
                                    System.out.println("\n SheetName is "+ substringToBeRemoved);
                                    exportFilename = getFilename ( substringToBeRemoved, scFileExt );
                                }
                                else
                                {
                                    sheetName = sheetName.replace( substringToBeRemoved, "" );
                                    m_zTaskLogger.info("sheetName getDrgIDFromPartList :"+ sheetName );
                                    exportFilename = getFilename ( sheetName, scFileExt ); 
                                }
                            }
                            m_zTaskLogger.info("ExportFile name :"+exportFilename);
                            
                             /**
                             * Adding option for Item and Revision Id
                             */
                            
                            zTransTask = addOptions( zTransTask, "ItemID", scItemId );
                            zTransTask = addOptions( zTransTask, "Revision", scItemRevId );
                            /**
                            * Exporting file to staging location
                            */
                            File zFile = TranslationRequest.getFileToStaging( zIFile, stagingLoc );
                            try
                            {
                                 zFile.renameTo( new File (stagingLoc + File.separatorChar + exportFilename) );
                            }
                            catch( Exception zEx )
                            {
                                m_zTaskLogger.debug( "Rename to " + stagingLoc + File.separatorChar + exportFilename + " failed." );
                            }
                            /**
                            * Preparing task
                            */
                            zTransTask = prepTransTask(zTransTask, tcdataset, TcitemRev, exportFilename, true, false,".pdf", 0, null);
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
