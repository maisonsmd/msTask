/*
	Name:       FlashLED.ino
	Created:	08/20/2018 17:26:10
	Author:     maisonsmd

	This example show how to flash a LED using 2 tasks
*/
#include <msTask.h>

//function declarations to make the compiler happy

void TurnLedOn();
void TurnLedOff();

//create tasks, minimum period is 5ms
msTask taskOn(1000, TurnLedOn);
msTask taskOff(10, TurnLedOff);

void TurnLedOn() {
	//turn LED on, start taskOff to turn LED off in next 10ms
	digitalWrite(LED_BUILTIN, HIGH);
	taskOff.start();
}
void TurnLedOff() {
	//turn LED off and stop taskOff, wait taskOn to turn LED on again, repeat
	digitalWrite(LED_BUILTIN, LOW);
	taskOff.stop();
}
void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	//call once
	msTask::init();
}

void loop()
{
	//nothing to do
}
