#include <Adafruit_Fingerprint.h>

// Define the fingerprint sensor pins
#define FINGERPRINT_RX 2
#define FINGERPRINT_TX 3

// Create a fingerprint sensor object
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

// Define the number of fingerprints to store
#define NUM_FINGERPRINTS 50

// Define an array to hold the IDs of stored fingerprints
uint16_t fingerprintIDs[NUM_FINGERPRINTS];

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  while (!Serial);

  // Initialize the fingerprint sensor
  finger.begin(FINGERPRINT_SERIAL_BAUDRATE);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }

  // Clear any existing fingerprint templates
  finger.emptyDatabase();

  // Store up to NUM_FINGERPRINTS fingerprints
  for (int i = 0; i < NUM_FINGERPRINTS; i++) {
    Serial.print("Place finger ");
    Serial.print(i+1);
    Serial.println(" on the sensor...");

    // Wait for a fingerprint to be detected
    while (!finger.getImage()) {
      delay(100);
    }

    // Convert the fingerprint image into a template
    int fingerprintID = finger.image2Tz();
    if (fingerprintID != FINGERPRINT_OK) {
      Serial.println("Failed to convert image to template :(");
      return;
    }

    // Store the fingerprint template
    fingerprintIDs[i] = finger.storeTemplate();
    if (fingerprintIDs[i] == 0) {
      Serial.println("Failed to store template :(");
      return;
    }

    Serial.print("Stored fingerprint with ID #");
    Serial.println(fingerprintIDs[i]);
  }

  Serial.println("Fingerprint enrollment complete!");
}

void loop() {
  Serial.println("Place finger on the sensor...");

  // Wait for a fingerprint to be detected
  while (!finger.getImage()) {
    delay(100);
  }

  // Convert the fingerprint image into a template
  int fingerprintID = finger.image2Tz();
  if (fingerprintID != FINGERPRINT_OK) {
    Serial.println("Failed to convert image to template :(");
    return;
  }

  // Search for the fingerprint in the stored templates
  uint16_t matchID = finger.searchTemplate();
  if (matchID == FINGERPRINT_NOTFOUND) {
    Serial.println("Authentication failed :(");
  } else {
    Serial.print("Authenticated fingerprint with ID #");
    Serial.println(matchID);
  }
}
