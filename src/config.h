#pragma once

// ============================================================
//  config.h
//  Hardware pin assignments, ETH PHY settings, network config,
//  and fire-sequence timing constants.
// ============================================================

// --- Ethernet PHY (Olimex ESP32-PoE-ISO / LAN8710A in RMII mode) ---
#define ETH_PHY_ADDR    0
#define ETH_PHY_POWER   12
#define ETH_PHY_MDC     23
#define ETH_PHY_MDIO    18
#define ETH_PHY_TYPE    ETH_PHY_LAN8720   // LAN8710A is compatible
#define ETH_CLK_MODE    ETH_CLOCK_GPIO17_OUT

// --- Serial ---
#define SERIAL_BAUD     115200

// --- TCP Server ---
#define TCP_PORT        5000

// --- Static IP ---
#define LOCAL_IP        192, 168, 0, 150
// #define LOCAL_IP        192, 168, 0, 254
#define GATEWAY_IP      192, 168, 0, 1
#define SUBNET_MASK     255, 255, 255, 0
#define PRIMARY_DNS     8, 8, 8, 8
#define SECONDARY_DNS   1, 1, 1, 1

// --- GPIO Pin Assignments ---
const int GPIO_PIN_n2oValve = 13; 
const int GPIO_PIN_purge    = 14;  
const int GPIO_PIN_o2Valve  = 32;
const int GPIO_PIN_fire     = 33;
const int GPIO_PIN_firePWM  = 5;


// --- Solenoid logic helpers ---
//  Pass these to the set_*() functions for readability.
const bool ACTIVATE_PIN   = true;
const bool DEACTIVATE_PIN = false;

// --- Fire / ignition sequence timing (all in ms) ---
#define PRE_PURGE_DELAY     1500    // Delay until post-fire N2 purge
#define OXYGEN_PRE_PURGE    20      // Start O2 this many ms early
#define CHAMBER_TIME        5500    // Total test duration
#define OXYGEN_RUNTIME      5000    // How long O2 valve stays open
#define PRE_PURGE           0       // Gap between O2 close and N2 open
#define PURGE_N2            10000   // N2 post-fire purge duration
#define NUM_SPARKS          60      // Number of ignition sparks
#define SPARK_LENGTH        5       // Each spark pulse length (ms)
#define SPARK_INTERVAL      3       // Gap between sparks (ms)

// --- Watchdog / safety ---
#define GCS_TIMEOUT_MS      5000    // Cut solenoids if no GCS input for this long
