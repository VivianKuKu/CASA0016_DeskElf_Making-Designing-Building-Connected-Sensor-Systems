#include "Timer.h"

int ldr=A0;//Set A0(Analog Input) for LDR.
int value_ldr=0;


Timer t;  

void setup()
{

  Serial.begin(9600);
  t.every(5000,WriteToSerial); 
  
}

void loop()
{
  
  value_ldr = analogRead(ldr);//Reads the Value of LDR(light).
  Serial.println("LDR value is :");//Prints the value of LDR to Serial Monitor.
  Serial.println(value_ldr);
  delay(1000);
  
  

  if(value_ldr < 100){
    
      t.update(); // Update t  
  }
  
}

void WriteToSerial()
{
  
  Serial.println("Hello World");

}
