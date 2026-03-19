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