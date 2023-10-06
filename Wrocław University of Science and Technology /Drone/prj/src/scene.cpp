#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include "vector.hh"
#include "solid.hh"
#include "cuboid.hh"
#include "drone.hh"
#include "prism6.hh"
#include "scene.hh"
#include <algorithm>
#include "sharp_top_hill.hh"
#include "table_land.hh"
#include "ridge_hill.hh"
#include <cmath>

#define PLIK_ROBOCZY__DRON1_KORPUS "dat/PlikRoboczy_Dron1_Korpus.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1 "dat/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2 "dat/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3 "dat/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4 "dat/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS "dat/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1 "dat/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2 "dat/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3 "dat/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4 "dat/PlikWlasciwy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__GORA1 "dat/gora1.dat"

#define PLIK_TRASY_PRZELOTU "dat/trasa_przelotu.dat"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/**
 * @brief Function which counts how much a X coordinate needs to change
 * 
 * @param direction parameter which holds a direction that drone has to move (in degrees)
 * @param distance parameter which holds a distance that drone has to fly
 * @return double that holds a X coordinate change
 */

double scene::changeNumbers1(double direction, double distance)
{
    double x;
    direction = direction * M_PI / 180;
    x = distance * sin(direction);
    return x;
}

/**
 * @brief Function which counts how much a Y coordinate needs to change
 * 
 * @param direction parameter which holds a direction that drone has to move (in degrees)
 * @param distance parameter which holds a distance that drone has to fly
 * @return double that holds a Y coordinate change 
 */

double scene::changeNumbers2(double direction, double distance)
{
    double y;
    direction = direction * M_PI / 180;
    y = distance * cos(direction);
    return y;
}

/**
 * @brief Function that creates a fly-way of a drone
 * 
 * @param location parameter which holds location of a drone
 * @param distance parameter which holds distance of a drone's flight
 * @param direction parameter which holds direction of a drone's flight
 * @return true returns true if all is complete
 * @return false returns false if something is done wrong
 */

bool scene::DodajTrasePrzelotu(vector3d location, double distance, int direction)
{
    double x, y;

    x = changeNumbers1(direction, distance);
    y = changeNumbers2(direction, distance);

    ofstream StrmWy(PLIK_TRASY_PRZELOTU);

    if (!StrmWy.is_open())
    {
        cerr << endl
             << " Nie mozna otworzyc do zapisu pliku: " << PLIK_TRASY_PRZELOTU << endl
             << endl;
        return false;
    }

    StrmWy << location[0] << "  " << location[1] << "  " << location[2] << "  " << endl
           << location[0] << "  " << location[1] << "  "
           << "80" << endl
           << location[0] + y << "  " << location[1] + x << "  "
           << "80" << endl
           << location[0] + y << "  " << location[1] + x << "  "
           << "0" << endl;
    Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
    return !StrmWy.fail();
}



/**
 * @brief Function responsible for drone's flight animation
 * 
 * @param direction parameter which holds direction of a drone's flight
 * @param distance parameter which holds distance of a drone's flight
 * @return true returns true if all is complete
 * @return false returns false if something is done wrong
 */

bool scene::AnimacjaLotuDrona(const double direction, const double distance, drone &drones, int whichdrone)
{
    _whichdrone = whichdrone;

    //-------------------------------------
    // Wznoszenie ...
    //

    /**
     * @brief drone's take off
     * 
     */
    cout << endl
         << "Wznoszenie ... " << endl;
    for (; drones.location[2] <= 80; drones.location[2] += 2) //operation of slow summation of drone's vertical coordiantes
    {
        if (!PrzemiescDrona(drones.angle, drones.location, whichdrone)) //displaying take off movement
            return false;
        usleep(50000); // 0.1 ms
        Lacze.Rysuj();
    }
    drones.location[2] -= 2;

    /**
     * @brief drone's in-place turning (in the direction of destination)
     * 
     */

    cout << "Zmiana orientacji ... " << endl;

    for (; drones.angle <= direction; drones.angle += 5) //operation of slow summation of drone's angle coordiantes
    {
        if (!PrzemiescDrona(drones.angle, drones.location, whichdrone)) //displaying turning movement
            return false;
        usleep(50000);
        Lacze.Rysuj();
    }
    drones.angle -= 5;

    //-------------------------------------
    // Lot do przodu ...
    //

    /**
     * @brief drone's forward movement (in the direction of destination)
     * 
     */
    cout << "Lot do przodu ... " << endl;
    for (int i = 0; i < distance; ++i)
    {
        drones.location = drones.location + vector3d{cos(direction * M_PI / 180), sin(direction * M_PI / 180), 0}; //operation of summation of drone's X and Y coordiantes
        if (!PrzemiescDrona(drones.angle, drones.location, whichdrone))                                            //displaying flying movement
            return false;
        usleep(50000);
        Lacze.Rysuj();
    }


    IfCollideFlight(direction, 2, drones, whichdrone);
    

    //-------------------------------------
    // Opadanie ...
    //
    /**
     * @brief drone's landing movement
     * 
     */
    cout << "Opadanie ... " << endl;
    for (; drones.location[2] >= 0; drones.location[2] -= 2) //operation of slow subtraction of drone's vertical coordiantes
    {
        if (!PrzemiescDrona(drones.angle, drones.location, whichdrone)) //displaying landing movement
            return false;
        usleep(50000); // 0.1 ms
        Lacze.Rysuj();
    }
    drones.location[2] += 2;

    return true;
}

