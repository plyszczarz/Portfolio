#ifndef SCENE_HH
#define SCENE_HH

#include <iostream>
#include "drone.hh"
#include "lacze_do_gnuplota.hh"
#include "scene.hh"
#include <list>
#include <memory>
#include "sceneObject.hh"

/**
 * @brief Class scene that inhertis drone class
 * 
 * Class contains:
 * - variable of "drone" type that has array of two drones
 * - variable that is connected to graphic application
 */

class scene :public drone
{

    public:
    int _whichdrone;
    drone drones[2];
    PzG::LaczeDoGNUPlota Lacze;
    std::list< std::shared_ptr<SObject>> obstacles;
    std::list< std::shared_ptr<drone>> _drones;

    double changeNumbers1(double direction, double distance);               // Definiction of functions
    double changeNumbers2(double direction, double distance);
    bool DodajTrasePrzelotu(vector3d location, double distance, int direction);
    bool AnimacjaLotuDrona(const double direction, const double distance, drone &drones, int whichdrone);
    string file(int number, string name);
    void AddSharp(vector3d scale, vector3d position, int number, string nname);
    void AddRidge(vector3d scale, vector3d position, int number, string nname);
    void AddTable(vector3d scale, vector3d position, int number, string nname);
    bool RemoveObstacle();
    bool IsColliding(drone &Drone, int whichdrone);
    void IfCollideFlight(const double direction, const double distance, drone &Drone, int whichdrone);
    void AdditionalHorizontalFlight(const double direction, const double distance, drone &drones, int whichdrone);
    double Checking(vector3d Olocation, vector3d Dlocation);
};



#endif