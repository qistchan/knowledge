package com.ge.transportation.plm.mfg.custompanel;


import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.forms.widgets.FormToolkit;

import com.ge.transportation.plm.mfg.constants.Constants;
import com.teamcenter.rac.aifrcp.AIFUtility;
import com.teamcenter.rac.kernel.TCComponentProject;
import com.teamcenter.rac.kernel.TCSession;
import com.teamcenter.rac.util.AbstractCustomPanel;
import com.teamcenter.rac.util.IPageComplete;

public class GETManufacturingPartIDPanel extends AbstractCustomPanel implements IPageComplete {
  private Composite m_compositeObj;

  public GETManufacturingPartIDPanel() {
  }

  public GETManufacturingPartIDPanel(Composite p_parentObj) {
      super(p_parentObj);
  }

  @Override
  public void createPanel() {
	  
      FormToolkit FormToolkitObj = new FormToolkit(parent.getDisplay());
      m_compositeObj = FormToolkitObj.createComposite(parent);
      
      boolean isIDText = false;
 
	  final String strCurrentProject = getCurrentProject();
	 
	  Text itemIDText = null;
	  
	  Control[] parentChildren = parent.getChildren();
	    for (int inx = 0; inx < parentChildren.length; inx++) {
	      	      
	      if(parentChildren[inx] instanceof Composite) {
	    	  
	    	  Control[]  parentGrandChildren = ((Composite)parentChildren[inx]).getChildren();
	    	  for (int jnx = 0; jnx < parentGrandChildren.length; jnx++) {
	    		  
	    		  if(parentGrandChildren[jnx] instanceof Composite) {
	    			  
	    			  Control[]  parentGreatGrandChildren = ((Composite)parentGrandChildren[jnx]).getChildren();
	    			  for (int knx = 0; knx < parentGreatGrandChildren.length; knx++) {
	    				  
	    				  if(parentGreatGrandChildren[knx] instanceof Label) {
	    					 
	    					  if((Constants.BusinessObjects.strItemIDLabel).equals(((Label)parentGreatGrandChildren[knx]).getText())) {
	    						  isIDText = true;
	    					  } 
	    				  } else  if(parentGreatGrandChildren[knx] instanceof Text) {
	    	    			  
	    					  if(isIDText) {
	    						  isIDText = false;
		    					  itemIDText = (Text)parentGreatGrandChildren[knx];
		    					  itemIDText.setText(((Constants.General.EMPTY_STRING_VALUE_C).equals(strCurrentProject))?strCurrentProject:strCurrentProject + Constants.General.DASH_STRING_VALUE_C);
		    					  itemIDText.setSelection(4);
		    					  
		    					  itemIDText.addListener(SWT.KeyUp, new Listener() {
	    					        @Override
	    					        public void handleEvent(Event event) {
	    					            Text itemIDText = (Text)event.widget;

	    					            String strTypedText = itemIDText.getText();
	    					            Pattern PatternObj = Pattern.compile(Constants.General.CARET_STRING_VALUE_C + strCurrentProject + Constants.General.MFG_ITEM_ID_REGEX);
	    					            Matcher MatcherObj = PatternObj.matcher(strTypedText);
	    					            if(!MatcherObj.find()) {
	    					            	itemIDText.setForeground(new Color (parent.getDisplay(), 255, 0, 0));
	    					            } else {
	    					            	itemIDText.setForeground(new Color (parent.getDisplay(), 0, 0, 0));
	    					            }
	    					        }
	    					    });
	    					  } 
	    	    		  } 
	    			  }
	    		  }
	    	  }
	      }
	  }
  }

  public boolean isPageComplete() {
	  
      return true;
  }
  

  @Override
  public Composite getComposite() {
      return m_compositeObj;
  }

  @Override
  public void updatePanel() {
	  
  }
  
  public String getCurrentProject() {
	  
	  String strCurrentProject = Constants.General.EMPTY_STRING_VALUE_C;
	  
	  try {
		  TCComponentProject tcCurrentProject = ((TCSession)AIFUtility.getDefaultSession()).getCurrentProject();
		  if(null != tcCurrentProject) {
			  
			  strCurrentProject = tcCurrentProject.getPropertyDisplayableValue(Constants.BusinessObjects.Properties.strProjectID);
		  }
	  } catch(Exception eObj) {
		  
		  MessageDialog.openError(parent.getShell(), "Error", eObj.getMessage());
	  }
	  
	  return strCurrentProject;
  }

  @Override
  public Object getUserInput() {
	  
      return null;
  }
}