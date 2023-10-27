#include <string>
#include <iostream>
using namespace std;

struct NodoTablaCerrada
{
	string clave;
	int valor;
	NodoTablaCerrada(string unaClave, int unValor) : clave(unaClave), valor(unValor){};
};

class TablaHashCerrada
{
private:
	NodoTablaCerrada **array;
	int tamanio;
	int cantidadDeElementos;

public:
	TablaHashCerrada(int tamaniInicial)
	{
		this->tamanio = tamaniInicial;
		this->cantidadDeElementos = 0;
		array = new NodoTablaCerrada *[this->tamanio]();
	}

	void insertar(string unaClave)
	{
		int valorHash = this->fnHash(unaClave);
		int pos = valorHash % this->tamanio;
		int i = 0;
		int inserte = false;

		while (!inserte)
		{
			if (this->array[pos] == NULL)
			{
				this->array[pos] = new NodoTablaCerrada(unaClave, pos);
				this->cantidadDeElementos++;
				inserte = true;
			}
			else if (this->array[pos]->clave.compare(unaClave) == 0) // Si las claves coinciden actualizo el valor
			{
				this->array[pos]->valor = pos;
				inserte = true;
			}
			// Lineal
			i++;
			pos = (valorHash + i) % this->tamanio;

		}
	}

	int getPos(string unaClave)
	{
		int valorHash = this->fnHash(unaClave);
		int pos = valorHash % this->tamanio;
		for (int i = 0; i <= this->tamanio; i++)
		{
			if (this->array[pos]->clave.compare(unaClave) == 0)
			{
				return array[pos]->valor;
			}
			// Lineal
			pos = (valorHash + i) % this->tamanio;
		}
	}

		string getClave(int unaPos)
	{
		if(this->array[unaPos]!=NULL){
			return this->array[unaPos]->clave;
		}
		return "";
	}

	int fnHash(string clave)
	{
		int sum = 0;
		for (int k = 0; k < clave.length(); k++)
			sum = sum + int(clave[k]);
		return sum;
	}
};