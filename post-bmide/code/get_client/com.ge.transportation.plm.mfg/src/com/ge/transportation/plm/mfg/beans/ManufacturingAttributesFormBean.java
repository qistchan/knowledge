package com.ge.transportation.plm.mfg.beans;

import java.util.Date;
import java.util.TreeMap;

import com.ge.transportation.plm.mfg.constants.Constants;
import com.teamcenter.rac.kernel.TCComponentBOMLine;
import com.teamcenter.rac.kernel.TCComponentForm;
import com.teamcenter.rac.kernel.TCComponentItem;

public class ManufacturingAttributesFormBean {
	
	private boolean m_isModified = false;
	private boolean m_isEngMakeBuySet = false;
	private int m_iLoadingIndex = 0;
	private int m_iStructureCode = -1;
	private double m_dStockMaterialQuantity = 0;
	
	private Date m_itemPublishDate = null;
	private Date m_BOMPublishDate = null;
	
	private String m_strMakeBuy = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strTCProject = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strProjectID = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strEngMakeBuy = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strOrgTemplate = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strPlanningCode = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strObjectString = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strStockMaterial = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strStockMaterialID = Constants.General.EMPTY_STRING_VALUE_C;
	private String m_strMasterTemplate = Constants.General.EMPTY_STRING_VALUE_C;
	
	private TreeMap<String, StockMaterialAttributesFormBean> m_treeStockMaterials = new TreeMap<String, StockMaterialAttributesFormBean>();
	
	private TCComponentItem m_tcStockMaterial = null;
	private TCComponentItem m_tcComponentItem = null;
	private TCComponentForm m_tcComponentForm = null;
	
	private TCComponentBOMLine m_tcComponentBOMLine = null;
	
	public void setModified(boolean p_isModified) {
		this.m_isModified = p_isModified;
	}
	
	public void setEngMakeBuySet(boolean p_isEngMakeBuySet) {
        this.m_isEngMakeBuySet = p_isEngMakeBuySet;
    }
	
	public void setLoadingIndex(int p_iLoadingIndex) {
		this.m_iLoadingIndex = p_iLoadingIndex;
	}
	
	public void setStructureCode(int p_iStructureCode) {
		this.m_iStructureCode = p_iStructureCode;
	}
	
	public void setStockMaterialQuantity(double p_dStockMaterialQuantity) {
		this.m_dStockMaterialQuantity = p_dStockMaterialQuantity;
	}
	
	public void setObjectString(String p_strObjectString) {
		this.m_strObjectString = p_strObjectString;
	}
	
	public void setMakeBuy(String p_strMakeBuy) {
		this.m_strMakeBuy = p_strMakeBuy;
	}
	
	public void setEngMakeBuy(String p_strEngMakeBuy) {
		this.m_strEngMakeBuy = p_strEngMakeBuy;
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
	
	public void setPlanningCode(String p_strPlanningCode) {
		this.m_strPlanningCode = p_strPlanningCode;
	}
	
	public void setOrgTemplate(String p_strOrgTemplate) {
		this.m_strOrgTemplate = p_strOrgTemplate;
	}
	
	public void setStockMaterial(String p_strStockMaterial) {
		this.m_strStockMaterial = p_strStockMaterial;
	}
	
	public void setStockMaterialID(String p_strStockMaterialID) {
		this.m_strStockMaterialID = p_strStockMaterialID;
	}
	
	public void setStockMaterialItem(TCComponentItem p_tcStockMaterial) {
		this.m_tcStockMaterial = p_tcStockMaterial;
	}
	
	public void setMasterTemplate(String p_strMasterTemplate) {
		this.m_strMasterTemplate = p_strMasterTemplate;
	}
	
	public void setItemPublishDate(Date p_itemPublishDate) {
		this.m_itemPublishDate = p_itemPublishDate;
	}
	
	public void setBOMPublishDate(Date p_BOMPublishDate) {
		this.m_BOMPublishDate = p_BOMPublishDate;
	}
	
	public void setStockMaterials(TreeMap<String, StockMaterialAttributesFormBean> p_arrStockMaterials) {
		this.m_treeStockMaterials = p_arrStockMaterials;
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
	
	public boolean getModified() {
		return this.m_isModified;
	}
	
	public boolean getEngMakeBuySet() {
        return this.m_isEngMakeBuySet;
    }
	
	public int getLoadingIndex() {
		return this.m_iLoadingIndex;
	}
	
	public int getStructureCode() {
		return this.m_iStructureCode;
	}
	
	public double getStockMaterialQuantity() {
		return this.m_dStockMaterialQuantity;
	}
	
	public String getObjectString() {
		return this.m_strObjectString;
	}
	
	public String getMakeBuy() {
		return this.m_strMakeBuy;
	}
	
	public String getEngMakeBuy() {
		return this.m_strEngMakeBuy;
	}
	
	public String getTCProject() {
		return this.m_strTCProject;
	}
	
	public String getTCProjectID() {
		return this.m_strProjectID;
	}
	
	public String getOrgTemplate() {
		return this.m_strOrgTemplate;
	}
	
	public String getPlanningCode() {
		return this.m_strPlanningCode;
	}
	
	public String getStockMaterial() {
		return this.m_strStockMaterial;
	}
	
	public String getStockMaterialID() {
		return this.m_strStockMaterialID;
	}
	
	public String getMasterTemplate() {
		return this.m_strMasterTemplate;
	}
	
	public Date getItemPublishDate() {
		return this.m_itemPublishDate;
	}
	
	public Date getBOMPublishDate() {
		return this.m_BOMPublishDate;
	}
	
	public TreeMap<String, StockMaterialAttributesFormBean> getStockMaterials() {
		return this.m_treeStockMaterials;
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
}