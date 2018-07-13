/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GETNXPDFTaskPrep.java
//   Purpose : Task Prep Class for invoking NX Clone and sending the request 
//                 for 3D PDF generation to Anark Core Server 
//
//    History:
//      Who                           Date                 Description
//  Capgemini Development Team     15 May, 2017         Initial creation
//
//   ============================================================================
*/

package com.ge.get6UGEXPDF;

import com.ge.GETCommon;
import com.teamcenter.ets.request.TranslationRequest;
import com.teamcenter.ets.soa.SoaHelper;
import com.teamcenter.ets.translator.ugs.ugtopv.UgCommonUtil;
import com.teamcenter.schemas.soa._2006_03.exceptions.ServiceException;
import com.teamcenter.services.strong.structuremanagement.StructureService;
import com.teamcenter.services.strong.core._2006_03.DataManagement.Relationship;
import com.teamcenter.services.strong.importexport.FileImportExportService;
import com.teamcenter.services.strong.importexport._2007_06.FileImportExport.ExportToApplicationResponse;
import com.teamcenter.services.strong.importexport._2008_06.FileImportExport.ExportToApplicationInputData1;
import com.teamcenter.soa.client.FileManagementUtility;
import com.teamcenter.services.strong.core.DataManagementService;
import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.ServiceData;
import com.teamcenter.soa.client.model.strong.BOMLine;
import com.teamcenter.soa.client.model.strong.BOMWindow;
import com.teamcenter.soa.client.model.strong.Dataset;
import com.teamcenter.soa.client.model.strong.EPMConditionTask;
import com.teamcenter.soa.client.model.strong.ImanFile;
import com.teamcenter.soa.client.model.strong.Item;
import com.teamcenter.soa.client.model.strong.ItemRevision;
import com.teamcenter.soa.client.model.strong.POM_application_object;
import com.teamcenter.soa.client.model.strong.PSBOMViewRevision;
import com.teamcenter.services.strong.cad.StructureManagementService;
import com.teamcenter.services.strong.cad._2007_01.StructureManagement;
import com.teamcenter.soa.client.model.strong.RevisionRule;
import com.teamcenter.soa.exceptions.NotLoadedException;
import com.teamcenter.translationservice.task.TranslationDBMapInfo;
import com.teamcenter.translationservice.task.TranslationData;
import com.teamcenter.translationservice.task.TranslationDataRef;
import com.teamcenter.translationservice.task.TranslationSrcInfo;
import com.teamcenter.translationservice.task.TranslationTask;
import com.teamcenter.translationservice.task.TranslationTaskUtil;
import com.teamcenter.translationservice.task.types.TranslationSrcInfoItemFiletypeType;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.UUID;

