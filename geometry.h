#include "types.h"
// Geometry Headers

// Cuboids
#define CUBOID_VERTICES 8

typedef struct Cuboid { Vec3 points[CUBOID_VERTICES]; } Cuboid;


extern int CUBOID_Render(Cuboid*);
