int pin = 2;
int i = 0;
void setup() {
  Serial.begin(115200);
  Serial.println("begin");
  

}

void loop() {
  if (Serial.available()){
    
    i = Serial.parseInt();

    switch(i){
      case 1:
        i = 0;
        makePinHigh();
        break;
      case 2:
        i = 0;
        makePinLow();
        break;
      case 3:
        i = 0;
        Serial.println("input floating");
        makePinInput(); 
        break;
      case 4:
        i = 0;
        Serial.println("input pull up");
        makePinInputPullup();
        break;
      default:
        i = 0;
      break;
    }
    
//    if (i == 1){
//      i = 0;
//      makePinHigh();
//    } else if (i = 2){
//      i = 0;
//      makePinLow();
//    } else if (i == 3){
//      i = 0;
//      Serial.println("input floating");
//      makePinInput();
//    } else if (i == 4){
//      i = 0;
//      Serial.println("input pull up");
//      makePinInputPullup();
//    } else if (i == 5){
//      i = 0;
//      makePinInputPulldown();
//    } else {
//      i = 0;
//    }
  }
}


void makePinHigh(){
  Serial.println("high:");
  pinMode(pin,OUTPUT);
  digitalWrite(pin,HIGH);
  
}

void makePinLow(){
  Serial.println("low:");
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  
}

void makePinInput(){
  Serial.println("input floating");
  pinMode(pin, INPUT);
  
}

void makePinInputPullup(){
  Serial.println("input pull up");
  pinMode(pin, INPUT_PULLUP);
  
}

void makePinInputPulldown(){
//  pinMode(pin, INPUT_PULLDOWN)
  
}
