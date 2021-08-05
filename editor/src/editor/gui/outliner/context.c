#include "context.h"

void
outliner_ctx (struct editor *editor, struct nk_context **ctx,
              struct element *el, struct nk_rect bounds)
{
  if (nk_contextual_begin (*ctx, 0, nk_vec2 (100, 300), bounds))
    {
      nk_layout_row_dynamic (*ctx, 15, 1);

      // TODO: Make this useful
      if (nk_contextual_item_label (*ctx, "Delete", NK_TEXT_CENTERED))
        {
          vector_delete_child (&editor->current_scene->elements, el);
          UnloadModel (el->model);

          editor->selected_element = NULL;
        }

      nk_contextual_end (*ctx);
    }
}
