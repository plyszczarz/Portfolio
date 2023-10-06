#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include "lacze_do_gnuplota.hh"
#include "vector.hh"
#include "solid.hh"
#include "prism6.hh"


#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "bryly_wzorcowe/graniastoslup6.dat"

/**
 * @brief Function resposible for creating an airscrew of a drone
 * 
 * @param NazwPliku_RotorWDronie parameter that holds name of a file that has coordinates of airscrew
 * @param kat  variable which holds angle of a change
 * @param trans variable which holds translation of movement
 * @return true returns true if all is complete
 * @return false returns false if something is done wrong
 */

bool prism6::TworzRotor(const char *NazwPliku_RotorWDronie, double kat, vector3d trans)
{

#define SKALA_ROTORA 8, 8, 2
    vector3d skala;
    skala[0] = 8;
    skala[1] = 8;
    skala[2] = 2;
    return TworzOpisPrzetransformowanejBryly2(PLIK_WZORCOWEGO_GRANIASTOSLUPA6, NazwPliku_RotorWDronie, kat, skala, trans);
}