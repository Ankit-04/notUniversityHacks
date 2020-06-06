#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 12, 13);

typedef struct  {
  String question;
  String choices[5];
  int correctAnswer;
} questionGroup;

//starting from here

const byte arraySize = 3;

questionGroup question[arraySize] = {
  {"what is ajdkshfjahsdjkf", {"AHSKJDF", "FDJKG", "SFDHGKJ", "HGFJHF", "DJFHGKJDH"}, 2},
  {"what is what", {"AHSKJDF", "FDJKG", "SFDHGKJ", "HGFJHF", "DJFHGKJDH"}, 2},
  {"what is hello", {"AHSKJDF", "FDJKG", "SFDHGKJ", "HGFJHF", "DJFHGKJDH"}, 2}
};

// to here replace the code with what the pthon file gives you

bool answered = false;
int questionNumber = -1;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

}

void loop() {
  while (questionNumber != arraySize - 1) {
    answered = false;

    while (answered == false) {
      // check if a option is selected, if so set answered to true so the loop breaks
      delay(5000);
      break;
    }
    questionNumber++;
    printNextQuestion(questionNumber);

  }
  lcd.clear();
  lcd.write("you got a __ out of __");
  delay(1000000);
}
void printNextQuestion(int index) {
  lcd.clear();
  lcd.print(question[index].question);
}
