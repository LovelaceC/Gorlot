#include "outliner.h"

struct editor *outliner_editor = NULL;

static void
tree_draw_element (struct nk_context **ctx, struct element *el)
{
  struct nk_rect bounds;
  bounds = nk_widget_bounds (*ctx);

  if (nk_tree_element_push (*ctx, NK_TREE_NODE, "Element", NK_MINIMIZED,
                            &el->selected))
    {
      // TODO: If element has children, draw them here :3
      nk_tree_element_pop (*ctx);
    }

  if (el->selected)
    {
      if (outliner_editor->selected_element
          && outliner_editor->selected_element != el)
        {
          outliner_editor->selected_element->selected = 0;
        }

      outliner_editor->selected_element = el;
    }

  if (nk_contextual_begin (*ctx, 0, nk_vec2 (100, 300), bounds))
    {
      nk_layout_row_dynamic (*ctx, 15, 1);

      // TODO: Make this useful
      if (nk_contextual_item_label (*ctx, "Delete", NK_TEXT_CENTERED))
        {
          vector_delete_child (&outliner_editor->current_scene->elements, el);
          outliner_editor->selected_element = NULL;
        }

      nk_contextual_end (*ctx);
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
      // TODO: Stop using magic numbers
      nk_layout_row_static (*ctx, 250, OUTLINER_WIDTH - 22, 1);

      if (nk_group_begin (*ctx, "Outliner", NK_WINDOW_BORDER))
        {
          // TODO: Scene name
          if (nk_tree_push (*ctx, NK_TREE_NODE, "Scene", NK_MAXIMIZED))
            {
              for (int i = 0; i < scene->elements.children; i++)
                {
                  if (!scene->elements.child[i])
                    {
                      continue;
                    }

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

          nk_layout_row_dynamic (*ctx, 25, 1);
          nk_label (*ctx, "Element", NK_TEXT_LEFT);

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
          nk_label (*ctx, "Rotation:", NK_TEXT_LEFT);
          nk_layout_row_dynamic (*ctx, 25, 3);
          {
            nk_property_float (*ctx, "#x", -360, &selected_element->rotation.x,
                               360, 1.0f, 1.0f);
            nk_property_float (*ctx, "#y", -360, &selected_element->rotation.y,
                               360, 1.0f, 1.0f);
            nk_property_float (*ctx, "#z", -360, &selected_element->rotation.z,
                               360, 1.0f, 1.0f);
          }
          nk_layout_row_dynamic (*ctx, 25, 1);

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

          nk_checkbox_label (*ctx, "Visible", &selected_element->visible);
        }
    }
  nk_end (*ctx);
}

void
outliner_free (struct nk_context **ctx, struct scene *scene)
{
}
