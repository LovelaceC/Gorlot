#include <raylib.h>

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include <raylib-nuklear.h>

#include <gorlot.h>

#include "config.h"

#include "editor/editor.h"
#include "editor/gui.h"

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
