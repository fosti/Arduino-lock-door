/*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9
#define led 8

RFID rfid(SS_PIN,RST_PIN);
int serNum[5];
int cards[][5] = {
  {5,117,21,219,190},{131,16,185,69,111},{144,217,135,53,251},{48,219,135,53,89},{21,74,79,230,246},{64,69,225,16,244},{96,218,135,53,8},{94,191,93,89,229},{169,50,201,35,113}
,{169,50,201,35,113}};
bool access = false;

void setup(){
    Serial.begin(9600);
    SPI.begin();
    rfid.init();
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH);   
}

void loop(){
    if(rfid.isCard()){    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
           
        }
        
       if(access){
          Serial.println("Welcome!");
           digitalWrite(led, LOW); 
           delay(2000);
      } else {
           Serial.println("Not allowed!"); 
           digitalWrite(led, HIGH); 
           delay(500);
       }        
    }
    else {
      Serial.println("no card");
      delay(500);
      digitalWrite(led, HIGH);
    }
    
    rfid.halt();

}
