#include "macros/scrcmd.inc"
#include "res/text/bank/fuego_ironworks_outside.h"


    ScriptEntry FuegoIronworksOutside_Sign
    ScriptEntry FuegoIronworksOutside_Policeman
    ScriptEntry FuegoIronworksOutside_Cameraman
    ScriptEntry FuegoIronworksOutside_InterviewerLeft
    ScriptEntry FuegoIronworksOutside_InterviewerRight
    ScriptEntryEnd

FuegoIronworksOutside_Sign:
    ShowLandmarkSign FuegoIronworksOutside_Text_SignFuegoIronworks
    End

FuegoIronworksOutside_Policeman:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message FuegoIronworksOutside_Text_PolicemanThereIsAnInterview
    WaitButton
    CloseMessage
    ReleaseAll
    End

FuegoIronworksOutside_Cameraman:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message FuegoIronworksOutside_Text_Cameraman
    WaitButton
    CloseMessage
    ReleaseAll
    End

FuegoIronworksOutside_InterviewerLeft:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message FuegoIronworksOutside_Text_InterviewerLeft
    WaitButton
    CloseMessage
    ReleaseAll
    End

FuegoIronworksOutside_InterviewerRight:
    PlaySE SEQ_SE_CONFIRM
    LockAll
    Message FuegoIronworksOutside_Text_InterviewerRight
    WaitButton
    CloseMessage
    ReleaseAll
    End


    .balign 4, 0
