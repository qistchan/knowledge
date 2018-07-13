package com.get.ontrack.model;

import java.util.Date;
import java.util.List;

public class DesignRelease implements java.io.Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String bomLineItemId;
	private String designReleaseId = "";
	private String description;
	private String engrStartDate;
	private String engrRequiredDate;
	private String designRequiredDate;
	private String engrStartDateLabel;
	private String engrRequiredDateLabel;
	private String designRequiredDateLabel;
	private String engrComponentNo;
	private String designComponentNo;
	private String backOff;
	private String engrDuration;
	private String designDuration;
	private String templateName;
	private String indexId;
	private String projectId;
	public String edot = "";
	public String status = "";
	public String state = "";
	public String mainGroup = "";
	private String engrOrgProject = "";
	private String designOrgProject = ""; 

	private Date dP1date;
	private String engrActualDate = "";
	private String engrPromiseDate = "";
	private String engrActualDateLabel = "";
	private String engrPromiseDateLabel = "";
	private String engrDateChangeReason = "";
	private String engrResource = "";
	private String engrECR = "";
	private String engrComment="";
	private String designPromiseDate = "";
	private String designActualDate = "";
	private String designPromiseDateLabel = "";
	private String designActualDateLabel = "";
	private String designDateChangeReason = "";
	private String designResource = "";
	private String technicalData = "";
	private String designECN = "";
	private String designComment="";
	private boolean autoClose = false;
	private boolean editChecked = false;
	
	public DesignRelease() {
		super();
	}

	public String getBomLineItemId() {
		return bomLineItemId;
	}

	public void setBomLineItemId(String bomLineItemId) {
		this.bomLineItemId = bomLineItemId;
	}

	public String getDesignReleaseId() {
		return designReleaseId;
	}

	public void setDesignReleaseId(String designReleaseId) {
		this.designReleaseId = designReleaseId;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getEngrStartDate() {
		return engrStartDate;
	}

	public void setEngrStartDate(String engrStartDate) {
		this.engrStartDate = engrStartDate;
	}

	public String getEngrRequiredDate() {
		return engrRequiredDate;
	}

	public void setEngrRequiredDate(String engrRequiredDate) {
		this.engrRequiredDate = engrRequiredDate;
	}

	public String getDesignRequiredDate() {
		return designRequiredDate;
	}

	public void setDesignRequiredDate(String designRequiredDate) {
		this.designRequiredDate = designRequiredDate;
	}

	public String getEngrStartDateLabel() {
		return engrStartDateLabel;
	}

	public void setEngrStartDateLabel(String engrStartDateLabel) {
		this.engrStartDateLabel = engrStartDateLabel;
	}

	public String getEngrRequiredDateLabel() {
		return engrRequiredDateLabel;
	}

	public void setEngrRequiredDateLabel(String engrRequiredDateLabel) {
		this.engrRequiredDateLabel = engrRequiredDateLabel;
	}

	public String getDesignRequiredDateLabel() {
		return designRequiredDateLabel;
	}

	public void setDesignRequiredDateLabel(String designRequiredDateLabel) {
		this.designRequiredDateLabel = designRequiredDateLabel;
	}

	public String getEngrComponentNo() {
		return engrComponentNo;
	}

	public void setEngrComponentNo(String engrComponentNo) {
		this.engrComponentNo = engrComponentNo;
	}

	public String getDesignComponentNo() {
		return designComponentNo;
	}

	public void setDesignComponentNo(String designComponentNo) {
		this.designComponentNo = designComponentNo;
	}

	public String getBackOff() {
		return backOff;
	}

	public void setBackOff(String backOff) {
		this.backOff = backOff;
	}

	public String getEngrDuration() {
		return engrDuration;
	}

	public void setEngrDuration(String engrDuration) {
		this.engrDuration = engrDuration;
	}

	public String getDesignDuration() {
		return designDuration;
	}

	public void setDesignDuration(String designDuration) {
		this.designDuration = designDuration;
	}

	public String getTemplateName() {
		return templateName;
	}

	public void setTemplateName(String templateName) {
		this.templateName = templateName;
	}

	public String getIndexId() {
		return indexId;
	}

	public void setIndexId(String indexId) {
		this.indexId = indexId;
	}

	public String getProjectId() {
		return projectId;
	}

	public void setProjectId(String projectId) {
		this.projectId = projectId;
	}

	public String getEdot() {
		return edot;
	}

	public void setEdot(String edot) {
		this.edot = edot;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}
	
	public String getState() {
		return state;
	}

	public void setState(String state) {
		this.state = state;
	}

	public Date getdP1date() {
		return dP1date;
	}

	public void setdP1date(Date dP1date) {
		this.dP1date = dP1date;
	}

	public String getEngrActualDate() {
		return engrActualDate;
	}

	public void setEngrActualDate(String engrActualDate) {
		this.engrActualDate = engrActualDate;
	}

	public String getEngrPromiseDate() {
		return engrPromiseDate;
	}

	public void setEngrPromiseDate(String engrPromiseDate) {
		this.engrPromiseDate = engrPromiseDate;
	}

	public String getEngrActualDateLabel() {
		return engrActualDateLabel;
	}

	public void setEngrActualDateLabel(String engrActualDateLabel) {
		this.engrActualDateLabel = engrActualDateLabel;
	}

	public String getEngrPromiseDateLabel() {
		return engrPromiseDateLabel;
	}

	public void setEngrPromiseDateLabel(String engrPromiseDateLabel) {
		this.engrPromiseDateLabel = engrPromiseDateLabel;
	}

	public String getEngrDateChangeReason() {
		return engrDateChangeReason;
	}

	public void setEngrDateChangeReason(String engrDateChangeReason) {
		this.engrDateChangeReason = engrDateChangeReason;
	}

	public String getEngrResource() {
		return engrResource;
	}

	public void setEngrResource(String engrResource) {
		this.engrResource = engrResource;
	}

	public String getEngrECR() {
		return engrECR;
	}

	public void setEngrECR(String engrECR) {
		this.engrECR = engrECR;
	}

	public String getEngrComment() {
		return  engrComment;
	}

	public void setEngrComment(String engrComment) {
		this.engrComment = engrComment;
	}

	public String getDesignPromiseDate() {
		return designPromiseDate;
	}

	public void setDesignPromiseDate(String designPromiseDate) {
		this.designPromiseDate = designPromiseDate;
	}

	public String getDesignActualDate() {
		return designActualDate;
	}

	public void setDesignActualDate(String designActualDate) {
		this.designActualDate = designActualDate;
	}

	public String getDesignPromiseDateLabel() {
		return designPromiseDateLabel;
	}

	public void setDesignPromiseDateLabel(String designPromiseDateLabel) {
		this.designPromiseDateLabel = designPromiseDateLabel;
	}

	public String getDesignActualDateLabel() {
		return designActualDateLabel;
	}

	public void setDesignActualDateLabel(String designActualDateLabel) {
		this.designActualDateLabel = designActualDateLabel;
	}

	public String getDesignDateChangeReason() {
		return designDateChangeReason;
	}

	public void setDesignDateChangeReason(String designDateChangeReason) {
		this.designDateChangeReason = designDateChangeReason;
	}

	public String getDesignResource() {
		return designResource;
	}

	public void setDesignResource(String designResource) {
		this.designResource = designResource;
	}

	public String getDesignECN() {
		return designECN;
	}
	
	public String getMainGroup() {
		return mainGroup;
	}

	public void setMainGroup(String mainGroup) {
		this.mainGroup = mainGroup;
	}

	public String getEngrOrgProject() {
		return engrOrgProject;
	}

	public void setEngrOrgProject(String engrOrgProject) {
		this.engrOrgProject = engrOrgProject;
	}

	public String getDesignOrgProject() {
		return designOrgProject;
	}

	public void setDesignOrgProject(String designOrgProject) {
		this.designOrgProject = designOrgProject;
	}

	public void setDesignECN(String designECN) {
		this.designECN = designECN;
	}

	public String getDesignComment() {
		return designComment;
	}

	public void setDesignComment(String designComment) {
		this.designComment = designComment;
	}

	public boolean getAutoClose() {
		return autoClose;
	}

	public void setAutoClose(boolean autoClose) {
		this.autoClose = autoClose;
	}

	public boolean isEditChecked() {
		return editChecked;
	}

	public void setEditChecked(boolean editChecked) {
		this.editChecked = editChecked;
	}

	public String getTechnicalData() {
		return technicalData;
	}

	public void setTechnicalData(String technicalData) {
		this.technicalData = technicalData;
	}

}
