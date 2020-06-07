#include <LiquidCrystal.h>
#include <IRremote.h>
#include <TimerFreeTone.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buzzerPin = 6;
const int blueLight = 7;
const int greenLight = 8;
const int redLight = 9; //this and the blue an green light pin are part of the RGB
const int remotePin = 10;
const int remoteLight = 13; //this is just a white led that flashes when remote is pressed
IRrecv irrecv(remotePin);
decode_results results;

const byte arraySize = 6;

typedef struct  {
  String question;
  String choices[5];
  int correctAnswer;
} questionGroup;

questionGroup question[arraySize] = {
  {"Cost of a single scantron paper?", {"15 cents", "20 cents", "25 cents", "30 cents", "35 cents"}, 5},
  {"What is the smallest country?", {"San Marino", "Luxembourg", "Chad", "Vatican City", "New Zealand"}, 4},
  {"What is the biggest island?", {"Greenland", "New Guinea", "Borneo", "Madagascar", "Java"}, 1},
  {"Where is the MLH headquarters?", {"Detroit", "New York", "Washington", "Philadelphia", "Chicago"}, 2},
  {"Who is the inventor of Bluetooth?", {"Jaap Hartsen", "Charle Babbage", "Graham Daniel", "Hedy Lamarr", "Ben Franklin"}, 1},
  {"What year was MLH founded?", {"2011", "2012", "2013", "2014", "2015"}, 3}
};

int questionNumber = 0;
int choice;
int answer;
int numCorrect = 0;
String realAnswer = "";

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

  while (questionNumber < arraySize) {

    printNextQuestion(questionNumber);
    if (irrecv.decode(&results)) {

      TimerFreeTone(buzzerPin, 300, 100);
      digitalWrite(remoteLight, HIGH);
      delay(100);
      digitalWrite(remoteLight, LOW);
      Serial.println(results.value, HEX);

      answer = question[questionNumber].correctAnswer;

      if (results.value == 0xFF30CF || results.value == 0xFF18E7 || results.value == 0xFF7A85 || results.value == 0xFF10EF || results.value == 0xFF38C7) {

        switch (results.value) {
          case 0xFF30CF: //Keypad button "1"
            choice = 1;
            break;
          case 0xFF18E7: //Keypad button "2"
            choice = 2;
            break;
          case 0xFF7A85: //Keypad button "3"
            choice = 3;
            break;
          case 0xFF10EF:
            choice = 4;
            break;
          case 0xFF38C7:
            choice = 5;
            break;
        }
        Serial.println(choice);
        if (choice == answer) {
          RGB_color(0, 255, 0);
          delay(500);
          RGB_color(0, 0, 0);
          numCorrect++;
          
        } else {
          RGB_color(255, 0, 0);
          delay(500);
          RGB_color(0, 0, 0);
          lcd.setCursor(0,0);
          lcd.print("Correct answer: ");
          lcd.setCursor(0,1);
          realAnswer = question[questionNumber].choices[question[questionNumber].correctAnswer-1];
          lcd.print(realAnswer);
          delay(2000);
        }
        questionNumber++;
      }

      irrecv.resume();
    }

  }
lcd.clear();
String congrats1 = "Congrats! You";
String congrats2 = "got "+ String(numCorrect)+"/"+String(arraySize)+" correct!";
lcd.print(congrats1);
lcd.setCursor(0,1);
lcd.print(congrats2);

RGB_color(255, 0, 0);
delay(200);
RGB_color(255, 153, 51);
delay(200);
RGB_color(255, 255, 0);
delay(200);
RGB_color(0, 255, 0);
delay(200);
RGB_color(0, 255, 255);
delay(200);
RGB_color(0, 255, 0);
delay(200);
RGB_color(0, 0, 255);
delay(200);
RGB_color(127, 0, 255);
delay(200);
RGB_color(255, 0, 255);
delay(200);

}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(redLight, red_light_value);
  analogWrite(greenLight, green_light_value);
  analogWrite(blueLight, blue_light_value);
}

void printNextQuestion(int index) {
  int counter = 0;
  lcd.clear();
  String currentQuestion1 = question[index].question.substring(0, 16);
  String currentQuestion2 = question[index].question.substring(16);
  lcd.setCursor(0,0);
  lcd.print(currentQuestion1);
  lcd.setCursor(0, 1);
  lcd.print(currentQuestion2);
  delay(2000);

  while (counter < 5 && !irrecv.decode(&results)) {
    String possibilities = String(counter + 1) + ". " + question[index].choices[counter];
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(possibilities);
    delay(2000);
    counter++;
  }

}
