#include <avr/pgmspace.h>

void setup() {
  pinMode(PIN_PA4, OUTPUT);
  pinMode(PIN_PA1, INPUT);
  pinMode(PIN_PA2, INPUT);
  pinMode(PIN_PA3, INPUT);
  pinMode(PIN_PA5, INPUT);
  pinMode(PIN_PA6, INPUT);
  pinMode(PIN_PA7, INPUT);
  pinMode(PIN_PB0, INPUT_PULLUP);
  pinMode(PIN_PB1, INPUT);
  pinMode(PIN_PB2, INPUT);
  pinMode(PIN_PB3, INPUT);
}

void loop() {
  if (!digitalRead(PIN_PA1)
      || !digitalRead(PIN_PA2)
      || !digitalRead(PIN_PA3)
      || !digitalRead(PIN_PA5)
      || !digitalRead(PIN_PA6)
      || !digitalRead(PIN_PA7)
      || !digitalRead(PIN_PB0)
      || !digitalRead(PIN_PB1)
      || !digitalRead(PIN_PB2)
      || !digitalRead(PIN_PB3)) {
    digitalWrite(PIN_PA4, 0);
  } else {
    digitalWrite(PIN_PA4, 1);
  }
}
