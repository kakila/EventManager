EventManager
================

A library for attaching *Callbacks* to *Event Publishers* for the Dwenguino/Arduino platform.

Introduction
------------
It is quite common to associate a function call to an event.
For example, if pin **X** of the board goes **UP** one would like to turn a **LED** on.
To do this we need an object (the Manager) that knows that function `ledOn` should be called
when X goes up. Something like:

```
manager.bind (ledOn, X_up)
```

Here `manager` is the object that knows the relation betwen the *callback*[[1]](#callback) `ledOn`
and the *event publisher* `X_up`.


### Concrete Example

The example above can be made concrete. Lets say we waiting for a LOW in pin 2 (which
was correctly configured). The code looks like:
```c++
#include <EventManager.h>

class Publisher: public EventPublisher
{
  uint8_t pin;
  unsigned int sinceLast;

  public:
    // This is the constructor. It is called
    // whenever we create an instance of this class.
    // It sets the parameters.
    Publisher(uint8_t P): pin(P), sinceLast(0){};

    // Here we say if the event was triggered,
    // We check for a LOW in pin.
    // We check every 200 ms to allow human input
    bool is_triggered()
    {
       bool is_down = false;
       if (millis()- sinceLast > 200)
       {
          sinceLast = millis();
          is_down   =  (digitalRead(pin) == LOW);
       };
      return is_down;
    }
};

// The pin with the led
const int ledPin = 13;

// Here we define the callback (assume we have a led on ledPin).
// All callbacks should receive a pointer to Event.
// Here we do not use it because this is a silly example
void writeHIGHtoPin(const Event * ev)
{
  static bool state = false; // just to remember the button state
  if (state)
  {
    digitalWrite(ledPin, LOW);
    state = false;
  }
  else
  {
    digitalWrite(ledPin, HIGH);
    state = true;
  }
}

// The pin with the button
const int buttonPin = 2;
// We create an instance of the class
// saying that it should pulish events on buttonPin
Publisher pin_is_high(buttonPin);

// We create the callback
Callback ledOn = writeHIGHtoPin;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  // We bind the callback and the event publisher
  dwenguinoManager.bind(ledOn, pin_is_high);
}

void loop()
{
  dwenguinoManager.update();
}
```

See the `examples` folder for this and other examples of use.

Related libraries
-----------------
* [Bounce](http://playground.arduino.cc/Code/Bounce)

* [Messenger](http://playground.arduino.cc/Code/CmdMessenger)


<a name="callback">[1]</a>: Callback is a fancy name for functions that are called
when something happens.
