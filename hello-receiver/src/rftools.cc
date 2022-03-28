//
// Created by cameron.king on 3/27/2022.
//
/// @file

#include "rftools.h"
#include "config.h"

namespace rftools {

void ResetRF69(const uint32_t rst_pin) {
  pinMode(rst_pin, OUTPUT);
  digitalWrite(rst_pin, LOW);
  delay(10);
  digitalWrite(rst_pin, HIGH);
  delay(10);
  digitalWrite(rst_pin, LOW);
  delay(10);
}

void CrashFlash(const uint32_t led_pin, const char *message) {
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  if (DEBUG) {
    Serial.print("CrashFlash: ");
    Serial.println(message);
  }
  while (true) {
    digitalWrite(led_pin, HIGH); // .
    delay(100);
    digitalWrite(led_pin, LOW);
    delay(100);
    digitalWrite(led_pin, HIGH); // .
    delay(100);
    digitalWrite(led_pin, LOW);
    delay(100);
    digitalWrite(led_pin, HIGH); // .
    delay(100);
    digitalWrite(led_pin, LOW);
    delay(300);

    digitalWrite(led_pin, HIGH); // -
    delay(300);
    digitalWrite(led_pin, LOW);
    delay(100);
    digitalWrite(led_pin, HIGH); // -
    delay(300);
    digitalWrite(led_pin, LOW);
    delay(100);
    digitalWrite(led_pin, HIGH); // -
    delay(300);
    digitalWrite(led_pin, LOW);
    delay(300);

    digitalWrite(led_pin, HIGH); // .
    delay(100);
    digitalWrite(led_pin, LOW);
    delay(100);
    digitalWrite(led_pin, HIGH); // .
    delay(100);
    digitalWrite(led_pin, LOW);
    delay(100);
    digitalWrite(led_pin, HIGH); // .
    delay(100);
    digitalWrite(led_pin, LOW);
    delay(700);
  }
}
Error RF69Setup(RHReliableDatagram &manager, RH_RF69 &driver,
                const uint32_t rst_pin, const float center_frequency_in_mhz,
                const int8_t power_in_dbm, const bool is_high_power_module) {
  rftools::ResetRF69(rst_pin);

  if (!manager.init()) {
    return FailedToInitializeManager;
  }

  if (!driver.setFrequency(center_frequency_in_mhz)) {
    return CenterFrequencyOutOfRange;
  }

  driver.setTxPower(power_in_dbm, is_high_power_module);

  return NoError;
}

} // namespace rftools