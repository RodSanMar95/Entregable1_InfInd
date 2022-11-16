#include "sensorvelocidad.h"

double operator *(SensorVelocidad &SVel, int t)
{
    return SVel.getValue() * static_cast<double>(t);
}
double operator + (SensorVelocidad &SVel, double d)
{
    return SVel.getValue()+d;
}
bool operator > (SensorVelocidad &SVel, double Vel)
{
    return SVel.getValue()>Vel;
}
bool operator < (SensorVelocidad &SVel, double Vel)
{
    return SVel.getValue()<Vel;
}
