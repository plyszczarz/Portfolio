

/**
 * @mainpage Multi-language drone operations
 * @section Content Content:
 * @ref - User iterface with language choice
 * 
 * 
 * @ref - Drone's flight animation with optional degree of direction and distance 
 * 
 * 
 * @ref - Class diagram:
 * 
 * 
 * 
 * 
 * 
 * 
 * @image html DiaFINAL.png "Class diagram"
 */

/***
 *              _____                    _____                   _______                   _____          
 *             /\    \                  /\    \                 /::\    \                 /\    \         
 *            /::\    \                /::\    \               /::::\    \               /::\____\        
 *           /::::\    \              /::::\    \             /::::::\    \             /::::|   |        
 *          /::::::\    \            /::::::\    \           /::::::::\    \           /:::::|   |        
 *         /:::/\:::\    \          /:::/\:::\    \         /:::/~~\:::\    \         /::::::|   |        
 *        /:::/  \:::\    \        /:::/__\:::\    \       /:::/    \:::\    \       /:::/|::|   |        
 *       /:::/    \:::\    \      /::::\   \:::\    \     /:::/    / \:::\    \     /:::/ |::|   |        
 *      /:::/    / \:::\    \    /::::::\   \:::\    \   /:::/____/   \:::\____\   /:::/  |::|   | _____  
 *     /:::/    /   \:::\ ___\  /:::/\:::\   \:::\____\ |:::|    |     |:::|    | /:::/   |::|   |/\    \ 
 *    /:::/____/     \:::|    |/:::/  \:::\   \:::|    ||:::|____|     |:::|    |/:: /    |::|   /::\____\
 *    \:::\    \     /:::|____|\::/   |::::\  /:::|____| \:::\    \   /:::/    / \::/    /|::|  /:::/    /
 *     \:::\    \   /:::/    /  \/____|:::::\/:::/    /   \:::\    \ /:::/    /   \/____/ |::| /:::/    / 
 *      \:::\    \ /:::/    /         |:::::::::/    /     \:::\    /:::/    /            |::|/:::/    /  
 *       \:::\    /:::/    /          |::|\::::/    /       \:::\__/:::/    /             |::::::/    /   
 *        \:::\  /:::/    /           |::| \::/____/         \::::::::/    /              |:::::/    /    
 *         \:::\/:::/    /            |::|  ~|                \::::::/    /               |::::/    /     
 *          \::::::/    /             |::|   |                 \::::/    /                /:::/    /      
 *           \::::/    /              \::|   |                  \::/____/                /:::/    /       
 *            \::/____/                \:|   |                   ~~                      \::/    /        
 *             ~~                      \ |___|                                            \/____/         
 *                                                                                                                                                                                                    
 */

/*!
 * \file
 * \brief Przykład animacji przelotu drona
 *
 * Przykład ten ma tylko i wyłącznie za zadanie pokazanie efektów animacji lotu
 * drona. Kod w nim zawarty nie jest pisany w sposób obiektowo zorientowany.
 * Dlatego też nie należy wzorować się na nim.
 * Niemniej można się wzorować na ciągu operacji, które należy wykonać,
 * aby otrzymać właściwą animację.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include "lacze_do_gnuplota.hh"
#include "cuboid.hh"
#include "drone.hh"
#include "prism6.hh"
#include "scene.hh"
#include "solid.hh"
#include "vector.hh"
#include "sharp_top_hill.hh"
#include "ridge_hill.hh"
#include "table_land.hh"

using namespace std;

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

#define PLIK_WLASCIWY__DRON2_KORPUS "dat/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1 "dat/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2 "dat/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3 "dat/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4 "dat/PlikWlasciwy_Dron2_Rotor4.dat"

#define PLIK_TRASY_PRZELOTU "dat/trasa_przelotu.dat"

/**
 * @brief Function that displays english menu
 * 
 * @param wybor variable which holds a user's choice
 */

