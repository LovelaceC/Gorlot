#include <gorlot.h>

void
matrix_mat4_scale_from_vec3 (mat4 mat, vec3 vec)
{
  glm_scale (mat, vec);
}

void
matrix_mat4_rotate_from_vec3 (mat4 mat, vec3 vec)
{
  glm_rotate_x (mat, vec[0], mat);
  glm_rotate_x (mat, vec[1], mat);
  glm_rotate_x (mat, vec[2], mat);
}

Matrix
matrix_mat4_to_matrix (mat4 mat)
{
  Matrix matrix = MatrixIdentity ();
  matrix.m0 = mat[0][0];
  matrix.m4 = mat[0][1];
  matrix.m8 = mat[0][2];
  matrix.m12 = mat[0][3];

  matrix.m1 = mat[1][0];
  matrix.m5 = mat[1][1];
  matrix.m9 = mat[1][2];
  matrix.m13 = mat[1][3];

  matrix.m2 = mat[2][0];
  matrix.m6 = mat[2][1];
  matrix.m10 = mat[2][2];
  matrix.m14 = mat[2][3];

  matrix.m3 = mat[3][0];
  matrix.m7 = mat[3][1];
  matrix.m11 = mat[3][2];
  matrix.m15 = mat[3][3];

  return matrix;
}
