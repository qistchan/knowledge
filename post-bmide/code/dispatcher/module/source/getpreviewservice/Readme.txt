PreviewService Translator Readme
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
  PreviewService is a generic preview generation translator which is a 
  combination of the translators which are configured as a part of this
  translator which use Visconvert. 
  It can be used as a post processor for preview generation.

-------------------------------------------------------------------------

Prerequisites:
==============
  - Refer to the pre-requisites of the translators which are configured 
    as a part of this translator
-------------------------------------------------------------------------

Licenses Needed:
================
  - Refer to the licensing information of the translators 
    which are configured as a part of this translator
-------------------------------------------------------------------------

Installation Instructions:
==========================
  - Copy the \Translators\previewservice directory and its contents from
    the installation CD into the Module directory on the user’s machine.
-------------------------------------------------------------------------

Translator Configuration:
=========================
  - Configuration of Translator.xml:
    Set isactive="true" in translator.xml file inside <PreviewService> tag
  - Replace appropriate values for "CHANGE_ME" in previewservice.bat/sh as per
    the instructions
  - To Configure Jt2Jpeg:
    - on Windows: set LM_LICENSE_FILE=CHANGE_ME
    - on UNIX: export LM_LICENSE_FILE=CHANGE_ME and export DISPLAY=CHANGE_ME
  - To Configure Visconvert Prepare:
    - on Windows: set TC_VVCP=CHANGE_ME
    - on UNIX: export TC_VVCP=CHANGE_ME
-------------------------------------------------------------------------

Verification:
=============
  - Run the translator standalone from the command prompt to test that 
    it is working properly.
  - After the Translator setup is complete, verify the Translator 
    installation by dragging and dropping a CAD file in to Teamcenter 
    Enterprise Rich Client or Classic Client. The CAD file will be 
    translated and if this translator is enabled as the post
    processor for the CAD file translator, a preview file will be 
    produced.
-------------------------------------------------------------------------

Usage:
======
  Go to Translator dirctory and call previewservice.bat/sh -help
Example:
  D:\Module\Translators\previewservice\previewservice.bat -help

  - Usage of Jt2Jpeg:
          Translator executable name: jt2jpeg.exe
          Twenty one parameters to pass: 
          1) -i
          2) Input Jt file(.jt) name to translate with complete path
          3) -o 
          4) Output JPEG file(.jpeg) name with complete path
          5) -image
          6) 3
          7) -view
          8) 0
          9) -size
          10) 500
          11) 500
          12) -bg
          13) 0
          14) -vtype
          15) 1
          16) -quality
          17) 100
          18) -b
          19) Name of bom (Bills of Material) file to be created
          20) -l
          21) Name of log file created in case of any error

          jt2jpeg.exe -i inputFile -o outputFile -image 3 -view 0 -size 500 500
                      -bg 0 -vtype 1 -quality 100 -b BOMFile -l LogFile
-------------------------------------------------------------------------

Running the Translator Standalone:
==================================
 - Information for running translator standalone is provided in the Usage by 
    previewservice.bat/sh -help
  - Running Jt2Jpeg standalone:
          - Type the following command at the command prompt:
            jt2jpeg.exe -i inputFile -o outputFile
            Example: jt2jpeg.exe -i e:\ebox\ebox.jt -o e:\ebox\ebox.jpeg 
                                 -image 3 -view 0 -size 500 500 -bg 0 -vtype 1 
                                 -quality 100 -b jt2jpeg.bom -l jt2jpeg.log

          - On UNIX machines
            The DISPLAY variable in previewservice.sh should be set to valid display.
            Example : export DISPLAY=machinename:0.0.
              
            To do this change previewservice.sh script 
            (located in <Module_Install>/translators/previewservice folder) as follows: 
            change 
                  export DISPLAY=:0.0 
            to 
                  export DISPLAY=:1.0 
            Note: If the display variable is incorrectly set, the translator 
                  may hang.

            
            JT2JPEG is supported only on machines with valid display hardware. 
            Some Unix systems may not have a valid display available because 
            of a lack of display hardware. For these cases, using a virtual 
            framebuffer to run the translator may work in some instances, but 
            it is not supported. If you want to try running the translator on 
            a system without display hardware, do the following steps.

            Verify that the X11 libs are installed on the system.
            Use a virtual frame buffer (available with the X11 graphics 
            libs: Xvfb) to emulate the X Server Display in virtual memory.

            In the startup script of the unix machine add following lines. 
            This will send any graphics output going to display 1 to shared 
            memory. 
            /usr/X11R6.1/bin/Xvfb :1 -screen 0 1152x900x24 &
            where /usr/X11R6.1/bin is the path where Xvfb is located.
            1152x900x24 is the resolution x depth of the screen.

            To set the current display, which will use the frame buffer for 
            displaying graphics, change previewservice.sh script 
            (located in <Module_Install>/translators/previewservice folder) as follows: 
            change
               export DISPLAY=:0.0
            to 
               export DISPLAY=:1.0
-------------------------------------------------------------------------
