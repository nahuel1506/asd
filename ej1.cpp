#include <iostream>
#include <cassert>
#define TABLA_HASH_ABIERTA
#include <string>
using namespace std;

struct nodoHeap
{
	int pedidos;
	string comida;
};

struct NodoLista
{
	string comida;
	int pedidos;
	NodoLista *sig;
	NodoLista(string unaClave, int unValor) : comida(unaClave), pedidos(unValor), sig(0){};
	NodoLista(string unaClave, int unValor, NodoLista *unSig) : comida(unaClave), pedidos(unValor), sig(unSig){};
};

typedef NodoLista *Lista;

class TablaHash
{
private:
	Lista *arrList;
	int tamanio;

public:
	TablaHash(int cantidadComidas)
	{
		this->tamanio = cantidadComidas;
		arrList = new Lista[this->tamanio]();
	}

	int fnHash(string clave)
	{
		int sum = 0;
		for (int k = 0; k < clave.length(); k++)
		{
			sum = sum * 97 + int(clave[k]);
		}
		return sum;
	}

    string getComida(int pos){
        return this->arrList[pos]->comida;
    }

    int getPedidos(string unaComida){
        int pos = abs(this->fnHash(unaComida)) % this->tamanio;
        return this->arrList[pos]->pedidos;
    }

	void insertarEnTabla(string unaComida)
	{
		int pos = abs(this->fnHash(unaComida)) % this->tamanio;
		if (arrList[pos] != NULL)
		{
			arrList[pos]->pedidos++;
		}
		else
		{
			arrList[pos] = new NodoLista(unaComida, 1);
		}
	}
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

	bool hijoEsMayor(int posHijo, int posPadre)
	{
		return this->elementos[posHijo]->pedidos > this->elementos[posPadre]->pedidos;
	}

	bool hijoEsIgual(int posHijo, int posPadre)
	{
		return this->elementos[posHijo]->pedidos == this->elementos[posPadre]->pedidos;
	}

	void flotar(int pos)
	{
		if (pos > 1)
		{
			int posPadre = padre(pos);
			if (hijoEsMayor(pos, posPadre))
			{
				intercambiar(pos, posPadre);
				flotar(posPadre);
			}
		}
	}

	void hundir(int pos)
    {
        int posHijoIzq = posIzq(pos);
        int posHijoDer = posDer(pos);
        int hijoMayor = posHijoIzq; 

        if (posHijoDer < this->primeroLibre && this->elementos[posHijoIzq]->pedidos < this->elementos[posHijoDer]->pedidos) 
        {
            hijoMayor = posHijoDer; 
        }

        if (hijoMayor < this->primeroLibre && hijoEsMayor(hijoMayor, pos)) 
        {
            intercambiar(pos, hijoMayor);
            hundir(hijoMayor);
        }
    }

	void insertarAux(int pedidos, string comida)
	{
		if (!this->estaLleno())
		{
			nodoHeap *nuevo = new nodoHeap;
			nuevo->pedidos = pedidos;
			nuevo->comida = comida;
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
			this->elementos[1] = this->elementos[this->primeroLibre - 1]; // this->primeroLibre - 1 es el último
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

	void insertar(string comida, int pedidos)
	{
		this->insertarAux(pedidos, comida);
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
	cout << "PRIMERO" << endl;
	int cantidadComidas = 0;
	cin >> cantidadComidas;

	TablaHash *tabla = new TablaHash(cantidadComidas);
	string comida;

	for (int i = 0; i < cantidadComidas+1; i++)
	{
		cin >> comida;
		tabla->insertarEnTabla(comida);
	}

	MaxHeap *heap = new MaxHeap(cantidadComidas);

	for (int i = 0; i < cantidadComidas; i++)
	{
		if (tabla->getComida(i) != "")
		{
			heap->insertar(tabla->getComida(i), tabla->getPedidos(tabla->getComida(i)));
		}
	}

	while (!heap->esVacio())
	{
		nodoHeap *tope = heap->obtenerMaximo();
		cout << tope->comida << endl;
	}
	return 0;
}