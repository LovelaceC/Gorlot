#include "scale_tool.h"

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
  element_set_static (el, 0);

  return el;
}

void
scale_tool_update (struct editor *editor, struct element *scale_tool)
{
  if (editor->selected_element)
    {
      scale_tool->position = editor->selected_element->position;

      struct element *selected_axis = NULL;

      struct element *x = scale_tool->children.child[0];
      struct element *y = scale_tool->children.child[1];
      struct element *z = scale_tool->children.child[2];

      // TODO: Update scale tool scale based on the selected_element's scale

      if (editor->selected_tool == TOOL_SCALE)
        {
          // TODO: Delete elses (I don't like using them, I made this fast just
          // to test how I'd do it)

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
              Vector3 rotation = editor->current_cam->rotation;

              editor->selected_element->scale.x
                  += (-mouse_delta.y * sin (rotation.x)
                      - mouse_delta.x * cos (rotation.x))
                     * 0.01;
            }

          if (editing_axis[1])
            {
              Vector2 mouse_delta = GetMouseDelta ();
              Vector3 rotation = editor->current_cam->rotation;

              editor->selected_element->scale.y += -mouse_delta.y * 0.01;
            }

          if (editing_axis[2])
            {
              Vector2 mouse_delta = GetMouseDelta ();
              Vector3 rotation = editor->current_cam->rotation;

              editor->selected_element->scale.z
                  += (-mouse_delta.y * sin (rotation.x + 1.57)
                      - mouse_delta.x * cos (rotation.x + 1.57))
                     * 0.01;
            }

          if (IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
            {
              editing_axis[0] = 0;
              editing_axis[1] = 0;
              editing_axis[2] = 0;
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
