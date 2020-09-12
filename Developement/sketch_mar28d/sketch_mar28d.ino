#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {0, 1, 10, 13}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  lcd.print("Press A to start");
  lcd.setCursor(0, 1);
  lcd.print("Program init");
  char key = keypad.getKey();

while(key != NO_KEY && key != 'A'){
  lcd.print("Tank Capacity");
  lcd.setCursor(0, 1); 
  lcd.print("Capacity:");
  char key1 = keypad.getKey();
  lcd.setCursor(8, 1);
  
  if(key1 !=NO_KEY && key1 != 'A' && key1 != 'B' && key1 != 'C' && key1 != 'D') {
  lcd.print("Fill time");
  lcd.setCursor(0, 1); 
  lcd.print("time:");
  
  }
  
}
}

void loop() {

}
