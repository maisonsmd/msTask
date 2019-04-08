/*
	Name:       msTask.h
	Created:	08/20/2018 17:26:10
	Author:     WILDLIFE\maisonsmd
*/

//TimeOne extended library with multiple callback
#ifndef _MSTIMERONE_h
#define _MSTIMERONE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <TimerOne.h>

class msTask {
private:
	static volatile msTask ** callbacks;
	static volatile uint8_t nCallbacks;
	volatile static uint32_t _micros;
	volatile static uint32_t lastPeriod;
	volatile static uint32_t lastMicrosSetPeriod;
	volatile static boolean taskPeriodChanged;
	volatile uint32_t nextMicros = 0UL;
	volatile uint32_t period = 1000000UL;
	volatile boolean enable;
	void(*isrCallBack)();
	static TimerOne timer;

	static void mainISR() {
		uint32_t elapsed = micros();
		timer.stop();
		//reduce error between timer1 and micros()
		if (taskPeriodChanged) {
			_micros += micros() - lastMicrosSetPeriod;
			taskPeriodChanged = false;
		} else
			_micros += lastPeriod;
		uint32_t minMicros = 4294967295UL;
		for (uint8_t i = 0; i < getCount(); i++) {
			if (getTasks()[i]->enable == false)
				continue;
			if (_micros >= getTasks()[i]->nextMicros) {
				getTasks()[i]->nextMicros = _micros + getTasks()[i]->period;
				if (getTasks()[i]->isrCallBack != nullptr)
					getTasks()[i]->isrCallBack();
			}
			if (getTasks()[i]->nextMicros < minMicros) {
				minMicros = getTasks()[i]->nextMicros;
			}
		}
		//to avoid var overflow
		if (_micros > 3294967295UL) {
			for (uint8_t i = 0; i < getCount(); i++) {
				getTasks()[i]->nextMicros -= _micros;
			}
			minMicros -= _micros;
			_micros = 0UL;
		}

		elapsed = micros() - elapsed;
		//10: offset, to make sure interrupts are called
		if (minMicros >= _micros + elapsed) {
			timer.setPeriod(minMicros - _micros - elapsed);
			lastPeriod = minMicros - _micros;
		}
		//10: offset, to make sure interrupts are called
		else if (minMicros >= _micros) {
			timer.setPeriod(minMicros - _micros);
			lastPeriod = minMicros - _micros;
		}
		lastMicrosSetPeriod = micros();
	}

	void create(uint32_t period, void(*callback)()) {
		if (period < 5UL)
			period = 5UL;
		this->enable = true;
		this->period = period * 1000UL;
		this->isrCallBack = callback;

		volatile msTask ** temp = new volatile msTask *[nCallbacks + 1];
		for (uint8_t i = 0; i < nCallbacks; i++) {
			temp[i] = callbacks[i];
		}
		temp[nCallbacks] = this;
		if (callbacks != nullptr)
			delete[] callbacks;
		callbacks = temp;

		msTask::nCallbacks++;
	}
public:
	msTask(uint32_t period, void(*callback)()) {
		create(period, callback);
	}
	msTask(const msTask & msTimerOne_) {
		create(msTimerOne_.period, msTimerOne_.isrCallBack);
	}
	msTask(const msTask * msTimerOne_) {
		create(msTimerOne_->period, msTimerOne_->isrCallBack);
	}
	msTask() {
		create(1000, nullptr);
	}
	static void init() {
		timer.stop();
		uint32_t minMicros = 4294967295UL;
		for (uint8_t i = 0; i < getCount(); i++) {
			getTasks()[i]->nextMicros = getTasks()[i]->period + _micros;
			if (getTasks()[i]->nextMicros < minMicros)
				minMicros = getTasks()[i]->nextMicros;
		}
		timer.attachInterrupt(mainISR);
		timer.initialize(minMicros - _micros);
		lastPeriod = minMicros - _micros;
		lastMicrosSetPeriod = micros();
	}
	void start() {
		enable = true;
		this->nextMicros = _micros + this->period;
	}
	void stop() {
		enable = false;
	}
	boolean isRunning() {
		return enable;
	}
	uint32_t getPeriod() {
		return period;
	}
	void setPeriod(uint32_t period) {
		timer.stop();
		_micros += micros() - lastMicrosSetPeriod;
		if (period < 5UL)
			period = 5UL;
		this->period = period * 1000UL;
		this->nextMicros = _micros + this->period;

		uint32_t minMicros = 4294967295UL;
		for (uint8_t i = 0; i < getCount(); i++) {
			if (getTasks()[i]->nextMicros < minMicros)
				minMicros = getTasks()[i]->nextMicros;
		}
		if (minMicros > _micros)
			timer.setPeriod(minMicros - _micros);
		else
			timer.setPeriod(10);
		lastPeriod = minMicros - _micros;
		lastMicrosSetPeriod = micros();

		taskPeriodChanged = true;
	}
	void setCallback(void(*callback)()) {
		isrCallBack = callback;
	}
	static uint8_t getCount() {
		return nCallbacks;
	}
	static volatile msTask ** getTasks() {
		return callbacks;
	}
};

volatile msTask ** msTask::callbacks = nullptr;
volatile uint8_t msTask::nCallbacks = 0;
volatile uint32_t msTask::_micros = 0;
volatile uint32_t msTask::lastPeriod = 0;
volatile uint32_t msTask::lastMicrosSetPeriod = micros();
volatile boolean msTask::taskPeriodChanged = false;
#endif
