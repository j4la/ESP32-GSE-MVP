// ============================================================
//  main.cpp
//  Project Horizon — GSE firmware entry point.
//  Delegates hardware init and loop work to dedicated modules.
// ============================================================

#include <Arduino.h>
#include "config.h"
#include "states.h"
#include "actuators.h"
#include "network.h"

void setup() {
    // --- GPIO ---
    pinMode(GPIO_PIN_n2oValve, OUTPUT);
    pinMode(GPIO_PIN_purge,    OUTPUT);
    pinMode(GPIO_PIN_o2Valve,  OUTPUT);
    pinMode(GPIO_PIN_fire,     OUTPUT);
    pinMode(GPIO_PIN_firePWM,  OUTPUT);

    // --- Safe / default state ---
    //  Purge open, all propellant valves closed.
    executeCommand(command::SYSTEM_ACTIVE);

    // --- Serial ---
    Serial.begin(SERIAL_BAUD);
    // Note: blocking here prevents Ethernet init if no PC is connected.
    // Remove the while(!Serial) wait for standalone (no-USB) operation.
    while (!Serial) {}

    Serial.println("\n--- Project Horizon: GSE Firmware ---");

    // --- Ethernet / TCP ---
    // initEthernet();

    if (!initEthernet()) {
        Serial.println("Fatal: Ethernet init failed. Halting.");
        while (true) { delay(1000); }
    }
}

void loop() {
    handleTCP();
}
