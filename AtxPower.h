/*
 * AtxPower - Class for powering on and off an ATX power source from an Arduino
 *
 *  Created on: 12 xan, 2016
 *  Author: Hadrián Candela Iglesias
 *  Copyright 2015 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
 *  Project link: https://github.com/c4ndel4/AtxPower
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * 0.1  12  Jan 2016 - initial release
 */

#ifndef ATXPOWER_H_
#define ATXPOWER_H_


#if defined (ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif


typedef struct {
  uint8_t pinPowerOk;
  uint8_t pinPowerOn;
  uint8_t pinPowerInt;
} AtxPowerConfig;

class AtxPower {
    
  public:

    AtxPower(AtxPowerConfig config);
    ~AtxPower();
    void readPowerInt();
    bool getPowerStatus();
    void addPowerOnResponse(void(*function)());
    void addPowerOffResponse(void(*function)());
    void debug();

  private:

    typedef struct {
      void (*function)();
    } FunctionList;

    AtxPowerConfig _config;
    bool _powerStatus;
    FunctionList *_powerOnResponseList;
    byte _powerOnListCount;
    FunctionList *_powerOffResponseList;
    byte _powerOffListCount;
    void setPowerStatus(bool powerStatus);

};


#endif /* ATXPOWER_H_ */
