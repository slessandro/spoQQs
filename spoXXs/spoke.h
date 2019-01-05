#ifndef SPOKE_H
#define SPOKE_H

#include <iostream>



namespace wheel 
{
    class Spoke;
}



class wheel::Spoke
{

public:
    int             flange;
    int             nHub;
    float           xHub;
    float           yHub;
    float           angleHub;
    int             nRim;
    float           xRim;
    float           yRim;
    float           angleRim;
    float           zDisplacement;

    float           bracingOffset;
    float           radialOffset;
    std::string     spokeLabel;

private:
    float           length_;
    float           realXcross_;
    float           bracingAngle_;
    float           ratio_;
    float           force_;
    float           modulus_;
    float           section_;
    float           elongation_;
    float           weight_;

public:
    Spoke (std::string label = "");

private:
    void            calcSpokeLenght();
    void            calcSpokeRealX(float angleX);
    void            calcBracingAngle();

public:
    float           getLength() const;
    float           getRealXcross() const;
    float           getBracingAngle() const;
    float           getRatio() const;
    float           getForce() const;
    float           getModulus() const;
    float           getSection() const;
    float           getElongation() const;
    float           getWeight() const;

    void            calcSpoke(int holes);
    void            calcSpokeForce(float bracingMax , float tensionMax);
    void            calcSpokeElongation(float modulus , float specificVol , float weightmm);
};

#endif  // SPOKE_H
