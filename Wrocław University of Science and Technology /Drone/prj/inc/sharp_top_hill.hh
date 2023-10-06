#ifndef SHARP_TOP_HILL_HH
#define SHARP_TOP_HILL_HH

#include <iostream>
#include "solid.hh"
#include "vector.hh"
#include "sceneObject.hh"


/**
 * @brief Class of obstacle "SharpTopHill"
 * 
 * contains scale, location, number and name of a obstacle
 * 
 */

class sharp : public solid , public SObject
{
    vector3d Oscale;
    vector3d Olocation;
    int OL_number;
    string name = "sharp";

    public:

    sharp(const char *file_Entry_name, vector3d scale, vector3d pos, const char *file_Exit_name, int O_number)
    {
        CreateHillSSS(file_Entry_name, scale, pos, file_Exit_name);
        OL_number = O_number; 
        Oscale = scale;
        Olocation = pos;
    }

    ~sharp()
    {
        
    }

    bool CreateHillSSS(const char *file_Entry_name, vector3d scale, vector3d pos,const  char *file_Exit_name);
    bool CreateHillSSS(istream &file_Entry_name, vector3d scale, vector3d pos, ostream &file_Exit_name);
    void Transform_a_pointSSS(vector3d &location, vector3d scale, vector3d trans);
    vector3d OLOCATION(){return Olocation;};
    vector3d OSCALE(){return Oscale;};
    double Checking(vector3d Olocation, vector3d Dlocation);
};



#endif