void menuE(char &wybor)
{

  cout << endl
       << endl;
  cout << "l - Make a flight with a drone" << endl;
  cout << "j - Choose a language" << endl;
  cout << "m - Display menu" << endl;
  cout << "k - End a program" << endl;
  cout << "s - Show drone's coordinates" << endl;
  cout << "a - Add new obsticle object" << endl;
  cout << "u - Delete an obsticle object" << endl;
  cout << "d - Display a scene" << endl;
  cout << endl;
  cout << "Number of type "
          "vector"
          " objects totally created:"
       << endl;
  cout << vector3d::howmanyCCC() << endl;
  cout << "Number of type "
          "vector"
          " objects that actually exist:"
       << endl;
  cout << vector3d::howmanyTTT() << endl;
  cout << "Your choice (m - menu) is --->>> ";
  cin >> wybor;
  cout << endl
       << endl
       << endl;
}

/**
 * @brief Function that displays polish menu
 * 
 * @param wybor variable which holds a user's choice
 */

void menuP(char &wybor)
{

  cout << endl
       << endl;
  cout << "l - Wykonaj lot dronem" << endl;
  cout << "j - Wybierz jezyk" << endl;
  cout << "m - Wyswietl menu" << endl;
  cout << "k - Zakoncz program" << endl;
  cout << "s - Pokaz wspolrzedne polorzenia drona" << endl;
  cout << "a - Dodaj przeszkode" << endl;
  cout << "d - Wyswietl scene" << endl;
  cout << endl;
  cout << "Ilosc wszystkich obiektow typu "
          "vector"
          ":"
       << endl;
  cout << vector3d::howmanyCCC() << endl;
  cout << "Ilosc wszystkich stworzonych obiektow typu "
          "vector"
          ":"
       << endl;
  cout << vector3d::howmanyTTT() << endl;
  cout << "Twoj wybor (m - menu) to --->>> ";
  cin >> wybor;
  cout << endl
       << endl
       << endl;
}

/**
 * @brief Function that displays czech menu
 * 
 * @param wybor variable which holds a user's choice
 */

void menuC(char &wybor)
{

  cout << endl
       << endl;
  cout << "l - Letí dron" << endl;
  cout << "j - Vyber jazyk" << endl;
  cout << "m - Zobrazit nabídku" << endl;
  cout << "k - Dokončit program" << endl;
  cout << "s - Zobrazit souřadnice pólů dronů" << endl;
  cout << endl;
  cout << "Počet všech objektů typu "
          "vector"
          ":"
       << endl;
  cout << vector3d::howmanyCCC() << endl;
  cout << "Počet všech vytvořených objektů typu "
          "vector"
          ":"
       << endl;
  cout << vector3d::howmanyTTT() << endl;
  cout << "Tvoje volba (m - menu) to --->>> ";
  cin >> wybor;
  cout << endl
       << endl
       << endl;
}

#define PLIK_WLASCIWY__GORA1 "dat/gora1.dat"
#define PLIK_WLASCIWY__GORA2 "dat/gora2.dat"
#define PLIK_WLASCIWY__GORA3 "dat/gora3.dat"
#define PLIK_WLASCIWY__PLASKOWYZ1 "dat/plaskowyz1.dat"

#define OBSTICLE_OBJECT1 "dat/objectSSS.dat"
#define OBSTICLE_OBJECT2 "dat/objectTTT.dat"
#define OBSTICLE_OBJECT3 "dat/objectRRR.dat"

/**
 * @brief Main function where all the magic happens :))
 * 
 * @return int ;//
 */

