#include "rotate_tool.h"

#include "../editor.h"

static _Bool
axis_clicked (struct element *axis, struct editor *editor)
{
  // This function checks the axis (and its children) if they were clicked or
  // not.
  _Bool clicked = 0;

  Vector3 position = axis->position;
  position = element_get_final_position (axis);

  editor->editor_ray
      = GetMouseRay (GetMousePosition (), editor->editor_cam.cam);

  editor->editor_ray_collision
      = GetRayCollisionModel (editor->editor_ray, axis->model);

  clicked = editor->editor_ray_collision.hit;

  if (clicked)
    {
      return clicked;
    }

  for (int i = 0; i < axis->children.children; i++)
    {
      clicked = axis_clicked (axis->children.child[i], editor);

      if (clicked)
        {
          break;
        }
    }

  return clicked;
}

struct element *
rotate_tool ()
{
  // TODO: Draw cones at the end of the each axis
  struct element *el = NULL;
  el = malloc (sizeof (struct element));
  *el = element_create ();
  el->scale = (Vector3){ 0.5f, 0.5f, 0.5f };

  // X Axis
  struct element *x = NULL;
  x = malloc (sizeof (struct element));
  *x = element_create ();

  x->mesh = GenMeshTorus (0.1f, 1.5f, 32, 32);
  x->color = RED;
  x->rotation.y = 90.0f;
  x->model = LoadModelFromMesh (x->mesh);

  element_add_child (el, x);

  // Y Axis
  struct element *y = NULL;
  y = malloc (sizeof (struct element));
  *y = element_create ();

  y->mesh = GenMeshTorus (0.1f, 1.5f, 32, 32);
  y->color = GREEN;
  y->rotation.x = 90.0f;
  y->model = LoadModelFromMesh (y->mesh);

  element_add_child (el, y);

  // Z Axis
  struct element *z = NULL;
  z = malloc (sizeof (struct element));
  *z = element_create ();

  z->mesh = GenMeshTorus (0.1f, 1.5f, 32, 32);
  z->color = BLUE;
  z->model = LoadModelFromMesh (z->mesh);

  element_add_child (el, z);

  return el;
}

void
rotate_tool_update (struct editor *editor, struct element *rotate_tool)
{
  if (editor->selected_element)
    {
      rotate_tool->position = editor->selected_element->position;

      struct element *x = rotate_tool->children.child[0];
      struct element *y = rotate_tool->children.child[1];
      struct element *z = rotate_tool->children.child[2];

      // TODO: Update rotate tool scale based on the selected_element's scale

      if (editor->selected_tool == TOOL_ROTATE)
        {
          if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
            {
              for (int i = 0; i < rotate_tool->children.children; i++)
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

                  struct element *axis = rotate_tool->children.child[i];

                  if (axis_clicked (axis, editor))
                    {
                      axis->color = YELLOW;
                    }
                }
            }
        }
    }

  element_update (rotate_tool);
}

void
rotate_tool_free (struct element **rotate_tool)
{
  struct element *el = *rotate_tool;

  for (int i = 0; i < el->children.children; i++)
    {
      struct element *child = el->children.child[i];
      element_free (child);

      if (child->children.children != 0)
        {
          rotate_tool_free (&child);
        }

      free (el->children.child[i]);
      el->children.child[i] = NULL;
    }

  vector_free (&el->children);
  element_free (el);

  free (el);
  el = NULL;
}
