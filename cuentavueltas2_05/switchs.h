#pragma once

// PL pin 1
int loadB = 10;
// CE pin 15
int clockEnablePin = 13;
// Q7 pin 7
int dataIn = 12;
// CP pin 2
int clockIn = 11;

void setupSwitchs () {
  // Setup 74HC165 connections
  pinMode(loadB, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);
}

byte arrayBotones (){
  // Write pulse to loadB pin
  digitalWrite(loadB, LOW);
  delayMicroseconds(5);
  digitalWrite(loadB, HIGH);
  delayMicroseconds(5);
 
  // Get data from 74HC165
  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnablePin, LOW);
  byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin, HIGH);

  return incoming;
}
