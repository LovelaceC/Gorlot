#include "rotate_tool.h"

#include "../editor.h"

static _Bool editing_axis[3] = { 0 };

static void
axis_set_colour (struct element *axis, Color colour)
{
  // Change an element colour recursively
  axis->color = colour;

  for (int i = 0; i < axis->children.children; i++)
    {
      struct element *child = axis->children.child[i];
      child->color = colour;
    }

  // Also, change it for the parent
  if (axis->parent)
    {
      axis->parent->color = colour;
    }
}

static _Bool
axis_selected (struct element *axis, struct editor *editor)
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
      clicked = axis_selected (axis->children.child[i], editor);

      if (clicked)
        {
          break;
        }
    }

  return clicked;
}

static _Bool
is_editing_axis ()
{
  // Returns true if any value in editing_axis is not 0
  return editing_axis[0] || editing_axis[1] || editing_axis[2];
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

      struct element *selected_axis = NULL;

      struct element *x = rotate_tool->children.child[0];
      struct element *y = rotate_tool->children.child[1];
      struct element *z = rotate_tool->children.child[2];

      // TODO: Update rotate tool scale based on the selected_element's scale

      if (editor->selected_tool == TOOL_ROTATE)
        {
          if ((axis_selected (x, editor) && !is_editing_axis ())
              || editing_axis[0])
            {
              axis_set_colour (x, YELLOW);

              if (IsMouseButtonDown (MOUSE_BUTTON_LEFT) && !is_editing_axis ())
                {
                  editing_axis[0] = 1;
                }
            }
          else
            {
              axis_set_colour (x, RED);
            }

          if ((axis_selected (y, editor) && !is_editing_axis ())
              || editing_axis[1])
            {
              axis_set_colour (y, YELLOW);

              if (IsMouseButtonDown (MOUSE_BUTTON_LEFT) && !is_editing_axis ())
                {
                  editing_axis[1] = 1;
                }
            }
          else
            {
              axis_set_colour (y, GREEN);
            }

          if ((axis_selected (z, editor) && !is_editing_axis ())
              || editing_axis[2])
            {
              axis_set_colour (z, YELLOW);

              if (IsMouseButtonDown (MOUSE_BUTTON_LEFT) && !is_editing_axis ())
                {
                  editing_axis[2] = 1;
                }
            }
          else
            {
              axis_set_colour (z, BLUE);
            }

          if (editing_axis[0])
            {
              Vector2 mouse_delta = GetMouseDelta ();
              float speed = 0.3;
              editor->selected_element->rotation.x
                  += -(mouse_delta.y + mouse_delta.x) * speed;
            }

          if (editing_axis[1])
            {
              Vector2 mouse_delta = GetMouseDelta ();
              float speed = 0.3;
              editor->selected_element->rotation.y
                  += -(mouse_delta.y + mouse_delta.x) * speed;
            }

          if (editing_axis[2])
            {
              Vector2 mouse_delta = GetMouseDelta ();
              float speed = 0.3;
              editor->selected_element->rotation.z
                  += -(mouse_delta.y + mouse_delta.x) * speed;
            }

          if (IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
            {
              editing_axis[0] = 0;
              editing_axis[1] = 0;
              editing_axis[2] = 0;
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
