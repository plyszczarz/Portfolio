#ifndef CUBOID_HH
#define CUBOID_HH

#include <iostream>
#include "vector.hh"
#include "solid.hh"

using namespace std;


/*!
 * \brief  Class Cuboid that inherit a "solid" class
 *
 * Class has a variable type "vector3d" containing a scale of drone's body
 * 
 */

class cuboid : public solid
{
    vector3d scale;
    public:


    bool TworzKorpus(const char *NazwPliku_KorpusuWDronie, double kat, vector3d trans);         //Definiction of body-creating function
};


#endif