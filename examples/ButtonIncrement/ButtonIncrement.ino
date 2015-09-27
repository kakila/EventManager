// This example makes the 5 buttons of the Dwenguino
// or any swtiches you have connected in the correspoding ports
// increase/decrease variables (N/S value[0], E/W value[1]).
// The amount of increase/decrease depends on how long you keep
// pressing the buttons.Tapping them will give you increments/decrements
// of 1. If you keep pressing them, after you have produced a total change of
// 10, the incrmeent/decrement becomes 10. It keeps going that way till a 1000.

#include <Wire.h>
#include <LiquidCrystal.h>
#include <Dwenguino.h>
#define MAX_EVENTS 6      // Default is MAX_EVENTS 5 we need 6
#define MAX_OBSERVERS 1   // Default is MAX_OBSERVERS 10 we need 1 (we could have left it)
#include <EventManager.h>

/////////////////////////////////
////// Start definitions ////////
int value[2]         = {0};      // These are the values we modifiy with the buttons
int old_value[2]     = {0,0};    // These are just to remember the previous values
int default_value[2] = {-10,30}; // These are default and initial values.

enum button_name {N,W,S,E,C};    // The buttons we are using.

// This class published events (isTriggered returns true) while
// the button defined at construction time is pressed.
class ButtonOnPressingPublisher: public EventPublisher
{
  uint8_t port;

  public:
    // It is created giving the button it should watch
    ButtonOnPressingPublisher(button_name type)
    {
        switch (type)
        {
          case button_name::N: port = SW_N; break;
          case button_name::W: port = SW_W; break;
          case button_name::S: port = SW_S; break;
          case button_name::E: port = SW_E; break;
          case button_name::C: port = SW_C; break;
        }
        event = new Event(type);
    };

    // The event is triggered whenever the given button is pressed.
    bool isTriggered()
    {
      return (digitalRead(port) == PRESSED);
    };
};

// This class published events (isTriggered returns true) only
// wehn any of the buttons is released.
class ButtonOnReleasePublisher: public EventPublisher
{
  const uint8_t port[5] = {SW_N, SW_W,SW_S,SW_E,SW_C};
  bool was_pressed[5] = {false};

  void set_event (const unsigned int &i)
  {
      switch (i)
      {
        case 0: event->type = button_name::N; break;
        case 1: event->type = button_name::W; break;
        case 2: event->type = button_name::S; break;
        case 3: event->type = button_name::E; break;
        case 4: event->type = button_name::C; break;
      }
  };

  public:
    // Once constructed it will check all buttons
    ButtonOnReleasePublisher() { event = new Event(0);};

    // It is triggered when the a button it released. It will not
    // publish two events if two buttons are released simultaneoulsy.
    // For that you need to define a class like ButtonOnPressingPublisher
    // defined before.
    bool isTriggered()
    {
      for (unsigned int i=0; i < 5; i++)
      {
        if (digitalRead(port[i]) == PRESSED) was_pressed[i] = true;
        else if (digitalRead(port[i]) != PRESSED && was_pressed[i])
        {
          was_pressed[i] = false;
          set_event(i);
          return true;
        }
      }
      return false;
    };
};

////////////////////////
/// Helper functions ///

// To print the values to the LCD
void printValue ()
{
    dwenguinoLCD.home();
    dwenguinoLCD.print("0:");
    dwenguinoLCD.print(value[0]);
    dwenguinoLCD.print(" 1:");
    dwenguinoLCD.print(value[1]);
};

// This is a functions that increments or decrements a variable
// depending on the argument dir (1, -1). dir == 0 resets
// the values to defualts.
void changeValue(uint8_t button, int8_t dir)
{
    dwenguinoLCD.clear();

    uint8_t idx;
    if (button == button_name::N || button == button_name::S)
       idx = 0;
    else if (button == button_name::E || button == button_name::W)
       idx = 1;
    else
    {
        value[0] = default_value[0];
        value[1] = default_value[1];
        dwenguinoLCD.setCursor(0,2);
        dwenguinoLCD.print("Reset");
    }

    // If the change is bigger than 10 we increments by 10;
    // If it is bugger than 100 we increment by 100, and so on.
    unsigned int dv = abs (value[idx] - old_value[idx]);
    for (unsigned int i=10; i < 10000; i *= 10)
        if (dv < i){
          value[idx] += (i/10) * dir;
          break;
        }

    printValue();
};

///////////////////////////////////////////
/// Actual actions that will take place ///

// Here we wrap the previous function to give it the signature of a callback
void increase_value (const Event * ev){ changeValue(ev->getType(), 1);};
void decrease_value (const Event * ev){ changeValue(ev->getType(), -1);};
void reset_value    (const Event * ev){ changeValue(ev->getType(), 0);};

// Here we create a callback to store the current values in the old_values
// This way we can calculate the change of the values between events.
void update_old_value(const Event * ev)
{
    uint8_t button = ev->getType();
    if (button == button_name::N || button == button_name::S)
      old_value[0] = value[0];
    else if (button == button_name::E || button == button_name::W)
      old_value[1] = value[1];
};

// We create the callbacks and give them nice names
Callback onButtonIncrease = increase_value;
Callback onButtonDecrease = decrease_value;
Callback onButtonReset    = reset_value;
Callback onReleaseButton  = update_old_value;

////////////////////////////////
/////// Create publishers //////

// We get only one publisher for the release button event
// because it checks all the buttons.
// Then We create one publisher per button to weatch for presses.
// Both classes could be implemented either way, but their behavior
// would be slightly different. Give it a try!
ButtonOnReleasePublisher button_Released;

ButtonOnPressingPublisher is_N_pressed(button_name::N);
ButtonOnPressingPublisher is_S_pressed(button_name::S);
ButtonOnPressingPublisher is_W_pressed(button_name::W);
ButtonOnPressingPublisher is_E_pressed(button_name::E);
ButtonOnPressingPublisher is_C_pressed(button_name::C);

////////////////////////////////
//////// Setup and Loop ////////
void setup()
{
  initDwenguino();
  // Here we say: If N is pressed increase value[0] (check code of changeValue);
  // if S is pressed decrease value[0]; and so on.
  // If you want to have arbitrary variables modified, instead of
  // global ones. You will need to extend the Event class (via inheritance)
  // to contian also a pointer to the varibale that needs ot be changed.
  dwenguinoManager.bind(onButtonIncrease, is_N_pressed);
  dwenguinoManager.bind(onButtonDecrease, is_S_pressed);

  dwenguinoManager.bind(onButtonIncrease, is_E_pressed);
  dwenguinoManager.bind(onButtonDecrease, is_W_pressed);

  dwenguinoManager.bind(onButtonReset,    is_C_pressed);

  dwenguinoManager.bind(onReleaseButton,  button_Released);

  value[0]     = default_value[0];
  old_value[0] = value[0];
  value[1]     = default_value[1];
  old_value[1] = value[1];

  printValue();

}

unsigned int sinceLast = 0;
void loop()
{
    if (millis()- sinceLast > 200)
    {
      sinceLast = millis();
      dwenguinoManager.update();
    }
}
