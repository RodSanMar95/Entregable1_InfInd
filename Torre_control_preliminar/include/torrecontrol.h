#ifndef TORRECONTROL_H
#define TORRECONTROL_H
#include "colalim.h"//le da igual si es mayuscula o minuscula para identificar el fichero
#include "msg.h"


class TorreControl
{
    private:                //Lo inicializamos como puntero nulo
        ColaLim<Msg> *mPtr = nullptr;//Puntero a elementos de la clase colalim
    public:
        TorreControl(ColaLim<Msg> *nPtr = nullptr):mPtr(nPtr) {};
        Msg simula();
        void MuestraMenuComandos(void);
        char introduzca_opcion(int &);
        void envia_msg(ColaLim<Msg> *);
};

#endif // TORRECONTROL_H
