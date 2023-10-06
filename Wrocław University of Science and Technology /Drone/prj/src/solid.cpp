#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <fstream>
#include <cassert>
#include "vector.hh"
#include "solid.hh"
#include "cuboid.hh"
#include "drone.hh"
#include "prism6.hh"
#include "scene.hh"
#include "matrix.hh"



#define ILOSC_WIERZ_LINII_TWORZACEJ 4

using namespace std;

/**
 * @brief Function that change (turns) a single point coordinates by given angle
 * 
 * @param kat variable that contains angle of turn
 * @param punkt varaible which contains a point that is transformed
 * @return vector3d that contains transformed point coordinates
 */

vector3d solid::Obrot(double kat, vector3d &punkt)
{
    matrix3x3 M;
    M.przypisanieZZZ(kat);
    punkt=M*punkt;
    return punkt;
}

/**
 * @brief Function that change (truns and moves) a single point by given angle and translation
 * 
 * @param kat variable that contains angle of turn
 * @param punkt varaible which contains a point that is transformed
 * @param skala variable which contains a scale 
 * @param trans variable which contains a translation of a point
 * @return vector3d that contains transformed point coordinates
 */

vector3d solid::ZmienPunkt(double kat, vector3d &punkt, vector3d skala, vector3d trans)
{
    Obrot(kat, punkt);
    punkt[0] = punkt[0] * skala[0] + trans[0];
    punkt[1] = punkt[1] * skala[1] + trans[1];
    punkt[2] = punkt[2] * skala[2] + trans[2];
    return punkt;
}

/**
 * @brief Function that saves transformed pionts to a file 
 * 
 * @param StrmWe_DaneWejsciowe variable that gives a file from which function gets points
 * @param StrmWy_DaneWynikowe variable that takes transformed points to a new file
 * @param kat variable that contains an angle of turn
 * @param skala variable which contains a scale 
 * @param trans variable which contains a translation of a point
 * @return true returns true if all is complete
 * @return false returns false if something is done wrong
 */

bool solid::TworzOpisPrzetransformowanejBryly1(istream &StrmWe_DaneWejsciowe, ostream &StrmWy_DaneWynikowe, double kat, vector3d skala, vector3d trans)
{
    assert(StrmWe_DaneWejsciowe.good());
    assert(StrmWy_DaneWynikowe.good());

    vector3d punkt;
    StrmWe_DaneWejsciowe >> punkt;

    while (!StrmWe_DaneWejsciowe.fail())
    {

        for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ; ++IloscWierzcholkow)
        {
            ZmienPunkt(kat, punkt, skala, trans);

            StrmWy_DaneWynikowe << punkt;
            StrmWe_DaneWejsciowe >> punkt;

            assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ-1 || !StrmWe_DaneWejsciowe.fail());
        }
        StrmWy_DaneWynikowe << endl;
    }
    return !StrmWy_DaneWynikowe.fail();
}

/**
 * @brief Function resposible for proper inter-file savenigs 
 * 
 * @param StrmWe_DaneWejsciowe variable that gives a file from which function gets points
 * @param StrmWy_DaneWynikowe variable that takes transformed points to a new file
 * @param kat variable that contains an angle of turn
 * @param skala variable which contains a scale 
 * @param trans variable which contains a translation of a point
 * @return true returns true if all is complete
 * @return false returns false if something is done wrong
 */

bool solid::TworzOpisPrzetransformowanejBryly2(const char *NazwaPliku_DaneWejsciowe, const char *NazwaPliku_DaneWynikowe, double kat, vector3d skala, vector3d trans)
{
    ifstream Plik_BrylaWzorcowa(NazwaPliku_DaneWejsciowe);
    ofstream Plik_KorpusuDrona(NazwaPliku_DaneWynikowe);


    if (!Plik_BrylaWzorcowa.is_open())
    {
        cerr << endl
             << " Blad otwarcia do odczytu pliku: " << NazwaPliku_DaneWejsciowe << endl
             << endl;
        return false;
    }

    if (!Plik_KorpusuDrona.is_open())
    {
        cerr << endl
             << " Blad otwarcia do odczytu pliku: " << NazwaPliku_DaneWynikowe << endl
             << endl;
        return false;
    }
    return TworzOpisPrzetransformowanejBryly1(Plik_BrylaWzorcowa, Plik_KorpusuDrona, kat, skala, trans);
}

/**
 * @brief Function to get a name
 * 
 * @return std::string name
 */

std::string solid::GetFinalName()
{
    return NazwaPliku_BrylaFinalna;
}