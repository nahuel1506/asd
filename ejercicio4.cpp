#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct Plato {
    string nombre;
    int entradas;
    Plato(string unNombre) : nombre(unNombre), entradas(0) {}
};

class Grafo {
public:
    int tamanio;

    Grafo(int P) {
        tamanio = P;
    }

    void aniadirArista(string B) {
        platos[B]->entradas++;
    }

    void ordenTopologico()
    {
		// inicializa el grado de entrada de cada uno de ls vertices del grafo
        int * gradoEntranda = initGradoDeEntrada();         
		Cola cola = new Cola;
        int vertice, cont = 0;
        for (int v = 1; v <= V; v++) // encolo todos los vertices de grado de entrada 0
            if (gradoEntranda[v] == 0)
                cola->encolar(v);

        while (!cola->estaVacia())
        {
            vertice = cola->desencolar();
            cont++;
            cout << vertice << endl; // proceso el vertice
            // Existe un struct arista para definir las aristas y un typedef para ListaAristas definido
            ListaAristas adyacentes = this->adyacentesA(vertice);
			// recorrer los adyecentes al vertice
            while (adyacentes)
            {
                Arista * a = adyacentes->dato;
                int w = a->destino;
                gradoEntranda[w]--; // quito un grado de entrada
                if (gradoEntranda[w] == 0)
                {
                    cola->encolar(w); // el vertice w esta listo para imprimir
                }
                adyacentes = adyacentes->sig;
            }
        }
        if (cont < V)
            cout << "ERROR: el grafo tiene ciclos" << endl;
    }
    
};

int main() {
    int P, D;
    cin >> P >> D;

    Grafo grafo(P);

    string pedido;
    for (int i = 0; i < P; i++) {
        cin >> pedido;
        grafo.platos[pedido] = new Plato(pedido);
    }

    string v, vaAl;
    for (int i = 0; i < D; i++) {
        cin >> v >> vaAl;
        grafo.aniadirArista(v, vaAl);
    }
    
  

    return 0;
}
