#include <iostream>
#include <string>
#include <cstring>
#include "ColaPrioridadExtendida.cpp"

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
		this->listaAdy = new Vertice *[cantVertices + 1];
		listaAdy[0] = NULL;
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

int dijkstra(Grafo &grafo, int origen, int destino)
{
	bool *visitados = new bool[grafo.getV() + 1]();
	int *vengoDe = new int[grafo.getV() + 1]; // este vector es opcional, es para guardar el camino, podría ponerlo como retorno
	int *costos = new int[grafo.getV() + 1];
	for (int i = 0; i < grafo.getV() + 1; i++)
	{
		vengoDe[i] = -1;
		costos[i] = INT_MAX;
	}
	costos[origen] = 0;
	ColaPrioridadExtendida cp = ColaPrioridadExtendida(grafo.getV());
	cp.encolar(origen, 0);	// se encola el origen con prioridad 0
	while (!cp.estaVacia()) // usar la cola prioridad con minheap me asegura siempre traer el vertice de menor costo
	{
		int v = cp.desencolar(); // extrae el vértice de menor costo no visitado
		visitados[v] = true; // para cada w adyacente a v
		for (Arista *adyacente = grafo.adyacentesA(v); adyacente != NULL; adyacente = adyacente->sig)
		{
			int w = adyacente->destino;
			int distVconW = adyacente->peso;

			if (!visitados[w] && costos[w] > costos[v] + distVconW)
			{
				costos[w] = costos[v] + distVconW;
				vengoDe[w] = v;
				cp.encolar(w, costos[w]);
			}
		}
	}

	int pos = destino;
	int posAnterior = -1;
	int costo = costos[pos];
	while (vengoDe[pos] != -1)
	{
		posAnterior = pos;
		pos = vengoDe[pos];
	}
	return posAnterior == -1 ? -1 : costo;
}

int main()
{
	int N, M;
	cin >> N >> M;

	Grafo grafo(N);
	int a, b, c;

	for (int i = 0; i < M; i++)
	{
		cin >> a >> b >> c;
		grafo.aniadirArista(a, b, c);
	}

	int origen, destino;
	cin >> origen >> destino;

	int minima_energia = dijkstra(grafo, origen, destino);
	cout << minima_energia << endl;

	return 0;
};