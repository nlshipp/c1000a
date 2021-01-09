#ifndef _RUT_UTIL_H
#define _RUT_UTIL_H


#define rut_doSystemAction(from, cmd )  do { \
						system(cmd); \
						tsl_printf("%s -- %s\n", from, cmd); \
					} while(0)

/** Macro to determine if this is a new MdmObject creation case.
 */
#define ADD_NEW(n, c) (((n) != NULL) && (c == NULL))


/** Macro to determine if this is a MdmObject deletion case
 */
#define DELETE_EXISTING(n, c) (((n) == NULL) && (c != NULL))


/** Macro to determine if an MdmObject is being added and enabled,
 *  or if an existing MdmObject that is currently disabled is now is being enabled.
 */
#define ENABLE_NEW_OR_ENABLE_EXISTING(n, c) \
   (((n) != NULL && (n)->Enable && (c) == NULL) || \
    ((n) != NULL && (n)->Enable && (c) != NULL && !((c)->Enable)))
    
/** Macro to determine if an existing MdmObject is being enabled.
 */
#define ENABLE_EXISTING(n, c) \
   ((n) != NULL && (n)->Enable && (c) != NULL && !((c)->Enable))


/** Macro to determine if an MdmObject is being deleted (which implies disble),
 *  or if an existing MdmObject that is currently enabled is now being disabled.
 */
#define DELETE_OR_DISABLE_EXISTING(n, c) \
   (((n) == NULL) ||                                                    \
    ((n) != NULL && !((n)->Enable) && (c) != NULL && (c)->Enable))

/** Macro to determine if this is POTENTIALLY a modification of an existing
 * and enabled object.  
 * 
 * This macro must be used in conjunction with another function which
 * you provide that determines if any of the fields in the object has
 * changed.  This macro only verifies that the object currently exists
 * and is enabled. Example usage:
 * 
 * if (POTENTIAL_CHANGE_OF_EXISTING(newObj, currObj) && fieldsHaveChanged(newObj, currObj)
 * 
 */
#define POTENTIAL_CHANGE_OF_EXISTING(n, c) \
   (((n) != NULL && (n)->Enable && (c) != NULL && (c)->Enable))



#endif // _RUT_UTIL_H

