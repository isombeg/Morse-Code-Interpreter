const int ELEC_INPUT_PIN = 7; //Digital pin 7 will be used to detect electrical input

char *g = malloc(5);

//Letters and corresponding morse code
#define morse_A "01"
#define morse_B "1000"
#define morse_C "1010"
#define morse_D "100"
#define morse_E "0"
#define morse_F "0010"
#define morse_G "110"
#define morse_H "0000"
#define morse_I "00"
#define morse_J "0111"
#define morse_K "101"
#define morse_L "0100"
#define morse_M "11"
#define morse_N "10"
#define morse_O "111"
#define morse_P "0110"
#define morse_Q "1101"
#define morse_R "010"
#define morse_S "000"
#define morse_T "1"
#define morse_U "001"
#define morse_V "0001"
#define morse_W "011"
#define morse_X "1001"
#define morse_Y "1011"
#define morse_Z "1100"

//Classification of different characters and Morse Code:

  // Lists of the alphabet:
char *oneInpChar = "ET";
char *twoInpChar = "AIMN";
char *thrInpChar_A = "DGKO";
char *thrInpChar_B = "RSUW";
char *fourInpChar_A = "BCQXYZ";
char *fourInpChar_B = "FHJLPV";
  
  //Lists of lists containing the Morse code for each character above:
const char *oneInpDigits[ 2 ] = {morse_E, morse_T};
const char *twoInpDigits[ 4 ] = {morse_A, morse_I,morse_M, morse_N};
const char *thrInpDigits_A[ 4 ] = {morse_D, morse_G, morse_K, morse_O};
const char *thrInpDigits_B[ 4 ] = {morse_R, morse_S, morse_U, morse_W};
const char *fourInpDigits_A[ 6 ] = {morse_B, morse_C, morse_Q, morse_X, morse_Y, morse_Z};
const char *fourInpDigits_B[ 6 ] = {morse_F, morse_H, morse_J, morse_L, morse_P, morse_V};

int counter(char *code){
  
  int counter = 0;
  
  for (int i = 0; i < 4; i++){ //Loop counts how many 1s and 0s are in the loop
    
    if (code[i] == '0' || code[i] == '1'){
      counter++;
    }
  }
  
  return counter;
}

int dashDotDet(){ //Function determining whether input is a dash or a dot
  int powerState = digitalRead(ELEC_INPUT_PIN); //Store whether button is being pushed or not in bool variable
    
    if (powerState == HIGH){ //In the event that button is being pushed, execute following procedure
      
      delay(1000);
      powerState = digitalRead(ELEC_INPUT_PIN); //If after a second the button is still down, register a dash
      
      if (powerState == HIGH){
        return 1;
      }
      
      
      else if(powerState == LOW){ //If after a second the button isn't still down, register a dot
        return 0;
      }
    }
    else if(powerState == LOW){ //If the button was never pressed in the first place, recur
      dashDotDet();
    }
}

int chngCharDet(){ //Function determining whether or not the user will being inputting code for a different character
  if (digitalRead(ELEC_INPUT_PIN) == LOW){ //If button is unpressed
    int initTime = millis(); //Time elapsed in millisecs since program started running
    while (digitalRead(ELEC_INPUT_PIN) == LOW && millis() - initTime < 2000){ //while button remains unpressed and time elapsed since initializing initTime is less than 2000 ms
      
    }
    int finalTime = millis();
    if  ((finalTime - initTime) < 2000){
      return 0; //user not changing chars if time between initializing initTime and finalTime is lesser than 2000
    }
    else if (finalTime - initTime >= 2000){
      return 1; //user changing chars if time between initializing initTime and finalTime is greater than or equal to 2000
    }

  }
  else{
    chngCharDet();
  }
} //If the button remains unpressed for more than 2 seconds, the software established that the user will input Morse code for a new character

char *linkDashDot(){ //Function that will link dashes and dots belonging to the Morse code for a certain character together
  
  char dashDotStr[] = {NULL,NULL,NULL,NULL,'\0'}; //Initialize pointer with 4 chars
  int chngState; // Boolean var that will later be assigned store whether user intends to change characters or not
  int index = -1;

  Serial.println("Commencing recording of dash and dots\n");
  
  do{
    if (digitalRead(ELEC_INPUT_PIN) == LOW){
      
      index++;
      Serial.print("index: ");
      Serial.println(index);

      chngState = chngCharDet();
      Serial.print("chngState: ");
      Serial.println(chngState);

      if (chngState == 0){
      
        int blip = dashDotDet(); //bool stores whether entry is a dash or a dot
        Serial.print("blip: ");
        Serial.println(blip);
      
        dashDotStr[index] = (char) (blip + 48); //bool is stored in dashDotList
        Serial.print("dashDotStr: ");
        Serial.println(dashDotStr);
      
      }
      
    }
  } while (chngState == 0 && index < 3); //while user doesn't intend to change char and index is lesser than 3

  Serial.println("Terminating the recording process\n");
  
  return dashDotStr;
}

char charDet(char *morseCode, int arrSize){ //function to find character corresponding to morse code
  
  int indexNum = -1;
  switch(arrSize){
    
    case 1 :
      
      while (morseCode != oneInpDigits[indexNum] && indexNum <= 1){
        indexNum++;
      }

      return oneInpChar[indexNum];
      break;

    case 2 :
      //Serial.println("Case 2 satisfied");

      while (morseCode != twoInpDigits[indexNum] && indexNum <= 4){
        indexNum++;
      }

      //Serial.print("indexNum: ");
      //Serial.println(indexNum);
      return twoInpChar[indexNum];
      break;

    case 3 :
      //Serial.println("Case 3 satisfied");

      if (morseCode[0] == '1'){ //Procedure If morse code begins with 1
        while (morseCode != thrInpDigits_A[indexNum] && indexNum <= 4){
          indexNum++;
        }
        
        return thrInpChar_A[indexNum]; 
      }

      else if (morseCode[0] == '0'){ //Procedure if morse code begins with 0
        while (morseCode != thrInpDigits_B[indexNum] && indexNum <= 4){
          indexNum++;
        }
        
        return thrInpChar_B[indexNum]; 
      }
      
      break;

    case 4 :
      //Serial.println("Case 4 satisfied");

      if (morseCode[0] == '1'){ //Procedure If morse code begins with 1
        while (morseCode != fourInpDigits_A[indexNum] && indexNum <= 6){
          indexNum++;
        }
        
        return fourInpChar_A[indexNum]; 
      }

      else if (morseCode[0] == '0'){ //Procedure if morse code begins with 0
        while (morseCode != fourInpDigits_B[indexNum] && indexNum <= 6){
          indexNum++;
        }
        
        return fourInpChar_B[indexNum]; 
      }
      
      break;
  }
}



void setup() {
  Serial.begin(9600);
  pinMode(ELEC_INPUT_PIN, INPUT);
  Serial.println("Commencing recording process. Please begin inputting.\n");
  
}

void loop() {
  
  Serial.println(linkDashDot());

}
