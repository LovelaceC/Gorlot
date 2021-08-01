#ifndef __EDITORGUI_OUTLINER_H
#define __EDITORGUI_OUTLINER_H

#include <gorlot.h>
#include <raylib-nuklear.h>

#include "../../config.h"

void outliner_init (struct nk_context **ctx, struct scene *scene);
void outliner_draw (struct nk_context **ctx, struct scene *scene);
void outliner_free (struct nk_context **ctx, struct scene *scene);

#endif
