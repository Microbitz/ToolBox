#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <Servo.h>
Servo myservo;

//Botones..............................................INICIALIZACION
bool Standby = false;
bool MaxMin = false;
float T_on;
float Desf;
int DIN1 = A0;
int DIN2 = A1;
int DIN3 = A2;
int Dstate1 = 0;
int Dstate2 = 0;
int Dstate3 = 0;
int V1;


void setup() {
  myservo.attach(9);
  pinMode(DIN1, INPUT);
  pinMode(DIN2, INPUT);
  pinMode(DIN3, INPUT);
  Serial.begin(9600);
  //LCD.........................................................CONFIG
  lcd.init();
  lcd.home ();
  lcd.setBacklight(HIGH);
  lcd.clear ();
  lcd.print("Angulo:");
  lcd.setCursor ( 0, 1 );
  lcd.print(V1);

  //Interrupcion TIMER1.......................................CONFIG
  cli();
  TCCR2A  = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 249;
  TCCR2B |= (1 << WGM21);
  TCCR2B |= (0 << CS22) | (1 << CS21) | (0 << CS20);
  TIMSK2 |= (1 << OCIE2A);
  sei(); // allow interrupts
}

//Interrupcion 1 Segundo..................................OPERATIVO
ISR(TIMER2_COMPA_vect) {
  if (Standby == true) {
    T_on = T_on + 0.001;
  }
  if (T_on >= (1.0 + Desf)) {   // tiempo en segundos con decimales si quieres menos cambiar el valor despues de >=
    T_on = 0.0;
    Desf = 0.0;
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
      V1 = V1 - 1;
      if (V1 < 0) V1 = 0;
    }

    if (Dstate2 == HIGH) {
      Standby = true;
      T_on = 0.0;
      V1 = V1 + 1;
      if (V1 > 180) V1 = 180;
    }
  }
  lcd.setCursor ( 0, 0 );
  lcd.print("Angulo:");
  lcd.setCursor ( 0, 1 );
  lcd.print(V1);
  lcd.print("  ");

  myservo.write(V1);
  Serial.println(V1);
}
