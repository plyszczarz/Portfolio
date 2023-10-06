#ifndef PRISM6_HH
#define PRISM6_HH

#include <iostream>
#include "vector.hh"
#include "solid.hh"

/**
 * @brief Class prism6 that inherits solid class
 * 
 * Class contains:
 * - variable of "vector3d" type which contains location of a drone
 * 
 */

class prism6 : public solid
{
    vector3d location;
    public:


    bool TworzRotor(const char *NazwPliku_RotorWDronie, double kat, vector3d trans);            //Function declaration
};




#endif