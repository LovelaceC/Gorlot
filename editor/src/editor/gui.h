#ifndef __EDITORGUI_H
#define __EDITORGUI_H

#include <raylib-nuklear.h>
#include <stdio.h>

#include <gorlot.h>

#include "../config.h"

struct editor;

void editorgui_init (struct nk_context **ctx, struct editor *editor);
void editorgui_draw (struct nk_context **ctx, struct editor *editor);
void editorgui_free (struct nk_context **ctx, struct editor *editor);

#endif
