
#include <math.h>
#include <float.h>
#include "rendering.h"
#include "vec_math.h"

t_vec3 plane_intersect(t_plane *plane, t_vec3 pos, t_vec3 dir)
{
	float denom = vec3_dot(plane->normal, dir);
	if (fabsf(denom) < FLT_EPSILON)
		return vec3_init(NAN, NAN, NAN);
	float t = vec3_dot(vec3_sub(plane->pos, pos), plane->normal) / denom;
	if (t < 0)
		return vec3_init(NAN, NAN, NAN);
	return vec3_add(pos, vec3_mul(dir, t));
}

t_color	plane_sample_color(t_plane *plane, t_vec3 pos)
{
	(void)pos;
	return (plane->color);
}
