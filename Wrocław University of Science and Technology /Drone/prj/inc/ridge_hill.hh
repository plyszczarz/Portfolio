#ifndef RIDGE_HILL_HH
#define RIDGE_HILL_HH

#include <iostream>
#include "solid.hh"
#include "vector.hh"
#include "sceneObject.hh"



/**
 * @brief Class of obstacle "RidgeHill"
 * 
 * contains scale, location, number and name of a obstacle
 * 
 */

class ridge : public solid , public SObject
{
    vector3d Oscale;
    vector3d Olocation;
    int OL_number;
    string name = "ridge";

    public:

    ridge(const char *file_Entry_name, vector3d scale, vector3d pos, const char *file_Exit_name, int O_number)
    {
        CreateHillRRR(file_Entry_name, scale, pos, file_Exit_name);
        OL_number = O_number; 
        Oscale = scale;
        Olocation = pos;
    }

    ~ridge()
    {
        
    }


    bool CreateHillRRR(const char *file_Entry_name, vector3d scale, vector3d pos, const char *file_Exit_name);
    bool CreateHillRRR(istream &file_Entry_name, vector3d scale, vector3d pos, ostream &file_Exit_name);
    void Transform_a_pointRRR(vector3d &location, vector3d scale, vector3d trans);
    vector3d OLOCATION(){return Olocation;};
    vector3d OSCALE(){return Oscale;};
    double Checking(vector3d Olocation, vector3d Dlocation);
    

};



#endif