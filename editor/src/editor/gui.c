#include "gui.h"

#include "gui/outliner.h"
#include "gui/topbar.h"

#include "editor.h"

extern struct editor editor;

void
editorgui_draw (struct nk_context **ctx)
{
  topbar_draw (ctx, editor.current_scene);
  outliner_draw (ctx, editor.current_scene);
}
