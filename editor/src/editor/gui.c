#include "gui.h"

#include "gui/explorer/explorer.h"
#include "gui/outliner/outliner.h"
#include "gui/topbar/topbar.h"

void
editorgui_init (struct nk_context **ctx, struct editor *editor)
{
  topbar_init ();
  outliner_init ();
  explorer_init ();
}

void
editorgui_draw (struct nk_context **ctx, struct editor *editor)
{
  topbar_draw (ctx, editor);
  outliner_draw (ctx, editor);
  explorer_draw (ctx);
}

void
editorgui_free (struct nk_context **ctx, struct editor *editor)
{
  topbar_free ();
  outliner_free ();
  explorer_free ();
}