public class GETUGEXPDFTaskPrep
extends com.teamcenter.ets.extract.TaskPrep
{
    /**
    * The ETS Extractor service invokes the prepareTask() class method to
    * prepare input data for translation requests. This method does the
    * following :
    * 1. Prepares all input files containing values to be used as input arguments by UG CLone and Anark Core Server
    * 2. Create TranslationTask object
    *
    * @return A complete or empty Translation Task object
    */
    private static final String partslistFileName = "PartsList.xlsm";
    private static final String anarkfileSuffix = "_Anark.txt";
    private static final String anarkwatermarkFileSuffix = "_AnarkWM.txt";
    private static final String translatorlogFileName = "GE_get6UGEXPDF.log";
    private static final String UTF8_ENCODING = "UTF-8";
    private static final String PDF_FILE_EXT = ".pdf";
    private static final String LOG_FILE_EXT = ".log";
    private static final String TEXT_FILE_EXT = ".txt";
    private static final String UGPART_FILE_EXT = ".prt";
    private static final String exportexcelTemplate = "GET_PartList_excel_template";
    private static final String anarkDatasetSuffix = "_3D_PDF";
    private static final String dispatcherresultDir = "result";
    private static final String pdffileMapperKey = "pdffile";
    private static final String pdffiledescMapperKey = "reportDesc";
    private static final String anarklogfileMapperKey = "anarklogfile";
    private static final String anarklogDescMapperKey = "anarklogDesc";
    private static final String logfileMapperKey = "logfile";
    private static final String logDescMapperKey = "logDesc";
    
    private FileImportExportService fileImportExportService = FileImportExportService.getService(SoaHelper.getSoaConnection());
    private FileManagementUtility fileManagementUtility = new FileManagementUtility(SoaHelper.getSoaConnection());
    private DataManagementService dmServ = DataManagementService.getService(SoaHelper.getSoaConnection());
    private StructureService structureService = StructureService.getService(SoaHelper.getSoaConnection());

    public TranslationTask prepareTask()
            throws Exception
    {
        /**
         * Getting primary and secondary object from dispatcher request
         */
        ModelObject[] zPrimaryObjs = this.request.getPropertyObject(GETCommon.primaryObjectsAttr).getModelObjectArrayValue();
        ModelObject[] zSecondaryObjs = this.request.getPropertyObject(GETCommon.secondaryObjectsAttr).getModelObjectArrayValue();

        String scTaskId = this.request.getPropertyObject(GETCommon.taskIDAttr).getStringValue();
        UUID scUUID = UUID.randomUUID();
        UUID scwatermarkUUID = UUID.randomUUID();
        
        /**
         * Generate the input filenames, which will contain argument values, for UGClone and ACS
         */
        String scDBStringFileName = scTaskId + TEXT_FILE_EXT;
        String scDBAnarkStringFileName = scDBStringFileName + anarkfileSuffix;
        String scDBAnarkStringWMFileName = scDBStringFileName + anarkwatermarkFileSuffix;

        TranslationTask zTask = new TranslationTask();
        TranslationData zDBStringTransData = new TranslationData();
        TranslationSrcInfo zDBStringTransSourceInfo = new TranslationSrcInfo();
        TranslationDBMapInfo zTransDBMapInfo = new TranslationDBMapInfo();
        /**
         * Prepare the task object
         */
        zDBStringTransSourceInfo.setFiletype(TranslationSrcInfoItemFiletypeType.SOURCE);
        zDBStringTransSourceInfo.setFilename(scDBStringFileName);
        zDBStringTransData.setTranslationSrcInfo(zDBStringTransSourceInfo);
        zDBStringTransData.setId("0");
        zTask.addTranslationData(0, zDBStringTransData);
        
        TranslationDataRef zDBStringTransDataRef = new TranslationDataRef();
        zDBStringTransDataRef.setId("0");
        zTask.setTranslationDataRef(zDBStringTransDataRef);
        
        /**
         * Generate the absolute filenames, which will contain argument values, for UGClone and ACS
         */
        String scDBStringFile = this.stagingLoc + File.separatorChar + scDBStringFileName;
        String scDBAnarkStringFile = this.stagingLoc + File.separatorChar + scDBAnarkStringFileName;        
        String scDBAnarkStringWMFile = this.stagingLoc + File.separatorChar + scDBAnarkStringWMFileName;
        
        UgCommonUtil zUgComUtil = new UgCommonUtil(this.m_zTaskLogger);

        boolean singlePart = false;
        FileOutputStream zDBStringStream = null;
        PrintStream zDBStringPrintStream = null;
        FileOutputStream zDBAnarkStringStream = null;
        PrintStream zDBAnarkStringPrintStream = null;
        FileOutputStream zDBAnarkWMStringStream = null;
        PrintStream zDBAnarkWMStringPrintStream = null;
        try
        {
            zDBStringStream = new FileOutputStream(scDBStringFile);
            zDBStringPrintStream = new PrintStream(zDBStringStream, false, UTF8_ENCODING);
            zDBAnarkStringStream = new FileOutputStream(scDBAnarkStringFile);
            zDBAnarkStringPrintStream = new PrintStream(zDBAnarkStringStream, false, UTF8_ENCODING);
            zDBAnarkWMStringStream = new FileOutputStream(scDBAnarkStringWMFile);
            zDBAnarkWMStringPrintStream = new PrintStream(zDBAnarkWMStringStream, false, UTF8_ENCODING);
            
            for (int i = 0; i < zPrimaryObjs.length; i++)
            {
                ModelObject primaryObject = zPrimaryObjs[i];
                ModelObject secondaryObject = null;
                if (zSecondaryObjs.length >= i) {
                    secondaryObject = zSecondaryObjs[i];
                }
                Dataset dataset = null;
                ItemRevision itemRev = null;
                if ((primaryObject instanceof Dataset)) {
                    dataset = (Dataset)primaryObject;
                } else if ((primaryObject instanceof ItemRevision)) {
                    itemRev = (ItemRevision)primaryObject;
                }
                if (secondaryObject != null) {
                    if ((secondaryObject instanceof ItemRevision)) {
                        itemRev = (ItemRevision)secondaryObject;
                    }
                }
                if (itemRev == null)
                {
                    this.m_zTaskLogger.error("ItemRevision in NULL");
                }
                else
                {
                    itemRev = (ItemRevision)SoaHelper.getProperties(itemRev, new String[] { GETCommon.itemsTagAttr, GETCommon.itemrevisionIDAttr });                    
                    Item zItem = itemRev.get_items_tag();
                        
                    /**
                     * Check for existing 3D PDF files and delete
                     */
                    deleteExistingPDF(itemRev);

                    String primaryObjectUid = primaryObject.getUid();
                    this.m_zTaskLogger.debug("  primaryObjectUid " + primaryObjectUid);
                    TranslationTaskUtil.setUserAttrValue(zTransDBMapInfo, GETCommon.priobjuidAttr, primaryObjectUid);
                    if (secondaryObject != null)
                    {
                        String secondaryObjectUid = secondaryObject.getUid();
                        this.m_zTaskLogger.debug("  secondaryObjectUid " + secondaryObjectUid);
                        TranslationTaskUtil.setUserAttrValue(zTransDBMapInfo, GETCommon.secobjuidAttr, secondaryObjectUid);
                    }
                    zItem = (Item)SoaHelper.getProperties(zItem, GETCommon.fnd0PartIdentifierAttr);
                    String scMfkId = zItem.get_fnd0PartIdentifier();
                    String revId = itemRev.get_item_revision_id();
                    /**
                     * Set the MapperResults for the TranslationTask
                     * 1. 3D PDF file
                     * 2. Anark Log file
                     * 3. Dispatcher Log file
                     */
                    String pdfFileName = scMfkId + "_" + revId + PDF_FILE_EXT;
                    String reportDesc = "Generated from Anark 3D PDF";
                    String AnarklogFilename = this.stagingLoc + File.separatorChar + dispatcherresultDir + File.separatorChar + scTaskId + LOG_FILE_EXT;
                    String anarkLogDesc = "Anark Execution Log file";
                    String logFilename = this.stagingLoc + File.separatorChar + dispatcherresultDir + File.separatorChar + translatorlogFileName;
                    String logDesc = "Dispatcher services run log file";
                    TranslationTaskUtil.setUserAttrValue(zDBStringTransSourceInfo, GETCommon.itemidAttr, scMfkId);

                    TranslationTaskUtil.setUserAttrValue(zDBStringTransSourceInfo, GETCommon.revisionidAttr, revId);
                    TranslationTaskUtil.setMapperResults(zTransDBMapInfo, pdffileMapperKey,
                            pdfFileName);
                    TranslationTaskUtil.setMapperResults(zTransDBMapInfo, pdffiledescMapperKey,
                            reportDesc);
                    TranslationTaskUtil.setMapperResults(zTransDBMapInfo, anarklogfileMapperKey,
                            AnarklogFilename);
                    TranslationTaskUtil.setMapperResults(zTransDBMapInfo, anarklogDescMapperKey,
                            anarkLogDesc);
                    TranslationTaskUtil.setMapperResults(zTransDBMapInfo, logfileMapperKey,
                            logFilename);
                    TranslationTaskUtil.setMapperResults(zTransDBMapInfo, logDescMapperKey,
                            logDesc);

                   
                    String anarkString = null;
                    String bctFilename = null;
                    if (dataset != null)
                    {
                        dataset = (Dataset)SoaHelper.getProperties(dataset, GETCommon.objectNameAttr);
                        String datasetName = dataset.get_object_name();
                        String datasetType = dataset.get_object_type();
                        String relationType = zUgComUtil.getRelationType(itemRev, dataset);

                        boolean fMasterPart = !datasetType.equalsIgnoreCase(GETCommon.ugpartDatasetType);

                        /**
                         * Check if the input is an assembly or single part
                         */
                        if (!(isAssembly(dataset, itemRev)))
                        {
                            singlePart = true;
                        }
                        anarkString = getAnarkCLIName(scMfkId, revId, fMasterPart, datasetName, relationType, this.stagingLoc);                    
                    }                    
                    if (singlePart) {
                        zDBStringPrintStream.println("-part=" + scMfkId + " -rev=" + revId);
                    } else {
                        zDBStringPrintStream.println("-assembly=" + scMfkId + " -rev=" + revId);
                        /**
                         * If assembly, export the Parts list
                         */
                        StructureManagement.CreateBOMWindowsOutput zOut = createBomWindow(itemRev.get_items_tag(), itemRev);
                        BOMLine rootBomLine = zOut.bomLine;
                        if(checkResultDirectory())
                        {
                            exportToExcel(new ModelObject[] { rootBomLine });
                        }else
                        {
                            this.m_zTaskLogger.error("Unable to create result directory");
                        }
                        StructureManagementService smServ = StructureManagementService.getService(SoaHelper.getSoaConnection());
                        smServ.closeBOMWindows(new BOMWindow[] { zOut.bomWindow });
                    }
                    
                    /**
                     * Check for the BCT file, download if present
                     */
                    if(checkResultDirectory())
                    {
                        bctFilename = downloadBCTFile(itemRev,this.stagingLoc + File.separatorChar + dispatcherresultDir);
                    }else
                    {
                        this.m_zTaskLogger.error("Unable to create result directory");
                    }
                    zDBAnarkStringPrintStream.println(scUUID);
                    zDBAnarkStringPrintStream.println("-cadfile \"" + anarkString + "\"");
                    zDBAnarkStringPrintStream.println(scTaskId);
                    zDBAnarkStringPrintStream.println(anarkString);
                    //zDBAnarkStringPrintStream.println(scMfkId + "_" + revId + UGPART_FILE_EXT);
                    zDBAnarkStringPrintStream.println(scMfkId + UGPART_FILE_EXT);
                    if(bctFilename.length()>2)
                    {
                        zDBAnarkStringPrintStream.println(bctFilename);
                    }
                    
                    /**
                     * Check for the workflow task name to generate the input argument values for Watermarking
                     */
                    ModelObject[] tasks = itemRev.get_process_stage_list();
                    EPMConditionTask conditionTask = null;
                    if (tasks != null & tasks.length > 0)
                    {
                        dmServ.getProperties(tasks, new String[]{GETCommon.rootTargetAttachmentsAttr, GETCommon.creationDateAttr, GETCommon.rootTaskAttr, GETCommon.currentNameAttr});
                        for (ModelObject taskObject : tasks)
                        {
                            if (!(taskObject instanceof EPMConditionTask))
                            {
                                continue;
                            }
                            m_zTaskLogger.info("Got the EPM Condition Task Instance");
                            conditionTask = (EPMConditionTask) taskObject;                            
                            String taskName = conditionTask.get_current_name();                            
                            m_zTaskLogger.info("Current Task Name: " + taskName);
                            if(!taskName.equals("Released"))
                            {
                                zDBAnarkWMStringPrintStream.println(scwatermarkUUID);
                                zDBAnarkWMStringPrintStream.println(taskName);
                            }
                        }
                    }
                }
            }
            zDBStringTransData.setTranslationDBMapInfo(zTransDBMapInfo);            
        }
        catch (Exception e) 
        {
            e.printStackTrace();
        }
        finally
        {
            try
            {
                if (zDBStringStream != null) {
                    zDBStringStream.close();
                }
                if (zDBAnarkStringStream != null) {
                    zDBAnarkStringStream.close();
                }
                if (zDBAnarkWMStringStream != null) {
                    zDBAnarkWMStringStream.close();
                }
            }
            finally
            {
                try
                {
                    if (zDBStringPrintStream != null) {
                        zDBStringPrintStream.close();
                    }
                    if (zDBAnarkStringPrintStream != null) {
                        zDBAnarkStringPrintStream.close();
                    }
                    if (zDBAnarkWMStringPrintStream != null) {
                        zDBAnarkWMStringPrintStream.close();
                    }
                }
                finally
                {
                    zDBStringStream = null;
                    zDBStringPrintStream = null;
                    zDBAnarkStringStream = null;
                    zDBAnarkStringPrintStream = null;
                    zDBAnarkWMStringStream = null;
                    zDBAnarkWMStringPrintStream = null;
                }
            }
        }
        return zTask;
    }

    /**
     * Method to get Command Line input name format for UG Clone
     */
    public static String getCLIName(String mfkId, String revId, boolean fMasterPart, String partName, String imanRelationshipType)
    {
        String[] cliDelimiters = { "/", "@", "#", "$", "^", "&", "(", ")", "|", "[", "]", "{", "}" };


        String cliDelimiter = null;
        for (int i = 0; i < cliDelimiters.length; i++)
        {
            String delimiter = cliDelimiters[i];
            if (mfkId.indexOf(delimiter) == -1) {
                if (revId.indexOf(delimiter) == -1) {
                    if ((fMasterPart) || (partName.indexOf(delimiter) == -1))
                    {
                        cliDelimiter = delimiter;

                        break;
                    }
                }
            }
        }
        if (cliDelimiter == null) {
            return null;
        }
        StringBuffer buffer = new StringBuffer();
        buffer.append("@DB" + cliDelimiter + mfkId + cliDelimiter + revId);
        if (!fMasterPart) {
            buffer.append(cliDelimiter + imanRelationshipType + cliDelimiter + partName);
        }
        return buffer.toString();
    }

    /**
     * Method to get Command Line input name format for ACSCLI
     */
    public static String getAnarkCLIName(String mfkId, String revId, boolean fMasterPart, String partName, String imanRelationshipType, String stagingLocation)
    {
        StringBuffer buffer = new StringBuffer();
        //buffer.append(stagingLocation + File.separatorChar + dispatcherresultDir + File.separatorChar + mfkId + "_" + revId + UGPART_FILE_EXT);
        buffer.append(stagingLocation + File.separatorChar + dispatcherresultDir + File.separatorChar + mfkId + UGPART_FILE_EXT);
        return buffer.toString();
    }

    /**
     * Method to check if Item Revision is an Assembly
     */
    private boolean isAssembly(Dataset dataset, ItemRevision itemRev)
            throws Exception
    {
        itemRev = (ItemRevision)SoaHelper.getProperties(itemRev, GETCommon.structureRevisionsAttr);
        PSBOMViewRevision[] bvrs = itemRev.get_structure_revisions();
        if ((bvrs.length > 0)) {
            return true;
        }
        return false;
    }

    /**
     * Method to create BOM Window, pack the bom structure befor export to excel
     */
    public StructureManagement.CreateBOMWindowsOutput createBomWindow(Item zItem, ItemRevision zRev)
            throws Exception
    {
        StructureManagementService smServ = StructureManagementService.getService(SoaHelper.getSoaConnection());

        StructureManagement.GetRevisionRulesResponse zRevRes = smServ.getRevisionRules();
        String configRule = GETCommon.latestworkingRevisionRule;
        RevisionRule zSelRule = null;
        for (StructureManagement.RevisionRuleInfo zRule : zRevRes.output) {
            if (zRule.revRule.get_object_name().equals(configRule))
            {
                zSelRule = zRule.revRule;
                break;
            }
        }
        StructureManagement.CreateBOMWindowsInfo[] arg0 = new StructureManagement.CreateBOMWindowsInfo[1];
        arg0[0] = new StructureManagement.CreateBOMWindowsInfo();
        arg0[0].item = zItem;
        arg0[0].itemRev = zRev;
        if (zSelRule != null)
        {
            this.m_zTaskLogger.info("Applying " + zSelRule.get_object_name() + " Revision rule to expand the assembly");
            arg0[0].revRuleConfigInfo = new StructureManagement.RevisionRuleConfigInfo();
            arg0[0].revRuleConfigInfo.revRule = zSelRule;
        }
        StructureManagement.CreateBOMWindowsResponse zRes = smServ.createBOMWindows(arg0);
        if(zRes.output.length > 0)
        {
            BOMLine bomLine = zRes.output[0].bomLine;

            packAllChildren(bomLine);
        }
        return zRes.output[0];
    }

    /**
     * Method to export the BOM structure to Excel using template
     */
    protected void exportToExcel(ModelObject[] objects)
    {
        try
        {
            String scExportedFilePath = this.stagingLoc + File.separatorChar + dispatcherresultDir + File.separatorChar + partslistFileName;
            ExportToApplicationInputData1 data = new
                    ExportToApplicationInputData1();

            data.applicationFormat = GETCommon.msexcelDatasetType; // "MSWordXMLLive" | "MSWordXML" | "MSExcelLive" | "MSExcel"
            data.attributesToExport = new String[0];
            data.objectsToExport = objects;
            data.templateId = exportexcelTemplate; // "REQ_default_excel_template" | "REQ_default_struct_template" | "REQ_default_RM_template" | "REQ_default_rel_template" ;

            ExportToApplicationResponse resp =
                    fileImportExportService.exportToApplication(new 
                            ExportToApplicationInputData1[]{ data });

            if(resp.transientFileReadTickets.length > 0)
            {
                for(String ticket :
                    resp.transientFileReadTickets)
                {
                    System.out.println("Ticket: " +
                            ticket);
                    fileManagementUtility.getTransientFile(ticket,
                            scExportedFilePath);
                }
            }
        }
        catch(ServiceException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Method to download BCT file to Staging location
     */
    private String downloadBCTFile(ModelObject modelObject, String stagingLoc)
            throws Exception
    {
        ItemRevision itemRev = (ItemRevision)modelObject;

        String bct_relation = GETCommon.imanspecificationRelType;
        String dataset_types = GETCommon.bctinspectorDatasetType;
        String bctFilename = "";

        ModelObject[] revObjArr = { itemRev };
        String[] revProps = new String[1];
        revProps[0] = bct_relation;
        this.dmServ.getProperties(revObjArr, revProps);
        ModelObject[] related_objs = itemRev.getPropertyObject(
                bct_relation).getModelObjectArrayValue();

        POM_application_object[] RelObjs = (POM_application_object[])Arrays.copyOf(
                related_objs, related_objs.length, 
                POM_application_object[].class);

        for (int knx = 0; knx < RelObjs.length; knx++) {
            if ((RelObjs[knx] instanceof Dataset)) {
                Dataset dataset = (Dataset)RelObjs[knx];
                
                if (dataset_types.contains(dataset.get_object_type())) {
                    ModelObject[] dsObj = { dataset };
                    String[] dsProps = new String[2];
                    dsProps[0] = GETCommon.refListAttr;
                    dsProps[1] = GETCommon.lastModDateAttr;
                    this.dmServ.getProperties(dsObj, dsProps);
                    ModelObject[] contexts = dataset.get_ref_list();

                    POM_application_object[] contObjArr = 
                            (POM_application_object[])Arrays.copyOf(contexts, contexts.length, 
                                    POM_application_object[].class);
                    ImanFile zIFile = null;
                    for (int j = 0; j < contObjArr.length; j++) {
                        if ((contObjArr[j] instanceof ImanFile)) {
                            zIFile = (ImanFile)contObjArr[j];
                        }
                    }

                    File zFile = TranslationRequest.getFileToStaging(
                            zIFile, stagingLoc);
                    bctFilename = zFile.getName();
                }
            }
        }
        return bctFilename;
    }
    /**
     * Method to check the presence of staging result directory
     */
    private boolean checkResultDirectory()
    {
        boolean stat = true;
        File resultDir = new File(this.stagingLoc + File.separatorChar + dispatcherresultDir);

        if(!resultDir.exists())
        {
            stat = resultDir.mkdir();
        }
        return stat;
        
    }

    /**
     * Method to pack bom lines
     */
    private void packAllChildren(BOMLine bomLine)
            throws Exception
    {
        ItemRevision rev = (ItemRevision)bomLine.get_bl_revision();
        SoaHelper.refresh(rev);

        PSBOMViewRevision[] bvrs = rev.get_structure_revisions();
        SoaHelper.refresh(bvrs);

        bomLine = (BOMLine)SoaHelper.getProperties(bomLine, GETCommon.blChildlinesAttr);
        ModelObject[] cmps = bomLine.get_bl_child_lines();
        for (int i = 0; i < cmps.length; i++) {
            if ((cmps[i] instanceof BOMLine))
            {
                BOMLine tempBomLine = (BOMLine)cmps[i];
                ServiceData response =  structureService.packOrUnpack(new BOMLine[] {tempBomLine},2);
                String errorMessage = GETCommon.getErrorFromServiceData(response);
                if (errorMessage != null)
                {
                    this.m_zTaskLogger.error("Unable to pack the bomlines : " + errorMessage);
                }
            }
        }
    }

    /**
     * Method to delete existing 3D PDF dataset associated with Item Revision
     */
    private void deleteExistingPDF(ModelObject modelObject)
            throws Exception
    {
        boolean cleartoDelete=false;
        ItemRevision itemRev = (ItemRevision)modelObject;

        String pdf_relation = GETCommon.imanmanifestationRelType;
        String dataset_types = GETCommon.pdfDatasetType;
        String pdfFilesuffix = anarkDatasetSuffix;

        ModelObject[] revObjArr = { itemRev };
        String[] revProps = new String[1];
        revProps[0] = pdf_relation;
        this.dmServ.getProperties(revObjArr, revProps);
        ModelObject[] related_objs = itemRev.getPropertyObject(
                pdf_relation).getModelObjectArrayValue();

        POM_application_object[] RelObjs = (POM_application_object[])Arrays.copyOf(
                related_objs, related_objs.length, 
                POM_application_object[].class);

        for (int knx = 0; knx < RelObjs.length; knx++) {
            if ((RelObjs[knx] instanceof Dataset)) {
                Dataset dataset = (Dataset)RelObjs[knx];
                
                if (dataset_types.contains(dataset.get_object_type())) {
                    ModelObject[] dsObj = { dataset };
                    String[] dsProps = new String[2];
                    dsProps[0] = GETCommon.refListAttr;
                    dsProps[1] = GETCommon.objectNameAttr;
                    this.dmServ.getProperties(dsObj, dsProps);
                    
                    if(dataset.get_object_name().contains(pdfFilesuffix))
                    {
                        this.m_zTaskLogger.info("Existing 3D PDF detected : " + dataset.get_object_name());
                        
                        cleartoDelete = deleteRelation(modelObject, dataset, GETCommon.imanmanifestationRelType);
                        if(cleartoDelete)
                        {
                            ServiceData response = dmServ.deleteObjects(dsObj);
                            String errorMessage = GETCommon.getErrorFromServiceData(response);
                            if (errorMessage != null)
                            {
                                this.m_zTaskLogger.info(errorMessage);
                                throw new Exception(errorMessage);
                            }
                            this.m_zTaskLogger.info(dataset.get_object_name() + " Deleted..");
                        }
                        else
                        {
                            this.m_zTaskLogger.info("Unable to delete existing 3D PDF : " + dataset.get_object_name() + ". Please delete manually and resubmit");
                        }
                    }
                }
            }
        }
    }
    /**
     * Method to delete existing 3D PDF Dataset relation associated with Item Revision
     */
    public boolean deleteRelation(Object primaryObj, Object secondaryObj, String relationName) throws NotLoadedException
    {
        if(primaryObj == null || secondaryObj == null)
        {
            return false;
        }
        Relationship relationship[] = new Relationship[1];
        relationship[0] = new Relationship();
        relationship[0].clientId=this.request.getPropertyObject(GETCommon.taskIDAttr).getStringValue();
        relationship[0].primaryObject=(ModelObject)primaryObj;
        relationship[0].secondaryObject=(ModelObject)secondaryObj;
        relationship[0].relationType=relationName;
        relationship[0].userData=null;
        ServiceData response = dmServ.deleteRelations(relationship);
        if(response.sizeOfPartialErrors() == 0)
        {
            return true;
        }
        else
        {
            String errorMessage = GETCommon.getErrorFromServiceData(response);
            if (errorMessage != null)
            {
                this.m_zTaskLogger.info(errorMessage);
            }
            return false;
        }
    }
}