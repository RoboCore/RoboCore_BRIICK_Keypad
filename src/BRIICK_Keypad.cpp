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

// --------------------------------------------------
// Libraries

#include <BRIICK_Keypad.h>

// --------------------------------------------------
// --------------------------------------------------

// Constructor (default)
BRIICK_Keypad::BRIICK_Keypad(void) :
  BRIICK_Keypad(KEYPAD_ADDRESS) // call the main constructor
{
  // nothing to do
}

// --------------------------------------------------

// Constructor
//  @param (address) : the I2C address of the device [uint8_t]
BRIICK_Keypad::BRIICK_Keypad(uint8_t address) :
#ifdef BRIICK_KEYPAD_DEBUG
  _debugger(nullptr),
#endif
  _address(address),
  _initialized(false),
  _buttonState(0),
  _ledAttached(0),
  _ledState(0)
{
  // nothing to do
}

// --------------------------------------------------
// --------------------------------------------------

// Attach one or more LED to its button
//  @param (led) : the LED to attach (bitwise) [uint8_t]
//  @returns true if successful [bool]
bool BRIICK_Keypad::attachLED(uint8_t led) {
  // check if initialized
  if (!this->_initialized) {
    return false;
  }

  // check the parameter
  if (led & ~KEYPAD_LED_ALL) {
    return false;
  }

  // update the list of attached LED
  this->_ledAttached |= led;

  return true;
}

// --------------------------------------------------

// Check if a button is pressed
//  @param (button) : the button to read (bitwise) [uint8_t]
//  @returns true if pressed [bool]
bool BRIICK_Keypad::buttonPressed(uint8_t button) {
  // check if initialized
  if (!this->_initialized) {
    return false;
  }

  uint8_t res = this->readButton(button);

  if (res != KEYPAD_ERROR){
    // check for single button or bitwise combination
    if ((button == KEYPAD_BTN_1) || \
      (button == KEYPAD_BTN_2) || \
      (button == KEYPAD_BTN_3) || \
      (button == KEYPAD_BTN_4)) {
      if (res == HIGH){
        return true;
      }
    } else if (res & button){
      return true;
    }
  }

  return false;
}

// --------------------------------------------------

// Configure the BRIICK
//  @returns true if successful [bool]
bool BRIICK_Keypad::config(void) {
  // check if already initialized
  if (this->_initialized) {
    return true;
  }

  // start the I2C communication
  Wire.begin();

  // configure the GPIO
  uint8_t register_mask = KEYPAD_BTN_ALL; // buttons as inputs and LEDs as outputs
  Wire.beginTransmission(this->_address);
  Wire.write(KEYPAD_REGISTER_CONFIG);
  Wire.write(register_mask);
  if (Wire.endTransmission() == 0) {
    this->_initialized = true; // set
    
    // turn off the LEDs
    this->setLED(KEYPAD_LED_ALL, LOW);
  } else {
#ifdef BRIICK_KEYPAD_DEBUG
    if (this->_debugger != nullptr) {
      this->_debugger->println("Couldn't access the keypad");
    }
#endif
  }

  return this->_initialized;
}

// --------------------------------------------------

// Detach one or more LED from its button
//  @param (led) : the LED to detach (bitwise) [uint8_t]
//  @returns true if successful [bool]
bool BRIICK_Keypad::detachLED(uint8_t led) {
  // check if initialized
  if (!this->_initialized) {
    return false;
  }

  // check the parameter
  if (led & ~KEYPAD_LED_ALL) {
    return false;
  }

  // update the list of attached LED
  this->_ledAttached &= ~led;

  return true;
}

// --------------------------------------------------

