#include <math.h>
float x;
float y;
float x1;
float y1;
float mag;
float phase;
float Vl,Vr;
const byte interruptPin = 2;
volatile byte state = LOW;


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), door, LOW);
}

void loop() {
 
  x = analogRead(A0);
  y = analogRead(A1);
  x1=mapfloat(x, 0, 1023, -180, 180);
  y1=mapfloat(y, 0, 1023, -180, 180);
  mag=sqrt(pow(x1,2)+pow(y1,2));
  phase = degrees(atan2(y1, x1));

  if (phase>=0 && phase<=90){
    Vl=mag;
    Vr=mag-mapfloat(phase,0,90,0,mag);
    Serial.print("F");
  }
   else if (phase<0 && phase>=-90){
    Vr=mag;
    Vl=mag-mapfloat(phase,0,-90,0,mag);
    Serial.print("F");
  }
  else if (phase<-90 && phase>=-180){
    Vr=mag;
    Vl=mag-mapfloat(phase,-180,-90,0,mag);
    Serial.print("B");
  }
  else{
    Vl=mag;
    Vr=mag-mapfloat(phase,90,180,mag,0);
    Serial.print("B");
  }

  
  Serial.print(" ");
  Serial.print(int(Vl));
  Serial.print(" ");
  Serial.println(int(Vr));
  delay(10);
}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
 return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void door(){
  Serial.print("O");
  Serial.print(" ");
  Serial.print("1");
  Serial.print(" ");
  Serial.println("1");
}

