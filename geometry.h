// Geometry Headers

// Vectors 3D and 2D

typedef struct Vec3 {
    float x;
    float y;
    float z;
} vec3;


typedef struct Vec2 {
    float x;
    float y;
} vec2;

typedef struct Vec2i {
    int x;
    int y;
} vec2i;

// Cuboids
#define CUBOID_VERTICES 8

typedef struct Cuboid { 
    vec3 points[CUBOID_VERTICES]; 
} Cuboid;

extern int CUBOID_Render(Cuboid*);
