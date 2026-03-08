#pragma once

// ============================================================
//  states.h
//  FSM state IDs, action IDs, and the GCS command map type.
// ============================================================

void executeCommand(command cmd);

// --- FSM States ---
enum State {
    STATE_standby    = 0,
    STATE_fuelActive = 1,
    STATE_ignActive  = 2,
};

// --- FSM Actions ---
enum Action {
    ACT_neutral = 0,
    ACT_fill    = 1,
    ACT_purge   = 2,
    ACT_fire    = 3,
    ACT_O2      = 4,
};