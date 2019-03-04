//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//#include <LiquidCrystalFast.h> // Utilizar com LCD 40X4
//LiquidCrystalFast lcd(10 , 11, 7 , 8 , 6 , 5 , 4 , 3);
                 //   RS   RW  E1  E2  D4  D5  D6  D7
                    
byte SETA_DIREITA[8] = {
B01000,
B01100,
B01110,
B01111,
B01110,
B01100,
B01000,
B00000 };

byte SETA_ESQUERDA[8] = {
B00010,
B00110,
B01110,
B11110,
B01110,
B00110,
B00010,
B00000 };

int ADC_TECLADO = 0x00;

int col = 7;
int lin = 0;

int posicao = 1;

int ppm     = 0;
int ganho   = 0;
int squelch = 0;
int width   = 5;

int step_geral = 1;

boolean direita  = 0x00, but_1 = 0x0,
        mais     = 0x00, but_2 = 0x0,
        menos    = 0x00, but_3 = 0x0,
        esquerda = 0x00, but_4 = 0x0,       
        enter    = 0x00, but_5 = 0x0;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       

void setup()
{ Serial.begin(9600);

  lcd.begin(16,2);  
  lcd.createChar(0, SETA_DIREITA);  
  lcd.createChar(1, SETA_ESQUERDA);  
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Iniciando");
  delay(500);
  
  lcd.setCursor(0,0);
  lcd.print("Iniciando.      ");
  delay(500);
  
  lcd.setCursor(0,0);
  lcd.print("Iniciando..     ");
  delay(500);
  
  lcd.setCursor(0,0);
  lcd.print("Iniciando...    ");
  delay(1500);
  
  lcd.clear();  
  lcd.setCursor(0,0);
  lcd.print("RECEPTOR SDR-RTL");
  lcd.setCursor(0,1);
  lcd.print("by ALVARO JUNIOR");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("000.000 000 G:00");
  lcd.setCursor(0,1);
  lcd.print("SdB:0   W:005  1"); 

  lcd.setCursor(7,0);  // SELETOR
  lcd.print((char)0); }
  
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 

