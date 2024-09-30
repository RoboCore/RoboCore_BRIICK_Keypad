#ifndef BRIICK_KEYPAD_H
#define BRIICK_KEYPAD_H

/*******************************************************************************
* RoboCore BRIICK Keypad Library (v1.0)
* 
* Library to use the BRIICK Keypad v1.0.
* 
* Copyright 2024 RoboCore.
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

#define BRIICK_KEYPAD_DEBUG

// --------------------------------------------------
// Libraries

#include <stdint.h>

#include <Wire.h>

#ifdef BRIICK_KEYPAD_DEBUG
#include <Stream.h>
#endif

// --------------------------------------------------
// Macros

#ifndef HIGH
#define HIGH (1)
#define LOW (0)
#endif

#define KEYPAD_ADDRESS (0x27) // default address

#define KEYPAD_REGISTER_INPUT   (0x00)
#define KEYPAD_REGISTER_OUTPUT  (0x01)
#define KEYPAD_REGISTER_CONFIG  (0x03)

#define KEYPAD_ERROR   (0x81)

#define KEYPAD_BTN_1   (0x04)
#define KEYPAD_BTN_2   (0x08)
#define KEYPAD_BTN_3   (0x10)
#define KEYPAD_BTN_4   (0x20)
#define KEYPAD_BTN_ALL  (KEYPAD_BTN_1 | \
                        KEYPAD_BTN_2 | \
                        KEYPAD_BTN_3 | \
                        KEYPAD_BTN_4)

#define KEYPAD_LED_1   (0x01)
#define KEYPAD_LED_2   (0x02)
#define KEYPAD_LED_3   (0x40)
#define KEYPAD_LED_4   (0x80)
#define KEYPAD_LED_ALL  (KEYPAD_LED_1 | \
                        KEYPAD_LED_2 | \
                        KEYPAD_LED_3 | \
                        KEYPAD_LED_4)

// --------------------------------------------------
// Class - BRIICK Keypad

class BRIICK_Keypad {
  public:
    BRIICK_Keypad(void);
    BRIICK_Keypad(uint8_t);

    bool attachLED(uint8_t);
    bool buttonPressed(uint8_t);
    bool config(void);
    bool detachLED(uint8_t);
    uint8_t readButton(uint8_t);
    bool setLED(uint8_t, uint8_t);
  
#ifdef BRIICK_KEYPAD_DEBUG
    void setDebugger(Stream &);
#endif

  private:
    uint8_t _address;
    uint8_t _buttonState;
    bool _initialized;
    uint8_t _ledAttached;
    uint8_t _ledState;

#ifdef BRIICK_KEYPAD_DEBUG
    Stream * _debugger;
#endif

    bool _updateLED(void);
};

// --------------------------------------------------

#endif // BRIICK_KEYPAD_H
