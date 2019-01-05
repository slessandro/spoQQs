#include <pattern.h>



wheel::Pattern::Pattern () :  iHoles_{1} , spokesPerBlock_{1} , lacing_{new int[iHoles_]} , pattern_{new int[spokesPerBlock_]}
{
    isOk_ = false;
}



bool wheel::Pattern::getOk()
{
    return isOk_;
}



int wheel::Pattern::getiHoles()
{
    return iHoles_;
}



int wheel::Pattern::getLacing(int index)
{
    if (index >= iHoles_) return 0;
    return lacing_[index];
}



int wheel::Pattern::modulus(int dividend, int divisor)
{
    int reminder;

    reminder = dividend % divisor;
    if (reminder < 0) reminder = reminder + divisor;

    return reminder;
}



void wheel::Pattern::setPattern()
{
    for (int i = 0 ; i < iHoles_ ; i++)
        {
        lacing_[i] = pattern_[modulus(i,spokesPerBlock_)];
        }
}



int wheel::Pattern::initPattern(int iHoles , int spokesPerBlock)
{
    if (iHoles <= 0) iHoles = 1;
    if (iHoles != iHoles_)
        {
        lacing_.reset(new int[iHoles]);
        for (int i = 0 ; i < iHoles ; i++)
            lacing_[i] = 0;
        }
    iHoles_ = iHoles;

    if (spokesPerBlock <= 0) spokesPerBlock = 1;
    if (spokesPerBlock > 10) spokesPerBlock = 10;
    if (spokesPerBlock != spokesPerBlock_)
        {
        for (int i = 0 ; i < spokesPerBlock ; i++)
            pattern_[i] = 0;
        }
    spokesPerBlock_ = spokesPerBlock;

    return spokesPerBlock_;
}



void wheel::Pattern::loadPattern(int* ppattern , bool radialSP)
{
    for (int i = 0 ; i < spokesPerBlock_ ; i++)
        pattern_[i] = *(ppattern+i) * (!radialSP);

    setPattern();
}



bool wheel::Pattern::check()
{
    int     counter;
    bool    isPassed;

    isPassed = true;
    for (int j = 0 ; j < spokesPerBlock_ ; j++)
        {
        counter = 0;
        for (int i = 0 ; i < spokesPerBlock_ ; i++)
            {
            if ( modulus(i+pattern_[i],spokesPerBlock_) == j) counter++;
            }
        if (counter > 1) isPassed = false;
        }

    if (iHoles_ % spokesPerBlock_ != 0) isPassed = false;

    isOk_ = isPassed;
    return isOk_;
}
