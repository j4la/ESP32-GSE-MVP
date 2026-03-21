#pragma once

// ============================================================
//  network.h
//  Ethernet initialisation and TCP server declarations.
// ============================================================

#include <WiFiServer.h>
#include <WiFiClient.h>

extern WiFiServer server;

// Bring up the LAN8710A PHY and apply static IP.
// Returns true on success.
bool initEthernet();

bool initMDNS();

// Call from loop() — handles new connections and incoming data.
// Triggers GCS command dispatch and watchdog reset.
void handleTCP();

void checkTimeout(unsigned long *lastPacket);
