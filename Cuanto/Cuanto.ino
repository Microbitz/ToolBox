#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

bool T1 = false;
bool T2 = false;
bool T3 = false;

float T_on;
byte Loops = 0;

void setup() {

  Serial.begin(9600);
  //LCD.........................................................CONFIG
  lcd.init();
  lcd.home ();
  lcd.setBacklight(HIGH);
  lcd.clear ();
  lcd.print("T:");
  lcd.setCursor ( 0, 1 );

  //Interrupcion 1 Segundo......................................CONFIG
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 12499;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}

//Interrupcion 1 Segundo..................................OPERATIVO
ISR(TIMER1_COMPA_vect) {

  if (T_on < 1.0) {
    T_on = T_on + 0.01;
  }

}

void loop() {
  if (T_on < 1.0) {
    Loops = Loops + 1;
  }
  lcd.setCursor ( 0, 1 );
  lcd.print(Loops);  
}
