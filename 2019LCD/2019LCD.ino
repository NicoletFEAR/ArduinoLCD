//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
#include <Wire.h>
/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

boolean connectedToRIO = false; // are we connected to the RoboRIO?
String whatToDoWithYou; // What must be executed >:D
String currentPlay = "?";
String currentPos = "?";
String switch1 = "?";
String switch2 = "?";
String switch3 = "?";
String switch4 = "?";
String toDo;
String delayVal = "";

void resetLcd()
{
  lcd.clear();
  lcd.setCursor(0,0);
}

int callFromRIO(int bytesComing)
{
  whatToDoWithYou = "";
  while ( Wire.available() > 0 )  {
    char n = (char)Wire.read();
    if (((int)n) > ((int)(' ')))
      whatToDoWithYou += n;
  }
}

void setup()
{
 lcd.begin(16, 2);              // start the library
 resetLcd(); // reset display
 lcd.setCursor(0,0); // set cursor to start

 
  lcd.print("Starting Up! :D");
  lcd.setCursor(0,1);
  lcd.print("---+++---+++--->");
  // RoboRIO my love!!! :)
  delay(10000);
  Wire.begin(8);
  Wire.onReceive(callFromRIO);
  // Rev up your serial ports to 9600 bps:
  Serial.begin(9600);
  //Make sure everyone sees that amazing start up screen ;)
  delay(4000);
}
 
void loop()
{

  toDo = whatToDoWithYou;
  
  Serial.println(whatToDoWithYou);
  currentPos = toDo.charAt(0);
  currentPlay = toDo.charAt(1);
  switch1 = toDo.charAt(2);
  switch2 = toDo.charAt(3);
  switch3 = toDo.charAt(4);
  switch4 = toDo.charAt(5);
  delayVal = "";
  delayVal = toDo.substring(6);

  Serial.println(switch1);
  Serial.println(switch4);
    if (currentPos == "")
    currentPos = "E";
  if (currentPlay == "")
    currentPlay = "E";
  if (delayVal == "")
    delayVal = "E";
  if (switch1 == "")
    switch1 = "E";
  if (switch2 == "")
    switch2 = "E";
  if (switch3 == "")
    switch3 = "E";
  if (switch4 == "")
    switch4 = "E";

    // print the information:
  resetLcd();
  lcd.setCursor(0,0);
  lcd.print("POS:");
  lcd.print(currentPos);
  lcd.setCursor(0,1);
  lcd.print("PLAY:");
  lcd.print(currentPlay);
  
  lcd.setCursor(7,0);
  lcd.print("BKP:");
  lcd.print(switch1);
  lcd.print(switch2);
  lcd.print(switch3);
  lcd.print(switch4);
  
  lcd.setCursor(7,1);
  lcd.print("DLY: ");
  lcd.print(delayVal);

  delay(100);
 
}
