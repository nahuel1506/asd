#include <iostream>
#include <string>
using namespace std;

struct NodoPrioridad {
	int elemento;
	int prioridad;
	NodoPrioridad* sig;
};

class ColaPrioridadInt{
private:
	NodoPrioridad* primero;
	NodoPrioridad* ultimo;
	unsigned int cantElem;
	unsigned int cota;
public:

ColaPrioridadInt(unsigned int cota) {
	this->cota = cota;
	this->cantElem = 0;
	this->primero = NULL;
	this->ultimo = NULL;
}

void encolar(int e, int p) {
	if(!esLlena()){
	NodoPrioridad* aux = new NodoPrioridad;
	aux->elemento = e;
	aux->prioridad = p;
	aux->sig = NULL;

	if (esVacia()) {
		this->primero = aux;
		this->ultimo = aux;
	}
	else {
		if (p > this->primero->prioridad) {//si tiene mayor prioridad, lo pongo al inicio de la lista, osea que es el primero en salir
			aux->sig = this->primero;
			this->primero = aux;
		}
		else {//Si tiene una prioridad menor a p, voy a avanzar hasta colocarlo en donde tenga mayor prioridad, tambi�n lo voy a insertar al comienzo
			NodoPrioridad* actual = this->primero;
			NodoPrioridad* anterior = NULL;

			while (actual != NULL && p <= actual->prioridad) {
				anterior = actual;
				actual = actual->sig;
			}
				aux->sig = actual; //el resto de elementos los pongo a la derecha de aux
				anterior->sig = aux; //aux va luego del anterior (anterior tiene mayor prioridad)
			}
		}
	this->cantElem++;	
	}

}

int principio() {
	if(!esVacia())
	return this->primero->elemento;
}

int principioPrioridad() {
	if(!esVacia())
	return this->primero->prioridad;
}

void desencolar() {
	if (!esVacia()) {
		NodoPrioridad* aux = this->primero;
		this->primero = this->primero->sig;
		delete aux;
		this->cantElem--;
		if (this->primero == NULL) {
			this->ultimo = NULL;
		}
	}
}
bool esVacia() {
	return this->cantElem==0;
}

bool esLlena() {
	return this->cantElem==this->cota;
}

unsigned int cantidadElementos() {
	return this->cantElem;
}

};