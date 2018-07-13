package com.get.ontrack.common;

import java.io.File;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.List; 

public class GETDesignReleaseCommonOperations {
	
	public GETDesignReleaseCommonOperations()
	{
		
	}
	
	
public  boolean isFileValid ( String fileName ){
		
		boolean isValid = false;
		File file = null;
		
		try {
			file = new File ( fileName );
			if ( null != file  ){
				if ( file.isFile() && file.exists() ){
					file.setWritable(true);
					isValid = true;
					System.out.println( "File Exist : " + fileName );
				} else {
					System.out.println( "ERROR : File Exist - " + fileName );
				}
			}
			
		} catch (Exception e) {
			// TODO: handle exception
		}
			
		return isValid;
	}

	
	public   String getDateCalculation ( Date date, int weeks, boolean isFriday) {
	    
		String reqDate = null;
	    try {
			Calendar currentDate = Calendar.getInstance();
			currentDate.setTime(date);
			
			Calendar newDate = Calendar.getInstance();
			newDate.setTimeInMillis(currentDate.getTimeInMillis());
			newDate.add(Calendar.WEEK_OF_YEAR, weeks);        
			
			SimpleDateFormat dateFormatter = new SimpleDateFormat("MM/dd/yyyy");

			
			if ( isFriday ) {
			    int dayofweek = newDate.get(Calendar.DAY_OF_WEEK);      
			    switch(dayofweek){
			    	case Calendar.SUNDAY:
			    		newDate.add(Calendar.DATE, 5);
			    		break;
			    	case Calendar.MONDAY:
			    		newDate.add(Calendar.DATE, 4);
			    		break;
			    	case Calendar.TUESDAY:
			    		newDate.add(Calendar.DATE, 3);
			    		break;
			    	case Calendar.WEDNESDAY:
			    		newDate.add(Calendar.DATE, 2);
			    		break;
			    	case Calendar.THURSDAY:
			    		newDate.add(Calendar.DATE, 1);
			    		break;
			    	case Calendar.SATURDAY:
			    		newDate.add(Calendar.DATE, -1);
			    		break;
			    }
			}
			
			Date requiredDate = newDate.getTime();
			reqDate = dateFormatter.format(requiredDate);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return reqDate;

	}
	
public   String getStartDate( Date dateP1, String backOff, String engrDuration){
		
		String startDate = null;
		int backoffNo = 0;
		int duration = 0;
		try {
			
			if ( backOff != null && backOff.length()>0 ){
				if ( backOff.endsWith("w") || backOff.endsWith("W")){
					backOff = backOff.substring(0, backOff.length()-1);
				}
				backoffNo = Integer.parseInt(backOff);
			} else {
				return "";
			}
			
			if ( engrDuration != null && engrDuration.length()>0 ){
				if ( engrDuration.endsWith("w") || engrDuration.endsWith("W")){
					engrDuration = engrDuration.substring(0, engrDuration.length()-1);
				}
				duration = Integer.parseInt(engrDuration);
			} else {
				return "";
			}

			int engrDur = (backoffNo + duration ) * (-1);
			startDate = getDateCalculation(dateP1, engrDur, false);

		} catch (NumberFormatException e) {
			e.printStackTrace();
		}										

		return startDate;
	}
	
	public   String getEngrRequiredtDate( Date dateP1, String backOff){
		
		String requiredDate = null;
		int backoffNo = 0;
		try {
			
			if ( backOff != null && backOff.length()>0 ){
				if ( backOff.endsWith("w") || backOff.endsWith("W")){
					backOff = backOff.substring(0, backOff.length()-1);
				}
				backoffNo = Integer.parseInt(backOff);
			} else {
				return "";
			}
			
			backoffNo *= (-1);
			requiredDate = getDateCalculation(dateP1, backoffNo, false);
			
		} catch (NumberFormatException e) {
			e.printStackTrace();
		}										

		return requiredDate;
	}
	
	public   String getDesignRequiredtDate( Date dateP1, String backOff, String designDuration){
		
		String requiredDate = null;
		int backoffNo = 0;
		int duration = 0;
		
		try {
			
			if ( backOff != null && backOff.length()>0 ){
				if ( backOff.endsWith("w") || backOff.endsWith("W")){
					backOff = backOff.substring(0, backOff.length()-1);
				}
				backoffNo = Integer.parseInt(backOff);
			} else {
				return "";
			}
			
			if ( designDuration != null && designDuration.length()>0 ){
				if ( designDuration.endsWith("w") || designDuration.endsWith("W")){
					designDuration = designDuration.substring(0, designDuration.length()-1);
				}
				duration = Integer.parseInt(designDuration);
			} else {
				return "";
			}

			int designDur = (backoffNo - duration ) * (-1);
			requiredDate = getDateCalculation(dateP1, designDur, false );
			
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return requiredDate;
	}
	
	public String getColorCode( String reqdDate){
		
		String colorCode = "";
		int iRqdDate = 0;
		int iTodayDate = 0;
		int reqdDateYear = 0;
		int todayDateYear = 0;
		int fwFactor = 0;
		Calendar dateCal = null;
		DateFormat sdf = null;
		Date dateFW = null;
		String reqdDateFW = null;
		
		//Get Year
		
		try {
			
			//Required Date Year
			dateCal = Calendar.getInstance();
			if ( reqdDate != null && reqdDate.length() > 0 ){
				sdf = new SimpleDateFormat("MM/dd/yyyy");
				dateFW =  sdf.parse(reqdDate);
				dateCal.setTime(dateFW);
				reqdDateYear = dateCal.get(Calendar.YEAR);
			}
			
			//Current Year
			todayDateYear = Calendar.getInstance().get(Calendar.YEAR);
			
			//Fiscal Week Factor
			if ( (reqdDateYear - todayDateYear) > 0 ){
				fwFactor = (reqdDateYear - todayDateYear ) * 52;
			}
			
		
			//Required Date FW
			reqdDateFW = getFW(reqdDate);
			if ( reqdDateFW != null && reqdDateFW.length()>0 ){
				if ( reqdDateFW.startsWith("w") || reqdDateFW.startsWith("W")){
					reqdDateFW = reqdDateFW.substring(1, reqdDateFW.length());
				}
				iRqdDate = Integer.parseInt(reqdDateFW) + fwFactor;
			}
			
			//Today Date Date FW
			DateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
			String todayDate = dateFormat.format(new Date());
			
			todayDate = getFW(todayDate);
			if ( todayDate.startsWith("w") || todayDate.startsWith("W")){
				todayDate = todayDate.substring(1, todayDate.length());
			}
			iTodayDate = Integer.parseInt(todayDate);
			
			if ( iRqdDate == iTodayDate ){
				colorCode = GETDesignReleaseConstants.ColorCode.strYellow;
			} else if ( iRqdDate > iTodayDate ) {
				if ( iRqdDate - iTodayDate == 1 ){
					colorCode = GETDesignReleaseConstants.ColorCode.strBlue;
				}  	else if ( iRqdDate - iTodayDate > 2 ){
					colorCode = GETDesignReleaseConstants.ColorCode.strWhite;
				}
			} else {
				colorCode = GETDesignReleaseConstants.ColorCode.strRed;
			}
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
				
//		if ( iRqdDate - iTodayDate > 2 ){
//			colorCode = GETDesignReleaseConstants.ColorCode.strWhite;
//		} else if ( iTodayDate - iRqdDate >= 1 ){
//			colorCode = GETDesignReleaseConstants.ColorCode.strRed;
//		} else if ( iTodayDate - iRqdDate == 0 ){
//			colorCode = GETDesignReleaseConstants.ColorCode.strYellow;
//		} else if ( iRqdDate - iTodayDate == 1 ){
//			colorCode = GETDesignReleaseConstants.ColorCode.strBlue;
//		} 
		//System.out.println("Color Code : " + colorCode); 		 
		return colorCode;
	}
	
	public String getFW ( String setDate) {
		String fiscalWeek = null;
		DateFormat sdf = null;
		Date dateFW = null;
		try {
			
			if ( setDate != null && setDate.length() > 0 ){
				sdf = new SimpleDateFormat("MM/dd/yyyy");
				dateFW =  sdf.parse(setDate);
				if ( dateFW == null ){
					return "";
				}
			} else {
				return "";
			}

			Calendar setDateCal = Calendar.getInstance();
			setDateCal.setTime(dateFW);
			int fwYear = setDateCal.get(Calendar.YEAR);

			Calendar cal = Calendar.getInstance();
			cal.set( Calendar.YEAR, fwYear );
			cal.set( Calendar.MONTH , Calendar.JANUARY);
			cal.set( Calendar.DAY_OF_MONTH, 0 );
			
  
			int mondaysCount = 0;

			while ( mondaysCount != 1 ) {
				cal.add( Calendar.DAY_OF_MONTH, 1 );
				if ( cal.get( Calendar.DAY_OF_WEEK ) == Calendar.MONDAY ) {
					mondaysCount++; 
				}
			}
			
			Date date = cal.getTime();
			Calendar calendarStart = Calendar.getInstance();
			calendarStart.setTime(date);
			
			Calendar calendarFW = Calendar.getInstance();
			calendarFW.setTime(dateFW);

			int weekNo = weekOf(calendarStart, calendarFW);
			fiscalWeek = "W"+String.valueOf(weekNo);
//			System.out.println("FW : " + reqDate);
			
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return fiscalWeek;

	}
	
	public   int weekOf(Calendar yearStart, Calendar date) {
		
		final int LENGTH_OF_WEEK = 7 * 24 * 60 * 60 * 1000;
	    int weeksElapsed = 0;
		try {
			long millisElapsed = date.getTimeInMillis() - yearStart.getTimeInMillis();
			weeksElapsed = (int) (millisElapsed / LENGTH_OF_WEEK);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    
	    return weeksElapsed + 1;
	}
	
	public  int[] getIntArray(List<Integer> integers) throws Exception {
	    int[] ints = new int[integers.size()];
	    int i = 0;
	    for (Integer n : integers) {
	        ints[i++] = n;
	    }
	    return ints;
	}



}
