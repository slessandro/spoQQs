#ifndef SPOKES_H
#define SPOKES_H

#include <iostream>
#include <memory>

#include <hole.h>
#include <spoke.h>



namespace wheel
{
    class Spokes;
}



class wheel::Spokes
{

private:
    int                             iHoles_;

    float                           weightPerMmL_;
    float                           spokeSectionL_;

    float                           weightPerMmR_;
    float                           spokeSectionR_;

public:
    float                           youngModulus;           //  GPa
    float                           specificVolume;         //  (mm^3)/g
    float                           forceNominal;           //  N

    float                           bracingParameterL;
    float                           radialOffsetL;
    float                           threadDiameterL;
    float                           packWeightL;
    float                           packLengthL;
    int                             packPcsL;
    std::string                     labelL;

    float                           bracingParameterR;
    float                           radialOffsetR;
    float                           threadDiameterR;
    float                           packWeightR;
    float                           packLengthR;
    int                             packPcsR;
    std::string                     labelR;

private:
    std::unique_ptr<wheel::Spoke[]> arraySpokes_;

public:
    Spokes(std::string str1 = "" , std::string str2 = "");

private:
    void                            addSpecs();

public:
    void                            initSpokes(int iHoles);
    void                            loadSpoke(int index, int indexRim , wheel::Hole holeRim , int flange , int indexFlange , wheel::Hole holeHub, float z);
    void                            calcSpokes();
    wheel::Spoke                    getSpoke(int index);
};

#endif // SPOKES_H
