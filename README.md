#TimerOne Library#

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
Foo.stop();
```
## Start a task
```C++
Foo.start();
```
## Change a task's period
```C++
Foo.setPeriod(500);
```

You can read example [Blink_AnalogRead](https://github.com/maisonsmd/msTask/examples/Blink_AnalogRead/Blink_AnalogRead.ino) to know how to use.
