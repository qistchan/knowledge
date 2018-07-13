package com.ge.get6UGEXPDF;

import com.teamcenter.ets.soa.SoaHelper;
import com.teamcenter.soa.client.model.Type;
import com.teamcenter.soa.client.model.strong.ItemRevision;
import com.teamcenter.tstk.util.log.ITaskLogger;

public class PreferenceManager
{
  private String TOP_CLASS_FOR_PREFERENCE = "ItemRevision";
  private ITaskLogger m_zTaskLogger;
  
  public PreferenceManager(ITaskLogger m_zTaskLogger) {
    this.m_zTaskLogger = m_zTaskLogger;
  }

  public String[] getObjTypePreferenceValue(ItemRevision itemRev, String prefix, String suffix)
  {
    String[] prefVal = null;
    Type itemRevType = itemRev.getTypeObject();
    prefVal = getObjectClassPreferenceValue(itemRevType, prefix, suffix);
    return prefVal;
  }

  private String[] getObjectClassPreferenceValue(Type itemRevType, String prefix, String suffix)
  {
    String[] prefVal = null;
    
    String preName = prefix + itemRevType.getName().toUpperCase() + suffix;
    try {
      prefVal = SoaHelper.getPreference(preName);
    } catch (Exception e) {
      e.printStackTrace();
    }
    
    if (prefVal == null) {
      this.m_zTaskLogger.debug("No preference for : " + preName);
      if (!itemRevType.getName().equals(this.TOP_CLASS_FOR_PREFERENCE)) {
        prefVal = getObjectClassPreferenceValue(
          itemRevType.getParent(), prefix, suffix);
      }
    } else {
      this.m_zTaskLogger.debug("Preference " + preName + ":");
      String[] arrayOfString1; int j = (arrayOfString1 = prefVal).length; for (int i = 0; i < j; i++) { String pref = arrayOfString1[i];
        this.m_zTaskLogger.debug(pref);
      }
    }
    return prefVal;
  }
}