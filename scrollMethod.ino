void scroll(int i, int c, int x) {

  //creates a new string every time this method is called in the for loop
  String displayedString = "";

  //for loop- each time this is passed, a new String will be created and printed on the LCD
  for (int n = i; n < x; n++) {
  
    if (c == 1) {
      displayedString += lyrics1[n];
    }

    if (c == 2) {
      displayedString += lyrics2[n];
    }
  }
  lcd.setCursor(0, 0);
 
  lcd.print(displayedString.substring(0, 17));
}
