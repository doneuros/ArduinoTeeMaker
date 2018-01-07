void meassureTempreature(){
  sensors.begin();      
   for(int i=0;i<10;i++){
      sensors.requestTemperatures();  
      Serial.println(sensors.getTempCByIndex(0));
      if(sensors.getTempCByIndex(0)>60){
        return;
      }
      delay(1000);
   }
  
}
