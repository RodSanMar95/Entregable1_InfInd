#ifndef SENSOR_H
#define SENSOR_H


class Sensor//clase abstracta
{
    public:
        Sensor(int nID = 0): mID(nID) {};
        int getID(void){return mID;}
        virtual double getValue(void) = 0;
        virtual void setValue(double nValue) = 0;


    protected:
        int mID;


    private:
};


#endif // SENSOR_H
