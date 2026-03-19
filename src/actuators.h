#pragma once

// ============================================================
//  actuators.h
//  Declarations for all solenoid/relay control functions and
//  the ignition spark sequence.
// ============================================================

// --- Ignition ---
void attemptIgnition();

// --- Emergency stop ---
//  Immediately de-energises every output.
void emergencyStop();
