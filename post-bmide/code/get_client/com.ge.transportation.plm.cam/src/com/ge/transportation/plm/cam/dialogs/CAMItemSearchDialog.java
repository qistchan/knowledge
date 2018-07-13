package com.ge.transportation.plm.cam.dialogs;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import org.eclipse.jface.dialogs.Dialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.KeyAdapter;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.MessageBox;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;

import com.ge.transportation.plm.cam.common.Common;
import com.ge.transportation.plm.cam.common.Logger;

public class CAMItemSearchDialog extends Dialog 
{
	 String test1 = null;
	 int isFound = 0;
	 ArrayList<String> Machines = null;
	 ArrayList<String> Machinesg=null;
	 Button buttonOk = null;
	 Button buttonCancel = null;
	 
	 protected CAMItemSearchDialog(Shell parentShell)
	 {
		 super(parentShell);
		 
	 }
	 
	 protected Control createDialogArea(Composite parent) 
	 {
		 Composite area = (Composite) super.createDialogArea(parent);
		 area.getShell().setText("List of machines");
		 Logger.write("INFO - "+"Machine Search Dialog Opened Successfully");
		 GridLayout gridLayout = new GridLayout();
		 gridLayout.numColumns = 2;
		 area.setLayout(gridLayout);
		 
		 /*Filter */
		 final Text Filter;
		 new Label(area, SWT.NULL).setText("Filter:");
		 Filter = new Text(area, SWT.SINGLE | SWT.BORDER);
		 GridData gridData = new GridData(GridData.FILL_HORIZONTAL);
		 gridData.horizontalSpan = 1;
		 Filter.setLayoutData(gridData);
		 Filter.setTextLimit(1);
		 /*Text */
		 new Label(area, SWT.NULL).setText("Machine ID's available for the given site:");
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 gridData.horizontalSpan = 1;
		 /*Seperator*/
		 Label separator = new Label(area, SWT.HORIZONTAL | SWT.SEPARATOR);
		 gridData = new GridData(GridData.FILL_HORIZONTAL);
		 gridData.horizontalSpan = 2;
		 separator.setLayoutData(gridData);
			
		 /*Table format*/
		 final Table table = new Table(area, SWT.BORDER | SWT.FULL_SELECTION);
		 TableItem item = new TableItem(table, SWT.NONE);
		 
		 GridData data = new GridData(SWT.FILL, SWT.FILL, true, true);
		 data.heightHint = 200;
		 data.widthHint = 200;
		 data.horizontalSpan = 2;
		 table.setLayoutData(data);
		 
		 java.lang.String SelectedSite = CAMItemCreationDialog.labelSite.getText();
		 
		 String str1="ERIE";
		 String str2="GROVECITY";
		 
		 final boolean retval1 = str1.equals(SelectedSite);
		 final boolean retval2 = str2.equals(SelectedSite);
		 /*Editing*/
		 
		 if(retval1)
		 {
			 try 
			 {
				 //Machines = DBConnection.get_Machines_ERIE();
				 Machines = get_Machines_ERIE();
				 
			 } 
			 catch (SQLException e) 
			 {
				 e.printStackTrace();
				 Logger.write(e);
				 
			 }
			 
			 int MachineSize = Machines.size();
			 for (int i = 1; i < MachineSize; i++) 
			 {
				 item = new TableItem(table, SWT.NONE);
				 item.setText(Machines.get(i));
				 
			 }
			 
		 }
		 else if (retval2)
		 {
			 try 
			 {
				 Machinesg = get_Machines_GROVECITY();
				 
			 }
			 catch (SQLException e) 
			 {
				 e.printStackTrace();
				 Logger.write(e);
				 
			 }
			 
			 int MachineSizeG = Machinesg.size();
			 for (int i = 1; i < MachineSizeG; i++) 
			 {
				 item = new TableItem(table, SWT.NONE);
				 item.setText(Machinesg.get(i));
				 
			 }
			 
		 }
		 
		 Filter.addKeyListener(new KeyAdapter()
		 {
			 public void keyPressed(KeyEvent e)
			 {
				 if(e.keyCode >=97 && e.keyCode <=122)
				 {
					 table.removeAll();

					 //TableItem	item1 = new TableItem(table, SWT.NONE);
					 java.lang.String SelectedSiteT = CAMItemCreationDialog.labelSite.getText();
					 
					 String str1T="ERIE";
					 String str2T="GROVECITY";

					 final boolean retval1T = str1T.equals(SelectedSiteT);
					 final boolean retval2T = str2T.equals(SelectedSiteT);
					 char pp = e.character;
					 Filter.setText(String.valueOf(pp));

					 if(retval1T)
					 {
						 try 
						 {
							 //Machines = DBConnection.get_Machines_ERIE();
							 Machines = get_Machines_ERIE();
							 
						 }
						 catch (SQLException e1) 
						 {
							 e1.printStackTrace();
							 Logger.write(e1);
							 
						 }
						 
						 int MachineSize = Machines.size();
						 for (int i = 0; i < MachineSize; i++) 
						 {
							 String positioni = Machines.get(i);
							 char testchar = positioni.charAt(0);//"h"
							 char testchar2 = Filter.getText().charAt(0);
							 
							 boolean P = equalsIgnoreCaseTest(testchar, testchar2);
							 // TableItem item = new TableItem(table, SWT.NONE);
							 
							 if(P)
							 {
								 TableItem item1 = new TableItem(table, SWT.NONE);
								 
								 item1.setText(Machines.get(i));
								 isFound=1;
								 
							 }
							 
						 }
						 
					 }
					 else if (retval2T)
					 {
						 try 
						 {
							 Machinesg = get_Machines_GROVECITY();

						 }
						 catch (SQLException e1) 
						 {
							 e1.printStackTrace();
							 Logger.write(e1);
							 
						 }
						 
						 int MachineSizeG = Machinesg.size();
						 
						 for (int i = 0; i < MachineSizeG; i++) 
						 {
							 String positioni = Machinesg.get(i);
							 char testchar = positioni.charAt(0);//"h"
							 char testchar2 = Filter.getText().charAt(0);
							 boolean P = equalsIgnoreCaseTest(testchar, testchar2);
							 // TableItem item = new TableItem(table, SWT.NONE);
							 if(P)
							 {
								 TableItem item1 = new TableItem(table, SWT.NONE);
								 item1.setText(Machinesg.get(i));
								 isFound=1;
								 
							 }
							 
						 }
						 if(isFound==0)
						 {
							 
						 }
						 
					 }
					 //} /*Editing*/
					 
				 }
				 else if(e.keyCode ==8)
				 {
					 CreateTableLayout();
					 
				 } 
				 else if(Filter.getText().length()==0)
				 {
					 CreateTableLayout();
					 
				 }
				 else if(e.keyCode >= 48 && e.keyCode <= 57)
				 {
					 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR | SWT.OK);
					 messageBox1.setText("Error");
					 messageBox1.setMessage("Please enter only an alphabet");
					 messageBox1.open();
					 Logger.write("ERROR - "+"Please enter only an alphabet");
					 Filter.setText("");
					 
				 }
				 
			 }
			 private void CreateTableLayout() 
			 {
				 String str1="ERIE";
				 String str2="GROVECITY";
				 String SelectedSite11 = CAMItemCreationDialog.labelSite.getText();
				 final boolean retval11 = str1.equals(SelectedSite11);
				 final boolean retval21 = str2.equals(SelectedSite11);
				 /*Editing*/
				 
				 if(retval11)
				 {
					 try 
					 {
						 //Machines = DBConnection.get_Machines_ERIE();
						 Machines = get_Machines_ERIE();
						 
					 }
					 catch (SQLException e1) 
					 {
						 e1.printStackTrace();
						 Logger.write(e1);
						 
					 }
					 
					 int MachineSize = Machines.size();
					 for (int i = 1; i < MachineSize; i++) 
					 {
						 //TableItem item11 = new TableItem(table, SWT.NONE);
						 TableItem item1 = new TableItem(table, SWT.NONE);
						 item1.setText(Machines.get(i));
						 
					 }
					 
				 }
				 else if (retval21)
				 {
					 try 
					 {
						 Machinesg = get_Machines_GROVECITY();
						 
					 }
					 catch (SQLException e1) 
					 {
						 e1.printStackTrace();
						 Logger.write(e1);
						 
					 }
					 
					 int MachineSizeG = Machinesg.size();
					 for (int i = 1; i < MachineSizeG; i++) 
					 {
						 //TableItem item11 = new TableItem(table, SWT.NONE);
						 TableItem item1 = new TableItem(table, SWT.NONE);
						 item1.setText(Machinesg.get(i));
						 
					 }
					 
				 }
				 
			 }
			 
			 private boolean equalsIgnoreCaseTest(char testchar, char testchar2) 
			 {
				 if((Character.toLowerCase(testchar) == Character.toLowerCase(testchar2))||(Character.toUpperCase(testchar) == Character.toUpperCase(testchar2))) 
				 {
					 return true;
					 
				 }
				 else
				 {
					 return false;
					 
				 }
				 
			 }
			 
		 });
		 
