#include "editor.h"

struct editor
editor_create ()
{
  struct editor editor;

  editor.editor_cam = (Camera3D){ 0 };
  editor.editor_cam.position = (Vector3){ 10.0f, 10.0f, 10.0f };
  editor.editor_cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
  editor.editor_cam.up = (Vector3){ 0.0f, 1.0f, 0.0 };
  editor.editor_cam.fovy = 45.0f;
  editor.editor_cam.projection = CAMERA_PERSPECTIVE;

  editor.editor_scene = scene_create ();

  editor.current_cam = NULL;
  editor.current_scene = NULL;

  return editor;
}

void
editor_free (struct editor *editor)
{
  scene_free (&editor->tool_scene);
  scene_free (&editor->editor_scene);

  editor->current_cam = NULL;
  editor->current_scene = NULL;
}
