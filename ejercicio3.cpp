#include <iostream>
#include <cassert>
#include <string>
using namespace std;

struct nodoHeap
{
    int urgencia;
    int tiempo;
    int paciente;
};

class MaxHeap
{
private:
    nodoHeap **elementos;
    int capacidad;
    int primeroLibre;

    void intercambiar(int x, int y)
    {
        nodoHeap *aux = this->elementos[x];
        this->elementos[x] = this->elementos[y];
        this->elementos[y] = aux;
    }

    int padre(int pos)
    {
        return pos / 2;
    }

    int posIzq(int pos)
    {
        return pos * 2;
    }
    int posDer(int pos)
    {
        return pos * 2 + 1;
    }

    bool vaAntes(int pos, int posPadre)
    {
        if (this->elementos[pos]->urgencia > this->elementos[posPadre]->urgencia)
        {
            return true;
        }
        else if (this->elementos[pos]->urgencia == this->elementos[posPadre]->urgencia)
        {
            if (this->elementos[pos]->tiempo < this->elementos[posPadre]->tiempo)
            {
                return true;
            }
            else if (this->elementos[pos]->tiempo == this->elementos[posPadre]->tiempo)
            {
                return this->elementos[pos]->paciente < this->elementos[posPadre]->paciente;
            }
        }
        return false;
    }

    void flotar(int pos)
    {
        if (pos > 1)
        {
            int posPadre = padre(pos);
            if (vaAntes(pos, posPadre))
            {
                intercambiar(pos, posPadre);
                flotar(posPadre);
            }
        }
    }

    void hundir(int posPadre)
    {
        int posHijoIzq = posIzq(posPadre);
        int posHijoDer = posDer(posPadre);
        int posHijoMayor = posHijoIzq;

        if (posHijoDer < this->primeroLibre && vaAntes(posHijoDer, posHijoIzq))
        {
            posHijoMayor = posHijoDer;
        }

        if (posHijoMayor < this->primeroLibre && vaAntes(posHijoMayor, posPadre))
        {
            intercambiar(posHijoMayor, posPadre);
            hundir(posHijoMayor);
        }
    }

    void insertarAux(int paciente, int tiempo, int urgencia)
    {
        if (!this->estaLleno())
        {
            nodoHeap *nuevo = new nodoHeap;
            nuevo->urgencia = urgencia;
            nuevo->tiempo = tiempo;
            nuevo->paciente = paciente;
            this->elementos[this->primeroLibre] = nuevo;
            this->flotar(this->primeroLibre);
            this->primeroLibre++;
        }
    }

    nodoHeap *obtenerMaximoAux()
    {
        nodoHeap *ret = NULL;
        if (!this->esVacio())
        {
            ret = this->elementos[1];
            this->elementos[1] = this->elementos[this->primeroLibre - 1];
            this->primeroLibre--;
            hundir(1);
        }
        return ret;
    }

public:
    MaxHeap(int tamanio)
    {
        this->elementos = new nodoHeap *[tamanio + 1]();
        this->capacidad = tamanio;
        this->primeroLibre = 1;
    }

    bool esVacio()
    {
        return this->primeroLibre == 1;
    }

    bool estaLleno()
    {
        return this->primeroLibre >= this->capacidad + 1;
    }

    void insertar(int paciente, int tiempo, int urgencia)
    {
        this->insertarAux(paciente, tiempo, urgencia);
    }

    nodoHeap *obtenerMaximo()
    {
        return this->obtenerMaximoAux();
    }

    void destruir()
    {
        for (int i = 1; i < this->primeroLibre; i++)
        {
            delete this->elementos[i];
        }
        delete[] this->elementos;
    }
};

int main()
{
    int cantidad = 0;
    cin >> cantidad;
    MaxHeap *heap = new MaxHeap(cantidad);
    int paciente, urgencia, espera;
    for (int i = 0; i < cantidad; i++)
    {
        cin >> paciente >> espera >> urgencia;
        heap->insertar(paciente, espera, urgencia);
    }
    while (!heap->esVacio())
    {
        nodoHeap *tope = heap->obtenerMaximo();
        cout << tope->paciente << endl;
    }
    heap->destruir(); 
    delete heap;      
    return 0;
}
