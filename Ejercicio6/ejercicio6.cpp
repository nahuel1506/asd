#include <iostream>
#include <string>
#include "MFsetv2.cpp"
#include "MinHeap.cpp"

struct Vertice
{
    int dato;
    int grado;
    Arista *ady;
    Vertice(int unDato, int unGrado) : dato(unDato), grado(unGrado), ady(0){};
    Vertice(int unDato, int unGrado, Arista *unAdy) : dato(unDato), grado(unGrado), ady(unAdy){};
};

class Grafo
{

private:
    Vertice **listaAdy;
    int cantVertices;
    int cantAristas;
    bool esDirigido;

public:
    Grafo(int cantidadDeVertices, bool dirigido = true)
    {
        this->cantVertices = cantidadDeVertices;
        this->cantAristas = 0;
        this->listaAdy = new Vertice *[cantVertices+1];
        // Inicializo la lista en NULL
        for (int i = 1; i <= cantidadDeVertices; i++)
        {
            this->listaAdy[i] = new Vertice(i, 0, NULL);
        }
        this->esDirigido = dirigido;
    }

    void aniadirArista(int origen, int destino, int peso = 0)
    {

        // Siempre modifico el sig del origen ya que este es el vertice y el resto son sus adyacentes
        Arista *aux = new Arista(origen, destino, peso, this->listaAdy[origen]->ady);
        this->listaAdy[origen]->ady = aux;
        // Inserto al comienzo
        this->listaAdy[destino]->grado++; // cada vez que introduzca una arista, voy a sumarle un grado al vertice destino
        this->cantAristas++;

        if (!this->esDirigido && origen != destino)
        { // Si es no dirigido agrego el simétrico
            Arista *aux2 = new Arista(destino, origen, peso, this->listaAdy[destino]->ady);
            this->listaAdy[destino]->ady = aux2;
            this->listaAdy[origen]->grado++; // como es simetrico también aumenta el grado en el vertice origen
            this->cantAristas++;
        }
    }

    int getV()
    {
        return this->cantVertices;
    }

    int getA()
    {
        return this->cantAristas;
    }

    // Hacer que retorne un tipo de dato adecuado
    Arista *adyacentesA(int origen)
    {
        return this->listaAdy[origen]->ady;
    }
};

int Kruskal(Grafo &grafo)
{
    int cantV = grafo.getV();
    int cantA = grafo.getA();
    MinHeap heap = MinHeap(cantA);
    for (int i = 1; i <= cantV; i++)
    {
        for (Arista *aux = grafo.adyacentesA(i); aux != NULL; aux = aux->sig)
        {
            heap.insertar(aux);
        }
    }
    int retorno = 0;
    int aristasAceptadas = 0;
    MFSet mfset(cantV + 1);

    while ((!heap.estaVacio()) || aristasAceptadas < (cantV - 1))
    {
        Arista *a = heap.getTope();
        heap.eliminarTope();
        if (mfset.find(a->origen) != mfset.find(a->destino))
        {
            mfset.merge(a->origen, a->destino);
            retorno += a->peso;
            aristasAceptadas++;
        }
    }
    return retorno;
}

int main()
{
    int N, M;
    cin >> N;
    cin >> M;

    Grafo grafo(N, false);

    int a, b, c;
    for (int i = 0; i < M; i++)
    {
        cin >> a >> b >> c;
        grafo.aniadirArista(a, b, c);    
    }

   int minima_energia = Kruskal(grafo);
   cout << minima_energia << endl;

    return 0;
};