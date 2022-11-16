#include "sensorhorizontal.h"

double operator + (SensorHorizontal &SHor, SensorVelocidad &Velocidad)
{
    return SHor.getValue() + Velocidad.getValue();
}

bool operator > (SensorHorizontal &SHor, double Hor)
{
    return SHor.getValue()>Hor;
}

double operator + (SensorHorizontal &SHor, double d)
{
    return SHor.getValue()+d;
}

double operator- (SensorHorizontal &SHor, double d)
{
    return SHor.getValue() - d;
}
bool operator < (SensorHorizontal &SHor, double Hor)
{
    return SHor.getValue()<Hor;
}
