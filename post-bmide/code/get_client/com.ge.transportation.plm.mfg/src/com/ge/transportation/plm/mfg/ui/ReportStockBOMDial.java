package com.ge.transportation.plm.mfg.ui;

import java.io.FileNotFoundException;
import java.io.IOException;

import org.eclipse.jface.dialogs.Dialog;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

import com.ge.transportation.plm.mfg.constants.Constants;
import com.ge.transportation.plm.mfg.operations.ReportStockBOMExcel;
import com.teamcenter.rac.aif.kernel.AIFComponentContext;
import com.teamcenter.rac.aif.kernel.InterfaceAIFComponent;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.kernel.TCComponent;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentBOMWindow;
import com.teamcenter.rac.kernel.TCComponentBOMWindowType;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentItem;
import com.teamcenter.rac.kernel.TCComponentItemRevision;
import com.teamcenter.rac.kernel.TCComponentProject;
import com.teamcenter.rac.kernel.TCComponentRevisionRule;

import com.teamcenter.rac.kernel.TCException;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.soa.exceptions.NotLoadedException;

public class ReportStockBOMDial extends Dialog 
{
	private Text itemIdText;
	static ReportStockBOMExcel repStockMBom;
	private TCComponentBOMWindow bomWindow;
	private TCComponentRevisionRule selectedRevRule;
	private TCComponentItemRevision topParentRevision = null;
	private TCSession session;
	private TCComponentRevisionRule[] revRuleList;
	protected String SelectedItem1;
	protected String sSelectedRevRule;
	private String sProjName;
	private Composite composite = null;
	
	public ReportStockBOMDial ( Shell parentShell, TCComponentItemRevision itemRevParent ) 
	{
		 super(parentShell);
		 topParentRevision = itemRevParent;
	}
	
	//construct the dialogue box
	protected Control createDialogArea ( Composite parent )
	{
		composite = new Composite ( parent, SWT.NONE );
		GridLayout layout = new GridLayout(2, false);
		composite.setLayout(layout);
		composite.getShell().setText(Constants.ReportStockBOM.STOCKBOMTITLE);
		
		Label itemIdLabel = new Label ( composite, SWT.NONE );
		itemIdLabel.setText ( Constants.ReportStockBOM.ITEMIDREVID );
		itemIdLabel.setLayoutData ( new GridData ( GridData.END, GridData.CENTER, false, false ) );

		itemIdText = new Text ( composite, SWT.BORDER );
		GridData gridData = new GridData ( GridData.FILL, GridData.FILL, true, false );
		gridData.widthHint = convertHeightInCharsToPixels ( 20 );
		itemIdText.setLayoutData ( gridData );
		try 
		{
			itemIdText.setText ( topParentRevision.getPropertyDisplayableValue ( Constants.ReportStockBOM.ITEMIDS) + "/" + topParentRevision.getPropertyDisplayableValue ( Constants.ReportStockBOM.REV ) );
			itemIdText.setEditable ( false );
		} 
		catch ( NotLoadedException e1 ) 
		{
			e1.printStackTrace();
			MessageDialog.openError ( getParentShell(), "Error", "Report Generation Failed" + e1.getMessage() );
		}
		
		Label revRuleLabel = new Label ( composite, SWT.NONE );
		revRuleLabel.setText ( Constants.ReportStockBOM.REVRULES );
		revRuleLabel.setLayoutData (new GridData ( GridData.END, GridData.CENTER, false, false ) );

		final Combo RevRules = new Combo ( composite, SWT.DROP_DOWN );
	    
	    try 
		{
			session = ( TCSession ) ( AIFUtility.getDefaultSession() );
			revRuleList = TCComponentRevisionRule.listAllRules ( session );
			TCComponentProject sessionProj = session.getCurrentProject();
			sProjName = sessionProj.getPropertyDisplayableValue ( Constants.ReportStockBOM.PROJNAME );
			System.out.println ( "sProjName =" +sProjName );
			
			//set the default value
			RevRules.setText ( Constants.ReportStockBOM.GRVWIP );
			sSelectedRevRule = RevRules.getText();
			
			for ( int i = 0; i < revRuleList.length; i++ )
			{
				String revRuleName = revRuleList[i].getPropertyDisplayableValue ( Constants.ReportStockBOM.PARTNAME );
				RevRules.add ( revRuleName );
			}
			RevRules.addSelectionListener ( new SelectionAdapter() 
			{
				public void widgetSelected ( SelectionEvent e) 
				{
					sSelectedRevRule  = RevRules.getText();
				}
				
			});
			
		} 
		catch ( TCException | NotLoadedException e ) 
		{
			e.printStackTrace();
			MessageDialog.openError( getParentShell(), "Error", "Report Generation Failed" + e.getMessage() );
		}
	    catch ( Exception e ) 
		{
			e.printStackTrace();
			createNewDial ( e.getMessage() );
		}
	    
	    return composite;
	}
	
