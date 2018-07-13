/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET6DRSFilePushFromTC.java//
//    Purpose:   Code to push the drawing sheet files and pdf files to DRS from the staging location in module
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     10 July, 2016         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/
package com.ge.GET6DRSFilePushFromTC;

import java.io.File;
import java.io.IOException;

import org.apache.commons.io.FileUtils;
import org.apache.commons.io.FilenameUtils;

public class GET6DRSFilePushFromTC
{   
    static final String execEnvironment = "Production";  
    static final String PDFFile = "pdf";
    static final String rasterFile ="ras";
    static final String allowedItemSeries = "Y2K";
    static final String textFileExtension = ".txt";
    static final String textFile = "txt";    
    
    static String rootDirectory = "";   
    static String prevRevFolderNumber = "-1";
    static String prevSuffixFoldername = "1";
    static String stagingDirectoryResultFolder = "Result";
    static String dummyFileName = "DummyFile.pdf";
    
   
    /**STARTFUNCDOC *
    ===========================================================================
    * Method to set the root directory
    * 
    * @param inputItemID - outputRootdirectory in string 
    * @return File - Destination File
    ===========================================================================    
    ENDFUNCDOC   **/    
    public static void setRootDirectory( String outputRootdirectory )
    {
        rootDirectory = outputRootdirectory;        
    }
    
    /**STARTFUNCDOC *
    ===========================================================================
    * Method to get the pattern root ID
    * 
    * @param inputItemID - outputRootdirectory in string 
    * @return String - pattern root ID after truncation
    ===========================================================================    
    ENDFUNCDOC   **/ 
    
    public static String getPatternID ( String inputItemID )
    {    
         String patternRootId = com.ge.get6DrgIDFromPartlist.Get6DrgIDFromPartlist.getDrgIDFromPartList( inputItemID );
         return patternRootId;
    }
    
   /**STARTFUNCDOC *
    ===========================================================================
    * Method to return destination Folder/File used to put dataset fetched from Teamcenter
    * 
    * @param inputItemID - InputItemID in string 
    * @return File - Destination File
    ===========================================================================    
    ENDFUNCDOC   **/      
    public static File getDestinationPath( String patternItemID )
    {
        int modulus = 0;
        int j = 0;
        String filePath="";
        char[] arrayPat = new char[37];     //   takes upto 23 chars length of Item:  TOC\\9-W\\H-A\\CAD\\345\\-29\\301\\2
        char[] inputId = patternItemID.toCharArray();

        for( int i=0; i<inputId.length; i++ )         //Splits the ItemID in groups of 3
        {
            arrayPat[j] = inputId[i];
            j++;
            modulus = ( i+1 )%3;
            if( ( modulus == 0 ) && ( (i+1)!= inputId.length) )
            {
                arrayPat[j] = File.separatorChar;
                arrayPat[j+1]= File.separatorChar;
                j = j+2;             
            }
        }
        for( int i=0; i< arrayPat.length; i++ )
        {
            filePath = filePath + arrayPat[i];
        }        
       
        filePath = filePath.trim();  //To remove the trailing spaces
        System.out.print( "Folder location: " + filePath );
        File drsFilePath = new File( rootDirectory + File.separator + filePath.toLowerCase() );
        return drsFilePath;     //Returns the file directory where fetched dataset file is to be placed
    }   
 
    
    /**STARTFUNCDOC *
    ===========================================================================
     * Method to prepare Folder structure in case of a new Item
     * 
     * @param File - drsPath 
     * @return None
     ===========================================================================    
    ENDFUNCDOC   **/    
    public static void createFolderStructure( File drsPath )
    { 
        if ( new File( drsPath.getAbsolutePath() + File.separator).mkdirs() )       //creates the folder structure till -1 folder
        {
            System.out.println("\nFolder Creation Successful");
        }
    }
    
