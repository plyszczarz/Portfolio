#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <String.h>

#define CARDS_AMOUNT 5
#define SERVO_PIN 5
#define TIME_OPEN 2000

#define RST_PIN 9 // Podłącz wyjście RST do D9
#define SS_PIN 10 // Podłącz wyjście SDA do D10

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo lock;

String password_array[CARDS_AMOUNT];
int free_slots[CARDS_AMOUNT];

void menu_display(){
    lcd.print("Admin card");
    Serial.println("Welcome admin");
    Serial.println("a - add new card");
    Serial.println("d - delete existing card");
    Serial.println("s - display numbers of saved cards");
    Serial.println("n - display your card number");
}

int count_slots(){
    int empty_slot_counter = 0;
    int x = 0;
    for (int i = 1; i < CARDS_AMOUNT; i++){
        if (password_array[i].length() == 0){
            empty_slot_counter++;
            free_slots[x] = i;
            x++;
        }
    }
    return empty_slot_counter;
}

bool is_there_spot_like_this(char choice){
    for (int i = 0; i < CARDS_AMOUNT; i++){
        if (free_slots[i] == atoi(choice)){
            return true;
        }
    }
    return false;
}

bool check_door_access(String content){
    for(int i=0; i< CARDS_AMOUNT; i++){
        if(password_array[i] == content)
            return true;
    }
    return false;
}

void AdminInterface(){
    char option;
    int slots = 0;
    char choice;
    Serial.flush();
    bool cardIsPassed = false;

    while (Serial.available() == 0){}

    option = Serial.read();
    Serial.println(option);

    if (option == 'a'){
        switch (option){
        case 'a':
            Serial.println("");
            slots = count_slots();

            if (slots > 0){
                Serial.println("Add card: ");
                int isCardAddedRight = 0;

                while (isCardAddedRight == 0){
                    Serial.println("Free slots:");
                    for (int i = 0; i < (sizeof(free_slots) / sizeof(free_slots[0]))-1; i++){
                        Serial.print(free_slots[i]);
                        Serial.print(", ");
                    }
                    Serial.println("");

                Serial.print("Pick a slot: ");
                while (Serial.available() == 0){}
                choice = Serial.read();

                if (!is_there_spot_like_this(choice)){
                    Serial.println("Wrong choice!!!");
                }
                else{
                    Serial.println(choice);

                    while (!cardIsPassed){
                        // if (mfrc522.PICC_IsNewCardPresent())
                        if(1){
                            //if (mfrc522.PICC_ReadCardSerial())
                            if(1){
                                Serial.println("UID tag :");
                                String content = "";
                                byte option;
                                for (byte i = 0; i < mfrc522.uid.size; i++){
                                    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                                    Serial.print(mfrc522.uid.uidByte[i], HEX);
                                    if (i == 0){
                                        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
                                        content.concat(String(mfrc522.uid.uidByte[i], HEX));
                                    }
                                    else{
                                        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
                                        content.concat(String(mfrc522.uid.uidByte[i], HEX));
                                    }
                                }
                                Serial.println();
                                Serial.print("Message : ");
                                content.toUpperCase();
                                password_array[choice] = content;
                                cardIsPassed = true;
                            }
                        }
                    }
                }
                isCardAddedRight = 1;
            }
            }
            break;

        case 'd':
            Serial.println("Choose which password you want to delete");
            for (int passNum = 1; passNum < (sizeof(password_array) / sizeof(password_array[0])); passNum++){
                if (password_array[passNum] != ""){
                    Serial.print("You can delete number");
                    Serial.println(passNum);
                    Serial.println(password_array[passNum]);
                }
            }
            break;

        case 's':
            int help = count_slots();

            Serial.println("Saved cards passwords:");
            for (int i = 0; i < (CARDS_AMOUNT - help); i++){
                Serial.println(password_array[i]);
            }
            break;

        case 'n':
            if (mfrc522.PICC_IsNewCardPresent()){
                if (mfrc522.PICC_ReadCardSerial()){
                    Serial.println("UID tag :");
                    String content = "";
                    byte option;
                    for (byte i = 0; i < mfrc522.uid.size; i++){
                        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                        Serial.print(mfrc522.uid.uidByte[i], HEX);
                        if (i == 0){
                            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
                            content.concat(String(mfrc522.uid.uidByte[i], HEX));
                        }
                        else{
                            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
                            content.concat(String(mfrc522.uid.uidByte[i], HEX));
                        }
                    }
                    Serial.println();
                    Serial.print("Message : ");
                    content.toUpperCase();
                    Serial.println(content);
                }
            }
            break;

        default:
            Serial.println("its not on the list, bye");
            break;
        }
    }
}

void openLock(){
    lock.write(180);
    delay(TIME_OPEN);
    lock.write(0);
}

void Proceed()
{
    String content = "";
    if (mfrc522.PICC_IsNewCardPresent()){
        if (mfrc522.PICC_ReadCardSerial()){
            lcd.clear();
            Serial.println("UID tag :");
            //String content = "";
            byte letter;
            for (byte i = 0; i < mfrc522.uid.size; i++){
                Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522.uid.uidByte[i], HEX);
                content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
                content.concat(String(mfrc522.uid.uidByte[i], HEX));
            }
            Serial.println();
            Serial.print("Message : ");
            content.toUpperCase();
        }

        if (content == password_array[0]){
            lcd.print("ADMIN");
            menu_display();
            AdminInterface();
        }

        if(check_door_access(content)){
            openLock();
        }
        else{
            lcd.print("Acces denied");
            Serial.println("Acces denied");
        }
    }
}

void setup(){
    password_array[0] = "77 A2 81 B5";
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);

    Serial.begin(9600);
    Serial.println("Welcome");
    
    SPI.begin();
    mfrc522.PCD_Init();

    lock.attach(SERVO_PIN);
    lock.write(0);
}

void loop(){
    //menu_display();
    //AdminInterface();
    openLock();
    Proceed();
}