package war.src.com.get.tc.Restservice;

import java.util.List;

import com.fasterxml.jackson.annotation.JsonProperty;

public class CreateUser

{
	@JsonProperty
	
	private String userID;
	private String firstName;
	private String lastName;
	private String email;
	private boolean activeStatus = true;
	public boolean isActiveStatus() {
		return activeStatus;
	}
	public void setActiveStatus(boolean activeStatus) {
		this.activeStatus = activeStatus;
	}
	private List<String> groupDetails;
	private String groupRoles;
  public String getGroupRoles() {
		return groupRoles;
	}
	public void setGroupRoles(String groupRoles) {
		this.groupRoles = groupRoles;
	}
	//  private String grp;
  //  private String subGrp1;
  //  private String subGrp2;
  //  private List<String> grpRole;
  //  private String ipClr;
    private String country;
	public String getUserID() {
		return userID;
	}
	public void setUserID(String userID) {
		this.userID = userID;
	}
	public String getFirstName() {
		return firstName;
	}
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}
	public String getLastName() {
		return lastName;
	}
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	
	public List<String> getGroupDetails() {
		return groupDetails;
	}
	public void setGroupDetails(List<String> groupDetails) {
		this.groupDetails = groupDetails;
	}
	public String getCountry() {
		return country;
	}
	public void setCountry(String country) {
		this.country = country;
	}
 }