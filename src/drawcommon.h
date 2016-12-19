#ifndef DRAW_COMMON_H
#define DRAW_COMMON_H
#include "vector3d.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  vec3 pt[3];
} triangle;

typedef struct {
  int npoly;
  triangle *poly;
} object;

void drawTriangle(triangle *poly);
int drawCylinder(int slices, float radius, float height);

#ifdef __cplusplus
}
#endif

#endif