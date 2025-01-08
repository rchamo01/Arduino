#pragma once

#include <IRremote.h>

int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

char mando (){
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
    switch (results.value){
//      case 0x00FFA25D:
//        irrecv.resume(); // empezamos una nueva recepción
//        return 'A';
//      break;
      case 0x00FF629D:
        return 'B';
      break;
//      case 0x00FFE21D:
//        irrecv.resume();
//        return 'C';
//      break;
      case 0x00FF22DD:
        return 'D';
      break;
      case 0x00FF02FD:
        return 'E';
      break;
      case 0x00FFC23D:
        return 'F';
      break;
//      case 0x00FFE01F:
//        irrecv.resume();
//        return 'G';
//      break;
      case 0x00FFA857:
        return 'H';
      break;
//      case 0x00FF906F:
//        irrecv.resume();
//        return 'I';
//      break;
      case 0x00FF6897:
        return '1';
      break;
      case 0x00FF9867:
        return '2';
      break;
      case 0x00FFB04F:
        return '3';
      break;
      case 0x00FF30CF:
        return '4';
      break;
      case 0x00FF18E7:
        return '5';
      break;
      case 0x00FF7A85:
        return '6';
      break;
      case 0x00FF10EF:
        return '7';
      break;
      case 0x00FF38C7:
        return '8';
      break;
      case 0x00FF5AA5:
        return '9';
      break;
      case 0x00FF42BD:
        return 'X';
      break;
      case 0x00FF4AB5:
        return '0';
      break;
      case 0x00FF52AD:
        return 'Y';
      break;
      default:  
        return 'Z';
      break;
    }
  }
  
}
