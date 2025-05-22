#include <Wire.h>
#include <MFRC522_I2C.h>
#include <SPI.h>
#include <SD.h>

#define SDA_PIN 0x28  // Default I2C address for MFRC522
#define RST_PIN 9      // Reset pin for RFID module

#define LED_CHARGE 3    // LED for charging indication
#define LED_DATA 4      // LED for data transfer indication
#define BUZZER_PIN 5    // Buzzer pin
#define SWITCH_PIN 6    // Push button to allow data transfer
#define TRANSISTOR1 7   // Transistor controlling D+
#define TRANSISTOR2 8   // Transistor controlling D-

#define SD_CS 10        // Chip Select pin for SD card

MFRC522_I2C mfrc522(SDA_PIN, RST_PIN);
File logFile;

bool dataTransferAllowed = false;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    mfrc522.PCD_Init();
    pinMode(LED_CHARGE, OUTPUT);
    pinMode(LED_DATA, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    pinMode(TRANSISTOR1, OUTPUT);
    pinMode(TRANSISTOR2, OUTPUT);

    // SD Card Initialization
    if (!SD.begin(SD_CS)) {
        Serial.println("SD Card initialization failed!");
    } else {
        Serial.println("SD Card ready.");
    }

    digitalWrite(LED_CHARGE, HIGH);  // Indicate charging is active
    digitalWrite(LED_DATA, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(TRANSISTOR1, LOW);
    digitalWrite(TRANSISTOR2, LOW);
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    if (!mfrc522.PICC_ReadCardSerial()) return;

    Serial.print("Card UID: ");
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println(uid);

    if (isAuthorized(uid)) {
        allowDataTransfer();
    } else {
        blockDataTransfer();
    }

    mfrc522.PICC_HaltA();  // Halt PICC
}

bool isAuthorized(String uid) {
    return (uid == "12ab34cd56"); // Replace with actual authorized UID
}

void allowDataTransfer() {
    if (digitalRead(SWITCH_PIN) == LOW) { // Switch pressed
        Serial.println("Data Transfer Allowed");
        digitalWrite(LED_DATA, HIGH);
        digitalWrite(TRANSISTOR1, HIGH);
        digitalWrite(TRANSISTOR2, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);  // Buzzer ON when data transfer occurs
        logEvent("Data transfer started");
        delay(500);
        digitalWrite(BUZZER_PIN, LOW);   // Stop buzzer after short beep
    }
}

void blockDataTransfer() {
    Serial.println("Data Transfer Blocked");
    digitalWrite(LED_DATA, LOW);
    digitalWrite(TRANSISTOR1, LOW);
    digitalWrite(TRANSISTOR2, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    logEvent("Unauthorized data transfer attempt");
}

void logEvent(String event) {
    logFile = SD.open("log.txt", FILE_WRITE);
    if (logFile) {
        logFile.println(event);
        logFile.close();
    }
}
