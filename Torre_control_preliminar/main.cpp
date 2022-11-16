#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <unistd.h>

#include "msg.h"//incluimos la cabecera
#include "colalim.h"
#include "torrecontrol.h"
#include "drone.h"
#include "globales.h"
#include "bateria.h"
#include "sensoraltura.h"
#include "sensorvelocidad.h"
#include "sensorhorizontal.h"

using namespace std;

const int Tiempo_Muestreo = 10;
int avances_simulacion = 1;//cuenta el numero de avances que hacemos en la simulacion


template<typename T>
void aterriz_dron(Drone &, T);

template<typename T>
void print_time (T start, const int tMuestreo)//funcion de imprimir tiempo en simulaciones, sobrecarga de la primera
{
    T end = chrono::steady_clock::now();
    cout<< " Tiempo transcurrido: "<< chrono::duration_cast<chrono::seconds>(chrono::seconds(tMuestreo)+ end - start).count()<<" segundos"<<endl;
}

template<typename T>
void print_time (T start)//funcion inicial de imprimir tiempo
{
    T end = chrono::steady_clock::now();
    cout<< " Tiempo transcurrido: "<< chrono::duration_cast<chrono::seconds>(end - start).count()<<" segundos"<<endl;
}
template<typename T>
void print_time_avanzado (T start)//funcion de imprimir tiempo cuando ha habido simulaciones
{
    T end = chrono::steady_clock::now();
    cout<< " Tiempo transcurrido: "<< chrono::duration_cast<chrono::seconds>(chrono::seconds(Tiempo_Muestreo*avances_simulacion)+end - start).count()<<" segundos"<<endl;
}



