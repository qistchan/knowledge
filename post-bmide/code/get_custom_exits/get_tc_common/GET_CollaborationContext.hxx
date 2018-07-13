
/* STARTFILEDOC ***
//   ===========================================================================
//   Filename:   GET_CollaborationContext.hxx
//
//    Purpose:   Header class for dealing with Teamcenter Collaboration Context objects
//
//    History:
//      Who                   Date                 Description
//  TCS Development Team     01 Dec, 2016          Initial creation
//
//   ============================================================================
// ENDFILEDOC   ***/

#ifndef GET_COLLABORATIONCONTEXT_HXX
#define GET_COLLABORATIONCONTEXT_HXX

// GE Includes
#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_WorkspaceObject.hxx>
#include <GET_BOMViewRevision.hxx>
#include <GET_RevisionRule.hxx>

//CPP Includes
#include <sstream>
#include <string>
#include <vector>
#include <map>

// Smart Pointer Definition
namespace get
{
    #define GET_CollaborationContextUnqPtr unique_ptr<GET_CollaborationContext>
    #define GET_CollaborationContextShrPtr shared_ptr<GET_CollaborationContext>
}

namespace get
{
    class DLLEXPORT GET_CollaborationContext : public GET_WorkspaceObject
    {
        public:
		
		/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   GET_CollaborationContext
			 //
			 //    Purpose:   Constructor for the class GET_CollaborationContext
			 //
			 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
			 //               tTag    - The Tag of this Teamcenter Item Revision Object
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team       01 Dec, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_CollaborationContext ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_CollaborationContext
			 //
			 //    Purpose:   Destructor for the class GET_CollaborationContext
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team       01 Dec, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual ~GET_CollaborationContext();
						
			/*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getInstance ( tTag )
			 //
			 //    Purpose:   Method to get the instance of this class using tag_t
			 //
			 //     Inputs:   tTag - tag of the object
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_CollaborationContext Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
			 
            static GET_CollaborationContextUnqPtr getInstance ( const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getInstance ( sUID )
			 //
			 //    Purpose:   Method to get the instance of this class using string UID
			 //
			 //     Inputs:   sUID - UID as string
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_CollaborationContext Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_CollaborationContextUnqPtr getInstance ( const string );
			
			/*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   createConfigContext ( const string, const string, const string )
            //
            //   Purpose :   Method to create configuration context for given name
            //
            //   Inputs  :   Type name - can be empty - will take default type
 		    //				 Name of the ConfigurationContext
 		    //				 Description of the ConfigurationContext
            //
            //   Outputs :   Unique pointer of ConfigurationContext instance
            //
            //   Return  :   The GET_CollaborationContext Smart Pointer instance of Collaboration Context Object
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team       01 Dec, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
            static GET_CollaborationContextUnqPtr createConfigContext ( const string, const string, const string );
			
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   setConfigRevRule ( GET_CollaborationContextShrPtr, GET_RevisionRuleShrPtr )
            //
            //   Purpose :   Method to set configuration revision rule
            //
            //   Inputs  :   Share pointer of Config Context & Revision Rule
            //
            //   Outputs :   None
            //
            //   Return  :   None
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team       01 Dec, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
			static void setConfigRevRule ( GET_CollaborationContextShrPtr, GET_RevisionRuleShrPtr );
			
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   createStructContext ( const string, const string, const string )
            //
            //   Purpose :   Method to create Structure Context
            //
            //   Inputs  :   structContextType, structContextName, structContextDesc
            //
            //   Outputs :   None
            //
            //   Return  :   Share pointer of created Structure context
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team       01 Dec, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
			static GET_CollaborationContextUnqPtr createStructContext ( const string, const string, const string );

            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   addContextContent ( GET_CollaborationContextShrPtr structCnxtShrPtr, vector<GET_WorkspaceObjectShrPtr>, int )
            //
            //   Purpose :   Method to add Context Content
            //
            //   Inputs  :   Share pointer of Struct Context and Component, subType
            //
            //   Outputs :   None
            //
            //   Return  :   None
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team       01 Dec, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
			static void addContextContent ( GET_CollaborationContextShrPtr structCnxtShrPtr, vector<GET_WorkspaceObjectShrPtr>, int );
			
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   setConfigContext ( tag_t, tag_t )
            //
            //   Purpose :   Method to set configuration context
            //
            //   Inputs  :   Share pointer of Struct Context and Config Context
            //
            //   Outputs :   None
            //
            //   Return  :   None
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team       01 Dec, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
			static void setConfigContext ( GET_CollaborationContextShrPtr, GET_CollaborationContextShrPtr );
			
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   createCollaborationCntx ( const string, const string, const string )
            //
            //   Purpose :   Method to create CC Object
            //
            //   Inputs  :   ccType, ccName, ccDesc
            //
            //   Outputs :   None
            //
            //   Return  :   Share pointer of created Collaboration context
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team       01 Dec, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
			static GET_CollaborationContextUnqPtr createCollaborationCntx ( const string, const string, const string );
			
            /*STARTFUNCDOC ***
            //
            ===========================================================================
            //   Function:   addStructContent ( GET_CollaborationContextShrPtr, GET_CollaborationContextShrPtr )
            //
            //   Purpose :   Method to add Structure Content
            //
            //   Inputs  :   Share pointer of Collaboration context & Component Context
            //
            //   Outputs :   None
            //
            //   Return  :   None
            //
            //   History :
            //      Who                    Date                 Description
            //  TCS Development Team       01 Dec, 2016         Initial creation
            //
            ===========================================================================
            //ENDFUNCDOC   ***/
			static void addStructContent ( GET_CollaborationContextShrPtr, GET_CollaborationContextShrPtr );
			
    };
}

#endif // GET_COLLABORATIONCONTEXT_HXX
