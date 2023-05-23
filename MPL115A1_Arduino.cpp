/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT License
 */
 
/**
 * @file MPL115A1_Arduino.cpp
 * @brief This file contains the functions for MPL115A1 evaluation by Arduino
 */
 
#include <Arduino.h>
#include <SPI.h>
#include "MPL115A1_Arduino.h"

void MPL115A1_Arduino::init() {
  pinMode(SS, OUTPUT);
  pinMode(SHDN, OUTPUT);
  digitalWrite(SS, HIGH);
  power(LOW);
  power(HIGH);
  SPI.begin();
  coefficient_acquisition();
}

uint8_t MPL115A1_Arduino::power(uint8_t pin_condition) {
  if (pin_condition == LOW || pin_condition == HIGH) {
    digitalWrite(SHDN, pin_condition);
    delay(7);
    return 0;
  } else return 1;
}


uint8_t MPL115A1_Arduino::register_access (uint8_t read, uint8_t regAddress) {
  uint8_t read_bit = (read==0)? 0 : 0x80;
  digitalWrite(SS, LOW);
  SPI.transfer(read_bit | (regAddress<<1));
  uint8_t ret = SPI.transfer(0x00);
  digitalWrite(SS, HIGH);
  return ret;
}

float MPL115A1_Arduino::pressure_acquisition () {
  if (!coefficient_flag) coefficient_acquisition();
  register_access(0, 0x12);
  delay(5);
  
  uint16_t pressure = register_access(1, 0x00)<<2;
  pressure += register_access(1, 0x01)>>6;

  uint16_t temperature = register_access(1, 0x02)<<2;
  temperature += register_access(1, 0x03)>>6;
  
  float pressure_comp = (a0 + (b1+c12*temperature)*pressure + b2*temperature) * (65.0/1023.0)+50.0;

  return pressure_comp;
}

void MPL115A1_Arduino::coefficient_acquisition() {
  int16_t x = 0;
  
  // read a0
  x = register_access(1, 0x04)<<8;
  x += register_access(1, 0x05);
  a0 = x/8.0;
  
  // read b1
  x = register_access(1, 0x06)<<8;
  x += register_access(1, 0x07);
  b1 = x/8192.0;

  // read b2
  x = register_access(1, 0x08)<<8;
  x += register_access(1, 0x09);
  b2 = x/16384.0;

  // read c12
  x = register_access(1, 0x0a)<<8;
  x += register_access(1, 0x0b);
  c12 = x/4194304.0/4.0;  // 2^22 = 4194304, 4 is bit shift because c12 is 14-bit register
  coefficient_flag=1;
}