int main()
{
    ColaLim<Msg> *Pcanal;
    Pcanal = new ColaLim<Msg>(10);
    TorreControl torre(Pcanal);
    Bateria bat(100, 1.);
    SensorAltura alt(0., 1);
    SensorVelocidad vel(0., 2);
    SensorHorizontal hor(0., 3);
    Drone drone(Pcanal, bat, alt, vel, hor, false);

    int cent_comandos = 0;
    auto start = chrono::steady_clock::now();
    char opcion;
    do
    {

        do
        {
            torre.MuestraMenuComandos();
            try
            {
                opcion = torre.introduzca_opcion(cent_comandos);
            }
            catch(erroresComandos error)
            {
                if(error == comando_erroneo)
                {
                    cout<<endl;
                    cerr << "ERROR. La opcion no introducida no es correcta"<<endl;
                    cout<<endl;
                }
            }

        }
        while(!cent_comandos);

        switch(opcion)
        {
        case 49:
        {
            if(drone.getDronEncendido()==false)
            {
                cout<<endl;
                cout<< "Encendiendo el motor..."<<endl;
                drone.setDronEncendido(true);
                cout<< "El vehiculo ha arrancado con exito."<<endl;
                print_time(start);
                cout<<endl;
            }
            else
            {
                cout<<endl;
                cerr<< "ERROR. El dron ya está encendido."<<endl;
                cout<<endl;
            }

            break;
        }
        case 50:
        {
            if(!(drone.getDronEncendido()))
            {
                cout<<endl;
                cerr<< "ERROR. El vehiculo no esta encendido."<<endl;
                cout<<endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                Msg msg = drone.despegue();
                drone.simula_altura(Tiempo_Muestreo, msg);
                bat = drone.getBat();
                bat.descargaBat(msg,Tiempo_Muestreo);
                drone.setBat(bat);
                cout<<drone<<endl;
                cout<< "El vehiculo ha despegado con exito."<<endl;
                print_time(start);
                cout<<endl;
            }
            break;
        }
        case 51:
        {
            if(!(drone.getDronEncendido()))
            {
                cout<<endl;
                cerr<< "ERROR. El vehiculo no esta encendido."<<endl;
                cout<<endl;
                exit(EXIT_FAILURE);
            }
            else if(drone.getAlt().getValue()<0.1)
            {
                cout<<endl;
                cerr<< "ERROR. El vehiculo no ha despeguado o no tiene altura, no puede volar a ras de suelo."<<endl;
                cout<<endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                torre.envia_msg(Pcanal);
                print_time(start);

            }
            break;
        }
        case 52:
        {
            if(drone.getBat().getCarga()<10)
            {
                cout<<endl;
                cerr<< "PELIGRO. La carga del dron esta por debajo de lo deseado\n";
                cerr<< "Procedemos al atterrizaje.."<<endl;
                aterriz_dron(drone,start);
                exit(EXIT_FAILURE);
            }
            else
            {
                if (Pcanal->empty())
                {
                    cerr<< "ERROR. No Hay mensajes en la cola. "<<endl;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    Msg msg;

                    msg = torre.simula();
                    while(msg.getAlt()!=drone.getAlt().getValue())
                    {
                        drone.simula_altura(Tiempo_Muestreo, msg);
                        bat = drone.getBat();
                        bat.descargaBat(msg,Tiempo_Muestreo);
                        drone.setBat(bat);
                        cout<<drone;
                        print_time(start, avances_simulacion*Tiempo_Muestreo);
                        avances_simulacion++;

                    }
                    while(msg.getHor()!=drone.getHor().getValue())
                    {
                        drone.simula_horiz(Tiempo_Muestreo, msg);
                        bat = drone.getBat();
                        bat.descargaBat(msg,Tiempo_Muestreo);
                        drone.setBat(bat);
                        cout<<drone;
                        print_time(start, avances_simulacion*Tiempo_Muestreo);
                        avances_simulacion++;
                    }
                    cout<<bat<<endl;
                }
            }

            break;
        }
        case 53:
        {
            cout<<endl;
            cout<< "Informacion del vehiculo." <<endl;
            drone.info_dron();
            print_time_avanzado(start);
            cout<<endl;
            break;
        }
        case 54:
        {
            if(!(drone.getDronEncendido()))
            {
                cout<<endl;
                cerr<< "ERROR. El vehiculo no esta encendido."<<endl;
                cout<<endl;
                exit(EXIT_FAILURE);
            }
            else if(drone.getAlt().getValue()<0.1)
            {
                cout<<endl;
                cerr<< "ERROR. El vehiculo no ha despeguado o no tiene altura, no puede volar a ras de suelo."<<endl;
                cout<<endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                aterriz_dron(drone,start);
            }
            break;
        }
        case 55:
        {
            if(drone.getAlt().getValue()!=0)
            {
                aterriz_dron(drone,start);
            }
            cout<<endl;
            cout<< "El programa va a finalizar... "<<endl;
            break;
        }

        }


        /*   for(int i=0; i<10; i++)
           {
               torre.simula();
               drone.simula(Tiempo_Muestreo);
           }*/

    }
    while(opcion != '7');

    print_time_avanzado(start);

    return 0;
}
template<typename T>
void aterriz_dron(Drone &drone, T start)
{
    Msg msg(0.,0.15,drone.getHor().getValue());
    Bateria bat;
    cout<<endl;
    cout<< "El vehiculo volvera a la pista de aterrizaje "<<endl;
    cout<<endl;
    while(msg.getAlt()!=drone.getAlt().getValue())
    {
        drone.simula_altura(Tiempo_Muestreo, msg);
        bat = drone.getBat();
        bat.descargaBat(msg,Tiempo_Muestreo);
        drone.setBat(bat);
        cout<<drone;
        print_time(start, avances_simulacion*Tiempo_Muestreo);
        avances_simulacion++;
    }
    while(msg.getHor()!=drone.getHor().getValue())
    {
        drone.simula_horiz(Tiempo_Muestreo, msg);
        bat = drone.getBat();
        bat.descargaBat(msg,Tiempo_Muestreo);
        drone.setBat(bat);
        cout<<drone;
        print_time(start, avances_simulacion*Tiempo_Muestreo);
        avances_simulacion++;
    }
    cout<<bat<<endl;
}

