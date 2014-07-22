#ifndef SVSIMPLEPOINT_H
#define SVSIMPLEPOINT_H

class SvSimplePoint
{
protected:
    int m_px, m_py, m_pz;

public:
    int x() {return m_px;}
    int y() {return m_py;}
    int z() {return m_pz;}

    int setX(int px) {return m_px = px;}
    int setY(int py) {return m_py = py;}
    int setZ(int pz) {return m_pz = pz;}



    SvSimplePoint();
};

#endif // SVSIMPLEPOINT_H
