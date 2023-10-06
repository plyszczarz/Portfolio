#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include "vector.hh"
#include "solid.hh"
#include "lacze_do_gnuplota.hh"
#include "cuboid.hh"
#include "prism6.hh"
#include "drone.hh"
#include "scene.hh"
#include "sceneObject.hh"



using namespace std;


#define PLIK_ROBOCZY__DRON1_KORPUS "dat/PlikRoboczy_Dron1_Korpus.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1 "dat/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2 "dat/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3 "dat/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4 "dat/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS "dat/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1 "dat/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2 "dat/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3 "dat/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4 "dat/PlikWlasciwy_Dron1_Rotor4.dat"


#define PLIK_WLASCIWY__DRON2_KORPUS "dat/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1 "dat/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2 "dat/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3 "dat/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4 "dat/PlikWlasciwy_Dron2_Rotor4.dat"



/**
 * @brief Function that creates all parts of a drone
 * 
 * @return true returns true if all is complete
 * @return false returns false if something is done wrong
 */

bool drone::TworzDrona()
{
    vector3d trans, LP, PP, LT, PT;                     //translations created
    static double KatObrotuRotora_st = 0;               //angle of airscrew turning
#define TRANSLACJA_ROTOR_LEWY_PRZEDNI 5, 4, 5           //coordinates of airscrews 
#define TRANSLACJA_ROTOR_PRAWY_PRZEDNI 5, -4, 5
#define TRANSLACJA_ROTOR_LEWY_TYLNY -5, 4, 5
#define TRANSLACJA_ROTOR_PRAWY_TYLNY -5, -4, 5

    trans[0] = 0;
    trans[1] = 0;                               //assigning values of translation to variables
    trans[2] = 2;

    LP[0]=5;
    LP[1]=4;                                    //assigning values of coordinates to all of the airscrews
    LP[2]=5;

    PP[0]=5;
    PP[1]=-4;
    PP[2]=5;

    LT[0]=-5;
    LT[1]=4;
    LT[2]=5;

    PT[0]=-5;
    PT[1]=-4;
    PT[2]=5;


    if (!body.TworzKorpus(PLIK_ROBOCZY__DRON1_KORPUS, 0, trans))                    //creating drone's body with added coordinates
        return false;

    if (!airscrew[0].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR1, KatObrotuRotora_st, LP))            //creating all drone's airscrews with added coordinates
        return false;

    if (!airscrew[1].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR2, -KatObrotuRotora_st, PP))
        return false;

    if (!airscrew[2].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR3, -KatObrotuRotora_st, LT))
        return false;

    if (!airscrew[3].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR4, KatObrotuRotora_st, PT))
        return false;

#define SKOK_OBROTU_ROTOROW_stopnie 10

    KatObrotuRotora_st += SKOK_OBROTU_ROTOROW_stopnie;

    return true;
}



bool drone::TworzDrona2()
{
    vector3d trans, LP, PP, LT, PT;                     //translations created
    static double KatObrotuRotora_st = 0;               //angle of airscrew turning
#define TRANSLACJA_ROTOR_LEWY_PRZEDNI 5, 4, 5           //coordinates of airscrews 
#define TRANSLACJA_ROTOR_PRAWY_PRZEDNI 5, -4, 5
#define TRANSLACJA_ROTOR_LEWY_TYLNY -5, 4, 5
#define TRANSLACJA_ROTOR_PRAWY_TYLNY -5, -4, 5

    trans[0] = 0;
    trans[1] = 0;                               //assigning values of translation to variables
    trans[2] = 2;

    LP[0]=5;
    LP[1]=4;                                    //assigning values of coordinates to all of the airscrews
    LP[2]=5;

    PP[0]=5;
    PP[1]=-4;
    PP[2]=5;

    LT[0]=-5;
    LT[1]=4;
    LT[2]=5;

    PT[0]=-5;
    PT[1]=-4;
    PT[2]=5;


    if (!body.TworzKorpus(PLIK_ROBOCZY__DRON1_KORPUS, 0, trans))                    //creating drone's body with added coordinates
        return false;

    if (!airscrew[0].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR1, KatObrotuRotora_st, LP))            //creating all drone's airscrews with added coordinates
        return false;

    if (!airscrew[1].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR2, -KatObrotuRotora_st, PP))
        return false;

    if (!airscrew[2].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR3, -KatObrotuRotora_st, LT))
        return false;

    if (!airscrew[3].TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR4, KatObrotuRotora_st, PT))
        return false;

#define SKOK_OBROTU_ROTOROW_stopnie 10

    KatObrotuRotora_st += SKOK_OBROTU_ROTOROW_stopnie;

    return true;
}




/**
 * @brief Function responsible for drone's movement
 * 
 * @param KatOrDrona_st variable which holds an angle of drone's turn
 * @param pozycja variable which holds current coordinates of a drone
 * @return true returns true if all is complete
 * @return false returns false if something is done wrong
 */

