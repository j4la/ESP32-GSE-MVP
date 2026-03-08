// ============================================================
//  states.h
//  FSM state IDs, action IDs, and the GCS command map type
//  state machine transitions and GCS command.
// ============================================================
#include <Arduino.h>
#include "states.h"
#include "config.h"
#include "actuators.h"
#include <cstdint>

// GCS Command
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

void executeCommand(command cmd)
{
    switch (cmd) {
        case (command::SYSTEM_ACTIVE):
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(DEACTIVATE_PIN);
                set_o2Valve(DEACTIVATE_PIN);
                set_fire(DEACTIVATE_PIN);
                set_firePWM(DEACTIVATE_PIN);
            break;

        case (command::FILL):
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(DEACTIVATE_PIN);
                set_o2Valve(DEACTIVATE_PIN);
                set_fire(DEACTIVATE_PIN);
                set_firePWM(DEACTIVATE_PIN);
            break;
        case (command::FILL_N2O):
                set_n2oValve(ACTIVATE_PIN);
                set_purge(ACTIVATE_PIN);
                set_o2Valve(DEACTIVATE_PIN);
                set_fire(DEACTIVATE_PIN);
                set_firePWM(DEACTIVATE_PIN);
            break;
        case (command::FILL_PURGE):
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(DEACTIVATE_PIN);
                set_o2Valve(DEACTIVATE_PIN);
                set_fire(DEACTIVATE_PIN);
                set_firePWM(DEACTIVATE_PIN);

            break;
        case (command::LAUNCH):
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(ACTIVATE_PIN);
                set_o2Valve(DEACTIVATE_PIN);
                set_fire(DEACTIVATE_PIN);
                set_firePWM(DEACTIVATE_PIN);

            break;
        case (command::LAUNCH_O2):
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(ACTIVATE_PIN);
                set_o2Valve(ACTIVATE_PIN);
                set_fire(DEACTIVATE_PIN);
                set_firePWM(DEACTIVATE_PIN);

            break;
        case (command::LAUNCH_O2_FIRE):
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(ACTIVATE_PIN);
                set_o2Valve(ACTIVATE_PIN);
                set_fire(ACTIVATE_PIN);
                attemptIgnition();
                // set_firePWM(false);
            break;
        case (command::LAUNCH_FIRE):
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(ACTIVATE_PIN);
                set_o2Valve(DEACTIVATE_PIN);
                set_fire(ACTIVATE_PIN);
                attemptIgnition();
            break;

        case (command::ESTOP):
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(DEACTIVATE_PIN);
                set_o2Valve(DEACTIVATE_PIN);
                set_fire(DEACTIVATE_PIN);
                set_firePWM(DEACTIVATE_PIN);

            break;

    }
        
    
}

/*
System SYSTEM_ACTIVE Mode

Fill Mode

Fill->N2O

Fill->Purge

Launch Mode

Launch->O2

Launch->O2->Fire

Estop

*/