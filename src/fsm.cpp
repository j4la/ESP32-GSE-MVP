// ============================================================
//  fsm.cpp
//  GSE finite state machine transitions and GCS command
//  dispatcher.
// ============================================================

#include <Arduino.h>
#include "fsm.h"
#include "actuators.h"
#include "config.h"
#include "states.h"

// Global FSM state (initialised in main.cpp setup())
int STATE_current = STATE_standby;
int ACT_current   = ACT_purge;

// -----------------------------------------------------------
//  switchState
//    Drives solenoids according to the new (STATE, ACTION)
//    pair, then updates the previous-state/action pointers.
// -----------------------------------------------------------
void switchState(int STATE, int ACTION, int* previousState, int* previousAction) {
    switch (STATE) {

        // ---- FUEL ACTIVE ----
        case STATE_fuelActive:
            if (ACTION == ACT_purge) {
                if (*previousAction == ACT_fill) {
                    set_n2oValve(DEACTIVATE_PIN);   // Close fuel valve
                }
                set_purge(ACTIVATE_PIN);            // Open purge
                *previousAction = ACT_purge;
            }
            else if (ACTION == ACT_fill) {
                set_purge(DEACTIVATE_PIN);          // Close purge
                set_n2oValve(ACTIVATE_PIN);         // Open fuel valve
                *previousAction = ACT_fill;
            }
            else if (ACTION == ACT_neutral) {
                set_n2oValve(DEACTIVATE_PIN);
                set_purge(DEACTIVATE_PIN);
                *previousAction = ACT_neutral;
            }
            *previousState = STATE_fuelActive;
            break;

        // ---- IGNITION ACTIVE ----
        case STATE_ignActive:
            // Transition clean-up from fuelActive
            if (*previousState == STATE_fuelActive) {
                if (*previousAction == ACT_fill) {
                    set_n2oValve(DEACTIVATE_PIN);
                }
                else if (*previousAction == ACT_purge) {
                    set_purge(DEACTIVATE_PIN);
                }
            }

            if (ACTION == ACT_fire) {
                if (*previousAction == ACT_O2) {
                    set_o2Valve(DEACTIVATE_PIN);    // Close O2 before firing
                }
                set_fire(ACTIVATE_PIN);
                *previousAction = ACT_fire;
            }
            else if (ACTION == ACT_O2) {
                set_o2Valve(ACTIVATE_PIN);
                *previousAction = ACT_O2;
            }
            *previousState = STATE_ignActive;
            break;

        // ---- STANDBY ----
        case STATE_standby:
            // TODO: define standby entry actions if needed
            *previousState = STATE_standby;
            break;

        default:
            Serial.println("[FSM] Unknown state — triggering emergency stop.");
            emergencyStop();
            break;
    }
}

// -----------------------------------------------------------
//  GCScommand
//    Interprets an incoming GCS command map and forwards it
//    to switchState().
//
//    TODO: Define the byte protocol with the GCS team and
//    populate the decode logic below.
// -----------------------------------------------------------

