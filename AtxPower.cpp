/*
 * AtxPower - Class for powering on and off an ATX power source from an Arduino
 *
 *  Created on: 5 xan, 2016
 *  Author: Hadrián Candela Iglesias
 *  Copyright 2015 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
 *  Project link: https://github.com/c4ndel4/AtxPower
 *
 *  See "AtxPower.h" for purpose, syntax, version history, links, and more.
 */

#include "AtxPower.h"

AtxPower::AtxPower(AtxPowerConfig config): 
          _powerOnResponseList(NULL),
          _powerOnListCount(0),
          _powerOffResponseList(NULL),
          _powerOffListCount(0) {
  _config = config;
  pinMode(_config.pinPowerOk, INPUT);
  pinMode(_config.pinPowerOn, OUTPUT);
  pinMode(_config.pinPowerInt, INPUT_PULLUP);
  digitalWrite(_config.pinPowerOn,HIGH);
  _powerStatus = false;
  while(digitalRead(_config.pinPowerOk));
}

AtxPower::~AtxPower() {
  delete [] _powerOnResponseList;
  delete [] _powerOffResponseList;
}

bool AtxPower::getPowerStatus() {
  return _powerStatus;
}

void AtxPower::setPowerStatus(bool powerStatus) {
  _powerStatus = powerStatus;
  if(_powerStatus) {
    digitalWrite(_config.pinPowerOn, LOW);
    for (byte i = 0; i < _powerOnListCount; i++) {
      (*_powerOnResponseList[i].function)();
    }
  } else {
    for (byte i = 0; i < _powerOffListCount; i++) {
      (*_powerOffResponseList[i].function)();
    }
    digitalWrite(_config.pinPowerOn, HIGH);
  }
}

void AtxPower::readPowerInt() {
  if(!digitalRead(_config.pinPowerInt)) {
    while(!digitalRead(_config.pinPowerInt));
    setPowerStatus(!_powerStatus);
  }
}

void AtxPower::addPowerOnResponse(void(*function)()) {
  _powerOnResponseList = (FunctionList *) realloc(_powerOnResponseList, (_powerOnListCount + 1) * sizeof(FunctionList));
  _powerOnResponseList[_powerOnListCount].function = function;
  _powerOnListCount++;
}

void AtxPower::addPowerOffResponse(void(*function)()) {
  _powerOffResponseList = (FunctionList *) realloc(_powerOffResponseList, (_powerOffListCount + 1) * sizeof(FunctionList));
  _powerOffResponseList[_powerOffListCount].function = function;
  _powerOffListCount++;
}

void AtxPower::debug() {
  Serial.print("Pin Power Ok: ");
  Serial.println(_config.pinPowerOk);
  Serial.print("Pin Power On: ");
  Serial.println(_config.pinPowerOn);
  Serial.print("Pin Power Btn: ");
  Serial.println(_config.pinPowerInt);
  Serial.print("Power Status: ");
  Serial.println(_powerStatus);
}