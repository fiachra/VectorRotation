#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Quaternion.h"

Quaternion *quaternionNew(void)
{
  return malloc(sizeof(Quaternion));
}
 
Quaternion *quaternionNewSet(double q1,
         double q2,
         double q3,
         double q4)
{
  Quaternion *q = malloc(sizeof(Quaternion));
  if (q != NULL) {
    q->q[0] = q1; q->q[1] = q2; q->q[2] = q3; q->q[3] = q4;
  }
  return q;
}
 
 
void quaternionCopy(Quaternion *r, Quaternion *q)
{
  size_t i;
 
  if (r == NULL || q == NULL) return;
  for(i = 0; i < 4; i++) r->q[i] = q->q[i];
}
 
 
double quaternionNorm(Quaternion *q)
{
  size_t i;
  double r = 0.0;
 
  if (q == NULL) {
    fprintf(stderr, "NULL quaternion in norm\n");
    return 0.0;
  }
 
  for(i = 0; i < 4; i++) r += q->q[i] * q->q[i];
  return sqrt(r);
}
 
 
void quaternionNeg(Quaternion *r, Quaternion *q)
{
  size_t i;
 
  if (q == NULL || r == NULL) return;
  for(i = 0; i < 4; i++) r->q[i] = -q->q[i];
}
 
 
void quaternionConj(Quaternion *r, Quaternion *q)
{
  size_t i;
 
  if (q == NULL || r == NULL) return;
  r->q[0] = q->q[0];
  for(i = 1; i < 4; i++) r->q[i] = -q->q[i];
}
 
 
void quaternionAdd_d(Quaternion *r, Quaternion *q, double d)
{
  if (q == NULL || r == NULL) return;
  quaternionCopy(r, q);
  r->q[0] += d;
}
 
 
void quaternionAdd(Quaternion *r, Quaternion *a, Quaternion *b)
{
  size_t i;
 
  if (r == NULL || a == NULL || b == NULL) return;
  for(i = 0; i < 4; i++) r->q[i] = a->q[i] + b->q[i];
}
 
 
void quaternionMul_d(Quaternion *r, Quaternion *q, double d)
{
  size_t i;
 
  if (r == NULL || q == NULL) return;
  for(i = 0; i < 4; i++) r->q[i] = q->q[i] * d;
}
 
bool quaternionEqual(Quaternion *a, Quaternion *b)
{
  size_t i;
 
  for(i = 0; i < 4; i++) if (a->q[i] != b->q[i]) return false;
  return true;
}
 
 
#define A(N) (a->q[(N)])
#define B(N) (b->q[(N)])
#define R(N) (r->q[(N)])
void quaternionMul(Quaternion *r, Quaternion *a, Quaternion *b)
{
  //size_t i;
  //double ri = 0.0;
 
  if (r == NULL || a == NULL || b == NULL) return;
  R(0) = A(0)*B(0) - A(1)*B(1) - A(2)*B(2) - A(3)*B(3);
  R(1) = A(0)*B(1) + A(1)*B(0) + A(2)*B(3) - A(3)*B(2);
  R(2) = A(0)*B(2) - A(1)*B(3) + A(2)*B(0) + A(3)*B(1);
  R(3) = A(0)*B(3) + A(1)*B(2) - A(2)*B(1) + A(3)*B(0);
}
#undef A
#undef B
#undef R
 
 
void quaternionPrint(Quaternion *q)
{
  if (q == NULL) return;
  printf("(%lf, %lf, %lf, %lf)\n", 
   q->q[0], q->q[1], q->q[2], q->q[3]);
}
