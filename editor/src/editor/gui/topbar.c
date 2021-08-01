#include "topbar.h"

void
topbar_draw (struct nk_context **ctx, struct scene *scene)
{
  if (nk_begin (*ctx, "Menubar", nk_rect (0, 0, window_width, 30),
                NK_WINDOW_BORDER))
    {
      nk_menubar_begin (*ctx);
      nk_layout_row_begin (*ctx, NK_STATIC, 18, 5);

      nk_layout_row_push (*ctx, 45);
      if (nk_menu_begin_label (*ctx, "File", NK_TEXT_LEFT, nk_vec2 (120, 200)))
        {
          nk_layout_row_dynamic (*ctx, 18, 1);

          if (nk_menu_item_label (*ctx, "New", NK_TEXT_LEFT))
            {
              printf ("TODO: New.\n");
            }

          if (nk_menu_item_label (*ctx, "Save", NK_TEXT_LEFT))
            {
              printf ("TODO: Save.\n");
            }

          if (nk_menu_item_label (*ctx, "Save As", NK_TEXT_LEFT))
            {
              printf ("TODO: Save As.\n");
            }

          if (nk_menu_item_label (*ctx, "Open", NK_TEXT_LEFT))
            {
              printf ("TODO: Open.\n");
            }

          if (nk_menu_item_label (*ctx, "Export", NK_TEXT_LEFT))
            {
              printf ("TODO: Export project.\n");
            }

          nk_menu_end (*ctx);
        }

      nk_layout_row_push (*ctx, 60);
      if (nk_menu_begin_label (*ctx, "Edit", NK_TEXT_LEFT, nk_vec2 (120, 200)))
        {
          nk_layout_row_dynamic (*ctx, 18, 1);

          if (nk_menu_item_label (*ctx, "Undo", NK_TEXT_LEFT))
            {
              printf ("TODO: Undo.\n");
            }

          if (nk_menu_item_label (*ctx, "Redo", NK_TEXT_LEFT))
            {
              printf ("TODO: Redo.\n");
            }

          if (nk_menu_item_label (*ctx, "Copy", NK_TEXT_LEFT))
            {
              printf ("TODO: Copy.\n");
            }

          if (nk_menu_item_label (*ctx, "Paste", NK_TEXT_LEFT))
            {
              printf ("TODO: Paste.\n");
            }

          if (nk_menu_item_label (*ctx, "Delete", NK_TEXT_LEFT))
            {
              printf ("TODO: Delete.\n");
            }

          nk_menu_end (*ctx);
        }

      nk_layout_row_push (*ctx, 60);
      if (nk_menu_begin_label (*ctx, "Add", NK_TEXT_LEFT, nk_vec2 (120, 200)))
        {
          nk_layout_row_dynamic (*ctx, 18, 1);

          // TODO: Free all these elements' memory
          if (nk_menu_item_label (*ctx, "Cube", NK_TEXT_ALIGN_LEFT))
            {
              struct element *el = NULL;
              el = malloc (sizeof (struct element));
              *el = element_create_primitive (PRIMITIVE_CUBE);
              scene_add_element (scene, el);
            }

          if (nk_menu_item_label (*ctx, "Cylinder", NK_TEXT_ALIGN_LEFT))
            {
              printf ("TODO: Add cylinder.\n");
            }

          if (nk_menu_item_label (*ctx, "Sphere", NK_TEXT_ALIGN_LEFT))
            {
              printf ("TODO: Add sphere.\n");
            }

          if (nk_menu_item_label (*ctx, "Torus", NK_TEXT_ALIGN_LEFT))
            {
              printf ("TODO: Add torus.\n");
            }

          if (nk_menu_item_label (*ctx, "Cone", NK_TEXT_ALIGN_LEFT))
            {
              printf ("TODO: Add cone.\n");
            }

          nk_menu_end (*ctx);
        }

      nk_layout_row_end (*ctx);
      nk_menubar_end (*ctx);
    }

  nk_end (*ctx);
}
