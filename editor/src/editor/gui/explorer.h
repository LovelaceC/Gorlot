#ifndef __EDITORGUI_EXPLORER_H
#define __EDITORGUI_EXPLORER_H

#include <gorlot.h>
#include <raylib-nuklear.h>

#include "../../config.h"

void explorer_init (struct nk_context **ctx, struct scene *scene);
void explorer_draw (struct nk_context **ctx, struct scene *scene);
void explorer_free (struct nk_context **ctx, struct scene *scene);

#endif
