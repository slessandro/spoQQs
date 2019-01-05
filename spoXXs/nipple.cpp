#include <nipple.h>



wheel::Nipple::Nipple(std::string str1 , std::string str2)
{
    packWeightL = 0.0;
    packLengthL = 1.0;
    packPcsL = 1;
    labelL = str1;

    packWeightR = 0.0;
    packLengthR = 1.0;
    packPcsR = 1;
    labelR = str2;
}



float wheel::Nipple::totalWeightL() const
{
    return totalWeightL_;
}



float wheel::Nipple::totalWeightR() const
{
    return totalWeightR_;
}



void wheel::Nipple::calcNipples(int holes , int holesL)
{
    int holesR = holes - holesL;

    totalWeightL_ = (packWeightL / packPcsL) * holesL;
    totalWeightR_ = (packWeightR / packPcsR) * holesR;
}
