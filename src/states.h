#pragma once

// ============================================================
//  states.h
//  FSM state IDs, action IDs, and the GCS command map type.
// ============================================================

#include <map>
// using std::map;

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

// --- GCS command map type ---
//  Key   = command byte identifier (TODO: define once GCS protocol is finalised)
//  Value = encoded (state << 8 | action) or a dedicated struct — see notes.
// using GCSCommandMap = map<int, int>;
