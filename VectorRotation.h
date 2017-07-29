#include "Utilities.h"

/*
 * Function:  ConvertToListenerSpace
 * --------------------
 * Given the position and rotation of a listener in world space, convert on object's world space position to listener space
 *
 *  objPos: Object position
 *  listPos: Listener position
 *  listRot: Listener Rotation
 *	objLSPos: Object's converted Listener space position 
 *  
 *
 *  returns: Error Code REC_OK (0)
 */

RotationErrorCode ConvertToListenerSpace(Vec3* objPos, Vec3* listPos, Rot3* listRot, Vec3* objLSPos);
