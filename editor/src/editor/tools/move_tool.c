#include "move_tool.h"

#include "../editor.h"

static _Bool editing_axis[3] = { 0 };

static _Bool
axis_selected (struct element *axis, struct editor *editor)
{
  // This function checks the axis (and its children) if they were clicked or
  // not.
  _Bool clicked = 0;

  Vector3 position = axis->position;
  position = element_get_final_position (axis);

  editor->editor_ray = GetMouseRay (GetMousePosition (), editor->editor_cam);

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

  // Y Axis
  struct element *y = NULL;
  y = malloc (sizeof (struct element));
  *y = element_create ();

  y->mesh = GenMeshCylinder (0.05f, 1.0f, 32);
  y->color = GREEN;
  y->rotation.y = 90.0f;
  y->scale.y = 1.5f;
  y->model = LoadModelFromMesh (y->mesh);

  // Z Axis
  struct element *z = NULL;
  z = malloc (sizeof (struct element));
  *z = element_create ();

  z->mesh = GenMeshCylinder (0.05f, 1.0f, 32);
  z->color = BLUE;
  z->rotation.x = 90.0f;
  z->scale.z = 1.5f;
  z->model = LoadModelFromMesh (z->mesh);

  element_add_child (el, x);
  element_add_child (el, y);
  element_add_child (el, z);

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

          if (axis_selected (x, editor) && !is_editing_axis ())
            {
              x->color = YELLOW;

              if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
                {
                  editing_axis[0] = 1;
                }
            }
          else
            {
              x->color = RED;
            }

          if (axis_selected (y, editor) && !is_editing_axis ())
            {
              y->color = YELLOW;

              if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
                {
                  editing_axis[1] = 1;
                }
            }
          else
            {
              y->color = GREEN;
            }

          if (axis_selected (z, editor) && !is_editing_axis ())
            {
              z->color = YELLOW;

              if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
                {
                  editing_axis[2] = 1;
                }
            }
          else
            {
              z->color = BLUE;
            }

          if (editing_axis[0])
            {
              // TODO: Move X
              Vector2 mouse_delta = GetMouseDelta ();
              float speed = 0.05f;

              editor->selected_element->position.x
                  -= mouse_delta.x * speed / 1.0f;
              editor->selected_element->position.x
                  -= mouse_delta.y * speed / 1.0f;
            }

          if (editing_axis[1])
            {
              // TODO: Move Y
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
                  -= mouse_delta.y * speed / 1.0f;
              editor->selected_element->position.z
                  -= mouse_delta.x * speed / 1.0f;
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
      element_free (el->children.child[i]);

      free (el->children.child[i]);
      el->children.child[i] = NULL;
    }

  vector_free (&el->children);
  element_free (el);

  free (el);
  el = NULL;
}
