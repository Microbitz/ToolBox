#include <VirtualWire.h>

//Creamos un mensaje
//La constante VW_MAX_MESSAGE_LEN viene definida en la libreria
byte message[VW_MAX_MESSAGE_LEN];
byte messageLength = VW_MAX_MESSAGE_LEN;

void setup()
{
  pinMode(2, OUTPUT); //Configuramos el pin 6
  pinMode(3, OUTPUT); //Configuramos el pin 7
  pinMode(4, OUTPUT); //Configuramos el pin 8
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

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
      digitalWrite(2, HIGH);
      Serial.write("LED 1 Encendido\n");
      delay(1000);
      Serial.println("ON_1");
    }
    if (comparar("OFF_1") == 0) {
      digitalWrite(2, LOW);
      Serial.write("LED 1 Apagado\n");
      Serial.println("OFF_1");
    }
    if (comparar("ON_2") == 0) {
      digitalWrite(3, HIGH);
      Serial.write("LED 2 Encendido\n");
      delay(1000);
      Serial.println("ON_2");
    }
    if (comparar("OFF_2") == 0) {
      digitalWrite(3, LOW);
      Serial.write("LED 2 Apagado\n");
      Serial.println("OFF_2");
    }
    if (comparar("ON_3") == 0) {
      digitalWrite(4, HIGH);
      Serial.write("LED 3 Encendido\n");
      delay(1000);
      Serial.println("ON_3");
    }
    if (comparar("OFF_3") == 0) {
      digitalWrite(4, LOW);
      Serial.write("LED 3 Apagado\n");
      Serial.println("OFF_3");
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
