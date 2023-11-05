#include <iostream>
#include <cassert>
#include <string>
using namespace std;

struct Nodo
{
    int dato;
    Nodo *sig;
    Nodo() : dato(0), sig(NULL) {}
    Nodo(int d) : dato(d), sig(NULL) {}
};

class ColaInt
{
private:
    int cantElem;
    Nodo *primero;
    Nodo *ultimo;

public:
    ColaInt()
    {
        {
            this->primero = this->ultimo = NULL;
            this->cantElem = 0;
        }
    }

    void encolar(int e)
    {
        Nodo *aux = new Nodo(e);
        if (esVacia())
        {
            this->primero = aux;
            this->ultimo = aux;
        }
        else
        {
            this->ultimo->sig = aux;
            this->ultimo = aux;
        }
        this->cantElem++;
    }

    int principio()
    {
        if (!esVacia())
        {
            return this->primero->dato;
        }
        return 0;
    }

    void desencolar()
    {
        if (!esVacia())
        {
            Nodo *aux = this->primero;
            this->primero = this->primero->sig;
            delete aux;
            this->cantElem--;
            if (this->primero == NULL)
            {
                this->ultimo = NULL;
            }
        }
    }

    bool esVacia()
    {
        return this->cantElem == 0;
    }

    unsigned int cantidadElementos()
    {
        return this->cantElem;
    }
};