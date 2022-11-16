#ifndef BATERIA_H
#define BATERIA_H
#include<iostream>
#include "msg.h"


class Bateria
{
    int mCarga;
    double mVelDescg;

    public:
        Bateria(int nCarga = 100, double nVelDescg = 1):mCarga(nCarga), mVelDescg(nVelDescg) {};
        int getCarga(void){return mCarga;}
        double getVelDescg(void){return mVelDescg;}
        void setCarga(int nCarga){mCarga=nCarga;}
        void setVelDescg(double nVelDescg){mVelDescg=nVelDescg;}
        void descargaBat (Msg &, double);
        friend std::ostream & operator << (std::ostream &, Bateria &);
};

#endif // BATERIA_H
