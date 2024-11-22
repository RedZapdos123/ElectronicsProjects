//Including some custom libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Defining the pins
#define TRIG_PIN 2
#define ECHO_PIN 3
#define LASER_PIN 9
#define BUZZER_PIN 10
#define LED_PIN 13
#define UNUSED_GND_PIN 4

//Defining the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Defining the array of strings with words to be displayed
const char* names[] = {"BY:", " ", "MRIDANKAN", "PRANATHI", "ADITYA", "DHANNU", "ARSHIYA", "SHIVANI"};
const int numNames = 8;

//The driver code
void setup() {
  //Setting the pinmodes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LASER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(UNUSED_GND_PIN, OUTPUT);
  digitalWrite(UNUSED_GND_PIN, LOW);

  //Setting up the LCD display
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("EP INNOVATIVE");
  lcd.setCursor(0, 1);
  lcd.print("PROJECT");
  delay(2000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("SONIC RULER");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Measuring length");
  lcd.setCursor(0, 1);
  lcd.print("using sound");
  delay(1500);
  lcd.clear();

  //Displaying the names and the Project name
  for (int i = 0; i < numNames; i = i + 2) {
    lcd.setCursor(0, 0);
    lcd.print(names[i]);
    lcd.setCursor(0, 1);
    lcd.print(names[i + 1]);
    delay(1500);
    lcd.clear();
  }
}

//The loop function
void loop() {
  long duration, distanceCm;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //Calculating the distance through time duration ercho detection
  duration = pulseIn(ECHO_PIN, HIGH);
  distanceCm = duration * 0.034 / 2;

  lcd.setCursor(3, 0);
  lcd.print("Distance: ");
  lcd.setCursor(5, 1);
  lcd.print(distanceCm);
  lcd.print(" cm ");

  //Setting up the laser, buzzer and the on board Arduino UNO LED to produce output on detection
  if (distanceCm > 0 && distanceCm < 800) {
    digitalWrite(LASER_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LASER_PIN, LOW);
  }

  delay(500);
}
