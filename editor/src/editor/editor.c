#include "editor.h"

struct editor
editor_create ()
{
  struct editor editor;

  editor.editor_scene = scene_create ();

  editor.selected_tool = TOOL_MOVE; // By default, here it must be select

  editor.move_tool = move_tool ();
  // TODO: The other tools

  editor.wires = element_create_primitive (PRIMITIVE_CUBE);
  editor.wires.position = (Vector3){ 0.0f, 1000000.f, 0.0f };
  editor.wires.visible = 0;
  editor.wires.color = Fade (LIME, 0.3f);

  editor.editor_cam = (Camera3D){ 0 };
  editor.editor_cam.position = (Vector3){ 10.0f, 10.0f, 10.0f };
  editor.editor_cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
  editor.editor_cam.up = (Vector3){ 0.0f, 1.0f, 0.0 };
  editor.editor_cam.fovy = 45.0f;
  editor.editor_cam.projection = CAMERA_PERSPECTIVE;

  editor.editor_ray = (Ray){ 0 };
  editor.editor_ray_collision = (RayCollision){ 0 };

  editor.current_cam = NULL;
  editor.current_scene = NULL;

  editor.selected_element = NULL;

  return editor;
}

void
editor_draw_wires (struct editor *editor)
{
  if (editor->selected_element)
    {
      editor->wires.position = editor->selected_element->position;
      editor->wires.scale
          = (Vector3){ editor->selected_element->scale.x + 0.2f,
                       editor->selected_element->scale.y + 0.2f,
                       editor->selected_element->scale.z + 0.2f };
      editor->wires.visible = 1;
      element_update (&editor->wires);
      element_draw (&editor->wires);
    }
}

void
editor_draw_tools (struct editor *editor)
{
  if (editor->selected_element)
    {
      switch (editor->selected_tool)
        {
          // TODO: Draw tools here
        case TOOL_MOVE:
          editor->move_tool.position = editor->selected_element->position;
          struct element *el = editor->move_tool.children.child[0];
          // editor->move_tool.children.child[0]->rotation =

          // element_update (&editor->move_tool);
          element_draw (&editor->move_tool);
          break;
        case TOOL_ROTATE:
          break;
        case TOOL_SCALE:
          break;
        default:
          break;
        }
    }
}

void
editor_free (struct editor *editor)
{
  scene_free (&editor->editor_scene);

  editor->current_cam = NULL;
  editor->current_scene = NULL;
}
