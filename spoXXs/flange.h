#ifndef FLANGE_H
#define FLANGE_H

#include <memory>
#include <hole.h>



namespace wheel 
{
    class Flange;
}



class wheel::Flange
{

private:
    int                             iHoles_;
    float                           flangeAngle_;
    float                           holesOffset_;
    float                           pairedHolesAngle_;
    bool                            isStraightpull_;
    bool                            isPaired_;
    bool                            isRadialStraightpull_;
    bool                            isAlternativeCoupled_;
    bool                            isHeadsAlternating_;
    bool                            isHeadsout_;

public:
    float                           flangeDiameter;
    float                           holesDiameter;
    float                           holeZeroAngle;
    float                           tilt;
    float                           thickness;
    std::string                     label;

private:
    std::unique_ptr<wheel::Hole[]>  arrayHoles_;

public:
    Flange ();

    void                            initHoles(int iHoles);
    int                             getiHoles();
    wheel::Hole                     getHole(int index);
    float                           getHolesOffset() const;
    void                            setHolesOffset(float holesOffset);
    float                           getFlangeAngle();
    float                           getPairedHolesAngle();

    void                            setStraightpull(bool isStraightpull);
    bool                            getStraightpull();
    void                            setPaired(bool isPaired);
    bool                            getPaired();
    void                            setRadialStraightpull(bool isRadialStraightpull);
    bool                            getRadialStraightpull();
    void                            setAlternativeCoupled(bool isAlternativeCoupled);
    bool                            getAlternativeCoupled();
    void                            setHeadsout(bool isHeadsout);
    bool                            getHeadsout();
    void                            setHeadsAlternating(bool isAlternating);
    bool                            getHeadsAlternating();

    float                           getRadialOffset();
    float                           getBracingParameters();
    void                            setTilt(float newTilt);
    void                            setAssociated(int index, int value);
    void                            calcBaseAngleHoles(std::string holeLabel);
};

#endif // FLANGE_H
