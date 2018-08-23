/*
	Name:       Blink_AnalogRead.ino
	Created:	08/20/2018 17:26:10
	Author:     maisonsmd
*/

#include <msTask.h>

//function declarations to make the compiler happy
void BlinkTask();
void AnalogTask();

//create tasks, minimum period is 5ms
msTask taskBlink(1000, BlinkTask);
msTask taskAnalogRead(300, AnalogTask);

void BlinkTask() {
	//task must be done as fast as possible,
	//delay functions are not recommended

	//toggle LED 13 every 1 second
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void AnalogTask() {
	//task must be done as fast as possible,
	//delay functions are not recommended

	//print analogRead(A0) every 300ms
	Serial.print("analogRead: ");
	Serial.println(analogRead(A0));
}

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(9600);
	Serial.setTimeout(20);
	//call once
	msTask::init();
}

void loop()
{
	//these line is not necessary, just for demonstration purpose
	if (Serial.available()) {
		char c = Serial.read();
		if (c == 'S') {
			//you can stop a task with:
			taskAnalogRead.stop();

			Serial.println("you stopped taskAnalogRead");
			//type "S" in serial terminal to test
		}
		else if (c == 'R') {
			//or restart it with:
			taskAnalogRead.start();

			Serial.println("you started taskAnalogRead");
			//type "R" in serial terminal to test
		}
		else if (c == 'P') {
			uint32_t ms = Serial.parseInt();
			//or change a task's period with:
			taskAnalogRead.setPeriod(ms);

			Serial.print("you set taskAnalogRead's period to: ");
			Serial.println(ms);
			//type Px in serial terminal to test
			//with x is number of milliseconds
			//ex: P1000
		}
	}
}
