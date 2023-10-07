#ifndef GPS_HH
#define GPS_HH

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <stdint.h>

//w strukturze
//czas, pozcyja, predkosc w sentych czesciach km/h, wysokosc npm w dm, kierunek(16bit zmienna), precyzja_h(16bit zmienna), fix(16bit zmienna)

//minuta to 1,8km

#define GPRMC 4
#define GPGGA 1


class GPS{
enum class BaudRate { set_4k8 = 4800, set_9k6 = 9600, set_14k4 = 14400, set_19k2 = 19200, set_38k4 = 38400, set_57k6 = 57600, set_115k2 = 115200};

BaudRate rate = BaudRate::set_9k6; 
//BaudRate rate = set_9k6; 

struct Data{
    uint32_t time;
    float coords1, coords2;
    char coords_orientation1, coords_orientation2;
    float Speed;
    uint32_t NPM;
    uint16_t Direction;
    uint8_t Precision_h;
    uint8_t Fix;
};

    Data data;

    char checksum[2];
    char command_checksum[1];

    int seconds =0;
    char status_code;
    float coordinate1, coordinate2;
    char coordinate_orientation1, coordinate_orientation2; 
    float speed;
    int day=0;
    int number_of_satelites_in_use;
    float h_precision;
    char height_unit;
    float separation;
    char separation_unit;

    char set_up_command[50];
    int type;

    public:

    char *Get_new_token(char gps_info[]);
    int formatInteger(int _number, char* _buffer);
    void reverse(char* _buffer, int count);
    void Time(char gps_info[]);
    void Status(char gps_info[]);
    void Coordinates(char gps_info[]);
    void Speed(char gps_info[]);
    void Direction(char gps_info[]);
    void Date(char gps_info[]);
    void Fix_or_NoFix(char gps_info[]);
    void How_many_satelites(char gps_info[]);
    void Horizontal_precision(char gps_info[]);
    void Above_the_water(char gps_info[]);
    void GeoSepa(char gps_info[]);
    void Command_Type(char gps_info[]);
    void Display();
    void Command_Setup();
    void Processing(char gps_info[]);
    void Save();
    int Check(char info[]);
    void Parse(char gps_info[]);
    void FormatToHex(uint8_t n, char* buffer);
    void setBaudRate(BaudRate BaudRate, char *output_command);
    void setUpdateRate(int freq, char *output_command);
    void setMeasureFreq(int freq, char *output_command);
    void setInformation(int mask, char *output_command);
    void addCheckSum(char* command);
};

 #endif