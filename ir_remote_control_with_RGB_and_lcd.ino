#include <IRremote.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;


int red_light_pin= 5;
int green_light_pin = 10;
int blue_light_pin = 9;

int red=0;
int green=0;
int blue=0;



unsigned long key_value = 0;


void setup(){ 
  Serial.begin(9600);

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  RGB_color(0,0,0);
  
  lcd.begin(16, 2); // initialize the lcd
  lcd.clear();
  lcd.setBacklight(255);
  lcd.print("Customize ur RGB!");
 
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){

   if (irrecv.decode(&results)){

         int prev_red = red;
         int prev_green = green;
         int prev_blue = blue;
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFFA25D:
          Serial.println("CH-");
          red = red - 10;
          break;
          case 0xFF629D:
          Serial.println("CH");
          red = red + 10;
          break;
          case 0xFFE21D:
          Serial.println("CH+");
          red=0;green=0;blue=0; 
          break;
          case 0xFF22DD:
          Serial.println("|<<");
          green = green - 10;
          break;
          case 0xFF02FD:
          Serial.println(">>|");
          green = green + 10;
          break ;  
          case 0xFFC23D:
          Serial.println(">|");
          red=255;green=255;blue=255; 
          break ;               
          case 0xFFE01F:
          blue = blue - 10;
          Serial.println("-");
          break ;  
          case 0xFFA857:
          blue = blue + 10;
          Serial.println("+");
          break ;  
          case 0xFF906F:
          red=127;green=127;blue=127; 
          Serial.println("EQ");
          break ;  
          case 0xFF6897:
          Serial.println("0");
          red=255;green=0;blue=0; 
          break ;  
          case 0xFF9867:
          Serial.println("100+");
          red=red +100;green=green +100;blue=blue +100; 
          break ;
          case 0xFFB04F:
          Serial.println("200+");
          red=red +200;green=green +200;blue=blue +200; 
          break ;
          case 0xFF30CF:
          Serial.println("1");
          red=0;green=255;blue=0; 
          break ;
          case 0xFF18E7:
          Serial.println("2");
          red=0;green=0;blue=255; 
          break ;
          case 0xFF7A85:
          Serial.println("3");
           red=255;green=255;blue=0; 
          break ;
          case 0xFF10EF:
          Serial.println("4");
          red=0;green=255;blue=255; 
          break ;
          case 0xFF38C7:
          Serial.println("5");
          red=255;green=0;blue=255; 
          break ;
          case 0xFF5AA5:
          Serial.println("6");
          red=100;green=150;blue=200; 
          break ;
          case 0xFF42BD:
          Serial.println("7");
          red=200;green=150;blue=100; 
          break ;
          case 0xFF4AB5:
          Serial.println("8");
          red=20;green=40;blue=60; 
          break ;
          case 0xFF52AD:
          Serial.println("9");
          red=90;green=45;blue=15; 
          break ;      
        }
        key_value = results.value;
        irrecv.resume(); 

        if(red>255 || red<0){
          red = prev_red;
        }
        if(green>255 || green<0){
          green = prev_green;
        }
        if(blue>255 || blue<0){
          blue = prev_blue;
        }
    
        lcd.clear();
        lcd.print("   R:"+ String(red) + "  G:"+ String(green));
        lcd.setCursor(0,1);
        lcd.print("      B:"+ String(blue)); 
        RGB_color(red,green,blue);
  }

}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
