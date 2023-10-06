#ifndef SCENEOBJECT_HH
#define SCENEOBJECT_HH

#include <iostream>
#include "solid.hh"
#include <string>
#include <memory>
#include <algorithm>
#include <list>





/**
 * @brief Class which defines scene objects 
 * 
 * contains number and type of a obstacle
 * 
 */

class SObject
{
    int Onumber;
    std::string Otype;

    // public:
    // SObject(int number, std::string type) : Onumber(number), Otype(type) {};
    // virtual void Crash(std::shared_ptr<SObject> Pobj) = 0;
    // virtual ~SObject();

    public:

    int TakeNumber();
    std::string TakeType();
    virtual vector3d OLOCATION() = 0;
    virtual vector3d OSCALE() = 0;
    virtual double Checking(vector3d Olocation, vector3d Dlocation) = 0;
    //virtual bool COLIDE(shared_ptr<SObject>, vector3d location) =0;
};


#endif