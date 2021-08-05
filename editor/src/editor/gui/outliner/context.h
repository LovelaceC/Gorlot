#ifndef __OUTLINER_CTX_H
#define __OUTLINER_CTX_H

#include <gorlot.h>
#include <raylib-nuklear.h>

#include "../../editor.h"

void outliner_ctx (struct editor *editor, struct nk_context **ctx,
                   struct element *el, struct nk_rect bounds);

#endif
