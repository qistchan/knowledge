
/**
 * @file  GET_Form.hxx
 * @brief Class for dealing with form objects
 */

#ifndef GET_FORM_HXX
#define GET_FORM_HXX

//GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>
#include <GET_Item.hxx>

//CPP Includes
#include <string>
#include <vector>

// Smart Pointer Definition
namespace get
{
    #define GET_FormUnqPtr unique_ptr<GET_Form>
    #define GET_FormShrPtr shared_ptr<GET_Form>
}

namespace get
{
    class DLLEXPORT GET_Form : public GET_WorkspaceObject
	{
        public:
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   GET_Form ( const GET_DUMMY, const tag_t )
            //
            //   Purpose :   Constructor for the class GET_Form
            //
            //   Inputs  :   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
            //               tTag    - The Tag of this Teamcenter Form Object
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team     02 May, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            GET_Form ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   ~GET_Form()
            //
            //   Purpose :   Destructor for the class GET_Form
            //
            //   Inputs  :   none
            //
            //   Outputs :   none
            //
            //   Return  :   none
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team     02 May, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
		    virtual ~GET_Form();

		     /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   getDataFile()
		     //
		     //    Purpose:   Method to Get Data File Object for this Form
		     //
		     //    Inputs:    none
		     //
		     //    Outputs:   none
		     //
		     //    Return:    The GET_POM_object smart pointer for the Data File Object for this form
		     //
		     //     History:
		     //      Who                   Date                 Description
		     //  TCS Development Team     22 Mar, 2016         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
		    GET_POM_objectUnqPtr getDataFile();

		     /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   setDataFile()
		     //
		     //    Purpose:   Method to set Data File for this Form
		     //
		     //    Inputs:    dataFilePtr - The GET_POM_object Smart Pointer for the Data File Object to be set for this Form
		     //
		     //    Outputs:   none
		     //
		     //    Return:    none
		     //
		     //     History:
		     //      Who                   Date                 Description
		     //  TCS Development Team     22 Mar, 2016         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
		    void setDataFile ( const GET_POM_objectShrPtr );

		     /*STARTFUNCDOC ***
		     //
		     ===========================================================================
		     //   Function:   createForm()
		     //
		     //    Purpose:   Method to create form
		     //
		     //    Inputs:    sFormName - The Form Name (string)
		     //               sFormDescription - The Description to be set for the Form (string)
		     //               sFormType - The Form Type to be created (string)
		     //
		     //    Outputs:   none
		     //
		     //    Return:    The GET_Form Smart Pointer instance for the newly created Form
		     //
		     //     History:
		     //      Who                   Date                 Description
		     //  TCS Development Team     22 Mar, 2016         Initial creation
		     //
		     ===========================================================================
		     //ENDFUNCDOC   ***/
		    GET_FormUnqPtr createForm ( const string, const string, const string );

		    /*STARTFUNCDOC ***
		    //
		    ===========================================================================
		    //   Function:   getInstance(tTag)
		    //
		    //    Purpose:   Method to Get the GET_Form Smart Pointer instance from the give the tag
		    //
		    //    Inputs:    tTag - The Teamcenter tag of the Input Form Object (tag_t)
		    //
		    //    Outputs:   none
		    //
		    //    Return:    The GET_Form smart pointer for the the given tag
		    //
		    //     History:
		    //      Who                   Date                 Description
		    //  TCS Development Team     22 Mar, 2016         Initial creation
		    //
		    ===========================================================================
		    //ENDFUNCDOC   ***/
		    static GET_FormUnqPtr getInstance ( const tag_t );

		    /*STARTFUNCDOC ***
		    //
		    ===========================================================================
		    //   Function:   getInstance(sUID)
		    //
		    //    Purpose:   Method to Get the GET_Form Smart Pointer instance from the give the UID
		    //
		    //    Inputs:    sUID - The Teamcenter UID of the Input Form Object (string)
		    //
		    //    Outputs:   none
		    //
		    //    Return:    The GET_Form smart pointer for the the given UID
		    //
		    //     History:
		    //      Who                   Date                 Description
		    //  TCS Development Team     22 Mar, 2016         Initial creation
		    //
		    ===========================================================================
		    //ENDFUNCDOC   ***/
		    static GET_FormUnqPtr getInstance ( const string );
	};
}

#endif // GET_FORM_HXX
