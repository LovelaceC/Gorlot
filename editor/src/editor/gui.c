#include "gui.h"

#include "gui/explorer.h"
#include "gui/outliner.h"
#include "gui/topbar.h"

void
editorgui_init (struct nk_context **ctx, struct editor *editor)
{
  topbar_init (ctx, editor->current_scene);
  outliner_init (ctx, editor->current_scene, editor);
  explorer_init (ctx, editor->current_scene);
}

void
editorgui_draw (struct nk_context **ctx, struct editor *editor)
{
  topbar_draw (ctx, editor->current_scene);
  outliner_draw (ctx, editor->current_scene);
  explorer_draw (ctx, editor->current_scene);
}

void
editorgui_free (struct nk_context **ctx, struct editor *editor)
{
  topbar_free (ctx, editor->current_scene);
  outliner_free (ctx, editor->current_scene);
  explorer_free (ctx, editor->current_scene);
}
