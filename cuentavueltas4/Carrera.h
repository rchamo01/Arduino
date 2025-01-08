#pragma once

#include <LiquidCrystal.h>
#include "Zumbador.h"
#include "remote.h"

//////////////////////////////////////////////
//LEDS
int LED1 = 11;
int LED2 = 12;
int LED3 = 13;
int tiempo = 500;

////////////////////////////////////////////////
int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0;
int vueltas1 = 0, vueltas2 = 0;

///////////////////////////////////////////////
//Distancia
volatile bool distanciaInicial1;
volatile bool distanciaInicial2;
int dist = 400;

///////////////////////////////////////////////
//
int crono = 100; //esta en segundos



//int factorial (int num){
//  int n = num;
//  for (int i = 1; i< n; i++){
//    num = num * i;
//  }
//  return num;
//}

//int combinacion (int jug){
//  return factorial(jug)/(factorial(jug-2));
//}

void semaforo (){
  digitalWrite(LED1, HIGH);
  delay(tiempo);
  digitalWrite(LED2, HIGH);
  delay(tiempo);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void ledOn(){
  digitalWrite(LED3, HIGH);
}

void ledOff(){
  digitalWrite(LED3, LOW);
}

int dist_promedio(int IR, int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(IR);
  }
  return suma/n;
}

bool ADC0_promedio(int IR, int n)
{
  if(dist_promedio (IR, 20) < dist){
    return 0;
  }
  else{
    return 1;
  }
}

bool flancoIR (int IR){
  bool aux = 0;
  
  if (IR == A1){
    bool distanciaFinal1 = ADC0_promedio(IR, 20);
    
    if ((distanciaInicial1 == 0 && distanciaFinal1 == 1)){
      aux = 1;
    }
    else {
      aux = 0;
    } 
    distanciaInicial1 = distanciaFinal1;
  }
  if (IR == A2){
    bool distanciaFinal2 = ADC0_promedio(IR, 20);
    
    if ((distanciaInicial2 == 0 && distanciaFinal2 == 1)){
      aux = 1;
    }
    else {
      aux = 0;
    }
    distanciaInicial2 = distanciaFinal2; 
  }

  return aux;
}

