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

Vector3
vector_vector3_add_vector3 (Vector3 v1, Vector3 v2)
{
  Vector3 vec = { 0 };

  vec.x = v1.x + v2.x;
  vec.y = v1.y + v2.y;
  vec.z = v1.z + v2.z;

  return vec;
}
