package com.ge.transportation.plm.mfg.beans;

import com.ge.transportation.plm.mfg.constants.Constants;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentItem;


public class StockMaterialAttributesFormBean {
	
	private boolean m_isModified = false;
	
	private int m_iLoadingIndex = 0;
	private int m_iStructureCode = 4;
	
	private String m_isPreferred = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strTCProject = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strProjectID = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strObjectString = Constants.General.EMPTY_STRING_VALUE_C;
	
	private TCComponentItem m_tcComponentItem = null;
	private TCComponentForm m_tcComponentForm = null;
	
	public void setModified(boolean p_isModified) {
		this.m_isModified = p_isModified;
	}
	
	public void setPreferred(String p_isPreferred) {
		this.m_isPreferred = p_isPreferred;
	}
	
	public void setLoadingIndex(int p_iLoadingIndex) {
		this.m_iLoadingIndex = p_iLoadingIndex;
	}
	
	public void setObjectString(String p_strObjectString) {
		this.m_strObjectString = p_strObjectString;
	}
	
	public void setTCProject(String p_strTCProject) {
		this.m_strTCProject = p_strTCProject;
		if(!(Constants.General.EMPTY_STRING_VALUE_C).equals(this.m_strTCProject)) {
			this.setTCProjectID(this.m_strTCProject.substring(0, 3));
		}
	}
	
	public void setTCProjectID(String p_strProjectID) {
		this.m_strProjectID = p_strProjectID;
	}
	
	public void setStructureCode(int p_iStructureCode) {
	}
	
	public void setTCComponentItem(TCComponentItem p_tcComponentItem) {
		this.m_tcComponentItem = p_tcComponentItem;
	}
	
	public void setTCComponentForm(TCComponentForm p_tcComponentForm) {
		this.m_tcComponentForm = p_tcComponentForm;
	}
	
	public String getPreferred() {
		return this.m_isPreferred;
	}
	
	public boolean getModified() {
		return this.m_isModified;
	}
	
	public int getLoadingIndex() {
		return this.m_iLoadingIndex;
	}
	
	public int getStructureCode() {
		return this.m_iStructureCode;
	}
	
	public String getTCProject() {
		return this.m_strTCProject;
	}
	
	public String getTCProjectID() {
		return this.m_strProjectID;
	}
	
	public String getObjectString() {
		return this.m_strObjectString;
	}
	
	public TCComponentItem getTCComponentItem() {
		return this.m_tcComponentItem;
	}
	
	public TCComponentForm getTCComponentForm() {
		return this.m_tcComponentForm;
	}
}