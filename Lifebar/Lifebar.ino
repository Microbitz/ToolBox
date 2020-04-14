#include <Adafruit_NeoPixel.h>

//Neopixel.............................................INICIALIZACION
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN        6
#define NUMPIXELS  8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

//Variables............................................INICIALIZACION
const int A7_int = A7;
const int numReadings = 30;   // Numero de muestras
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;
int arranque;
int Life = 8;
float T_impacto = 1.0;
int Sense = 1000;

//Botones..............................................INICIALIZACION
bool Standby = false;
float T_on;


void setup() {

  //NEOPIXEL....................................................CONFIG
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  Serial.begin(9600);
  pixels.clear();

  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.show();

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  //Interrupcion TIMER1.......................................CONFIG
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

ISR(TIMER1_COMPA_vect) {
  if (Standby == true) {
    T_on = T_on + 0.01;
  }
  if (T_on >= T_impacto) {   // tiempo en segundos con decimales si quieres menos cambiar el valor despues de >=
    T_on = 0.0;
    Standby = false;
  }
}

void loop() {
  //Entradas................................................OPERATIVO
  if (arranque < 500) {
    arranque = arranque + 1;
  }

  total = total - readings[readIndex];
  readings[readIndex] = analogRead(A7_int);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  Serial.print(arranque);
  Serial.print(",");
  Serial.print(Life);
  Serial.print(",");
  Serial.println(average);

  //NeoPixel................................................OPERATIVO
  if (Standby == false && arranque >= 500 && average < Sense) {
    Life = Life - 1;
    if (Life < 0)Life = 0;
    Standby = true;
  }

  if (arranque >= 500 && Life == 8) {
    pixels.setPixelColor(0, pixels.Color(5, 0, 0));
    pixels.setPixelColor(1, pixels.Color(5, 0, 0));
    pixels.setPixelColor(2, pixels.Color(5, 0, 0));
    pixels.setPixelColor(3, pixels.Color(5, 0, 0));
    pixels.setPixelColor(4, pixels.Color(5, 0, 0));
    pixels.setPixelColor(5, pixels.Color(5, 0, 0));
    pixels.setPixelColor(6, pixels.Color(5, 0, 0));
    pixels.setPixelColor(7, pixels.Color(5, 0, 0));
    pixels.show();
  }

  if (Life == 7) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(5, 0, 0));
    pixels.setPixelColor(2, pixels.Color(5, 0, 0));
    pixels.setPixelColor(3, pixels.Color(5, 0, 0));
    pixels.setPixelColor(4, pixels.Color(5, 0, 0));
    pixels.setPixelColor(5, pixels.Color(5, 0, 0));
    pixels.setPixelColor(6, pixels.Color(5, 0, 0));
    pixels.setPixelColor(7, pixels.Color(5, 0, 0));
    pixels.show();
  }

  if (Life == 6) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(5, 0, 0));
    pixels.setPixelColor(3, pixels.Color(5, 0, 0));
    pixels.setPixelColor(4, pixels.Color(5, 0, 0));
    pixels.setPixelColor(5, pixels.Color(5, 0, 0));
    pixels.setPixelColor(6, pixels.Color(5, 0, 0));
    pixels.setPixelColor(7, pixels.Color(5, 0, 0));
    pixels.show();
  }

  if (Life == 5) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(5, 0, 0));
    pixels.setPixelColor(4, pixels.Color(5, 0, 0));
    pixels.setPixelColor(5, pixels.Color(5, 0, 0));
    pixels.setPixelColor(6, pixels.Color(5, 0, 0));
    pixels.setPixelColor(7, pixels.Color(5, 0, 0));
    pixels.show();
  }

  if (Life == 4) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(5, 0, 0));
    pixels.setPixelColor(5, pixels.Color(5, 0, 0));
    pixels.setPixelColor(6, pixels.Color(5, 0, 0));
    pixels.setPixelColor(7, pixels.Color(5, 0, 0));
    pixels.show();
  }

  if (Life == 3) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(5, pixels.Color(5, 5, 0));
    pixels.setPixelColor(6, pixels.Color(5, 5, 0));
    pixels.setPixelColor(7, pixels.Color(5, 5, 0));
    pixels.show();
  }

  if (Life == 2) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0));
    pixels.setPixelColor(6, pixels.Color(5, 5, 0));
    pixels.setPixelColor(7, pixels.Color(5, 5, 0));
    pixels.show();
  }

  if (Life == 1) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0));
    pixels.setPixelColor(7, pixels.Color(0, 5, 0));
    pixels.show();
  }

  if (Life == 0) {
    pixels.setPixelColor(0, pixels.Color(0, 5, 0));
    pixels.setPixelColor(1, pixels.Color(0, 5, 0));
    pixels.setPixelColor(2, pixels.Color(0, 5, 0));
    pixels.setPixelColor(3, pixels.Color(0, 5, 0));
    pixels.setPixelColor(4, pixels.Color(0, 5, 0));
    pixels.setPixelColor(5, pixels.Color(0, 5, 0));
    pixels.setPixelColor(6, pixels.Color(0, 5, 0));
    pixels.setPixelColor(7, pixels.Color(0, 5, 0));
    pixels.show();
    delay(500);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0));
    pixels.setPixelColor(7, pixels.Color(0, 0, 0));
    pixels.show();
    delay(500);
  }


}
