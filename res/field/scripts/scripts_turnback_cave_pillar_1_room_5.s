#include "macros/scrcmd.inc"
#include "res/text/bank/turnback_cave_giratina_room.h"


    ScriptEntry TurnbackCavePillar1Room5_OnTransition
    ScriptEntry TurnbackCavePillar1Room5_CursedBook
    ScriptEntryEnd

TurnbackCavePillar1Room5_OnTransition:
    End

TurnbackCavePillar1Room5_CursedBook:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message TurnbackCaveGiratinaRoom_Text_CursedBook
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, TurnbackCavePillar1Room5_ReadBook
    GoTo TurnbackCavePillar1Room5_BookEnd
    End

TurnbackCavePillar1Room5_ReadBook:
    BufferPlayerName 0
    Message TurnbackCaveGiratinaRoom_Text_CursedBookRead
    WaitButton
    CloseMessage
    PlaySE SEQ_SE_PL_SYUWA
    FadeScreenOut
    WaitFadeScreen
    Warp MAP_HEADER_TURNBACK_CAVE_PILLAR_1_ROOM_3, 0, 25, 16, DIR_SOUTH
    FadeScreenIn
    WaitFadeScreen
    End

TurnbackCavePillar1Room5_BookEnd:
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
