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

