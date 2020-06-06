struct questionGroup{
    String question;
    String choices[5];
    int correctAnswer;
};

struct questionGroup question1 ={"what is ajdkshfjahsdjkf",{"AHSKJDF","FDJKG","SFDHGKJ","HGFJHF","DJFHGKJDH"}, 2};





void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.print(question1.choices[2]);
  delay(50000);

}
