#ifndef NIPPLE_H
#define NIPPLE_H

#include <iostream>



namespace wheel 
{
    class Nipple;
}



class wheel::Nipple
{

private:
    int             iHolesL_;
    int             iHolesR_;
    float           totalWeightL_;
    float           totalWeightR_;

public:
    float           packWeightL;
    float           packLengthL;
    int             packPcsL;
    std::string     labelL;

    float           packWeightR;
    float           packLengthR;
    int             packPcsR;
    std::string     labelR;

public:
    Nipple (std::string lbl1="" , std::string lbl2="");

    float   totalWeightL() const;
    float   totalWeightR() const;

    void    calcNipples(int holes , int holesL);
};

#endif  // NIPPLE_H
