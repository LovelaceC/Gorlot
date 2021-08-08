#include "move_tool.h"

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
move_tool ()
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

  x->mesh = GenMeshCylinder (0.05f, 1.0f, 32);
  x->color = RED;
  x->rotation.z = 90.0f;
  x->scale.x = 1.5f;
  x->model = LoadModelFromMesh (x->mesh);

  element_add_child (el, x);

  // X Cone
  struct element *x_cone = NULL;
  x_cone = malloc (sizeof (struct element));
  *x_cone = element_create ();

  x_cone->mesh = GenMeshCone (0.1f, 0.2f, 32);
  x_cone->position.x = x->scale.x;
  x_cone->color = RED;
  x_cone->rotation.z = 90.0f;
  x_cone->model = LoadModelFromMesh (x_cone->mesh);

  element_add_child (x, x_cone);

  // Y Axis
  struct element *y = NULL;
  y = malloc (sizeof (struct element));
  *y = element_create ();

  y->mesh = GenMeshCylinder (0.05f, 1.0f, 32);
  y->color = GREEN;
  y->rotation.y = 90.0f;
  y->scale.y = 1.5f;
  y->model = LoadModelFromMesh (y->mesh);

  element_add_child (el, y);

  // Y COne
  struct element *y_cone = NULL;
  y_cone = malloc (sizeof (struct element));
  *y_cone = element_create ();

  y_cone->mesh = GenMeshCone (0.1f, 0.2f, 32);
  y_cone->position.y = y->scale.y;
  y_cone->color = GREEN;
  y_cone->rotation.y = 90.0f;
  y_cone->model = LoadModelFromMesh (y_cone->mesh);

  element_add_child (y, y_cone);

  // Z Axis
  struct element *z = NULL;
  z = malloc (sizeof (struct element));
  *z = element_create ();

  z->mesh = GenMeshCylinder (0.05f, 1.0f, 32);
  z->color = BLUE;
  z->rotation.x = -90.0f;
  z->scale.z = 1.5f;
  z->model = LoadModelFromMesh (z->mesh);

  element_add_child (el, z);

  // Z COne
  struct element *z_cone = NULL;
  z_cone = malloc (sizeof (struct element));
  *z_cone = element_create ();

  z_cone->mesh = GenMeshCone (0.1f, 0.2f, 32);
  z_cone->position.z = z->scale.z;
  z_cone->color = BLUE;
  z_cone->rotation.x = -90.0f;
  z_cone->model = LoadModelFromMesh (z_cone->mesh);

  element_add_child (z, z_cone);

  return el;
}

void
move_tool_update (struct editor *editor, struct element *move_tool)
{
  if (editor->selected_element)
    {
      move_tool->position = editor->selected_element->position;

      struct element *selected_axis = NULL;

      struct element *x = move_tool->children.child[0];
      struct element *y = move_tool->children.child[1];
      struct element *z = move_tool->children.child[2];

      // TODO: Update move tool scale based on the selected_element's scale

      if (editor->selected_tool == TOOL_MOVE)
        {
          // TODO: Delete elses (I don't like using them, I made this fast just
          // to test how I'd do it)
          // TODO: Fix movement based on camera rotation (as sometimes it must
          // be negative, whereas some others it must be positive(

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
              float speed = 0.05f;

              editor->selected_element->position.x
                  -= mouse_delta.y * speed
                     * sin (editor->current_cam->rotation.x) / 1.0f;

              editor->selected_element->position.x
                  -= mouse_delta.x * speed
                     * cos (editor->current_cam->rotation.x) / 1.0f;
            }

          if (editing_axis[1])
            {
              Vector2 mouse_delta = GetMouseDelta ();
              float speed = 0.05f;

              editor->selected_element->position.y
                  -= mouse_delta.y * speed / 1.0f;
            }

          if (editing_axis[2])
            {
              Vector2 mouse_delta = GetMouseDelta ();
              float speed = 0.05f;

              editor->selected_element->position.z
                  -= mouse_delta.y * speed
                     * sin (editor->current_cam->rotation.x * DEG2RAD) / 1.0f;
              editor->selected_element->position.z
                  -= mouse_delta.x * speed
                     * cos (editor->current_cam->rotation.x * DEG2RAD) / 1.0f;
            }

          if (IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
            {
              editing_axis[0] = 0;
              editing_axis[1] = 0;
              editing_axis[2] = 0;
            }
        }
    }

  element_update (move_tool);
}

void
move_tool_free (struct element **move_tool)
{
  struct element *el = *move_tool;

  for (int i = 0; i < el->children.children; i++)
    {
      struct element *child = el->children.child[i];
      element_free (child);

      if (child->children.children != 0)
        {
          move_tool_free (&child);
        }

      free (el->children.child[i]);
      el->children.child[i] = NULL;
    }

  vector_free (&el->children);
  element_free (el);

  free (el);
  el = NULL;
}
