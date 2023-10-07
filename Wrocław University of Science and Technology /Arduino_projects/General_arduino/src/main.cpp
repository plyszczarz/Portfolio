#include <Arduino.h>

int wypelnienie_niebieskie = 0, wypelnienie_zielone=255, wypelnienie_czerwone=255, interwal = 5;
unsigned int time = 0, time_interval = 10;
int counter =255;


void setup() {
    Serial.begin(9600);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    time = millis();
}

void loop() {
    if(wypelnienie_czerwone <= 255 && wypelnienie_czerwone != 0 && wypelnienie_niebieskie >= 0 && wypelnienie_niebieskie != 255 && wypelnienie_zielone == 255 && millis() > (time+time_interval)){
        wypelnienie_czerwone -= interwal;
        wypelnienie_niebieskie += interwal;
        time = millis();
    }

    if(wypelnienie_czerwone >= 0 && wypelnienie_czerwone !=255 && wypelnienie_niebieskie == 255 && wypelnienie_zielone <= 255 && wypelnienie_zielone != 0 && millis() > (time+time_interval)){
        wypelnienie_czerwone += interwal;
        wypelnienie_zielone -= interwal;
        time = millis();
    }

    if(wypelnienie_czerwone == 255 && wypelnienie_niebieskie <= 255 && wypelnienie_niebieskie != 0 && wypelnienie_zielone >= 0 && wypelnienie_zielone != 255 && millis() > (time+time_interval)){
        wypelnienie_niebieskie -= interwal;
        wypelnienie_zielone += interwal;
        time = millis();
    }

    analogWrite(9, wypelnienie_niebieskie); 
    analogWrite(10, wypelnienie_zielone); 
    analogWrite(11, wypelnienie_czerwone); 
}