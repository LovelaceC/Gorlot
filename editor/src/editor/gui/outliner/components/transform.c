#include "transform.h"

void
outliner_draw_transform_component (struct editor *editor,
                                   struct nk_context **ctx)
{
  struct element *selected_element = editor->selected_element;

  if (nk_tree_push (*ctx, NK_TREE_TAB, "Transform", NK_MAXIMIZED))
    {
      // ------ POSITION -------
      if (nk_tree_push (*ctx, NK_TREE_NODE, "Position", NK_MAXIMIZED))
        {
          nk_layout_row_dynamic (*ctx, 25, 3);
          {
            nk_property_float (*ctx, "#x", -4294967296,
                               &selected_element->position.x, 4294967296, 1.0f,
                               0.2f);
            nk_property_float (*ctx, "#y", -4294967296,
                               &selected_element->position.y, 4294967296, 1.0f,
                               0.2f);
            nk_property_float (*ctx, "#z", -4294967296,
                               &selected_element->position.z, 4294967296, 1.0f,
                               0.2f);
          }
          nk_tree_pop (*ctx);
        }

      if (nk_tree_push (*ctx, NK_TREE_NODE, "Rotation", NK_MAXIMIZED))
        {
          nk_layout_row_dynamic (*ctx, 25, 3);
          {
            nk_property_float (*ctx, "#x", -360, &selected_element->rotation.x,
                               360, 1.0f, 1.0f);
            nk_property_float (*ctx, "#y", -360, &selected_element->rotation.y,
                               360, 1.0f, 1.0f);
            nk_property_float (*ctx, "#z", -360, &selected_element->rotation.z,
                               360, 1.0f, 1.0f);
          }
          nk_tree_pop (*ctx);
        }

      if (nk_tree_push (*ctx, NK_TREE_NODE, "Scale", NK_MAXIMIZED))
        {
          nk_layout_row_dynamic (*ctx, 25, 3);
          {
            nk_property_float (*ctx, "#x", -4294967296,
                               &selected_element->scale.x, 4294967296, 1.0f,
                               0.2f);
            nk_property_float (*ctx, "#y", -4294967296,
                               &selected_element->scale.y, 4294967296, 1.0f,
                               0.2f);
            nk_property_float (*ctx, "#z", -4294967296,
                               &selected_element->scale.z, 4294967296, 1.0f,
                               0.2f);
          }
          nk_tree_pop (*ctx);
        }

      nk_checkbox_label (*ctx, "Invisible", &selected_element->visible);

      nk_tree_pop (*ctx);
    }
}
