#include "gui.h"

#include "gui/outliner.h"
#include "gui/topbar.h"

extern struct scene scene;

void
editorgui_draw (struct nk_context **ctx)
{
  topbar_draw (ctx, &scene);
  outliner_draw (ctx, &scene);
}
