#include "move_tool.h"

#include "../editor.h"

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

      struct element *x = move_tool->children.child[0];
      struct element *y = move_tool->children.child[1];
      struct element *z = move_tool->children.child[2];

      // TODO: Update move tool scale based on the selected_element's scale

      if (editor->selected_tool == TOOL_MOVE)
        {
          if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
            {
              for (int i = 0; i < move_tool->children.children; i++)
                {
                  struct element *axis = move_tool->children.child[i];

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
