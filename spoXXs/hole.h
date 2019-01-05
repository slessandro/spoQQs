#ifndef HOLE_H
#define HOLE_H

#include <iostream>



namespace wheel 
{
    class Hole;
}



class wheel::Hole
{

public:
    int             associated;
    float           x;
    float           y;
    float           angle;
    float           temp;
    std::string     label;

    Hole (std::string str = "");
};

#endif // HOLE_H
