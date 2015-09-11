EventManager
================

A library for attaching *Callbacks* to *Event Publishers* for the Dwenguino/Arduino platform.

Introduction
------------
It is quite comon to associate a function call to an event. 
For example, if pin **X** of the board goes **UP** one would like to turn a **LED** on.
To do this we need an object (the Manager) that knows that function `ledOn` should be called
when X goes up. Something like:

```
manager.bind (ledOn, X_up)
```

Here `manager` is the object that knows the relation betwen the *callback*[[1]](#callback) `ledOn` 
and the *event publisher* `X_up`.


### Concrete Example

The example above can be made concrete. Lets say we waiting for a 0 in pin 5 (which 
was correctly configured). The code looks like:
```
class Publisher: public EventPublisher
{
  uint8_t pin;
  unsigned int sinceLast;

  public:
    // This is the constructor. It is called
    // whenever we create an instance of this class.
    Publisher(uint8_t P){ pin = P; sinceLast = 0; };

    // Here we say if the event was triggered,
    // that is we check for a 0 in pin.
    // We check every 200 ms to allow human input
    bool is_triggered()
    { 
       bool is_down = false;
       if (millis()- sinceLast > 200)
       {
          sinceLast = millis();
          is_down   =  (digitalRead(pin) == 0);
       };
      return is_down;
    }
};

// Here we define the callback (assume we have aled on pin 3).
// All callbacks should receive a pointer to Event, but here we
// do not need it, since it is a silly example.
void writeHIGHtoPin(const Event * ev){ digitalWrite(3, HIGH); }

// We create an instance of the class 
// saying that it should pulish events on pin 5
Publisher pin_is_zero(5);

// We create the callback
Callback ledOn = writeHIGHtoPin;

void setup()
{
  // We bind the callback and the event publisher
  dwenguinoManager.bind(ledOn, pin_is_zero);
}

void loop()
{
  dwenguinoManager.update();
}
```

Related libraries
-----------------
* [Bounce](http://playground.arduino.cc/Code/Bounce)

* [Messenger](http://playground.arduino.cc/Code/CmdMessenger)


<a name="callback">[1]</a>: Callback is a fancy name for functions that are called 
when something happens.

