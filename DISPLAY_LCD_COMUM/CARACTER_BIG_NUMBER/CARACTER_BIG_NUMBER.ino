#include <Wire.h>

#include <LiquidCrystalFast.h>
LiquidCrystalFast lcd(10 , 11, 7 , 8 , 6 , 5 , 4 , 3);
                  //  RS   RW  E1  E2  D4  D5  D6  D7

//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//0x3F AZUL PEQUENO 20X4
//0X27 BIG NUMBER   20X4


byte simb_1[8] = {
B01111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111};

byte simb_2[8] = {
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11110};

byte simb_3[8] = {
B11110,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111};

byte simb_4[8] = {
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B01111};

byte simb_5[8] = {
B11111,
B11111,
B00000,
B00000,
B00000,
B00000,
B11111,
B11111};

byte simb_6[8] = {
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111};

byte simb_7[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B11111,
B11111};

byte simb_8[8] = {
B11111,
B11111,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void setup()
{
  lcd.begin(40,4);
  //lcd.init();               
  //lcd.backlight();
  lcd.clear();
  
  lcd.createChar(0, simb_8);     
  lcd.createChar(1, simb_1);
  lcd.createChar(2, simb_2);
  lcd.createChar(3, simb_3);
  lcd.createChar(4, simb_4);
  lcd.createChar(5, simb_5);
  lcd.createChar(6, simb_6);
  lcd.createChar(7, simb_7);

  Serial.begin(9600);
  //lcd.begin (20,4);
  //lcd.clear();  


}
  
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
      
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
void loop()
{
  // numero 0
  lcd.setCursor(16,0);
  lcd.print((char)1);
  lcd.setCursor(17,0);
  lcd.print((char)0);
  lcd.setCursor(18,0);
  lcd.print((char)3);
  lcd.setCursor(16,1);
  lcd.print((char)4);
  lcd.setCursor(17,1);
  lcd.print((char)7);
  lcd.setCursor(18,1);
  lcd.print((char)2);
  delay(1000);
  
  // numero 1
  lcd.setCursor(0,0);
  lcd.print((char)0);
  lcd.setCursor(1,0);
  lcd.print((char)3);
  lcd.setCursor(2,0);
  lcd.print(" ");
  lcd.setCursor(0,1);
  lcd.print((char)7);
  lcd.setCursor(1,1);
  lcd.print((char)6);
  lcd.setCursor(2,1);
  lcd.print((char)7);
  delay(1000);
  
  // numero 2
  lcd.setCursor(12,0);
  lcd.print((char)5);
  lcd.setCursor(13,0);
  lcd.print((char)5);
  lcd.setCursor(14,0);
  lcd.print((char)3);
  lcd.setCursor(12,1);
  lcd.print((char)4);
  lcd.setCursor(13,1);
  lcd.print((char)7);
  lcd.setCursor(14,1);
  lcd.print((char)7);
  delay(1000);
  
  // numero 3
  lcd.setCursor(20,0);
  lcd.print((char)5);
  lcd.setCursor(21,0);
  lcd.print((char)5);
  lcd.setCursor(22,0);
  lcd.print((char)3);
  lcd.setCursor(20,1);
  lcd.print((char)7);
  lcd.setCursor(21,1);
  lcd.print((char)7);
  lcd.setCursor(22,1);
  lcd.print((char)2);
  delay(1000);
  
  // numero 4
  lcd.setCursor(4,0);
  lcd.print((char)4);
  lcd.setCursor(5,0);
  lcd.print((char)7);
  lcd.setCursor(6,0);
  lcd.print((char)3);
  lcd.setCursor(4,1);
  lcd.print(" ");
  lcd.setCursor(5,1);
  lcd.print(" ");
  lcd.setCursor(6,1);
  lcd.print((char)6); 
  delay(1000);
  
  // numero 5
  lcd.setCursor(0,0);
  lcd.print((char)1);
  lcd.setCursor(1,0);
  lcd.print((char)5);
  lcd.setCursor(2,0);
  lcd.print((char)5);
  lcd.setCursor(0,1);
  lcd.print((char)7);
  lcd.setCursor(1,1);
  lcd.print((char)7);
  lcd.setCursor(2,1);
  lcd.print((char)2);
  delay(1000);
  
  // numero 6
  lcd.setCursor(0,0);
  lcd.print((char)1);
  lcd.setCursor(1,0);
  lcd.print((char)5);
  lcd.setCursor(2,0);
  lcd.print((char)5);
  lcd.setCursor(0,1);
  lcd.print((char)4);
  lcd.setCursor(1,1);
  lcd.print((char)7);
  lcd.setCursor(2,1);
  lcd.print((char)2);
  delay(1000);
  
  // numero 7
  lcd.setCursor(8,0);
  lcd.print((char)0);
  lcd.setCursor(9,0);
  lcd.print((char)0);
  lcd.setCursor(10,0);
  lcd.print((char)3);
  lcd.setCursor(8,1);
  lcd.print(" ");
  lcd.setCursor(9,1);
  lcd.print(" ");
  lcd.setCursor(10,1);
  lcd.print((char)6);
  delay(1000);
  
 // numero 8
  lcd.setCursor(0,0);
  lcd.print((char)1);
  lcd.setCursor(1,0);
  lcd.print((char)5);
  lcd.setCursor(2,0);
  lcd.print((char)3);
  lcd.setCursor(0,1);
  lcd.print((char)4);
  lcd.setCursor(1,1);
  lcd.print((char)7);
  lcd.setCursor(2,1);
  lcd.print((char)2);
  delay(1000);
  
  // numero 9
  lcd.setCursor(0,0);
  lcd.print((char)1);
  lcd.setCursor(1,0);
  lcd.print((char)5);
  lcd.setCursor(2,0);
  lcd.print((char)3);
  lcd.setCursor(0,1);
  lcd.print((char)7);
  lcd.setCursor(1,1);
  lcd.print((char)7);
  lcd.setCursor(2,1);
  lcd.print((char)2);
  delay(1000);}
