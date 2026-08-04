#include "macros/btlanimcmd.inc"

.data

L_0:
    Func_FadeBg FADE_BG_TYPE_MON_SPRITE, 1, 16, 0, BATTLE_COLOR_WHITE
    Func_FadeBg FADE_BG_TYPE_BASE, 1, 16, 0, BATTLE_COLOR_WHITE
    WaitForAnimTasks
    End
