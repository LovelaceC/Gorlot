#ifndef __EDITORGUI_TOPBAR_H
#define __EDITORGUI_TOPBAR_H

#include <gorlot.h>
#include <raylib-nuklear.h>

#include "../../config.h"

void topbar_init (struct nk_context **ctx, struct scene *scene);
void topbar_draw (struct nk_context **ctx, struct scene *scene);
void topbar_free (struct nk_context **ctx, struct scene *scene);

#endif
