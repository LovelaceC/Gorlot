#include <gorlot.h>

struct camera
camera_create ()
{
  struct camera camera = { 0 };

  camera.cam = (Camera3D){ 0 };
  camera.cam.target = (Vector3){ 0.0f, 0.0f, 0.0f };
  camera.cam.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.cam.fovy = 45.0f;
  camera.cam.projection = CAMERA_PERSPECTIVE;

  return camera;
}

void
camera_set_position (struct camera *camera, Vector3 position)
{
  camera->position = position;
  camera->cam.position = position;
}

void
camera_update (struct camera *camera)
{
  UpdateCamera (&camera->cam);
  camera->position = camera->cam.position;

  Matrix view_matrix = GetCameraMatrix (camera->cam);
  Quaternion q = QuaternionFromMatrix (view_matrix);
  Vector3 rot = QuaternionToEuler (q);

  camera->rotation = rot;
}
