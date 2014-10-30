  // defining the alphabet
  #include "font.h"
  #include <Time.h>

  // define the Arduino LED pins in use
  // const int LEDpins[] = {11,10,9,8,7,6,5,4};
  const int LEDpins[] = {4,5,6,7,8,9,10,11};
  
  // sensor setup
  const int sensorPIN = A1;  // define the Arduino sensor pin
  
  // number of LEDs
  const int charHeight = 8;
  const int charWidth = 5;
  
  // Total LED's in a row
  int rows= 8;

  // variable to store the value coming from the sensor		        
  int sensVal;  
  
  int i;
  char textString[] = "KOOS POV TEST";
  
  String tmp_str;

  void setup()
  {
  	//hr,min,sec,day,month,yr
    setTime(22,30,30,27,10,2014);
    
    pinMode(sensorPIN, INPUT);

    for (i = 0; i < rows; i++){
      pinMode(LEDpins[i], OUTPUT);    
    }

    pinMode(12, OUTPUT);
    digitalWrite(12 , HIGH);
    
    pinMode(3, OUTPUT);
    digitalWrite(3 , HIGH);

    Serial.begin(9600);
  }

  void loop()
  {

    tmp_str = clokTime();
    tmp_str = tmp_str + " ";
    
    Serial.print(analogRead(sensorPIN));
    // while(analogRead(sensorPIN) != 0)
    // {
    //   digitalWrite(13, LOW);   // set the LED off
    // }
    
    // digitalWrite(13, HIGH);   // set the LED on
    
    // printen klok letter voor letter
    for (int k = 0; k < tmp_str.length(); k++){
      printLetter(tmp_str.charAt(k));
    }
    
    // delay(2); // pauze tussen de teksten  
    
    // for (int k = sizeof(textString)-1; k > -1; k--){
    //   printLetterboven(textString[k]);
    // }  
  }

  String clokTime(){

    String str1;
    String str2;
    String str3;

    if (hour() < 10)
      str1 = "0" + String(hour());
    else
      str1 = String(hour());
    if (minute() < 10)
      str2 = "0" + String(minute());
    else
      str2 = String(minute());
    if (second() < 10)
      str3 = "0" + String(second());
    else
      str3 = String(second());

    return str1 + ":" + str2 + ":" + str3;
  }

  void printLetterboven(char ch)
  {
    // make sure the character is within the alphabet bounds (defined by the font.h file)
    // if it's not, make it a blank character
    if (ch < 32 || ch > 126){
      ch = 32;
    }
    // subtract the space character (converts the ASCII number to the font index number)
    ch -= 32;
    // step through each byte of the character array
    for (int i = charWidth - 1; i > -1; i--) {
      byte b = font[ch][i];
      // ventilator draai tegen de klok in
      for (int j = 0; j < charHeight; j++) {
        digitalWrite(LEDpins[j], bitRead(b,j));
      }
        delay(1);
    }
    //clear the LEDs
    for (i = 0; i < rows; i++){
      digitalWrite(LEDpins[i] , LOW);
    }
    // space between letters
    delay(1);

  }  

  void printLetter(char ch)
  {
    // make sure the character is within the alphabet bounds (defined by the font.h file)
    // if it's not, make it a blank character
    if (ch < 32 || ch > 126){
      ch = 32;
    }
    // subtract the space character (converts the ASCII number to the font index number)
    ch -= 32;
    // step through each byte of the character array
    for (int i = 0; i < charWidth; i++) {
      byte b = font[ch][i];
      // ventilator draai tegen de klok in
      for (int j = 0; j < charHeight; j++) {
        digitalWrite(LEDpins[j], bitRead(b, 7-j));
      }
      delay(1);
    }
    //clear the LEDs
    for (i = 0; i < rows; i++){
      digitalWrite(LEDpins[i] , LOW);
    }
    // space between letters
    delay(1);
  }
