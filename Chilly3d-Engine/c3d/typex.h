#ifndef C3D_TYPEX
#define C3D_TYPEX

typedef struct
{
	float x, y;
} c3d_vec2f;

typedef struct
{
	float x, y, z;
} c3d_vec3f;

typedef struct
{
	c3d_vec3f p0;
	c3d_vec3f p1;
	c3d_vec3f p2;
} c3d_triangle3d;



#endif // C3D_TYPEX
