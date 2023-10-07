#include "gps.hh"
#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <memory>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iomanip> 


char *GPS::Get_new_token(char gps_info[]){

    return strtok(NULL, ",");
}

void GPS::Time(char gps_info[]){

    char *temp = Get_new_token(gps_info);
    int hour, min, sec;
    int help1;

    hour = atoi(temp);
    help1 = hour;
    hour = help1/10000;
    min = (help1-(hour*10000))/100;
    sec = (help1-(hour*10000) - (min*100));
    seconds = hour*3600 + min*60 +sec;                             //time stamp

    data.time = (day-1)*(86400) + seconds;

    /*
    Meaning:
    amount of counted days before, minus one (not including present day), multiplied by amount of seconds in 
    one day (24 hours * 60 minutes * 60 seconds). Result is date (counting from 1 Jan 1970y) given in seconds
    */

}

void GPS::Status(char gps_info[]){

    char *temp= Get_new_token(gps_info);
    status_code = *temp;
}


void GPS::Coordinates(char gps_info[]){

    char *temp = Get_new_token(gps_info);
    float coordinate1_angle = atof(temp);

    temp = Get_new_token(gps_info);
    coordinate_orientation1 = *temp;
    temp = Get_new_token(gps_info);
    float coordinate2_angle = atof(temp);
    temp = Get_new_token(gps_info);
    coordinate_orientation2 = *temp;

    int help1 = coordinate1_angle;
    int help2 = coordinate2_angle;
    float coordinate1_minutes = coordinate1_angle - ((help1/100)*100);
    float coordinate2_minutes = coordinate2_angle - ((help2/100)*100);

    coordinate1_angle = help1/100;
    coordinate2_angle = help2/100;
    coordinate1 = coordinate1_angle*60 + coordinate1_minutes;
    coordinate2 = coordinate2_angle*60 + coordinate2_minutes;

    data.coords1 = coordinate1;
    data.coords2 = coordinate2;
    data.coords_orientation1 = coordinate_orientation1;
    data.coords_orientation2 = coordinate_orientation2;
}


void GPS::Speed(char gps_info[]){

    char *temp = Get_new_token(gps_info);

    speed = 0;
    speed = atof(temp);
    speed = 1.852*speed;

    data.Speed = speed;
}


void GPS::Direction(char gps_info[]){

    char *temp = Get_new_token(gps_info);

    data.Direction = atof(temp);
}


void GPS::Date(char gps_info[]){
    int arr_of_days[] = {0,31,59,90,120,151,181,212,243,273,304,334};
    char *temp = Get_new_token(gps_info);
    int days, months, years;
    int days_in_months;
    int count_leap_years;

    days = atoi(temp);
    days_in_months = days;
    days = days_in_months/10000;
    months = (days_in_months-(days*10000))/100;
    years = (days_in_months-(days*10000) - (months*100));

    days_in_months = arr_of_days[months-1];
    if(years%4 == 0 && years%100 != 0 || years%400 == 0){
        if(months > 2)
        days_in_months += 1;
    }
    count_leap_years = (years/4) - (years/100) + (years/400);
    int days_in_years = (count_leap_years*366) + ((years - count_leap_years)*365);
    day = 10957 + days_in_years + days_in_months + days;                            //amount of days between 1970 and 2000 + days in given years + days in given months + given days
}



void GPS::Fix_or_NoFix(char gps_info[]){
    char *temp = Get_new_token(gps_info);

    data.Fix = atoi(temp);
}


void GPS::How_many_satelites(char gps_info[]){
    char *temp = Get_new_token(gps_info);

    number_of_satelites_in_use = atoi(temp);
}


void GPS::Horizontal_precision(char gps_info[]){
    char *temp = Get_new_token(gps_info);

    data.Precision_h = atof(temp);
}


void GPS::Above_the_water(char gps_info[]){
    char *temp = Get_new_token(gps_info);

    data.NPM = atof(temp)*10;
    temp = Get_new_token(gps_info);
    height_unit = *temp;
}


void GPS::GeoSepa(char gps_info[]){
    char *temp = Get_new_token(gps_info);

    separation = atof(temp);
    temp = Get_new_token(gps_info);
    separation_unit = *temp;
}


void GPS::Command_Type(char gps_info[]){
    char *temp = strtok(gps_info, ",");

    if(strcmp(temp, "$GPRMC") == 0){
        type = 1;
    }
    if(strcmp(temp, "$GPGGA") == 0){
        type = 2;
    }
}


void GPS::Display(){
    if(type == 1){
        std::cout << "Data: " << day << std::endl;
        std::cout << "Godzina: " << data.time << std::endl;
        std::cout << "Status: " << status_code << std::endl;
        std::cout << "Polozenie: " << std::setprecision(8) << coordinate1 << coordinate_orientation1 << " , " << coordinate2 << coordinate_orientation2 << std::endl;
        std::cout << "Predkosc: " << speed << " km/h"<< std::endl;
        std::cout << "Kierunek (w stopniach od polnocy): " << data.Direction << std::endl;
    }
    if(type == 2){
        std::cout << "Godzina: " << data.time << std::endl;
        std::cout << "Polozenie: " << std::setprecision(8) << coordinate1 << coordinate_orientation1 << " , " << coordinate2 << coordinate_orientation2 << std::endl;
        std::cout << "Stan GPS: " << data.Fix << std::endl;
        std::cout << "Ilosc uzywanych satelit: " << number_of_satelites_in_use<< std::endl;
        std::cout << "Precyzja pozioma: " << data.Precision_h<< std::endl;
        std::cout << "Wysokosc nad poziomem morza: " << data.NPM << " D" << height_unit<< std::endl;
        std::cout << "Separacja geoidalna: " << separation << " " << separation_unit<< std::endl;
    }
}

