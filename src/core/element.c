#include <cglm/affine.h>
#include <cglm/mat4.h>
#include <gorlot.h>

#include <cglm/cglm.h>
#include <raymath.h>

struct element
element_create ()
{
  struct element el = { 0 };

  el.matrix = (Matrix){ 0 };

  el.position = (Vector3){ 0.0f, 0.0f, 0.0f };
  el.rotation = (Vector3){ 0.0f, 0.0f, 0.0f };
  el.scale = (Vector3){ 1.0f, 1.0f, 1.0f };

  el.children = vector_create ();

  el.color = RAYWHITE;

  el.selected = 0;
  el.visible = 1;

  return el;
}

struct element
element_create_primitive (enum primitive_type type)
{
  struct element el = element_create ();

  switch (type)
    {
    case PRIMITIVE_CUBE:
      el.mesh = GenMeshCube (1.0f, 1.0f, 1.0f);
      break;
    case PRIMITIVE_CYLINDER:
      el.mesh = GenMeshCylinder (0.5f, 1.0f, 32);
      break;
    case PRIMITIVE_PLANE:
      // TODO: This
      break;
    case PRIMITIVE_SPHERE:
      el.mesh = GenMeshSphere (0.5f, 32, 32);
      break;
    case PRIMITIVE_TORUS:
      el.mesh = GenMeshTorus (0.5f, 1.0f, 32, 32);
      break;
    case PRIMITIVE_KNOT:
      el.mesh = GenMeshKnot (1.0f, 1.0f, 32, 32);
      break;
    default:
      printf (
          "element_create_primitive: `%d' is not a valid primitive type.\n",
          type);
      return el;
      break;
    }

  el.model = LoadModelFromMesh (el.mesh);
  return el;
}

void
element_update (struct element *el)
{
  Vector3 rotation = el->rotation;
  rotation.x *= DEG2RAD;
  rotation.y *= DEG2RAD;
  rotation.z *= DEG2RAD;

  mat4 mat = GLM_MAT4_IDENTITY_INIT;
  glm_rotate_x (mat, rotation.x, mat);
  glm_rotate_y (mat, rotation.y, mat);
  glm_rotate_z (mat, rotation.z, mat);

  vec3 scale = { el->scale.x, el->scale.y, el->scale.z };
  glm_scale (mat, scale);

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

  el->matrix = matrix;

  for (int i = 0; i < el->children.children; i++)
    {
      element_update (el->children.child[i]);
    }
}

void
element_draw (struct element *el)
{
  el->model.transform = el->matrix;

  for (int i = 0; i < el->children.children; i++)
    {
      element_draw (el->children.child[i]);
    }

  if (el->visible)
    {
      DrawModel (el->model, el->position, 1.0f, el->color);
    }
}
