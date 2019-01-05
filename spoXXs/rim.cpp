#include <math.h>

#include <rim.h>



wheel::Rim::Rim () : iHoles_{1} , arrayHoles_{new wheel::Hole[iHoles_]}
{
    label = "constructor";

    isGrouped = false;
    isGroupedAuto = false;
    isSwapped = false;
    holesPerGroupMan = 1;
    holesPerGroupAuto = 1;
    holesPerGroupShift = 0;
    rimAngle_ = 0.0;

    erd = 0.1;
    osb = 0.0;
    groupedHolesDistance = 0.01;
    spokeBedDistance = 0.0;
    weight = 0.0;
}



int wheel::Rim::getiHoles()
{
    return iHoles_;
}



float wheel::Rim::getRimAngle()
{
    return rimAngle_;
}



float wheel::Rim::getGroupedHolesAngle()
{
    return groupedHolesAngle_;
}



float wheel::Rim::calcBaseAngleHoles(std::string holeLabel, int holesPerG)
{
    int     i;

    float   pi =  3.1415927;
    float   angle;

    if (holesPerG <= 0)
        holesPerG =1;

    rimAngle_ = 2*pi/iHoles_;
    if (groupedHolesDistance > +erd) groupedHolesDistance =  erd;
    if (groupedHolesDistance < -erd) groupedHolesDistance = -erd;
    groupedHolesAngle_ = 2*asin(groupedHolesDistance/erd);

    for( i = 0; i < iHoles_ ; i++)
        {
        angle = i*rimAngle_ + ((i % holesPerG)-float(holesPerG-1)/2.0)*(groupedHolesAngle_-rimAngle_)*isGrouped;
        arrayHoles_[i].angle = angle;
        arrayHoles_[i].x = (erd/2)*cos(arrayHoles_[i].angle);
        arrayHoles_[i].y = (erd/2)*sin(arrayHoles_[i].angle);
        arrayHoles_[i].label = holeLabel;
        }

    rotateLeftArray ( holesPerGroupShift + holesPerGroupAutoShift , 1 );

    return holesPerG;
}



void wheel::Rim::rotateRim (float angle)
{
    if (angle == 0) return;
    for (int i=0 ; i<iHoles_ ; i++)
        {
        arrayHoles_[i].angle = arrayHoles_[i].angle + angle;
        arrayHoles_[i].x = (erd/2)*cos(arrayHoles_[i].angle);
        arrayHoles_[i].y = (erd/2)*sin(arrayHoles_[i].angle);
        }
}



void wheel::Rim::rotateLeftArray(int amount , bool zeroing)
{
    int     i;
    int     j;

    float   temporary;
    float   pi =  3.1415927;
    float   resetvalue = 0;

    amount = amount % iHoles_ ;
    if (amount<0) amount = iHoles_ + amount;

    if (zeroing) resetvalue = arrayHoles_[amount].angle;

    for( i = 0; i < iHoles_ ; i++)
        {
        temporary = arrayHoles_[i].angle - resetvalue;
        if (temporary < 0) temporary = 2*pi + temporary;
        arrayHoles_[i].temp = temporary;
        }

    for( i = 0; i < iHoles_ ; i++)
        {
        j = (i+amount) % iHoles_;
        arrayHoles_[i].angle = arrayHoles_[j].temp;
        arrayHoles_[i].x = (erd/2)*cos(arrayHoles_[i].angle);
        arrayHoles_[i].y = (erd/2)*sin(arrayHoles_[i].angle);
        }
}



void wheel::Rim::initRim(int iHoles)
{
    if (iHoles <= 0) return;
    if (iHoles != iHoles_) arrayHoles_.reset(new wheel::Hole[iHoles]);
    iHoles_ = iHoles;

    if (!isGrouped)
        calcBaseAngleHoles(label,1);
    else if (!isGroupedAuto)
        holesPerGroupMan = calcBaseAngleHoles(label,holesPerGroupMan);
    else
        holesPerGroupAuto = calcBaseAngleHoles(label,holesPerGroupAuto);
}



wheel::Hole wheel::Rim::getHole( int index )
{
    return arrayHoles_[index];
}




