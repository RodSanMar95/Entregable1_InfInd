/*#include <math.h>
#include <deque>
#include <vector>

#include "sensor.h"
#include "drone.h"
#include "colalim.h"
#include "msg.h"
#include "bateria.h"
#include "sensorvelocidad.h"
#include "sensoraltura.h"
#include "sensorhorizontal.h"*/
#include "drone.h"

const int Tiempo_Muestreo = 10;

Drone::Drone(ColaLim<Msg> *nPtr = nullptr, Bateria nBateria=Bateria(100,1.), SensorAltura nAlt=SensorAltura (0.,0), SensorVelocidad nVel =SensorVelocidad(0.,0), SensorHorizontal nHor = SensorHorizontal(0.,0), bool nDronEncendido = false)
{
    mPtr = nPtr;
    mBateria = nBateria;
    mAlt = nAlt;
    mVel = nVel;
    mHor = nHor;
    mDronEncendido = nDronEncendido;

}
void Drone::simula_altura(int tMuest, Msg &msg)
{
    mVel = msg.getVel();
    if(mAlt<msg.getAlt())
    {
        double val = mAlt + mVel*tMuest;
        mAlt.setValue(val);
    }
    else
    {
        double val = mAlt - mVel*tMuest;
        mAlt.setValue(val);
    }

    if(fabs(mAlt-msg.getAlt())<mVel*tMuest)
    {
        mAlt.setValue(msg.getAlt());
    }

}
void Drone::simula_horiz(int tMuest, Msg &msg)
{
    mVel = msg.getVel();
    if(mHor<msg.getHor())
    {
        double val = mHor + mVel*tMuest;
        mHor.setValue(val);

    }
    else
    {
        double val;
        val = mHor - mVel*tMuest;
        mHor.setValue(val);
    }

    if(fabs(mHor-msg.getHor())<mVel*tMuest)
    {
        mHor.setValue(msg.getHor());
    }

}
std::ostream & operator<< (std::ostream &out, Drone &drone)
{
    out << "POSICION: (" << drone.getAlt().getValue() << ", " << drone.getVel().getValue() << ", " << drone.getHor().getValue() << ")";
    return out;
}
Msg Drone::despegue(void)
{
    double altura = 1;

    std::cout<<std::endl;
    std::cout<< "El dron despeguara y ascendera 1 metro."<<std::endl;
    std::cout<<std::endl;

    Msg msg(altura, 0.15, 0);

    return msg;
}
void Drone::info_dron(void)
{
  //std::vector<int> p;
    std::vector<Sensor *> v;
    Sensor *Palt = (Sensor *)&mAlt;
    v.push_back(Palt);
    Sensor *Pvel = (Sensor *)&mVel;
    v.push_back(Pvel);
    Sensor *Phor = (Sensor *)&mHor;
    v.push_back(Phor);

    std::cout<< "Identificadores de los Sensores: ";
    for(auto elem: v)
    {
        std::cout<< elem->getID()<< " ";
    }
    std::cout<<std::endl;

    std::cout<< "Estado: ";
    if(mDronEncendido)
        std::cout<< "Encendido"<<std::endl;
    else
        std::cout<< "Apagado"<<std::endl;
    std::cout<< "Altura: "<<mAlt.getValue()<<std::endl;
    std::cout<< "Ultima velocidad: "<<mVel.getValue()<<std::endl;
    std::cout<< "Posicion horizontal: "<<mHor.getValue()<<std::endl;
    std::cout<< "Numero de mensajes en cola: "<<mPtr->size()<<std::endl;

}



