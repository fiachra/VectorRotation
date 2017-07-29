#define PI 3.14159265

#define DEG_TO_RAD(angleDegrees) (angleDegrees * PI / 180.0)

#define false 0
#define true 1

typedef int bool; // or #define bool int

typedef struct vec3_t{
	float x;
	float y;
	float z;
}Vec3;

typedef struct rot3_t{
	float roll;
	float pitch;
	float yaw;
}Rot3;

typedef struct matrix_t{ 
	int h, w; 
	double *x;
} Matrix;

typedef enum rotationErrorCode_t{
	REC_OK,
	REC_POSITIONS_MATCH,
	REC_INPUT_INVALID,
	REC_NUM_ERROR_CODES
}RotationErrorCode;

void printVec3(Vec3* v);

//Matrix Functions
void matShow(Matrix* a);
Matrix* matMul(Matrix* a, Matrix* b);
Matrix* matNew(int h, int w);
bool getInverse4x4(Matrix* src, Matrix* dest);
