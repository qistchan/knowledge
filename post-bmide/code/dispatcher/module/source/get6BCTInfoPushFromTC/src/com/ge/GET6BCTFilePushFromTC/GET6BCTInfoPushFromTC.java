package com.ge.GET6BCTFilePushFromTC;

import java.io.File;
import java.io.IOException;

import org.apache.commons.io.FileUtils;

public class GET6BCTInfoPushFromTC 
{
    static final String stagingDirectoryResultFolder = "Result";
    static final String dummyFileName = "DummyFile.txt";
    static final String execEnvironment = "Production";
    static final String allowedItemSeries = "Y2K";
    
    public static File getFileFromStaging(String inputDirectoryPath)
    {
        File folder = new File(inputDirectoryPath);
        File[] listOfFiles = folder.listFiles();
        File inputFile = null;
        //checking for Physical file in the staging dir
        for ( File iPhyFile : listOfFiles ) 
        {
            if ( iPhyFile.isFile() )
            {    
                inputFile = new File(iPhyFile.getAbsolutePath()); 
            }
        }
        return inputFile;
    }
    
    public static void pushFileToNas(String inputDirectoryPath, String outputDirectoryPath, File InputFile)
    {
        File folder = new File(inputDirectoryPath);
        File[] listOfFiles = folder.listFiles();
        //checking for Physical file in the staging dir
        for ( File iPhyFile : listOfFiles ) 
        {
            System.out.println(iPhyFile.getName());
            if( iPhyFile.isDirectory() && iPhyFile.getName().equalsIgnoreCase(stagingDirectoryResultFolder) )
            {
                System.out.println("Result folder found");
                File dummyFile = new File(iPhyFile.getAbsolutePath()+  File.separator + dummyFileName);
                try
                { 
                    if(dummyFile.createNewFile())
                    {
                        System.out.println("Dummy file placed in Result folder \n");
                    }
                }
                catch ( IOException e )
                {
                    e.printStackTrace();
                }
            }
            else if(iPhyFile.isFile())
            {
                File OutputDirectoryLocation = new File(outputDirectoryPath);
                try 
                {
                	//copy file from staging to NAS location
                    FileUtils.copyFileToDirectory(InputFile,OutputDirectoryLocation);
                } 
                catch (IOException e) 
                {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) 
    {
         //get the args from bat file
         System.out.println("number of args from get6BctPush.bat" + args.length);
        if( args.length == 5 )
        {
            String inputDir = args[0];
            String outputDir = args[1];
            String itemId = args[2];
            String sEnvID = args[4];  
        
            if(sEnvID.equalsIgnoreCase(execEnvironment))
            {
                File inputTextFile =  getFileFromStaging(inputDir);
                pushFileToNas(inputDir, outputDir, inputTextFile);
            }
            else
            {
                if ( itemId.substring(0, 3).equalsIgnoreCase( allowedItemSeries ) )
                {
                    File inputTextFile =  getFileFromStaging(inputDir);
                    pushFileToNas(inputDir, outputDir, inputTextFile);
                }
                else
                {
                    System.out.println( "The Item id " + itemId + " is not recommended for Dev/Proto/QA environments." );;
                }
            }
        }
        else
        {
            System.out.println("Number of arguments not equal to 5");
        }
    }
}
