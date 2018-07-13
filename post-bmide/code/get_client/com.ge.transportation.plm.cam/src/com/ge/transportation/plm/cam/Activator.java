package com.ge.transportation.plm.cam;

import java.text.SimpleDateFormat;
import java.util.Date;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.osgi.framework.BundleContext;

import com.ge.transportation.plm.cam.common.Logger;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.swt.widgets.Shell;
import com.teamcenter.rac.aif.AIFDesktop;
import com.teamcenter.rac.kernel.TCComponentGroup;
import com.teamcenter.rac.kernel.TCComponentUser;
import com.teamcenter.rac.kernel.TCSession;

/**
 * The activator class controls the plug-in life cycle
 */
public class Activator extends AbstractUIPlugin {

	// The plug-in ID
	public static final String PLUGIN_ID = "com.ge.transportation.plm.cam"; //$NON-NLS-1$

	// The shared instance
	private static Activator plugin;
	TCSession session = (TCSession) AIFDesktop.getActiveDesktop().getCurrentApplication().getSession();
	private TCComponentUser user  		 = null ;
	private TCComponentGroup group		 = null ;
	//private TCComponentRole role       	 = null ;
	/**
	 * The constructor
	 */
	public Activator() {
	}

	/*
	 * (non-Javadoc)
	 * @see org.eclipse.ui.plugin.AbstractUIPlugin#start(org.osgi.framework.BundleContext)
	 */
	public void start(BundleContext context) throws Exception {
		
		SimpleDateFormat sdf = new SimpleDateFormat("ddMMyyyy_hhmmss");
		Date curDate = new Date();
		String strDate = sdf.format(curDate);
		String TEMPLOCATION = System.getenv("TMP");
		String TMPLOCATION = System.getenv("TEMP");
		user = session.getUser();
		String f = null;
		
		/* In case TMP environment variable is not set create log at c:\temp directory*/
		
		if( (TEMPLOCATION == null || TEMPLOCATION == "") && (TMPLOCATION == null || TMPLOCATION == "" ))
		{
			showError("TMP/TEMP Enviornment variable is not set."+"\n"+"Please set either of them to procede with CAM UTILS!!");
			return;
		}
		
		if( TEMPLOCATION != null)
		{
			f = TEMPLOCATION+"\\"+user.getUserId()+"_"+"CAM_Utils_log_"+strDate+".log";
		}
		else if( TMPLOCATION != null )
		{
			f = TMPLOCATION+"\\"+user.getUserId()+"_"+"CAM_Utils_log_"+strDate+".log";
		}
		
		Logger.setLogFilename(f);
		Logger.write("*************************************CAM UTIL STARTS**********************************************");
		super.start(context);
		plugin = this;
		getEnviornmentVariable();
	}

	/*
	 * (non-Javadoc)
	 * @see org.eclipse.ui.plugin.AbstractUIPlugin#stop(org.osgi.framework.BundleContext)
	 */
	public void stop(BundleContext context) throws Exception {
		plugin = null;
		
		Logger.write("*************************************CAM UTIL ENDS*********************************************");
		
		super.stop(context);
	}

	/**
	 * Returns the shared instance
	 *
	 * @return the shared instance
	 */
	public static Activator getDefault() {
		return plugin;
	}

	/**
	 * Returns an image descriptor for the image file at the given
	 * plug-in relative path
	 *
	 * @param path the path
	 * @return the image descriptor
	 */
	public static ImageDescriptor getImageDescriptor(String path) {
		return imageDescriptorFromPlugin(PLUGIN_ID, path);
	}
	public void getEnviornmentVariable()
	{
		String name = new Object(){}.getClass().getEnclosingMethod().getName();
		try
		{

			Logger.write("INFO - Running customer environment");
			
			Logger.write("INFO - Operation List Enviornment variables:");
			Logger.write("INFO - Java(TM) SE Runtime Environment="+System.getProperty("java.version"));
			user = session.getUser();
			Logger.write("INFO - Logged in User - "+user);
			Logger.write("INFO - Logged In User ID - "+user.getUserId());
			group = session.getGroup();
			Logger.write("INFO - Logged In User Group - "+group);
			Logger.write("INFO - Logged In User Group Name - "+group.getFullName());
			Logger.write("INFO - Logged In User Role - "+session.getRole());
			Logger.write("INFO - Logged In User Role Name - "+session.getRole().toString());
						
			Logger.write("INFO - GETS_CAM_BIN_DIR="+System.getenv("GETS_CAM_BIN_DIR"));
			Logger.write("INFO - GETS_BASE_DIR="+System.getenv("GETS_BASE_DIR"));
			Logger.write("INFO - GETS_COMMON_DECODE="+System.getenv("GETS_COMMON_DECODE"));
			Logger.write("INFO - UGII_CAM_POST_DIR="+System.getenv("UGII_CAM_POST_DIR"));
			Logger.write("INFO - UGII_CAM_POST_CONFIG_FILE="+System.getenv("UGII_CAM_POST_CONFIG_FILE"));
			Logger.write("INFO - UGII_CAM_LIBRARY_MACHINE_CONFIG_DIR="+System.getenv("UGII_CAM_LIBRARY_MACHINE_CONFIG_DIR"));
			Logger.write("INFO - UGII_CAM_USER_DEF_EVENT_DIR="+System.getenv("UGII_CAM_USER_DEF_EVENT_DIR"));
			Logger.write("INFO - FMS_HOME="+System.getenv("FMS_HOME"));
			Logger.write("INFO - UGII_UGMGR_HTTP_="+System.getenv("UGII_UGMGR_HTTP_"));
			Logger.write("INFO - UGII_UGMGR_COMMUNICATION="+System.getenv("UGII_UGMGR_COMMUNICATION"));
			Logger.write("INFO - GII_CAM_LIBRARY_MACHINE_CONFIG_DIR="+System.getenv("GII_CAM_LIBRARY_MACHINE_CONFIG_DIR"));
			Logger.write("INFO - UGII_CAM_USER_DEF_EVENT_DIR="+System.getenv("UGII_CAM_USER_DEF_EVENT_DIR"));
			
		}
		catch( Exception ex )
		{
			Logger.write( "FATAL ERROR - "+name);
			ex.printStackTrace();
			Logger.write(ex);
			
			showError( "exception while getting group and role" );
			Logger.write( "ERROR - exception while getting group and role" );
		}
	}
	public void showError( String errorMessage )
	{
		//String mainMessage = null;
		Logger.write(  "ERROR - "+errorMessage );
		MessageBox messageBox1 = new MessageBox( getShell(), SWT.ERROR|SWT.OK);
		messageBox1.setText("Error");
		messageBox1.setMessage( errorMessage );
		messageBox1.open();
	}

	private Shell getShell() {
		return null;
	}
}
