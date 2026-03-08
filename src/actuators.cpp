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

void set_n2oValve(bool activate) {
    // HIGH = open, LOW = closed
    digitalWrite(GPIO_PIN_n2oValve, activate ? HIGH : LOW);
    Serial.printf("N2O PIN: %d\t\t", activate ? HIGH : LOW);
}

void set_o2Valve(bool activate) {
    // HIGH = open, LOW = closed
    digitalWrite(GPIO_PIN_o2Valve, activate ? HIGH : LOW);
    Serial.printf("O2 PIN: %d\t\t", activate ? HIGH : LOW);
}

void set_purge(bool activate) {
    // HIGH = closed, LOW = open  (inverted — normally-open valve)
    digitalWrite(GPIO_PIN_purge, activate ? HIGH : LOW);
    Serial.printf("Purge PIN: %d\t\t", activate ? HIGH : LOW);
}

void set_fire(bool activate) {
    digitalWrite(GPIO_PIN_fire, activate ? HIGH : LOW);
    Serial.printf("Fire PIN: %d\t\t", activate ? HIGH : LOW);
}

void set_firePWM(bool activate){
    digitalWrite(GPIO_PIN_firePWM, activate ? HIGH : LOW);
    Serial.printf("Fire PWM PIN: %d\t\t", activate ? HIGH : LOW);
}

// -----------------------------------------------------------
//  AttemptIgnition
//    Pulses the spark output NUM_SPARKS times.
// i hop ehtis works
// -----------------------------------------------------------
void attemptIgnition() {
    Serial.println("\n- Attempting ignition...");
    for (int i = 0; i < NUM_SPARKS; i++) {
        Serial.print("SPARK\t");
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
    set_purge(DEACTIVATE_PIN);      // LOW = open (purge flows)
    set_fire(DEACTIVATE_PIN);
    set_firePWM(DEACTIVATE_PIN);
}
