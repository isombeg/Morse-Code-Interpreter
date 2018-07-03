const int ELEC_INPUT_PIN = 7; //Digital pin 7 will be used to detect electrical input

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

bool dashDotDet(){ //Function determining whether input is a dash or a dot
  bool powerState = digitalRead(ELEC_INPUT_PIN); //Store whether button is being pushed or not in bool variable
  if (powerState == HIGH){ //In the event that button is being pushed, execute following procedure
    delay(1000);
    powerState = digitalRead(ELEC_INPUT_PIN); //If after a second the button is still down, register a dash
    if (powerState == HIGH){
      return true;
    }
    else if(powerState == LOW){ //If after a second the button isn't still down, register a dot
      return false;
    }
  }
  else if(powerState == LOW){ //If the button was never pressed in the first place, recur
    dashDotDet();
  }
}

bool chngCharDet(){ //Function determining whether or not the user will being inputting code for a different character
  if (digitalRead(ELEC_INPUT_PIN) == LOW){
    delay(2000);
    if (digitalRead(ELEC_INPUT_PIN) == LOW){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
} //If the button remains unpressed for more than 2 seconds, the software established that the user will input Morse code for a new character

bool linkDashDot(){ //Function that will link dashes and dots belonging to the Morse code for a certain character together
  bool first; bool scnd; bool third; bool fourth;
  bool fillList[ 5 ] = {first, scnd, third, fourth};
  bool chngState = false; // Boolean var that will later be assigned store whether user intends to change characters or not
  int index = -1;
  while (chngState == false){
    if (digitalRead(ELEC_INPUT_PIN) == LOW && index < 4){
      index += 1;
      bool blip = dashDotDet();
      fillList[index] = blip;
      chngState = chngCharDet();
    }
  }
  bool dashDotList[ index ];
  for (int entryNum = 0; entryNum < index; entryNum++){
    dashDotList[entryNum] = fillList[entryNum];
  }
  
  return dashDotList;
}

char charDet(){
  
}



void setup() {
  Serial.begin(9600);
  pinMode(ELEC_INPUT_PIN, INPUT);
  
}

void loop() {
  linkDashDot();
}
