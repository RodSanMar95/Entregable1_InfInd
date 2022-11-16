#ifndef SENSORALTURA_H
#define SENSORALTURA_H
#include "sensor.h"
#include "sensorvelocidad.h"


class SensorAltura: Sensor//herencia
{
    public:
        SensorAltura(double nAlt=0, int id=0): Sensor(id) {Alt = nAlt;}
        double getValue(void){return Alt;}
        void setValue(double nValue){Alt = nValue;}
        friend double operator + (SensorAltura &, SensorVelocidad &);
        friend bool operator > (SensorAltura &, double);
        friend bool operator < (SensorAltura &, double);
        friend double operator + (SensorAltura &, double );
        friend double operator - (SensorAltura &, double );
    protected:

    private:
        double Alt = 0.;
};

#endif // SENSORALTURA_H
