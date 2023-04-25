// SPI/I2C master by PS_O5

#include <SPI.h>
#include <Wire.h>
#include "pins_arduino.h"

#define SLAVE_ADDRESS 42

// command we might send
#define CMD_ID     1

void setup (void)
{
  Wire.begin();   
  Serial.begin(115200);  // start serial for output

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();
  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV16);

}  // end of setup


void loop (void)
{

  char c;

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "Hello, world!\n" ; c = *p; p++)
    SPI.transfer (c);

  // disable Slave Select
  digitalWrite(SS, HIGH);

  delay (200);  // 200 mS delay

  Wire.beginTransmission (SLAVE_ADDRESS);
  Wire.write(CMD_ID);
  Wire.endTransmission ();

  Wire.requestFrom (SLAVE_ADDRESS, 1); 

  if (Wire.available ())
    {
    Serial.print ("Slave is ID: ");
    Serial.println(Wire.read(), DEC);
    }

  delay (1000);  // 1 second delay
}  // end of loop