/**
 * @brief Function which creates a file name due to given obstacle name and number
 * 
 * @param number number of file
 * @param name name of file
 * @return string returns created file name
 */

string scene::file(int number, string name)
{
    ostringstream stru;
    stru << "dat/" << name << number << ".dat";
    return stru.str();
}

/**
 * @brief Function which adds a obstacle SharpTopHill
 * 
 * @param scale scale that you want to scale a obstacle
 * @param position coordinates
 * @param number number of a obstacle
 * @param nname name of a obstacle
 */

void scene::AddSharp(vector3d scale, vector3d position, int number, string nname)
{
    nname = file(number, nname);          //file name changing function usage
    Lacze.DodajNazwePliku(nname.c_str()); //adding created file to scene
    obstacles.push_back(std::make_shared<sharp>("bryly_wzorcowe/szescian_na_powierzchni.dat", scale, position, nname.c_str(), number));
}

/**
 * @brief Function which adds a obstacle RidgeHill
 * 
 * @param scale scale that you want to scale a obstacle
 * @param position coordinates
 * @param number number of a obstacle
 * @param nname name of a obstacle
 */

void scene::AddRidge(vector3d scale, vector3d position, int number, string nname)
{
    nname = file(number, nname);          //file name changing function usage
    Lacze.DodajNazwePliku(nname.c_str()); //adding created file to scene
    obstacles.push_back(std::make_shared<ridge>("bryly_wzorcowe/szescian_na_powierzchni.dat", scale, position, nname.c_str(), number));
}

/**
 * @brief Function which adds a obstacle TableLand
 * 
 * @param scale scale that you want to scale a obstacle
 * @param position coordinates
 * @param number number of a obstacle
 * @param nname name of a obstacle
 */

void scene::AddTable(vector3d scale, vector3d position, int number, string nname)
{
    nname = file(number, nname);          //file name changing function usage
    Lacze.DodajNazwePliku(nname.c_str()); //adding created file to scene
    obstacles.push_back(std::make_shared<tableLand>("bryly_wzorcowe/szescian_na_powierzchni.dat", scale, position, nname.c_str(), number));
}

/**
 * @brief Function which deletes choosen obstacle
 * 
 * @return true returns true if everything went correctyl
 * @return false returns false if something went wrong
 */

bool scene::RemoveObstacle()
{
    std::string Oname = "obstacle";
    list<shared_ptr<SObject>> help;
    shared_ptr<SObject> x;
    help = obstacles; //creating secound list to make deleting from list easier :))
    int choice, size;
    cout << "What obstacle do you want to delete?" << endl;

    for (int i = 0; i < 2; ++i)
    {
        help.pop_back();
    }

    size = (int)help.size();

    for (int y = 0; y < size; ++y)
    {
        cout << y + 1 << "---->";
        x = help.front(); //displaying existing obstacles
        help.pop_front();
        cout << endl;
    }
    help = obstacles;

    for (int i = 0; i < 2; ++i)
    {
        help.pop_back();
    }

    cin >> choice;
    if (obstacles.empty())
    {
        cout << "No obstacles to delete!!!" << endl; //assertion
        return false;
    }
    else
    {
        for (int z = 1; z < choice; z++)
        {
            help.pop_front(); //removing from help list untill we get wated obstacle
        }
        obstacles.remove(help.front());
        // Lacze.UsunNazwePliku(help.front().get()->GetFinalName());
        // cout << "usuwam pik o nazwie"<<help.front().get()->GetFinalName() << endl;
        Oname = file(choice, Oname);         //discovering name of file to delete
        Lacze.UsunNazwePliku(Oname.c_str()); //deleting found file from scene
        remove(Oname.c_str());
    }
    return true;
}

