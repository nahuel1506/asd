#include <iostream>
#include <string>
using namespace std;

struct Arista
{
    int origen;
    int destino;
    int peso;
    Arista *sig;
    Arista(int unOrigen, int unDestino, int unPeso) : origen(unOrigen), destino(unDestino), peso(unPeso), sig(0){};
    Arista(int unOrigen, int unDestino, int unPeso, Arista *unSig) : origen(unOrigen), destino(unDestino), peso(unPeso), sig(unSig){};
};

class MinHeap
{
private:
    Arista **arr;
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
        Arista* aux = this->arr[pos1];
        this->arr[pos1] = this->arr[pos2];
        this->arr[pos2] = aux;
    }

    void flotar(int pos)
    {
        // trato de flotar si no soy la raiz
        if (pos > 1)
        {
            int posPadre = padre(pos);
            if (this->arr[posPadre]->peso > this->arr[pos]->peso) //Si es mayor que 0 el segundo va antes
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

        // si tengo mis dos hijos
        if (posHijoIzq < primeroLibre && posHijoDer < primeroLibre)
        {
          int posHijoMenor = this->arr[posHijoIzq]->peso <= this->arr[posHijoDer]->peso ? posHijoIzq : posHijoDer;    
            if (this->arr[pos]->peso > this->arr[posHijoMenor]->peso )
            {
                intercambiar(pos, posHijoMenor);
                hundir(posHijoMenor);
            }
        }
        // si tengo solo hijo izquierdo
        else if (posHijoIzq < primeroLibre)
        {
            if (this->arr[pos]->peso > this->arr[posHijoIzq]->peso)
            {
                intercambiar(pos, posHijoIzq);
                hundir(posHijoIzq);
            }
        }
    }

public:
    MinHeap(int unaCapacidad) //la pos 0 no se usa
    {
        
        this->arr = new Arista*[unaCapacidad + 1];
        this->primeroLibre = 1;
        this->capacidad = unaCapacidad;
    }

    Arista* getTope()
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

    void insertar(Arista* dato)
    {
        if (!this->estaLleno())
        {
            this->arr[this->primeroLibre] = dato; //lo coloco en el primer lugar libre
            flotar(this->primeroLibre);
            this->primeroLibre++;
        }
    }

    Arista* getUltimo()
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