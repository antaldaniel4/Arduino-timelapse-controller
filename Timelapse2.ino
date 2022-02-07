#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);
byte myArray[] = {3, 5, 10, 20, 40};
byte interval = 0;
int  count = 0;
boolean setreset = false;
int perform = 0;


void setup() {
 lcd.begin(16, 2);
pinMode(1, INPUT);    //mode
pinMode(3, INPUT);    //start-reset
pinMode(5, OUTPUT);   //Fókusz
pinMode(4, OUTPUT);   //Exponál
 Serial.begin(9600); 
}

void loop() {

   while(1)
    { count = 0;
      
      if (digitalRead(1) == HIGH)
           interval ++ ;
           delay(600);
          if (interval >= 5)                   // fényképezési intervallum megválasztás(tömbböl)
              interval = 0;
        lcd.setCursor(0, 0);     
        lcd.print("Interval:");
        lcd.setCursor(9, 0);
        lcd.print("   ");  
        lcd.setCursor(9, 0);
        lcd.print(myArray[interval]);        //kiiratom az intervallumot

     if (digitalRead(3) == HIGH)                //program elindítása
     {      
           setreset = !setreset;   
              delay(100);
                perform = myArray[interval]*10;   //Feltöltöm a számláló értékével hogy startkor elsüljön
                count = 0;

                while(setreset)
                {                  
                  if (myArray[interval]*10 == perform) 
                       { digitalWrite(4, HIGH);         //gép exponálása
                          delay(500);
                         digitalWrite(5, HIGH);
                          count++;

                          lcd.setCursor(0, 1);
                          lcd.print("Expo:");
                          lcd.setCursor(5, 1);
                          lcd.print("      ");
                          lcd.setCursor(5, 1);
                          lcd.print(count);
                          delay(300);
                          digitalWrite(4, LOW);
                          digitalWrite(5, LOW);
                          perform = 0;
                       }

                           else { 
                                delay(500);
                                    if (digitalRead(3) == HIGH)       //Start Leállítás vizsgálata
                                       { delay(100);
                                        setreset = 0;}
                                        else
                                        {  perform = perform + 5;
                                        }

                                                               
                                }
                }
     } 
    }
    

}
