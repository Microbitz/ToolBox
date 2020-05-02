#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

//IR.............................................INICIALIZATION

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Neopixel.............................................INICIALIZATION
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN        6
#define NUMPIXELS  8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Variables.............................................INICIALIZATION
int Life = 8;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  pixels.begin();
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

}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }


  //Inputs................................................OPERATING
  
  if (results.value == 0x488F3CBB){
    Life = Life -1;
    delay(500);
  }

  //NeoPixel................................................OPERATIVO

  
  if (Life == 8) {
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
