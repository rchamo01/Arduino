#include <LiquidCrystal.h>

LiquidCrystal lcd (7,6,5,4,3,2); //pin PCB
int V0 = 8; //pin PCB
int brill = 100;

int vueltas1 = 0, vueltas2 = 0;

int crono = 10; //esta en segundos

volatile bool distanciaInicial1;
volatile bool distanciaInicial2;



void setup() {
  Serial.begin(9600);
  ///////////////////////////////////////////
  //PANTALLA LCD
  lcd.begin(16,2);
  pinMode(V0, OUTPUT); //V0 pantalla LCD
  distanciaInicial1 = ADC0_promedio(A1, 20);
  distanciaInicial2 = ADC0_promedio(A2, 20);

}

void loop() {
  carrera();
  delay(10);
  

}

bool ADC0_promedio(int IR, int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(IR);
  }  
  if((suma/n) < 400){
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
    if (distanciaInicial1 == 0 && distanciaFinal1 == 1){
      aux = 1;
    }
    else {
      aux = 0;
    } 
    distanciaInicial1 = distanciaFinal1;
  }
  if (IR == A2){
    bool distanciaFinal2 = ADC0_promedio(IR, 20);
    if (distanciaInicial2 == 0 && distanciaFinal2 == 1){
      aux = 1;
    }
    else {
      aux = 0;
    }
    distanciaInicial2 = distanciaFinal2; 
  }

  return aux;
}

void carrera (){
  int tiempo_crono;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A:");
  lcd.print(vueltas1);
  lcd.setCursor(0,1);
  lcd.print("B:");
  lcd.print(vueltas2);
  lcd.setCursor(13,1);
  lcd.print(tiempo_crono);

  tiempo_crono = crono - millis()/1000;

  if (flancoIR(A1)){
      vueltas1++;
  }
  if (flancoIR(A2)){
      vueltas2++;
  }
  
  
}
