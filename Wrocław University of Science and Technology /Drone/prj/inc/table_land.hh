#ifndef TABLE_LAND_HH
#define TABLE_LAND_HH

#include <iostream>
#include "solid.hh"
#include <string>
#include "sceneObject.hh"



/**
 * @brief Class of obstacle "TableLand"
 * 
 * contains scale, location, number and name of a obstacle
 * 
 */

class tableLand : public solid , public SObject
{
    vector3d Oscale;
    vector3d Olocation;
    int OL_number;
    string name = "tableLand";

    public:

    tableLand(const char *file_Entry_name, vector3d scale, vector3d pos, const char *file_Exit_name, int O_number)
    {
        CreateHillTTT(file_Entry_name, scale, pos, file_Exit_name);
        OL_number = O_number; 
        Oscale = scale;
        Olocation = pos;
    }

    ~tableLand()
    {
        
    }

    bool CreateHillTTT(const char *file_Entry_name, vector3d scale, vector3d pos, const char *file_Exit_name);
    bool CreateHillTTT(istream &file_Entry_name, vector3d scale, vector3d pos, ostream &file_Exit_name);
    void Transform_a_pointTTT(vector3d &location, vector3d scale, vector3d trans);
    vector3d OLOCATION(){return Olocation;};
    vector3d OSCALE(){return Oscale;};
    double Checking(vector3d Olocation, vector3d Dlocation);
};



#endif