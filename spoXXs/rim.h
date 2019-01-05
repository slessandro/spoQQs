#ifndef RIM_H
#define RIM_H

#include <memory>
#include <hole.h>



namespace wheel
{
    class Rim;
}



class wheel::Rim
{

private:
    int                             iHoles_;
    float                           rimAngle_;
    float                           groupedHolesAngle_;

public:
    bool                            isFront;
    bool                            isGrouped;
    bool                            isGroupedAuto;
    bool                            isSwapped;
    int                             holesPerGroupMan;
    int                             holesPerGroupAuto;
    int                             holesPerGroupShift;
    int                             holesPerGroupAutoShift;
    float                           erd;
    float                           osb;
    float                           groupedHolesDistance;
    float                           spokeBedDistance;
    float                           weight;
    std::string                     label;

private:
    std::unique_ptr<wheel::Hole[]>  arrayHoles_;

public:
    Rim ();

    int                             getiHoles();
    float                           getRimAngle();
    float                           getGroupedHolesAngle();

private:
    float                           calcBaseAngleHoles( std::string holeLabel , int holesPerG );

public:
    void                            rotateRim (float angle);
    void                            rotateLeftArray ( int amount , bool zeroing );
    void                            initRim ( int iHoles );
    wheel::Hole                     getHole ( int index );
};

#endif // RIM_H
