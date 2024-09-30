/*******************************************************************************
* RoboCore BRIICK Keypad - Read Buttons with LED (v1.0)
* 
* Simple program to read all the buttons of the BRIICK Keypad and update the
* corresponding LED.
* 
* Copyright 2024 RoboCore.
* Written by Francois (14/08/2024).
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

uint8_t buttons = 0;

void setup() {
  // configure the serial communication
  Serial.begin(115200);

  // configure the BRIICK
  Serial.println(keypad.config());

  // attach the LED
  keypad.attachLED(KEYPAD_LED_1); // attach one LED at a time
  keypad.attachLED(KEYPAD_LED_2);
  keypad.attachLED(KEYPAD_LED_3 | KEYPAD_LED_4); // attach two or more LED at a time
  // keypad.attachLED(KEYPAD_LED_ALL); // or attach all the LED at the same time
}

void loop() {
  // read all the buttons
  buttons = keypad.readButton(KEYPAD_BTN_ALL);

  // check for read error
  if (buttons == KEYPAD_ERROR){
    Serial.println("ERROR");
  }

  // check if button 1
  if (buttons & KEYPAD_BTN_1){
    Serial.println("Button 1 was pressed");
  }
  // check if button 2
  if (buttons & KEYPAD_BTN_2){
    Serial.println("Button 2 was pressed");
  }
  // check if button 3
  if (buttons & KEYPAD_BTN_3){
    Serial.println("Button 3 was pressed");
  }
  // check if button 4
  if (buttons & KEYPAD_BTN_4){
    Serial.println("Button 4 was pressed");
  }

  delay(100); // just for a little filtering of the output on the serial terminal
}
