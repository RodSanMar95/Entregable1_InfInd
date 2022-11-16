#ifndef SENSORHORIZONTAL_H
#define SENSORHORIZONTAL_H
#include "sensor.h"
#include "sensorvelocidad.h"


class SensorHorizontal: Sensor //heremcia
{
    public:
        SensorHorizontal(double nHor=0, int id=0): Sensor(id) {Hor = nHor;}
        double getValue(void){return Hor;}
        void setValue(double nHor){Hor=nHor;}
        friend double operator + (SensorHorizontal &, SensorVelocidad &);
        friend bool operator > (SensorHorizontal &, double);
        friend double operator + (SensorHorizontal &, double);
        friend double operator - (SensorHorizontal &, double );
        friend bool operator < (SensorHorizontal &, double);

    protected:

    private:
        double Hor = 0;
};

#endif // SENSORHORIZONTAL_H
