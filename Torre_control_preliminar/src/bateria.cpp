#include "bateria.h"
#include "msg.h"

void Bateria::descargaBat (Msg &msg, double t)
{
    mVelDescg = msg.getVel()*0.1;
    if(mCarga > 0.)
        mCarga = mCarga - mVelDescg*t;
}
std::ostream & operator << (std::ostream &out, Bateria &bat)
{
    int carga = bat.getCarga();
    out<< "BATERIA:[";
    for(int i = 0; i<(carga/10); ++i)
    {
        std::cout<< "#";
    }
    for(int i = (carga/10); i < 10; ++i)
    {
        std::cout<< "-";
    }
    out<< "] ("<<carga<< "%)"<<std::endl;
    return out;

}