    /**STARTFUNCDOC *
    ===========================================================================
     * Method to prepare Folder structure -1 in case of a revised Item
     * 
     * @param File - drsPath 
     * @return None
     ===========================================================================    
    ENDFUNCDOC   **/
    
    public static void createPreviousRevisionFolder(  String patternID, File drsPath )
    {
        if ( patternID.length() > 9 )
        {
            if ( new File( drsPath.getAbsolutePath() + "-" + File.separator + prevSuffixFoldername ).mkdirs() )
            {
                System.out.println("Folder Creation Successful if the item ID contains Suffix then create folder 1");
            }
        }
        else if ( new File( drsPath.getAbsolutePath() + File.separator + prevRevFolderNumber ).mkdirs() )       //creates the folder structure till -1 folder
        {
            System.out.println("Folder Creation Successful for previous revision");
        }       
    }
    
    /**STARTFUNCDOC *
    ===========================================================================
     * Method to get name of files in the request folder in staging directory
     * 
     * @param inputItemID - InputDir in string 
     * @return String - Name of file
     ===========================================================================    
    ENDFUNCDOC   **/
    
    public static String getFileName(String inputDir)
    {
        File folder = new File(inputDir);
        File[] listOfFiles = folder.listFiles();
        String nameTemp = "";
        for (File iPhyFile : listOfFiles) 
        {
            if ( iPhyFile.isFile() )
            {
                nameTemp =  iPhyFile.getName();
            }
        }
        return nameTemp;
    }
    
    /**STARTFUNCDOC *
    ===========================================================================
    /**
    * Method to facilitate movement of obsolete revisions to -1 folder
    * 
    * @param directory - InputItem File 
    * @return nothing - Moves the obsolete revisions to -1 folder         
     ===========================================================================    
    ENDFUNCDOC   **/       
    