		 /*Editing*/

		 /*Tabel*/
		 new Label(area, SWT.NULL).setText("");
		 gridData = new GridData(GridData.HORIZONTAL_ALIGN_FILL);
		 gridData.horizontalSpan = 2;

		 /*Seperator*/
		 Label separator1 = new Label(area, SWT.HORIZONTAL | SWT.SEPARATOR);
		 gridData = new GridData(GridData.FILL_HORIZONTAL);
		 gridData.horizontalSpan = 2;
		 separator1.setLayoutData(gridData);
		 
		 table.addListener(SWT.Selection, new Listener() 
		 {
			 public void handleEvent(Event event) 
			 {
				 if (event.detail == SWT.RADIO) 
				 {
					 return;
					 
				 }
				 else 
				 {
					 String selectedValue = event.item.toString();
					 if(!selectedValue.isEmpty())
					 {
						 int strLen = selectedValue.length();
						 if (strLen!=0)
						 {
							 String test = selectedValue.substring(11, strLen);
							 int strLen1 = test.length();
							 test1 = test.substring(0,strLen1-1);
							 
						 }
						 
					 }
					 else
					 {
						 test1 = null;
						 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR | SWT.OK);
						 messageBox1.setText("Error");
						 messageBox1.setMessage("Please select one machine");
						 messageBox1.open();
						 Logger.write("ERROR - "+"Please select one machine");
						 
					 }
					 
				 }
				 
			 }
			 
		 });
		 
		 //new Label(area, SWT.NULL).setText("V1.3");
		 //gridData = new GridData(GridData.HORIZONTAL_ALIGN_END);
		 //gridData.horizontalSpan = 1;
		 
		 return area;
		 
	 }
	 
	 @Override
	 protected void okPressed()
	 {
		 if(test1.length()==0)
		 {
			 MessageBox messageBox1 = new MessageBox(getShell(), SWT.ICON_ERROR | SWT.OK);
			 messageBox1.setText("Error");
			 messageBox1.setMessage("Please select one machine");
			 messageBox1.open();
			 Logger.write("ERROR - "+"Please select one machine");
			 
		 }
		 else
		 {
			 CAMItemCreationDialog.labelMID.setText(test1);
			 super.okPressed();
			 Logger.write("INFO - "+"Selected MachineID was set for Machine ID");
			 
		 }
		 
	 }
	 
	 protected void cancelPresed()
	 {
		 CAMItemCreationDialog.labelMID.setText("");
		 Logger.write("ERROR - "+"User not selected any Machine ID");
		 super.cancelPressed();
		 Logger.write("INFO - "+"Clicked CANCEL");
		 
	 }
	 
	 protected ArrayList<String> get_Machines_ERIE() throws SQLException
	 {
		 final ArrayList<String> get_Machines = new ArrayList<String>();
		 String MACHINENO_MACHIENNAME = null;

		 /* Check for JDBC Driver */
		 Common.checkDriver();
		 
		 /* get connected to DB */
		 Connection conn = Common.connectDB();
		
		 Statement stmt = conn.createStatement(ResultSet.TYPE_FORWARD_ONLY,ResultSet.CONCUR_READ_ONLY);
		 ResultSet rs=stmt.executeQuery("select DISTINCT MACHINE_NO, MACHINE_NAME from GETS_MFG_MACHINES WHERE  SITE_SEQ=12 ORDER BY MACHINE_NO ASC");
		 try
		 {
			 while (rs.next())
			 {
				 String MACHINE_NO = rs.getString("MACHINE_NO");
				 String MACHINE_NAME = rs.getString("MACHINE_NAME");
				 if (MACHINE_NO != null && MACHINE_NAME!=null)
				 {
					 MACHINENO_MACHIENNAME = MACHINE_NO.concat(" - ").concat(MACHINE_NAME);
					 get_Machines.add(MACHINENO_MACHIENNAME);
					 
				 }
				 
			 }
			 
		 }
		 catch (SQLException e)
		 {
			 e.printStackTrace();
			 Logger.write(e);
			 
		 }
		 finally
		 {
			 if (conn != null)
			 {
				 try
				 {
					 conn.close();
					 
				 }
				 catch (SQLException e)
				 {
					 e.printStackTrace();
					 Logger.write(e);
					 
				 }
				 
			 }
			 
		 }
		 return get_Machines;
		 
	 }
	 
	 protected static ArrayList<String> get_Machines_GROVECITY() throws SQLException
	 {
		 final ArrayList<String> get_Machinesg = new ArrayList<String>();
		 
		 /* Check for JDBC Driver */
		 Common.checkDriver();
		 /* get connected to DB */
		 Connection conn = Common.connectDB();
		 Statement stmt = conn.createStatement(ResultSet.TYPE_FORWARD_ONLY,ResultSet.CONCUR_READ_ONLY);
		 ResultSet rs=stmt.executeQuery("select DISTINCT MACHINE_NO, MACHINE_NAME from GETS_MFG_MACHINES WHERE  SITE_SEQ=11 ORDER BY MACHINE_NO ASC");
		 
		 try
		 {
			 while (rs.next())
			 {
				 String MACHINE_NO = rs.getString("MACHINE_NO");
				 String MACHINE_NAME = rs.getString("MACHINE_NAME");
				 if (MACHINE_NO != null && MACHINE_NAME!=null)
				 {
					 String MACHINENO_MACHIENNAME_G = MACHINE_NO.concat(" - ").concat(MACHINE_NAME);
					 get_Machinesg.add(MACHINENO_MACHIENNAME_G);
					 
				 }
				 
			 }
			 
		 }
		 catch (SQLException e)
		 {
			 com.ge.transportation.plm.cam.common.Common.showError( e.getErrorCode(), e.getMessage(), e.getClass().getName() );
			 e.printStackTrace();
			 Logger.write(e);
			 
		 }
		 finally
		 {
			 if (conn != null)
			 {
				 try
				 {
					 conn.close();
					 
				 }
				 catch (SQLException e)
				 {
					 e.printStackTrace();
					 Logger.write(e);
					 
				 }
				 
			 }
			 
		 }
		 return get_Machinesg;
		 
	 }
}
