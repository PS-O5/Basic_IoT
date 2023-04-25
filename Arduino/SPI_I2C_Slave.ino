// SPI/I2C slave by PS_O5

#include "pins_arduino.h"
#include <Wire.h>

char buf [100];
volatile byte pos;
volatile boolean process_it;

// command we might get
#define CMD_ID     1
#define MY_ADDRESS 42

char command;

void setup (void)
{
  Serial.begin (115200);   // debugging

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // get ready for an interrupt
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPCR |= _BV(SPIE);

  Wire.begin (MY_ADDRESS);
  Wire.onReceive (receiveEvent);  // interrupt handler for incoming messages
  Wire.onRequest (requestEvent);  // interrupt handler for when data is wanted

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
byte c = SPDR;  // grab byte from SPI Data Register

  if (!process_it)
    {
    // add to buffer if room
    if (pos < sizeof buf)
      {
      buf [pos++] = c;

      // example: newline means time to process buffer
      if (c == '\n')
        process_it = true;

      }  // end of room available
  } // if not waiting for previous one to be processed

}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process_it)
    {
    buf [pos] = 0; 
    Serial.println (buf);
    pos = 0;
    process_it = false;
    }  // end of flag set

}  // end of loop

void receiveEvent (int howMany)
 {
   command = Wire.available();  // remember command for when we get request
} // end of receiveEvent


void requestEvent ()
{
 switch (command)
   {
   case CMD_ID:      Wire.write(0x55); break;   // send our ID

   }  // end of switch

}  // end of requestEvent
