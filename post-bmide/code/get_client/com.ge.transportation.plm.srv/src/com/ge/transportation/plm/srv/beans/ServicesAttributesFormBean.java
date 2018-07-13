package com.ge.transportation.plm.srv.beans;

import java.util.Date;
import java.util.TreeMap;

import com.ge.transportation.plm.srv.constants.Constants;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentItem;

/**
* <h1>ServicesAttributesFormBean</h1>
* This class implements creation of 
* Services Form Type for Services functionality 
* using the Custom UI
*
* @author  Sudheer Arikere
* @version 1.0
* @since   2017-09-07
*/

public class ServicesAttributesFormBean {
	
	private boolean m_isModified = false;
	private int m_iLoadingIndex = 0;
	
	private String m_strsrvName ; // = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strSrvItemType = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strTierType = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strEngineFamily = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strObjectString = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strRepairable = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strCompID = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strPositionTracked = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_isServiceable = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_isSerialized = Constants.General.EMPTY_STRING_VALUE_C;
	
	private String m_isName ;//= Constants.General.EMPTY_STRING_VALUE_C;
	
	private TCComponentItem m_tcStockMaterial = null;
	private TCComponentItem m_tcComponentItem = null;
	private TCComponentForm m_tcComponentForm = null;
	
	private TCComponentBOMLine m_tcComponentBOMLine = null;
	
	public void setModified(boolean p_isModified) {
		this.m_isModified = p_isModified;
	}
	
	public void setLoadingIndex(int p_iLoadingIndex) {
		this.m_iLoadingIndex = p_iLoadingIndex;
	}
	
	public void setObjectString(String p_strObjectString) {
		this.m_strObjectString = p_strObjectString;
	}
	
/*	public void setSrvName(String p_strsrvName) {
		this.m_strsrvName = p_strsrvName;
	}*/
	
	public void setSrvItemType(String p_strSrvItemType) {
		this.m_strSrvItemType = p_strSrvItemType;
	}
	
	public void setEngineFamily(String p_strEngineFamily) {
		this.m_strEngineFamily = p_strEngineFamily;
	}
	
	public void setRepairable(String p_strRepairable) {
		this.m_strRepairable = p_strRepairable;
	}
	
	public void setTierType(String p_strTierType) {
		this.m_strTierType = p_strTierType;
	}
	
	public void setCompID(String p_tcCompID) {
		this.m_strCompID = p_tcCompID;
	}
	
	public void setPositionTracked(String p_strPositionTracked) {
		this.m_strPositionTracked = p_strPositionTracked;
	}
	
	public void setTCComponentItem(TCComponentItem p_tcComponentItem) {
		this.m_tcComponentItem = p_tcComponentItem;
	}
	
	public void setTCComponentForm(TCComponentForm p_tcComponentForm) {
		this.m_tcComponentForm = p_tcComponentForm;
	}
	
	public void setTCComponentBOMLine(TCComponentBOMLine p_tcComponentBOMLine) {
		this.m_tcComponentBOMLine = p_tcComponentBOMLine;
	}
	
	public void setServiceable(String p_isServiceable) {
		this.m_isServiceable = p_isServiceable;
	}
	
	public void setSerialized(String p_isSerialized) {
		this.m_isSerialized = p_isSerialized;
	}
	
	public boolean getModified() {
		return this.m_isModified;
	}
	
	public int getLoadingIndex() {
		return this.m_iLoadingIndex;
	}
	
	public String getSrvItemType() {
		return this.m_strSrvItemType;
	}
	
	public String getEngineFamily() {
		return this.m_strEngineFamily;
	} 
	
	public String getTierType() {
		return this.m_strTierType;
	} 
	
	public String getObjectString() {
		return this.m_strObjectString;
	}
	
	public String getRepairable() {
		return this.m_strRepairable;
	}
	
	public String getCompID() {
		return this.m_strCompID;
	}
	
	public String getPositionTracked() {
		return this.m_strPositionTracked;
	}
	
	public TCComponentItem getStockMaterialItem() {
		return this.m_tcStockMaterial;
	}
	
	public TCComponentItem getTCComponentItem() {    
		return this.m_tcComponentItem;
	}
	
	public TCComponentForm getTCComponentForm() {
		return this.m_tcComponentForm;
	}
	
	public TCComponentBOMLine getTCComponentBOMLine() {
		return this.m_tcComponentBOMLine;
	}
	
	public String getServiceable() {
		return this.m_isServiceable;
	}
	
	public String getSerialized() {
		return this.m_isSerialized;
	}
	
	public String getName() {
		return this.m_isName;
	}
}