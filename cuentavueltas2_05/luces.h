#pragma once

int luz0 = 1;
int luz1 = 0;
int luz2 = 2;
int luz3 = 3;
int luz4 = 4;
  
int zum = 5;
int boton = 6;

bool estadoAnterior;

void setupLuces(){
  pinMode(luz0, OUTPUT);
  pinMode(luz1, OUTPUT);
  pinMode(luz2, OUTPUT);
  pinMode(luz3, OUTPUT);
  pinMode(luz4, OUTPUT);
  digitalWrite(luz0, LOW);
  digitalWrite(luz1, LOW);
  digitalWrite(luz2, LOW);
  digitalWrite(luz3, LOW);
  digitalWrite(luz4, LOW);

  pinMode(zum, OUTPUT);
  pinMode(boton, INPUT);
}

void zumbador (int nota, int tiem) {
  tone (zum, nota, tiem);
  delay(tiem);
  noTone(zum);
}

void semaforo (){
  digitalWrite(luz1, HIGH);
  delay(1000);
  digitalWrite(luz0, HIGH);
  delay(1000);
  digitalWrite(luz2, HIGH);
  delay(1000);
  digitalWrite(luz3, HIGH);
  delay(1000);
  digitalWrite(luz4, HIGH);
  delay(1000);
  digitalWrite(luz0, LOW);
  digitalWrite(luz1, LOW);
  digitalWrite(luz2, LOW);
  digitalWrite(luz3, LOW);
  digitalWrite(luz4, LOW);
  zumbador(500, 500);
}

bool flancoBoton(){
  bool estadoActual = digitalRead(boton);
  int aux;
  if (estadoActual == HIGH && estadoAnterior == LOW){
    aux = 1;
  }
  else {
    aux =  0;
  }
  estadoAnterior = estadoActual;
  return aux;
}
