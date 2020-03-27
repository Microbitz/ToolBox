#include <VirtualWire.h>

//Creamos un mensaje
//La constante VW_MAX_MESSAGE_LEN viene definida en la libreria
byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;

void setup()
{
  pinMode(6, OUTPUT); //Configuramos el pin 6
  pinMode(7, OUTPUT); //Configuramos el pin 7
  pinMode(8, OUTPUT); //Configuramos el pin 8
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);

  Serial.begin(9600);//Iniciamos el Serial
  Serial.println("Iniciando...");

  //Iniciar el receptor
  vw_set_rx_pin(11);
  vw_setup(2000);
  vw_rx_start();
}
void loop()
{
  if (vw_get_message(message, &messageLength))
  {
    if (comparar("ON_1") == 0) {
      digitalWrite(6, HIGH);
      Serial.write("LED 1 Encendido\n");
      delay(1000);
      digitalWrite(6, LOW);
    }
    if (comparar("OFF_1") == 0) {
      digitalWrite(6, LOW);
      Serial.write("LED 1 Apagado\n");
    }

    if (comparar("ON_2") == 0) {
      digitalWrite(7, HIGH);
      Serial.write("LED 2 Encendido\n");
      delay(1000);
      digitalWrite(7, LOW);
    }
    if (comparar("OFF_2") == 0) {
      digitalWrite(7, LOW);
      Serial.write("LED 2 Apagado\n");
    }

    if (comparar("ON_3") == 0) {
      digitalWrite(8, HIGH);
      Serial.write("LED 3 Encendido\n");
      delay(1000);
      digitalWrite(8, LOW);
    }
    if (comparar("OFF_3") == 0) {
      digitalWrite(8, LOW);
      Serial.write("LED 3 Apagado\n");
    }

    if (comparar("LON_1") == 0) {
      digitalWrite(6, HIGH);
      Serial.write("LED 1 Encendido\n");
    }
    if (comparar("LON_2") == 0) {
      digitalWrite(7, HIGH);
      Serial.write("LED 1 Encendido\n");
    }
    if (comparar("LON_3") == 0) {
      digitalWrite(8, HIGH);
      Serial.write("LED 1 Encendido\n");
    }

  }
}

char comparar(char* cadena) {
  //Esta funcion compara el string cadena con el mensaje recibido.
  //Si son iguales, devuelve 1. Si no, devuelve 0.

  for (int i = 0; i < messageLength; i++)
  {
    if (message[i] != cadena[i])
    {
      return 1;
    }
  }

  return 0;

}
