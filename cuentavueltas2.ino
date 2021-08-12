#include <LiquidCrystal.h>
LiquidCrystal lcd (3,2,4,5,6,7);

int VUELTAS1 = 0;
int TIEMPO1 = 0;
int tiempoTotal1;
int BOTON1 = 0;

int VUELTAS2 = 0;
int TIEMPO2 = 0;
int tiempoTotal2;
int BOTON2 = 0;

void setup() {
  pinMode (8,INPUT);
  pinMode (9,INPUT);
  
  lcd.begin(16,2);
  
  Serial.begin(9600);

}

void loop() {
  BOTON1 = digitalRead (8);
  BOTON2 = digitalRead (9);
  
  tiempoTotal1 = millis()/1000;
  tiempoTotal2 = millis()/1000;
  
  if (BOTON1 == 1){
    VUELTAS1 = VUELTAS1 +1;
    TIEMPO1 = tiempoTotal1 -  TIEMPO1;
    }

  if (BOTON2 == 1){
    VUELTAS2 = VUELTAS2 +1;
    TIEMPO2 = tiempoTotal2- TIEMPO2;
    }
  
  funcion(VUELTAS1, VUELTAS2, TIEMPO1, TIEMPO2, tiempoTotal1, tiempoTotal2);

  Serial.print ("Boton=");
  Serial.print(BOTON1);
  Serial.print(", Vueltas=");
  Serial.print(VUELTAS1);
  Serial.print(", TIEMPO=");
  Serial.print(TIEMPO1);
  Serial.print(", tiempoTotal=");
  Serial.println(tiempoTotal1);

  delay(300);

}

void funcion (int vueltas1, int vueltas2, int tiempo1, int tiempo2, int tiempoTotal1, int tiempoTotal2){
  lcd.setCursor(0,0);
  lcd.print(vueltas1);
  lcd.print("/");
  lcd.print(tiempo1);
  lcd.print("/");
  lcd.print(tiempoTotal1);
  lcd.setCursor(0,1);
  lcd.print(vueltas2);
  lcd.print("/");
  lcd.print(tiempo2);
  lcd.print("/");
  lcd.print(tiempoTotal2);
  
  
}
