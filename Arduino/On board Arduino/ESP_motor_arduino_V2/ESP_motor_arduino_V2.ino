#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

uint8_t servonum = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

const int IN1=10;
const int IN2=11;
const int ENA=6;

const int IN3=8;
const int IN4=7;
const int ENB=9;

int pulselength176 = map(176, 0, 180, SERVOMIN, SERVOMAX);
int pulselength46 = map(46, 0, 180, SERVOMIN, SERVOMAX);

void setup() {
  
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
   
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
     
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(ENB, OUTPUT);
  // initialize serial:
  Serial.begin(57600);
  pwm.setPWM(servonum, 0, pulselength176);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    int commaIndex = inputString.indexOf(' ');
      //Search for the next comma just after the first
    int secondCommaIndex = inputString.indexOf(' ', commaIndex + 1);
    String firstValue = inputString.substring(0, commaIndex);
    String secondValue = inputString.substring(commaIndex + 1, secondCommaIndex);
    String thirdValue = inputString.substring(secondCommaIndex + 1); // To the end of the string
    int Vl = secondValue.toInt();
    int Vr = thirdValue.toInt();
    Serial.print("Direction: ");
    Serial.print(firstValue);
    Serial.print("\t");
    Serial.print("Left_M: ");
    Serial.print(Vl);
    Serial.print("\t");
    Serial.print("Right_M: ");
    Serial.println(Vr);
    //Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
    drive(firstValue, Vl, Vr);
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void drive(String dir, int Ml, int Mr){
  if(dir=="F"){
    Motor1_Forward(Ml);
    Motor2_Forward(Mr);
    pwm.setPWM(servonum, 0, pulselength176);
  }
  else if(dir=="B"){
    Motor1_Backward(Mr);
    Motor2_Backward(Ml);
    pwm.setPWM(servonum, 0, pulselength176);
  }
  else if(dir=="O"){
    pwm.setPWM(servonum, 0, pulselength46);
  }
  
}

void Motor1_Forward(int Speed) 
{
     digitalWrite(IN1,HIGH); 
     digitalWrite(IN2,LOW);  
     analogWrite(ENA,Speed);
}
  
void Motor1_Backward(int Speed) 
{    
     digitalWrite(IN1,LOW); 
     digitalWrite(IN2,HIGH);  
     analogWrite(ENA,Speed);
}
void Motor1_Brake()      
{
     digitalWrite(IN1,LOW); 
     digitalWrite(IN2,LOW); 
}     
void Motor2_Forward(int Speed) 
{
     digitalWrite(IN3,HIGH); 
     digitalWrite(IN4,LOW);  
     analogWrite(ENB,Speed);
}
  
void Motor2_Backward(int Speed) 
{    
     digitalWrite(IN3,LOW); 
     digitalWrite(IN4,HIGH);  
     analogWrite(ENB,Speed);
}
void Motor2_Brake()
{
     digitalWrite(IN3,LOW); 
     digitalWrite(IN4,LOW); 
}

