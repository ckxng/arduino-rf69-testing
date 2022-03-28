#include <Arduino.h>

#include <RHReliableDatagram.h>
#include <RH_RF69.h>
#include <SPI.h>
#include <LowPower.h>

#include <config.h>
#include <radiopins.h>

#include "rftools.h"

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram rf69_manager(rf69, MY_ADDRESS);

// packet counter, we increment per transmission
int16_t packet_num = 0;

void setup() {
  Serial.begin(9600);
  while (DEBUG && !Serial) {
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

// Dont put this on the stack:
uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];

void loop() {
  rf69.setModeIdle();  // must idle to read temperature
  auto message =
      "Hello World #" + std::to_string(packet_num++) + " t" +
      std::to_string(rf69.temperatureRead()) + " b" +
      std::to_string(static_cast<int>(analogRead(PIN_A7) * 6.6 / 102.4)) + " " +
      HAM_RADIO_CALLSIGN;

  if (DEBUG) {
    Serial.print("Sending ");
    Serial.println(message.c_str());
  }

  // Send a message to the DESTINATION!
  if (rf69_manager.sendtoWait((uint8_t *)message.c_str(), message.length(),
                              DEST_ADDRESS)) {
    // Now wait for a reply from the server
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (rf69_manager.recvfromAckTimeout(buf, &len, 2000, &from) && DEBUG) {
      buf[len] = 0; // zero out remaining string

      Serial.print("Got reply from #");
      Serial.print(from);
      Serial.print(" [RSSI :");
      Serial.print(rf69.lastRssi());
      Serial.print("] : ");
      Serial.println((char *)buf);
    } else if (DEBUG) {
      Serial.println("No reply, is anyone listening?");
    }
  } else if (DEBUG) {
    Serial.println("Sending failed (no ack)");
  }
  rf69.sleep();
  // TODO set timer interrupt on Cortex M0
  // LowPower.standby();
  delay(10000);
}
