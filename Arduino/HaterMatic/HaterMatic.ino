/******************************************************************************
HaterMatic.ino
Main code for the "HaterMatic" project
Mike Hord @ SparkFun Electronics
19 Feb 2014
https://github.com/sparkfun/HaterMatic

This code uses SparkFun's 6-value coin accecptor (COM-11636) and thermal
printer (COM-10438) to allow people to pay to have a piece of harsh language
directed at them.

Resources:
SoftwareSerial library
avr/pgmspace.h

Development environment specifics:
Developed in Arduino 1.0.5
Developed on a SparkFun Arduino Pro Mini 5V/16MHz (DEV-11113)

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

// First things first: let's include the files we need to make all this happen.

#include <SoftwareSerial.h> // Support for the software serial port we'll use
                            //  to talk to the coin acceptor and printer.
#include <avr/pgmspace.h>   // Support for reading data (in this case our
                            //  insult strings) from flash memory. This eases
                            //  the burden on the much smaller SRAM, at the
                            //  cost of increased memory access time.
#include "insultStrings.h"  // Header file created for this project, which
                            // contains all the insult strings.

// Some definitions that will help us elsewhere in the code.
//  The definitions for number of insults of each time can be found in the
//  "insultStrings.h" file.

// These are pin redefinitions.
#define COIN_INPUT 7  // Serial (or pulse) input from the coin acceptor.
#define PRINTER_OUTPUT 8 // Serial output to printer
#define GET_INSULT A0 // Pushbutton input from insult request button.
#define INHIBIT 9     // Reject any further coins inserted

// Instantiate a software serial port on pins COIN_INPUT and PRINTER_OUTPUT.
//  Note that the printer communicates at 19200bps and the coin acceptor at
//  9600bps; this isn't a big deal because this is a half-duplex system, so
//  we can change between them at will, and use the INHIBIT signal to prevent
//  coins being accepted during print cycles, so we know no data will come
//  from the coin acceptor when the baud rate is wrong.
SoftwareSerial swser(COIN_INPUT, PRINTER_OUTPUT); // RX, TX

// We'll use two more defines to increase the readability of our code. The
//  preprocessor will simply replace any instance of "coinInput" or
//  "printerOutput" with "swser". Under the hood, it generates the same code,
//  but it lets us keep tabs on what we're doing more easily.
#define coinInput swser
#define printerOutput swser

// Set up a debug mode. If we define DEBUG to be 0, that will make the
//  necessary code changes later on to route the output to the printer. If we
//  define DEBUG to be 1, it will set up the code
#define DEBUG 0
#if DEBUG == 1
#undef printerOutput
#define printerOutput Serial
#endif

void setup()
{
  // We could use the hardware serial port for communicating with our serial
  //  devices; I've chosen to leave it available for debugging. We can
  //  easily re-route all of our serial data from the printer to the hardware
  //  serial port simply by changing the DEBUG define from 0 to 1.
  Serial.begin(57600);
  Serial.println("Hello, world!");
  
  // If we're *not* debugging, we'll need to activate our SW serial port at
  //  19200 to access the printer. We want to do that, feed a few lines
  //  through, print "Hello, world!" to check our printer's vitals, then
  //  feed a few more lines through.
  #if DEBUG == 0
  printerOutput.begin(19200);
  feed();
  #endif
  
  // If we *are* debugging, then this is all we want to do.
  printerOutput.println("Hello, world!");
  
  // Again, if we're not debugging, we need to do this to manipulate our
  //  printer and to allow us to change baud rates on the SW serial port.
  #if DEBUG == 0
  feed();
  printerOutput.end();
  #endif
  
  // Debugging or not, at this point we want to prepare to receive 9600baud
  //  serial data from the coin acceptor.
  coinInput.begin(9600);
  
  // We have two GPIO pins: the "Insult me!" button and the INHIBIT signal
  //  to the coin acceptor. When the button goes low, we've received a request
  //  for an insult. When we pull INHIBIT low, the coin acceptor will reject
  //  *all* coins. This is useful for preventing people from feeding in coins
  //  during a print cycle that would be missed due to the data rate mismatch.
  pinMode(GET_INSULT, INPUT_PULLUP);
  pinMode(INHIBIT, OUTPUT);
  digitalWrite(INHIBIT, HIGH);
}

void loop()
{
  // Cashola is the variable which stores the amount of money received. Each
  //  cent dropped in increases cashola by one. By making it a static variable,
  //  I ensure that it persists from one loop() iteration to the next without
  //  making it a global variable.
  static unsigned int cashola = 0;
  
  // Check for any input from the coin acceptor. The coin acceptor outputs a
  //  simple binary value representing the value of the coin inserted; in this
  //  case, I've set it equal (on the coin acceptor) to the value of the coin
  //  in cents.
  if (coinInput.available() > 0)
  {
    // Oddly enough, for nickels and dimes, the data coming out of the coin
    //  acceptor has a framing error: the last bit is a little too long. The
    //  SoftwareSerial receive function doesn't seem to wait for the stop bit
    //  (which will always be one), so it starts another read when it sees the
    //  extra long final bit, then reads all ones, which is interpreted as -1.
    //  We want to reject any result which is -1, since that's a nonsense coin
    //  value anyway.
    if (coinInput.peek() != -1) 
    {
      cashola += coinInput.read();
      Serial.println(cashola);
    }
    else coinInput.read();
  }
  
  // Catch our button press and issue an insult, but only if we've paid for it!
  if (digitalRead(GET_INSULT) == LOW && cashola > 0)
  { 
    // Before we go any further, we want to stop the coin acceptor from taking
    //  any more coins. If we accept more coins during this time, the 9600baud
    //  data from the coin acceptor will be misinterpreted by SoftwareSerial,
    //  which is expecting 19200baud data.
    digitalWrite(INHIBIT, LOW);
    
    // We use the current time value to randomize our insult selection. This
    //  isn't, of course, *truly* random; a determined attacker could break it.
    //  It's good enough for this purpose; it will be random to almost everyone
    //  who uses the device.
    long time = millis();
    
    // We need just the low byte, and we'll only need a subset of that. Cast
    //  away the higher bytes.
    byte stringSelect = (byte)time;
    
    // This little block is needed when we're not debugging. It changes the
    //  baud rate on the soft serial port so it can talk to the printer rather
    //  than the coin acceptor, then feeds out a bit of paper before printing
    //  the insult.
    #if DEBUG == 0
    coinInput.end();
    printerOutput.begin(19200);
    feed();
    #endif
    
    // Choose an insult based on the amount your client has paid. By using the
    //  modulo on the NUM constants, we ensure that we never request an insult
    //  with a number higher than we have provided.
    if      (cashola > 0   && cashola < 5)  cheapStrings();
    else if (cashola >= 5  && cashola < 10) valueStrings(stringSelect % NUM_V);
    else if (cashola >= 10 && cashola <25) qualityStrings(stringSelect % NUM_Q);
    else if (cashola >= 25) luxuryStrings(stringSelect % NUM_L);
    
    cashola = 0;  // Reset our received cash amount.
    
    // As above: when not debugging, go back to 9600baud for interfacing with
    //  the coin acceptor. The .flush() command waits until the serial data
    //  has been sent to proceed; failure to do this may result in corrupted
    //  data out of the soft serial port.
    #if DEBUG == 0
    feed();
    printerOutput.flush();
    printerOutput.end();
    coinInput.begin(9600);
    #endif
    
    // Debounce delay, and wait until the button is released to exit the loop
    //  and release the inhibit on the coin acceptor.
    delay(250);
    while (digitalRead(GET_INSULT) == LOW);
    digitalWrite(INHIBIT, HIGH);
  }
}

// Cheapskates don't get much variety.
void cheapStrings()
{
  printerOutput.println(F("Cheapskate!"));
}

// For the three higher-tier insult classes, we'll select an item from a list
//  defined in the insultStrings.h file based on the value calculated above.
void valueStrings(byte stringSelect)
{
  char buffer[150];
  strcpy_P(buffer, (char*)pgm_read_word(&(valueStringList[stringSelect])));
  printerOutput.println(buffer);
}

void qualityStrings(byte stringSelect)
{
  char buffer[150];
  strcpy_P(buffer, (char*)pgm_read_word(&(qualityStringList[stringSelect])));
  printerOutput.println(buffer);
}

void luxuryStrings(byte stringSelect)
{
  char buffer[150];
  strcpy_P(buffer, (char*)pgm_read_word(&(luxuryStringList[stringSelect])));
  printerOutput.println(buffer);
}

// Feed out an inch or so of paper, so the "receipt" is of a fair size.
void feed()
{
  printerOutput.print("\n\n\n\n");
}

