#include <wheel_define.h>

#include <math.h>
#include <hole.h>
#include <hub.h>
#include <rim.h>
#include <spokes.h>
#include <pattern.h>
#include <iomanip>
#include <cstring>



namespace wheel
{



int modulus(int dividend, int divisor)
{
    int reminder;

    reminder = dividend % divisor;
    if (reminder < 0) reminder = reminder + divisor;

    return reminder;
}



int calcHolesPerGroupAuto (int iHoles , int iHolesL)
{
    // call only after hub initialization
    int     gcd = iHoles;
    int     b = iHolesL;
    int     reminder;

    while( b != 0 )
        {
        reminder = gcd % b;
        gcd = b;
        b = reminder;
        }

    return ( iHoles / gcd );
}



int calcHolesPerGroupAutoShift (int iHoles , int iHolesL)
{
    // call only after hub initialization
    int     iHolesR = iHoles - iHolesL;
    int     gcd = iHoles;
    int     tmp = iHolesL;
    int     rem;
    int     sign;

    while( tmp != 0 )
        {
        rem = gcd % tmp;
        gcd = tmp;
        tmp = rem;
        }

    iHolesL = iHolesL / gcd;
    iHolesR = iHolesR / gcd;

    sign = ((iHolesR-iHolesL) > 0) - ((iHolesR-iHolesL) < 0);

    return sign*( (abs(iHolesR-iHolesL)+1) / 2 );
}



float calcHubRimRelations (wheel::Hub& hub , wheel::Rim& rim)
{
    // call only after rim initialization
    int     i;
    int     j;

    int     iHoles;
    int     iHolesL;
    int     iHolesR;

    float   angle;
    float   autoTilt;
    float   pi = 3.1415927;
    float   dp;
    float   a;
    float   b;
    float   diff;

    iHoles  = hub.getiHoles();
    iHolesL = hub.getiHolesL();
    iHolesR = hub.getiHolesR();

    dp = 2.0*pi;

    angle = 0;
    for ( i=0 ; i<iHolesL ; i++)
        {
        j = hub.getHole(LEFT,i).associated;
        a = rim.getHole(j).angle;
        while (a < 0)
            a = a + dp;
        while (a >= dp)
            a = a - dp;
        b = hub.getHole(LEFT,i).angle;
        while (b < 0)
            b = b + dp;
        while (b >= dp)
            b = b - dp;
        diff = a - b;
        diff = diff - dp*int(diff/pi);
        angle = angle + diff;
        }
    angle = angle/iHolesL;

    rim.rotateRim (-angle);

    angle = 0;
    for ( i=0 ; i<iHolesR ; i++)
        {
        j = hub.getHole(RIGHT,i).associated;
        a = rim.getHole(j).angle;
        while (a < 0)
            a = a + dp;
        while (a >= dp)
            a = a - dp;
        b = hub.getHole(RIGHT,i).angle;
        while (b < 0)
            b = b + dp;
        while (b >= dp)
            b = b - dp;
        diff = a - b;
        diff = diff - dp*int(diff/pi);
        angle = angle + diff;
        }
    autoTilt = angle/iHolesR;

    hub.setTilt(autoTilt,AUTO);

    angle = 0;
    for ( i=0 ; i<iHolesL ; i++)
        {
        j = hub.getHole(LEFT,i).associated;
        a = rim.getHole(j).angle;
        while (a < 0)
            a = a + dp;
        while (a >= dp)
            a = a - dp;
        b = hub.getHole(LEFT,i).angle;
        while (b < 0)
            b = b + dp;
        while (b >= dp)
            b = b - dp;
        diff = a - b;
        diff = diff - dp*int(diff/pi);
        angle = angle + diff;
        }
    for ( i=0 ; i<iHolesR ; i++)
        {
        j = hub.getHole(RIGHT,i).associated;
        a = rim.getHole(j).angle;
        while (a < 0)
            a = a + dp;
        while (a >= dp)
            a = a - dp;
        b = hub.getHole(RIGHT,i).angle;
        while (b < 0)
            b = b + dp;
        while (b >= dp)
            b = b - dp;
        diff = a - b;
        diff = diff - dp*int(diff/pi);
        angle = angle + diff;
        }
    angle = angle/iHoles;

    rim.rotateRim (-angle);

    return autoTilt;
}



float calcDisplacementZ(int flange , float flangeWidth , bool isFront , float osb , bool isSwapped , float spokeBedDistance)
{
    if (!isFront)
        osb = -osb;

    if (flange == LEFT)
        flangeWidth = flangeWidth + osb;
    else
        flangeWidth = flangeWidth - osb;

    if (isSwapped)
        spokeBedDistance = -spokeBedDistance;

    flangeWidth = flangeWidth - (spokeBedDistance/2);

    return flangeWidth;
}



void populateSpokes (wheel::Hub& hub , wheel::Rim& rim , wheel::Spokes& spokes , wheel::Pattern& patternL , wheel::Pattern& patternR)
{
    int             holesL;
    int             holesR;

    float           z;

    int             j;
    int             k;

    wheel::Hole     hubHole;
    wheel::Hole     rimHole;


    holesL = hub.getiHolesL();
    holesR = hub.getiHolesR();

    z = calcDisplacementZ(LEFT  , hub.widthL , hub.isFront , rim.osb , rim.isSwapped , rim.spokeBedDistance);
    for (int i = 0 ; i < holesL ; i++ )
        {
        k = patternL.getLacing(i);
        j = modulus(i+k , holesL);
        j = hub.getHole(LEFT , j).associated;

        hubHole = hub.getHole(LEFT ,i);
        rimHole = rim.getHole(j);

        spokes.loadSpoke(i , j , rimHole , LEFT , i , hubHole , z);
        }

    z = calcDisplacementZ(RIGHT , hub.widthR , hub.isFront , rim.osb , rim.isSwapped , rim.spokeBedDistance);
    for (int i = 0 ; i < holesR ; i++ )
        {
        k = patternR.getLacing(i);
        j = modulus (i+k , holesR);
        j = hub.getHole(RIGHT, j).associated;

        hubHole = hub.getHole(RIGHT ,i);
        rimHole = rim.getHole(j);

        spokes.loadSpoke(i+holesL , j , rimHole , RIGHT , i , hubHole , z);
        }
}



}
