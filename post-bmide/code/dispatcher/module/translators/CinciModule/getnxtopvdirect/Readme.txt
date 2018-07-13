Nx to Pv Direct Translator Readme
=============================================
  - Version - Refer to the Module/lib/version.txt file for version number.
  Global Technical Access Center (GTAC)
  - Refer to "Global Technical Access Center (GTAC)" section in top level 
    "readme.txt" in \Translators package
-------------------------------------------------------------------------

Contents:
=========
  - Proprietary & Restricted Rights Notice
  - Introduction
  - Prerequisites
  - Licenses Needed     
  - Installation Instructions
  - Translator Configuration
  - Verification
  - Usage
  - Running the Translator Standalone
-------------------------------------------------------------------------

Introduction:
=============
  Nx to Pv Direct Translator translates UG files (.prt) to Jt (.jt) and 
  directly stores the Jt files in TeamCenter Engineering.
-------------------------------------------------------------------------

Prerequisites:
==============
  - TeamCenter Engineering installed on machine
  - Supported Unigraphics NX installed on machine
-------------------------------------------------------------------------

Licenses Needed:
================
  - TeamCenter Engineering 
  - Unigraphics NX
-------------------------------------------------------------------------

Installation Instructions:
==========================
  - Copy the \Translators\getnxtopvdirect directory and its contents from
    the installation CD into the Module directory on the user’s machine.
-------------------------------------------------------------------------

Translator Configuration:
=========================
  - Configuration of Translator.xml:
    Set isactive="true" in translator.xml file inside <getnxtopvdirect> tag
  - Replace appropriate values for "CHANGE_ME" in getnxtopvdirect.bat/sh as per
    the instructions
-------------------------------------------------------------------------

Verification:
=============
  - Run the translator standalone from the command prompt to test that 
    it is working properly.
  - After the Translator setup is complete , verify the Translator             
    installation by translating a UG file through Teamcenter Engineering.
-------------------------------------------------------------------------

Usage:
======
  Go to Translator dirctory and call getnxtopvdirect.bat/sh -help
Example:
  D:\Module\Translators\getnxtopvdirect\getnxtopvdirect.bat -help
-------------------------------------------------------------------------

Running the Translator Standalone:
==================================
 - Information for running translator standalone is provided in the Usage by
    getnxtopvdirect.bat/sh -help
-------------------------------------------------------------------------
