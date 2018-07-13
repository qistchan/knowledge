/*==================================================================================================

                                            G E T S

====================================================================================================

Filename:           xmlParserDom.java
File description:   This class parses the input plmxmls and updates the types based on the input itemid-type mapping 
                    and cleans unused attributes from forms
Author:                Dhana Prabhakar Kandula
==================================================================================================*/



import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;


import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class XMLParserDOM {
    
    private String inputTxt;
    private String inputXml;
    private String inputXsl;
    private String outputFol;
    HashSet<String> Items;
    HashSet<String> ItemRevs;
    HashSet<String> ItemRevForms;
    private HashMap<String, String> itemIDTypesMap = new HashMap<String, String>();
    
    //Constructor
    public XMLParserDOM(String intxt, String inxml, String inxsl, String outFol )
    {
        inputTxt = intxt;
        inputXml = inxml;
        inputXsl = inxsl;
        outputFol = outFol;
        
        Items = new HashSet<String> ();
        ItemRevs = new HashSet<String> ();
        ItemRevForms = new HashSet<String> ();
    }
    
    /**
     * Prints Usage Info
     */
    public static void printUsage()
    {
        System.out.println("java -jar xmlParserDom.jar -inTxt=<input Text file> -inXml=<input Xml file> -outFol=<Output Fol> -inXsl=<Input XSL>");
        System.out.println("    Where");
        System.out.println("          -inTxt    : Input file containing item ids and target types");
        System.out.println("          -inXml : Input xml to proces");
        System.out.println("          -inXsl : Input XSL");
        System.out.println("          -outFol : Output Folder ");
    }
    
    /**
     * Processes Input Args
     */
    public static HashMap<String, String> processArgs(String[] args) throws Exception
    {
        HashMap<String,String> argsMap = new HashMap<String,String>();
        for (int i=0; i<args.length; i++)
        {
            String arg = args[i];
            String [] argArray = arg.split("=");
            if( argArray.length > 2 )
            {
                throw new Exception("Argument " + arg + " is not in valid format.\n If this is due to special character please use input file.");
            }
            if( argArray.length == 1 )
            {
                argsMap.put(argArray[0],"");
            }
            if( argArray.length == 2 )
            {
                argsMap.put(argArray[0],argArray[1]);
            }
        }
        return argsMap;
    }
    
    /**
     * Writes the output log
     */
    public void printToFile(HashSet<String> Items, HashSet<String> ItemRevs, HashSet<String> ItemRevForms) throws Exception
    {
    	String logFile=inputXml.substring(inputXml.lastIndexOf("\\")+1);
    	logFile= logFile.substring(0,logFile.lastIndexOf("."))+".log";
    	System.out.println("#### logFile= "+ logFile);
        String filename = outputFol+"/"+ logFile;
        FileWriter fw = new FileWriter(filename);
        fw.write("***** SUMMARY OF TRANSFORMATION ********\n");
        fw.write("---> Total Num of Item Processed:"+Items.size()+"\n");
        fw.write("---> Total Num of Item Revisions Processed:"+ItemRevs.size()+"\n");
        fw.write("---> Total Num of Item Revision Master Forms Processed:"+ItemRevForms.size()+"\n");
        fw.write("Items List: \n");
        for (String id : Items )
        {
            fw.write(id+"\n");
        }
        fw.write("************************************** \n");
        fw.write("Item Revs List: \n");
        for (String id : ItemRevs )
        {
            fw.write(id+"\n");
        }
        fw.write("************************************** \n");
        fw.write("Item Rev Master Forms List: \n");
        for (String id : ItemRevForms )
        {
            fw.write(id+"\n");
        }
        fw.close();
    }
    
    
    /**
     * Reads the input txt and Parses through the input plmxml and modifies it as per the id-type mapping
     */
    public void doIt() throws Exception
    {
        FileReader fr = null;
        BufferedReader br = null;
        try {
            // Read the input xml into Doc builder
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            factory.setValidating(false);
            DocumentBuilder builder = factory.newDocumentBuilder();
            FileInputStream in = new FileInputStream(inputXml);
            Document doc = builder.parse(in);
            // Read and process the input file
            fr = new FileReader(inputTxt);
            br = new BufferedReader(fr);
            String line = br.readLine();
            String split = "=";
            while(line != null)
            {
                System.out.println("Line:"+line);
                if (!line.isEmpty())
                {
                    String[] itemIDType = line.split(split);
                    if (!(itemIDTypesMap.containsKey(itemIDType[0])))
                    {
                        if (itemIDType.length > 1)
                        {
                            itemIDTypesMap.put(itemIDType[0], itemIDType[1]);
                        }
                    }
                }
                line = br.readLine();
            }
            //Target types place holders
            String tarItmType = "";
            String tarItmTypeRev = "";
            String tarItmTypeRevForm = "";
            //String currItem = "";
            //Parse through the input values and modify
            Set<String> itemIds = itemIDTypesMap.keySet();
            for(String currItem : itemIds) {
                //currItem = iter.next();
                System.out.println("Processing Item ID:" +  currItem);
                tarItmType =   itemIDTypesMap.get(currItem); 
                tarItmTypeRev = tarItmType + "Revision";
                tarItmTypeRevForm = tarItmType + "Revision" + "Master";
                // Update Product
                // Get All Product Nodes
                NodeList prdNodes = doc.getElementsByTagName("Product");
                String prdId = "";
                for (int indx= 0; indx < prdNodes.getLength(); indx++) {
                    Element prdElement = (Element) prdNodes.item(indx);
                    if(prdElement.getAttribute("productId").equals(currItem)){
                        NamedNodeMap attr = prdNodes.item(indx).getAttributes();
                        Node nodeAttr = attr.getNamedItem("subType");
                        nodeAttr.setTextContent(tarItmType);
                        Node nodeAttr2 = attr.getNamedItem("id");
                        prdId = nodeAttr2.getTextContent();
                        //Rename nodename based on Type
                        if(tarItmType.equals("GET6MechPart")|| tarItmType.equals("GET6SoftwarePart") || tarItmType.equals("GET6ElectPart"))
                        {
                            Node nodeAttr3 = attr.getNamedItem("productId");
                            doc.renameNode(nodeAttr3,"", "catalogueId");
                            doc.renameNode(prdNodes.item(indx),"http://www.plmxml.org/Schemas/PLMXMLSchema", "Design");
                        }
                        Items.add(currItem);
                        break;
                    }
                 }
                // Update Product Revision
                NodeList prdRevnodes = doc.getElementsByTagName("ProductRevision");
                for (int indx= 0; indx < prdRevnodes.getLength(); indx++) {
                    Element prdElement = (Element) prdRevnodes.item(indx);
                    String masterRef = "#"+prdId;
                    if(prdElement.getAttribute("masterRef").equals(masterRef)){
                        NamedNodeMap attr = prdRevnodes.item(indx).getAttributes();
                        Node nodeAttr = attr.getNamedItem("subType");
                        nodeAttr.setTextContent(tarItmTypeRev);
                         //Rename nodename based on Type
                        if(tarItmType.equals("GET6MechPart")|| tarItmType.equals("GET6SoftwarePart") || tarItmType.equals("GET6ElectPart "))
                        {
                            doc.renameNode(prdRevnodes.item(indx),"http://www.plmxml.org/Schemas/PLMXMLSchema", "DesignRevision");
                        }
                        ItemRevs.add(currItem);
                        break;
                    }
                 }
                // Update Form
                NodeList prdFrmnodes = doc.getElementsByTagName("Form");
                for (int indx= 0; indx < prdFrmnodes.getLength(); indx++) {
                    Element prdElement = (Element) prdFrmnodes.item(indx);
                    String frmName= prdElement.getAttribute("name");
                    String[] FormName = null;
                    if (frmName != null && frmName.length() > 0)
                    {
                        //frmName = frmName.substring(0, frmName.length()-2);
                        FormName = frmName.split("/");
                    }
                    if(FormName[0].equals(currItem)){
                        NamedNodeMap attr = prdFrmnodes.item(indx).getAttributes();
                        Node nodeAttr = attr.getNamedItem("subType");
                        nodeAttr.setTextContent(tarItmTypeRevForm);
                        Node nodeAttr2 = attr.getNamedItem("subClass");
                        nodeAttr2.setTextContent(tarItmTypeRevForm);
                        //loop through the form and Remove userdata flags under Form
                        NodeList list = prdFrmnodes.item(indx).getChildNodes();
                        for (int i = 0; i < list.getLength(); i++) 
                        {
                            Node node = list.item(i);
                           if ("UserData".equals(node.getNodeName())) 
                           {
                               NodeList clist = node.getChildNodes();
                               for (int j = 0; j < clist.getLength(); j++) 
                                  {
                                   Node cNode = clist.item(j);
                                   if ("UserValue".equals(cNode.getNodeName())) 
                                   {
                                       node.removeChild(cNode);
                                   }
                                  }
                           }
                        }
                        ItemRevForms.add(currItem);
                        break;
                        }
                    }
                 }
            //Write the modified to out xml
            String outputXml = outputFol + "\\temp.xml";
            String xmlFile=inputXml.substring(inputXml.lastIndexOf("\\")+1);
            System.out.println("#### xmlFile= " + xmlFile);
            String tranXml = outputFol + "\\"+ xmlFile;
            // Write the output to new xml file and also write log file
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
            DOMSource source = new DOMSource(doc);
            File outFile = new File(outputXml);
            StreamResult result = new StreamResult(outFile);
            transformer.transform(source, result);
            // Remove spaces
            File stylesheet = new File ( inputXsl );
            StreamSource stylesource = new StreamSource ( stylesheet );
            TransformerFactory tFactory = TransformerFactory.newInstance ( );
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
            Transformer ntransformer = tFactory.newTransformer ( stylesource );
            ntransformer.transform ( new StreamSource ( outputXml ), new StreamResult ( new FileOutputStream (tranXml) ));
            printToFile(Items, ItemRevs, ItemRevForms);
            outFile.delete();
            
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        finally
        {
            try {
                br.close();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            try {
                fr.close();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }
    
    /**
     * @param args
     */
    public static void main(String[] args) {
        try {
            HashMap<String, String> argmap = processArgs(args);
            String intxt = argmap.get("-inTxt");
            String inxml = argmap.get("-inXml");
            String inxsl = argmap.get("-inXsl");
            String outFol = argmap.get("-outFol");
            boolean blnContinue = true;
            if( intxt == null )
            {
                System.out.println("Please provide input file using option -inTxt");
                blnContinue = false;
                //printUsage();
            }
            if( inxml == null )
            {
                System.out.println("Please provide output file using option -inXml");
                blnContinue = false;
                //printUsage();
            }
            if( outFol == null )
            {
                System.out.println("Please provide output file using option -outFol");
                blnContinue = false;
                //printUsage();
            }
            if( inxsl == null )
            {
                System.out.println("Please provide output file using option -inxsl");
                blnContinue = false;
                //printUsage();
            }
            if( blnContinue )
            {
                System.out.println("*****input text file      : " + intxt);
                System.out.println("*****input xml file   : " + inxml);
                System.out.println("*****input xsl file   : " + inxsl);
                System.out.println("*****out Fol file   : " + outFol);
                XMLParserDOM pclass = new XMLParserDOM(intxt, inxml, inxsl, outFol);
                System.out.println("Processing.... ");
                pclass.doIt();
                System.out.println("********** Done. Please check for Transformed.xml in Folder: " + outFol);
            }
            else
            {
                printUsage();
            }
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
