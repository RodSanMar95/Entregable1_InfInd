#include "torrecontrol.h"
#include "globales.h"
#include <limits>

Msg TorreControl::simula()//Hay que poner la referencia a la clase porque estan en ficheros distintos
{
    if ((mPtr != nullptr) && !(mPtr->empty()))//Si no esta vacia la cola a la que yo accedo a traves del puntero
    {
        Msg msg = mPtr->pop();//procesamos el ultimo elemento de la cola apuntada por el puntero
        std::cout << msg <<std::endl;
        return msg;
    }
}
void TorreControl::MuestraMenuComandos(void)
{
    std::cout<< "------- VEHICULO AEREO NO TRIPULADO -----\n";
    std::cout<< "1.- Arranque del vehiculo\n";
    std::cout<< "2.- Despegue Vehiculo\n";
    std::cout<< "3.- Enviar mensaje a la cola\n";
    std::cout<< "4.- Simular mensaje\n";
    std::cout<< "5.- Solicitud de informacion sobre el estado/condicion del vehiculo e informacion captada por los sensores\n";
    std::cout<< "6.- Aterrizaje\n";
    std::cout<< "7.- Desconexion/apagado del vehiculo\n";


}

char TorreControl::introduzca_opcion(int &cent)
{
    char opcion;
    std::cout<< "Introduzca una opcion: ";
    std::cin>>opcion;
    if(!(opcion>48 && opcion <56))//codigos ascii entre 1 y 5
    {
        cent = 0;
        throw comando_erroneo;
    }

    cent = 1;
    return opcion;

}
void TorreControl::envia_msg(ColaLim<Msg> *Ptr)
{
    double altura, velocidad, horizontal;
    int cent = 0;
    do
    {
        std::cout<< "Introduce la altura a la que debemos llegar: ";
        std::cin>>altura;
        if(altura<0)
        {
            cent = 1;
            std::cout<<std::endl;
            std::cerr<< "ERROR. La altura ha de ser mayor que cero."<<std::endl;
            std::cout<<std::endl;
        }
    }while(cent);

    cent = 0;
    do
    {
        std::cout<< "Introduce la velocidad de desplazamiento: ";
        std::cin>>velocidad;
        if(altura<0)
        {
            cent = 1;
            std::cout<<std::endl;
            std::cerr<< "ERROR. La velocidad ha de ser mayor que cero."<<std::endl;
            std::cout<<std::endl;
        }
    }while(cent);

    std::cout<< "Indroduce la posicion horizontal a alcanzar: ";
    std::cin>>horizontal;

    Msg mensaje(altura,velocidad, horizontal);

    std::cout<<mensaje<<std::endl;
    Ptr ->put(mensaje);
    std::cout<< "Se ha enviado el mensaje a la cola de comandos con exito."<<std::endl;
    std::cout<<std::endl;

}
