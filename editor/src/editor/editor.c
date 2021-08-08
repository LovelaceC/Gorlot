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
  editor.rotate_tool = rotate_tool ();

  editor.editor_cam = (Camera3D){ 0 };
  editor.editor_cam.position = (Vector3){ 10.0f, 10.0f, -10.0f };
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

  // Update tools
  move_tool_update (editor, editor->move_tool);
  scale_tool_update (editor, editor->scale_tool);
  rotate_tool_update (editor, editor->rotate_tool);
}

void
editor_draw_wires (struct editor *editor)
{
  if (editor->selected_element)
    {
      Vector3 scale = editor->selected_element->scale;
      DrawCubeWires (editor->selected_element->position, scale.x, scale.y,
                     scale.z, YELLOW);
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
          element_draw (editor->rotate_tool);
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
  rotate_tool_free (&editor->rotate_tool);

  editor->move_tool = NULL;
  editor->scale_tool = NULL;
  editor->rotate_tool = NULL;

  // Set some pointers to NULL
  editor->current_tool = NULL;
  editor->current_cam = NULL;
  editor->current_scene = NULL;
  editor->selected_element = NULL;

  // Free the editorgui and Nuklear
  editorgui_free (ctx, editor);
  UnloadNuklear (*ctx);
}
