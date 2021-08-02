#include <raylib.h>

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include <raylib-nuklear.h>

#include <gorlot.h>

#include "config.h"

#include "editor/editor.h"
#include "editor/gui.h"

#include "utils/input.h"

struct editor editor;

int
main ()
{
  InitWindow (window_width, window_height, "Gorlot");

  editor = editor_create ();
  editor.current_cam = &editor.editor_cam;
  editor.current_scene = &editor.editor_scene;

  SetCameraMode (editor.editor_cam, CAMERA_FREE);

  SetTargetFPS (60);

  struct nk_context *ctx = InitNuklear (10);

  editorgui_init (&ctx);

  while (!WindowShouldClose ())
    {
      UpdateCamera (editor.current_cam);
      UpdateNuklear (ctx);

      editorgui_draw (&ctx);

      if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT))
        {
          Vector2 pos = GetMousePosition ();

          if (editor_mouse_in_viewport (pos))
            {
              editor.editor_ray = GetMouseRay (pos, editor.editor_cam);

              // Check collision between ray and all scene objects
              for (int i = 0; i < editor.current_scene->elements.children; i++)
                {
                  // TODO: Optimise this?
                  struct element *el
                      = (struct element *)
                            editor.current_scene->elements.child[i];

                  Vector3 pos = el->position;
                  Vector3 scale = el->scale;

                  editor.editor_ray_collision = GetRayCollisionBox (
                      editor.editor_ray,
                      (BoundingBox){
                          (Vector3){ pos.x - scale.x / 2, pos.y - scale.y / 2,
                                     pos.z - scale.z / 2 },
                          (Vector3){ pos.x + scale.x / 2, pos.y + scale.y / 2,
                                     pos.z + scale.z / 2 } });

                  if (editor.editor_ray_collision.hit)
                    {
                      el->selected = 1;
                      break; // Leave the for loop
                    }

                  el->selected = 0;
                }
            }
        }

      scene_update (editor.current_scene);

      BeginDrawing ();
      {
        ClearBackground (BLACK);

        BeginScissorMode (0, TOPBAR_HEIGHT, window_width - OUTLINER_WIDTH,
                          window_height);

        BeginMode3D (*editor.current_cam);
        {
          for (int i = 0; i < editor.current_scene->elements.children; i++)
            {
              element_draw (editor.current_scene->elements.child[i]);
            }

          DrawGrid (1000, 1.0f);
        }
        EndMode3D ();

        EndScissorMode ();

        DrawFPS (0, 0);
        DrawNuklear (ctx);
      }
      EndDrawing ();
    }

  editorgui_free (&ctx);

  UnloadNuklear (ctx);
  CloseWindow ();

  return 0;
}
