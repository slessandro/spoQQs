#include <math.h>

#include <spoke.h>



wheel::Spoke::Spoke(std::string label)
{
    flange = 0;
    nHub = 0;
    xHub = 0.0;
    yHub = 0.0;
    angleHub = 0.0;
    nRim = 0;
    xRim = 0.0;
    yRim = 0.0;
    angleRim = 0.0;
    zDisplacement = 0.0;

    bracingOffset = 1.0;
    radialOffset = 0.0;

    length_ = 0.0;
    realXcross_ = 0.0;
    bracingAngle_ = 0.0;
    ratio_ = 1;
    force_ = 1;
    modulus_ = 1;
    section_ = 1.0;
    elongation_ = 0.0;
    weight_ = 0.0;

    spokeLabel = label;
}



float wheel::Spoke::getLength() const
{
    return length_;
}



float wheel::Spoke::getRealXcross() const
{
    return realXcross_;
}



float wheel::Spoke::getBracingAngle() const
{
    return bracingAngle_;
}



float wheel::Spoke::getRatio() const
{
    return ratio_;
}



float wheel::Spoke::getForce() const
{
    return force_;
}



float wheel::Spoke::getModulus() const
{
    return modulus_;
}



float wheel::Spoke::getSection() const
{
    return section_;
}



float wheel::Spoke::getElongation() const
{
    return elongation_;
}



float wheel::Spoke::getWeight() const
{
    return weight_;
}



void wheel::Spoke::calcSpokeLenght()
{
    length_ =  sqrt(pow(xHub-xRim,2) + pow(yRim-yHub,2) + pow(zDisplacement,2)) + radialOffset;
}



void wheel::Spoke::calcSpokeRealX(float angleX)
{
    float   pi = 3.1415927;
    float   angle;

    angle = angleRim - angleHub;

    if (angle > +pi)
        angle = angle - 2*pi;

    if (angle < -pi)
        angle = angle + 2*pi;

    realXcross_ = (angle) / (2*angleX);
}



void wheel::Spoke::calcBracingAngle()
{
    float   pi = 3.1415927;
    bracingAngle_ =  (180.0/pi)*asin((zDisplacement+bracingOffset)/length_);
}



void wheel::Spoke::calcSpoke(int holes)
{
    float pi = 3.1415927;
    float crossAngle;

    calcSpokeLenght();
    calcBracingAngle();

    crossAngle = 2*pi / float(holes);

    calcSpokeRealX(crossAngle);
}



void wheel::Spoke::calcSpokeForce(float bracingMin , float tensionMax)
{
    float pi = 3.1415927;

    ratio_ = sin((pi/180.0) * bracingMin) / sin((pi/180.0) * bracingAngle_);
    force_ = ratio_ * tensionMax;
}



void wheel::Spoke::calcSpokeElongation(float modulus , float specificVol , float weightmm)
{
    modulus_ = modulus;
    weight_ = weightmm * length_;
    section_ = weightmm * specificVol;
    elongation_ = force_*length_/ (modulus * section_ * 1000.0);         // (F*l)/(Young*S)
}
