
package com.teamcenter.getrans;

import java.util.Comparator;

import com.teamcenter.soa.client.model.ModelObject;
import com.teamcenter.soa.client.model.PropertyDescription;

/**
 * Class for sorting Model Objects based on given attribute
 * 
 * @author TCSL
 */
public class GETModelObjectSorter implements Comparator<ModelObject>
{
    private String attrName;

    /**
     * Constructor for the Class GETModelObjectSorter
     * 
     * @param attrName - Attribute name based on which sorting should be done
     */
    public GETModelObjectSorter(String attrName)
    {
        this.attrName = attrName;
    }

    /**
     * Method overriding Comparator method to return comparison result of
     * 
     * @param mo1 - Model Object 1
     * @param mo2 - Model Object 2
     * @return - Result of comparison
     */
    public int compare(ModelObject mo1, ModelObject mo2)
    {
        int compareResult = 0;

        try
        {
            int propType = mo1.getPropertyObject(attrName).getPropertyDescription().getType();

            switch(propType)
            {
                case PropertyDescription.CLIENT_PROP_TYPE_bool:
                    compareResult = Boolean.valueOf(mo1.getPropertyObject(attrName).getBoolValue()).compareTo(Boolean.valueOf(mo2.getPropertyObject(attrName).getBoolValue()));
                    break;
                case PropertyDescription.CLIENT_PROP_TYPE_char:
                    compareResult = mo1.getPropertyObject(attrName).getCharValue() < mo2.getPropertyObject(attrName).getCharValue()? -1 : 
                    mo1.getPropertyObject(attrName).getCharValue() > mo2.getPropertyObject(attrName).getCharValue()? 1 : 0;
                    break;
                case PropertyDescription.CLIENT_PROP_TYPE_date:
                    compareResult = mo1.getPropertyObject(attrName).getCalendarValue().compareTo(mo2.getPropertyObject(attrName).getCalendarValue());
                    break;
                case PropertyDescription.CLIENT_PROP_TYPE_double:
                    compareResult = mo1.getPropertyObject(attrName).getDoubleValue() < mo2.getPropertyObject(attrName).getDoubleValue()? -1 : 
                    mo1.getPropertyObject(attrName).getDoubleValue() > mo2.getPropertyObject(attrName).getDoubleValue()? 1 : 0;
                    break;
                case PropertyDescription.CLIENT_PROP_TYPE_float:
                    compareResult = mo1.getPropertyObject(attrName).getFloatValueAsDouble() < mo2.getPropertyObject(attrName).getFloatValueAsDouble() ? -1 : 
                    mo1.getPropertyObject(attrName).getFloatValueAsDouble() > mo2.getPropertyObject(attrName).getFloatValueAsDouble()? 1 : 0;
                    break;
                case PropertyDescription.CLIENT_PROP_TYPE_int:
                    compareResult = mo1.getPropertyObject(attrName).getIntValue() < mo2.getPropertyObject(attrName).getIntValue() ? -1 : 
                    mo1.getPropertyObject(attrName).getIntValue() > mo2.getPropertyObject(attrName).getIntValue()? 1 : 0;
                    break;
                case PropertyDescription.CLIENT_PROP_TYPE_short:
                    compareResult = mo1.getPropertyObject(attrName).getShortValue() < mo2.getPropertyObject(attrName).getShortValue() ? -1 : 
                    mo1.getPropertyObject(attrName).getShortValue() > mo2.getPropertyObject(attrName).getShortValue()? 1 : 0;
                    break;
                case PropertyDescription.CLIENT_PROP_TYPE_string:
                    compareResult = mo1.getPropertyObject(attrName).getStringValue().compareTo(mo2.getPropertyObject(attrName).getStringValue());
                    break;
                default:
                    compareResult = 0;
                    break;
            }
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }

        return compareResult;
    }
}
