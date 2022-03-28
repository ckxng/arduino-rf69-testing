#include <Arduino.h>
#include <string>

#include <RHReliableDatagram.h>
#include <RH_RF69.h>

#include "config.h"
#include "radiopins.h"
#include "rftools.h"

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram rf69_manager(rf69, MY_ADDRESS);

// Don't put this on the stack
// +1 because we make c-strings with it when we print to serial
uint8_t buf[RH_RF69_MAX_MESSAGE_LEN+1];

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }

  // for reading the battery voltage
  pinMode(PIN_A7, INPUT);

  // radio setup
  if (rftools::RF69Setup(rf69_manager, rf69, RFM69_RST, RF69_FREQ,
                         RF69_POWER_IN_DBM, RF69_IS_HIGH_POWER)) {
    rftools::CrashFlash(LED, "failed to setup radio chip");
  }
  if (DEBUG) {
    Serial.println("RFM69 radio init OK!");
  }
}

void loop() {

  if (rf69_manager.available()) {
    // Wait for a message addressed to us from the client
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (rf69_manager.recvfromAck(buf, &len, &from)) {
      // zero out the character behind the received message to make a c_str
      buf[len] = 0;

      if (DEBUG) {
        Serial.print("Got packet from #");
        Serial.print(from);
        Serial.print(" [RSSI: ");
        Serial.print(rf69.lastRssi());
        Serial.print("]: ");
        Serial.println((char *)buf);
      }

      rf69.setModeIdle();  // must idle to read temperature
      std::string reply =
          "!r" + std::to_string(rf69.lastRssi()) + " f" + std::to_string(from) +
          " l" + std::to_string(len) + " t" +
          std::to_string(rf69.temperatureRead()) + " b" +
          std::to_string(static_cast<int>(analogRead(PIN_A7) * 6.6 / 102.4)) +
          " " + HAM_RADIO_CALLSIGN;

      if (DEBUG) {
        Serial.print("  Reply: ");
        Serial.println(reply.c_str());
      }

      // Send a reply back to the originator client
      if (!rf69_manager.sendtoWait((uint8_t *)reply.c_str(), reply.length(),
                                   from) &&
          DEBUG)
        Serial.println("Sending failed (no ack)");
    }
  }
}