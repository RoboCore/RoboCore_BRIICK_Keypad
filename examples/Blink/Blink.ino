/*******************************************************************************
* RoboCore BRIICK Keypad - Blink (v1.0)
* 
* Simple program to blink all the LEDs of the BRIICK Keypad.
* 
* Copyright 2024 RoboCore.
* Written by Francois (27/06/2024).
* 
* 
* This file is part of the BRIICK Keypad library by RoboCore ("RoboCore-BRIICK-Keypad-lib").
* 
* "RoboCore-BRIICK-Keypad-lib" is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* "RoboCore-BRIICK-Keypad-lib" is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public License
* along with "RoboCore-BRIICK-Keypad-lib". If not, see <https://www.gnu.org/licenses/>
*******************************************************************************/

#include <BRIICK_Keypad.h>

BRIICK_Keypad keypad;

const uint16_t DELAY_TIME = 1000; // [ms]

void setup() {
  // configure the serial communication
  Serial.begin(115200);

  // configure the BRIICK
  Serial.println(keypad.config());
}

void loop() {
  // blink LED 1
  keypad.setLED(KEYPAD_LED_1, HIGH);
  delay(DELAY_TIME);
  keypad.setLED(KEYPAD_LED_1, LOW);
  delay(DELAY_TIME);

  // blink LED 2
  keypad.setLED(KEYPAD_LED_2, HIGH);
  delay(DELAY_TIME);
  keypad.setLED(KEYPAD_LED_2, LOW);
  delay(DELAY_TIME);
  
  // blink LED 3
  keypad.setLED(KEYPAD_LED_3, HIGH);
  delay(DELAY_TIME);
  keypad.setLED(KEYPAD_LED_3, LOW);
  delay(DELAY_TIME);
  
  // blink LED 4
  keypad.setLED(KEYPAD_LED_4, HIGH);
  delay(DELAY_TIME);
  keypad.setLED(KEYPAD_LED_4, LOW);
  delay(DELAY_TIME);
  
  // blink all
  keypad.setLED(KEYPAD_LED_ALL, HIGH);
  delay(DELAY_TIME);
  keypad.setLED(KEYPAD_LED_ALL, LOW);
  delay(DELAY_TIME);
}
