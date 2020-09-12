//Hello, This is the code to use a 4x4 keypad matrix with and Arduino and show the result on an LCD screen
//You should wire you keypad from 8to1 (keypad pins) to 9to2 Arduino digital pins
//SurtrTech

#include <Keypad.h> //The keypad and LCD i2c libraries
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27 //defining the LCD pins
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad
//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {8,7,6,5}; //Rows 0 to 3 //if you modify your pins you should modify this too
byte colPins[numCols]= {4,3,2,1}; //Columns 0 to 3
//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

int GetNumber()
{
   int num = 0;
   char key = myKeypad.getKey();
   while(key != '#')
   {
      switch (key)
      {
         case NO_KEY:
            break;

         case '0': case '1': case '2': case '3': case '4':
         case '5': case '6': case '7': case '8': case '9':
            lcd.print(key);
            num = num * 10 + (key - '0');
            break;

         case '*':
            num = 0;
            lcd.clear();
            digitalWrite(12, LOW);
            digitalWrite(13, LOW);
            lcd.clear();
            lcd.home ();
            lcd.print("DSCE Station");
            lcd.setCursor(0,1);
            lcd.print("Fuel Amount : ");
            delay(2000);
            break;
      }

      key = myKeypad.getKey();
   }

   return num;
}
void setup()
           {
            Serial.begin(9600);   // Initiate a serial communication
            SPI.begin();      // Initiate  SPI bus
            mfrc522.PCD_Init();   // Initiate MFRC522
            Serial.println("Approximate your card to the reader...");
            Serial.println();
            pinMode(13,OUTPUT);
            pinMode(12,OUTPUT);
            Serial.begin(9600);
            lcd.begin (16,2);
            lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
            lcd.setBacklight(HIGH);
            lcd.home ();
            lcd.print("DSCE Station");
            lcd.setCursor(0,1);
            lcd.print("Fuel Amount : ");
            delay(2000);
           }

void loop()
{
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "49 4F 58 5A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Welcome to DSCE Petrol Station.");
    Serial.println("Customer ID : 1");
    Serial.println("Customer Name : Akshay Bankapure");
    Serial.println("Total Balance : Rs 500");
    Serial.println("User Authenticated! Proceed with refueling.");
    
    Serial.println();
    delay(3000);
  }
 
 else   {
    {
    Serial.println("Invalid Customer!");
    
    
    Serial.println();
    delay(3000);
  }
  }
   int v1 = GetNumber();
   int price=v1*71.23;
   int remaining=500-price;
   if(price<=500&& content.substring(1) == "49 4F 58 5A"){
    lcd.clear();
    lcd.home();
    lcd.print("Amount: ");
    lcd.print(price);
    digitalWrite(A1, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Remaining: ");
    lcd.print(remaining);
   }
   else{
    lcd.clear();
    lcd.home();
    digitalWrite(A0, HIGH);
    lcd.print("ERROR!");
   }
   Serial.println("Operation complete. See you soon!");
   

}
