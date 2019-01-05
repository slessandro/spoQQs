#ifndef WHEELBUILDER_H
#define WHEELBUILDER_H



namespace wheel
{
int     calcHolesPerGroupAuto       (int iHoles , int iHolesL);
int     calcHolesPerGroupAutoShift  (int iHoles , int iHolesL);
float   calcHubRimRelations         (wheel::Hub& hub , wheel::Rim& rim);
float   calcDisplacementZ           (int flange , float flangeWidth , bool isFront , float osb , bool isSwapped , float spokeBedDistance);
void    populateSpokes              (wheel::Hub& hub , wheel::Rim& rim , wheel::Spokes& spokes , wheel::Pattern& patternL , wheel::Pattern& patternR);
}

#endif // WHEELBUILDER_H
