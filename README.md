# AtxPower
Class for powering on and off an ATX power source from an Arduino

You must connect the ATX (purple wire) standby 5v power supply to one 5v arduino input and GND to GND.

Then, you can connect the ATX (gray wire) Power Good (or Power OK) signal to one digital arduino pin
And the ATX (green wire) Power On to another digital arduino pin.
Now, connect a button to another arduino pin and you are ready to use the library.

You only need to inform in what pins are conected the three pins
	AtxPowerConfig config = {.pinPowerOk=4, .pinPowerOn=7, .pinPowerInt=2};
and get the object;
	AtxPower * atxPower = new AtxPower(config);

Now, in setup you can set what methods you want to execute on power On and Off
	atxPower->addPowerOnResponse(onPowerOn);
	atxPower->addPowerOffResponse(onPowerOff);

And each loop 
	atxPower->readPowerInt();
	if(atxPower->getPowerStatus()) {
		//Do something
	}