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

void executeCommand(command cmd)
{
    // Deativate everything by default
    // TODO convert to port mask method
    set_n2oValve(DEACTIVATE_PIN);
    set_o2Valve(DEACTIVATE_PIN);
    set_purge(DEACTIVATE_PIN);
    set_fire(DEACTIVATE_PIN);
    set_firePWM(DEACTIVATE_PIN);
    set_fillArmPin(DEACTIVATE_PIN);
    set_ignArmPin(DEACTIVATE_PIN);

    switch (cmd) {
        case (command::SYSTEM_ACTIVE):
                Serial.println("\nSYSTEM_ACTIVE command from GCS run");
            break;

        case (command::FILL):
                set_fillArmPin(ACTIVATE_PIN);
                Serial.println("\nFILL command from GCS run");
            break;
        case (command::FILL_N2O):
                set_n2oValve(ACTIVATE_PIN);
                set_purge(ACTIVATE_PIN);
                set_fillArmPin(ACTIVATE_PIN);
                Serial.println("\nFILL_N2O command from GCS run");
            break;
        case (command::FILL_PURGE):
                set_fillArmPin(ACTIVATE_PIN);
                Serial.println("\nFILL_PURGE command from GCS run");
            break;
        case (command::LAUNCH):
                set_purge(ACTIVATE_PIN);
                set_ignArmPin(ACTIVATE_PIN);
                Serial.println("\nLAUNCH command from GCS run");
            break;
        case (command::LAUNCH_O2):
                set_purge(ACTIVATE_PIN);
                set_o2Valve(ACTIVATE_PIN);
                set_ignArmPin(ACTIVATE_PIN);
                Serial.println("\nLAUNCH_O2 command from GCS run");
            break;
        case (command::LAUNCH_O2_FIRE):
                set_purge(ACTIVATE_PIN);
                set_o2Valve(ACTIVATE_PIN);
                set_fire(ACTIVATE_PIN);
                set_ignArmPin(ACTIVATE_PIN);
                attemptIgnition();
                Serial.println("\nLAUNCH_O2_FIRE command from GCS run");
            break;
        case (command::LAUNCH_FIRE):
                set_purge(ACTIVATE_PIN);
                set_fire(ACTIVATE_PIN);
                set_ignArmPin(ACTIVATE_PIN);
                attemptIgnition();
                Serial.println("\nLAUNCH_FIRE command from GCS run");
            break;

        case (command::ESTOP):
                Serial.println("\nESTOP command from GCS run");
            break;

    }
        
    
}