/****************************************************************************
 * 
 * 				Copyright (c) 2013 GE Oil & Gas
 * 					Unpublished - All rights reserved
 * 
 ****************************************************************************
 *
 * File description:
 * 
 * Filename: GELogger
 * Module  : com.teamcenter.rac.logger
 *
 ****************************************************************************
 * Date			Name				Description of Change
 * 14-Feb-2013	Mukunthan			Initial Creation
 * 21-Feb-2013	Mukunthan			Setting the Log Level while initializing
 * 21-Feb-2013	Mukunthan			Fixed the issue for multiple logs created in the same session
 * 29-Mar-2013	Mahendra			Default log directory is taken as current directory
 ****************************************************************************/
package com.get.ontrack.logger;

import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.Properties;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PropertyConfigurator;

import com.get.ontrack.common.GETDesignReleaseConstants;



/**
 * Common class to provide the logger 
 *
 */
public final class GELogger {

	private static final String LOGGERPREFIX = "log4j.logger.";
	private static String timestamp = null;
	private static Logger currentLogger = null;
	
	/**
	 * Initiate Root Logger
	 * @return
	 */
	public static void initLogger() {
		initLoggerBase((String)null);
	}
	
	/**
	 * Initiate logger by class
	 * @param class 
	 * @return
	 */
	public static void initLogger(Class<?> clazz) {
		initLoggerBase(LOGGERPREFIX + clazz.getPackage().getName());
	}
	
	/**
	 * Initiate logger by name
	 * @param name 
	 * @return
	 */
	private static void initLoggerBase(String strLoggerName) {
		// if logger already initiated, skip initiation

		String currentLoggerName = null;
		
		
		if(null == System.getProperty(GETDesignReleaseConstants.Logger.LOG_DIR)) {
			System.setProperty(GETDesignReleaseConstants.Logger.LOG_DIR, GETDesignReleaseConstants.Logger.LOG_DIR_DEFAULT);
		}
		
		try{
			InputStream fileinputstream = GELogger.class.getResourceAsStream("log4j.properties");
			Properties properties = new Properties();

			properties.load(fileinputstream);
			fileinputstream.close();
			Properties properties1 = new Properties();
			String s;
			String s1;
			
			for(Iterator<Object> iterator = properties.keySet().iterator(); iterator.hasNext(); )
			{
				
				Object obj = iterator.next();
				s = (String)obj;
				s1 = properties.getProperty(s);
				
				// if file name contains time stamp. add the time stamp to file name
				if(s1.contains("${timestamp}")) {
					timestamp = null == timestamp ? getDateTime() : timestamp;
					s1 = s1.replaceFirst("..timestamp.", timestamp);
				}
			
				// initialize only specific logger
				if(s.startsWith(LOGGERPREFIX)) {
					if(null != strLoggerName && strLoggerName.startsWith(s)) {
						properties1.put(s, s1);
						currentLoggerName = s.replaceFirst(LOGGERPREFIX, "");
					}
				} else {
					properties1.put(s, s1);
				}
			}

			fileinputstream.close();
			PropertyConfigurator.configure(properties1);
			
			if(null != currentLoggerName) {
				setCurrentLogger(currentLoggerName);
			}
		}
		catch (Exception e) {
			Logger.getRootLogger().warn("error in initializing the loggers -> ", e);
		}	
	}
	
	
	/**
	 * get current logger
	 * @return
	 */
	public static Logger getCurrentLogger() {
		return null != currentLogger?currentLogger:Logger.getRootLogger();
	}
	
	/**
	 * set current logger from logger
	 * @param logger
	 */
	public static void setCurrentLogger(Logger logger) {
		currentLogger = logger;
		if(null != System.getProperty("log")) {
			updateLogLevelFromPreference(currentLogger, System.getProperty("log"));
		}
	}

	/**
	 * set current logger from name
	 * @param loggerName
	 */
	public static void setCurrentLogger(String loggerName) {
		currentLogger = Logger.getLogger(loggerName) ;
		if(null != System.getProperty("log")) {
			updateLogLevelFromPreference(currentLogger, System.getProperty("log"));
		}
	}

	/**
	 * set current logger from class
	 * @param clazz
	 */
	public static void setCurrentLogger(Class<?> clazz) {
		currentLogger = Logger.getLogger(clazz) ;
		if(null != System.getProperty("log")) {
			updateLogLevelFromPreference(currentLogger, System.getProperty("log"));
		}
	}

	/**
	 * get Date Time stamp
	 * @return
	 */
	private static String getDateTime() {
		SimpleDateFormat simpledateformat = new SimpleDateFormat("yyyyMMddHHmmss");
		Date date = new Date();
		return simpledateformat.format(date);
	}

	/**
	 * get the custom logger level from 
	 * @param loggerMap
	 */
	private static void updateLogLevelFromPreference(Logger logger, String sLevel) {
		// update the level only if not root logger
		if(null != sLevel) {
			logger.setLevel(Level.toLevel(sLevel, logger.getLevel()));
		}
	}
}