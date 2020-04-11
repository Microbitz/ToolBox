#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define pulse_ip 7
int ontime, offtime, duty;
float ontime_f, offtime_f;
float freq, period;
float TiempoH, TiempoL;
int Salida;
bool rise = true;
bool fall = false;


void setup()
{
  Serial.begin(9600);
  pinMode(pulse_ip, INPUT);


  // TIMER 1 for interrupt frequency 50 Hz:
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 39999;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect) {
  if (rise == true){
    TiempoH = TiempoH + 0.02;
  }
  if (TiempoH > (ontime_f / 1000.0)){
    TiempoH = 0.0;
    fall = true;
    rise = false;
  }
  if (fall == true){
    TiempoL = TiempoL + 0.02;
  }
  if (TiempoL > (offtime_f / 10000.0)){
    TiempoL = 0.0;
    rise = true;
    fall = false;
  }
}

void loop()
{
  ontime = pulseIn(pulse_ip, HIGH);
  offtime = pulseIn(pulse_ip, LOW);
  ontime_f = float(ontime);
  offtime_f = float(offtime);
  Serial.print(20);
  Serial.print(",");
  Serial.print(rise*10+(fall*-1));
  Serial.print(",");
  Serial.println(-10);
}