// Read one or more buttons
//  @param (button) : the button to read (bitwise) [uint8_t]
//  @returns the state of the buttons (bitwise - when asked) or KEYPAD_ERROR on error [uint8_t]
//  Note: HIGH means button pressed.
uint8_t BRIICK_Keypad::readButton(uint8_t button) {
  // Notes on the error value
  //  - 0 doesn't work as a return value because it also means no button pressed.
  //  - 0xFF can work as a return value, but it can be intepreted as all buttons pressed (bitwise).
  //  - -1 can work as a return value, but it can be intepreted as all buttons pressed (bitwise).
  //  - KEYPAD_ERROR is the alternative to keep the value as [uint8_t], still be bitwise and not interfere with the buttons.

  // check if initialized
  if (!this->_initialized) {
    return KEYPAD_ERROR;
  }

  // check the parameters
  if (button & ~KEYPAD_BTN_ALL) {
    return KEYPAD_ERROR;
  }

  // get the data
  uint8_t data = KEYPAD_ERROR;
  Wire.beginTransmission(this->_address);
  Wire.write(KEYPAD_REGISTER_INPUT);
  if (Wire.endTransmission() == 0) {
    if (Wire.requestFrom(this->_address, static_cast<uint8_t>(1)) > 0) {
      data = Wire.read();
      data &= KEYPAD_BTN_ALL; // mask the buttons here because <Wire.read()> can return 0xFF if all eight GPIO of the I2C chip are being used
    }
  }

  // handle the data
  if (data != KEYPAD_ERROR) {
    this->_buttonState = data; // update

    // udpate the attached LEDs
    this->_updateLED();

    // check for single button or bitwise combination
    if ((button == KEYPAD_BTN_1) || \
        (button == KEYPAD_BTN_2) || \
        (button == KEYPAD_BTN_3) || \
        (button == KEYPAD_BTN_4)) {
      return (this->_buttonState & button) ? HIGH : LOW;
    } else {
      return this->_buttonState;
    }
  } else {
#ifdef BRIICK_KEYPAD_DEBUG
    if (this->_debugger != nullptr) {
      this->_debugger->println("Couldn't read the keypad");
    }
#endif
  }

  return data;
}

// --------------------------------------------------

// Set the debugger of the object
//  @param (stream) : the stream to print to [Stream &]
#ifdef BRIICK_KEYPAD_DEBUG
void BRIICK_Keypad::setDebugger(Stream & stream) {
  this->_debugger = &stream;
}
#endif // BRIICK_KEYPAD_DEBUG

// --------------------------------------------------

// Set the state of one or more LED
//  @param (led) : the LED to set (bitwise) [uint8_t]
//  @param (level) : the level to set (0 or 1) [uint8_t]
//  @returns true if successful [bool]
bool BRIICK_Keypad::setLED(uint8_t led, uint8_t level) {
  // check if initialized
  if (!this->_initialized) {
    return false;
  }

  // check the parameters
  if ((led & ~KEYPAD_LED_ALL) || (level > HIGH)) {
    return false;
  }

  // check if attached
  if (led & this->_ledAttached) {
    // don't update an attached LED
    return false;
  }
  // update according to the level
  if (level == HIGH){
    led |= this->_ledState;
  } else {
    led = this->_ledState & ~led;
  }

  // send the data
  Wire.beginTransmission(this->_address);
  Wire.write(KEYPAD_REGISTER_OUTPUT);
  Wire.write(led);
  if (Wire.endTransmission() == 0) {
    this->_ledState = led; // update
    return true;
  } else {
#ifdef BRIICK_KEYPAD_DEBUG
    if (this->_debugger != nullptr) {
      this->_debugger->println("Couldn't write to the keypad");
    }
#endif
  }

  return false;
}

// --------------------------------------------------

// Update the states of the attached LED
//  @returns true if successful [bool]
bool BRIICK_Keypad::_updateLED(void) {
  // check if initialized
  if (!this->_initialized) {
    return false;
  }

  // check if there are LED attached
  if (!this->_ledAttached) {
    return true;
  }

  // set the data to be sent
  uint8_t data = this->_ledState;
  const uint8_t MASKS[2][4] = { { KEYPAD_LED_1, KEYPAD_LED_2, KEYPAD_LED_3, KEYPAD_LED_4} , \
                                { KEYPAD_BTN_1, KEYPAD_BTN_2, KEYPAD_BTN_3, KEYPAD_BTN_4 } };
  for (uint8_t i=0 ; i < 4 ; i++) {
    if (this->_ledAttached & MASKS[0][i]) {
      if (this->_buttonState & MASKS[1][i]) {
        data |= MASKS[0][i];
      } else {
        data &= ~MASKS[0][i];
      }
    }
  }

  // send the data
  Wire.beginTransmission(this->_address);
  Wire.write(KEYPAD_REGISTER_OUTPUT);
  Wire.write(data);
  if (Wire.endTransmission() == 0) {
    this->_ledState = data; // update
    return true;
  } else {
#ifdef BRIICK_KEYPAD_DEBUG
    if (this->_debugger != nullptr) {
      this->_debugger->println("Couldn't write to the keypad");
    }
#endif
  }

  return false;
}

// --------------------------------------------------
