// ============================================================
//  network.cpp
//  Ethernet PHY init, static IP config, and TCP server loop.
// ============================================================

#include <Arduino.h>
#include <ETH.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "network.h"
#include "config.h"
#include "actuators.h"
#include "states.h"

WiFiServer server(TCP_PORT);

// Timestamp of the last valid GCS packet (used for watchdog).
static unsigned long lastGCSPacketMs = 0;

// -----------------------------------------------------------
//  initEthernet
// -----------------------------------------------------------
bool initEthernet() {
    IPAddress local_IP(LOCAL_IP);
    IPAddress gateway(GATEWAY_IP);
    IPAddress subnet(SUBNET_MASK);
    IPAddress primaryDNS(PRIMARY_DNS);
    IPAddress secondaryDNS(SECONDARY_DNS);

    Serial.println("Initializing Ethernet PHY...");

    if (!ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC,
                   ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE)) {
        Serial.println("Failed to initialize Ethernet!");
        return false;
    }

    if (!ETH.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("Warning: Failed to configure Static IP — falling back to DHCP.");
    } else {
        Serial.println("Static IP configuration applied.");
    }

    // Wait for a valid IP
    Serial.print("Waiting for IP");
    while (ETH.localIP()[0] == 0) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("HIVE Node IP: ");
    Serial.println(ETH.localIP());

    server.begin();
    Serial.printf("TCP server listening on port %d\n", TCP_PORT);

    lastGCSPacketMs = millis();
    return true;
}

// -----------------------------------------------------------
//  handleTCP
//    Called from loop(). Accepts new clients, reads packets,
//    dispatches GCS commands, and enforces the 5-second
//    watchdog.
// -----------------------------------------------------------
void handleTCP() {
    // --- Watchdog: no GCS input for GCS_TIMEOUT_MS → safe state ---
    // if (millis() - lastGCSPacketMs > GCS_TIMEOUT_MS) {
    //     Serial.println("[WATCHDOG] GCS timeout — emergency stop.");
    //     emergencyStop();
    //     // Reset timer so we don't spam the serial console
    //     lastGCSPacketMs = millis();
    // }

    WiFiClient client = server.available();
    if (!client) return;

    Serial.print("\n[New Connection from ");
    Serial.print(client.remoteIP());
    Serial.println("]");

    while (client.connected()) {
        if (client.available()) {
            uint8_t buffer[128];
            int bytesRead = client.read(buffer, min(client.available(), 128));

            // Reset watchdog on every valid packet
            lastGCSPacketMs = millis();

            // 0x02 ID starting to show that GSE packet 

            // Should I do this inside a loop because index 0 might not be the first byte?
            if (buffer[0] == 0x02)
            {
                // Check if (buffer[i+1] == flippedBits(buffer[i+2]))
                if (buffer[1] == (uint8_t)~buffer[2])    {
                    executeCommand(static_cast<command>(buffer[1]));
                    if (static_cast<command>(buffer[1]) == command::FILL_PURGE)
                    {
                        // Do we want a delay here? or should purge be a constant state
                    }
                }
                else    {
                    Serial.println("Error, data byte and inverted byte don't match.");
                }
            }

            // --- Hex dump (debug) ---
            for (int i = 0; i < bytesRead; i++) {

                Serial.printf("%02X ", buffer[i]);
            }
            Serial.println();
        }
    }

    Serial.println("\n[Connection Closed]");
    client.stop();
}