void CARRERA(int jug, LiquidCrystal lcd){
  String corredores[] = {"AB", "BA", "CD", "DC", "EF", "FE", "AG", "GA", "BC", "CB", "DE", "ED", "FG", "GF", "AC", "CA", "BD", "DB", "EG", "GE", 
  "AF", "FA", "BE", "EB", "CG", "GC", "AD", "DA", "CE", "EC", "BG", "GB", "DF", "FD", "AE", "EA", "BF", "FB", "DG", "GD", "CF", "FC"};

  bool sema = false;
  int tiempo_crono;
  int tiempo_inicial;

  bool carrera_aux = false;

//  int pilotos[jug];
//  for (int i = 0; i<jug; i++){
//     pilotos[i] = new piloto;
//  }

  static int i = 0;
  while (i<42){
    if (jug == 2 && (corredores[i][0] == 'C' || corredores[i][1] == 'C' || corredores[i][0] == 'D' || corredores[i][1] == 'D' || corredores[i][0] == 'E' || corredores[i][1] == 'E' || 
    corredores[i][0] == 'F' || corredores[i][1] == 'F' || corredores[i][0] == 'G' || corredores[i][1] == 'G')) {i++; continue;}
    else if (jug == 3 && (corredores[i][0] == 'D' || corredores[i][1] == 'D' || corredores[i][0] == 'E' || corredores[i][1] == 'E' || corredores[i][0] == 'F' || corredores[i][1] == 'F' ||
    corredores[i][0] == 'G' || corredores[i][1] == 'G')) {i++; continue;}
    else if (jug == 4 && (corredores[i][0] == 'E' || corredores[i][1] == 'E' || corredores[i][0] == 'F' || corredores[i][1] == 'F' || corredores[i][0] == 'G' || corredores[i][1] == 'G')) {i++; continue;}
    else if (jug == 5 && (corredores[i][0] == 'F' || corredores[i][1] == 'F' || corredores[i][0] == 'G' || corredores[i][1] == 'G')) {i++; continue;}
    else if (jug == 5 && (corredores[i][0] == 'G' || corredores[i][1] == 'G')) {i++; continue;}
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("J");
    lcd.print(corredores[i][0]);
    lcd.print(": ");
    lcd.print(vueltas1);
    lcd.setCursor(0,1);
    lcd.print("J");
    lcd.print(corredores[i][1]);
    lcd.print(": ");
    lcd.print(vueltas2);
    lcd.setCursor(13,1);
    lcd.print(tiempo_crono);
    switch (corredores[i][0]){
        case 'A':
          lcd.setCursor(7,0);
          lcd.print(A);
        break;
        case 'B':
          //pilotos[1].mostrarPantalla(0, lcd);
          lcd.setCursor(7,0);
          lcd.print(B);
        break;
        case 'C':
          //pilotos[2].mostrarPantalla(0, lcd);
          lcd.setCursor(7,0);
          lcd.print(C);
        break;
        case 'D':
          //pilotos[3].mostrarPantalla(0, lcd);
          lcd.setCursor(7,0);
          lcd.print(D);
        break;
        case 'E':
          //pilotos[4].mostrarPantalla(0, lcd);
          lcd.setCursor(7,0);
          lcd.print(E);
        break;
        case 'F':
          //pilotos[5].mostrarPantalla(0, lcd);
          lcd.setCursor(7,0);
          lcd.print(F);
        break;
        case 'G':
          //pilotos[6].mostrarPantalla(0, lcd);
          lcd.setCursor(7,0);
          lcd.print(G);
        break;
    }
    switch (corredores[i][1]){
        case 'A':
          //pilotos[0].mostrarPantalla(1, lcd);
          lcd.setCursor(7,1);
          lcd.print(A);
        break;
        case 'B':
          //pilotos[1].mostrarPantalla(1, lcd);
          lcd.setCursor(7,1);
          lcd.print(B);
        break;
        case 'C':
          //pilotos[2].mostrarPantalla(1, lcd);
          lcd.setCursor(7,1);
          lcd.print(C);
        break;
        case 'D':
          //pilotos[3].mostrarPantalla(1, lcd);
          lcd.setCursor(7,1);
          lcd.print(D);
        break;
        case 'E':
          //pilotos[4].mostrarPantalla(1, lcd);
          lcd.setCursor(7,1);
          lcd.print(E);
        break;
        case 'F':
          //pilotos[5].mostrarPantalla(1, lcd);
          lcd.setCursor(7,1);
          lcd.print(F);
        break;
        case 'G':
          //pilotos[6].mostrarPantalla(1, lcd);
          lcd.setCursor(7,1);
          lcd.print(G);
        break;
    }
    delay(10);

    if (sema == false){
      ledOff();
      semaforo();
      tiempo_inicial = millis()/1000;
      vueltas1 = 0;
      vueltas2 = 0;
      carrera_aux = true;
      sema = true; 
    }
    
    tiempo_crono = crono - millis()/1000 + tiempo_inicial;
    if (tiempo_crono == 0) {
      ledOn();
      carrera_aux = false;
      //zumbador(450, 400, 1000);
    }

    if (flancoIR(A1) && carrera_aux == true){
      vueltas1++;
      switch (corredores[i][0]){
        case 'A':
          A++;
        break;
        case 'B':
          B++;
        break;
        case 'C':
          C++;
        break;
        case 'D':
          D++;
        break;
        case 'E':
          E++;
        break;
        case 'F':
          F++;
        break;
        case 'G':
          G++;
        break;   
      }
    }
    if(flancoIR(A2) && carrera_aux == true){
      vueltas2++;
      switch (corredores[i][1]){
        case 'A':
          A++;
        break;
        case 'B':
          B++;
        break;
        case 'C':
          C++;
        break;
        case 'D':
          D++;
        break;
        case 'E':
          E++;
        break;
        case 'F':
          F++;
        break;
        case 'G':
          G++;
        break;
      }
    }

    char aux = mando();
    Serial.println(aux);
    if (aux == 'E'){
      sema = false;
      i++;
    }
    else if(aux == 'X'){
      break;
    }
    
  }
  
}

void CLASIFICACION (LiquidCrystal lcd){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A:");
  lcd.print(A);
  lcd.print("B:");
  lcd.print(B);
  lcd.print("C:");
  lcd.print(C);
  lcd.print("D:");
  lcd.print(D);
  lcd.setCursor(0,1);
  lcd.print("E:");
  lcd.print(E);
  lcd.print("F:");
  lcd.print(F);
  lcd.print("G:");
  lcd.print(G);
  delay(50);
  
}
