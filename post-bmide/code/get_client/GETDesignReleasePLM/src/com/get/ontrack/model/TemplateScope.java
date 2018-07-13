package com.get.ontrack.model;

import java.util.ArrayList;
import java.util.List;

public class TemplateScope {
	
	private String id;

	private String text;
	
	private String state;
	
	private List<Children> children = new ArrayList<>();

	public TemplateScope() {
		super();
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getText() {
		return text;
	}

	public void setText(String text) {
		this.text = text;
	}

	public String getState() {
		return state;
	}

	public void setState(String state) {
		this.state = state;
	}

	public List<Children> getChildren() {
		return children;
	}

	public void setChildren(List<Children> children) {
		this.children = children;
	}
	
	
}
