#ifndef __EDITORGUI_TOPBAR_H
#define __EDITORGUI_TOPBAR_H

#include <gorlot.h>
#include <raylib-nuklear.h>

#include "../../../config.h"

#include "../../editor.h"

void topbar_init ();
void topbar_draw (struct nk_context **ctx, struct editor *editor);
void topbar_free ();

#endif
