#ifndef __MOVE_TOOL_H
#define __MOVE_TOOL_H

#include <gorlot.h>

struct editor;

struct element *move_tool ();
void move_tool_update (struct editor *editor, struct element *move_tool);
void move_tool_free (struct element **move_tool);

#endif
