#include "explorer.h"

void
explorer_init ()
{
}

void
explorer_draw (struct nk_context **ctx)
{
  if (nk_begin (*ctx, "Explorer",
                nk_rect (0, window_height - EXPLORER_HEIGHT, EXPLORER_WIDTH,
                         EXPLORER_HEIGHT),
                NK_WINDOW_BORDER))
    {
    }
  nk_end (*ctx);
}

void
explorer_free ()
{
}
