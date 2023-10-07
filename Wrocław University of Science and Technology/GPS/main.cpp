#include "gps.hh"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <cstring>


/*

Początkowe komendy:

PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0       ->      Podstawowe informacje GGA i RMC
PTMK300,1000,0,0,0,0                                ->      Pomiar co sekunde
PMTK220,1000                                        ->      update rate 1hz
PMTK251,9600                                        ->      BaudRate 9600

*/



int main(){
    GPS gps;

    //char gps_info[] = "$GPRMC,220410.00,A,4042.6000,N,07400.4168,W,2.03,221.11,160412,,,A*45";
    //char gps_info[] = "$GPGGA,202410.00,4042.6000,N,07400.4168,W,1,4,3.14,276.7,M,-34.2,M,,*59";
    //char gps_info[] = "$GPGLL,5133.81,N,00042.25,W*75";
    //char gps_info[] = "$GPGSA,A,3,,,,,,16,18,,22,24,,,3.6,2.1,2.2*3C";

    char gps_info[] = "$GPGGA,182409.000,5107.0658,N,01703.9342,E,1,05,2.25,131.1,M,42.6,M,,*69";

    gps.Command_Setup();
    gps.Parse(gps_info);
    
    return 0;
}