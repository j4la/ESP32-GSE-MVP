#pragma once

// ============================================================
//  actuators.h
//  Declarations for all solenoid/relay control functions and
//  the ignition spark sequence.
// ============================================================

// --- Solenoid helpers ---
void set_n2oValve(bool activate);
void set_o2Valve(bool activate);
void set_purge(bool activate);
void set_fire(bool activate);
void set_firePWM(bool activate);

// --- Ignition ---
void AttemptIgnition();

// --- Emergency stop ---
//  Immediately de-energises every output.
void emergencyStop();
