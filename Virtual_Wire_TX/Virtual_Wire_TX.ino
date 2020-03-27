#include <VirtualWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Botones y menu...........................................INICIALIZACION
const int buttonPin0 = 6;
const int buttonPin1 = 7;
const int buttonPin2 = 8;
const int LATCHPin = 2;
int button0State;
int button1State;
int button2State;
int LATCHState;
bool LED1 = false;
bool LED2 = false;
bool LED3 = false;
bool LED4 = false;

//Estados...........................................INICIALIZACION


void setup()
{
  //Iniciamos el Serial y la comunicacion por radio
  Serial.begin(9600);
  Serial.print("Sistema encendido\n");
  pinMode(buttonPin0, INPUT); //Configuramos el pin 6
  pinMode(buttonPin1, INPUT); //Configuramos el pin 7
  pinMode(buttonPin2, INPUT); //Configuramos el pin 8
  pinMode(LATCHPin, INPUT); //Configuramos el pin 8

  vw_set_tx_pin(12);
  vw_setup(2000);

  lcd.init();
  lcd.home ();
  lcd.print("TX");
  lcd.setBacklight(HIGH);

}
void loop()
{
  //Boton.....................................................OPERATIVO
  button0State = digitalRead(buttonPin0);
  button1State = digitalRead(buttonPin1);
  button2State = digitalRead(buttonPin2);
  LATCHState = digitalRead(LATCHPin);

  if (button0State == HIGH) {
    if (LED1 == false) {
      if (LATCHState == HIGH)send("LON_1");
      if (LATCHState == LOW)send("ON_1");
      lcd.setCursor(0, 1);
      lcd.print("TX 1 ON  ");
      Serial.println("TX 1 ON ");
      delay(2000);
    }
    if (LED1 == true) {
      send("OFF_1");
      lcd.setCursor(0, 1);
      lcd.print("TX 1 OFF");
      Serial.println("TX 1 OFF");
      delay(2000);
    }
    LED1 = !LED1;
    if (LATCHState == LOW)LED1 = false;
  }
  if (button1State == HIGH) {
    if (LED2 == false) {
      if (LATCHState == HIGH)send("LON_2");
      if (LATCHState == LOW)send("ON_2");
      lcd.setCursor(0, 1);
      lcd.print("TX 2 ON  ");
      Serial.println("TX 2 ON ");
      delay(2000);
    }
    if (LED2 == true) {
      send("OFF_2");
      lcd.setCursor(0, 1);
      lcd.print("TX 2 OFF");
      Serial.println("TX 2 OFF");
      delay(2000);
    }
    LED2 = !LED2;
    if (LATCHState == LOW)LED2 = false;
  }
  if (button2State == HIGH) {
    if (LED3 == false) {
      if (LATCHState == HIGH)send("LON_3");
      if (LATCHState == LOW)send("ON_3");
      lcd.setCursor(0, 1);
      lcd.print("TX 3 ON  ");
      Serial.println("TX 3 ON ");
      delay(2000);
    }
    if (LED3 == true) {
      send("OFF_3");
      lcd.setCursor(0, 1);
      lcd.print("TX 3 OFF");
      Serial.println("TX 3 OFF");
      delay(2000);
    }
    LED3 = !LED3;
    if (LATCHState == LOW)LED3 = false;
  }

}

//Funcion para enviar el mensaje
void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message)); //Envia el mensaje
  vw_wait_tx(); //Espera hasta que se haya acabado de transmitir todo

  Serial.println(message); //Muestra el mensaje por Serial
}
