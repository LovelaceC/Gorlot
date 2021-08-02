#include "outliner.h"
#include <raylib.h>

struct editor *outliner_editor = NULL;

static void
tree_draw_element (struct nk_context **ctx, struct element *el)
{
  if (nk_tree_element_push (*ctx, NK_TREE_NODE, el->name, NK_MINIMIZED,
                            &el->selected))
    {
      // TODO: If element has children, draw them here :3
      nk_tree_element_pop (*ctx);
    }

  if (el->selected)
    {
      outliner_editor->selected_element = el;
    }
}

void
outliner_init (struct nk_context **ctx, struct scene *scene,
               struct editor *editor)
{
  outliner_editor = editor;
}

void
outliner_draw (struct nk_context **ctx, struct scene *scene)
{
  if (nk_begin (*ctx, "Outliner",
                nk_rect (window_width - OUTLINER_WIDTH, TOPBAR_HEIGHT,
                         OUTLINER_WIDTH, window_height - TOPBAR_HEIGHT),
                NK_WINDOW_BORDER))
    {
      // TODO: Stop using maging numbers
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

      const float ratio[] = { OUTLINER_WIDTH - 22, OUTLINER_HEIGHT - 300 };

      // TODO: Selected object components
      if (outliner_editor->selected_element)
        {
          // TODO: Move this to another file?
          struct element *selected_element = outliner_editor->selected_element;

          // nk_layout_row (*ctx, NK_STATIC, 25, 2, ratio);
          nk_layout_row_dynamic (*ctx, 25, 1);
          nk_label (*ctx, TextFormat ("Editing %s", selected_element->name),
                    NK_TEXT_LEFT);

          // TODO: Check when the name is being modified and clear it, and
          // assign the new value.
          /*nk_label (*ctx, "Name:", NK_TEXT_LEFT);
          nk_edit_string (
              *ctx, NK_EDIT_SIMPLE, buf, &selected_element->name_len,
              sizeof (selected_element->name) - 1, nk_filter_default);*/

          nk_label (*ctx, "Position:", NK_TEXT_LEFT);
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
          nk_layout_row_dynamic (*ctx, 25, 1);

          // TODO: Rotation
          /*nk_label (*ctx, "Rotation:", NK_TEXT_LEFT);
          nk_layout_row_dynamic (*ctx, 25, 3);
          {
            nk_property_float (*ctx, "#x", -4294967296,
                               &selected_element->rotation.x, 4294967296, 1.0f,
                               0.2f);
            nk_property_float (*ctx, "#y", -4294967296,
                               &selected_element->rotation.y, 4294967296, 1.0f,
                               0.2f);
            nk_property_float (*ctx, "#z", -4294967296,
                               &selected_element->rotation.z, 4294967296, 1.0f,
                               0.2f);
          }
          nk_layout_row_dynamic (*ctx, 25, 1);*/

          nk_label (*ctx, "Scale:", NK_TEXT_LEFT);
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
          nk_layout_row_dynamic (*ctx, 25, 1);
        }
    }
  nk_end (*ctx);
}

void
outliner_free (struct nk_context **ctx, struct scene *scene)
{
}
