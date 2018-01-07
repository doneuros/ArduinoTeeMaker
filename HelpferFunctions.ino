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

void helper2(){
  Serial.println("Ready");
}

void teaMaking(){
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

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {45, 42, 41, 38}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {53, 50, 49, 46}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void printMembraneInput(){
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }
}


