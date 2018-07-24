const int ELEC_INPUT_PIN = 7; //Digital pin 7 will be used to detect electrical input

//Letters and corresponding morse code
int A[ 2 ] = {0, 1};
int B[ 4 ] = {1, 0, 0, 0};
int C[ 4 ] = {1,0,1,0};
int D[ 3 ] = {1,0,0};
int E[ 1 ] = {0};
int F[ 4 ] = {0,0,1,0};
int G[ 3 ] = {1,1,0};
int H[ 4 ] = {0,0,0,0};
int I[ 2 ] = {0,0};
int J[ 4 ] = {0,1,1,1};
int K[ 3 ] = {1,0,1};
int L[ 4 ] = {0,1,0,0};
int M[ 2 ] = {1,1};
int N[ 2 ] = {1,0};
int O[ 3 ] = {1,1,1};
int P[ 4 ] = {0,1,1,0};
int Q[ 4 ] = {1,1,0,1};
int R[ 3 ] = {0,1,0};
int S[ 3 ] = {0,0,0};
int T[ 1 ] = {1};
int U[ 3 ] = {0,0,1};
int V[ 4 ] = {0,0,0,1};
int W[ 3 ] = {0,1,1};
int X[ 4 ] = {1,0,0,1};
int Y[ 4 ] = {1,0,1,1};
int Z[ 4 ] = {1,1,0,0};

//Classification of different characters and Morse Code:

  // Lists of the alphabet:
char oneInpChar[ 2 ] = {'E','T'};
char twoInpChar[ 4 ] = {'A','I','M','N'};
char thrInpChar_A[ 4 ] = {'D','G','K','O'};
char thrInpChar_B[ 4 ] = {'R','S','U','W'};
char fourInpChar_A[ 6 ] = {'B','C','Q','X','Y','Z'};
char fourInpChar_B[ 6 ] = {'F','H','J','L','P','V'};
  
  //Lists of lists containing the Morse code for each character above:
int oneInpDigits[ 2 ][ 1 ] = {{E},{T}};
int twoInpDigits[ 4 ][ 2 ] = {{A},{I},{M},{N}};
int thrInpDigits_A[ 4 ][ 3 ] = {{D},{G},{K},{O}};
int thrInpDigits_B[ 4 ][ 3 ] = {{R},{S},{U},{W}};
int fourInpDigits_A[ 6 ][ 4 ] = {{B},{C},{Q},{X},{Y},{Z}};
int fourInpDigits_B[ 6 ][ 4 ] = {{F},{H},{J},{L},{P},{V}};

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
  if (digitalRead(ELEC_INPUT_PIN) == LOW){ //If button is unpressed
    int initTime = millis(); //Time elapsed in millisecs since program started running
    while (digitalRead(ELEC_INPUT_PIN) == LOW && millis() - initTime < 2000){ //while button remains unpressed and time elapsed since initializing initTime is less than 2000 ms
      
    }
    int finalTime = millis();
    if  ((finalTime - initTime) < 2000){
      return false; //user not changing chars if time between initializing initTime and finalTime is lesser than 2000
    }
    else if (finalTime - initTime >= 2000){
      return true; //user changing chars if time between initializing initTime and finalTime is greater than or equal to 2000
    }

  }
  else{
    chngCharDet();
  }
} //If the button remains unpressed for more than 2 seconds, the software established that the user will input Morse code for a new character

bool linkDashDot(){ //Function that will link dashes and dots belonging to the Morse code for a certain character together
  int dashDotList[ 4 ] = {2, 2, 2, 2}; //Initialize list with 4 entries
  bool chngState = false; // Boolean var that will later be assigned store whether user intends to change characters or not
  int index = -1;

  while (chngState == false && index < 3){ //while user doesn't intend to change char and index is lesser than 3
    if (digitalRead(ELEC_INPUT_PIN) == LOW){
      index += 1;
      bool blip = dashDotDet(); //bool stores whether entry is a dash or a dot
      dashDotList[index] = blip; //bool is stored in dashDotList
      chngState = chngCharDet();
    }
  }
  int counter = 0;
  
  for (int i = 0; i < 4; i++){ 
    if (dashDotList[i] == 0 || dashDotList[i] == 1){
      counter += 1;
      Serial.print("counter: ");
      Serial.println(counter);
    }
  }

  int rsltList[ counter ];
  for (int i = 0; i < counter; i++){
    rsltList[i] = dashDotList[i];
  }
  
  return rsltList, counter;
}

char charDet(int morseCode[ ], int arrSize){ //function to find character corresponding to morse code
  Serial.println(morseCode[0]);
  switch(arrSize){
    case 1 :
      Serial.println("Case 1 satisfied");
      Serial.print("morseCode[0]: "); Serial.println(morseCode[0]);
      for (int i = 0; i < 2; i++){
        Serial.print("oneInpDigits[i][0]: "); Serial.println(oneInpDigits[i][0]);
        if (morseCode[0] == oneInpDigits[i][0]){
          return oneInpChar[i];
        }
      }
      break;

    case 2 :
      Serial.println("Case 2 satisfied");
  }
}



void setup() {
  Serial.begin(9600);
  pinMode(ELEC_INPUT_PIN, INPUT);
  
}

void loop() {
 Serial.println(charDet({0},1));

}
