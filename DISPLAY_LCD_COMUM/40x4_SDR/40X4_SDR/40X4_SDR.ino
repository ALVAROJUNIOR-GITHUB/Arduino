#include <LiquidCrystalFast.h>

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  

#include <Wire.h>


//LiquidCrystalFast lcd(12, 11, 10, 9, 5, 4, 3, 2);
         // LCD pins: RS  RW  E1 E2  D4 D5 D6 D7
LiquidCrystalFast lcd(10, 11, 7, 8, 6, 5, 4, 3);
         // LCD pins: RS  RW  E1 E2  D4 D5 D6 D7
         
byte aut_1[8] = {
B00001,
B00011,
B11111,
B11111,
B11111,
B00011,
B00001,
B00000 };

byte aut_2[8] = {
B00010,
B01001,
B00101,
B10101,
B00101,
B01001,
B00010,
B00000 };

byte seta[8] = {
B10000,
B11000,
B11100,
B11110,
B11100,
B11000,
B10000,
B00000 };

byte erro[8] = {
B11111,
B10001,
B10111,
B10001,
B10111,
B10001,
B11111,
B00000 };

byte barra[8] = {
B01110,
B01110,
B01110,
B01110,
B01110,
B01110,
B01110,
B01110 };

byte db[8] = {
B11111,
B11101,
B11101,
B10001,
B10101,
B10001,
B11111,
B00000 };

byte quilo[8] = {
B11111,
B10101,
B10101,
B10011,
B10101,
B10101,
B11111,
B00000 };

