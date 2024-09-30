/*******************************************************************************
* RoboCore BRIICK Keypad - Read Buttons (v1.0)
* 
* Simple program to read all the buttons of the BRIICK Keypad.
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

void setup() {
  // configure the serial communication
  Serial.begin(115200);

  // configure the BRIICK
  Serial.println(keypad.config());
}

void loop() {
  // read button 1
  if (keypad.readButton(KEYPAD_BTN_1) == HIGH) { // method 1
    Serial.println("Button 1 was pressed");
  }

  // read button 2
  if (keypad.readButton(KEYPAD_BTN_2) == HIGH) { // method 1
    Serial.println("Button 2 was pressed");
  }

  // read button 3
  if (keypad.buttonPressed(KEYPAD_BTN_3)) { // method 2
    Serial.println("Button 3 was pressed");
  }

  // read button 4
  if (keypad.buttonPressed(KEYPAD_BTN_4)) { // method 2
    Serial.println("Button 4 was pressed");
  }

  delay(100); // just for a little filtering of the output on the serial terminal
}
