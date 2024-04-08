// Flash @ 160MHz!

#include "DMXUSB.h"
#include "ESPDMX.h"

#include <SoftwareSerial.h>

#define DEBUG_TX 16 // D0 GPIO16 4
#define DEBUG_RX 5 // Unused
EspSoftwareSerial::UART debugPort;

#define FTDI Serial

const byte LED_PIN = 16;

#define DMXUSB_BAUDRATE 250000

DMXESPSerial dmx;
void myDMXCallback(int universe, char buffer[512]) {
  // Off by one error below
  // if (universe == 0) {
  //   for (int index=0; index < 512; index++) { // for each channel, universe starts at 0
  //     dmx.write(index, buffer[index]); // off by one!
  //   }
  // }
  
  // Full debug!
  // for (int i = 0; i < 512; i++) {
  //   dmx.buffer()[i] = buffer[i];
  //   if ((i % 32) == 0) {
  //     debugPort.println("");
  //     if (i < 32) debugPort.print('0');
  //     if (i < 128) debugPort.print('0');
  //     debugPort.print(i);
  //     debugPort.print(": ");
  //   }
  //   debugPort.print(dmx.buffer()[i], HEX);
  //   debugPort.print(" ");
  // }
  // debugPort.println("");
  // debugPort.print("------------------");
  // debugPort.print("");
  
  for (int i = 0; i < 512; i++) {
    dmx.buffer()[i] = buffer[i];
    // Light debug but still breaks DMX rate
    // debugPort.print(dmx.buffer()[i], HEX);
    // if ((i % 128) == 0) {
    //   debugPort.println("");
    // }
  }
  dmx.update();
}

DMXUSB myDMXUsb(
  // Stream serial,
  FTDI,
  // int baudrate,
  DMXUSB_BAUDRATE,
  // int mode,
  0,
  // void (*dmxInCallback)(int universe, unsigned int index, char buffer[512])
  myDMXCallback
);


void setup() {
  pinMode(LED_PIN, OUTPUT);

  FTDI.begin(DMXUSB_BAUDRATE);
  FTDI.swap();
  
  dmx.init((int)512);
  
  debugPort.begin(38400, SWSERIAL_8N1, DEBUG_RX, DEBUG_TX, false);
  digitalWrite(LED_PIN, HIGH);
  debugPort.println("INIT OK ...");
  delay(500);
  digitalWrite(LED_PIN, LOW);
  debugPort.println("INIT OK ...");
  delay(500);
  digitalWrite(LED_PIN, HIGH);
  debugPort.println("INIT OK ...");
  delay(500);
  digitalWrite(LED_PIN, LOW);
  debugPort.println("INIT OK ...");
  delay(500);
  
}

bool toggled = false;
long int lastToggle = 0;
void loop() {
  myDMXUsb.listen();
}



