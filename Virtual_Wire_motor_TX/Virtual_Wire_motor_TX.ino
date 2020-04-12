#include <VirtualWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Botones y menu...........................................INICIALIZACION
const int buttonPin0 = A0;
const int buttonPin1 = A1;
const int buttonPin2 = A2;
int button0State;
int button1State;
int button2State;
bool SET1 = false;
bool SET2 = false;
bool SET3 = false;


//Estados...........................................INICIALIZACION


void setup()
{
  //Iniciamos el Serial y la comunicacion por radio
  Serial.begin(9600);
  Serial.print("Sistema encendido\n");
  pinMode(buttonPin0, INPUT); //Configuramos el pin A0
  pinMode(buttonPin1, INPUT); //Configuramos el pin A1
  pinMode(buttonPin2, INPUT); //Configuramos el pin A2

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


  //********************************Boton 0*************************

  if (button0State == HIGH && SET1 == false) {
    send("ON_1");
    lcd.setCursor(0, 1);
    lcd.print("TX 1 ON  ");
    Serial.println("TX 1 ON ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("         ");
    SET1 = true;
  }
  if (button0State == LOW && SET1 == true) {
    send("OFF_1");
    lcd.setCursor(0, 1);
    lcd.print("TX 1 OFF  ");
    Serial.println("TX 1 OFF ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("         ");
    SET1 = false;
  }

  //********************************Boton 1*************************

  if (button1State == HIGH && SET2 == false) {
    send("ON_2");
    lcd.setCursor(0, 1);
    lcd.print("TX 2 ON  ");
    Serial.println("TX 2 ON ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("         ");
    SET2 = true;
  }
  if (button1State == LOW && SET2 == true) {
    send("OFF_2");
    lcd.setCursor(0, 1);
    lcd.print("TX 2 OFF  ");
    Serial.println("TX 2 OFF ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("         ");
    SET2 = false;
  }

  //********************************Boton 2*************************

  if (button2State == HIGH && SET3 == false) {
    send("ON_3");
    lcd.setCursor(0, 1);
    lcd.print("TX 3 ON  ");
    Serial.println("TX 3 ON ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("         ");
    SET3 = true;
  }
  if (button2State == LOW && SET3 == true) {
    send("OFF_3");
    lcd.setCursor(0, 1);
    lcd.print("TX 3 OFF  ");
    Serial.println("TX 3 OFF ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("         ");
    SET3 = false;
  }


}

//Funcion para enviar el mensaje
void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message)); //Envia el mensaje
  vw_wait_tx(); //Espera hasta que se haya acabado de transmitir todo

  Serial.println(message); //Muestra el mensaje por Serial
}
