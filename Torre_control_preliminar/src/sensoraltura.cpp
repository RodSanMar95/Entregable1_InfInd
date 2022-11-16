#include "sensoraltura.h"

double operator + (SensorAltura &SAlt, SensorVelocidad &Velocidad)
{
    return SAlt.getValue() + Velocidad.getValue();
}

bool operator > (SensorAltura &SAlt, double Alt)
{
    return SAlt.getValue()>Alt;
}
bool operator < (SensorAltura &SAlt, double Alt)
{
    return SAlt.getValue()<Alt;
}
double operator + (SensorAltura &SAlt, double d)
{
    return SAlt.getValue()+d;
}
double operator - (SensorAltura &SAlt, double d)
{
    return SAlt.getValue()-d;
}
