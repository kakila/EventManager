#include <Wire.h>
#include <LiquidCrystal.h>
#include <Dwenguino.h>
#include <CallbckPubManager.h>

enum button_name {N,W,S,E,C};

class ButtonOnPressingPublisher: public EventPublisher
{
  uint8_t port;
  public:
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

    bool is_triggered()
    {
      return (digitalRead(port) == PRESSED);
    };
};

void notify(const Event * ev)
{
    switch (ev->get_type())
    {
      case button_name::N: LEDS = LEDS ^ 0b10000000; break;
      case button_name::S: LEDS = LEDS ^ 0b00000001; break;
      case button_name::W: LEDS = LEDS ^ 0b00100000; break;
      case button_name::E: LEDS = LEDS ^ 0b00000100; break;
      case button_name::C: LEDS = LEDS ^ 0b00011000; break;
    }
}

////////////////////////////////
callback ButtonListener = notify;
ButtonOnPressingPublisher is_N_pressed(button_name::N);
ButtonOnPressingPublisher is_S_pressed(button_name::S);
ButtonOnPressingPublisher is_W_pressed(button_name::W);
ButtonOnPressingPublisher is_E_pressed(button_name::E);
ButtonOnPressingPublisher is_C_pressed(button_name::C);

void setup()
{
  initDwenguino();
  dwenguinoManager.bind(ButtonListener, is_N_pressed);
  dwenguinoManager.bind(ButtonListener, is_S_pressed);
  dwenguinoManager.bind(ButtonListener, is_W_pressed);
  dwenguinoManager.bind(ButtonListener, is_E_pressed);
  dwenguinoManager.bind(ButtonListener, is_C_pressed);

  LEDS = 0;
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

