#pragma once

// ============================================================
//  fsm.h
//  Declarations for the ground-support-equipment (GSE) finite
//  state machine and the GCS command dispatcher.
// ============================================================

#include "states.h"

// Current FSM state — readable from anywhere (e.g. TCP handler).
extern int STATE_current;
extern int ACT_current;

// Transition the FSM to STATE, performing ACTION.
// previousState / previousAction are updated in-place.
void switchState(int STATE, int ACTION, int* previousState, int* previousAction);

// Parse and execute a GCS command map entry.
// void GCScommand(GCSCommandMap command, int* previousState, int* previousAction);
