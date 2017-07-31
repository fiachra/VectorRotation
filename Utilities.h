#ifndef UTILITIES_H
#define UTILITIES_H

#define PI 3.14159265

#define DEG_TO_RAD(angleDegrees) (angleDegrees * PI / 180.0)
#define RAD_TO_DEG(angleRad) (angleRad * 180.0 / PI)
#include <stdbool.h>
#include "Quaternion.h"

/**
 *  Simple Struct to store 3D Vector
 */
typedef struct vec3_t{
	double x;
	double y;
	double z;
}Vec3;

/**
 *  Simple Struct to store Euler rotation
 */
typedef struct rot3_t{
	double roll;
	double pitch;
	double yaw;
}Rot3;

/**
 *  MxN matrix Struct
 */
typedef struct matrix_t{ 
	int h, w; 
	double *x;
} Matrix;

/**
 *  Enumerated Errors
 */
typedef enum rotationErrorCode_t{
	REC_OK,
	REC_MAT_NONINVERTIBLE,
	REC_INPUT_INVALID,
	REC_NUM_ERROR_CODES
}RotationErrorCode;

// printing functions
void printVec3(Vec3* v);
void printRot3(Rot3* r);

//Matrix Functions
void matShow(Matrix* a);
Matrix* matMul(Matrix* a, Matrix* b);
Matrix* matNew(int h, int w);
bool getInverse4x4(Matrix* src, Matrix* dest);

Quaternion *toQuaternion(Rot3 *r);
Rot3 toEulerianAngle(Quaternion* q);

#endif