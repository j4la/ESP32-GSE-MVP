#pragma once

// ============================================================
//  states.h
//  FSM state IDs, action IDs, and the GCS command map type.
// ============================================================

enum class command : uint8_t {
    SYSTEM_ACTIVE   = 0x01,
    FILL            = 0x23,
    FILL_N2O        = 0x13,
    FILL_PURGE      = 0x83,
    LAUNCH          = 0x05,
    LAUNCH_O2       = 0x45,
    LAUNCH_O2_FIRE  = 0x4D,
    LAUNCH_FIRE     = 0x0D,
    ESTOP           = 0x00
};

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
