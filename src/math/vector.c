#include <gorlot.h>

float *
vector_vector3_to_vec3 (Vector3 vector)
{
  // TODO: Is this good?
  static vec3 vec;
  vec[0] = vector.x;
  vec[1] = vector.y;
  vec[2] = vector.z;
  return vec;
}
