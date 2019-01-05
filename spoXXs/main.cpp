#include <wheel_define.h>

#include <iostream>
#include <math.h>

#include <hole.h>
#include <nipple.h>
#include <spoke.h>
#include <spokes.h>
#include <flange.h>
#include <hub.h>
#include <rim.h>
#include <pattern.h>
#include <wheel.h>
#include <wheelbuild.h>



int main(int argc, char *argv[])
{
    wheel::Wheel       wheel;

    if (wheel.commandLine(argc,argv) != 0) return 1;

    wheel.loadParameters();
    wheel.assessWheel(true,0.0);
    wheel.outputToScreen();
    wheel.outputToFile();
    wheel.saveParameters();
}
