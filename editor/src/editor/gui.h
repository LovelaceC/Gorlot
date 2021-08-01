#ifndef __EDITORGUI_H
#define __EDITORGUI_H

#include <raylib-nuklear.h>
#include <stdio.h>

#include <gorlot.h>

#include "../config.h"

void editorgui_init (struct nk_context **ctx);
void editorgui_draw (struct nk_context **ctx);
void editorgui_free (struct nk_context **ctx);

#endif
