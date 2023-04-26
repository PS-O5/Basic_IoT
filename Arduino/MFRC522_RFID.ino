#include <SPI.h>
#include <MFRC522.h>

// Define the RFID reader pins
#define RFID_SS_PIN 10
#define RFID_RST_PIN 9

// Create an MFRC522 RFID reader object
MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);

// Define the authorized RFID tag IDs
byte authorizedTagIDs[3][4] = {
  { 0x45, 0x2C, 0x3F, 0x54 }, // Replace with your own tag IDs. If you don't know how to get your own ID tags, bruh, leave this domain. Study history and arts.
  { 0x9A, 0xBC, 0xDE, 0xF1 },
  { 0x23, 0x4C, 0x9F, 0x87 }
};

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  while (!Serial);

  // Initialize the RFID reader
  SPI.begin();
  rfid.PCD_Init();

  // Print some information about the RFID reader
  Serial.print("Found chip ");
  Serial.print(rfid.PCD_ReadRegister(rfid.VersionReg), HEX);
  Serial.print(" (");
  Serial.print(rfid.PCD_ReadRegister(rfid.VersionReg), BIN);
  Serial.println(")");

  // Set the RFID reader to read mode
  rfid.PCD_SetAntennaGain(rfid.RxGain_max);
}

void loop() {
  // Check if an RFID tag is present
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Print the tag UID (unique identifier)
    Serial.print("Tag UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Check if the tag is authorized
    bool authorized = false;
    for (byte i = 0; i < 3; i++) {
      if (memcmp(rfid.uid.uidByte, authorizedTagIDs[i], 4) == 0) {
        authorized = true;
        break;
      }
    }

    // Print the authentication result. You can add your own functions replacing or along with the below authentication logic to do/not to do stuff :) or to fire an alarm (′ꈍωꈍ‵)
    if (authorized) {
      Serial.println("Authentication successful!");
    } else {
      Serial.println("Authentication failed :(");
    }

    // Halt the tag and stop reading
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
