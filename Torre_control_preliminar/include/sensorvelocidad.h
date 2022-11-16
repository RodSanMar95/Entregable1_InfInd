#ifndef SENSORVELOCIDAD_H
#define SENSORVELOCIDAD_H
#include "sensor.h"
#include "sensorvelocidad.h"


class SensorVelocidad: Sensor//herencia
{
    public:
        SensorVelocidad(double nVel=0., int id=0): Sensor(id), Vel(nVel) {}
        double getValue(void){return Vel;}
        void setValue(double nVel){Vel = nVel;}
        friend double operator *(SensorVelocidad &, int );
        friend double operator + (SensorVelocidad &, double);
        friend bool operator > (SensorVelocidad &, double);
        friend bool operator < (SensorVelocidad &, double);

    protected:

    private:
        double Vel = 0;
};

#endif // SENSORVELOCIDAD_H