	public void okPressed()
	{
		try
		{
			if ( sSelectedRevRule != null )
			{
				MessageDialog.openInformation ( getParentShell(), "INFO",
						"The Excel Report Genetaion will be running as a background process, depending on size of BOM it  may take while."
						+ "Once Report generation is compeleted Excel will be Opened Automatically" );
				composite.getParent().getParent().dispose();
				
			    //getParentShell().composite.dispose();
				new Thread(new Runnable() 
				{
				     public void run() 
				     {
				    	 startGeneratingReport();
				     }
				}).start();
			}
			else
			{
				MessageDialog.openError ( getParentShell(), "Error", "Please Select Revision rule" );
			}
		}
		catch ( ArrayIndexOutOfBoundsException ex )
		{
			ex.printStackTrace();
			createNewDial(ex.getMessage());
			
			return;
		}
		
	}
	
	public void startGeneratingReport()
	{
		try 
		{
			System.out.println ( "topParentRevision =" + topParentRevision.getPropertyDisplayableValue ( "object_name" ) );
			
			/*call class to write in excel*/
			repStockMBom = new ReportStockBOMExcel ( sProjName );
			
			System.out.println ( "SelectedRevRule =" + sSelectedRevRule );
			//get the selected rev rule
			for ( int i = 0; i < revRuleList.length; i++ )
			{
				String revRuleName = revRuleList[i].getPropertyDisplayableValue ( Constants.ReportStockBOM.PARTNAME );
				if ( revRuleName.equals(sSelectedRevRule) )
				{
					selectedRevRule = revRuleList[i];
				}
			}
			
			//get the BOM window
			int level = 0;
			
			TCComponentBOMWindowType bomWindowType = ( TCComponentBOMWindowType ) session.getTypeComponent ( Constants.ReportStockBOM.BOMWINDOW );
			
			//get default revision rule
			bomWindow = bomWindowType.create ( selectedRevRule );
			
			//get bom window and set item revision as top line
			TCComponentBOMLine topLine = bomWindow.setWindowTopLine ( null, topParentRevision, null, null );
			
			//create new function for recursive children
			getAllChildsBOM (  topLine, level );
			
			//save the excel
			ReportStockBOMExcel.closeExcel();
		} 
		catch ( ArrayIndexOutOfBoundsException ex )
		{
			ex.printStackTrace();
			createNewDial(ex.getMessage());
			
			return;
		}
		catch ( TCException e ) 
		{
			e.printStackTrace();
			createNewDial(e.getMessage());
			
			return;
		} 
		catch ( FileNotFoundException e ) 
		{
			e.printStackTrace();
			createNewDial(e.getMessage());
			
			return;
		} 
		catch ( IOException e ) 
		{
			e.printStackTrace();
			createNewDial(e.getMessage());
			
			return;
		}
		catch ( NotLoadedException e2 ) 
		{
			e2.printStackTrace();
			createNewDial(e2.getMessage());
			
			return;
		}
		catch ( Exception e)
		{
			e.printStackTrace();
			createNewDial(e.getMessage());
			
			return;
		}
	}

