# msTask

This library is based on Paul Stoffregen's TimerOne library that provide ability to add more than one callback, which I called "task"

To use this library, you'll need to install Paul Stoffregen's TimerOne as well:

https://github.com/PaulStoffregen/TimerOne

# Usage
## Create task:
```C++
msTask fooTask(1000, Foo);
msTask barTask(5000, Bar);
```
* The first parameter is task's period

* The second is the callback function:

```C++
void Foo(){
	//your Foo task's code here
}

void Bar(){
	//your Bar task's code here
}
```
## Init task
This function must be call in setup() once
```C++
msTask::init();
```

## Stop a task
```C++
fooTask.stop();
```
## Start a task
```C++
fooTask.start();
```
## Change a task's period
```C++
fooTask.setPeriod(500);
```
## Change a task's callback
```C++
fooTask.setCallback(Bar);
```
You can read example [Blink+AnalogRead](https://github.com/maisonsmd/msTask/blob/master/examples/Blink_AnalogRead/Blink_AnalogRead.ino), [FlashLED](https://github.com/maisonsmd/msTask/blob/master/examples/FlashLED/FlashLED.ino) or [TrafficLight](https://github.com/maisonsmd/msTask/blob/master/examples/TrafficLight/TrafficLight.ino)
to know how to use.
