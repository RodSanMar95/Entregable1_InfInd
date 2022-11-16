#include "msg.h"


std::ostream & operator<< (std::ostream &out, const Msg &msg)
{
    out << "MENSAJE: (" << msg.mAlt << ", " << msg.mVel << ", " << msg.mHor << ")";
    return out;
}
