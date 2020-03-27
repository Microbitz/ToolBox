#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <EEPROM.h>

//Botones y menu...........................................INICIALIZACION
const int buttonPin0 = 6;
const int buttonPin1 = 7;
const int buttonPin2 = 8;
int button0State = 6;
int button1State = 7;
int button2State = 8;
int menu = 0;
int acc = 0;
int segundos_menu = 180;                                        //tiempo de espera para volver al menu principal
bool standby = false;
float standby_time;

//Botones y menu...........................................INICIALIZACION
float Tiempo_actual;                                            //tiempo transcurrido
float Tiempo;

//Valores...........................................INICIALIZACION
float Valor_1 = 0.0;
float Valor_1_comp;
long Valor_1_comp_long;
float Valor_2 = 0.0;
float Valor_2_comp;
long Valor_2_comp_long;
float Valor_3 = 0.0;
float Valor_3_comp;
long Valor_3_comp_long;
float Valor_4 = 0.0;
float Valor_4_comp;
long Valor_4_comp_long;

int Valor_1_mil;
int Valor_1_cen;
int Valor_1_dec;
int Valor_1_uni;
int Valor_1_ddec;
int Valor_1_duni;

int Valor_2_mil;
int Valor_2_cen;
int Valor_2_dec;
int Valor_2_uni;
int Valor_2_ddec;
int Valor_2_duni;

int Valor_3_mil;
int Valor_3_cen;
int Valor_3_dec;
int Valor_3_uni;
int Valor_3_ddec;
int Valor_3_duni;

int Valor_4_mil;
int Valor_4_cen;
int Valor_4_dec;
int Valor_4_uni;
int Valor_4_ddec;
int Valor_4_duni;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  lcd.init();
  lcd.home ();
  lcd.print("Menu");
  lcd.setBacklight(HIGH);

  Valor_1_mil = EEPROM.read(0);
  Valor_1_cen = EEPROM.read(1);
  Valor_1_dec = EEPROM.read(2);
  Valor_1_uni = EEPROM.read(3);
  Valor_1_ddec = EEPROM.read(4);
  Valor_1_duni = EEPROM.read(5);
  Valor_1 = float((Valor_1_mil * 100000) + (Valor_1_cen * 10000) + (Valor_1_dec * 1000) + (Valor_1_uni * 100) + (Valor_1_ddec * 10) + Valor_1_duni);
  Valor_1 = Valor_1 / 100.0;
  Serial.print("Cargado:");
  Serial.print(Valor_1);
  Serial.println(" en V1");

  Valor_2_mil = EEPROM.read(6);
  Valor_2_cen = EEPROM.read(7);
  Valor_2_dec = EEPROM.read(8);
  Valor_2_uni = EEPROM.read(9);
  Valor_2_ddec = EEPROM.read(10);
  Valor_2_duni = EEPROM.read(11);
  Valor_2 = float((Valor_2_mil * 100000) + (Valor_2_cen * 10000) + (Valor_2_dec * 1000) + (Valor_2_uni * 100) + (Valor_2_ddec * 10) + Valor_2_duni);
  Valor_2 = Valor_2 / 100.0;
  Serial.print("Cargado:");
  Serial.print(Valor_2);
  Serial.println(" en V2");

  Valor_3_mil = EEPROM.read(12);
  Valor_3_cen = EEPROM.read(13);
  Valor_3_dec = EEPROM.read(14);
  Valor_3_uni = EEPROM.read(15);
  Valor_3_ddec = EEPROM.read(16);
  Valor_3_duni = EEPROM.read(17);
  Valor_3 = float((Valor_3_mil * 100000) + (Valor_3_cen * 10000) + (Valor_3_dec * 1000) + (Valor_3_uni * 100) + (Valor_3_ddec * 10) + Valor_3_duni);
  Valor_3 = Valor_3 / 100.0;
  Serial.print("Cargado:");
  Serial.print(Valor_3);
  Serial.println(" en V3");

  Valor_4_mil = EEPROM.read(18);
  Valor_4_cen = EEPROM.read(19);
  Valor_4_dec = EEPROM.read(20);
  Valor_4_uni = EEPROM.read(21);
  Valor_4_ddec = EEPROM.read(22);
  Valor_4_duni = EEPROM.read(23);
  Valor_4 = float((Valor_4_mil * 100000) + (Valor_4_cen * 10000) + (Valor_4_dec * 1000) + (Valor_4_uni * 100) + (Valor_4_ddec * 10) + Valor_4_duni);
  Valor_4 = Valor_4 / 100.0;
  Serial.print("Cargado:");
  Serial.print(Valor_4);
  Serial.println(" en V4");

  Valor_1_comp = Valor_1;
  Valor_2_comp = Valor_2;
  Valor_3_comp = Valor_3;
  Valor_4_comp = Valor_4;

  // TIMER 2 for interrupt frequency 20 Hz:
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 12499;
  TCCR2B |= (1 << WGM21);
  TCCR2B |= (0 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);

}

