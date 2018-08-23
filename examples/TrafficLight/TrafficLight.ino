#include <msTask.h>

#define RED_DURATION 5000
#define GREEN_DURATION 4000
#define YELLOW_DURATION 1000

#define RED_PIN 8
#define YELLOW_PIN 9
#define GREEN_PIN 10

void redOn();
void redOff();
void yellowOn();
void yellowOff();
void greenOn();
void greenOff();

msTask task(RED_DURATION, redOff);

void redOn() {
	digitalWrite(RED_PIN, LOW);
	//start a task that wait to turn red light off
	task.setCallback(redOff);
	task.setPeriod(RED_DURATION);
}
void redOff() {
	digitalWrite(RED_PIN, HIGH);
	greenOn();
}
void yellowOn() {
	digitalWrite(YELLOW_PIN, LOW);
	//start a task that wait to turn yellow light off
	task.setCallback(yellowOff);
	task.setPeriod(YELLOW_DURATION);
}
void yellowOff() {
	digitalWrite(YELLOW_PIN, HIGH);
	redOn();
}
void greenOn() {
	digitalWrite(GREEN_PIN, LOW);
	//start a task that wait to turn green light off
	task.setCallback(greenOff);
	task.setPeriod(GREEN_DURATION);
}
void greenOff() {
	digitalWrite(GREEN_PIN, HIGH);
	yellowOn();
}

void setup() {
	pinMode(RED_PIN, OUTPUT);
	pinMode(YELLOW_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);

	//Red lit up first
	redOn();
	yellowOff();
	greenOff();

	msTask::init();
}

void loop() {
	//do other things
}
