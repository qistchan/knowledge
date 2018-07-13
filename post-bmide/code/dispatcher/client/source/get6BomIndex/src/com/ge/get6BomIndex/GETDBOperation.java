
//==== Package  =================================================================
package com.ge.get6BomIndex;

//==== Imports  =================================================================
import java.util.List;

import com.teamcenter.ets.load.DefaultDatabaseOperation;
import com.teamcenter.translationservice.task.TranslationDBMapInfo;

//==== Class ====================================================================
/**
 * This class stores results for translation requests. This is a configuration
 * specified class based on provider name and translator name in Dispatcher
 * Client service property file. Stores translation result data on the source
 * dataset. If there are existing translation result data files, they may be
 * replaced depending upon the value of the UpdateExistingVisualizationData
 * TaskPrep instance variable.
 * 
 * @param zDbMapInfo
 *            DB mapper info object.
 * @param zFileList
 *            List of files mapped to the source file.
 * 
 * @throws Exception
 * 
 * 
 */
public class GETDBOperation extends DefaultDatabaseOperation 
{
    protected void load(TranslationDBMapInfo zDbMapInfo, List<String> zFileList) throws Exception
    {
        m_zTaskLogger.info((new StringBuilder()).append("Inside GETDBOperation for BOMIndex ").toString());
        try
        {
        }
        catch (Exception ex)
        {
        }
        m_zTaskLogger.info(" Exiting load method of GETDBOperation");
        // end load()
    }
}
