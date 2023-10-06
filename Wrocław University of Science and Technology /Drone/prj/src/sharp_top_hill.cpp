#include "sharp_top_hill.hh"
#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;

/**
 * @brief Function which transforms coordinates of a single point due to given scale and translation
 * 
 * @param location parameter that contains point's coordinates
 * @param scale scale that you want to scale a point?
 * @param trans translation value 
 */

void sharp::Transform_a_pointSSS(vector3d &location, vector3d scale, vector3d trans)
{
    location[0] = scale[0]*location[0] +trans[0];
    location[1] = scale[1]*location[1] +trans[1];
    location[2] = scale[2]*location[2] +trans[2];
}

/**
 * @brief Function that creates a specific obsticle called sharp top hill, 
 * 
 * @param file_Entry_name file name from which function gets elementary coordinates to transform
 * @param scale scale that you want to scale a obstacle
 * @param pos translation value
 * @param file_Exit_name file name from which function sends transformend obstacle's coordinates
 * @return true returns true  if everything went okay
 * @return false returns flase if something went wrong 
 */


bool sharp::CreateHillSSS(istream &file_Entry_name, vector3d scale, vector3d pos, ostream &file_Exit_name)
{
  assert(file_Entry_name.good());
  assert(file_Exit_name.good());
  
  vector3d coords;

  for (unsigned int Ind_krawedz = 0; Ind_krawedz < 5; ++Ind_krawedz) {
    for (unsigned int Ind_wierz = 0; Ind_wierz < 4; ++Ind_wierz) {
      file_Entry_name >> coords;
      if (file_Entry_name.fail()) return false;

      
      if (coords[2] > 0.5) 
      {                                             // Tutaj realizowana jest deformacja
	  coords[0] = coords[1] = 0;
      } else if (coords[2] == 0.5) 
      {
        coords[0] /= 2;  coords[1] /= 2;
      }

      Transform_a_pointSSS(coords, scale, pos);

      file_Exit_name << coords;
      if (file_Exit_name.fail()) return false;
    }
    file_Exit_name << endl; // Dodatkowa linia oddzielająca krawędzie
  }
  return !file_Exit_name.fail();
}

/**
 * @brief Function that makes sure if every file was opened correctly
 * 
 * @param file_Entry_name file name from which function gets elementary coordinates to transform
 * @param scale scale that you want to scale a obstacle
 * @param pos translation value
 * @param file_Exit_name file name from which function sends transformend obstacle's coordinates
 * @return true returns true  if everything went okay
 * @return false returns flase if something went wrong 
 */


bool sharp::CreateHillSSS(const char *file_Entry_name, vector3d scale, vector3d pos, const char *file_Exit_name)
{
  ifstream  sfile_Entry_name(file_Entry_name);
  ofstream  sfile_Exit_name(file_Exit_name);

  if (!sfile_Entry_name.is_open()) {
    cerr << ":( Niepowiodlo sie otwarcie pliku: " << file_Entry_name << endl;
    return false;
  }
  if (!sfile_Exit_name.is_open()) {
    cerr << ":( Niepowiodlo sie otwarcie pliku: " << file_Exit_name << endl;
    return false;
  }
  
  return CreateHillSSS(sfile_Entry_name, scale, pos, sfile_Exit_name);
}


/**
 * @brief Virtual function that counts and returns distance between drone and obstacle centers
 * 
 * @param Olocation location of a obstacle  
 * @param Dlocation location of a drone
 * @return double metioned distance
 */

double sharp::Checking(vector3d Olocation, vector3d Dlocation)
{
    double colideDistance;

    colideDistance = sqrt(pow((Dlocation[0] - Olocation[0]), 2) + pow((Dlocation[1] - Olocation[1]), 2));

    return colideDistance;
}