byte seletor[8] = {
B01110,
B01010,
B01010,
B11011,
B01010,
B01010,
B01110,
B00000 };

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 
void setup()
{ 
  Serial.begin(9600);
  
  lcd.begin(40,4);

  
  lcd.createChar(0,   aut_1);  
  lcd.createChar(1,   aut_2);  
  lcd.createChar(2,    seta);  
  lcd.createChar(3,    erro);  
  lcd.createChar(4,   barra);  
  lcd.createChar(5,      db);  
  lcd.createChar(6,   quilo);  
  lcd.createChar(7, seletor);
  
  lcd.clear();  
  lcd.setCursor(0,0);
  lcd.print("--------------------");
  lcd.setCursor(0,1);
  lcd.print("  RECEPTOR VER 1.0  ");
  lcd.setCursor(0,2);
  lcd.print("  by ALVARO JUNIOR  ");
  lcd.setCursor(0,3);
  lcd.print("--------------------");
  delay(1500); 

  //--------------------------------
  
  lcd.setCursor(0,0);
        
  lcd.print(" VHF:---.--- SQ:---  UHF:450.000 SQ:-25 ");
  lcd.setCursor(0,1);
  lcd.print("             RF:---              RF:065 ");
  lcd.setCursor(0,2);
  lcd.print("  ---------  WD:---  ----------  WD:550 ");
  lcd.setCursor(0,3);
  lcd.print(" 20% PPM --- CT:100  25% PPM 125 CT:100 "); 

  lcd.setCursor(3,2);  // SELETOR
  lcd.print((char)7);

  lcd.setCursor(25,2);  // SELETOR
  lcd.print((char)7);

  lcd.setCursor(11,2); // AUTO FALANTE 1
  lcd.print((char)0);

  lcd.setCursor(31,2); // AUTO FALANTE 1
  lcd.print((char)0);
  
  lcd.setCursor(0,0); // SETA
  lcd.print((char)2);
 
  //lcd.setCursor(0,3);  // AUTO FALANTE 1
  //lcd.print((char)0);
  
  //lcd.setCursor(1,3);  // AUTO FALANTE 2
  //lcd.print((char)1); 
  
  //lcd.setCursor(7,3);  // ERRO
  //lcd.print((char)3); 

  //lcd.setCursor(19,0); // dB SQL
  //lcd.print((char)5); 
  
  //lcd.setCursor(19,1); // dB RF
  //lcd.print((char)5); 

  //lcd.setCursor(19,2); // KILO WDT
  //lcd.print((char)6); 

  //lcd.setCursor(19,3); // KILO CUT
  //lcd.print((char)6); 
  
  lcd.setCursor(20,0); // BARRA
  lcd.print((char)4);
  lcd.setCursor(20,1);
  lcd.print((char)4);
  lcd.setCursor(20,2);
  lcd.print((char)4);
  lcd.setCursor(20,3);
  lcd.print((char)4);

  lcd.setCursor(39,0); // BARRA
  lcd.print((char)4);
  lcd.setCursor(39,1);
  lcd.print((char)4);
  lcd.setCursor(39,2);
  lcd.print((char)4);
  lcd.setCursor(39,3);
  lcd.print((char)4);
  
  delay(2500);  }
 
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void loop()
{   
  int Knob_MHZ = analogRead(A1); // MHZ
  int Knob_KHZ = analogRead(A0); // KHZ
  int Knob_PPM = analogRead(A2); // PPM
  int Knob_SQL = analogRead(A3); // SQL
  int Knob_GRF = analogRead(A2); // GRF
  int Knob_WDT = analogRead(A3); // WDT
//int Knob_CUT = analogRead(A2); // CUT
//int Knob_VOL = analogRead(A2); // VOL
  int Knob_SLI = analogRead(A7); // SLI
  
  int valor_freq_MHZ = map(Knob_MHZ,0,1023,   80,  200); // 1
  int valor_freq_KHZ = map(Knob_KHZ,0,1023,    0,  999); // 2
  int valor_PPM      = map(Knob_PPM,0,1023, -999,  999); // 3
  int valor_SQL      = map(Knob_SQL,0,1023, -100,  100); // 4
  int valor_GRF      = map(Knob_GRF,0,1023,    0,  100); // 5
  int valor_WDT      = map(Knob_WDT,0,1023,    1, 1000); // 6
//  int valor_CUT      = map(Knob_CUT,0,1023,    0,  500); // 7
//  int valor_VOL      = map(Knob_VOL,0,1023,    0,  100); // 8
  int SLIDER         = map(Knob_SLI,0,1023,    0,  110); // 9
  
  Serial.print("FRE:");  
  Serial.println((valor_freq_MHZ * 1000000L) + (valor_freq_KHZ * 1000L));
  delay(20); 

  Serial.print("PPM:");  
  Serial.println(valor_PPM);
  delay(20); 
  
 // Serial.print("VOL");  
 // Serial.println(valor_VOL);
 // delay(20); 
  
  Serial.print("SQL:");  
  Serial.println(valor_SQL);
  delay(20); 
  
  Serial.print("GRF:");  
  Serial.println(valor_GRF);
  delay(20); 

  Serial.print("WDT:");  
  Serial.println(valor_WDT * 1000L);
  delay(20); 

 // Serial.print("CUT:");  
 // Serial.println(valor_CUT);
 // delay(20); 
  
  //======================================
  // FREQUENCIA MHZ Axxx
  //======================================
  if ( valor_freq_MHZ < 100 ) 
  {  lcd.setCursor(4,0);
     lcd.print(" ");
     lcd.setCursor(5,0);
     lcd.print(valor_freq_MHZ); }
  
  if ( valor_freq_MHZ >= 100 ) 
  {  lcd.setCursor(4,0);
     lcd.print(valor_freq_MHZ); } 
   
   
  //======================================
  // FREQUENCIA KHZ Axxx
  //======================================
  if ( valor_freq_KHZ < 10 ) 
  {  lcd.setCursor(8,0);
     lcd.print("00");
     lcd.setCursor(10,0);
     lcd.print(valor_freq_KHZ); } 
     
  if ( valor_freq_KHZ >= 10 && valor_freq_KHZ < 100 ) 
  {  lcd.setCursor(8,0);
     lcd.print("0");
     lcd.setCursor(9,0);
     lcd.print(valor_freq_KHZ); }
     
  if ( valor_freq_KHZ >= 100 ) 
  {  lcd.setCursor(8,0);
     lcd.print(valor_freq_KHZ); }


  //======================================
  // CUT Axxx
  //======================================
//  if ( valor_CUT < 10 ) 
//  {  lcd.setCursor(16,3);
//     lcd.print("00");
//     lcd.setCursor(18,3);
//     lcd.print(valor_CUT); } 
     
//  if ( valor_CUT >= 10 && valor_CUT < 100 ) 
//  {  lcd.setCursor(16,3);
//     lcd.print("0");
//     lcd.setCursor(17,3);
//     lcd.print(valor_CUT); }
     
//  if ( valor_CUT >= 100 ) 
//  {  lcd.setCursor(16,3);
//     lcd.print(valor_CUT); }


  //======================================
  // GANHO RF Axxx
  //======================================
  if ( valor_GRF < 10 ) 
  {  lcd.setCursor(16,1);
     lcd.print("00");
     lcd.setCursor(18,1);
     lcd.print(valor_GRF); } 
     
  if ( valor_GRF >= 10 && valor_GRF < 100 ) 
  {  lcd.setCursor(16,1);
     lcd.print("0");
     lcd.setCursor(17,1);
     lcd.print(valor_GRF); }
     
  if ( valor_GRF >= 100 ) 
  {  lcd.setCursor(16,1);
     lcd.print(valor_GRF); }


  //======================================
  // WDT Axxx
  //======================================
  if ( valor_WDT < 10 ) 
  {  lcd.setCursor(16,2);
     lcd.print("00");
     lcd.setCursor(18,2);
     lcd.print(valor_WDT);
     lcd.setCursor(19,2);
     //lcd.print((char)6);
   } 
     
  if ( valor_WDT >= 10 && valor_WDT < 100 ) 
  {  lcd.setCursor(16,2);
     lcd.print("0");
     lcd.setCursor(17,2);
     lcd.print(valor_WDT);
     lcd.setCursor(19,2);
     //lcd.print((char)6);
   }
     
  if ( valor_WDT >= 100 && valor_WDT < 1000 ) 
  {  lcd.setCursor(16,2);
     lcd.print(valor_WDT);
     lcd.setCursor(19,2);
     //lcd.print((char)6);
   }
     
  if ( valor_WDT >= 1000 ) 
  {  lcd.setCursor(16,2);
     lcd.print(valor_WDT); }     
     
  //======================================
  // VOLUME Axxx
  //======================================
//  if ( valor_VOL == 0 ) 
// {  lcd.setCursor(0,3);
//     lcd.print("MUTE"); } 
     
//  if ( valor_VOL >= 1 && valor_VOL < 10 ) 
//  {  //lcd.setCursor(0,3);
//     //lcd.print("00");
//     lcd.setCursor(0,3);
//     lcd.print(valor_VOL);     
//     lcd.setCursor(1,3);
//     lcd.print("%  "); } 
     
//  if ( valor_VOL >= 10 && valor_VOL < 100 ) 
//  {  //lcd.setCursor(0,3);
//     //lcd.print("0");
//     lcd.setCursor(0,3);
//     lcd.print(valor_VOL);
//     lcd.setCursor(2,3);
//     lcd.print("% "); }
     
//  if ( valor_VOL >= 100 ) 
// {  lcd.setCursor(0,3);
//     lcd.print(valor_VOL); 
//     lcd.setCursor(3,3);
//     lcd.print("%"); }
  
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  
  if ( SLIDER >= 0 && SLIDER <=10 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(0,2);    
       //lcd.print((char)7); 
     }
  else if ( SLIDER > 10 && SLIDER <=20 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(1,2);     
       //lcd.print((char)7); 
     } 
  else if ( SLIDER > 20 && SLIDER <=30 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(2,2);  
       //lcd.print((char)7);
     }
  else if ( SLIDER > 30 && SLIDER <=40 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(3,2);    
       //lcd.print((char)7);
     }
  else if ( SLIDER > 40 && SLIDER <=50 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(4,2);    
       //lcd.print((char)7); 
     }
  else if ( SLIDER > 50 && SLIDER <=60 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(5,2);   
       //lcd.print((char)7); 
     }
  else if ( SLIDER > 60 && SLIDER <=70 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(6,2);    
       //lcd.print((char)7); 
     }
  else if ( SLIDER > 70 && SLIDER <=80 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(7,2); 
       //lcd.print((char)7);
     }       
  else if ( SLIDER > 80 && SLIDER <=90 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(8,2);  
       //lcd.print((char)7); 
     }
  else if ( SLIDER > 90 && SLIDER <=100 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(9,2);     
       //lcd.print((char)7);
     }
  else if ( SLIDER > 100 && SLIDER <=110 )
  {    lcd.setCursor(0,2);
       lcd.print("-----------");   
       lcd.setCursor(10,2);     
       //lcd.print((char)7);
     }

  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
       
  //======================================
  // SQUELCH Axxx
  //======================================
  if ( valor_SQL <= -100 ) 
  {  lcd.setCursor(16,0);
     lcd.print(valor_SQL); } 
     
  if ( valor_SQL <= -10 && valor_SQL >-100 ) 
  {  lcd.setCursor(19,0); // dB SQL
     //lcd.print((char)5);   
     lcd.setCursor(16,0);
     lcd.print(valor_SQL); } 
     
  if ( valor_SQL < 0 && valor_SQL >-10 ) 
  {  lcd.setCursor(19,0); // dB SQL
     lcd.print((char)5);
     lcd.setCursor(18,0);  
     lcd.print(" ");  
     lcd.setCursor(16,0);
     lcd.print(valor_SQL); }   
    
  if ( valor_SQL == 0 ) 
  {  lcd.setCursor(19,0); // dB SQL
     lcd.print((char)5); 
     lcd.setCursor(17,0);  
     lcd.print("  ");      
     lcd.setCursor(16,0);
     lcd.print(valor_SQL); }   
   
  if ( valor_SQL > 0 && valor_SQL < 10 ) 
  {  lcd.setCursor(19,0); // dB SQL
     lcd.print((char)5); 
     lcd.setCursor(18,0);  
     lcd.print(" "); 
     lcd.setCursor(16,0);
     lcd.print("+");     
     lcd.setCursor(17,0);
     lcd.print(valor_SQL); } 

  if ( valor_SQL >=10 && valor_SQL < 100 ) 
  {  lcd.setCursor(19,0); // dB SQL
     lcd.print((char)5);  
     lcd.setCursor(16,0);
     lcd.print("+");
     lcd.setCursor(17,0);
     lcd.print(valor_SQL); } 

  if ( valor_SQL >= 100 ) 
  {  lcd.setCursor(19,0); // dB SQL
     lcd.print((char)5);  
     lcd.setCursor(16,0);
     lcd.print("+"); 
     lcd.setCursor(17,0);
     lcd.print(valor_SQL); }  
  
  
  //======================================
  // PPM  
  //======================================
  if ( valor_PPM <= -100 ) 
  {  lcd.setCursor(8,3);
     lcd.print(valor_PPM); } 
     
  if ( valor_PPM <= -10 && valor_PPM >-100 ) 
  {  lcd.setCursor(11,3);
     lcd.print(" ");
     lcd.setCursor(8,3);
     lcd.print(valor_PPM); } 
     
  if ( valor_PPM < 0 && valor_PPM >-10 ) 
  {  lcd.setCursor(10,3);
     lcd.print("  ");
     lcd.setCursor(8,3);
     lcd.print(valor_PPM); }   
    
  if ( valor_PPM == 0 ) 
  {  lcd.setCursor(8,3);
     lcd.print(":   ");
     lcd.setCursor(9,3);
     lcd.print(valor_PPM); }   
   
  if ( valor_PPM > 0 && valor_PPM < 10 ) 
  {  lcd.setCursor(8,3);
     lcd.print("+   ");
     lcd.setCursor(9,3);
     lcd.print(valor_PPM); } 

  if ( valor_PPM >=10 && valor_PPM < 100 ) 
  {  lcd.setCursor(8,3);
     lcd.print("+   ");
     lcd.setCursor(9,3);
     lcd.print(valor_PPM); } 

  if ( valor_PPM >= 100 ) 
  {  lcd.setCursor(8,3);
     lcd.print("+   "); 
     lcd.setCursor(9,3);
     lcd.print(valor_PPM); }  
     
  }
