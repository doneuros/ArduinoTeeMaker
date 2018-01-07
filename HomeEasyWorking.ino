//http://www.instructables.com/id/RF-315433-MHz-Transmitter-receiver-Module-and-Ardu/step3/Arduino-Virtual-Wire-Library/
#include <HomeEasyCtrl.h>
#include <Servo.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Keypad.h>

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
  helper2();
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
  Serial.println("loop ...");
  //printMembraneInput();
}







