#include "scale_tool.h"

#include "../editor.h"

struct element *
scale_tool ()
{
  // TODO: Draw cones at the end of the each axis
  struct element *el = NULL;
  el = malloc (sizeof (struct element));
  *el = element_create ();
  el->scale = (Vector3){ 0.1f, 0.1f, 0.1f };

  // X Axis
  struct element *x = NULL;
  x = malloc (sizeof (struct element));
  *x = element_create ();

  x->mesh = GenMeshCube (1.0f, 0.1f, 0.1f);
  x->color = RED;
  x->scale.x = 1.5f;
  x->position.x = x->scale.x / 2;
  x->model = LoadModelFromMesh (x->mesh);

  element_add_child (el, x);

  // X Cube
  struct element *x_cube = NULL;
  x_cube = malloc (sizeof (struct element));
  *x_cube = element_create ();

  x_cube->mesh = GenMeshCube (0.15f, 0.15f, 0.15f);
  x_cube->color = RED;
  x_cube->position.x = x->scale.x;
  x_cube->model = LoadModelFromMesh (x_cube->mesh);

  element_add_child (x, x_cube);

  // Y Axis
  struct element *y = NULL;
  y = malloc (sizeof (struct element));
  *y = element_create ();

  y->mesh = GenMeshCube (1.0f, 0.1f, 0.1f);
  y->color = GREEN;
  y->scale.y = 1.5f;
  y->rotation.z = 90.0f;
  y->position.y = y->scale.y / 2;
  y->model = LoadModelFromMesh (y->mesh);

  element_add_child (el, y);

  // Y Cube
  struct element *y_cube = NULL;
  y_cube = malloc (sizeof (struct element));
  *y_cube = element_create ();

  y_cube->mesh = GenMeshCube (0.15f, 0.15f, 0.15f);
  y_cube->color = GREEN;
  y_cube->position.y = y->scale.y;
  y_cube->model = LoadModelFromMesh (y_cube->mesh);

  element_add_child (y, y_cube);

  // Z Axis
  struct element *z = NULL;
  z = malloc (sizeof (struct element));
  *z = element_create ();

  z->mesh = GenMeshCube (1.0f, 0.1f, 0.1f);
  z->color = BLUE;
  z->rotation.y = 90.0f;
  z->scale.z = 1.5f;
  z->position.z = z->scale.z / 2;
  z->model = LoadModelFromMesh (z->mesh);

  element_add_child (el, z);

  // Z Cube
  struct element *z_cube = NULL;
  z_cube = malloc (sizeof (struct element));
  *z_cube = element_create ();

  z_cube->mesh = GenMeshCube (0.15f, 0.15f, 0.15f);
  z_cube->color = BLUE;
  z_cube->position.z = z->scale.z;
  z_cube->model = LoadModelFromMesh (z_cube->mesh);

  element_add_child (z, z_cube);

  return el;
}

void
scale_tool_update (struct editor *editor, struct element *scale_tool)
{
  if (editor->selected_element)
    {
      scale_tool->position = editor->selected_element->position;

      struct element *x = scale_tool->children.child[0];
      struct element *y = scale_tool->children.child[1];
      struct element *z = scale_tool->children.child[2];

      // TODO: Update scale tool scale based on the selected_element's scale

      if (editor->selected_tool == TOOL_SCALE)
        {
          if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
            {
              for (int i = 0; i < scale_tool->children.children; i++)
                {
                  // TODO: Change this
                  // Create a variable `editing_axis[x,y,z]`, depending on the
                  // axis that was click, the value of the editing_axis[axis
                  // clicked] will be set to true, when the mouse is released
                  // that variable will be set back to zero, and while it's
                  // true the mouse will be captured and the selected element
                  // will translate depending on the variable that is set to
                  // true.
                  // Also, change the axis that is being edited colour to
                  // yellow, and then turn back to its original colour.

                  struct element *axis = scale_tool->children.child[i];

                  editor->editor_ray
                      = GetMouseRay (GetMousePosition (), editor->editor_cam);

                  editor->editor_ray_collision = GetRayCollisionBox (
                      editor->editor_ray,
                      (BoundingBox){
                          (Vector3){ axis->position.x - axis->scale.x / 2,
                                     axis->position.y - axis->scale.y / 2,
                                     axis->position.z - axis->scale.z / 2 },
                          (Vector3){ axis->position.x + axis->scale.x / 2,
                                     axis->position.y + axis->scale.y / 2,
                                     axis->position.z + axis->scale.z / 2 } });

                  if (editor->editor_ray_collision.hit)
                    {
                      axis->color = YELLOW;
                    }
                }
            }
        }
    }

  element_update (scale_tool);
}

void
scale_tool_free (struct element **scale_tool)
{
  struct element *el = *scale_tool;

  for (int i = 0; i < el->children.children; i++)
    {
      struct element *child = el->children.child[i];
      element_free (child);

      if (child->children.children != 0)
        {
          scale_tool_free (&child);
        }

      free (el->children.child[i]);
      el->children.child[i] = NULL;
    }

  vector_free (&el->children);
  element_free (el);

  free (el);
  el = NULL;
}
