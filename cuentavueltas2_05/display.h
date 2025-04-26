#pragma once

#include "LedControl.h"

LedControl lc = LedControl (7, 8, 9, 2);

void setupDisplay (){
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.shutdown(1,false);
  lc.setIntensity(1,1);
  lc.clearDisplay(0);
}

void display7segmentos(int vuel1, int min1, int seg1, int vuel2, int min2, int seg2){
  lc.setDigit(0,1,seg1 % 10,false);
  lc.setDigit(0,5,(seg1 / 10) % 10,false);
  lc.setDigit(0,7,(seg1 / 100) % 10,false);
  lc.setDigit(0,3,(seg1 / 1000) % 10,false);
  lc.setDigit(0,2,min1 % 10,false);
  lc.setDigit(0,6,(min1 / 10) % 10,false);
  lc.setDigit(0,4,vuel1 % 10,true);
  lc.setDigit(0,0,(vuel1 / 10)%10 ,false);
  ///////////////////////////////////
  lc.setDigit(1,1,vuel2 % 10,false);
  lc.setDigit(1,5,(vuel2 / 10) % 10,false);
  lc.setDigit(1,7,seg2 % 10,true);
  lc.setDigit(1,3,(seg2 / 10) % 10,false);
  lc.setDigit(1,2,(seg2 / 100) % 10,false);
  lc.setDigit(1,6,(seg2 / 1000) % 10,false);
  lc.setDigit(1,4,min2 % 10,false);
  lc.setDigit(1,0,(min2 / 10) % 10,false);
}
