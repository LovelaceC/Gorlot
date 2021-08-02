#include <gorlot.h>
#include <raylib.h>

struct element
element_create ()
{
  struct element el = { 0 };

  el.matrix = (Matrix){ 0 };

  el.position = (Vector3){ 0.0f, 0.0f, 0.0f };
  el.rotation = (Vector3){ 0.0f, 0.0f, 0.0f };
  el.scale = (Vector3){ 1.0f, 1.0f, 1.0f };

  el.children = vector_create ();

  el.selected = 0;

  memset (el.name, 0, sizeof (el.name));
  strncpy (el.name, "Element", sizeof (el.name));

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
      el.mesh = GenMeshCylinder (0.2f, 1.0f, 32);
      break;
    case PRIMITIVE_PLANE:
      // TODO: This
      break;
    case PRIMITIVE_SPHERE:
      el.mesh = GenMeshSphere (0.2f, 32, 32);
      break;
    case PRIMITIVE_TORUS:
      el.mesh = GenMeshTorus (0.5f, 1.0f, 32, 32);
      break;
    case PRIMITIVE_KNOT:
      // TODO: This
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
  Matrix rot = MatrixRotateXYZ (el->rotation);
  Matrix sca = MatrixScale (el->scale.x, el->scale.y, el->scale.z);

  el->matrix = MatrixAdd (rot, sca);
}

void
element_draw (struct element *el)
{
  el->model.transform = el->matrix;
  DrawModel (el->model, el->position, 1.0f, WHITE);

  if (el->selected)
    {
      DrawCubeWires (el->position, el->scale.x + .2f, el->scale.y + .2f,
                     el->scale.z + .2f, RED);
    }
}
