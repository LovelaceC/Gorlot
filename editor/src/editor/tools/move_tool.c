#include "move_tool.h"

#include "../editor.h"

struct element *
move_tool ()
{
  // TODO: Draw cones at the end of the each axis
  struct element *el = NULL;
  el = malloc (sizeof (struct element));
  *el = element_create ();

  Mesh cylinder = GenMeshCylinder (0.05f, 1.0f, 32);

  // X Axis
  struct element *x = NULL;
  x = malloc (sizeof (struct element));
  *x = element_create ();

  x->color = RED;
  x->rotation.z = 90.0f;
  x->scale.x = 1.5f;
  x->model = LoadModelFromMesh (cylinder);

  // Y Axis
  struct element *y = NULL;
  y = malloc (sizeof (struct element));
  *y = element_create ();

  y->color = GREEN;
  y->rotation.y = 90.0f;
  y->scale.y = 1.5f;
  y->model = LoadModelFromMesh (cylinder);

  // Z Axis
  struct element *z = NULL;
  z = malloc (sizeof (struct element));
  *z = element_create ();

  z->color = BLUE;
  z->rotation.x = 90.0f;
  z->scale.z = 1.5f;
  z->model = LoadModelFromMesh (cylinder);

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

      // TODO: Update move tool scale based on the selected_element's scale
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
