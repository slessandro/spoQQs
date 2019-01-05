#include <wheel_define.h>

#include <math.h>

#include <hub.h>



wheel::Hub::Hub () : iHoles_{2} , iHolesL_{1} , iHolesR_{1} , isFront{1}
{
    label = "constructor";

    numGCD_ = 0;
    numN_ = 0;
    numQN_ = 0;
    holeZeroAngleR_ = false;

    isTiltAuto = false;
    flangesTilt = 0.0;
    flangesTiltAuto = 0.0;
    flangeThickness = 0.0;
    old = 0.0;
    weight = 0.0;

    widthL = 0.0;
    flangeDiameterL = 0.1;
    holesDiameterL = 0.0;
    holesOffsetL = 0.0;
    isStraightpullL = false;
    isPairedL = false;
    isRadialStraightpullL = false;
    isHeadsAlternatingL = false;
    isHeadsoutL = false;

    widthR = 0.0;
    flangeDiameterR = 0.1;
    holesDiameterR = 0.0;
    holesOffsetR = 0.0;
    isStraightpullR = false;
    isPairedR = false;
    isRadialStraightpullR = false;
    isHeadsAlternatingR = false;
    isHeadsoutR = false;

    isAlternativeCoupled = false;
}



int wheel::Hub::getiHoles()
{
    return iHoles_;
}



int wheel::Hub::getiHolesL()
{
    return iHolesL_;
}



int wheel::Hub::getiHolesR()
{
    return iHolesR_;
}



float wheel::Hub::getHoleZeroAngleR()
{
    return holeZeroAngleR_;
}



int wheel::Hub::getGCD()
{
    return numGCD_;
}



int wheel::Hub::getN()
{
    return numN_;
}



int wheel::Hub::getQN()
{
    return numQN_;
}




void wheel::Hub::calcHoleAssociation()
{
    float N = 0.1;
    int a = iHoles_;
    int b = iHolesL_;
    int reminder;

    while( b != 0 )
        {
        reminder = a % b;
        a = b;
        b = reminder;
        numGCD_ = a;
        }

    a = int(iHoles_/numGCD_);
    b = int(iHolesL_/numGCD_);
    reminder = 0;

    while( N != floor(N) )
        {
        N = float(a*(reminder+1)-1)/b;
        numN_ = int(N);
        numQN_ = int(N-reminder);
        reminder++;
        }

    for ( a = 0 ; a < iHolesL_; a++ )
        {
        b = a*float(iHoles_)/iHolesL_;
        flangeL.setAssociated(a , b);
        }

    for ( a = 0 ; a < iHolesR_; a++ )
        {
        b = ((a+numQN_)*float(iHoles_)/iHolesR_)-numN_;
        flangeR.setAssociated(a , b);
        }
}



float wheel::Hub::calcHoleZeroAngleR()
{
    int value;
    value = (flangeR.getHole(0).associated)-1;
    return flangeL.getHole(value).angle;
}



void wheel::Hub::setFlangesParameters()
{
    flangeL.flangeDiameter = flangeDiameterL;
    flangeL.holesDiameter = holesDiameterL;
    flangeL.setHolesOffset(holesOffsetL);
    flangeL.tilt = 0;
    flangeL.thickness = flangeThickness;
    flangeL.setStraightpull(isStraightpullL);
    flangeL.setPaired(isPairedL);
    flangeL.setRadialStraightpull(isRadialStraightpullL);
    flangeL.setHeadsAlternating(isHeadsAlternatingL);
    flangeL.setHeadsout(isHeadsoutL);

    isStraightpullL = flangeL.getStraightpull();
    isPairedL = flangeL.getPaired();
    isRadialStraightpullL = flangeL.getRadialStraightpull();
    isHeadsAlternatingL = flangeL.getHeadsAlternating();
    isHeadsoutL = flangeL.getHeadsout();
    holesOffsetL = flangeL.getHolesOffset();


    flangeR.flangeDiameter = flangeDiameterR;
    flangeR.holesDiameter = holesDiameterR;
    flangeR.setHolesOffset(holesOffsetR);
    flangeR.tilt = 0;
    flangeR.thickness = flangeThickness;
    flangeR.setStraightpull(isStraightpullR);
    flangeR.setPaired(isPairedR);
    flangeR.setRadialStraightpull(isRadialStraightpullR);
    flangeR.setHeadsAlternating(isHeadsAlternatingR);
    flangeR.setHeadsout(isHeadsoutR);

    isStraightpullR = flangeR.getStraightpull();
    isPairedR = flangeR.getPaired();
    isRadialStraightpullR = flangeR.getRadialStraightpull();
    isHeadsAlternatingR = flangeR.getHeadsAlternating();
    isHeadsoutR = flangeR.getHeadsout();
    holesOffsetR = flangeR.getHolesOffset();


    if ((isStraightpullL || isPairedL || isStraightpullR || isPairedR) && (!isRadialStraightpullL || !isRadialStraightpullR))
        {
        flangeL.setAlternativeCoupled(isAlternativeCoupled);
        flangeR.setAlternativeCoupled(isAlternativeCoupled);
        }
    else
        {
        isAlternativeCoupled = false;
        flangeL.setAlternativeCoupled(isAlternativeCoupled);
        flangeR.setAlternativeCoupled(isAlternativeCoupled);
        }
}



void wheel::Hub::initFlanges(int iHoles , int iHolesL)
{
    std::string     flangeLabel;

    if (isFront)
        flangeLabel = "Front";
    else
        flangeLabel = "Rear";

    if (iHoles <= 0) iHoles = 2;

    if (iHolesL <= 0) iHolesL = 1;
    if (iHolesL >= iHoles) iHolesL = iHoles - 1;

    iHoles_  = iHoles;
    iHolesL_ = iHolesL;
    iHolesR_ = iHoles_ - iHolesL_;

    flangeL.initHoles(iHolesL_);
    flangeR.initHoles(iHolesR_);
    calcHoleAssociation();

    flangeL.holeZeroAngle = 0.0;
    flangeL.calcBaseAngleHoles(flangeLabel + " Left");

    holeZeroAngleR_ = calcHoleZeroAngleR();
    flangeR.holeZeroAngle = holeZeroAngleR_;
    flangeR.calcBaseAngleHoles(flangeLabel + " Right");
}



void wheel::Hub::setTilt(float newTilt, bool autoTilt)
{
    if (autoTilt)
        flangesTiltAuto = newTilt;
    else
        flangesTilt = newTilt;

    if (isTiltAuto)
        flangeR.setTilt(flangesTiltAuto);
    else
        flangeR.setTilt(flangesTilt);
}



float wheel::Hub::radialOffset(int flange)
{
    if (flange == LEFT)
        return flangeL.getRadialOffset();
    return flangeR.getRadialOffset();
}



float wheel::Hub::bracingParameter(int flange)
{
    if (flange == LEFT)
        return flangeL.getBracingParameters();
    return flangeR.getBracingParameters();
}



wheel::Hole wheel::Hub::getHole(int flange, int index)
{
    if (flange == LEFT)
        return flangeL.getHole(index);
    else
        return flangeR.getHole(index);
}
