// ============================================================
//  actuators.cpp
//  Solenoid / relay drive functions and ignition spark sequence.
// ============================================================

#include <Arduino.h>
#include "actuators.h"
#include "config.h"

// -----------------------------------------------------------
//  Solenoid helpers
//    Default solenoid states (power-off / de-energised):
//      Purge  solenoid : OPEN   (HIGH closes it)
//      O2     solenoid : CLOSED (HIGH opens it)
//      N2O    solenoid : CLOSED (HIGH opens it)
// -----------------------------------------------------------

// -----------------------------------------------------------
//  attemptIgnition
//    Pulses the spark output NUM_SPARKS times.
// -----------------------------------------------------------
void attemptIgnition() {
    Serial.println("\n- Attempting ignition...");
    for (int i = 0; i < NUM_SPARKS; i++) {
        Serial.print("SPARK\t");
        // digitalWrite(GPIO_PIN_firePWM, HIGH);
        digitalWrite(SPARE_TRG, HIGH);
        digitalWrite(SPARE_ARM, HIGH);
        delay(SPARK_LENGTH);
        // digitalWrite(GPIO_PIN_firePWM, LOW);
        digitalWrite(SPARE_TRG, LOW);
        digitalWrite(SPARE_ARM, LOW);
        delay(SPARK_INTERVAL);
    }
}
// -----------------------------------------------------------
//  emergencyStop
//    Safe-state: close propellant valves, open purge.
// -----------------------------------------------------------
void emergencyStop() {
    Serial.println("[EMERGENCY STOP] Cutting all solenoid outputs.");
    digitalWrite(FILL_ARM, LOW);
    digitalWrite(N2O_TRG, LOW);
    digitalWrite(PURGE_TRG, LOW);
    digitalWrite(SPARE_ARM, LOW);
    digitalWrite(IGN_ARM, LOW);
    digitalWrite(SPARE_TRG, LOW);
    digitalWrite(FIRE_TRG, LOW);
    digitalWrite(FIRE_PWM, LOW);
}