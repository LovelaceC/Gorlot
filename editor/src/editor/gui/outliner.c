#include "outliner.h"

static void
tree_draw_element (struct nk_context **ctx, struct element *el)
{
  if (nk_tree_element_push (*ctx, NK_TREE_NODE, el->name, NK_MINIMIZED,
                            &el->selected))
    {
      // TODO: If element has children, draw them here :3
      nk_tree_element_pop (*ctx);
    }
}

void
outliner_init (struct nk_context **ctx, struct scene *scene)
{
}

void
outliner_draw (struct nk_context **ctx, struct scene *scene)
{
  if (nk_begin (*ctx, "Outliner",
                nk_rect (window_width - OUTLINER_WIDTH, TOPBAR_HEIGHT,
                         OUTLINER_WIDTH, window_height - TOPBAR_HEIGHT),
                NK_WINDOW_BORDER))
    {
      nk_layout_row_static (*ctx, 250, OUTLINER_WIDTH - 22, 1);

      if (nk_group_begin (*ctx, "Outliner", NK_WINDOW_BORDER))
        {
          // TODO: Scene name
          if (nk_tree_push (*ctx, NK_TREE_NODE, "Scene", NK_MAXIMIZED))
            {
              for (int i = 0; i < scene->elements.children; i++)
                {
                  tree_draw_element (ctx, scene->elements.child[i]);
                }

              nk_tree_pop (*ctx);
            }
          nk_group_end (*ctx);
        }

      // TODO: Selected object components
    }
  nk_end (*ctx);
}

void
outliner_free (struct nk_context **ctx, struct scene *scene)
{
}
