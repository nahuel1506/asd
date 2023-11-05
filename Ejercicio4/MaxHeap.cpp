#include <iostream>
#include <string>
#include <cstring>
using namespace std;




class MaxHeap
{
private:
    string *arr;
    int primeroLibre;
    int capacidad;

    int izq(int pos)
    {
        return pos * 2;
    }

    int der(int pos)
    {
        return (pos * 2) + 1;
    }

    int padre(int pos)
    {
        return pos / 2;
    }

    void intercambiar(int pos1, int pos2)
    {
        string aux = this->arr[pos1];
        this->arr[pos1] = this->arr[pos2];
        this->arr[pos2] = aux;
    }

    void flotar(int pos)
    {
        // trato de flotar si no soy la raiz
        if (pos > 1)
        {
            int posPadre = padre(pos);
            if (this->arr[posPadre].compare(this->arr[pos])>0) //Si es mayor que 0 el segundo va antes
            {
                intercambiar(posPadre, pos);
                flotar(posPadre);
            }
        }
    }

    void hundir(int pos)
    {
        int posHijoIzq = izq(pos);
        int posHijoDer = der(pos);
        int posHijoMayor;

        // si tengo mis dos hijos
        if (posHijoIzq < primeroLibre && posHijoDer < primeroLibre)
        {
            if(this->arr[posHijoIzq].compare(this->arr[posHijoDer]) < 0){
               posHijoMayor = posHijoIzq;
            } else if(this->arr[posHijoIzq].compare(this->arr[posHijoDer]) > 0){
             posHijoMayor = posHijoDer;
            }
            
            if (this->arr[pos].compare(this->arr[posHijoMayor]) > 0 )
            {
                intercambiar(pos, posHijoMayor);
                hundir(posHijoMayor);
            }
        }
        // si tengo solo hijo izquierdo
        else if (posHijoIzq < primeroLibre)
        {
            if (this->arr[pos].compare(this->arr[posHijoIzq]) > 0)
            {
                intercambiar(pos, posHijoIzq);
                hundir(posHijoIzq);
            }
        }
    }

public:
    MaxHeap(int unaCapacidad) //la pos 0 no se usa
    {
        
        this->arr = new string[unaCapacidad + 1];
        this->primeroLibre = 1;
        this->capacidad = unaCapacidad;
    }

    string getTope()
    {
        return this->arr[1];
    }

    void eliminarTope()
    {
        if(!estaVacio()){
        this->arr[1] = this->arr[primeroLibre - 1];//pongo el último en la raiz
        this->primeroLibre--;
        hundir(1); //hundo la nueva raiz            
        }

    }

    void insertar(string dato)
    {
        if (!this->estaLleno())
        {
            this->arr[this->primeroLibre] = dato; //lo coloco en el primer lugar libre
            flotar(this->primeroLibre);
            this->primeroLibre++;
        }
    }

    string getUltimo()
    {
        return this->arr[primeroLibre - 1];
    }

    bool estaLleno()
    {
        return this->primeroLibre > this->capacidad;
    }

    bool estaVacio()
    {
        return this->primeroLibre == 1;
    }
};