#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>


char myKeys[] = {'2','7','9','0','2','7','8','1'};
char  uKeys[] = {'0','0','0','0','0','0','0','0'};
char  sKeys[8] = {'*','*','*','*','*','*','*','*'};
int rPins[4] = {3,4,5,6};
int cPins[4] = {7,8,9,10};
int rStates[4] = {};
int relay = 12;
char keyList1[4] = {'1', '2','3', 'A'};
char keyList2[4] = {'4', '5','6', 'B'};
char keyList3[4] = {'7', '8','9', 'C'};
char keyList4[4] = {'*', '0', '#', 'D'};
char keypressed;
int disp = -1;
char sign = '*';
char stablizer;
char myKeycomb;
char uKeycomb;
int counting;
String header = "Passkey:";
LiquidCrystal_I2C lcd(0x27, 16,2);
const int eMadd = 0;
char getKeys[8];

void setup(){
    pinMode(rPins[0], INPUT_PULLUP);
    pinMode(rPins[1], INPUT_PULLUP);
    pinMode(rPins[2], INPUT_PULLUP);
    pinMode(rPins[3], INPUT_PULLUP);
    pinMode(cPins[0], OUTPUT);
    pinMode(cPins[1], OUTPUT);
    pinMode(cPins[2], OUTPUT);
    pinMode(cPins[3], OUTPUT);
    pinMode(relay, OUTPUT);
    lcd.init();
    lcd.clear();
    lcd.backlight();
    //memWrite();
    
}


void memWrite(){
    EEPROM.put(eMadd, myKeys);
    
}


void memRead(){
    EEPROM.get(eMadd, getKeys);
    
}


void position(){
    delay(400);
    disp++;
}


void clr(){
    
    lcd.clear();
    disp = -1 ;
    keypressed = ' ';
    for (int k = 0; k <= 7; k++){
    uKeys[k] = '0';
        }
    
    
}


void confirm(){
    memRead();
    if(getKeys[0]+ getKeys[1]+getKeys[2]+ getKeys[3]+getKeys[4]+ getKeys[5] +getKeys[6]+ getKeys[7] == uKeys[0]+ uKeys[1]+uKeys[2]+ uKeys[3]+uKeys[4]+ uKeys[5] +uKeys[6]+ uKeys[7]){
        
        if(header == "Passkey:"){
        lcd.setCursor(0,1);
        lcd.print("Welcome!");
        digitalWrite(relay, HIGH);
        delay(5000);  
        digitalWrite(relay, LOW);
        lcd.setCursor(0,1);
        lcd.print("Locked!!");
        delay(500);
        clr();
            }
        
      else if(header == "Old Passkey:"){
            clr();
            header = "New Passkey:";
        
             }
 
        }
        
    
   else if(header == "New Passkey:"){
        for(int nKey =0; nKey<=7; nKey++){
            myKeys[nKey] = uKeys[nKey];
        }
      memWrite();
      lcd.setCursor(0,1);
      lcd.print("Changed!");
      delay(600);
      clr();
      header = "Passkey:";
   }
    
    
      
   else{
     lcd.setCursor(0,1);
     lcd.print("Denied!!");
     delay(500);
     clr();
        }
        
}

void headings(){
    lcd.setCursor(0,0);
    lcd.print(header);
}



void changeP(){
    clr();
    header = "Old Passkey:"; 
    
}




void keyEntry(){
    
    for(int j = 0; j<=7; j++){
        
        if (disp == j){
            uKeys[j] = keypressed;
            lcd.setCursor(disp, 1);
            lcd.print(sKeys[j]);
            //delay(100);
            //lcd.setCursor(disp, 1);
            //stablizer = sKeys[disp];
            //lcd.print(stablizer);
    
            
                      }                           
        
         }   
     
    
    }


void visibility(){
  
  if(sign = '*'){
    for(int vKey =0; vKey<=disp; vKey++){
        lcd.setCursor(vKey, 1);
        lcd.print(uKeys[vKey]);
        } 
    sign='+';
        }
        
    
  else if(sign = '+'){
    for(int vKey =0; vKey<=disp; vKey++){
        lcd.setCursor(vKey, 1);
        lcd.print(sKeys[vKey]);

          }
        
    sign='*';
          }
    
        
        
    }



void keypad(){
    
    digitalWrite(relay, LOW);
    digitalWrite(cPins[0], HIGH);
    digitalWrite(cPins[1], HIGH);
    digitalWrite(cPins[2], HIGH);
    digitalWrite(cPins[3], HIGH);
    
    
    for(int i =0; i < 4; i++){
    digitalWrite(cPins[i], LOW);
 
    rStates[0] = digitalRead(rPins[0]);
    rStates[1] = digitalRead(rPins[1]);
    rStates[2] = digitalRead(rPins[2]);
    rStates[3] = digitalRead(rPins[3]);
    
    if(rStates[0] == 0){
         if(i == 3){
                changeP();
            }
            
         else{
            keypressed = keyList1[i];
            position();
                
            }
            
              }
        
        
    else if(rStates[1] ==0){
            
         if(i==3){
                clr();
              header = "Passkey:";
                }
         else{
            keypressed = keyList2[i];
            position();            
                    }                  
            
    }
                
    
    else if(rStates[2] == 0){
           
        if(i == 3){
          clr();      
                  }
            
         else{
        keypressed = keyList3[i];
        position();
             }    
                            }
        
    
    else if(rStates[3] == 0){
            
         if(i==0){
              visibility();
            }
            
         else if(i==1){
              keypressed = ('0');
              position();
              }
            
            
         else if(i ==2){
                confirm();
            }
            
          else if(i ==3){
         lcd.setCursor(disp, 1);
         lcd.print(' ');
         keypressed = uKeys[disp-1];
         disp --;
         delay(400);

            }
            
            
            
         
                            }
    
    else{
        
        
    }
    
    
 }  

    
}


void loop(){
    
headings();  
keypad();   
keyEntry();
     
     
        
}