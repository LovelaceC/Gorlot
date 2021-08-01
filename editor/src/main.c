#include <raylib.h>

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include <raylib-nuklear.h>

#include <gorlot.h>

#include "config.h"

#include "editor/gui.h"

struct scene scene;

int
main ()
{
  InitWindow (window_width, window_height, "Gorlot");

  Camera3D camera = { 0 };
  camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  SetCameraMode (camera, CAMERA_FREE);

  SetTargetFPS (60);

  scene = scene_create ();

  struct nk_context *ctx = InitNuklear (10);

  while (!WindowShouldClose ())
    {
      UpdateCamera (&camera);
      UpdateNuklear (ctx);

      editorgui_draw (&ctx);

      scene_update (&scene);

      BeginDrawing ();
      {
        ClearBackground (BLACK);

        BeginScissorMode (0, TOPBAR_HEIGHT, window_width - OUTLINER_WIDTH,
                          window_height);

        BeginMode3D (camera);
        {
          for (int i = 0; i < scene.elements.children; i++)
            {
              element_draw (scene.elements.child[i]);
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

  UnloadNuklear (ctx);
  CloseWindow ();

  return 0;
}
