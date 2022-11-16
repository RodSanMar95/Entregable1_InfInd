#ifndef DRONE_H
#define DRONE_H

#include <deque>
#include <vector>
#include <math.h>

#include "globales.h"
#include "sensor.h"
#include "colalim.h"
#include "msg.h"
#include "bateria.h"
#include "sensoraltura.h"
#include "sensorvelocidad.h"
#include "sensorhorizontal.h"


class Drone
{
    private:
        ColaLim<Msg> *mPtr = nullptr;//Agregacion
        Bateria mBateria;//Composicion
        SensorAltura mAlt;
        SensorVelocidad mVel;
        SensorHorizontal mHor;
        bool mDronEncendido = false;


    public:
        Drone(ColaLim<Msg> *nPtr, Bateria nBateria, SensorAltura nAlt, SensorVelocidad nVel, SensorHorizontal nHor, bool nDronEncendido);
        ColaLim<Msg>* getPtr(void){return mPtr;}
        Bateria getBat(void){return mBateria;}
        SensorAltura getAlt(void){return mAlt;}
        SensorVelocidad getVel(void){return mVel;}
        SensorHorizontal getHor(void){return mHor;}
        bool getDronEncendido(void){return mDronEncendido;}
        void setPtr(ColaLim<Msg>* nPtr){mPtr=nPtr;}
        void setBat(Bateria nBateria){mBateria=nBateria;}
        void setAlt(SensorAltura nAlt){mAlt.setValue(nAlt.getValue());}
        void setVel(SensorVelocidad nVel){mVel.setValue(nVel.getValue());}
        void setHor(SensorHorizontal nHor){mHor.setValue(nHor.getValue());}
        void setDronEncendido(bool nDronEncendido){mDronEncendido=nDronEncendido;}
        void simula_altura(int, Msg &);
        void simula_horiz(int, Msg &);
        Msg despegue(void);
        void info_dron(void);


        friend std::ostream & operator<<(std::ostream &, Drone &);




};

#endif // DRONE_H
