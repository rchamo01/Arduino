#pragma once

#define DO 523.25
#define RE 587.33
#define MI 659.26
#define FA 698.46
#define SOL 783.99
#define LA 880
#define SI 987.77
#define RE2 1174.66
#define DO2 1062
#define DoS 554.37
#define RES 622.25
#define FAS 739.99
#define SOLS 830.61
#define FAS2 1479.98
#define a 1000
#define b 500
#define c 400

///////////////////////////////////////////
//ZUMBADOR
int ZUM = 9;

void zumbador(byte x, byte y, byte z){
  tone(ZUM, x, y);
  delay(z);
  noTone(ZUM);
}

void himnoESPANA (int pin){
  //int a = 1000, b = 500, c = 400;
  int temp[] = {a, a, a, b, b, b, b, b, b, b, b, b, b, a, a, 1500, b, b, b, b, b, 2000,
  a, 250, 250, a, 250, 250, a, 250, 250, b, b, b, b, a, a, 250, 250, b, b, a, a, 2000};
  int tiemp[] = {b, b, b, b, c, c, c, c, c, c, c, c, c, b, b, a, c, c, c, c, c, a,
  b, b, c, c, b, c, b, c, c, c, c, c, c, b, b, b, c, c, c, b, b, a};
  float mus[] = {SOL, RE, SI, SOL, RE2, DO2, SI, LA, SOL, SOL, FAS, MI, RE, SOL, LA, SI, RE2, DO2, SI, LA, SOL, RE2,
  RE2, SI, RE2, DO2, LA, DO2, SI, SOL, SI, LA, RE, MI, FAS, SOL, LA, SI, DO2, RE2, DO2, SI, LA, SOL};
  for (int i = 0; i<44;i++){
    tone (ZUM, mus[i], temp[i]);
    delay(tiemp[i]);
    noTone(ZUM);
  }
}
