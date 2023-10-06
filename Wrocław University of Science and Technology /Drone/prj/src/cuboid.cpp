#include "cuboid.hh"
#include "solid.hh"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>
#include <cassert>




using namespace std;


#define PLIK_WZORCOWEGO_SZESCIANU "bryly_wzorcowe/szescian.dat"


/**
 * @brief Function that creates body of a drone
 * 
 * @param NazwPliku_KorpusuWDronie parameter that holds name of a file that has coordinates of body
 * @param kat  variable which holds angle of a change
 * @param trans variable which holds translation of movement
 * @return true returns true if all is complete
 * @return false returns false if something is done wrong
 */

bool cuboid::TworzKorpus(const char *NazwPliku_KorpusuWDronie, double kat, vector3d trans)
{

#define SKALA_KORPUSU 10, 8, 4
    vector3d skala;
    skala[0] = 10;
    skala[1] = 8;
    skala[2] = 4;
    return TworzOpisPrzetransformowanejBryly2(PLIK_WZORCOWEGO_SZESCIANU, NazwPliku_KorpusuWDronie, kat, skala, trans);
}

