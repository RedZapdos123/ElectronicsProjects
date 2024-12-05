//The pin numbers' variable
int laserPin = 9;
int ledPin = 10;
int buzzerPin = 11;

//The time durations of signals' outputs
int dotDuration = 800;
int dashDuration = 2000;
int symbolSpace = 250;
int letterSpace = 500;
int wordSpace = 3000;

//The string array to store the morse code translations of the characters
char* morseTable[36] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
  "...--", "....-", ".....", "-....", "--...", "---..", "----." 
};

//Setting up the pins for output and the serial monitor for input
void setup(){
  //Setting the pin modes for output
  pinMode(laserPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  //Taking input from the user through the serial monitor
  Serial.begin(9600);
  Serial.println("Enter a sentence: ");
}

//The loop function for transmission
void loop(){
  //Checking if the serial is operational
  if(Serial.available()){
    String input = Serial.readStringUntil('\n');
    input.trim();
    //Converting the letters to upper case
    input.toUpperCase();

    for(int i = 0; i < input.length(); i++){
      char c = input[i];

      if(c == ' ') {
        delay(wordSpace);
      } 
      else if(isAlphaNumeric(c)){
        int index;
        //Checking if the inputed character is a digit
        if(isDigit(c)){
          index = c - '0' + 26;
        } 
        else{
          index = c - 'A';
        }

        char* morse = morseTable[index];

        //Transmitting the morse code signal
        for(int j = 0; j < strlen(morse); j++){
          if(morse[j] == '.'){
            digitalWrite(laserPin, HIGH);
            digitalWrite(ledPin, HIGH);
            digitalWrite(buzzerPin, HIGH);
            delay(dotDuration);
          } 
          else if(morse[j] == '-'){
            digitalWrite(laserPin, HIGH);
            digitalWrite(ledPin, HIGH);
            digitalWrite(buzzerPin, HIGH);
            delay(dashDuration);
          }

          digitalWrite(laserPin, LOW);
          digitalWrite(ledPin, LOW);
          digitalWrite(buzzerPin, LOW);
          delay(symbolSpace);
        }

        //Delay for letter spaces
        delay(letterSpace);

      }
    }

    Serial.println("\nCompleted the transmission.\n");
  }
}

 