package com.get.ontrack.model;

import java.util.ArrayList;

public class DesignReleaseWrapper implements java.io.Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private ArrayList<DesignRelease> designReleaseList = new ArrayList<DesignRelease>();
	private String checkedTemplates = "";
	private String existingCheckedTemplates = "";
	private String projectId;
	
	public ArrayList<DesignRelease> getDesignReleaseList() {
		return designReleaseList;
	}
	public void setDesignReleaseList(ArrayList<DesignRelease> designReleaseList) {
		this.designReleaseList = designReleaseList;
	}
	public String getCheckedTemplates() {
		return checkedTemplates;
	}
	public void setCheckedTemplates(String checkedTemplates) {
		this.checkedTemplates = checkedTemplates;
	}
	public String getExistingCheckedTemplates() {
		return existingCheckedTemplates;
	}
	public void setExistingCheckedTemplates(String existingCheckedTemplates) {
		this.existingCheckedTemplates = existingCheckedTemplates;
	}
	public String getProjectId() {
		return projectId;
	}
	public void setProjectId(String projectId) {
		this.projectId = projectId;
	}
}
