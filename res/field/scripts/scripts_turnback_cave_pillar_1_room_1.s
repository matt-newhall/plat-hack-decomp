#include "macros/scrcmd.inc"
#include "res/text/bank/turnback_cave_giratina_room.h"


    ScriptEntry TurnbackCavePillar1Room1_OnTransition
    ScriptEntry TurnbackCavePillar1Room1_CursedBook
    ScriptEntryEnd

TurnbackCavePillar1Room1_OnTransition:
    Call TurnbackCavePillar1Room1_IncrementRoomsVisited
    InitTurnbackCave VAR_TURNBACK_CAVE_PILLARS_SEEN, VAR_TURNBACK_CAVE_ROOMS_VISITED
    End

TurnbackCavePillar1Room1_IncrementRoomsVisited:
    AddVar VAR_TURNBACK_CAVE_ROOMS_VISITED, 1
    Return

TurnbackCavePillar1Room1_CursedBook:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message TurnbackCaveGiratinaRoom_Text_CursedBook
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_YES, TurnbackCavePillar1Room1_ReadBook
    GoTo TurnbackCavePillar1Room1_BookEnd
    End

TurnbackCavePillar1Room1_ReadBook:
    BufferPlayerName 0
    Message TurnbackCaveGiratinaRoom_Text_CursedBookRead
    WaitButton
    CloseMessage
    PlaySE SEQ_SE_PL_SYUWA
    FadeScreenOut
    WaitFadeScreen
    CheckHasCaughtSpecies SPECIES_UNOWN, VAR_RESULT
    GoToIfEq VAR_RESULT, TRUE, TurnbackCavePillar1Room1_WarpTunnel
    Warp MAP_HEADER_RUIN_MANIAC_CAVE_LONG, 0, 30, 7, DIR_SOUTH
    FadeScreenIn
    WaitFadeScreen
    End

TurnbackCavePillar1Room1_WarpTunnel:
    Warp MAP_HEADER_MANIAC_TUNNEL, 0, 45, 7, DIR_SOUTH
    FadeScreenIn
    WaitFadeScreen
    End

TurnbackCavePillar1Room1_BookEnd:
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
