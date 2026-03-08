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

void inline set_n2oValve(bool activate) {
    // HIGH = open, LOW = closed
    digitalWrite(GPIO_PIN_n2oValve, activate ? HIGH : LOW);
}

void inline set_o2Valve(bool activate) {
    // HIGH = open, LOW = closed
    digitalWrite(GPIO_PIN_o2Valve, activate ? HIGH : LOW);
}

void inline set_purge(bool activate) {
    // HIGH = closed, LOW = open  (inverted — normally-open valve)
    digitalWrite(GPIO_PIN_purge, activate ? HIGH : LOW);
}

void inline set_fire(bool activate) {
    digitalWrite(GPIO_PIN_fire, activate ? HIGH : LOW);
}

void inline set_firePWM(bool activate){
    digitalWrite(GPIO_PIN_firePWM, activate ? HIGH : LOW);
}

// -----------------------------------------------------------
//  AttemptIgnition
//    Pulses the spark output NUM_SPARKS times.
// i hop ehtis works
// -----------------------------------------------------------
void AttemptIgnition() {
    Serial.println("- Attempting ignition...");
    for (int i = 0; i < NUM_SPARKS; i++) {
        Serial.println("SPARK");
        digitalWrite(GPIO_PIN_firePWM, HIGH);
        delay(SPARK_LENGTH);
        digitalWrite(GPIO_PIN_firePWM, LOW);
        delay(SPARK_INTERVAL);
    }
}

// -----------------------------------------------------------
//  emergencyStop
//    Safe-state: close propellant valves, open purge.
// -----------------------------------------------------------
void emergencyStop() {
    Serial.println("[EMERGENCY STOP] Cutting all solenoid outputs.");
    set_n2oValve(DEACTIVATE_PIN);
    set_o2Valve(DEACTIVATE_PIN);
    set_purge(DEACTIVATE_PIN);   // LOW = open (purge flows)
    set_fire(DEACTIVATE_PIN);
}
