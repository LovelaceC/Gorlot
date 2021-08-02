#include "input.h"

_Bool
editor_mouse_in_viewport (Vector2 mouse_position)
{
  float x = mouse_position.x;
  float y = mouse_position.y;

  return y > TOPBAR_HEIGHT && x < window_width - OUTLINER_WIDTH;
}
