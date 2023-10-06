#ifndef SOLID_HH
#define SOLID_HH

#include <iostream>
#include "vector.hh"
#include <string>

/**
 * @brief Class solid
 * 
 * Class contains:
 * - variable of "vector3d" type that contains location of a drone
 * - variables with names of files
 */

class solid
{
    vector3d location;
    std::string NazwaPliku_BrylaFinalna;
    std::string NazwaPliku_BrylaWzorcowa;


    public:
    vector3d Obrot(double kat, vector3d &punkt);                        //Functions definitions
    vector3d ZmienPunkt(double kat, vector3d &punkt, vector3d skala, vector3d trans);
    bool TworzOpisPrzetransformowanejBryly1(istream &StrmWe_DaneWejsciowe, ostream &StrmWy_DaneWynikowe, double kat, vector3d skala, vector3d trans);
    bool TworzOpisPrzetransformowanejBryly2(const char *NazwaPliku_DaneWejsciowe, const char *NazwaPliku_DaneWynikowe, double kat, vector3d skala, vector3d trans);
    std::string GetFinalName();
};



#endif