/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT License
 */
/**
 * @file example_MPL115A1_Arduino.ino
 * @brief This file is an example code for MPL115A1_Arduino
 */

#include "MPL115A1_Arduino.h"

MPL115A1_Arduino mpl115a1(8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mpl115a1.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  mpl115a1.power(HIGH);
  Serial.println(mpl115a1.pressure_acquisition());
  mpl115a1.power(LOW);
  delay(5000);
}
