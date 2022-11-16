#ifndef COLALIM_H
#define COLALIM_H

#include <deque>

#include "globales.h"
#include "msg.h"

//Como es una clase genérica hay que implementarla en el header, sin fichero de implementacion

template <typename T>//Afecta a toda la clase
class ColaLim
{
    std::deque<T> mCola;//ColaLim tiene un miembro que es una cola
    int mTamMax;//ColaLim tiene un entero que es el tamaño de la cola
public:
    ColaLim(int nTam):mTamMax(nTam) {}//CONSTRUCTOR asigno el elemento que recibo a mTam
                                //Si usas esta sitaxis hay que poner los corchetes al final.
    void put(T nElem);//introduce un elemento en la cola
    T pop(void);//elimina el ultimo elemento de la cola, devuelve el ultimo entero
    bool empty(){return mCola.empty();}//Devolvemos true si la cola de la clase esta vacia.
    int size(){return mCola.size();}
};

template <typename T>
void ColaLim<T>::put(T nElem)//hay que indicar que este metodo es de esta clase, porque puede haber otros que se llamen igual
{       //La clase es generica
    if(mCola.size()>= mTamMax)//Si vamos a meter un nuevo elemento y el tamañp de la cola es el maximo quitamos el ultimo
    {
        mCola.pop_back();
    }
    mCola.push_front(nElem);

}
template <typename T>
T ColaLim<T>::pop(void)
{
    T valor;

    if(mCola.empty())
        throw cola_vacia;

    valor = mCola.back();//guardamos el ultimo elemento para procesarlo
    mCola.pop_back();//eliminamos el ultimo elemento
    return valor;
}


#endif // COLALIM_H
