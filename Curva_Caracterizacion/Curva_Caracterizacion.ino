int Valor_Sensor_raw;
int Valor_Sensor_scl;
float Ain_0;
float Curve_out;

//Valores de curva......
float y0 = 0.0;
float y1 = 10.0;
float y2 = 20.0;
float y3 = 30.0;
float y4 = 40.0;
float y5 = 50.0;
float y6 = 60.0;
float y7 = 70.0;
float y8 = 80.0;
float y9 = 90.0;
float y10 = 100.0;

float x0 = 1.0;
float x1 = 2.0;
float x2 = 3.0;
float x3 = 4.0;
float x4 = 5.0;
float x5 = 6.0;
float x6 = 7.0;
float x7 = 8.0;
float x8 = 9.0;
float x9 = 10.0;
float x10 = 11.0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  Valor_Sensor_raw = analogRead(A0);
  Valor_Sensor_scl = map(Valor_Sensor_raw, 0, 1023, 0, 1000);
  Ain_0 = float(Valor_Sensor_scl);
  Ain_0 = Ain_0 / 10.0;
  //((Y[n+1]-Yn)/ (X[n+1]-Xn))*(In-Xn)+Yn
if (Ain_0 == y0 ){Curve_out = x0;} 
if (Ain_0 > y0 && Ain_0 < y1){Curve_out = ((Ain_0 - y0) * ((x1 - x0) / (y1 - y0))) + x0;}
if (Ain_0 > y1 && Ain_0 < y2){Curve_out = ((Ain_0 - y1) * ((x2 - x1) / (y2 - y1))) + x1;}
if (Ain_0 > y2 && Ain_0 < y3){Curve_out = ((Ain_0 - y2) * ((x3 - x2) / (y3 - y2))) + x2;}
if (Ain_0 > y3 && Ain_0 < y4){Curve_out = ((Ain_0 - y3) * ((x4 - x3) / (y4 - y3))) + x3;}
if (Ain_0 > y4 && Ain_0 < y5){Curve_out = ((Ain_0 - y4) * ((x5 - x4) / (y5 - y4))) + x4;}
if (Ain_0 > y5 && Ain_0 < y6){Curve_out = ((Ain_0 - y5) * ((x6 - x5) / (y6 - y5))) + x5;}
if (Ain_0 > y6 && Ain_0 < y7){Curve_out = ((Ain_0 - y6) * ((x7 - x6) / (y7 - y6))) + x6;}
if (Ain_0 > y7 && Ain_0 < y8){Curve_out = ((Ain_0 - y7) * ((x8 - x7) / (y8 - y7))) + x7;}
if (Ain_0 > y8 && Ain_0 < y9){Curve_out = ((Ain_0 - y8) * ((x9 - x8) / (y9 - y8))) + x8;}
if (Ain_0 > y9 && Ain_0 < y10){Curve_out = ((Ain_0 - y9) * ((x10 - x9) / (y10 - y9))) + x9;}
if (Ain_0 > y10 ){Curve_out = x10;} 


  Serial.print(Ain_0, 2);
  Serial.print(",");
  Serial.println(Curve_out, 2);
  delay(10);
}
