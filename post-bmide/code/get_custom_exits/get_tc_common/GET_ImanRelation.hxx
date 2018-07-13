
/* STARTFILEDOC ***
 //   ===========================================================================
 //   Filename:   GET_ImanRelation.hxx
 //
 //    Purpose:   Header for dealing GET_ImanRelation class objects
 //
 //
 //    History:
 //      Who                   Date                 Description
 //  TCS Development Team     21 Mar, 2016         Initial creation
 //  TechM Development Team   20 May, 2017         Added findRelation function
 //   ============================================================================
 // ENDFILEDOC   ***/

#ifndef GET_IMAN_RELATION_HXX
#define GET_IMAN_RELATION_HXX

#include <GET_cpp_stl.h>
#include <GET_sysapi.h>
#include <GET_POM_object.hxx>
#include <GET_WorkspaceObject.hxx>

#include <string>
#include <vector>

// Smart Pointer Definition
namespace get
{
    #define GET_ImanRelationUnqPtr unique_ptr<GET_ImanRelation>
    #define GET_ImanRelationShrPtr shared_ptr<GET_ImanRelation>
}

namespace get
{
    class DLLEXPORT GET_ImanRelation : public GET_POM_object
    {
        private:

    	    /*STARTFUNCDOC ***
    		 //
    		 ===========================================================================
    		 //   Function:   getRelationType()
    		 //
    		 //    Purpose:   Method to get the tag of the given relation type
    		 //
    		 //     Inputs:   sRelationType - The string Relation Name whose tag is required
    		 //
    		 //    Outputs:   none
    		 //
    		 //     Return:   Returns the tag of relation (tag_t)
    		 //
    		 //    History:
    		 //      Who                    Date                 Description
    		 //  TCS Development Team     25 Mar, 2016         Initial creation
    		 //
    		 ===========================================================================
    		 //ENDFUNCDOC   ***/
            static tag_t getRelationType ( const string );

        public:

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   GET_ImanRelation
			 //
			 //    Purpose:   Constructor for the class GET_ImanRelation
			 //
			 //     Inputs:   enDummy - A Dummy Enum that can be accessed only from within this hierarchy
			 //               tTag    - The Tag of this Teamcenter ImanRelation Object
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     02 May, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            GET_ImanRelation ( const GET_DUMMY, const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   ~GET_ImanRelation
			 //
			 //    Purpose:   Destructor for the class GET_ImanRelation
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     02 May, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual ~GET_ImanRelation();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getInstance (tTag)
			 //
			 //    Purpose:   Method to get the instance of this class using tag_t
			 //
			 //     Inputs:   tTag - tag of the object
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_ImanRelation Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_ImanRelationUnqPtr getInstance ( const tag_t );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getInstance (sUID)
			 //
			 //    Purpose:   Method to get the instance of this class using string UID
			 //
			 //     Inputs:   sUID - UID as string
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_ImanRelation Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     11 Apr, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_ImanRelationUnqPtr getInstance ( const string );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getPrimary
			 //
			 //    Purpose:   Method to get the primary object for this relation object
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_POM_object Smart Pointer for the primary object
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     25 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual GET_POM_objectUnqPtr getPrimary();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   getSecondary()
			 //
			 //    Purpose:   Method to get the secondary object for this relation object
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The GET_POM_object Smart Pointer for the secondary object
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     25 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            virtual GET_POM_objectUnqPtr getSecondary();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   create()
			 //
			 //    Purpose:   Method to create Iman relation between given primary and secondary objects
			 //
			 //     Inputs:   primaryPtr    - Smart Pointer for Primary Object
			 //               secondaryPtr  - Smart Pointer for Secondary Object
			 //               sRelationType - Relation Name
			 //               userDataPtr   - Smart Pointer for userData
			 //
			 //    Outputs:   none
			 //
			 //     Return:   The newly created GET_ImanRelation Smart Pointer object is returned
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     25 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static GET_ImanRelationUnqPtr create ( const GET_POM_objectShrPtr,
            			const GET_POM_objectShrPtr, const string sRelationType,
            			const GET_POM_objectShrPtr );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   listRelatedObjects()
			 //
			 //    Purpose:   Method to get the all the primary/secondary objects for the provided object and relation.
			 //
			 //     Inputs:   objectPtr - The GET_POM_object Smart Pointer for the Object whose primaries/secondaries are required
			 //               sRelTypeStr - The Relation Name - Optional - need not be provided in which case all relations are returned
			 //               bIsPrimaryRequired - Boolean to indicate whether primary (true) or secondary (false) objects are required
			 //
			 //    Outputs:   none
			 //
			 //     Return:   A vector with the GET_POM_object Smart Pointer for the related primary Objects
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     25 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static vector<GET_POM_objectUnqPtr> listRelatedObjects ( const GET_POM_objectShrPtr, const string &sRelTypeStr = "", const bool &bIsPrimaryRequired = false );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   listRelatedWsObjects()
			 //
			 //    Purpose:   Method to get the related WorkspaceObject primaries/secondaries for the given input object
			 //
			 //     Inputs:   secondaryPtr - The input GET_POM_object Smart Pointer Object whose primary/secondary WorkspaceObjects are required
			 //               sRelTypeStr - The Relation Name - Optional - need not be provided in which case all relations are returned
			 //               sObjectType - The type of the related WorkspaceObject - Optional - need not be provided in which case all related Workspace Objects are returned
			 //               bIsPrimaryRequired - Boolean to indicate whether primary (true) or secondary (false) objects are required
			 //
			 //    Outputs:   none
			 //
			 //     Return:   A vector with the GET_WorkspaceObject Smart Pointer for the related primary/secondary Objects
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     25 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            static vector<GET_WorkspaceObjectUnqPtr> listRelatedWsObjects ( const GET_POM_objectShrPtr, const string &sRelTypeStr = "",
                                                                              const string &sObjectType = "", const bool &bIsPrimaryRequired = false );

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   saveRelation()
			 //
			 //    Purpose:   Method to save relation.
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     25 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            void saveRelation();

            /*STARTFUNCDOC ***
			 //
			 ===========================================================================
			 //   Function:   deleteRelation()
			 //
			 //    Purpose:   Method to delete relation.
			 //
			 //     Inputs:   none
			 //
			 //    Outputs:   none
			 //
			 //     Return:   none
			 //
			 //    History:
			 //      Who                    Date                 Description
			 //  TCS Development Team     25 Mar, 2016         Initial creation
			 //
			 ===========================================================================
			 //ENDFUNCDOC   ***/
            void deleteRelation();

            /*STARTFUNCDOC ***
        	 //
        	 ===========================================================================
        	 //   Function:   findRelation()
        	 //
        	 //    Purpose:   Method to find Iman relation between given primary and secondary objects
        	 //
        	 //     Inputs:   primaryPtr    - Smart Pointer for Primary Object
        	 //               secondaryPtr  - Smart Pointer for Secondary Object
        	 //               sRelationType - Relation Name
        	 //
        	 //    Outputs:   None
        	 //
        	 //    Return:    GET_ImanRelation Smart Pointer object is returned
        	 //
        	 //    History:
        	 //      Who                    Date                 Description
        	 //  TechM Development Team     20 May, 2017        Initial creation
        	 //
        	 ===========================================================================
        	 //ENDFUNCDOC   ***/
            static GET_ImanRelationUnqPtr findRelation ( const GET_POM_objectShrPtr,
            			const GET_POM_objectShrPtr, const string sRelationType );

    };
}

#endif // GET_IMAN_RELATION_HXX
