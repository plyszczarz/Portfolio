#include "sceneObject.hh"
#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>


/**
 * @brief Function that takes number of a scene object
 * 
 * @return int number
 */

int SObject::TakeNumber()
{
    return Onumber;
}

/**
 * @brief Function that takes type of a scene object
 * 
 * @return std::string name
 */

std::string SObject::TakeType()
{
    return Otype;
}