#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Botones..............................................INICIALIZACION
bool Standby = false;
float T_on;
int DIN1 = A0;
int DIN2 = A1;
int DIN3 = A2;
int Dstate1 = 0;
int Dstate2 = 0;
int Dstate3 = 0;
int V1;
int V2;
int V3;

void setup() {
  pinMode(DIN1, INPUT);
  pinMode(DIN2, INPUT);
  pinMode(DIN3, INPUT);
  Serial.begin(9600);
  //LCD.........................................................CONFIG
  lcd.init();
  lcd.home ();
  lcd.setBacklight(HIGH);
  lcd.clear ();
  lcd.print("Valores:");
  lcd.setCursor ( 0, 1 );
  lcd.print(V1);
  lcd.setCursor ( 4, 1 );
  lcd.print(V2);
  lcd.setCursor ( 8, 1 );
  lcd.print(V3);

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
  if (Standby == true) {
    T_on = T_on + 0.01;
  }
  if (T_on >= 2.0) {   // tiempo en segundos con decimales si quieres menos cambiar el valor despues de >=
    T_on = 0.0;
    Standby = false;
  }
}

void loop() {

  Dstate1 = digitalRead(DIN1);
  Dstate2 = digitalRead(DIN2);
  Dstate3 = digitalRead(DIN3);

  if (Standby == false) {      //Colocar dentro los botones
    if (Dstate1 == HIGH) {
      Standby = true;
      T_on = 0.0;
      V1 = V1 + 1;
      lcd.setCursor ( 0, 1 );
      lcd.print(V1);
    }

    if (Dstate2 == HIGH) {
      Standby = true;
      T_on = 0.0;
      V2 = V2 + 1;
      lcd.setCursor ( 4, 1 );
      lcd.print(V2);
    }

    if (Dstate3 == HIGH) {
      Standby = true;
      T_on = 0.0;
      V3 = V3 + 1;
      lcd.setCursor ( 8, 1 );
      lcd.print(V3);
    }
  }

  if (Standby == true) {
    lcd.setCursor ( 12, 0 );
    lcd.print("STBY");
  }
  if (Standby == false) {
    lcd.setCursor ( 12, 0 );
    lcd.print("    ");
  }


  Serial.println(T_on);
}
