#include "editor.h"

struct editor
editor_create ()
{
  struct editor editor;

  editor.editor_scene = scene_create ();

  editor.selected_tool = TOOL_SELECT;
  editor.current_tool = NULL;

  editor.move_tool = move_tool ();
  editor.scale_tool = scale_tool ();
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
editor_update (struct editor *editor, struct nk_context **ctx)
{
  UpdateCamera (editor->current_cam);
  UpdateNuklear (*ctx);

  if (editor->selected_element && !editor->selected_element->selected)
    {
      editor->selected_element = NULL;
    }

  // TODO: Move the editor select here?

  editorgui_draw (ctx, editor);
  scene_update (editor->current_scene);

  // TODO: Update all the other tools here :3
  move_tool_update (editor, editor->move_tool);
  scale_tool_update (editor, editor->scale_tool);
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
          element_draw (editor->move_tool);
          break;
        case TOOL_SCALE:
          element_draw (editor->scale_tool);
          break;
        case TOOL_ROTATE:
          break;
        default:
          break;
        }
    }
}

void
editor_free (struct editor *editor, struct nk_context **ctx)
{
  // Clean the scene
  scene_free (&editor->editor_scene);

  // Clean tools
  move_tool_free (&editor->move_tool);
  scale_tool_free (&editor->scale_tool);

  // Set some pointers to NULL
  editor->current_tool = NULL;
  editor->current_cam = NULL;
  editor->current_scene = NULL;
  editor->selected_element = NULL;

  // Free the editorgui and Nuklear
  editorgui_free (ctx, editor);
  UnloadNuklear (*ctx);
}