int count_digits(int number){
    int result=0;

    while(number>0){
        ++result;
        number /=10;
    }
    return result;
}

void GPS::reverse(char* _buffer, int count){
    for(int i=0;i<count/2;i++){
        char temp=_buffer[i];
        _buffer[i]=_buffer[count-i-1];
        _buffer[count-i-1]=temp;
    }
}

int GPS::formatInteger(int _number, char* _buffer){
	int count = 0;
	bool isNegative = _number < 0 ? true : false;
	_number = _number < 0 ? -_number : _number;
	do{
		_buffer[count++] = _number % 10 + '0';
		_number /= 10;
	}while (_number);

	if(isNegative)
		_buffer[count++] = '-';

	reverse(_buffer, count);
	return count;
}

void GPS::addCheckSum(char *command){
    int z = command[0];

    for(int i=0; command[i]!= '\0'; ++i){
        z ^= command[i];
    }

    FormatToHex(z, command_checksum);
    strcat(command, "*");
    strcat(command, command_checksum);
    strcat(command, "#\r\n");
}

void GPS::setBaudRate(BaudRate rate, char *output_command){
    char command[12] = "PMTK251,";
    char buffer[6];
    int baudrate_number = int(rate);
    int number_of_digits = formatInteger(baudrate_number,buffer);

    strncat(command, buffer, number_of_digits);
    strcpy(output_command, command);
    addCheckSum(output_command);

    // for(int i=0; i< 17 ; i++){
    //     std::cout <<  output_command[i];
    // }
}


void GPS::setUpdateRate(int freq, char *output_command){
    char command[13] = "PMTK220,";
    char buffer[6];
    int number_of_digits = formatInteger(freq,buffer);

    strncat(command, buffer, number_of_digits);
    strcpy(output_command, command);
    addCheckSum(output_command);

    // for(int i=0; i< 17 ; i++){
    //     std::cout <<  output_command[i];
    // }
}


void GPS::setMeasureFreq(int freq, char *output_command){
    char command[20] = "PMTK300,";
    char buffer[6];
    int number_of_digits = formatInteger(freq,buffer);

    strncat(command, buffer, number_of_digits);
    strcat(command, ",0,0,0,0");
    strcpy(output_command, command);
    addCheckSum(output_command);

    // for(int i=0; i< 25 ; i++){
    //     std::cout <<  output_command[i];
    // }
}


void GPS::setInformation(int mask, char *output_command){
    char DEC[] = "0123456789";
    char command[45] = "PMTK314,";
    int binary[4];
    char z=0;

    for(int i=3; i>=0; i--){
        binary[i] = mask & 1;
        mask >>= 1;
    }

    for(unsigned int i=0; i<sizeof(mask); i++){
        z = DEC[binary[i]];
        strncat(command, &z, 1);
        strcat(command, ",");
    }

    strcat(command, "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
    strcpy(output_command, command);
    addCheckSum(output_command);

    // for(int i=0; i< 50 ; i++){
    //     std::cout <<  output_command[i];
    // }
}


void GPS::Command_Setup(){
    setUpdateRate(1000,set_up_command);
    setMeasureFreq(1000,set_up_command);
    setBaudRate(rate, set_up_command);
    setInformation(GPRMC|GPGGA, set_up_command);
    //std::cout <<  set_up_command << std::endl;
}


void GPS::Processing(char gps_info[]){

switch(type){

        case 1:
            Time(gps_info);
            Status(gps_info);
            Coordinates(gps_info);
            Speed(gps_info);
            Direction(gps_info);
            Date(gps_info);
            Display();
            break;

        case 2:
            Time(gps_info);
            Coordinates(gps_info);
            Fix_or_NoFix(gps_info);
            How_many_satelites(gps_info);
            Horizontal_precision(gps_info);
            Above_the_water(gps_info);
            GeoSepa(gps_info);
            Display();
            break;

        default:
            break;
    }
    type =0;
}



void GPS::FormatToHex(uint8_t n, char* buffer){
    static char HEX[] = "0123456789ABCDEF";
    int index =1;

    while (n > 0){
        buffer[index--] = HEX[(n & 0xF)];
        n >>= 4;            
    }

    //for(int z=0; z<2; z++)
    // std::cout << buffer[z];
}



int GPS::Check(char gps_info[]){
    uint8_t z = gps_info[1];
    int i=0;

    for(i=2; gps_info[i]!= '*'; ++i){
        z ^= gps_info[i];
    }

    FormatToHex(z, checksum);

    if(checksum[0] == gps_info[i+1] && checksum[1] == gps_info[i+2]){
        return 1;
    }
    else{
        return 0;
    }
}



void GPS::Parse(char gps_info[]){
    int check;
    check = Check(gps_info);
    
    if(check == 1){
        Command_Type(gps_info);
        Processing(gps_info);
    }
    else{
        std::cout << "Blad, niezgodny checksum" << std::endl;
    }
}