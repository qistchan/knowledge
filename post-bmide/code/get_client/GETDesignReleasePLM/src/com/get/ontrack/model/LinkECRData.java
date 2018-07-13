package com.get.ontrack.model;

public class LinkECRData implements java.io.Serializable{

	private static final long serialVersionUID = 1L;
	private String bomLineItemId;
	private String description;
	private String designReleaseId = "";
	public LinkECRData() {
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
}
