// ============================================================
//  states.h
//  FSM state IDs, action IDs, and the GCS command map type
//  state machine transitions and GCS command.
// ============================================================
#include <Arduino.h>
#include "states.h"
// #include "network.h"
#include "config.h"
#include "actuators.h"
#include <cstdint>

// GCS Command
enum class command : uint8_t {
    STANDBY         = 0x21,
    FILL            = 0x03,
    FILL_N2O        = 0x13,
    FILL_PURGE      = 0x83,
    LAUNCH          = 0x05,
    LAUNCH_O2       = 0x45,
    LAUNCH_O2_FIRE  = 0x4D,
    ESTOP           = 0x00
};

void executeCommand(command cmd)
{
    switch (cmd) {
        case (command::STANDBY):
                set_n2oValve(false);
                set_purge(false);
                set_o2Valve(false);
                set_fire(false);
                set_firePWM(false);
                // set pwm pin LOW
            break;

        case (command::FILL):

            break;
        case (command::FILL_N2O):

            break;
        case (command::FILL_PURGE):

            break;
        case (command::LAUNCH):

            break;
        case (command::LAUNCH_O2):

            break;
        case (command::LAUNCH_O2_FIRE):

            break;
        case (command::ESTOP):

            break;

    }
        
    
}
// Maybe the BYTE_x can be used to obtain an array index and the instructinos can be stored in an array instead of a hash map

/*
System Standby Mode

Fill Mode

Fill->N2O

Fill->Purge

Launch Mode

Launch->O2

Launch->O2->Fire

Estop

*/