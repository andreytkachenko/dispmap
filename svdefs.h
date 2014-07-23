#ifndef SVDEFS_H
#define SVDEFS_H

#include <QDebug>

typedef unsigned int SvFrameId;

#define sign(a) (a == 0 ? 0 : (a > 0 ? 1 : -1))
#define max(a,b,c) (a > b ? (a > c ? a : c) : (b > c ? b : c))
#define min(a,b,c) (a < b ? (a < c ? a : c) : (b < c ? b : c))

#endif // SVDEFS_H
