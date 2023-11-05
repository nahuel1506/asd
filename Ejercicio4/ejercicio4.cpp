#include <iostream>
#include <string>
#include <cstring>
#include "MaxHeap.cpp"
#include "TablaHashCerrada.cpp"
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

	int *gradosEntrada()
	{
		int *g = new int[this->getV()];

		for (int i = 0; i < this->getV(); i++)
		{
			g[i] = listaAdy[i]->grado;
		}
		return g;
	}
};

bool ordenTopologico(Grafo &grafo, TablaHashCerrada &tabla)
{
	int *gradosArray = grafo.gradosEntrada();

	MaxHeap heap = MaxHeap(grafo.getV());
	int vertice, cont = 0;

	for (int v = 0; v < grafo.getV(); v++) // encolo todos los vertices de grado de entrada 0
	{
		if (gradosArray[v] == 0)
		{
			heap.insertar(tabla.getClave(v)); // se rompe
		}
	}

	while (!heap.estaVacio())
	{
		vertice = tabla.getPos(heap.getTope());
		heap.eliminarTope();
		cont++;
		cout << tabla.getClave(vertice) << endl; // proceso el vertice
		// Existe un struct arista para definir las aristas y un typedef para ListaAristas definido
		Arista *adyacentes = grafo.adyacentesA(vertice);
		// recorrer los adyecentes al vertice
		while (adyacentes != NULL)
		{
			int w = adyacentes->destino;
			gradosArray[w]--; // quito un grado de entrada

			if (gradosArray[w] == 0)
			{
				heap.insertar(tabla.getClave(w)); // el vertice w esta listo para imprimir
			}

			adyacentes = adyacentes->sig;
		}
	}

	delete[] gradosArray;

	return cont < grafo.getV();
}

int main()
{
	int P, D;
	cin >> P >> D;

	TablaHashCerrada vertices(P);
	Grafo grafoPlatos(P);

	for (int i = 0; i < P; i++)
	{
		string plato;
		cin >> plato;
		vertices.insertar(plato);
	}

	for (int i = 0; i < D; i++)
	{
		string A, B;
		cin >> A >> B;
		int a = vertices.getPos(A);
		int b = vertices.getPos(B);
		grafoPlatos.aniadirArista(a, b);
	}

	ordenTopologico(grafoPlatos,vertices);
	return 0;
};
