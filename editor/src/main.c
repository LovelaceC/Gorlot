#include <raylib.h>

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include <raylib-nuklear.h>

#include <gorlot.h>

#include "config.h"

#include "editor/editor.h"

#include "utils/input.h"

int
main ()
{
  // TODO: Be able to modify all these Flags manually in the editor, and they
  // are stored in a file that can also be modified manually by the end user.
  SetConfigFlags (FLAG_MSAA_4X_HINT);

  InitWindow (window_width, window_height, "Gorlot");

  struct editor editor = editor_create ();
  editor.current_cam = &editor.editor_cam;
  editor.current_scene = &editor.editor_scene;

  SetCameraMode (editor.editor_cam.cam, CAMERA_FREE);

  struct nk_context *ctx = InitNuklear (10);

  editorgui_init (&ctx, &editor);

  while (!WindowShouldClose ())
    {
      editor_update (&editor, &ctx);

      if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
        {
          Vector2 pos = GetMousePosition ();

          if (editor_mouse_in_viewport (pos)
              && editor.selected_tool == TOOL_SELECT)
            {
              editor.editor_ray = GetMouseRay (pos, editor.editor_cam.cam);

              // Check collision between ray and all scene objects
              for (int i = 0; i < editor.current_scene->elements.children; i++)
                {
                  // TODO: Optimise this?
                  struct element *el
                      = (struct element *)
                            editor.current_scene->elements.child[i];

                  editor.editor_ray_collision
                      = GetRayCollisionModel (editor.editor_ray, el->model);

                  if (editor.editor_ray_collision.hit)
                    {
                      if (editor.selected_element)
                        {
                          // If there's a selected element, deselect that
                          // element and set the current element
                          editor.selected_element->selected = 0;
                          editor.selected_element = NULL;
                        }

                      editor.selected_element = el;
                      el->selected = 1;
                      break; // Leave the for loop
                    }

                  // If no element was clicked, unselect th selected element
                  editor.selected_element = NULL;
                  editor.editor_ray_collision.hit = 0;
                  el->selected = 0;
                }
            }
        }

      BeginDrawing ();
      {
        ClearBackground (BLACK);

        BeginMode3D (editor.current_cam->cam);
        {
          for (int i = 0; i < editor.current_scene->elements.children; i++)
            {
              element_draw (editor.current_scene->elements.child[i]);
            }

          editor_draw_wires (&editor);
          editor_draw_tools (&editor);

          DrawGrid (1000, 1.0f);
        }
        EndMode3D ();

        DrawNuklear (ctx);
        DrawFPS (0, TOPBAR_HEIGHT);
      }
      EndDrawing ();
    }

  editor_free (&editor, &ctx);

  CloseWindow ();

  return 0;
}
