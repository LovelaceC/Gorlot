#ifndef __EDITOR_H
#define __EDITOR_H

#include <gorlot.h>

struct editor
{
  struct scene tool_scene;
  struct scene editor_scene;

  Camera3D editor_cam;

  Camera3D *current_cam;
  struct scene *current_scene;
};

struct editor editor_create ();
void editor_free (struct editor *editor);

#endif
