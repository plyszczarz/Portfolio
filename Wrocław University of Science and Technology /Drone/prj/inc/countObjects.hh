#ifndef COUNTOBJECTS_HH
#define COUNTOBJECTS_HH


#include <iostream>


/**
 * @brief Class to count objects of desired type
 * 
 * @tparam Object object we choose to count
 */

template <class Object>
class Count
{
    static int created;
    static int TotalAmount;

public:
    Count()
    {
        ++created;
        ++TotalAmount;
    }

    Count(const Count &)
    {
        ++created;
        ++TotalAmount;
    };

    ~Count()
    {
        --TotalAmount;
    };

    static int howmanyCCC()
    {
        return created;
    }

    static int howmanyTTT()
    {
        return TotalAmount;
    }
};




template <class Object>
int Count<Object>::created;


template <class Object>
int Count<Object>::TotalAmount;

#endif