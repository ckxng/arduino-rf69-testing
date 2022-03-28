//
// Created by cameron.king on 3/26/2022.
//

#ifndef HELLO_RECEIVER_INCLUDE_CONFIG_H_
#define HELLO_RECEIVER_INCLUDE_CONFIG_H_

#include <Arduino.h>
#include <string>

/// change addresses for each client board, any number :)
const static int MY_ADDRESS = 1;

/// Ham radio callsign (required for 434MHz in the USA)
const static std::string HAM_RADIO_CALLSIGN =
    "XXNXXX-" + std::to_string(MY_ADDRESS);

/// enable or disable debug behaviors (only enable if connected to PC on serial)
const static bool DEBUG = true;

/// is this a RF69HW high power module?  (if set incorrectly, no power output)
const static bool RF69_IS_HIGH_POWER = true;

/// set output power in dBm (RF69W -18 to +13, RF69HW -2 to +20).
/// USE CAUTION AT HIGH POWER WITH HIGH DUTY CYCLES OR POORLY TUNED ANTENNAS!
const static int8_t RF69_POWER_IN_DBM = 0;

/// Change to 915.0, 434.0 or other frequency, must match RX's freq!
const static float RF69_FREQ = 434.0;

#endif // HELLO_RECEIVER_INCLUDE_CONFIG_H_
