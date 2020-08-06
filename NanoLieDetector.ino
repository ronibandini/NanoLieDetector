
/* 
Nano Lie Detector
Roni Bandini
Buenos Aires, Argentina 8/2020
Twitter/Instagram @RoniBandini

Connections
GSR1 1 -> A1, 300K Resisor, GND
GSR 2 -> 5V
Heart rate monitor A0, 5v and GND
Vu-meter 3 and GND, 6 and GND
Buzzer D5 and GND

*/

#define USE_ARDUINO_INTERRUPTS true     
#include <PulseSensorPlayground.h>        

//  Pins
const int PulseWire = 0;  
int vumeterPin1 = 3;  
int vumeterPin2 = 6;  
int buzzerPin = 5;    
int potPin = 2;    
const int galvanicPin = 1;
const int LED13 = 13;         

int Threshold = 510;           

int galvanicVal =0;
int galvanicVumeter=0;
int galvanicCompensation=100;
int counter=0;
                               
PulseSensorPlayground pulseSensor;   


void setup() {   

  int myV=0;

  // move needles to top
  while (myV<20)
  {
    analogWrite(vumeterPin1, myV);  
    analogWrite(vumeterPin2, myV);  
    Serial.println(myV); 
    delay(50);    
    myV=myV+1;
  }

  analogWrite(vumeterPin1, 0);
  analogWrite(vumeterPin2, 0);

  tone(buzzerPin, 100);  
  delay(100);   
  noTone(buzzerPin);         
  
  Serial.begin(9600);         
  Serial.println("Nano Lie Detector started - Roni Bandini"); 
  
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);        
  Serial.println("Threesold");
  Serial.println(Threshold);  
   
  pulseSensor.setThreshold(Threshold);   

   if (pulseSensor.begin()) {
    Serial.println("PulseSensor Object ready"); 
  }
}



void loop() {
 
 
  int myBPM = pulseSensor.getBeatsPerMinute();                                                    
  
  if (pulseSensor.sawStartOfBeat()) {            

  // update galvanic 1/3
  if (counter==3){
   galvanicVal = analogRead(galvanicPin); 
    galvanicVal=galvanicVal-galvanicCompensation;
   counter=1;
  }
 else
  {  
    counter++;
  }
                       
 if (myBPM<180){
  Serial.println("♥");    
  analogWrite(vumeterPin1, 12);

  Serial.print("Galvanic: "); 
  Serial.println(galvanicVal); 
  
  if (galvanicVal>0)
  {
   // map value to fit vu-meter scale
   galvanicVumeter=map(galvanicVal,0,1024,0,20);
  }
  else
  {
   galvanicVumeter=0;
  }
  
  
  Serial.print("Galvanic vu-meter: "); 
  Serial.println(galvanicVumeter); 
  analogWrite(vumeterPin2, galvanicVumeter);

  if (galvanicVal>800){
    tone(buzzerPin, 50);  
    delay(10);   
    noTone(buzzerPin); 
    }
    
 }
}

  delay(20);                   
  // return needle for beat movement  
  analogWrite(vumeterPin1, 2);    

}

  
