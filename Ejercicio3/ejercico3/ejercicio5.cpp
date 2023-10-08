#include <iostream>
#include <cassert>
#include <string>
using namespace std;

struct nodoHeap
{
    int urgencia;
    int tiempo;
    int paciente;
    int ordenLlegada; // Nuevo campo para mantener el orden de llegada
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

    bool vaAntes(int pos1, int pos2)
    {
        if (this->elementos[pos1]->urgencia > this->elementos[pos2]->urgencia)
        {
            return true;
        }
        else if (this->elementos[pos1]->urgencia == this->elementos[pos2]->urgencia)
        {
            // Comparar por tiempo de espera
            if (this->elementos[pos1]->tiempo < this->elementos[pos2]->tiempo)
            {
                return true;
            }
            else if (this->elementos[pos1]->tiempo == this->elementos[pos2]->tiempo)
            {
                // Comparar por orden de llegada
                return this->elementos[pos1]->ordenLlegada < this->elementos[pos2]->ordenLlegada;
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
            nuevo->ordenLlegada = this->primeroLibre; // Asignar el orden de llegada
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
    int N, M;
    scanf("%d %d", &N, &M);
    init(N);

    for (int i = 0; i < M; i++) {
        int A, B, C;
        scanf("%d %d %d", &A, &B, &C);
        agregarPortal(A, B, C);
    }

    int origen, destino;
    scanf("%d %d", &origen, &destino);

    int minima_energia = encontrarMinimaEnergia(origen, destino);
    printf("%d\n", minima_energia);

    return 0;
}
