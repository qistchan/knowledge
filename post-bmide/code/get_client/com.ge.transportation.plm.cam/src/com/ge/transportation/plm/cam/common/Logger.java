package com.ge.transportation.plm.cam.common;

import java.io.*;
import java.text.*;
import java.util.Date;
import java.text.SimpleDateFormat;

public class Logger {

	public Logger() 
	{
		
	}
	
	private static String logFile = "";
    private final static DateFormat df = new SimpleDateFormat ("yyyy.MM.dd  hh:mm:ss ");    
    public static void setLogFilename(String filename) {
    	
    	try
    	{  
    		System.out.println("File name ::"+filename);
    		File temp = new File (filename);
    		temp.createNewFile();
    		logFile = temp.getAbsolutePath();
    		System.out.println(temp);

    	}
    	catch (Exception e)
    	{
    		System.out.println(stack2string(e));
    	}
        
        try {
            write("LOG file : " + filename);
        }
        catch (Exception e) { 
            System.out.println(stack2string(e));
        }
        
    }
    
    public static void write(String msg) {
        write(logFile, msg);
    }
    
    public static void write(Exception e) {
        write(logFile, stack2string(e));
    }
    
    public static void write(String file, String msg) {
        try 
        {
        	Date now = new Date();
            String currentTime = df.format(now); 
            FileWriter aWriter = new FileWriter(file, true);
            aWriter.write(currentTime + " " + msg 
                    + System.getProperty("line.separator"));
            System.out.println(currentTime + " " + msg);
            aWriter.flush();
            aWriter.close();
        }
        catch (Exception e) 
        {
            System.out.println(stack2string(e));
        }
    }
    
    private static String stack2string(Exception e) {
        try 
        {
            StringWriter sw = new StringWriter();
            PrintWriter pw = new PrintWriter(sw);
            e.printStackTrace(pw);
            return "FATAL ERROR ------\r\n" + sw.toString() + "------\r\n";
        }
        catch(Exception e2) 
        {
            return "bad stack2string";
        }
    }
	/* This file contains all reusable code*/
	    
}