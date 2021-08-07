#ifndef __ROTATE_TOOL_H
#define __ROTATE_TOOL_H

#include <gorlot.h>

struct editor;

struct element *rotate_tool ();
void rotate_tool_update (struct editor *editor, struct element *rotate_tool);
void rotate_tool_free (struct element **rotate_tool);

#endif
