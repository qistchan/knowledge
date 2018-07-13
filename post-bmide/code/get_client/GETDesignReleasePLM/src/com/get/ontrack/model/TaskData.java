package com.get.ontrack.model;

public class TaskData implements java.io.Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String activityId;
	private String description;
	private String engrComponentNo;
	private String designComponentNo;
	private String engrOrgProject;


	private String designOrgProject;
	private String backOff;
	private String engrDuration;
	private String designDuration;
	private String engrResource;
	private String designResource;
	public String getEngrResource() {
		return engrResource;
	}


	public void setEngrResource(String engrResource) {
		this.engrResource = engrResource;
	}


	public String getDesignResource() {
		return designResource;
	}


	public void setDesignResource(String designResource) {
		this.designResource = designResource;
	}


	private boolean exist = false;
	private boolean isChecked = false;
	
	public TaskData() {
		super();
	}


	public String getActivityId() {
		return activityId;
	}


	public void setActivityId(String activityId) {
		this.activityId = activityId;
	}


	public String getDescription() {
		return description;
	}


	public void setDescription(String description) {
		this.description = description;
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


	public boolean isExist() {
		return exist;
	}


	public void setExist(boolean exist) {
		this.exist = exist;
	}


	public boolean isChecked() {
		return isChecked;
	}


	public void setChecked(boolean isChecked) {
		this.isChecked = isChecked;
	}
	
}
