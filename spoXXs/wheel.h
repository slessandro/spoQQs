#ifndef WHEEL_H
#define WHEEL_H

#include <hole.h>
#include <nipple.h>
#include <spoke.h>
#include <spokes.h>
#include <flange.h>
#include <hub.h>
#include <rim.h>
#include <pattern.h>



namespace wheel
{
    class Wheel;
}



class wheel::Wheel
{
protected:
    wheel::Hub          hub;
    wheel::Rim          rim;
    wheel::Pattern      patternL;
    wheel::Pattern      patternR;
    wheel::Spokes       spokes;
    wheel::Nipple       nipples;

    bool                isFirstRun;
    bool                isScreenOutput_;
    bool                isFileOutput_;

    float               meanAngleL_;
    float               meanAngleR_;
    float               meanForceL_;
    float               meanForceR_;
    float               weightSpokes_;
    float               weightNipples_;
    float               meanElongationL_;
    float               meanElongationR_;

    float               rotationAnglePrev_;

    std::string         input_;
    std::string         output_;

public:
    bool                isFront;
    int                 iHoles;
    int                 iHolesL;
    int                 iHolesR;
    int                 blockL;
    int                 schemeL[10];
    int                 blockR;
    int                 schemeR[10];

public:
    Wheel();

    void    setIsScreenOutput(bool isScreenOutput);
    void    setIsFileOutput(bool isFileOutput);
    void    assessWheel(bool isFromInit, float angle);
    void    saveParameters();
    void    loadParameters();
    void    outputToScreen();
    void    outputToFile();
    int     commandLine(int argC , char* argV[]);
    void    calcMeanValues();
};

#endif // WHEEL_H