int main()
{
  char choice;   //variable that holds choice of user
  char language; //variable that holds choice of a language
  drone Drone;   //variable with our drone :)
  int whichdrone;
  char obsticle;
  vector3d scale;
  vector3d O_location;
  std::string nname = "obstacle";
  int O_number = 0;
  // char name;
  // char dat='dat/';
  // const char *DAT=&dat;
  scene DDrones;
  vector3d position;          //variable with coordinates
  scene actualscene;          //scene variable ;//
  double distance, direction; //variables that hold distance and direction of drone's movement

  actualscene.Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);

  actualscene.Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_KORPUS);
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR1);
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR2);
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR3);
  actualscene.Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR4);

  actualscene.Lacze.ZmienTrybRys(PzG::TR_3D);
  actualscene.Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.

  actualscene.Lacze.UstawZakresX(0, 200);
  actualscene.Lacze.UstawZakresY(0, 200);
  actualscene.Lacze.UstawZakresZ(0, 120);

  DDrones.drones[0].location[0] = 40;
  DDrones.drones[0].location[1] = 40;
  DDrones.drones[0].location[2] = 0;

  DDrones.drones[1].location[0] = 100;
  DDrones.drones[1].location[1] = 150;
  DDrones.drones[1].location[2] = 0;

  actualscene.obstacles.push_back(std::make_shared<drone>(DDrones.drones[0]));
  actualscene.obstacles.push_back(std::make_shared<drone>(DDrones.drones[1]));
  actualscene._drones.push_back(std::make_shared<drone>(DDrones.drones[0]));
  actualscene._drones.push_back(std::make_shared<drone>(DDrones.drones[1]));

  language = 'e'; //starting language

  actualscene.Lacze.UstawRotacjeXZ(64, 65); // Tutaj ustawiany jest widok

  if (!Drone.PrzemiescDrona(0, DDrones.drones[0].location, 1))
  {
    return 0;
  }
  if (!Drone.PrzemiescDrona(0, DDrones.drones[1].location, 2))
  {
    return 0;
  }
  actualscene.Lacze.Rysuj();

  while (choice != 'k') // converter for program working duration
  {
    if (language == 'e')
      menuE(choice);

    if (language == 'p') //stage of language choice
      menuP(choice);

    if (language == 'c')
      menuC(choice);

    switch (choice) //switch function that depends on the user's choice
    {

    case 'l':
      if (language == 'p') //Polish interface
      {
        cout << "Ktorym dronem chcesz polatac? (1 lub 2)" << endl;
        cin >> whichdrone;

        cout << "Podaj kierunek (w stopniach) w ktorym ma odleciec dron :" << endl;
        cin >> direction;

        cout << "Podaj odleglosc na jaka ma odleciec dron :" << endl; //stage of saving user's choises to variables
        cin >> distance;

        actualscene.Lacze.Rysuj(); //drawing a scene with drones
        cin.ignore(10000, '\n');

        if (!actualscene.DodajTrasePrzelotu(DDrones.drones[whichdrone - 1].location, distance, direction)) //drawing drone's fly-way
          return 1;
        actualscene.Lacze.Rysuj();

        cout << "Nacisnij ENTER, aby wykonac animacje lotu drona " << flush;
        cin.ignore(10000, '\n');
        if (!actualscene.AnimacjaLotuDrona(direction, distance, DDrones.drones[whichdrone - 1], whichdrone)) //drone flying animation
          return 1;

        cout << endl
             << "Nacisnij ENTER, aby usunac sciezke ... " << flush;
        cin.ignore(10000, '\n'); //deleting drone's fly-way

        actualscene.Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
        actualscene.Lacze.Rysuj();

        cout << "Nacisnij ENTER, aby zakonczyc ... " << flush;
        cin.ignore(10000, '\n'); //finishing a flight
      }

      else if (language == 'e') //English interface
      {
        cout << "Which drone you want to fly? (1 or 2)" << endl;
        cin >> whichdrone;

        cout << "Type a direction (in degrees) that you want your drone to go :" << endl;
        cin >> direction;

        cout << "Type a distance that you want your drone to make :" << endl; //stage of saving user's choises to variables
        cin >> distance;

        actualscene.Lacze.Rysuj(); //drawing a scene with drones
        cin.ignore(10000, '\n');

        if (!actualscene.DodajTrasePrzelotu(DDrones.drones[whichdrone - 1].location, distance, direction)) //drawing drone's fly-way
          return 1;
        actualscene.Lacze.Rysuj();

        cout << "Press ENTER to see an animation of drone's flight ... " << flush;
        cin.ignore(10000, '\n');
        if (!actualscene.AnimacjaLotuDrona(direction, distance, DDrones.drones[whichdrone - 1], whichdrone)) //drone flying animation
          return 1;

        cout << endl
             << "Press ENTER, to delete drone's way-drawing ... " << flush;
        cin.ignore(10000, '\n'); //deleting drone's fly-way

        actualscene.Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
        actualscene.Lacze.UsunNazwePliku("dat/AdditionalWayDrawing.dat");
        actualscene.Lacze.Rysuj();

        cout << "Press ENTER, to finish a flight ... " << flush;
        cin.ignore(10000, '\n'); //finishing a flight
      }

      else if (language == 'c') //Czech interface
      {
        cout << "Jakým dronem chcete létat? (1 nebo 2)" << endl;
        cin >> whichdrone;

        cout << "Zadejte směr (ve stupních), kterým chcete, aby dron odletěl :" << endl;
        cin >> direction;

        cout << "Zadejte vzdálenost, kterou má dron odletět :" << endl; //stage of saving user's choises to variables
        cin >> distance;

        actualscene.Lacze.Rysuj(); //drawing a scene with drones
        cin.ignore(10000, '\n');

        if (!actualscene.DodajTrasePrzelotu(DDrones.drones[whichdrone - 1].location, distance, direction)) //drawing drone's fly-way
          return 1;
        actualscene.Lacze.Rysuj();
        cout << "Klikněte na ENTER, můžete letět s dronem " << flush;
        cin.ignore(10000, '\n');
        if (!actualscene.AnimacjaLotuDrona(direction, distance, DDrones.drones[whichdrone - 1], whichdrone)) //drone flying animation
          return 1;

        cout << endl
             << "Klikněte na ENTER, odstraníte řádky ... " << flush;
        cin.ignore(10000, '\n'); //deleting drone's fly-way

        actualscene.Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
        actualscene.Lacze.Rysuj();

        cout << "Klikněte ENTER, pro dokončení ... " << flush;
        cin.ignore(10000, '\n'); //finishing a flight
      }

      break;

    case 'j': //stage of choosing a language

      cout << "What language are you choosing?   (E-English, P - Polski, C - čeština )" << endl;
      cin >> language;
      if (language != 'e' && language != 'p' && language != 'c')
      {
        cout << "Wrong choice! Zly wybor! Není dobrá volba!";
      }

      break;

    case 'm': //stage of displaying menu (depends on language chosen :))   )

      if (language == 'E')
        menuE(choice);

      if (language == 'P')
        menuP(choice);

      if (language == 'C')
        menuC(choice);

      break;

    case 's': //stage of displaying all drones location
      cout << "1 Drone" << endl;
      cout << DDrones.drones[0].location << endl;
      cout << "2 Drone" << endl;
      cout << DDrones.drones[1].location << endl;
      break;
    case 'a': //stage of adding obstacles to a scene
      ++O_number;
      cout << "(t - table-land, s - sharp-top-hill, r - ridge-hill)" << endl;
      cin >> obsticle;

      if (obsticle == 't' || obsticle == 's' || obsticle == 'r')
      {
        cout << "Enter scale (X,Y,Z)" << endl;
        cin >> scale;
        cout << "Enter location (X,Y,Z)" << endl;
        cin >> O_location;
        
        switch (obsticle)
        {
        case 't':
          actualscene.AddTable(scale, O_location, O_number, nname); //option of adding tableland as a obstacle
          break;

        case 's':
          actualscene.AddSharp(scale, O_location, O_number, nname); //option of adding tableland as a obstacle
          break;

        case 'r':
          actualscene.AddRidge(scale, O_location, O_number, nname); //option of adding tableland as a obstacle
          break;

        default:

          break;
        }
      }
      else 
      {
        cout << "Wrong option!" << endl;                  //assertion
      }
      break;
    case 'd':
      actualscene.Lacze.Rysuj(); //stage of displaying scene in GNUplot
      break;
    case 'u': //stage of removing a choosen obstacle
      actualscene.RemoveObstacle();
      --O_number;
      break;
    case 'k':

      break;

    default:

      break;
    }
  }
}
