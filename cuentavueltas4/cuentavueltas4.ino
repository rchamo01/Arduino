
//#include <LiquidCrystal.h>
#include "remote.h"
#include "Zumbador.h"
#include "Carrera.h"


///////////////////////////////////////////
//Pantalla LCD
LiquidCrystal lcd (7,6,5,4,3,2); //pin PCB
int V0 = 8; //pin PCB
int brill = 100;

///////////////////////////////////////////

enum Mode {inicio, brillo, tiempo_semaforos, nJugadores, cronometro, distancia, espana, carrera, clasificacion};
Mode mode = inicio;

int jugadores = 3;

void setup() {
  Serial.begin(9600);
  ///////////////////////////////////////////
  //PANTALLA LCD
  lcd.begin(16,2);
  pinMode(V0, OUTPUT); //V0 pantalla LCD

  ///////////////////////////////////////////
  // MANDO
  irrecv.enableIRIn(); // Empezamos la recepción  por IR

  ///////////////////////////////////////////
  //SEMAFORO
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
  //////////////////////////////////////////
  //ZUMBADOR
  pinMode(ZUM, OUTPUT);

  //////////////////////////////////////////
  //Distancia
  distanciaInicial1 = ADC0_promedio(A1, 20);
  distanciaInicial2 = ADC0_promedio(A2, 20);
}

void loop() {
  switch  (mode) {
    case inicio:
      INICIO();
    break;
    case brillo:
      BRILLO();
    break;
    case tiempo_semaforos:
      TIEMPO_SEMAFOROS();
    break;
    case nJugadores:
      NJUGADORES();
    break;
    case cronometro:
      CRONOMETRO();
    break;
    case distancia:
      DISTANCIA();
    break;
    case espana:
      ESPANA();
    break;
    case carrera:
      CARRERA(jugadores, lcd);
      mode = clasificacion;
    break;
    case clasificacion:
      CLASIFICACION(lcd);
      char aux = mando();
      if (aux == 'E'){
        mode = inicio;
      }
    break;
  }
  //Serial.println(mode);
}

void INICIO (){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CARRERA -> ^");
  lcd.setCursor(0,1);
  lcd.print("AJUSTES -> v");
  char aux = mando();
  Serial.println(aux);
  if (aux == 'B'){
    mode = carrera;
  }
  else if (aux == 'H'){
    mode = brillo;
  }
  delay(200);
}

void BRILLO(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("POT BRILLO -> OK");
  lcd.setCursor(0,1);
  lcd.print(brill);
  brill = map(potenciometro(), 0, 1023, 0, 255);
  analogWrite(V0, brill);
  char aux = mando();
  Serial.println(aux);
  if (aux == 'E'){
    mode = tiempo_semaforos;
  }
  delay(200);
}

void TIEMPO_SEMAFOROS(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SEM TIEMPO -> OK");
  lcd.setCursor(0,1);
  lcd.print(tiempo);
  lcd.print("ms");
  tiempo = map(potenciometro(), 0, 1023, 0, 2000);
  char aux = mando();
  //Serial.println(aux);
  if (aux == 'E'){
    mode = nJugadores;
  }
  delay(200);
}

void NJUGADORES (){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("N JUGAD -> OK");
  lcd.setCursor(0,1);
  lcd.print(jugadores);
  char aux = mando();
  //Serial.println(aux);
  if (aux == '0' || aux == '1' || aux == '2' || aux == '3' || aux == '4' || aux == '5' || aux == '6' || aux == '7' || aux == '8' || aux == '9'){
    jugadores = String(aux).toInt(); 
  }
  else if (aux == 'E'){
    mode = cronometro;
  }
  //Serial.println(jugadores);
  delay(200);
}

void CRONOMETRO (){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CRONO -> OK");
  lcd.setCursor(0,1);
  lcd.print(crono);
  lcd.print("s");
  crono = map(potenciometro(), 0, 1023, 60, 600);
  char aux = mando();
  if (aux == 'E'){
    mode = distancia;
  }
  delay(200);
}

void DISTANCIA () {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DMedida: ");
  lcd.print(dist_promedio(A1, 20));
  lcd.setCursor(0,1);
  lcd.print("DLimite: ");
  lcd.print(dist);
  dist = map(potenciometro(), 0, 1023, 60, 600);
  char aux = mando();
  if (aux == 'E'){
    mode = espana;
  }
  delay(200);
}

void ESPANA(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ESPANA? -> ^");
  lcd.setCursor(0,1);
  lcd.print("NO ESPANA -> v");
  char aux = mando();
  if (aux == 'B'){
    himnoESPANA(ZUM);
    mode = inicio;
  }
  else if (aux == 'H'){
    mode = inicio;
  }
  delay(200);
}

int potenciometro(){
  return analogRead(A0);
}
