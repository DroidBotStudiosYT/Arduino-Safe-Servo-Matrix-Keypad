#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

#define LEDred 10 //(could be int assignments)
#define LEDgreen 9

char* passcode = "01B70*";
int pozisyon = 0;//the digit place for the passcode

const byte rows = 4;//4 rows
const byte cols = 4;//4 columns

char keyMap [rows] [cols] = {

  //matrix map for keypad
  
  {'1', '2', '3', 'A'},

  {'4', '5', '6', 'B'},

  {'7', '8', '9', 'C'},

  {'*', '0', '#', 'D'}

};

Servo myservo; //object name

int passwordLength = 6;

byte rowPins [rows] = {1, 2, 3, 4}; //pins of the rows
byte colPins [cols] = {5, 6, 7, 8}; //pins for the cols

Keypad myKeypad = Keypad (makeKeymap(keyMap), rowPins, colPins, rows, cols);
//definintion of keypad

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); //defining the liquid crystal pins

void setup() {
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDred, OUTPUT);
  lcd.begin(16, 2);
  setLocked(true); //function at the end
  myservo.attach(A6);//pin for receiving commands
  myservo.write(10);//angle for servo
  lcd.setCursor(0, 0);//setup for lcd
  lcd.print("  Arduino Safe");//center the text
  lcd.setCursor(0, 1);
  lcd.print(" Enter Passcode");//same here
  delay(3000);
  lcd.clear();
  lcd.print("Passcode:");//starts inserting digits after "Passcode:"
}

void loop() {

  char whichKey = myKeypad.getKey(); //getKey is a keyword
  //getting the signal of which key is pressed

  if (whichKey == passcode [pozisyon]) { //pozisyon is 0
    pozisyon++;
  }
  if (whichKey) { //typing...
    lcd.print(whichKey); //to the passcode
    if (whichKey == '#') { //reset key is the hashtag
      pozisyon = 0;
      setLocked(true);
      lcd.clear();
      lcd.print("Passcode:");
      myservo.write(10);
    }

  }
  if (pozisyon == passwordLength) { //passwordLength is 6 (set it to whatever you want)
    setLocked(false); //pozisyon gets the digits on the keypad to match
    myservo.write(90);//set the servo to a unlocked state
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*** Verified ***"); //prints...
    lcd .setCursor(0, 1);
    lcd.print("DroidBot Studios");
    delay(5000);
    lcd.clear(); 
  }

}

void setLocked(int locked) {
  if (locked) { //setLocked(true); is going to match this if-statement
    digitalWrite(LEDred, HIGH);
    digitalWrite(LEDgreen, LOW);
  }
  else {//vice versa
    digitalWrite(LEDred, LOW);
    digitalWrite(LEDgreen, HIGH);//series of blinking green LEDs
    delay(500);
    digitalWrite(LEDgreen, LOW);
    delay(100);
    digitalWrite(LEDgreen, HIGH);
    delay(500);
    digitalWrite(LEDgreen, LOW);
    delay(100);
    digitalWrite(LEDgreen, HIGH);
    delay(500);
    digitalWrite(LEDgreen, LOW);
    delay(100);
    digitalWrite(LEDgreen, HIGH);
  }
}
