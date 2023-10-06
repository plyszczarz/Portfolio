#ifndef DRONE_HH
#define DRONE_HH

#include <iostream>
#include "vector.hh"
#include "cuboid.hh"
#include "prism6.hh"
#include "sceneObject.hh"
#include "ridge_hill.hh"
#include "sharp_top_hill.hh"
#include "table_land.hh"



/*!
 * \brief  Class drone
 *
 * Class has:
 * - variable type "vector3d" that contains a location of a drone
 * - variable type "cuboid" that contains a body of a drone
 * - variable type "prism6" that contains 4 airscrews of a drone
 * - variable type "double" that contains an angle of a turn
 */

class drone : public SObject
{

    public:
    vector3d location;
    cuboid body;
    prism6 airscrew[4];
    double angle;

    // drone(int number) : SObject(number, "drone") {};
    // ~drone();

    // virtual void Crash(std::shared_ptr<SObject>Pobj) override final
    // {
    //     if(Pobj.get() == this)
    //     {
    //         std::cout << "No crash" << endl;
    //     }
    //     else
    //     {
    //         std::cout << "coliding with" << Pobj->TakeType() << "number" << Pobj->TakeNumber() << std::endl;
    //     }
        
    // }

    bool PrzemiescDrona(double KatOrDrona_st, vector3d &pozycja, int whichdrone);                //Definitions of functions
    bool TworzDrona();
    bool TworzDrona2();
    vector3d ShowPosition();
    void AdditionalHorizontalFlight(const double direction, drone &drones, int distance, int whichdrone);
    vector3d DLOCATION() {return location;};
    vector3d OLOCATION(){return location;};
    vector3d OSCALE(){return {15,0,0};};
    double Checking(vector3d Olocation, vector3d Dlocation);
    void AdditionalWayDrawing(vector3d ActualDroneLocation, vector3d add);
};




#endif