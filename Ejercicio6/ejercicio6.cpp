#include <iostream>
#include <string>
#include "MFsetv2.cpp"
#include "ColaPrioridadExtendida.cpp"

struct NodoPlato
{
    string nombre;
    int entradas;
    NodoPlato *sig;
    NodoPlato(string unNombre) : nombre(unNombre), entradas(0) {}
};

struct Arista
{
    int origen;
    int destino;
    int peso;
    Arista *sig;
    Arista(int unOrigen, int unDestino, int unPeso) : origen(unOrigen), destino(unDestino), peso(unPeso), sig(0){};
    Arista(int unOrigen, int unDestino, int unPeso, Arista *unSig) : origen(unOrigen), destino(unDestino), peso(unPeso), sig(unSig){};
};

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
        this->listaAdy = new Vertice *[cantVertices];
        // Inicializo la lista en NULL
        for (int i = 0; i < cantidadDeVertices; i++)
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

void Kruskal(Grafo& grafo)
    {
        int v = grafo.getV();
        ColaPrioridadExtendida cp = ColaPrioridadExtendida(v);
        aniadirArista(cp);
        Lista<Arista> solucion();
        MFset mfset((grafo.getV() + 1));
        int aristasAceptadas = 0;

        while (cp.estaVacia() || aristaAceptadas < V - 1)
        {
            Arista a = cp.pop();
            if (mfset.find(a.origen) != mfset.find(a.destino))
            {
                mfset.merge(a.origen, a.destino);
                insertarEnLista(solucion, a);
                aristasAceptadas++;
            }
        }
    }



mfset.merge(0, 2);

int main()
{
    int N, M;
    cin >> N >> M;

    MFSet grafo(N);
    int a, b, c;

    for (int i = 0; i < M; i++)
    {
        cin >> a >> b >> c;
        mfset.merge(0, 2);
        grafo.aniadirArista(a, b, c);
    }

    int minima_energia = dijkstra(grafo, origen, destino);
    cout << minima_energia << endl;

    return 0;
};