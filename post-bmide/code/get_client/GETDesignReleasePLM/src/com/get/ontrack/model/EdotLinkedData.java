package com.get.ontrack.model;

public class EdotLinkedData  implements java.io.Serializable { 
	private static final long serialVersionUID = 1L;
	private String edotId ;
	private String ecnId ;
	private String techData  = "";
	public EdotLinkedData() {
		super();
	}
	public String getEdotId() {
		return edotId;
	}
	public void setEdotId(String edotId) {
		this.edotId = edotId;
	}
	public String getEcnId() {
		return ecnId;
	}
	public void setEcnId(String ecnId) {
		this.ecnId = ecnId;
	}
	public String getTechData() {
		return techData;
	}
	public void setTechData(String techData) {
		this.techData = techData;
	}



}
