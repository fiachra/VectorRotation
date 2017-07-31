#include <stdbool.h>
 
typedef struct quaternion_t
{
  double q[4];
} Quaternion;

Quaternion *quaternionNew(void);
Quaternion *quaternionNewSet(double q1,double q2,double q3, double q4);
void quaternionCopy(Quaternion *r, Quaternion *q) ;
double quaternionNorm(Quaternion *q);
void quaternionNeg(Quaternion *r, Quaternion *q);
void quaternionConj(Quaternion *r, Quaternion *q);
void quaternionAdd_d(Quaternion *r, Quaternion *q, double d);
void quaternionAdd(Quaternion *r, Quaternion *a, Quaternion *b);
void quaternionMul_d(Quaternion *r, Quaternion *q, double d);
bool quaternionEqual(Quaternion *a, Quaternion *b);
void quaternionMul(Quaternion *r, Quaternion *a, Quaternion *b);
void quaternionPrint(Quaternion *q);
