//
// Created by cameron.king on 3/26/2022.
//
/// @file

#ifndef HELLO_SENDER_INCLUDE_RADIOPINS_H_
#define HELLO_SENDER_INCLUDE_RADIOPINS_H_

#if defined(__AVR_ATmega32U4__) // Feather 32u4 w/Radio
#define RFM69_CS 8
#define RFM69_INT 7
#define RFM69_RST 4
#define LED 13
#endif

#if defined(ADAFRUIT_FEATHER_M0) || defined(ADAFRUIT_FEATHER_M0_EXPRESS) ||    \
    defined(ARDUINO_SAMD_FEATHER_M0)
// Feather M0 w/Radio
#define RFM69_CS 8
#define RFM69_INT 3
#define RFM69_RST 4
#define LED 13
#endif

#if defined(__AVR_ATmega328P__) // Feather 328P w/wing
#define RFM69_INT 3             //
#define RFM69_CS 4              //
#define RFM69_RST 2             // "A"
#define LED 13
#endif

#if defined(ESP8266) // ESP8266 feather w/wing
#define RFM69_CS 2   // "E"
#define RFM69_IRQ 15 // "B"
#define RFM69_RST 16 // "D"
#define LED 0
#endif

#if defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2) ||                               \
    defined(ARDUINO_NRF52840_FEATHER) ||                                       \
    defined(ARDUINO_NRF52840_FEATHER_SENSE)
#define RFM69_INT 9  // "A"
#define RFM69_CS 10  // "B"
#define RFM69_RST 11 // "C"
#define LED 13

#elif defined(ESP32) // ESP32 feather w/wing
#define RFM69_RST 13 // same as LED
#define RFM69_CS 33  // "B"
#define RFM69_INT 27 // "A"
#define LED 13
#endif

#if defined(ARDUINO_NRF52832_FEATHER)
/* nRF52832 feather w/wing */
#define RFM69_RST 7  // "A"
#define RFM69_CS 11  // "B"
#define RFM69_INT 31 // "C"
#define LED 17
#endif

/* Teensy 3.x w/wing
#define RFM69_RST     9   // "A"
#define RFM69_CS      10   // "B"
#define RFM69_IRQ     4    // "C"
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ )
*/

/* WICED Feather w/wing
#define RFM69_RST     PA4     // "A"
#define RFM69_CS      PB4     // "B"
#define RFM69_IRQ     PA15    // "C"
#define RFM69_IRQN    RFM69_IRQ
*/

#endif // HELLO_SENDER_INCLUDE_RADIOPINS_H_
