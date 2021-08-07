#ifndef __EDITOR_H
#define __EDITOR_H

#include <gorlot.h>

#include <raylib-nuklear.h>

#include "gui.h"

#include "tools/move_tool.h"
#include "tools/scale_tool.h"

enum tools
{
  TOOL_SELECT,
  TOOL_MOVE,
  TOOL_ROTATE,
  TOOL_SCALE
};

struct editor
{
  struct scene editor_scene;

  enum tools selected_tool;
  struct element *current_tool;

  // Tools
  struct element *move_tool;
  struct element *rotate_tool;
  struct element *scale_tool;

  Camera3D editor_cam;

  Camera3D *current_cam;
  struct scene *current_scene;

  Ray editor_ray;
  RayCollision editor_ray_collision;

  struct element *selected_element;
};

struct editor editor_create ();
void editor_update (struct editor *editor, struct nk_context **ctx);
void editor_draw_wires (struct editor *editor);
void editor_draw_tools (struct editor *editor);
void editor_free (struct editor *editor, struct nk_context **ctx);

#endif
