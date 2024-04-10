// - - - - -
// ESPDMX - A Arduino library for sending and receiving DMX using the builtin serial hardware port.
//
// Copyright (C) 2015  Rick <ricardogg95@gmail.com>
// This work is licensed under a GNU style license.
//
// Last change: Musti <https://github.com/IRNAS> (edited by Musti)
//
// Documentation and samples are available at https://github.com/Rickgg/ESP-Dmx
// Connect GPIO02 - TDX1 to MAX3485 or other driver chip to interface devices
// Pin is defined in library
// - - - - -

#include "ESPDMX.h"

DMXESPSerial dmx;

void setup() {
  //dmx.init();               // initialization for first 32 addresses by default
  dmx.init(512);           // initialization for complete bus
  delay(200);               // wait a while (not necessary)
}

void dump(uint8_t* buffer) {
   // Full debug!
   for (int i = 0; i < 512; i++) {
     //buffer[i] = buffer[i];
     if ((i % 32) == 0) {
       Serial.println("");
       if (i < 32) Serial.print('0');
       if (i < 128) Serial.print('0');
       Serial.print(i);
       Serial.print(": ");
     }
     Serial.print(buffer[i], HEX);
     Serial.print(" ");
   }
   Serial.println("");
   Serial.print("------------------");
   Serial.print("");
}


#define CHAN1 0
#define CHAN2 1
#define CHAN3 511
#define CHAN4 512

void loop() {

    dmx.write(CHAN4, 0);
    dmx.write(CHAN3, 0);
    dmx.write(CHAN1, 255);
    dmx.update();
    delay(1000);
    Serial.println("");
    Serial.print(CHAN3);
    Serial.print(" -> 0 - ");
    Serial.print(CHAN1);
    Serial.println(" -> 255");
    dump(dmx.buffer());
    
    dmx.write(CHAN1, 0);
    dmx.write(CHAN2, 255);
    dmx.update();
    delay(1000);
    Serial.println("");
    Serial.print(CHAN1);
    Serial.print(" -> 0 - ");
    Serial.print(CHAN2);
    Serial.println(" -> 255");
    dump(dmx.buffer());

    dmx.write(CHAN2, 0);
    dmx.write(CHAN3, 255);
    dmx.update();
    delay(1000);
    Serial.println("");
    Serial.print(CHAN2);
    Serial.print(" -> 0 - ");
    Serial.print(CHAN3);
    Serial.println(" -> 255");
    dump(dmx.buffer());

    dmx.write(CHAN3, 0);
    dmx.write(CHAN4, 255);
    dmx.update();
    delay(1000);
    Serial.println("");
    Serial.print(CHAN3);
    Serial.print(" -> 0 - ");
    Serial.print(CHAN4);
    Serial.println(" -> 255");
    dump(dmx.buffer());

}
