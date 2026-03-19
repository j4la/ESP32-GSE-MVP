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
    digitalWrite(N2O_TRG, LOW);
    digitalWrite(O2_TRG, LOW);
    digitalWrite(FIRE_TRG, LOW);
    digitalWrite(FIRE_PWM, LOW);
    digitalWrite(FILL_ARM, LOW);
    digitalWrite(IGN_ARM, LOW);
    digitalWrite(SPARE_ARM, LOW);
    digitalWrite(SPARE_TRG, LOW);

    switch (cmd) {
        case (command::SYSTEM_ACTIVE):
                digitalWrite(PURGE_TRG, HIGH);
                digitalWrite(FILL_ARM, HIGH);
                Serial.println("\nSYSTEM_ACTIVE run");
            break;

        case (command::FILL):
                digitalWrite(FILL_ARM, HIGH);
                digitalWrite(PURGE_TRG, HIGH);
                Serial.println("\nFILL run");
            break;
        case (command::FILL_N2O):
                digitalWrite(FILL_ARM, HIGH);
                digitalWrite(PURGE_TRG, HIGH);
                digitalWrite(N2O_TRG, HIGH);
                Serial.println("\nFILL_N2O run");
            break;
        case (command::FILL_PURGE):
                digitalWrite(PURGE_TRG, LOW);
                digitalWrite(FILL_ARM, HIGH);
                Serial.println("\nFILL_PURGE run");
            break;
        case (command::LAUNCH):
                digitalWrite(PURGE_TRG, HIGH);
                digitalWrite(FILL_ARM, HIGH);
                digitalWrite(IGN_ARM, HIGH);
                Serial.println("\nLAUNCH run");
            break;
        case (command::LAUNCH_O2):
                digitalWrite(PURGE_TRG, HIGH);
                digitalWrite(FILL_ARM, HIGH);
                digitalWrite(O2_TRG, HIGH);
                digitalWrite(IGN_ARM, HIGH);
                Serial.println("\nLAUNCH_O2 run");
            break;
        case (command::LAUNCH_O2_FIRE):
                digitalWrite(PURGE_TRG, HIGH);
                digitalWrite(FILL_ARM, HIGH);
                digitalWrite(IGN_ARM, HIGH);
                digitalWrite(O2_TRG, HIGH);
                attemptIgnition();
                Serial.println("\nLAUNCH_O2_FIRE run");
            break;
        case (command::LAUNCH_FIRE):
                digitalWrite(PURGE_TRG, HIGH);  
                digitalWrite(FILL_ARM, HIGH);              
                digitalWrite(IGN_ARM, HIGH);
                attemptIgnition();
                Serial.println("\nLAUNCH_FIRE run");
            break;

        case (command::ESTOP):
                Serial.println("\nESTOP run");
                emergencyStop();
            break;

    }
        
    
}