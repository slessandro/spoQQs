#include <math.h>

#include <flange.h>



wheel::Flange::Flange () : iHoles_{1} , arrayHoles_{new wheel::Hole[iHoles_]}
{
    flangeAngle_ = 0;
    pairedHolesAngle_ = 0;
    isStraightpull_ = false;
    isPaired_ = false;
    isRadialStraightpull_ = false;
    isAlternativeCoupled_ = false;
    isHeadsAlternating_= true;
    isHeadsout_ = false;

    flangeDiameter = 0.1;
    holesDiameter = 0;
    holesOffset_ = 0;
    holeZeroAngle = 0;
    tilt = 0;
    thickness = 0;
    label = "constructor";
}



void wheel::Flange::initHoles(int iHoles)
{
    if (iHoles <= 0) return;
    if (iHoles != iHoles_) arrayHoles_.reset(new wheel::Hole[iHoles]);
    iHoles_ = iHoles;
}



int wheel::Flange::getiHoles()
{
    return iHoles_;
}



wheel::Hole  wheel::Flange::getHole(int index)
{
    return arrayHoles_.get()[index];
}



float wheel::Flange::getFlangeAngle()
{
    return flangeAngle_;
}



float wheel::Flange::getHolesOffset() const
{
    return holesOffset_;
}



void wheel::Flange::setHolesOffset(float holesOffset)
{
    holesOffset_ = holesOffset;
}



float wheel::Flange::getPairedHolesAngle()
{
    return pairedHolesAngle_;
}



void wheel::Flange::setStraightpull(bool isStraightpull)
{
    isStraightpull_ = isStraightpull;

    if (isStraightpull_)
        {
        isPaired_ = false;
        pairedHolesAngle_ = 0;
        }
    else
        {
        isRadialStraightpull_= false;
        if (!isPaired_) isAlternativeCoupled_ = false;
        }
}



bool wheel::Flange::getStraightpull()
{
    return isStraightpull_;
}



void wheel::Flange::setPaired(bool isPaired)
{
    isPaired_ = isPaired;

    if (isPaired_)
        {
        pairedHolesAngle_ = asin(double(2.0*holesOffset_/flangeDiameter));
        if (isnan(pairedHolesAngle_))
            {
            holesOffset_ = 0.5*flangeDiameter*((holesOffset_ > 0) - (holesOffset_ < 0));
            pairedHolesAngle_ = (isPaired_)*asin(double((holesOffset_ > 0) - (holesOffset_ < 0)));
            }
        isStraightpull_ = false;
        isRadialStraightpull_ = false;
        }
    else
        {
        pairedHolesAngle_ = 0;
        if (!isStraightpull_) isAlternativeCoupled_ = false;
        }
}



bool wheel::Flange::getPaired()
{
    return isPaired_;
}



void wheel::Flange::setRadialStraightpull(bool isRadialStraightpull)
{
    isRadialStraightpull_ = isRadialStraightpull;

    if (!isStraightpull_)
        isRadialStraightpull_ = false;
}



bool wheel::Flange::getRadialStraightpull()
{
    return isRadialStraightpull_;
}



void wheel::Flange::setAlternativeCoupled(bool isAlternativeCoupled)
{
        isAlternativeCoupled_ = isAlternativeCoupled;
}



bool wheel::Flange::getAlternativeCoupled()
{
    return isAlternativeCoupled_;
}



void wheel::Flange::setHeadsout(bool isHeadsout)
{
    if (isHeadsAlternating_) isHeadsout = false;
    isHeadsout_ = isHeadsout;
}



bool wheel::Flange::getHeadsout()
{
    return isHeadsout_;
}



void wheel::Flange::setHeadsAlternating(bool isHeadsAlternating)
{
    isHeadsAlternating_ = isHeadsAlternating;
    if (isHeadsAlternating_)
        isHeadsout_ = false;
}



bool wheel::Flange::getHeadsAlternating()
{
    return isHeadsAlternating_;
}



float wheel::Flange::getRadialOffset()
{
    if (isStraightpull_)
        {
        if (isRadialStraightpull_)
            return 0;
        else
            return holesOffset_;
        }
    else
        return (-(holesDiameter)/2);
}



float wheel::Flange::getBracingParameters()
{
    if ( isStraightpull_ || isHeadsAlternating_ )
        return 0;
    else  if (isHeadsout_)
        return -(thickness+2)/2;
    else
        return  (thickness+2)/2;
}



void wheel::Flange::setTilt(float newTilt)
{
    float   pi = 3.1415927;
    float   angle;
    int     coupled = ( isStraightpull_ || isPaired_ ) && !isRadialStraightpull_;

    flangeAngle_ = 2*pi/iHoles_;
    pairedHolesAngle_ = (isPaired_)*asin(double(2.0*holesOffset_/flangeDiameter));
    if (isnan(pairedHolesAngle_))
        {
        holesOffset_ = 0.5*flangeDiameter*((holesOffset_ > 0) - (holesOffset_ < 0));
        pairedHolesAngle_ = (isPaired_)*asin(double((holesOffset_ > 0) - (holesOffset_ < 0)));
        }

    for(int i = 0; i < iHoles_; i++)
        {
        angle = newTilt + holeZeroAngle + ((coupled+1.0)*int((i+isAlternativeCoupled_)/(coupled+1))*flangeAngle_) + (2.0*((i+isAlternativeCoupled_)%2)*pairedHolesAngle_);
        arrayHoles_[i].angle = angle;
        arrayHoles_[i].x = (flangeDiameter/2)*cos(angle);
        arrayHoles_[i].y = (flangeDiameter/2)*sin(angle);
        }
}



void  wheel::Flange::setAssociated(int index , int value)
{
    arrayHoles_[index].associated = value;
}



void wheel::Flange::calcBaseAngleHoles(std::string holeLabel)
{
    setTilt (0);
    for(int i = 0; i < iHoles_; i++)
        {
        arrayHoles_[i].label = holeLabel;
        }
}

