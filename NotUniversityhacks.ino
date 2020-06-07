#include <LiquidCrystal.h>
#include <IRremote.h>
#include <TimerFreeTone.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//9716BE3F
//3D9AE3F7
//6182021B
//8C22657B
//488F3CBB

const int buzzerPin = 6;
const int blueLight = 7;
const int greenLight = 8;
const int redLight = 9; //this and the blue an green light pin are part of the RGB
const int remotePin = 10;
const int remoteLight = 13; //this is just a white led that flashes when remote is pressed
IRrecv irrecv(remotePin);
decode_results results;

const byte arraySize = 3;

typedef struct  {
  String question;
  String choices[5];
  int correctAnswer;
} questionGroup;

questionGroup question[arraySize] = {
  {"what is ajdkshfjahsdjkf", {"AHSKJDF", "FDJKG", "SFDHGKJ", "HGFJHF", "DJFHGKJDH"}, 2},
  {"what is what", {"AHSKJDF", "FDJKG", "SFDHGKJ", "HGFJHF", "DJFHGKJDH"}, 2},
  {"what is hello", {"AHSKJDF", "FDJKG", "SFDHGKJ", "HGFJHF", "DJFHGKJDH"}, 2}
};

int questionNumber = 0;
int choice;
int answer;

void setup() {
  // put your setup code here, to run once:
  pinMode (blueLight, OUTPUT);
  pinMode (greenLight, OUTPUT);
  pinMode (redLight, OUTPUT);
  pinMode (remoteLight, OUTPUT);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.clear();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // RGB_color(255, 0, 0); // Red
  // delay(1000);
  // RGB_color(0, 255, 0); // Green
  // delay(1000);

  while (questionNumber < arraySize) {

    printNextQuestion(questionNumber);
    delay(1000);
    if (irrecv.decode(&results)) {

      TimerFreeTone(buzzerPin, 300, 100);
      digitalWrite(remoteLight, HIGH);
      delay(100);
      digitalWrite(remoteLight, LOW);
      Serial.println(results.value, HEX);

      answer = question[questionNumber].correctAnswer;

      if (results.value == 0x9716BE3F || results.value == 0x3D9AE3F7 || results.value == 0x6182021B || results.value == 0x8C22657B || results.value == 0x488F3CBB) {

        switch (results.value) {
          case 0x9716BE3F: //Keypad button "1"
            choice = 1;
            break;
          case 0x3D9AE3F7: //Keypad button "2"
            choice = 2;
            break;
          case 0x6182021B: //Keypad button "3"
            choice = 3;
            break;
          case 0x8C22657B:
            choice = 4;
            break;
          case 0x488F3CBB:
            choice = 5;
            break;
        }
        Serial.println(choice);
        if (choice == answer) {
          RGB_color(0, 255, 0);
          delay(500);
          RGB_color(0, 0, 0);
        } else {
          RGB_color(255, 0, 0);
          delay(500);
          RGB_color(0, 0, 0);
        }
        questionNumber++;
      }

      irrecv.resume();
    }

  }

}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(redLight, red_light_value);
  analogWrite(greenLight, green_light_value);
  analogWrite(blueLight, blue_light_value);
}

void printNextQuestion(int index) {
  lcd.clear();
  String currentQuestion = question[index].question;
  lcd.print(currentQuestion);

}
