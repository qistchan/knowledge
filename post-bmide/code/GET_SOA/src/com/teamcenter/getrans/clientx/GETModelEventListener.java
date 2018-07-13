
//==================================================
//
//  Copyright 2015 GE Transportation All Rights Reserved.
//
//==================================================

package com.teamcenter.getrans.clientx;

import com.teamcenter.soa.client.model.ModelEventListener;
import com.teamcenter.soa.client.model.ModelObject;
//import com.teamcenter.soa.exceptions.NotLoadedException;

/**
 * Implementation of the ChangeListener. Print out all objects that have been updated.
 *
 */
public class GETModelEventListener extends ModelEventListener
{

    @Override
    public void localObjectChange(ModelObject[] objects)
    {
    	/*
        if (objects.length == 0) return;
        System.out.println("");
        System.out.println("The following objects have been updated in the client data model:");
        for (int i = 0; i < objects.length; i++)
        {
            String uid = objects[i].getUid();
            String type = objects[i].getTypeObject().getName();
            String name = "";
            if (objects[i].getTypeObject().isInstanceOf("WorkspaceObject"))
            {
                ModelObject wo = objects[i];
                try
                {
                    name = wo.getPropertyObject("object_string").getStringValue();
                }
                catch (NotLoadedException e) {} // just ignore
            }
            System.out.println("    " + uid + " " + type + " " + name);
        }*/
    }

    @Override
    public void localObjectDelete(String[] uids)
    {
    	/*
        if (uids.length == 0)
            return;

        System.out.println("");
        System.out.println("The following objects have been deleted from the server and removed from the client data model:");
        for (int i = 0; i < uids.length; i++)
        {
            System.out.println("    " + uids[i]);
        }*/
    }
}