void loop()
{ keyboardRead();
   
  int Knob_MHZ = analogRead(A4);
  int Knob_KHZ = analogRead(A5);
  
  int freq_MHZ = map(Knob_MHZ,0,1023,80,200);
  int freq_KHZ = map(Knob_KHZ,0,1023, 0,999);
  
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

  Serial.print("FRE:");  
  Serial.println((freq_MHZ * 1000000L) + (freq_KHZ * 1000L));
  delay(120);
  
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  
  if ( freq_MHZ < 100 ) 
  {  lcd.setCursor(0,0);
     lcd.print(" ");
     lcd.setCursor(1,0);
     lcd.print(freq_MHZ); }
  
  if ( freq_MHZ >= 100 ) 
  {  lcd.setCursor(0,0);
     lcd.print(freq_MHZ); } 
     
//**************************************** 

  if ( freq_KHZ < 10 ) 
  {  lcd.setCursor(4,0);
     lcd.print("00");
     lcd.setCursor(6,0);
     lcd.print(freq_KHZ); } 
     
  if ( freq_KHZ >= 10 && freq_KHZ < 100 ) 
  {  lcd.setCursor(4,0);
     lcd.print("0");
     lcd.setCursor(5,0);
     lcd.print(freq_KHZ); }
     
  if ( freq_KHZ >= 100 ) 
  {  lcd.setCursor(4,0);
     lcd.print(freq_KHZ); }
     
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  
  if ( direita == 0x01 )
  {    direita = 0x00;
       Serial.print("FRE:");  
       Serial.println((freq_MHZ * 1000000L) + (freq_KHZ * 1000L));
       delay(120); }
       //Serial.println("UNLK"); 
       //delay(120); } 
       
//====================================================================       
// STEP 1 - 5 - 1- 15 - 20
//====================================================================       
  if ( esquerda == 0x01 )
  {    esquerda =  0x00;
          
       if ( step_geral == 1 )  
       {    step_geral = 5;
            lcd.setCursor(15,1);
            lcd.print(5);
            lcd.setCursor(14,1);
            lcd.print(" ");

            ganho   = 0;

            Serial.print("GRF:");
            Serial.println(ganho);  
            lcd.setCursor(14,0);
            lcd.print("00"); }
            
       else if ( step_geral == 5 )  
       {    step_geral = 10;
            lcd.setCursor(14,1);
            lcd.print(10); 

            ganho   = 0;

            Serial.print("GRF:");
            Serial.println(ganho);  
            lcd.setCursor(14,0);
            lcd.print("00"); }
            
       else if ( step_geral == 10 )  
       {    step_geral = 15;
            lcd.setCursor(14,1);
            lcd.print(15);     

            ganho   = 0;

            Serial.print("GRF:");
            Serial.println(ganho);   
            lcd.setCursor(14,0);
            lcd.print("00"); }            
     
       else if ( step_geral == 15 )  
       {    step_geral = 20;
            lcd.setCursor(14,1);
            lcd.print(20); 

            ganho   = 0;

            Serial.print("GRF:");
            Serial.println(ganho);   
            lcd.setCursor(14,0);
            lcd.print("00"); }      
       
       else if ( step_geral == 20 )  
       {    step_geral = 1;
            lcd.setCursor(15,1);
            lcd.print(1);
            lcd.setCursor(14,1);
            lcd.print(" "); 
            Serial.print("GRF:");
            Serial.println(ganho);   }         
  }    
//====================================================================
//====================================================================
// SETUP'S GERAIS + + + + + + + + + + + + + + + + + + + + + + + + + +
//====================================================================
//====================================================================
  if ( mais == 0x01 )
  
  {    mais =  0x00;
       //==================================================
       // AJUSTE PPM + + + + + + + +
       //==================================================
       if ( posicao == 1 )
       {
       if ( ppm == 995 ) ppm = -5;
            
            ppm = ppm + 5;
            Serial.print("PPM:"); 
            Serial.println(ppm); 
            
       if ( ppm < 10 )
       {    lcd.setCursor(8,0);
            lcd.print("00");
            lcd.setCursor(10,0);
            lcd.print(ppm); } 
            
       if ( ppm >= 10 && ppm < 100)
       {    lcd.setCursor(8,0);
            lcd.print("0");
            lcd.setCursor(9,0);
            lcd.print(ppm); }   
            
       if ( ppm >= 100 )
       {    lcd.setCursor(8,0);
            lcd.print(ppm); }  
       }
       //==================================================
       // AJUSTE GANHO + + + + + + +
       //==================================================      
       if ( posicao == 2 )
       {

       if ( ganho == 99 && step_geral == 1  ) ganho = -1;
       if ( ganho == 95 && step_geral == 5  ) ganho = -5;
       if ( ganho == 90 && step_geral == 10 ) ganho = -10;
       if ( ganho == 90 && step_geral == 15 ) ganho = -15;
       if ( ganho == 80 && step_geral == 20 ) ganho = -20;
       
            ganho = ganho + step_geral;
            Serial.print("GRF:");
            Serial.println(ganho); 
            
       if ( ganho < 10 )
       {    lcd.setCursor(14,0);
            lcd.print("0");
            lcd.setCursor(15,0);
            lcd.print(ganho); }  
            
       if ( ganho >= 10 && ganho < 100)
       {    lcd.setCursor(14,0);
            lcd.print(ganho); }          
       }       
       //==================================================
       // AJUSTE SQUELCH + + + + + +
       //==================================================
       if ( posicao == 3 )
       {
       if ( squelch == 99 ) squelch = -1;
            
            squelch = squelch + 1; 
            Serial.print("SQL:");
            Serial.println(squelch); 
            
       if ( squelch < 0 && squelch >-10 )
       {    lcd.setCursor(4,1);
            lcd.print(squelch); 
            lcd.setCursor(6,1);
            lcd.print(" "); }

       if ( squelch <= -10 )
       {    lcd.setCursor(4,1);
            lcd.print(squelch); }
            
       if ( squelch == 0 )
       {    lcd.setCursor(4,1);
            lcd.print(squelch);
            lcd.setCursor(5,1);
            lcd.print("  "); }
            
       if ( squelch > 0 )
       {    lcd.setCursor(4,1);
            lcd.print("+");  
            lcd.setCursor(5,1);
            lcd.print(squelch); }      
       } 
       //==================================================
       // AJUSTE WIDTH  + + + + + + + + + + + + + + + + + 
       //==================================================
       if ( posicao == 4 )
       {
       if ( width == 995 ) width = 0;
            
            width = width + 5;
            Serial.print("WDT:"); 
            Serial.println(width * 10000L); 
            
       if ( width < 10 )
       {    lcd.setCursor(10,1);
            lcd.print("00");
            lcd.setCursor(12,1);
            lcd.print(width); } 
            
       if ( width >= 10 && width < 100)
       {    lcd.setCursor(10,1);
            lcd.print("0");
            lcd.setCursor(11,1);
            lcd.print(width); }   
            
       if ( width >= 100 )
       {    lcd.setCursor(10,1);
            lcd.print(width); }  
       }
       
       delay(120);
  }
//====================================================================       
//====================================================================
// SETUP'S GERAIS - - - - - - - - - - - - - - - - - - - - - - - - - - 
//====================================================================
//====================================================================
  if ( menos == 0x01 )
  {    menos =  0x00;
       //==================================================
       // AJUSTE PPM  - - - - - - - 
       //==================================================
       if ( posicao == 1 )
       {
       if ( ppm == 0 ) ppm = 1000;      
            
            ppm = ppm - 5;
            Serial.print("PPM:"); 
            Serial.println(ppm); 
            
       if ( ppm < 10 )
       {    lcd.setCursor(8,0);
            lcd.print("00");
            lcd.setCursor(10,0);
            lcd.print(ppm); }     
            
       if ( ppm >= 10 && ppm < 100)
       {    lcd.setCursor(8,0);
            lcd.print("0");
            lcd.setCursor(9,0);
            lcd.print(ppm); }     
            
       if ( ppm >= 100 )
       {    lcd.setCursor(8,0);
            lcd.print(ppm); }  
       }
     
       //==================================================
       // AJUSTE GANHO  - - - - - - 
       //==================================================     
       if ( posicao == 2 )
       {
      
       if ( ganho == 0 && step_geral == 1  ) ganho = 100;
       if ( ganho == 0 && step_geral == 5  ) ganho = 100;
       if ( ganho == 0 && step_geral == 10 ) ganho = 100;
       if ( ganho == 0 && step_geral == 15 ) ganho = 105;
       if ( ganho == 0 && step_geral == 20 ) ganho = 100;
            
            ganho = ganho - step_geral;
            Serial.print("GRF:");
            Serial.println(ganho); 
            
       if ( ganho < 10 )
       {    lcd.setCursor(14,0);
            lcd.print("0");
            lcd.setCursor(15,0);
            lcd.print(ganho); }       
            
       if ( ganho >= 10 && ganho < 100)
       {    lcd.setCursor(14,0);
            lcd.print(ganho); }          
       }    
       //==================================================
       // AJUSTE SQUELCH  - - - - - 
       //==================================================
       if ( posicao == 3 )
       {
       if ( squelch == -99 ) squelch = 1;
            
            squelch = squelch - 1;            
            Serial.print("SQL:");
            Serial.println(squelch); 
            
       if ( squelch >= 10 && squelch < 100 )
       {    lcd.setCursor(4,1);
            lcd.print("+");
            lcd.setCursor(5,1);
            lcd.print(squelch); }  
            
       if ( squelch > 0 && squelch < 10 )
       {    lcd.setCursor(4,1);
            lcd.print("+");
            lcd.setCursor(6,1);
            lcd.print(" ");    
            lcd.setCursor(5,1);
            lcd.print(squelch); }  
            
       if ( squelch == 0 )
       {    lcd.setCursor(4,1);
            lcd.print(squelch);  
            lcd.setCursor(5,1);
            lcd.print("  "); }      
            
       if ( squelch < 0 )
       {    lcd.setCursor(4,1);
            lcd.print(squelch); }
       }
       //==================================================
       // AJUSTE WIDTH  - - - - - - - - - - - - - - - - - 
       //==================================================
       if ( posicao == 4 )
       {
       if ( width == 5 ) width = 1000;      
            
            width = width - 5;
            Serial.print("WDT:");
            Serial.println(width * 10000L); 
            
       if ( width < 10 )
       {    lcd.setCursor(10,1);
            lcd.print("00");
            lcd.setCursor(12,1);
            lcd.print(width); }     
            
       if ( width >= 10 && width < 100)
       {    lcd.setCursor(10,1);
            lcd.print("0");
            lcd.setCursor(11,1);
            lcd.print(width); }     
            
       if ( width >= 100 )
       {    lcd.setCursor(10,1);
            lcd.print(width); }  
       }   
     
       delay(120);
  }
//=====================================================================       
// SELETOR DE POSICAO DO CURSOR
//=====================================================================      
  if ( enter == 0x01 )
  {    enter =  0x00;
       
       if ( posicao == 1 )       // inicio ppm
       {    posicao = 2;
            lcd.setCursor(11,0);
            lcd.print((char)0);
            lcd.setCursor(7,0);
            lcd.print(" "); }
      
       else if ( posicao == 2 )  // ganho
       {    posicao = 3;
            lcd.setCursor(11,0);
            lcd.print(" ");
            lcd.setCursor(7,1);
            lcd.print((char)1); }
            
       else if ( posicao == 3 )  // squelch
       {    posicao = 4;
            lcd.setCursor(7,1);
            lcd.print(" ");
            lcd.setCursor(13,1);
            lcd.print((char)1); }
          
       else if ( posicao == 4 )  // width
       {    posicao = 1;
            lcd.setCursor(13,1);
            lcd.print(" ");
            lcd.setCursor(7,0);
            lcd.print((char)0); }
       
       delay(120);
   }
       //Serial.println("STOP");   
       //delay(120);
}
//====================================================================       
// LEITURA DO TECLADO ANALOGICO
//====================================================================
void keyboardRead()
{   
     ADC_TECLADO = analogRead(A0);
     
     if      ( ADC_TECLADO < 50 )                        but_1 = 0x01;
     else if ( ADC_TECLADO > 50 &&  ADC_TECLADO < 150 )  but_2 = 0x01;
     else if ( ADC_TECLADO > 200 && ADC_TECLADO < 300 )  but_3 = 0x01;   
     else if ( ADC_TECLADO > 350 && ADC_TECLADO < 450 )  but_4 = 0x01; 
     else if ( ADC_TECLADO > 500 && ADC_TECLADO < 700 )  but_5 = 0x01; 
     
     if ( ADC_TECLADO > 50 && but_1 )
     {    but_1   = 0x00;
          direita = 0x01;
          //Serial.println(ADC_TECLADO); 
     } 
 
     if ( ADC_TECLADO > 450 && but_4 )
     {    but_4    = 0x00;
          esquerda = 0x01;
          //Serial.println(ADC_TECLADO);
     } 
        
     if ( ADC_TECLADO > 150 && but_2 )
     {    but_2   = 0x00;
          mais    = 0x01;
          //Serial.println(ADC_TECLADO);
     }  
        
     if ( ADC_TECLADO > 300 && but_3 )
     {    but_3   = 0x00;
          menos   = 0x01;
          //Serial.println(ADC_TECLADO);
     }   
          
     if ( ADC_TECLADO > 700 && but_5 )
     {    but_5    = 0x00;
          enter    = 0x01;
          //Serial.println(ADC_TECLADO); 
     } 
}        
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

