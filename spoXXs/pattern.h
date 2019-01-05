#ifndef PATTERN_H
#define PATTERN_H

#include <iostream>
#include <memory>



namespace wheel
{
    class Pattern;
}



class wheel::Pattern
{

private:
    bool                        isOk_;
    int                         iHoles_;
    int                         spokesPerBlock_;
    std::unique_ptr<int[]>      lacing_;
    int*                        pattern_;

public:
    Pattern ();

    bool                        getOk();
    int                         getiHoles();
    int                         getLacing(int index);

private:
    int                         modulus (int dividend, int divisor);
    void                        setPattern();

public:
    int                         initPattern(int iHoles , int spokesPerBlock);
    void                        loadPattern(int* ppattern, bool radialSP);
    bool                        check();
};

#endif // PATTERN_H
