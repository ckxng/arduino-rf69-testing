//
// Created by cameron.king on 3/27/2022.
//
/// @file

#ifndef HELLO_RECEIVER_INCLUDE_RFTOOLS_H_
#define HELLO_RECEIVER_INCLUDE_RFTOOLS_H_

#include "RHReliableDatagram.h"
#include "RH_RF69.h"
#include <Arduino.h>

namespace rftools {

enum Error {
  NoError = 0,
  FailedToInitializeManager,
  CenterFrequencyOutOfRange,
};

/**
 * Resets the RF69 so it will begin receiving data.
 * Sets reset pin to OUTPUT, then pulses the reset pin high.
 * @param rst_pin the pin number of the RF69 reset pin
 * @return 0 or rftools::Error on failure
 */
void ResetRF69(const uint32_t rst_pin);

/**
 * Flash the LED forever due to an unrecoverable crash
 * @param led_pin
 */
void CrashFlash(const uint32_t led_pin, const char *message);

/**
 * Setup the RF69 manager and chip.
 * Resets the chip.  Initializes the manager.  Sets the center frequency.
 * @param manager the manager class
 * @param driver the rf69 driver class
 * @param rst_pin the rf69 chip reset pin
 * @param center_frequency_in_mhz the center frequency to set
 * @param power_in_dbm the power in dBm to set
 * @param is_high_power_module true if this chip is RF69HW or RF69HCW, else
 *                             false
 * @return NoError on success or another rftools::Error
 */
Error RF69Setup(RHReliableDatagram &manager, RH_RF69 &driver,
                const uint32_t rst_pin, const float center_frequency_in_mhz,
                const int8_t power_in_dbm, const bool is_high_power_module);

} // namespace rftools

#endif // HELLO_RECEIVER_INCLUDE_RFTOOLS_H_
