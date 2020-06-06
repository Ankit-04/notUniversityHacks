
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
  Serial.begin(9600); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  RGB_color(255, 0, 0); // Red
  delay(1000);
  RGB_color(0, 255, 0); // Green
  delay(1000);
  lcd.print("Pls enter 1 or 2");
  lcd.setCursor(0, 1);
  lcd.print("into the monitor.");
  
  if (irrecv.decode(&results)) {

    TimerFreeTone(buzzerPin, 300, 100);
    digitalWrite(remoteLight, HIGH);
    delay(100);
    digitalWrite(remoteLight, LOW);
    Serial.println(results.value, HEX);
 
    irrecv.resume(); 
  }
  
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(redLight, red_light_value);
  analogWrite(greenLight, green_light_value);
  analogWrite(blueLight, blue_light_value);
}
