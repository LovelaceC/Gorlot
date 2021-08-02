#include "gui.h"

#include "gui/explorer.h"
#include "gui/outliner.h"
#include "gui/topbar.h"

#include "editor.h"

extern struct editor editor;

void
editorgui_init (struct nk_context **ctx)
{
  topbar_init (ctx, editor.current_scene);
  outliner_init (ctx, editor.current_scene);
  explorer_init (ctx, editor.current_scene);
}

void
editorgui_draw (struct nk_context **ctx)
{
  topbar_draw (ctx, editor.current_scene);
  outliner_draw (ctx, editor.current_scene);
  explorer_draw (ctx, editor.current_scene);
}

void
editorgui_free (struct nk_context **ctx)
{
  topbar_free (ctx, editor.current_scene);
  outliner_free (ctx, editor.current_scene);
  explorer_free (ctx, editor.current_scene);
}