	private void getAllChildsBOM ( TCComponentBOMLine topLine, int level ) 
	{
		try
		{
			//get item revision details
			TCComponentItemRevision itemRev = topLine.getItemRevision();
			if ( itemRev != null )
			{
				//get all bom line details
				String sFindNo = topLine.getPropertyDisplayableValue ( Constants.ReportStockBOM.FINDNO );
				
				//String sdFindNo = topLine.get
				String sQty =  topLine.getPropertyDisplayableValue ( Constants.ReportStockBOM.QTY );
				String sPackCount = topLine.getPropertyDisplayableValue ( Constants.ReportStockBOM.PACKCOUNT );
				String sBomLine = topLine.getPropertyDisplayableValue ( Constants.ReportStockBOM.BOMLINE );
				String sBomLLevel = Integer.toString(level);
				String sParentDetails = "";
				if ( level > 0 )
				{
					sParentDetails = topLine.getPropertyDisplayableValue ( Constants.ReportStockBOM.PARENTDETAILS );
				}
				
				String sitemId = itemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.ITEMIDS );
				String sRevId = itemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.REV );
				String sName = itemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.PARTNAME );
				String sUomTag = itemRev.getItem().getPropertyDisplayableValue ( Constants.ReportStockBOM.UOM );
				String sEngMakeBuy = itemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.ENGMAKEBUY );
				String sReleaseStat = itemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.RELEASESTATUS );
				String sItemRevType = itemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.REVTYPE );
				
				//get manufacturing form and its attributes
				TCComponentItem tcItem = itemRev.getItem();
				AIFComponentContext[] manufAttrForms = tcItem.getRelated ( Constants.ReportStockBOM.MANUFATTRFORMRELN );
				String sProjectMakeBuy = null;
				String sStrCode = null;
				String sStockMaterialQty = null;
				TCComponent stockmaterialRef = null;
				
				if ( manufAttrForms.length > 0 ) 
				{
					for ( int i = 0 ; i < manufAttrForms.length; i++  )
					{
						InterfaceAIFComponent manufAttrFormComp = manufAttrForms[i].getComponent();
						TCComponentForm manufAttrForm = ( TCComponentForm ) manufAttrFormComp;
						if ( manufAttrForm.getPropertyDisplayableValue ( Constants.ReportStockBOM.OWNINGPROJ ).equals(sProjName) )
						{
							sProjectMakeBuy = manufAttrForm.getPropertyDisplayableValue ( Constants.ReportStockBOM.PROJMAKEBUY );
							sStrCode = manufAttrForm.getPropertyDisplayableValue ( Constants.ReportStockBOM.STRCODE );
							sStockMaterialQty =  manufAttrForm.getPropertyDisplayableValue ( Constants.ReportStockBOM.STQTY );
							stockmaterialRef = manufAttrForm.getReferenceProperty ( Constants.ReportStockBOM.STOKMATERIALPROP );
						}
					}
				}
				
				//pass all above into excel function create new row and add all
				String sItemRevValue = sBomLLevel + Constants.ReportStockBOM.SEP + sBomLine + Constants.ReportStockBOM.SEP + sQty + Constants.ReportStockBOM.SEP + sFindNo + Constants.ReportStockBOM.SEP +  sPackCount + Constants.ReportStockBOM.SEP + sParentDetails + Constants.ReportStockBOM.SEP +
						              sitemId + Constants.ReportStockBOM.SEP + sName + Constants.ReportStockBOM.SEP + sUomTag + Constants.ReportStockBOM.SEP + sRevId +  Constants.ReportStockBOM.SEP + sStrCode + Constants.ReportStockBOM.SEP + sEngMakeBuy + Constants.ReportStockBOM.SEP + selectedRevRule 
						              + Constants.ReportStockBOM.SEP + sReleaseStat + Constants.ReportStockBOM.SEP + sProjectMakeBuy + Constants.ReportStockBOM.SEP + sItemRevType + Constants.ReportStockBOM.SEP + Constants.ReportStockBOM.NO;
				
				System.out.println ( "Item Rev details=" + sItemRevValue );
				ReportStockBOMExcel.writeExcel(sItemRevValue);
				
				if ( ( stockmaterialRef != null ) && ( stockmaterialRef instanceof TCComponentItem ) )
				{
					TCComponentItem stockMaterialItem = ( TCComponentItem ) stockmaterialRef;
					TCComponentItemRevision stockMaterialItemRev = stockMaterialItem.getLatestItemRevision();
					String sStockitemId = stockMaterialItemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.ITEMIDS );
					String sStockRevId = stockMaterialItemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.REV );
					String sStockName = stockMaterialItemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.PARTNAME );
					String sStockUomTag = stockMaterialItemRev.getItem().getPropertyDisplayableValue ( Constants.ReportStockBOM.UOM );
					String sStockEngMakeBuy = stockMaterialItemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.ENGMAKEBUY );
					String sStockReleaseStat = stockMaterialItemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.RELEASESTATUS );
					String sStockItemRevType = stockMaterialItemRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.REVTYPE );
					int iStockLevel = level+1;
					String sStockLevel = Integer.toString ( iStockLevel );
					String sStockBomLine = sStockitemId + "/" + sStockRevId + "-" + sStockName;
					
					//pass all above into excel function create new row and add all
					//do it later
					String sStringStockValue = sStockLevel + Constants.ReportStockBOM.SEP + sStockBomLine + Constants.ReportStockBOM.SEP + sStockMaterialQty + Constants.ReportStockBOM.SEP + Constants.ReportStockBOM.NA + Constants.ReportStockBOM.SEP +  Constants.ReportStockBOM.NA + Constants.ReportStockBOM.SEP + sitemId + "/" + sRevId + "-" + sName + Constants.ReportStockBOM.SEP +
							sStockitemId + Constants.ReportStockBOM.SEP + sStockName + Constants.ReportStockBOM.SEP + sStockUomTag + Constants.ReportStockBOM.SEP + sStockRevId +  Constants.ReportStockBOM.SEP + 4 + Constants.ReportStockBOM.SEP + sStockEngMakeBuy + Constants.ReportStockBOM.SEP + selectedRevRule 
				              + Constants.ReportStockBOM.SEP + sStockReleaseStat + Constants.ReportStockBOM.SEP + Constants.ReportStockBOM.NA + Constants.ReportStockBOM.SEP + sStockItemRevType + Constants.ReportStockBOM.SEP + Constants.ReportStockBOM.NO;
					
					System.out.println ( "Stock Materials details=" + sStringStockValue );
					ReportStockBOMExcel.writeExcel(sStringStockValue);
				}
				
				/*get stock material details may be for future enhancements
				AIFComponentContext[] materialItems = tcItem.getRelated(MATERIALTRELN);
				System.out.println ( "size of  material=" + materialItems.length );
				if ( materialItems.length > 0 )
				{
					InterfaceAIFComponent materialItemComp = materialItems[0].getComponent();
					TCComponentItem materialItem = (TCComponentItem) materialItemComp;
					System.out.println ( "materialItem=" + materialItem.getPropertyDisplayableValue ( ITEMIDS ) );
					AIFComponentContext[] stockMaterialItems = materialItem.getRelated ( STOCKMATERIALTRELN );
					System.out.println ( "size of stock material=" + stockMaterialItems.length );
					for ( int i = 0; i < stockMaterialItems.length; i++ )
					{
						InterfaceAIFComponent stockMaterialItemComp = stockMaterialItems[i].getComponent();
						TCComponentItem stockMaterialItem = (TCComponentItem) stockMaterialItemComp;
						TCComponentItemRevision stockMaterialItemRev = stockMaterialItem.getLatestItemRevision();
						String sStockitemId = stockMaterialItemRev.getPropertyDisplayableValue ( ITEMIDS );
						String sStockRevId = stockMaterialItemRev.getPropertyDisplayableValue ( REV );
						String sStockName = stockMaterialItemRev.getPropertyDisplayableValue ( PARTNAME );
						String sStockUomTag = stockMaterialItemRev.getItem().getPropertyDisplayableValue ( UOM );
						String sStockEngMakeBuy = stockMaterialItemRev.getPropertyDisplayableValue ( ENGMAKEBUY );
						String sStockReleaseStat = stockMaterialItemRev.getPropertyDisplayableValue ( RELEASESTATUS );
						String sStockItemRevType = stockMaterialItemRev.getPropertyDisplayableValue ( REVTYPE );
						int iStockLevel = level+1;
						String sStockLevel = Integer.toString(iStockLevel);
						String sStockBomLine = sStockitemId + "/" + sStockRevId + "-" + sStockName;
						
						System.out.println ( "stock material details= " + sStockitemId + "\n" + sStockRevId + "\n" + sStockName
							    + "\n" + sStockUomTag + 	"\n" + 	NA	+ "\n" +  NA + "\n" + NA + "\n" + NA 
							    + "\n" + NA + "\n" + sStockEngMakeBuy +  "\n" + sStockReleaseStat +  "\n" + sStockItemRevType 
							    + "\n" + sStockLevel + "\nEND stock material details"  );
						
						//pass all above into excel function create new row and add all
						//do it later
						String sStringStockValue = sStockLevel + SEP + sStockBomLine + SEP + NA + SEP + NA + SEP +  NA + SEP + sitemId + "/" + sRevId + "-" + sName + SEP +
								sStockitemId + SEP + sStockName + SEP + sStockUomTag + SEP + sStockRevId +  SEP + 4 + SEP + sStockEngMakeBuy + SEP + selectedRevRule 
					              + SEP + sStockReleaseStat + SEP + NA + SEP + sStockItemRevType + SEP;
						ReportStockBOMExcel.writeExcel(sStringStockValue);
					}
				}*/
				
				//get made from part details
				AIFComponentContext[] madeFromParts = tcItem.getRelated ( Constants.ReportStockBOM.MADEFROMPARTRELN );
				if ( madeFromParts.length > 0 )
				{
					InterfaceAIFComponent madeFromPartComp = madeFromParts[0].getComponent();
					TCComponentItem madeFromPart = ( TCComponentItem ) madeFromPartComp;
					TCComponentItemRevision madeFromPartRev = madeFromPart.getLatestItemRevision();
					String sMadeFrompartItemId = madeFromPartRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.ITEMIDS );
					String sMadeFrompartRevId = madeFromPartRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.REV );
					String sMadeFrompartName = madeFromPartRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.PARTNAME );
					String sMadeFrompartUomTag = madeFromPartRev.getItem().getPropertyDisplayableValue ( Constants.ReportStockBOM.UOM );
					String sMadeFrompartEngMakeBuy = madeFromPartRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.ENGMAKEBUY );
					String sMadeFrompartReleaseStat = madeFromPartRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.RELEASESTATUS );
					String sMadeFrompartItemRevType = madeFromPartRev.getPropertyDisplayableValue ( Constants.ReportStockBOM.REVTYPE );
					int iMadeFrompartLevel = level+1;
					String sMadeFrompartLevel = Integer.toString ( iMadeFrompartLevel );
					String sMadeFromBomLine = sMadeFrompartItemId + "/" + sMadeFrompartRevId + "-" + sMadeFrompartName;
					
					//get manufacturing form and its attributes
					AIFComponentContext[] manufAttrMadeForms = madeFromPart.getRelated ( Constants.ReportStockBOM.MANUFATTRFORMRELN );
					String sProjectMadeMakeBuy = "";
					String sMadeStrCode = "";
					if ( manufAttrMadeForms.length > 0 ) 
					{
						for ( int i = 0 ; i < manufAttrForms.length; i++  )
						{
							InterfaceAIFComponent manufAttrMadeFormComp = manufAttrMadeForms[i].getComponent();
							TCComponentForm manufAttrMadeForm = ( TCComponentForm ) manufAttrMadeFormComp;
							if ( manufAttrMadeForm.getPropertyDisplayableValue ( Constants.ReportStockBOM.OWNINGPROJ ).equals ( sProjName ) )
							{
								sProjectMadeMakeBuy = manufAttrMadeForm.getPropertyDisplayableValue ( Constants.ReportStockBOM.PROJMAKEBUY );
								sMadeStrCode = manufAttrMadeForm.getPropertyDisplayableValue ( Constants.ReportStockBOM.STRCODE );
							}
						}
						
					}
					
					//pass all above into excel function create new row and add all
					String sMadeFrompartValue = sMadeFrompartLevel + Constants.ReportStockBOM.SEP + sMadeFromBomLine + Constants.ReportStockBOM.SEP + Constants.ReportStockBOM.NA + Constants.ReportStockBOM.SEP + Constants.ReportStockBOM.NA + Constants.ReportStockBOM.SEP +  Constants.ReportStockBOM.NA + Constants.ReportStockBOM.SEP + sitemId + "/" + sRevId + "-" + sName + Constants.ReportStockBOM.SEP +
							sMadeFrompartItemId + Constants.ReportStockBOM.SEP + sMadeFrompartName + Constants.ReportStockBOM.SEP + sMadeFrompartUomTag + Constants.ReportStockBOM.SEP + sMadeFrompartRevId +  Constants.ReportStockBOM.SEP + sMadeStrCode + Constants.ReportStockBOM.SEP + sMadeFrompartEngMakeBuy 
							+ Constants.ReportStockBOM.SEP + selectedRevRule + Constants.ReportStockBOM.SEP +  sMadeFrompartReleaseStat + Constants.ReportStockBOM.SEP + sProjectMadeMakeBuy + Constants.ReportStockBOM.SEP + sMadeFrompartItemRevType + Constants.ReportStockBOM.SEP + Constants.ReportStockBOM.YES;
					
					System.out.println ( "Made From Part details=" + sMadeFrompartValue );
					ReportStockBOMExcel.writeExcel(sMadeFrompartValue);
				}
					
				//get all the childrens of Top BOM line
				AIFComponentContext[] childCount = topLine.getChildren();
				int iChildLevel = level + 1;
				for ( int i = 0; i < childCount.length; i++ )
				{
					InterfaceAIFComponent childComp = childCount[i].getComponent();
					TCComponentBOMLine bomLineChild = ( TCComponentBOMLine ) childComp;
					
					//pass into recursive function
					getAllChildsBOM ( bomLineChild, iChildLevel );
				}
			
			}
		}
		catch ( ArrayIndexOutOfBoundsException ex )
		{
			ex.printStackTrace();
			createNewDial ( ex.getMessage() );
			
			return;
		}
		catch ( NotLoadedException e2 ) 
		{
			e2.printStackTrace();
			createNewDial ( e2.getMessage() );
			
			return;
		}
		catch ( TCException e ) 
		{
			e.printStackTrace();
			createNewDial ( e.getMessage() );
			
			return;
			
		}
		catch ( Exception e )
		{
			e.printStackTrace();
			createNewDial ( e.getMessage() );
			
			return;
		}
	}

	public  void createNewDial ( String Message )
	{
		Display display = new Display();
	    Shell shell = new Shell ( display );
	    shell.setText ( "Shell" );
	    shell.setSize(200, 200);
	    MessageDialog.openError( shell, "Error", "Report Generation Failed"  );
	   
	    while ( !shell.isDisposed() ) 
	    {
	      if ( !display.readAndDispatch() )
	        display.sleep();
	    }
	    display.dispose();
	}
}
