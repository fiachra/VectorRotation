
struct Vec3{
	float x;
	float y;
	float z;
};

struct Rot3{
	float yaw;
	float pitch;
	float roll;
};

enum RotationErrorCode{
	REC_OK,
	REC_POSITIONS_MATCH,
	REC_INPUT_INVALID,
	REC_NUM_ERROR_CODES
};

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

enum RotationErrorCode ConvertToListenerSpace(struct Vec3* objPos,struct  Vec3* listPos,struct  Rot3* listRot,struct  Vec3* objLSPos);
