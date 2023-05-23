/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: MIT License
 */
 
/**
 * @file MPL115A1_Arduino.h
 * @brief This file is the header for MPL115A1_Arduino
 */

#ifndef _MPL115A1_Arduino_h
#define _MPL115A1_Arduino_h
#include <Arduino.h>

/**
* @brief Class to evaluate MPL115A1
*/
class MPL115A1_Arduino {
  public:
    uint8_t SHDN=9;               //!< @brief Default Arduino pin number of /SHDN pin
    float a0, b1, b2, c12;        //!< @brief Coefficient parameters for MPL115A1
    uint8_t coefficient_flag = 0; //!< @brief Flag indicating if coefficient parameters are taken

    /**
    * @brief Initialization function: Execute once after definition
    */
    void init();

    /**
    * @brief Power up/down MPL115A1 by /SHDN pin
    * @param pin_condition HIGH for power ON, LOW for power OFF
    * @return 0 if successfully done, 1 if parameter is other than HIGH or LOW
    */
    uint8_t power(uint8_t pin_condition);

    /**
    * @brief Take a pressure data calibrated by coefficient values
    * @return Pressure data by float
    */
    float pressure_acquisition();

    /**
    * @brief Take coefficient values: Once executed, a0, b1, b2, c12 are filled. No need to re-execution
    */
    void coefficient_acquisition();

    /**
    * @brief Function for register access
    * @param 0 for write, non-0 for read
    * @param regAddress 6-bit register address to access
    * @return Register value
    */
    uint8_t register_access (uint8_t read, uint8_t regAddress);

    /*
    * @param Constructor without paramters
    */
    MPL115A1_Arduino() {}

    /*
    * @param Constructor with unsigned int number: This sets the Arduino pin number for /SHDN pin
    * @param num digital pin number for /SHDN pin
    */
    MPL115A1_Arduino(uint8_t num) {SHDN=num;}
};

#endif