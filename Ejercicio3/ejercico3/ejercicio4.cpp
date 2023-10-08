#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;
struct NodoLista
{
	string comida;
	int pedidos;
	NodoLista *sig;
	NodoLista(string unaClave, int unValor) : comida(unaClave), pedidos(unValor), sig(0){};
	NodoLista(string unaClave, int unValor, NodoLista *unSig) : comida(unaClave), pedidos(unValor), sig(unSig){};
};

class Grafo {
    private:
    public:
   	void aniadirArista(int v, int w, int peso = 1)
	{
	}

	// Hacer que retorne un tipo de dato adecuado
	void adyacentesA(int origen)
	{
	}
    void ordenTopologico()
    {
		// inicializa el grado de entrada de cada uno de ls vertices del grafo
        int *gradoEntranda = initGradoDeEntrada();         
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


}:
int main() {
    int P, D;
    cin >> P >> D;

    for (int i = 0; i < P; i++) {
        string plato;
        cin >> plato;
        dependencias[plato] = vector<string>();
    }

    for (int i = 0; i < D; i++) {
        string A, B;
        cin >> A >> B;
        dependencias[A].push_back(B); // A debe ser preparado antes que B
    }

    vector<string> orden = ordenTopologico();

    if (orden.size() != P) {
        cout << "CICLO DETECTADO" << endl;
    } else {
        for (const string& plato : orden) {
            cout << plato << endl;
        }
    }

    return 0;
}
