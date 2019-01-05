#include <math.h>

#include <hole.h>



wheel::Hole::Hole(std::string str)
{
    associated = 0;
    x = 0.0;
    y = 0.0;
    angle = 0.0;
    temp = 0.0;

    label = str;
}
