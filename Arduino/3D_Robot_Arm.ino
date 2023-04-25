#include <Servo.h>

// Define servo pins
Servo servo1;
Servo servo2;
Servo servo3;

// Define potentiometer pins
int pot1 = A0;
int pot2 = A1;
int pot3 = A2;

// Define angle variables
int angle1;
int angle2;
int angle3;

void setup() {
  // Attach servos to pins
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  
  // Initialize serial communication
  Serial.begin(115200);
}

void loop() {
  // Read potentiometer values and convert to angles
  angle1 = map(analogRead(pot1), 0, 1023, 0, 180);
  angle2 = map(analogRead(pot2), 0, 1023, 0, 180);
  angle3 = map(analogRead(pot3), 0, 1023, 0, 180);
  
  // Move servos to angles
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  
  // Print angle values to serial monitor
  Serial.print("Angle 1: ");
  Serial.print(angle1);
  Serial.print(" | Angle 2: ");
  Serial.print(angle2);
  Serial.print(" | Angle 3: ");
  Serial.println(angle3);
  
  // Add a delay to avoid overwhelming the servos
  delay(20);
}