/**
 * @brief Virtual function that counts and returns distance between drone and obstacle centers
 * 
 * @param Olocation location of a obstacle  
 * @param Dlocation location of a drone
 * @return double metioned distance
 */

double scene::Checking(vector3d Olocation, vector3d Dlocation)
{
    double colideDistance;

    colideDistance = sqrt(pow((Dlocation[0] - Olocation[0]), 2) + pow((Dlocation[1] - Olocation[1]), 2));

    return colideDistance;
}


/**
 * @brief Function that deletes choosen drone from obstacle list, gets it's location and scale and calculates if choosen drone is able to land
 * 
 * @param Drone Drones features
 * @param whichdrone number of a drone
 * @return true if drone collides with obstacle
 * @return false if drone doesnt collide with a obstacle
 */

bool scene::IsColliding(drone &Drone, int whichdrone)

{
    list<shared_ptr<SObject>> help;
    help = obstacles;
    int _listSize;                                                      //creates extra list to make a work easier :))
    double colideDistance;
    shared_ptr<SObject> HelpDrone;
    vector3d ScaleObstacle, LocationObstacle, LocationDrone, ScaleDrone;                //variables to store cords and scales

    if (whichdrone == 1)
    {
        LocationDrone = _drones.front().get()->DLOCATION();
        ScaleDrone = _drones.front().get()->OSCALE();                                                    //getting drone info
        help.pop_front();
    }
    if (whichdrone == 2)
    {
        LocationDrone = _drones.back().get()->DLOCATION();
        ScaleDrone = _drones.back().get()->OSCALE();
        HelpDrone = help.front();
        help.pop_front();                                                                                 //getting drone info
        help.pop_front();
        help.push_front(HelpDrone);
    }

    LocationObstacle = help.front().get()->OLOCATION();
    ScaleObstacle = help.front().get()->OSCALE();                                                       //getting obstacle info

    colideDistance = help.front().get()->Checking(LocationObstacle, Drone.location);

    if (colideDistance < 2.0*(ScaleDrone[0]))
    {
        cout << "We cant land here, obstacle is underneath" << endl;                                    //checking if drone collide with other drone
        return true;
    }

    help.pop_front();
    _listSize = help.size();

    for (int x = 0; x < _listSize; ++x)
    {
        LocationObstacle = help.front().get()->OLOCATION();
        ScaleObstacle = help.front().get()->OSCALE();                                                   //checking if drone collide with obstacles
        colideDistance = help.front().get()->Checking(LocationObstacle, Drone.location);
        help.pop_front();

        if (colideDistance < (ScaleObstacle[0]) / 2 + ScaleDrone[0] || colideDistance < (ScaleObstacle[1]) / 2 + ScaleDrone[0])
        {
            cout << "We cant land here, obstacle is underneath" << endl;
            return true;
        }
    }
    return false;
}


/**
 * @brief Function that checks if drone coolide and makes additional flights and way-drawings due to the result
 * 
 * @param direction direction of additional flight
 * @param distance distance of additional flight
 * @param Drone drone features
 * @param whichdrone number of a drone
 */

void scene::IfCollideFlight(const double direction, const double distance, drone &Drone, int whichdrone)
{
    vector3d StartingDronePosition;

    if (whichdrone == 1)
    {
        StartingDronePosition = _drones.front().get()->DLOCATION();                                             //gets flying drone location
    }

    if (whichdrone == 2)
    {
        StartingDronePosition = _drones.back().get()->DLOCATION();                                             //gets flying drone location
    }

    StartingDronePosition = Drone.location;

    while (IsColliding(Drone, whichdrone))
    {
        if (whichdrone == 1)
        {
            _drones.front().get()->AdditionalHorizontalFlight(direction, Drone, distance, whichdrone);
            _drones.front().get()->AdditionalWayDrawing(StartingDronePosition, Drone.location);                         //additional flight and way-drawing
            Lacze.DodajNazwePliku("dat/AdditionalWayDrawing.dat");
            Lacze.Rysuj();
        }

        if (whichdrone == 2)
        {
            _drones.back().get()->AdditionalHorizontalFlight(direction, Drone, distance, whichdrone);
            _drones.back().get()->AdditionalWayDrawing(StartingDronePosition, Drone.location);                         //additional flight and way-drawing
            Lacze.DodajNazwePliku("dat/AdditionalWayDrawing.dat");
            Lacze.Rysuj();
        }
    }
    
}