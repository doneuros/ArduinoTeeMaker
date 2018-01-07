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


