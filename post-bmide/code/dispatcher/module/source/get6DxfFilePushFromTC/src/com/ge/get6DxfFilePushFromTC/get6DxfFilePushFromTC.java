/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET6DxfFilePushFromTC.java//
//    Purpose:   Code to push the DXF files to Toaster location to process CAStoDo folders in B-7
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     07 May, 2017         Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

package com.ge.get6DxfFilePushFromTC;

import java.io.File;
import java.io.IOException;

import org.apache.commons.io.FileUtils;

public class get6DxfFilePushFromTC 
{
    static final String sStagingDirectoryResultFolder = "Result";
    static final String sDummyFileName = "DummyFile.txt";

    
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   getFileFromStaging()
    //
    //    Purpose:   Method to get the DXF file from Module staging location
    //
    //    Inputs:    String sInputDirectoryPath
    //    Outputs:   File
    //
    //    Return:    none
    //
    //     History:
    //      Who                   Date                 Description
    //  TCS Development Team     07 May, 2017         Initial Creation
    //
    ===========================================================================*/
    public static File getFileFromStaging ( String sInputDirectoryPath )
    {
        File fFolder = new File( sInputDirectoryPath );
        File[] listOfFiles = fFolder.listFiles();
        File inputFile = null;
        //checking for Physical file in the staging dir
        for ( File fPhyFile : listOfFiles ) 
        {
            if ( fPhyFile.isFile() )
            {    
                inputFile = new File( fPhyFile.getAbsolutePath() ); 
            }
        }
        return inputFile;
    }
    
    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   pushFileToNas()
    //
    //    Purpose:   Method to push the file from staging to NAS location
    //
    //    Inputs:    String inputDirectoryPath
    //    Outputs:   None
    //    Return:    none
    //
    //     History:
    //      Who                   Date                 Description
    //  TCS Development Team     07 May, 2017         Initial Creation
    //
    ===========================================================================*/
    public static void pushFileToNas ( String sInputDirectoryPath, String outputDirectoryPath, File fInputFile )
    {
        File folder = new File( sInputDirectoryPath );
        File[] listOfFiles = folder.listFiles();
        //checking for Physical file in the staging dir
        for ( File fPhyFile : listOfFiles ) 
        {
            System.out.println(fPhyFile.getName());
            if( fPhyFile.isDirectory() && fPhyFile.getName().equalsIgnoreCase( sStagingDirectoryResultFolder ) )
            {
                File fDummyFile = new File(fPhyFile.getAbsolutePath()+ File.separator + sDummyFileName);
                try
                {
                    if( fDummyFile.createNewFile() )
                    {
                        System.out.println( "Dummy File placed in Result folder" );
                    }
                }
                catch ( IOException e )
                {
                    e.printStackTrace();
                }
            }
            else if( fPhyFile.isFile() )
            {
                File fOutputDirectoryLocation = new File( outputDirectoryPath );
                try 
                {
                    FileUtils.copyFileToDirectory( fInputFile, fOutputDirectoryLocation );
                } 
                catch (IOException e) 
                {
                    e.printStackTrace();
                }
            }
        }
    }

    /*STARTFUNCDOC ***
    //
    ===========================================================================
    //   Function:   main()
    //
    //    Purpose:   Main Method for DXF file transfer
    //
    //    Inputs:    String args
    //    Outputs:   None
    //
    //    Return:    none
    //
    //     History:
    //      Who                   Date                 Description
    //  TCS Development Team     07 May, 2017         Initial Creation
    //
    ===========================================================================*/
    public static void main( String[] args ) 
    {
         //get the args from bat file 
        System.out.println("args length: "+ args.length);

        if( args.length == 2 )
        {
            String sInputDir = args[0];
            String sOutputDir = args[1];
            
            File inputTextFile =  getFileFromStaging( sInputDir );
            pushFileToNas( sInputDir, sOutputDir, inputTextFile );
           
        }
        else
        {
            System.out.println( "Number of arguments not equal to 2" );
        }
    }
}
