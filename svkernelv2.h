#ifndef SVKERNELV2_H
#define SVKERNELV2_H

#include "svabstractkernel.h"

#define sign(a) (a == 0 ? 0 : (a > 0 ? 1 : -1))

class SvKernelV2: public SvAbstractKernel
{

private:
    unsigned short* m_figures = {
        0b000111000, // TYPE_0

        0b100011000, // TYPE_11_1
        0b110011000, // TYPE_22_2_1
        0b000110011, // TYPE_22_2_2
        0b000110001, // TYPE_33_3
        0b100010001, // TYPE_45

        0b010010001, // TYPE_56_1
        0b100110010, // TYPE_67_2_1
        0b010011001, // TYPE_67_2_2
        0b100010010, // TYPE_78_3
        0b010010010, // TYPE_90

        0b001010010, // TYPE_101_1
        0b001011010, // TYPE_112_2_1
        0b010110100, // TYPE_112_2_2
        0b010010100, // TYPE_123_3
        0b001010100, // TYPE_135

        0b000011100, // TYPE_146_1
        0b000011110, // TYPE_157_2_1
        0b011110000, // TYPE_157_2_2
        0b001110000, // TYPE_168_3
    };

public:
    enum FigureType {
        TYPE_NONE = 0,

        TYPE_0,     // 000
                    // 111
                    // 000

        TYPE_11_1,  // 100
                    // 011
                    // 000

        TYPE_22_2_1,// 110
                    // 011
                    // 000

        TYPE_22_2_2,// 000
                    // 110
                    // 011

        TYPE_33_3,  // 000
                    // 110
                    // 001

        TYPE_45,    // 100
                    // 010
                    // 001

        TYPE_56_1,  // 010
                    // 010
                    // 001
        TYPE_67_2_1,
        TYPE_67_2_2,
        TYPE_78_3,
        TYPE_90,
        TYPE_101_1,
        TYPE_112_2_1,
        TYPE_112_2_2,
        TYPE_123_3,
        TYPE_135,
        TYPE_146_1,
        TYPE_157_2_1,
        TYPE_157_2_2,
        TYPE_168_3
    };

    SvKernelV2();
    virtual ~SvKernelV2();
    void exec(int line) override;

    int max(int x, int y);
    unsigned int figureType(int x, int y, int level);
};

#endif // SVKERNELV2_H
