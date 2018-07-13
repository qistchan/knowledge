package com.ge.get6DrgIDFromPartlist;

public class Get6DrgIDFromPartlist
{
    
    /**STARTFUNCDOC *
    ===========================================================================
     * Method to get root Item ID from Item ID taken as input
     * 
     * @param inputItemID - InputItemID in string 
     * @return File - Returns Folder/File to be used to keep Fetched dataset  /**
     * Method to get root number of given item ID.
     *
     * @param partsListID - Item Id whose root number is to be retrieved
     * @return the drg id from part list             
     ===========================================================================    
    ENDFUNCDOC   **/
    public static String getDrgIDFromPartList(String inputItemID)
    {
        String dwgRoot = inputItemID;
        String tem_part_num = "";  
        try
        {
            if  ( dwgRoot.substring(0, 1).equals("T") || (dwgRoot.substring(0, 1).equals("D") || ( dwgRoot.substring(0, 1).equals("F") )) )
            {
                System.out.println("\nDwgroot is "+ dwgRoot);
                return dwgRoot;
            }
            
             dwgRoot = dwgRoot.replace("-", ""); 
             dwgRoot = dwgRoot.replaceAll("\\s+", "");

            //item length is less than 6
            if ( dwgRoot.length() < 6 )
            {
                return dwgRoot;
            }
            else
            {
                //check items start with P like p103c020
                if ( dwgRoot.substring(0, 1).equals("P") )
                {
                    int i = 1;
                    boolean flag = false;
                    while ( i <= dwgRoot.length() )
                    {
                        if ( !dwgRoot.substring(i, i+1).matches("[a-zA-Z0-9]") )
                        {
                            flag = true;
                            break;
                        }
                        i++;
                    }
                    if ( flag )
                    {
                        i = 1;
                        while( i <= dwgRoot.length() )
                        {
                            if ( dwgRoot.substring(i, i+1).matches("[a-zA-Z0-9]") ) 
                            {
                                tem_part_num += dwgRoot.substring(i, i + 1); 
                            }
                                    i++;
                        }
                        return tem_part_num;
                    }
                }
        
                if ( dwgRoot.substring(0, 2).equals("15") ) 
                {
                    dwgRoot = dwgRoot.substring( 0,8 );
                    
                    return dwgRoot;
                }
                
                //a50/e19/3
                if ( dwgRoot.indexOf("A50E") != -1 || dwgRoot.indexOf("B50E") != -1 || dwgRoot.indexOf("C50E")  != -1 || dwgRoot.indexOf("D50E")  != -1 || dwgRoot.indexOf("F50E")  != -1)
                {               
                    if (dwgRoot.substring(4, 4+1).matches("[0-9]") && dwgRoot.substring(5, 5+1).matches("[0-9]") && dwgRoot.substring(6, 6+1).matches("[0-9]"))
                    {
                        return dwgRoot.substring(0, 7);
                    }
                   
                    if (dwgRoot.substring(4, 4+1).matches("[0-9]") && dwgRoot.substring(5, 5+1).matches("[0-9]"))
                    {
                        return dwgRoot.substring(0, 6);
                    }
    
                    //a50/e2              
                    if (dwgRoot.substring(4, 4+1).matches("[0-9]"))
                    {
                        return dwgRoot.substring(0, 5);
                    }
                }
    
                //starting with "17" having 3 alphabet following
               
                if ( dwgRoot.substring(0, 2).equals("17") && dwgRoot.substring(2, 2+1).matches("[a-zA-Z]") &&
                        dwgRoot.substring(3, 3+1).matches("[a-zA-Z]") && dwgRoot.substring(4, 4+1).matches("[0-9]") &&
                        dwgRoot.substring(5, 5+1).matches("[0-9]") && dwgRoot.substring(6, 6+1).matches("[0-9]") &&
                        dwgRoot.substring(7, 7+1).matches("[0-9]") )
                {
                    return dwgRoot.substring(0, 8);
                }
               
                if ( dwgRoot.substring(0, 2).equals("17") && dwgRoot.substring(2, 2+1).matches("[a-z,A-Z]") &&
                        dwgRoot.substring(3, 3+1).matches("[a-zA-Z]") && dwgRoot.substring(4, 4+1).matches("[a-zA-Z]") &&
                        dwgRoot.substring(5, 5+1).matches("[0-9]") && dwgRoot.substring(6, 6+1).matches("[0-9]") &&
                        dwgRoot.substring(7, 7+1).matches("[0-9]") )
                {
                    return dwgRoot.substring(0, 8);
                }
    
                //17a/f20/b
                if ( dwgRoot.substring(0, 2).equals("17") && dwgRoot.substring(2, 2+1).matches("[a-zA-Z]") &&
                        dwgRoot.substring(3, 3+1).matches("[a-zA-Z]") && dwgRoot.substring(4, 4+1).matches("[0-9]") &&
                        dwgRoot.substring(5, 5+1).matches("[0-9]") && dwgRoot.substring(6, 6+1).matches("[0-9]") )
                {
                    return dwgRoot.substring(0, 7);
                }
    
                if ( dwgRoot.substring(0, 2).equals("17") && dwgRoot.substring(2, 2+1).matches("[a-zA-Z]") &&
                        dwgRoot.substring(3, 3+1).matches("[a-zA-Z]") && dwgRoot.substring(4, 4+1).matches("[0-9]") &&
                        dwgRoot.substring(5, 5+1).matches("[0-9]") )
                {
                    return dwgRoot.substring(0, 6);
                }
              
                //17a/d1
                if ( dwgRoot.substring(0, 2).equals("17") && dwgRoot.substring(2, 2+1).matches("[a-zA-Z]") &&
                        dwgRoot.substring(3, 3+1).matches("[a-zA-Z]") && dwgRoot.substring(4, 4+1).matches("[0-9]") )
                {
                    return dwgRoot.substring(0, 5);
                }          
                
                if ( dwgRoot.substring(0, 1).equals("B") )
                {
                    return "";
                }
    
               //check for P1 or G1 at the end of the rootID
                if ( dwgRoot.indexOf("P") != -1 || dwgRoot.indexOf("G") != -1 || dwgRoot.indexOf(".") != -1 || dwgRoot.indexOf("H") != -1 )
                {
                    int tem_index = 0;
                    boolean flg = false;
                    String reversedTemp =  new StringBuffer(dwgRoot).reverse().toString();
                    int tempStrLength = dwgRoot.length();                  
    
                    int pIndex = reversedTemp.indexOf("P");
                
                    int gIndex = reversedTemp.indexOf("G");
                    
                    int hIndex = reversedTemp.indexOf ( "H" );                  
                                        
                    //# The next to the last character is either "P" or "G"  AND AND H
                    //# The last character is a letter of the alphabet and NOT  a number then it should not be stripped off.                   
                    String tmpChar = dwgRoot.substring(tempStrLength - 2, tempStrLength - 1);
                       
                    if( tmpChar.equalsIgnoreCase("P") || tmpChar.equalsIgnoreCase("G") || tmpChar.equalsIgnoreCase("H") )
                    {
                        if ( tmpChar.equalsIgnoreCase("G") )
                        {                                  
                            if ( !(dwgRoot.substring(tempStrLength - 3, tempStrLength - 2)).equalsIgnoreCase("P") )
                            {
                                tmpChar = "";
                                tmpChar = dwgRoot.substring((tempStrLength - 1), tempStrLength);
                              
                                if ( tmpChar.matches("[^0-9]") )
                                {
                                    return dwgRoot;                                
                                }
                            }
                        }
                        else
                        {
                            tmpChar = "";
                            tmpChar = dwgRoot.substring((tempStrLength - 1), tempStrLength);
                          
                            // // If the part number is 84A123456PS  then return it 84A123456PS only or 84A123456HT items
                            if (tmpChar.matches("[^0-9]"))
                            {
                                return dwgRoot;
                            }
                        }
                    }
                    
                    //84E902393AGH1
                    if ( ( hIndex > 0 ) && ( hIndex < gIndex  ) )
                    { 
                        tem_index = gIndex;
                        dwgRoot = dwgRoot.substring( 0, ( dwgRoot.length() - tem_index ));
                        return dwgRoot;
                    }
                    //84E902393APH1
                    if ( ( hIndex > 0 ) && ( hIndex < pIndex  ) )
                    {
                        tem_index = pIndex;
                        dwgRoot = dwgRoot.substring( 0, ( dwgRoot.length() - tem_index ));
                        return dwgRoot;
                    }
    
                    // Check whether the drawing contain both G and P characters.
                    // If Group number exist for a drawing e.g. 84A111405PG2   trim only G2.
                    if ( (gIndex > 0) && (gIndex < pIndex ) )
                    {
                        pIndex = -1;
                    }
                    if ( pIndex != -1 )
                    {
                        tem_index = pIndex;
                        flg = true;
                    }
    
                    if ( !flg )
                    {    
                        pIndex = reversedTemp.indexOf("G");
                        if ( pIndex != -1 )
                        {
                            if ( !flg )
                            {
                                tem_index = pIndex;
                                flg = true;
                            }
                            else if ( pIndex < tem_index )
                            {
                                tem_index = pIndex;
                            }
                        }
    
                        if ( !flg )
                        {                           
                            pIndex = reversedTemp.indexOf("H");
                            if ( pIndex != -1 )
                            {
                                if ( !flg )
                                {
                                    tem_index = pIndex;
                                    flg = true;
                                }
                                else if ( pIndex < tem_index )
                                {
                                    tem_index = pIndex;
                                }
                            }
    
                            if ( !flg )
                            {
                                pIndex = reversedTemp.indexOf(".");
                                if ( pIndex != -1 )
                                {
                                    if ( !flg )
                                    {
                                        tem_index = pIndex;
                                        flg = true;
                                    }
                                    else if ( pIndex < tem_index )
                                    {
                                        tem_index = pIndex;
                                    }
                                }
                            }
                        }
                    }
                                 
                    // If the part number is 84A123456G  then return it 84A123456G only.
                    if ( (tem_index == 0) && dwgRoot.matches(".*[G]$") )
                    {
                        return dwgRoot;
                    }
    
                    // If the part number is like 84A213385CH  then return 84A213385CH only.
                    if ( (tem_index == 0) && ( dwgRoot.matches(".*[H]$") ) )
                    {
                        return dwgRoot;
                    }
                   
                    // if the part number is like 41C666376AP  then return 41C666376AP  only. 
                    if ( (tem_index == 0) && (dwgRoot.matches(".*[P]$")) )
                    {
                        return dwgRoot;
                    }
                    return dwgRoot.substring( 0, (dwgRoot.length() - 1) - tem_index );
                }
            }
            return dwgRoot;
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }
    return dwgRoot;
    }
}
