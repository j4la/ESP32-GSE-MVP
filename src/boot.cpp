#include <Arduino.h>
#include "boot.h"
// Bootup sequence

// Manually set GPIO pins low
void setGPIOlow()   {
    delay(1000);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(32, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(13, OUTPUT);

    delay(1000);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    digitalWrite(16, LOW);
    digitalWrite(15, LOW);
    digitalWrite(14, LOW);
    digitalWrite(13, LOW);
    delay(1000);

    digitalWrite(PURGE_TRG, HIGH);
    digitalWrite(FILL_ARM, HIGH);

    delay(100);
}

// Tests each relay one at a time
void relayTest()    {

    // N2O
    Serial.println("--- Activating N2O relay ---");
    digitalWrite(N2O_TRG, HIGH);
    digitalWrite(FILL_ARM, HIGH);
    digitalWrite(BOARD_LED, HIGH);
    delay(1000);
    Serial.println("--- Deactivating N2O relay ---");
    digitalWrite(N2O_TRG, LOW);
    digitalWrite(FILL_ARM, LOW);
    digitalWrite(BOARD_LED, LOW);
    delay(1000);

    // O2
    Serial.println("--- Activating O2 relay ---");
    digitalWrite(O2_TRG, HIGH);
    digitalWrite(FILL_ARM, HIGH);
    digitalWrite(BOARD_LED, HIGH);
    delay(1000);
    Serial.println("--- Deactivating O2 relay ---");
    digitalWrite(O2_TRG, LOW);
    digitalWrite(FILL_ARM, LOW);
    digitalWrite(BOARD_LED, LOW);
    delay(1000);

    // Purge
    Serial.println("--- Activating Purge relay ---");
    digitalWrite(PURGE_TRG, HIGH);
    digitalWrite(FILL_ARM, HIGH);
    digitalWrite(BOARD_LED, HIGH);
    delay(1000);
    Serial.println("--- Deactivating Purge relay ---");
    digitalWrite(PURGE_TRG, LOW);
    digitalWrite(FILL_ARM, LOW);
    digitalWrite(BOARD_LED, LOW);
    delay(1000);

    // Fire
    Serial.println("--- Activating Fire relay ---");
    digitalWrite(FIRE_TRG, HIGH);
    digitalWrite(IGN_ARM, HIGH);
    digitalWrite(BOARD_LED, HIGH);
    delay(1000);
    Serial.println("--- Deactivating Fire relay ---");
    digitalWrite(FIRE_TRG, LOW);
    digitalWrite(IGN_ARM, LOW);
    digitalWrite(BOARD_LED, LOW);
    delay(1000);

    // FirePWM
    Serial.println("--- Activating FirePWM relay ---");
    digitalWrite(FIRE_PWM, HIGH);
    digitalWrite(IGN_ARM, HIGH);
    digitalWrite(BOARD_LED, HIGH);
    delay(1000);
    Serial.println("--- Deactivating FirePWM relay ---");
    digitalWrite(FIRE_PWM, LOW);
    digitalWrite(IGN_ARM, LOW);
    digitalWrite(BOARD_LED, LOW);
    delay(1000);

}