    public static void copyPreviousRevFile( String patternID, File drsPath, String fileName, String fileExt)
    {     
        String aPath = drsPath.getAbsolutePath();
        String[] children = drsPath.list();
        String lastFolderPath;
        if ( patternID.length() > 9 )
        {
            lastFolderPath = aPath +  "-" + File.separator + prevSuffixFoldername;
        }
        else
        {
            lastFolderPath = aPath + File.separator + prevRevFolderNumber;
        }
        File lastFolder = new File(lastFolderPath);
      
        for( int i=0;i<children.length;i++ )
        {
            if ( (new File(aPath+ File.separator +children[i])).isFile() )
            { 
                if( fileExt.equalsIgnoreCase( PDFFile ) )
                {
                    if(children[i].equalsIgnoreCase(fileName))
                    {
                        File previousRevisionFile = new File( aPath + File.separator +children[i] );
                        
                        //copy the file from staging to nas target folder
                        copyFileDir( previousRevisionFile, lastFolder );                       
                        previousRevisionFile.delete();
                    }
                }
                else
                {
                    File previousRevisionFile = new File( aPath + File.separator + children[i] );
                    if( FilenameUtils.getExtension(previousRevisionFile.getAbsolutePath()).equalsIgnoreCase( rasterFile ) )
                    {
                        //copy the file from staging to nas target folder
                        copyFileDir( previousRevisionFile, lastFolder );
                       
                        previousRevisionFile.delete();
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }  
        
    
    /**STARTFUNCDOC *
    ===========================================================================
    /**
    *  Method to fetch dataset from latest revision of Item from Teamcenter
    * 
    * * @param itemId, dRSFile  - InputItem, File 
    * @return nothing - Fetches the dataset and moves to the appropriate folder location         
    ===========================================================================    
    ENDFUNCDOC   
     * @throws IOException **/ 
    
    public static void filePushToDRS( String inputDir, File trgDir)
    {        
        File folder = new File(inputDir);
        File[] listOfFiles = folder.listFiles();
        //checking for Physical file in the staging dir
        System.out.print("\nNo of files: "+listOfFiles.length);
        for ( File iPhyFile : listOfFiles ) 
        {
            if( iPhyFile.isDirectory() && iPhyFile.getName().equalsIgnoreCase(stagingDirectoryResultFolder) )           
            {
                File dummyFile = new File(iPhyFile.getAbsolutePath()+ File.separator +dummyFileName);
                System.out.print("\nDummy file: "+dummyFile.getName());
                try
                {
                    dummyFile.createNewFile();
                    System.out.print("\nDummy file created");
                }
                catch ( IOException e )
                {
                    e.printStackTrace();
                }
            }
            else if ( iPhyFile.isFile() ) 
            {
                //get the extenion for the file whether it is .pdf or .ras
                System.out.print("\nTarget directory: " + trgDir);
                if( FilenameUtils.getExtension( iPhyFile.getAbsolutePath()).equalsIgnoreCase( PDFFile ) )
                {
                    copyFileDir( iPhyFile, trgDir );
                }
                else if( FilenameUtils.getExtension( iPhyFile.getAbsolutePath()).equalsIgnoreCase( rasterFile ) )
                {
                    copyFileDir( iPhyFile, trgDir );
                }
            }
        }
    }
    
    /**STARTFUNCDOC *
    ===========================================================================
    /**
    *  Method to copy the file from staging to NAS
    * 
    * * @param itemId, dRSFile  - InputItem, File 
    * @return nothing -         
    ===========================================================================    
    ENDFUNCDOC   
     * @throws IOException **/ 
    public static void copyFileDir ( File iPhyFile, File trgDir)
    {
          try
          {
              FileUtils.copyFileToDirectory( iPhyFile, trgDir, false );
              System.out.println( "\nFile is copied to NAS\n" + iPhyFile.getName() );
          }
          catch ( IOException e )
          {
              e.printStackTrace();
          }
    }

    /**STARTFUNCDOC *
    ===========================================================================
    /**
    *  Method to fetch file extenion for raster and pdfs from the staging location
    * 
    * * @param inputDir 
    * @return String - Fetches the file extension from staging folder location         
    ===========================================================================    
    ENDFUNCDOC   **/ 
    
    public static String getFileExt(String inputDir)
    {
        File folder = new File(inputDir);
        File[] listOfFiles = folder.listFiles();
        String extTemp = "";
        
        for (File iPhyFile : listOfFiles) 
        {
            if ( iPhyFile.isFile() )
            {
                extTemp = FilenameUtils.getExtension( iPhyFile.getAbsolutePath() );
            }
        }
        return extTemp;
    }    
    
    /**STARTFUNCDOC *
    ===========================================================================
    /**
    *  Method to fetch revision id from the text file created in NAS
    * 
    * * @param inputDir 
    * @return String - get revision id from the txt file from staging folder location         
    ===========================================================================    
    ENDFUNCDOC   **/ 
    public static String getRevisionDetails( File drsPath, String revId )
    {
        String revisionId = "";
        File folder = new File(drsPath.getAbsolutePath());
        File[] listOfFiles = folder.listFiles();
      
        for (File iPhyFile : listOfFiles) 
        {
            if ( iPhyFile.isFile() && (FilenameUtils.getExtension(iPhyFile.getAbsolutePath())).equalsIgnoreCase(textFile) )
            {
                revisionId = FilenameUtils.removeExtension( iPhyFile.getName() );
            }
        }
        return revisionId ;
    }
    
    /**STARTFUNCDOC *
    ===========================================================================
    /**
    *  Method to remove previous revision text file from staging
    * 
    * * @param staging Nas location path 
    * @return String - removes the text file from staging folder location         
    ===========================================================================    
    ENDFUNCDOC   **/ 
    public static File getPreviousRevisionFile( File drsPath)
    {
        File folder = new File(drsPath.getAbsolutePath());
        File[] listOfFiles = folder.listFiles();
        File previousRevisionTextFile = null;
        for (File iPhyFile : listOfFiles) 
        {
            if ( iPhyFile.isFile() && (FilenameUtils.getExtension(iPhyFile.getAbsolutePath())).equalsIgnoreCase("txt") )
            {
                previousRevisionTextFile = iPhyFile;
            }
        }
        return previousRevisionTextFile ;
    }

    /**STARTFUNCDOC *
    ===========================================================================
    /**
    *  Main function, which gets the arguments from get6DrsPush.bat file and calls the corresponding method calls.
    * 
    * * @param String[] args
    * @return nothing         
    ===========================================================================    
    ENDFUNCDOC   **/
    
    public static void main(String[] args) 
    {           
        File drsPath = null;    
        //get the args from bat file
        if ( args.length == 5 )
        {
            String inputDir = args[0];
            String outputDir = args[1];
            String itemId = args[2];
            String revId = args[3];
            String sEnvID = args[4];        
            
            String inputItemID = itemId.toUpperCase();                   
            revId = revId.toUpperCase();
            setRootDirectory( outputDir );
            String fileName = "";
            String targetFile = "";
            String fileExt = "";
            File[] listOfFiles = null;
        
            //get the patterns with regex calls
            String patternRootId = getPatternID ( inputItemID );
            drsPath =  getDestinationPath( patternRootId );
            fileName = getFileName( inputDir );
            fileExt = getFileExt( inputDir );
            if ( sEnvID.equalsIgnoreCase( execEnvironment ) )
            { 
                if ( new File( drsPath.getAbsolutePath()).exists() )
                {                    
                    if( fileExt.equalsIgnoreCase(rasterFile) )
                    {
                        String revisionDetail = "";
                        revisionDetail = getRevisionDetails(drsPath,revId);
                        if(revisionDetail.isEmpty())
                        {
                            File revisionDetailFile = new File( drsPath.getAbsolutePath() + File.separator + revId + textFileExtension );
                            try 
                            {
                                revisionDetailFile.createNewFile();
                                revisionDetail = revId;
                            }
                            catch (IOException e)
                            {
                                e.printStackTrace();
                            }
                            
                         // -1 folder structure
                            createPreviousRevisionFolder( patternRootId, drsPath );
                         // move the existing files to -1 folder  
                            copyPreviousRevFile( patternRootId, drsPath, fileName, fileExt );                          
                        }
                       //comparing the latest revision from the revision file in the NAS
                        System.out.print("\nRevision ID in TC: " +revId + "\nPrevious Revisionfile in NAS: "+revisionDetail);
                        if( revId.equalsIgnoreCase( revisionDetail ) )
                        {
                            filePushToDRS( inputDir, drsPath );
                        }
                        else
                        {
                            // logic for previous revision folder and file push to already existing folder str for the latest revision
                            File previousRevisionFile = getPreviousRevisionFile( drsPath );
                            
                            File revisionDetailFile = new File( drsPath.getAbsolutePath() + File.separator + revId + textFileExtension );
                            //delete the existing revision text file
                            previousRevisionFile.delete();
                            try 
                            {
                                //create new revision text file
                                revisionDetailFile.createNewFile();
                            } 
                            catch (IOException e) 
                            {
                                // TODO Auto-generated catch block
                                e.printStackTrace();
                            }

                            if( new File( drsPath.getAbsolutePath() + File.separator + prevRevFolderNumber ).exists() )
                            {
                                File obsoleteFiles[] = ( new File( drsPath.getAbsolutePath() + File.separator + prevRevFolderNumber ) ).listFiles();
                                for(int i = 0; i<obsoleteFiles.length; i++)
                                {
                                    if( FilenameUtils.getExtension( obsoleteFiles[i].getAbsolutePath()).equalsIgnoreCase( rasterFile ) )
                                    {
                                        obsoleteFiles[i].delete();
                                    }
                                }
                                copyPreviousRevFile( patternRootId, drsPath, fileName, fileExt );// -1 folder structure
                                filePushToDRS( inputDir, drsPath ); //keep the files inside the folder
                            }
                            else
                            {
                                createPreviousRevisionFolder( patternRootId, drsPath );
                                copyPreviousRevFile( patternRootId, drsPath, fileName, fileExt );// -1 folder structure
                                filePushToDRS( inputDir, drsPath ); //keep the files inside the folder
                            }
                        }
                    }
                    else if ( fileExt.equalsIgnoreCase (PDFFile) )
                    {
                        listOfFiles = drsPath.listFiles();
                        boolean isPDFFilePresent = false;
                        for (int k = 0; k < listOfFiles.length; k++)
                        {
                           if ( listOfFiles[k].isFile() ) 
                           {
                               isPDFFilePresent = true;
                               targetFile = listOfFiles[k].getName();
                               if ( targetFile.equalsIgnoreCase(fileName) )
                               {
                                   // if the nas location already existed and files are already there then copy the files to -1 folder and push the latest revision files
                                   if(!( new File( drsPath.getAbsolutePath()+ File.separator + prevRevFolderNumber ) ).exists())
                                   {
                                        createPreviousRevisionFolder( patternRootId, drsPath );    
                                   }
                                   copyPreviousRevFile( patternRootId, drsPath, fileName, fileExt );// -1 folder structure
                                   filePushToDRS( inputDir, drsPath ); //keep the files inside the folder
                                }
                                else
                                {
                                    filePushToDRS( inputDir, drsPath ); //keep the files inside the folder
                                }
                            }
                        }
                    //for pushing the pdf in case Y2K123456 and y2K123456AC items
                       if ( !isPDFFilePresent )
                       {
                            filePushToDRS( inputDir, drsPath );
                       }
                    }  
                }
                else
                {
                    // create new folder structure and push the files                        
                    if( fileExt.equalsIgnoreCase(rasterFile) )
                    {
                        createFolderStructure( drsPath );
                        File revisionDetailFile = new File( drsPath.getAbsolutePath() + File.separator + revId + textFileExtension );
                        try 
                        {
                            revisionDetailFile.createNewFile();
                        }
                        catch (IOException e)
                        {
                            e.printStackTrace();
                        }
                        filePushToDRS( inputDir, drsPath );
                    }
                    else
                    { 
                        createFolderStructure( drsPath );
                        filePushToDRS( inputDir, drsPath );
                    }
                }
            }
            else
            {
                //chk for non-production items say Y2K series
                if ( inputItemID.substring(0, 3).equalsIgnoreCase( allowedItemSeries ) )
                { 
                    if ( new File( drsPath.getAbsolutePath()).exists() )
                    {                        
                        //process the rasters
                        if( fileExt.equalsIgnoreCase(rasterFile) )
                        {
                            String revisionDetail = "";
                            revisionDetail = getRevisionDetails(drsPath,revId);
                            if(revisionDetail.isEmpty())
                            {
                                File revisionDetailFile = new File( drsPath.getAbsolutePath() + File.separator + revId + textFileExtension );
                                try 
                                {
                                    //create a revision.txt file to compare the rasters with previous revision's rasters in NAS
                                    revisionDetailFile.createNewFile();
                                    revisionDetail = revId;
                                }
                                catch (IOException e)
                                {
                                    e.printStackTrace();
                                }
                                
                                createPreviousRevisionFolder( patternRootId, drsPath );//-1 folder structure 
                                copyPreviousRevFile( patternRootId, drsPath, fileName, fileExt );// move the existing files to -1 folder
                            }
                            System.out.println("Revision present in output directory before renaming: "+revisionDetail);
                            //comparing the latest revision with the revision file in NAS
                            if( revId.equalsIgnoreCase(revisionDetail) )
                            {
                                filePushToDRS( inputDir, drsPath );
                            }
                            else
                            {
                                // logic for previous revision folder and file push to already existing folder str for the latest revision
                                File previousRevisionFile = getPreviousRevisionFile( drsPath );
                                File revisionDetailFile = new File( drsPath.getAbsolutePath() + File.separator + revId + textFileExtension );
                                previousRevisionFile.delete();
                                //create the new text file in nas target folder
                                try 
                                {
                                    revisionDetailFile.createNewFile();
                                } 
                                catch (IOException e) 
                                {
                                    // TODO Auto-generated catch block
                                    e.printStackTrace();
                                }
                                
                                if( new File( drsPath.getAbsolutePath() + File.separator + prevRevFolderNumber ).exists() )
                                {
                                    File obsoleteFiles[] = ( new File( drsPath.getAbsolutePath() + File.separator + prevRevFolderNumber ) ).listFiles();
                                    for(int i = 0; i<obsoleteFiles.length; i++)
                                    {
                                        if(FilenameUtils.getExtension(obsoleteFiles[i].getAbsolutePath()).equalsIgnoreCase( "ras" ))
                                        {
                                            obsoleteFiles[i].delete();
                                        }
                                    }
                                    copyPreviousRevFile( patternRootId, drsPath, fileName, fileExt );// -1 folder structure
                                    filePushToDRS( inputDir, drsPath ); //keep the files inside the folder
                                }
                                else
                                {
                                    createPreviousRevisionFolder( patternRootId, drsPath );
                                    copyPreviousRevFile( patternRootId, drsPath, fileName, fileExt );// -1 folder structure
                                    filePushToDRS( inputDir, drsPath ); //keep the files inside the folder
                                }
                            }
                        }
                        else if ( fileExt.equalsIgnoreCase (PDFFile) )
                        {
                            listOfFiles = drsPath.listFiles();
                            boolean isPDFFilePresent = false;
                            for (int k = 0; k < listOfFiles.length; k++)
                            {
                                if (listOfFiles[k].isFile()) 
                                {
                                    isPDFFilePresent = true;
                                    targetFile = listOfFiles[k].getName();
                                    if ( targetFile.equalsIgnoreCase(fileName) )
                                    {
                                        // if the nas location already existed and files are already there then copy the files to -1 folder and push the latest revision files
                                        if( !( new File( drsPath.getAbsolutePath()+ File.separator + prevRevFolderNumber ) ).exists() )
                                        {
                                            createPreviousRevisionFolder( patternRootId, drsPath );    
                                        }
                                        copyPreviousRevFile( patternRootId, drsPath, fileName, fileExt );// -1 folder structure
                                        filePushToDRS( inputDir, drsPath ); //keep the files inside the folder
                                    }
                                    else
                                    {
                                        filePushToDRS( inputDir, drsPath ); //keep the files inside the folder
                                    }
                                }
                            }
                            //for pushing the pdf in case Y2K123456 and y2K123456AC items
                            if ( !isPDFFilePresent )
                            {
                                filePushToDRS( inputDir, drsPath );
                            }
                        }  
                    }
                    else
                    {
                        // create new folder structure and push the files
                        if( fileExt.equalsIgnoreCase(rasterFile) )
                        {
                            createFolderStructure( drsPath );
                            File revisionDetailFile = new File( drsPath.getAbsolutePath() + File.separator + revId + textFileExtension );
                            try 
                            {
                                revisionDetailFile.createNewFile();
                            }
                            catch (IOException e)
                            {
                                e.printStackTrace();
                            }
                            filePushToDRS( inputDir, drsPath );
                        }
                        else
                        {
                            createFolderStructure( drsPath );
                            filePushToDRS( inputDir, drsPath );
                        }
                    }
                }
                else
                {
                    System.out.println( "The Item id is not recommended for Dev/Proto/QA environments" );
                }
            }
        }
        else
        {
            System.out.println("Number of arguments coming from batch file is greater or lesser than 5. Please check the batch file");
        }
    }
}