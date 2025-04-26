#include "coche.h"
#include "luces.h"
#include "display.h"
#include "switchs.h"
#include "sensoresIR.h"

int minutos = 0, msegundos = 0;

Coche c1, c2;

long tiempoInicial;

byte modo = 2;

bool fin1 = false, fin2 = false;

byte numero_botones;

void setup() {
  setupLuces();
  setupDisplay();
  setupSwitchs();
  //Serial.begin(9600);
  numero_botones = arrayBotones();
  //Serial.println(numero_botones);
  //semaforo();
  //tiempoInicial = millis()/10;
}

void loop() {
  while (modo == 0){
    tiempos();
    display7segmentos(c1.vueltas,minutos,msegundos,c2.vueltas,minutos,msegundos);
    if (numero_botones >= 128){ // modo cuenta vueltas
      if (flancoIR(A0) == 1 && numero_botones - 128 > c1.vueltas){
        c1.vueltas = c1.vueltas + 1;
        zumbador (250, 50);
        if (c1.minRapida > (minutos - c1.minVuelta) || (c1.minRapida == (minutos - c1.minVuelta) && c1.msegundosRapida > (msegundos - c1.msegundosVuelta))){
          c1.minRapida = minutos - c1.minVuelta;
          c1.msegundosRapida = msegundos - c1.msegundosVuelta;
          c1.vRapida = c1.vueltas;
        }
        c1.minVuelta = minutos;
        c1.msegundosVuelta = msegundos;
      }
      if (flancoIR(A1) == 1 && numero_botones - 128 > c2.vueltas){
        c2.vueltas = c2.vueltas + 1;
        zumbador (500, 50);
        if (c2.minRapida > (minutos - c2.minVuelta) || (c2.minRapida == (minutos - c2.minVuelta) && c2.msegundosRapida > (msegundos - c2.msegundosVuelta))){
          c2.minRapida = minutos - c2.minVuelta;
          c2.msegundosRapida = msegundos - c2.msegundosVuelta;
          c2.vRapida = c2.vueltas;
        }
        c2.minVuelta = minutos;
        c2.msegundosVuelta = msegundos;
      }
      if (numero_botones - 128 <= c1.vueltas && fin1 == false){
        c1.minTotal = minutos;
        c1.msegundosTotal = msegundos;
        fin1 = true;
      }
      if (numero_botones - 128 <= c2.vueltas && fin2 == false){
        c2.minTotal = minutos;
        c2.msegundosTotal = msegundos;
        fin2 = true;
      }
      if (numero_botones - 128 ==  c1.vueltas && numero_botones - 128 == c2.vueltas){
        zumbador (500, 500);
        modo = 1;
      }
    }
    else { // modo cuenta tiempo
      if (flancoIR(A0) == 1 && numero_botones > minutos){
        c1.vueltas = c1.vueltas + 1;
        zumbador (250, 50);
        if (c1.minRapida > (minutos -  c1.minVuelta) || (c1.minRapida == (minutos - c1.minVuelta) && c1.msegundosRapida > (msegundos - c1.msegundosVuelta))){
          c1.minRapida = minutos - c1.minVuelta;
          c1.msegundosRapida = msegundos - c1.msegundosVuelta;
          c1.vRapida = c1.vueltas;
        }
        c1.minVuelta = minutos;
        c1.msegundosVuelta = msegundos;
      }
      if (flancoIR(A1) == 1 && numero_botones > minutos){
        c2.vueltas = c2.vueltas + 1;
        zumbador (500, 50);
        if (c2.minRapida > (minutos - c2.minVuelta) || (c2.minRapida == (minutos - c2.minVuelta) && c2.msegundosRapida > (msegundos - c2.msegundosVuelta))){
          c2.minRapida = minutos - c2.minVuelta;
          c2.msegundosRapida = msegundos - c2.msegundosVuelta;
          c2.vRapida = c2.vueltas;
        }
        c2.minVuelta = minutos;
        c2.msegundosVuelta = msegundos;
      }
      if (numero_botones ==  minutos){
        zumbador (500, 500);
        modo = 1;
      }
    }
    if (flancoBoton() == 1){
      modo = 2;
    }
  }
  while (modo == 1){
    if (numero_botones >= 128 ){ // modo cuenta vueltas
      display7segmentos(c1.vueltas, c1.minTotal, c1.msegundosTotal, c2.vueltas, c2.minTotal, c2.msegundosTotal);
    }
    else {
      display7segmentos(c1.vueltas, minutos, msegundos, c2.vueltas, minutos, msegundos);
    }
    if (flancoBoton() == 1){
      modo = 2;
    }
  }
  while (modo == 2){
    display7segmentos(c1.vRapida, c1.minRapida, c1.msegundosRapida, c2.vRapida, c2.minRapida, c2.msegundosRapida);
    if (flancoBoton() == 1){
      modo = 0;
      minutos = 0, msegundos = 0, c1.vueltas = 0, c2.vueltas = 0;
      c1.minVuelta = 0, c1.msegundosVuelta = 0, c2.minVuelta = 0, c2.msegundosVuelta = 0;
      c1.minRapida = 60, c1.msegundosRapida = 59, c2.minRapida = 60, c2.msegundosRapida = 59, c1.vRapida = 0, c2.vRapida = 0;
      fin1 = false, fin2 = false;
      numero_botones = arrayBotones();
      if (numero_botones >= 128){
        display7segmentos(numero_botones - 128, 0, 0, numero_botones - 128, 0, 0);
      }
      else{
        display7segmentos(0, numero_botones, 0, 0, numero_botones, 0);
      }
      delay(500);
      semaforo();
      tiempoInicial = millis()/10;
    }
  }

  //Serial.println(tiempo1);
  delay(50);

}

void tiempos(){
  long crono = millis()/10 - tiempoInicial;
  msegundos = crono - minutos * 6000;

  if (msegundos >= 6000){
    minutos = minutos + 1;
    msegundos = crono - minutos * 6000;
  }
}
