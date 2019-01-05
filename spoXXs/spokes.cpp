#include <wheel_define.h>

#include <spokes.h>



wheel::Spokes::Spokes(std::string str1 , std::string str2) : iHoles_{1} , arraySpokes_{new wheel::Spoke[iHoles_]}
{
    weightPerMmL_ = 0.1;
    spokeSectionL_ = 1.0;

    weightPerMmR_ = 0.1;
    spokeSectionR_ = 1.0;

    youngModulus = 200;
    specificVolume = 120;
    forceNominal = 1200;

    bracingParameterL = 1.0;
    radialOffsetL = 1.0;
    threadDiameterL = 1.0;
    packWeightL = 1.0;
    packLengthL = 0.1;
    packPcsL = 1;
    labelL = str1;

    bracingParameterR = 1.0;
    radialOffsetR = 1.0;
    threadDiameterR = 1.0;
    packWeightR = 1.0;
    packLengthR = 0.1;
    packPcsR = 1;
    labelR = str2;
}



void wheel::Spokes::addSpecs ()
{
    weightPerMmL_  = packWeightL/(packPcsL*packLengthL);
    spokeSectionL_ = specificVolume*weightPerMmL_;

    weightPerMmR_  = packWeightR/(packPcsR*packLengthR);
    spokeSectionR_ = specificVolume*weightPerMmR_;
}



void wheel::Spokes::initSpokes(int iHoles)
{
    if (iHoles <= 0) return;
    if (iHoles != iHoles_) arraySpokes_.reset(new wheel::Spoke[iHoles]);
    iHoles_ = iHoles;

    addSpecs();
}



void wheel::Spokes::loadSpoke(int index , int indexRim , wheel::Hole holeRim , int flange , int indexFlange , wheel::Hole holeHub , float z)
{
    float       bracingOffset;
    float       radialOffset;

    std::string label;

    if (flange == LEFT)
        {
        label = labelL + " L";
        bracingOffset = bracingParameterL;
        radialOffset = radialOffsetL;
        }
    else
        {
        label = labelR + " R";
        bracingOffset = bracingParameterR;
        radialOffset = radialOffsetR;
        }

    arraySpokes_[index].spokeLabel    = label;
    arraySpokes_[index].bracingOffset = bracingOffset;
    arraySpokes_[index].radialOffset  = radialOffset;

    arraySpokes_[index].flange        = flange;
    arraySpokes_[index].nHub          = indexFlange;
    arraySpokes_[index].xHub          = holeHub.x;
    arraySpokes_[index].yHub          = holeHub.y;
    arraySpokes_[index].angleHub      = holeHub.angle;
    arraySpokes_[index].nRim          = indexRim;
    arraySpokes_[index].xRim          = holeRim.x;
    arraySpokes_[index].yRim          = holeRim.y;
    arraySpokes_[index].angleRim      = holeRim.angle;
    arraySpokes_[index].zDisplacement = z;
}



void wheel::Spokes::calcSpokes()
{
    float   minBracing;

    minBracing = 90.0;
    for (int i = 0 ; i < iHoles_; i++ )
        {
        arraySpokes_[i].calcSpoke(iHoles_);
        if (arraySpokes_[i].getBracingAngle() < minBracing)
            minBracing = arraySpokes_[i].getBracingAngle();
        }

    for (int i = 0 ; i < iHoles_; i++ )
        {
        arraySpokes_[i].calcSpokeForce(minBracing , forceNominal);
        if (arraySpokes_[i].flange == LEFT)
            arraySpokes_[i].calcSpokeElongation(youngModulus , specificVolume , weightPerMmL_);
        else
            arraySpokes_[i].calcSpokeElongation(youngModulus , specificVolume , weightPerMmR_);
        }
}



wheel::Spoke wheel::Spokes::getSpoke(int index)
{
    return arraySpokes_[index];
}
