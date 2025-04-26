#pragma once

volatile bool distanciaInicial1;
volatile bool distanciaInicial0;
int dist = 350;

int dist_promedio(int IR)
{
  long suma=0;
  int n = 20;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(IR);
  }
  return suma/n;
}

bool ADC0_promedio(int IR)
{
  if(dist_promedio (IR) < dist){
    return 0;
  }
  else{
    return 1;
  }
}

bool flancoIR (int IR){
  bool aux = 0;
  
  if (IR == A1){
    bool distanciaFinal1 = ADC0_promedio(IR);
    
    if ((distanciaInicial1 == 0 && distanciaFinal1 == 1)){
      aux = 1;
    }
    else {
      aux = 0;
    } 
    distanciaInicial1 = distanciaFinal1;
  }
  if (IR == A0){
    bool distanciaFinal0 = ADC0_promedio(IR);
    
    if ((distanciaInicial0 == 0 && distanciaFinal0 == 1)){
      aux = 1;
    }
    else {
      aux = 0;
    }
    distanciaInicial0 = distanciaFinal0; 
  }

  return aux;
}
