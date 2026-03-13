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
    set_fire(DEACTIVATE_PIN);
    set_firePWM(DEACTIVATE_PIN);
    set_fillArmPin(DEACTIVATE_PIN);
    set_ignArmPin(DEACTIVATE_PIN);

    switch (cmd) {
        case (command::SYSTEM_ACTIVE):
                set_purge(ACTIVATE_PIN);
                digitalWrite(FILL_ARM, HIGH);
                Serial.println("\nSYSTEM_ACTIVE run");
            break;

        case (command::FILL):
                set_purge(ACTIVATE_PIN);
                set_fillArmPin(ACTIVATE_PIN);
                Serial.println("\nFILL run");
            break;
        case (command::FILL_N2O):
                set_purge(ACTIVATE_PIN);
                // delay(1000);
                set_n2oValve(ACTIVATE_PIN);
                set_fillArmPin(ACTIVATE_PIN);
                // Need to cahnge the deactivate purge pin at start of this function as this means n2o valve 
                // wont be open for long, literally until next packet is received and this function is called again
                // as all pins are deactivated everytime this function is run
                Serial.println("\nFILL_N2O run");
            break;
        case (command::FILL_PURGE):
                set_purge(DEACTIVATE_PIN);
                set_fillArmPin(ACTIVATE_PIN);
                Serial.println("\nFILL_PURGE run");
            break;
        case (command::LAUNCH):
                set_purge(ACTIVATE_PIN);
                set_fillArmPin(ACTIVATE_PIN);
                set_ignArmPin(ACTIVATE_PIN);
                Serial.println("\nLAUNCH run");
            break;
        case (command::LAUNCH_O2):
                set_purge(ACTIVATE_PIN);
                set_fillArmPin(ACTIVATE_PIN);
                set_o2Valve(ACTIVATE_PIN);
                set_ignArmPin(ACTIVATE_PIN);
                Serial.println("\nLAUNCH_O2 run");
            break;
        case (command::LAUNCH_O2_FIRE):
                digitalWrite(PURGE_TRG, HIGH);
                digitalWrite(FILL_ARM, HIGH);
                digitalWrite(O2_TRG, HIGH);
                digitalWrite(IGN_ARM, HIGH);
                digitalWrite(SPARE_ARM, HIGH);
                digitalWrite(SPARE_TRG, HIGH);

                // set_purge(ACTIVATE_PIN);
                // set_o2Valve(ACTIVATE_PIN);
                // set_fire(ACTIVATE_PIN);
                // set_ignArmPin(ACTIVATE_PIN);
                attemptIgnition();
                Serial.println("\nLAUNCH_O2_FIRE run");
            break;
        case (command::LAUNCH_FIRE):
                set_purge(ACTIVATE_PIN);
                digitalWrite(FILL_ARM, HIGH);
                digitalWrite(SPARE_ARM, HIGH);
                digitalWrite(SPARE_TRG, HIGH);
                set_ignArmPin(ACTIVATE_PIN);
                attemptIgnition();
                Serial.println("\nLAUNCH_FIRE run");
            break;

        case (command::ESTOP):
                Serial.println("\nESTOP run");
                emergencyStop();
            break;

    }
        
    
}