#ifndef HUB_H
#define HUB_H

#include <flange.h>



namespace wheel
{
    class Hub;
}



class wheel::Hub
{

private:
    int                 iHoles_;
    int                 iHolesL_;
    int                 iHolesR_;
    int                 numGCD_;
    int                 numN_;
    int                 numQN_;

    float               holeZeroAngleR_;
    wheel::Flange       flangeL;
    wheel::Flange       flangeR;

public:
    std::string         label;
    bool                isFront;
    bool                isTiltAuto;
    float               flangesTilt;
    float               flangesTiltAuto;
    float               flangeThickness;
    float               old;
    float               weight;

    float               widthL;
    float               flangeDiameterL;
    float               holesDiameterL;
    float               holesOffsetL;
    bool                isStraightpullL;
    bool                isPairedL;
    bool                isRadialStraightpullL;
    bool                isHeadsAlternatingL;
    bool                isHeadsoutL;

    float               widthR;
    float               flangeDiameterR;
    float               holesDiameterR;
    float               holesOffsetR;
    bool                isStraightpullR;
    bool                isPairedR;
    bool                isRadialStraightpullR;
    bool                isHeadsAlternatingR;
    bool                isHeadsoutR;

    bool                isAlternativeCoupled;

public:
    Hub ();

    int                 getiHoles();
    int                 getiHolesL();
    int                 getiHolesR();
    float               getHoleZeroAngleR();
    int                 getGCD();
    int                 getN();
    int                 getQN();

private:
    void                calcHoleAssociation();
    float               calcHoleZeroAngleR();

public:
    void                setFlangesParameters();
    void                initFlanges(int iHoles , int iHolesL);
    void                setTilt(float tiltValue, bool autoValue);
    float               radialOffset(int flange);
    float               bracingParameter(int flange);
    wheel::Hole         getHole(int flange, int index);
};

#endif // HUB_H
