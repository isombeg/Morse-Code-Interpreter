const int ELEC_INPUT_PIN = 7;

//Letters and corresponding morse code
static bool A[ 2 ] = {false, true};
static bool B[ 4 ] = {true, false, false, false};
static bool C[ 4 ] = {true, false, true, false};
static bool D[ 3 ] = {true, false, false};
static bool E[ 1 ] = {false};
static bool F[ 4 ] = {false, false, true, false};
static bool G[ 3 ] = {true, true, false};
static bool H[ 4 ] = {false, false, false, false};
static bool I[ 2 ] = {false, false};
static bool J[ 4 ] = {false, true, true, true};
static bool K[ 3 ] = {true, false, true};
static bool L[ 4 ] = {false, true, false, false};
static bool M[ 2 ] = {true, true};
static bool N[ 2 ] = {true, false};
static bool O[ 3 ] = {true, true, true};
static bool P[ 4 ] = {false, true, true, false};
static bool Q[ 4 ] = {true, true, false, true};
static bool R[ 3 ] = {false, true, false};
static bool S[ 3 ] = {false, false, false};
static bool T[ 1 ] = {true};
static bool U[ 3 ] = {false, false, true};
static bool V[ 4 ] = {false, false, false, true};
static bool W[ 3 ] = {false, true, true};
static bool X[ 4 ] = {true, false, false, true};
static bool Y[ 4 ] = {true, false, true, true};
static bool Z[ 4 ] = {true, true, false, false};

bool dashDotDet(){
  bool powerState = digitalRead(ELEC_INPUT_PIN);
  if (powerState == HIGH){
    delay(1000);
    powerState = digitalRead(ELEC_INPUT_PIN);
    if (powerState == HIGH){
      return true;
    }
    else if(powerState == LOW){
      return false;
    }
  }
  else if(powerState == LOW){
    dashDotDet();
  }
}

bool chngCharDet(){
  if (digitalRead(ELEC_INPUT_PIN) == LOW){
    delay(2000);
    if (digitalRead(ELEC_INPUT_PIN) == LOW){
      return true;
    }
    else{
      return false;
    }
  }
}
//
//bool linkDashDot(){
//  bool dashDotList[ 4 ];
//  bool chngState = false;
//  int index = -1;
//  while (chngState == false){
//    index += 1;
//    bool blip = dashDotDet();
//    dashDotList[index] = blip;
//    chngState = chngCharDet();
//  }
//  for (int entry = 0; entry < 4, entry++){
//    if (dashDotList[entry] == void){
//      
//    }
//  }
//}

char charDet(){
  
}



void setup() {
  Serial.begin(9600);
  pinMode(ELEC_INPUT_PIN, INPUT);
  
}

void loop() {
  bool a = dashDotDet();
  if (a == true){
    Serial.println("Dash");
  }

  else if (a == false){
    Serial.println("Dot");
  }
  

}
