#include "macros/scrcmd.inc"
#include "res/text/bank/turnback_cave_giratina_room.h"


    ScriptEntry TurnbackCavePillar1Room3_OnTransition
    ScriptEntry TurnbackCavePillar1Room3_CursedBook
    ScriptEntryEnd

TurnbackCavePillar1Room3_OnTransition:
    End

TurnbackCavePillar1Room3_CursedBook:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message TurnbackCaveGiratinaRoom_Text_CursedBook
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, TurnbackCavePillar1Room3_ReadBook
    GoTo TurnbackCavePillar1Room3_BookEnd
    End

TurnbackCavePillar1Room3_ReadBook:
    BufferPlayerName 0
    Message TurnbackCaveGiratinaRoom_Text_CursedBookRead
    WaitButton
    CloseMessage
    PlaySE SEQ_SE_PL_SYUWA
    FadeScreenOut
    WaitFadeScreen
    CheckHasCaughtSpecies SPECIES_UNOWN, VAR_RESULT
    GoToIfEq VAR_RESULT, TRUE, TurnbackCavePillar1Room3_WarpTunnel
    Warp MAP_HEADER_RUIN_MANIAC_CAVE_LONG, 0, 30, 7, DIR_SOUTH
    FadeScreenIn
    WaitFadeScreen
    End

TurnbackCavePillar1Room3_WarpTunnel:
    Warp MAP_HEADER_MANIAC_TUNNEL, 0, 45, 7, DIR_SOUTH
    FadeScreenIn
    WaitFadeScreen
    End

TurnbackCavePillar1Room3_BookEnd:
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