bool drone::PrzemiescDrona(double KatOrDrona_st, vector3d &pozycja, int whichdrone)
{
    vector3d skala;
#define SKALA_JEDNOSTKOWA 1, 1, 1

    skala[0] = 1;
    skala[1] = 1;           //assigning values to scale variables
    skala[2] = 1;

    if (!TworzDrona())
        return false;
    if(!TworzDrona2())
        return false;

    if(whichdrone == 1)
    {
    const char *NazwyPlikowRoboczych[] = {PLIK_ROBOCZY__DRON1_KORPUS, PLIK_ROBOCZY__DRON1_ROTOR1, PLIK_ROBOCZY__DRON1_ROTOR2,
                                          PLIK_ROBOCZY__DRON1_ROTOR3, PLIK_ROBOCZY__DRON1_ROTOR4, nullptr};

    const char *NazwyPlikowWlasciwych[] = {PLIK_WLASCIWY__DRON1_KORPUS, PLIK_WLASCIWY__DRON1_ROTOR1, PLIK_WLASCIWY__DRON1_ROTOR2,
                                           PLIK_WLASCIWY__DRON1_ROTOR3, PLIK_WLASCIWY__DRON1_ROTOR4, nullptr};

    assert(sizeof(NazwyPlikowRoboczych) == sizeof(NazwyPlikowWlasciwych));

    for (unsigned int Idx = 0; NazwyPlikowRoboczych[Idx] != nullptr; ++Idx)
    {
        if (!body.TworzOpisPrzetransformowanejBryly2(NazwyPlikowRoboczych[Idx], NazwyPlikowWlasciwych[Idx], KatOrDrona_st, skala, pozycja))
            return false;
    }
    }


    else if(whichdrone == 2)
    {
    const char *NazwyPlikowRoboczych[] = {PLIK_ROBOCZY__DRON1_KORPUS, PLIK_ROBOCZY__DRON1_ROTOR1, PLIK_ROBOCZY__DRON1_ROTOR2,
                                          PLIK_ROBOCZY__DRON1_ROTOR3, PLIK_ROBOCZY__DRON1_ROTOR4, nullptr};

    const char *NazwyPlikowWlasciwych[] = {PLIK_WLASCIWY__DRON2_KORPUS, PLIK_WLASCIWY__DRON2_ROTOR1, PLIK_WLASCIWY__DRON2_ROTOR2,
                                           PLIK_WLASCIWY__DRON2_ROTOR3, PLIK_WLASCIWY__DRON2_ROTOR4, nullptr};

    assert(sizeof(NazwyPlikowRoboczych) == sizeof(NazwyPlikowWlasciwych));

    for (unsigned int Idx = 0; NazwyPlikowRoboczych[Idx] != nullptr; ++Idx)
    {
        if (!body.TworzOpisPrzetransformowanejBryly2(NazwyPlikowRoboczych[Idx], NazwyPlikowWlasciwych[Idx], KatOrDrona_st, skala, pozycja))
            return false;
    }
    }
    return true;
}


/**
 * @brief Function that makes drone fly a little bit more :))
 * 
 * @param direction direction of additional flight
 * @param drones drone features
 * @param distance distance of additional flight
 * @param whichdrone number of a drone
 */

void drone::AdditionalHorizontalFlight(const double direction, drone &drones, int distance, int whichdrone)
{
    for(int x=0; x<distance; ++x)
    {
    drones.location = drones.location + vector3d{cos(direction*M_PI/180),sin(direction*M_PI/180),0};
    PrzemiescDrona(drones.angle, drones.location, whichdrone);                                                   //displaying flying movement
    usleep(50000);
    }
}

/**
 * @brief Virtual function that counts and returns distance between drone and obstacle centers
 * 
 * @param Olocation location of a obstacle  
 * @param Dlocation location of a drone
 * @return double metioned distance
 */

double drone::Checking(vector3d Olocation, vector3d Dlocation)
{
    double colideDistance;

    colideDistance = sqrt(pow((Dlocation[0] - Olocation[0]), 2) + pow((Dlocation[1] - Olocation[1]), 2));

    return colideDistance;
}

/**
 * @brief Function that saves to new file coordinates of additional way-drawing
 * 
 * @param ActualDroneLocation actual location of flying drone
 * @param add location where drone will try to land
 */

void drone::AdditionalWayDrawing(vector3d ActualDroneLocation, vector3d add)
{

    ofstream file("dat/AdditionalWayDrawing.dat");



    file << ActualDroneLocation[0] << " " << ActualDroneLocation[1] << " " << 80 << endl;

    file << add[0] << " " << add[1] << " " << add[2] << endl;
    file << add[0] << " " << add[1] << " " << 0 << endl;
}