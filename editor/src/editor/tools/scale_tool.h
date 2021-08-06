#ifndef __SCALE_TOOL_H
#define __SCALE_TOOL_H

#include <gorlot.h>

struct editor;

struct element *scale_tool ();
void scale_tool_update (struct editor *editor, struct element *scale_tool);
void scale_tool_free (struct element **scale_tool);

#endif
