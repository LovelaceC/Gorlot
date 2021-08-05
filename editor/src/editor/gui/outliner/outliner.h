#ifndef __EDITORGUI_OUTLINER_H
#define __EDITORGUI_OUTLINER_H

#include <gorlot.h>
#include <raylib-nuklear.h>

#include "../../../config.h"
#include "../../editor.h"

#include "context.h"

void outliner_init ();
void outliner_draw (struct nk_context **ctx, struct editor *editor);
void outliner_free ();

#endif
