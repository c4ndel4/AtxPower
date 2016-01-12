#include <AtxPower.h>

AtxPowerConfig config = {.pinPowerOk=4, .pinPowerOn=7, .pinPowerInt=2};
   
AtxPower * atxPower = new AtxPower(config);

void setup() {
  Serial.begin(9600);
  atxPower->addPowerOnResponse(onPowerOn);
  atxPower->addPowerOnResponse(debug);
  atxPower->addPowerOffResponse(onPowerOff);
  atxPower->addPowerOffResponse(debug);
}

void loop() {
  atxPower->readPowerInt();
  if(atxPower->getPowerStatus()) {
    //Serial.println("Do something while powered on");
    delay(1);
  }
}

void onPowerOn() {
  Serial.println("Only executed on power on");
}

void onPowerOff() {
  Serial.println("Only executed on power off");
}

void debug() {
  atxPower->debug();
}