//Interrupcion 1 Segundo..................................OPERATIVO
ISR(TIMER2_COMPA_vect) {
  Tiempo = Tiempo + 0.05;
  if (standby == true) {
    standby_time = standby_time + 0.05;
  }
  Tiempo_actual = Tiempo / 100;
  acc = int(Tiempo_actual);

  if (standby_time >= 40.0) {
    standby_time = 0.0;
    standby = false;
  }

    if (acc >= segundos_menu) {
    Tiempo = 0.0;
    menu = 0;
  }

}


void loop() {
  //Boton.....................................................OPERATIVO
  button0State = digitalRead(buttonPin0);
  button1State = digitalRead(buttonPin1);
  button2State = digitalRead(buttonPin2);
  if (standby == false) {
    if (button0State == HIGH) {
      menu = menu + 1;
      lcd.clear ();
      standby = true;
      Tiempo = 0.0;
    }

    if (button1State == HIGH) {
      if (menu == 1) {
        Valor_1_comp = Valor_1_comp + 0.1;
      }
      if (menu == 2) {
        Valor_2_comp = Valor_2_comp + 0.1;
      }
      if (menu == 3) {
        Valor_3_comp = Valor_3_comp + 0.1;
      }
      if (menu == 4) {
        Valor_4_comp = Valor_4_comp + 0.1;
      }
      standby = true;
    }
    if (button2State == HIGH) {
      if (menu == 1) {
        Valor_1_comp = Valor_1_comp - 0.1;
      }
      if (menu == 2) {
        Valor_2_comp = Valor_2_comp - 0.1;
      }
      if (menu == 3) {
        Valor_3_comp = Valor_3_comp - 0.1;
      }
      if (menu == 4) {
        Valor_4_comp = Valor_4_comp - 0.1;
      }
      standby = true;
    }
    if (menu == 5) {
      menu = 0;

      if (Valor_1_comp != Valor_1) {
        Valor_1 = Valor_1_comp;                                             //Conversion de dato, se separan ls digitos y se guardan cada uno en un registro de eeprom
        Valor_1_comp_long = long(Valor_1 * 100);          
        Valor_1_mil = (Valor_1_comp_long) / 100000;
        Valor_1_cen = ((Valor_1_comp_long) % 100000) / 10000;
        Valor_1_dec = ((Valor_1_comp_long) % 10000) / 1000;
        Valor_1_uni = ((Valor_1_comp_long) % 1000) / 100;
        Valor_1_ddec = ((Valor_1_comp_long) % 100) / 10;
        Valor_1_duni = (Valor_1_comp_long) % 10;
        EEPROM.write(0, Valor_1_mil);
        EEPROM.write(1, Valor_1_cen);
        EEPROM.write(2, Valor_1_dec);
        EEPROM.write(3, Valor_1_uni);
        EEPROM.write(4, Valor_1_ddec);
        EEPROM.write(5, Valor_1_duni);
        Serial.println("Salvado... V1");
      }
      if (Valor_2_comp != Valor_2) {
        Valor_2 = Valor_2_comp;
        Valor_2_comp_long = long(Valor_2 * 100);
        Valor_2_mil = (Valor_2_comp_long) / 100000;
        Valor_2_cen = ((Valor_2_comp_long) % 100000) / 10000;
        Valor_2_dec = ((Valor_2_comp_long) % 10000) / 1000;
        Valor_2_uni = ((Valor_2_comp_long) % 1000) / 100;
        Valor_2_ddec = ((Valor_2_comp_long) % 100) / 10;
        Valor_2_duni = (Valor_2_comp_long) % 10;
        EEPROM.write(6, Valor_2_mil);
        EEPROM.write(7, Valor_2_cen);
        EEPROM.write(8, Valor_2_dec);
        EEPROM.write(9, Valor_2_uni);
        EEPROM.write(10, Valor_2_ddec);
        EEPROM.write(11, Valor_2_duni);
        Serial.println("Salvado... V2");
      }
      if (Valor_3_comp != Valor_3) {
        Valor_3 = Valor_3_comp;
        Valor_3_comp_long = long(Valor_3 * 100);
        Valor_3_mil = (Valor_3_comp_long) / 100000;
        Valor_3_cen = ((Valor_3_comp_long) % 100000) / 10000;
        Valor_3_dec = ((Valor_3_comp_long) % 10000) / 1000;
        Valor_3_uni = ((Valor_3_comp_long) % 1000) / 100;
        Valor_3_ddec = ((Valor_3_comp_long) % 100) / 10;
        Valor_3_duni = (Valor_3_comp_long) % 10;
        EEPROM.write(12, Valor_3_mil);
        EEPROM.write(13, Valor_3_cen);
        EEPROM.write(14, Valor_3_dec);
        EEPROM.write(15, Valor_3_uni);
        EEPROM.write(16, Valor_3_ddec);
        EEPROM.write(17, Valor_3_duni);
        Serial.println("Salvado... V3");
      }
      if (Valor_4_comp != Valor_4) {
        Valor_4 = Valor_4_comp;
        Valor_4_comp_long = long(Valor_4 * 100);
        Valor_4_mil = (Valor_4_comp_long) / 100000;
        Valor_4_cen = ((Valor_4_comp_long) % 100000) / 10000;
        Valor_4_dec = ((Valor_4_comp_long) % 10000) / 1000;
        Valor_4_uni = ((Valor_4_comp_long) % 1000) / 100;
        Valor_4_ddec = ((Valor_4_comp_long) % 100) / 10;
        Valor_4_duni = (Valor_4_comp_long) % 10;
        EEPROM.write(18, Valor_4_mil);
        EEPROM.write(19, Valor_4_cen);
        EEPROM.write(20, Valor_4_dec);
        EEPROM.write(21, Valor_4_uni);
        EEPROM.write(22, Valor_4_ddec);
        EEPROM.write(23, Valor_4_duni);
        Serial.println("Salvado... V4");
      }
    }
  }


  //LCD.....................................................OPERATIVO
  //Menu_0
  if (menu == 0) {
    lcd.home ();
    lcd.print("Stand_BY");
    lcd.setCursor ( 0, 1 );
    lcd.print(Tiempo_actual, 2);
    lcd.setCursor ( 13, 1 );
    lcd.print(acc);
    lcd.print("  ");
  }
  //Menu_1
  if (menu == 1) {
    lcd.home ();
    lcd.print("V1:");
    lcd.print(Valor_1_comp, 2);
    lcd.setCursor ( 0, 1 );
    lcd.print(Valor_1, 2);
  }
  //Menu_2
  if (menu == 2) {
    lcd.home ();
    lcd.print("V2:");
    lcd.print(Valor_2_comp, 2);
    lcd.setCursor ( 0, 1 );
    lcd.print(Valor_2, 2);
  }
  //Menu_3
  if (menu == 3) {
    lcd.home ();
    lcd.print("V3:");
    lcd.print(Valor_3_comp, 2);
    lcd.setCursor ( 0, 1 );
    lcd.print(Valor_3, 2);
  }
  //Menu_4
  if (menu == 4) {
    lcd.home ();
    lcd.print("V4:");
    lcd.print(Valor_4_comp, 2);
    lcd.setCursor ( 0, 1 );
    lcd.print(Valor_4, 2);
  }
  if (menu == 5) {
    lcd.home ();
    lcd.clear ();
    lcd.print("Guardando ");
    lcd.print(menu);
  }
  delay(100);
  //PROGRAMA PRINCIPAL.....................................................OPERATIVO

}
