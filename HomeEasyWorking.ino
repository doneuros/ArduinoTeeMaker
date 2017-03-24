//http://www.instructables.com/id/RF-315433-MHz-Transmitter-receiver-Module-and-Ardu/step3/Arduino-Virtual-Wire-Library/
#include <HomeEasyCtrl.h>
#include <Servo.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

// Turorial: http://www.instructables.com/id/Make-a-pushbutton-without-a-resistor/
const int BUTTON_PIN = 6;//2;     // the number of the pushbutton pin
const int LED_PIN =  13;    // the number of the LED pin
const int LED_PIN_HOME_EASY =  8;
const int TRANSMITTER_PIN =  4;//3; //https://funksteckdose.net/mit-microcontrollern-steuern    
const int ONE_WIRE_BUS = 2;
const int SERVO_PIN = 9;//https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors?view=all

HomeEasyCtrl easy(TRANSMITTER_PIN,LED_PIN_HOME_EASY);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// variables will change:
int state = 2; //true=On, false=Off 
int buttonState = 0;         // variable for reading the pushbutton status
int counter = 0;
Servo servo1;

void setup() {
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_HOME_EASY, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT); 
  pinMode(LED_PIN_HOME_EASY, INPUT); 
  //initialize the buttonPin as output
  digitalWrite(BUTTON_PIN, HIGH); 
  setUpServo(); 
}

void setUpServo(){
  pinMode(1,OUTPUT);
  servo1.attach(SERVO_PIN); //analog pin 0
  Serial.println("Ready");
}

// the loop function runs over and over again forever
void loop() {
  //if tee is started
  if(state==1){
     Serial.println("Tee Started");
     digitalWrite(LED_PIN,HIGH);
     easy.deviceOn(); 
     meassureTempreature();
     rotateServo();
     digitalWrite(LED_PIN,LOW);  
     easy.deviceOff();   
     Serial.println("Tee finished");
     state=0;
  } if(state==2) {
     for(int i=0;i<10;i++){
        easy.deviceOn(); 
        delay(1000);
     }
     easy.deviceOff(); 
     state=0;
     Serial.println("Learning Finish");
  }else {  
    //listening for button or serial input to start tee routine
    buttonState = digitalRead(BUTTON_PIN);
    int data = readingData();
    if(data==1 || buttonState==LOW){
      Serial.println("Input for Tee");
      state=1;
    }
  }  
}

void rotateServo(){
     servo1.write(0);
     delay(1000);
     servo1.write(170);
     delay(1000);
     servo1.write(0);
}

void meassureTempreature(){
  sensors.begin();      
   for(int i=0;i<100;i++){
      sensors.requestTemperatures();  
      Serial.println(sensors.getTempCByIndex(0));
      if(sensors.getTempCByIndex(0)>60){
        return;
      }
      delay(1000);
   }
  
}

int readingData(){
    if (Serial.available()) {
      int input = Serial.read()-'0';
      if(input==1){
        Serial.println("Serial Input for Tee");
        return input;  
      }      
     } 
     return 0;
}

