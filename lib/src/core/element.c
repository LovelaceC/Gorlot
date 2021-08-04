#include <gorlot.h>

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

  el.parent = NULL;

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
element_add_child (struct element *parent, struct element *child)
{
  vector_add_child (&parent->children, child);
  child->parent = parent;
}

void
element_update (struct element *el)
{
  Vector3 rotation = el->rotation;
  rotation.x *= DEG2RAD;
  rotation.y *= DEG2RAD;
  rotation.z *= DEG2RAD;

  Vector3 scale = el->scale;

  if (el->parent)
    {
      scale = vector_vector3_add_vector3 (el->scale, el->parent->scale);
    }

  mat4 mat = GLM_MAT4_IDENTITY_INIT;
  matrix_mat4_rotate_from_vec3 (mat, vector_vector3_to_vec3 (rotation));
  matrix_mat4_scale_from_vec3 (mat, vector_vector3_to_vec3 (scale));

  el->matrix = matrix_mat4_to_matrix (mat);

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
      Vector3 position = el->position;

      // Inherit the parent's position
      if (el->parent)
        {
          position = vector_vector3_add_vector3 (el->position,
                                                 el->parent->position);
        }

      DrawModel (el->model, position, 1.0f, el->color);
    }
}

void
element_free (struct element *el)
{
  if (!el)
    {
      return;
    }

  for (int i = 0; i < el->children.children; i++)
    {
      element_free (el->children.child[i]);
    }

  // This is returning a segmentation fault error, todo fix it?
  /*UnloadMesh (el->mesh);
    UnloadModel (el->model);*/

  vector_free (&el->children);
  el->children.child = NULL;

  el->parent = NULL;
}
