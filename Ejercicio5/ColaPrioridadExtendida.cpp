#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct nodoHeap
{
    int dato;
    int prioridad;
    nodoHeap(int unDato, int unaPrioridad) : dato(unDato), prioridad(unaPrioridad){};
};

struct nodoTabla
{
    int clave;
    int valor;
    nodoTabla *sig;
    nodoTabla(int unaClave, int unValor) : clave(unaClave), valor(unValor), sig(0){};
    nodoTabla(int unaClave, int unValor, nodoTabla *unSig) : clave(unaClave), valor(unValor), sig(unSig){};
};

class ColaPrioridadExtendida
{
private:
    nodoTabla **arrayTabla;
    nodoHeap **arrayHeap;
    int tamanio;
    int primeroLibre;

    int izq(int pos)
    {
        return pos * 2;
    }

    int der(int pos)
    {
        return (pos * 2) + 1;
    }

    int padre(int pos)
    {
        return pos / 2;
    }

    void intercambiar(int pos1, int pos2)
    {
        nodoHeap *aux = this->arrayHeap[pos1];
        this->arrayHeap[pos1] = this->arrayHeap[pos2];
        this->arrayHeap[pos2] = aux;

        actualizarPosicion(arrayHeap[pos1]->dato, pos1);
        actualizarPosicion(arrayHeap[pos2]->dato, pos2);
    }

    void flotar(int pos)
    {
        // trato de flotar si no soy la raiz
        if (pos > 1)
        {
            int posPadre = padre(pos);
            if (this->arrayHeap[posPadre]->prioridad > this->arrayHeap[pos]->prioridad)
            {
                intercambiar(posPadre, pos);
                flotar(posPadre);
            }
        }
    }
    void hundir(int pos)
    {
        int posHijoIzq = izq(pos);
        int posHijoDer = der(pos);
        int posHijoMenor;
        // si tengo mis dos hijos
        if (posHijoIzq < primeroLibre && posHijoDer < primeroLibre)
        {
            int posHijoMenor = this->arrayHeap[posHijoIzq]->prioridad <= this->arrayHeap[posHijoDer]->prioridad ? posHijoIzq : posHijoDer;
            if (this->arrayHeap[pos]->prioridad > this->arrayHeap[posHijoMenor]->prioridad)
            {
                intercambiar(pos, posHijoMenor);
                hundir(posHijoMenor);
            }
        }
        // si tengo solo hijo izquierdo
        else if (posHijoIzq < primeroLibre)
        {
            if (this->arrayHeap[pos]->prioridad > this->arrayHeap[posHijoIzq]->prioridad)
            {
                intercambiar(pos, posHijoIzq);
                hundir(posHijoIzq);
            }
        }
    }

    nodoHeap *getTope()
    {
        if(!heapVacio()){
        return this->arrayHeap[1];            
        }
        return NULL;

    }
      nodoHeap *getUltimo()
    {
        return this->arrayHeap[primeroLibre - 1];
    }  

    void eliminarTope()
    {
        if(!heapVacio()){
        eliminarTabla(this->arrayHeap[primeroLibre - 1]->dato);
        this->arrayHeap[1] = this->arrayHeap[primeroLibre - 1]; // pongo el último en la raiz
        this->primeroLibre--;
        hundir(1); // hundo la nueva raiz            
        }

    }

    void insertarEnHeap(int dato, int prioridad)
    {
        if (!this->heapLleno())
        {
            nodoHeap *nuevo = new nodoHeap(dato, prioridad);
            this->arrayHeap[this->primeroLibre] = nuevo; // lo coloco en el primer lugar libre
            this->insertarEnTabla(dato, primeroLibre); //lo inserto en la tabla hash
            flotar(this->primeroLibre);
            this->primeroLibre++;
        }
    }


    void actualizarPrioridad(int posicion, int nuevaPrioridad)
    {
        if (posicion >= 1 && posicion < primeroLibre)
        {
            int antiguaPrioridad = arrayHeap[posicion]->prioridad;
            arrayHeap[posicion]->prioridad = nuevaPrioridad;
            if (nuevaPrioridad < antiguaPrioridad)
            {
                flotar(posicion);
            }
            else if (nuevaPrioridad > antiguaPrioridad)
            {
                hundir(posicion);
            }
        }
    }

    bool heapLleno()
    {
        return this->primeroLibre > this->tamanio;
    }

    bool heapVacio()
    {
        return this->primeroLibre == 1;
    }

    int fnHash(int clave)
    {
        return clave;
    }

    void insertarEnTabla(int unaClave, int unValor)
    {
        int pos = abs(this->fnHash(unaClave)) % this->tamanio;
        if (arrayTabla[pos] != NULL)
        {
            for (nodoTabla *aux = arrayTabla[pos]; aux != NULL; aux = aux->sig)
            {
                if (aux->clave == unaClave)
                {
                    aux->valor = unValor;
                    return;
                }
            }
        }
        else
        {
            arrayTabla[pos] = new nodoTabla(unaClave, unValor);
        }
    }

    void eliminarTabla(int unaClave)
    {
        int pos = abs(this->fnHash(unaClave)) % this->tamanio;
        nodoTabla *anterior = NULL;
        nodoTabla *actual = arrayTabla[pos];

        while (actual != NULL)
        {
            if (actual->clave == unaClave)
            {
                if (anterior == NULL)
                {
                    // El nodo a eliminar es el primer nodo de la lista
                    arrayTabla[pos] = actual->sig;
                }
                else
                {
                    // El nodo a eliminar está en medio o al final de la lista
                    anterior->sig = actual->sig;
                }

                delete actual; // Libero memoria del nodo
                return;
            }

            anterior = actual;
            actual = actual->sig;
        }
    }

    void actualizarPosicion(int unaClave, int nuevaPosicion)
    {
        int pos = abs(fnHash(unaClave)) % tamanio;
        for (nodoTabla *aux = arrayTabla[pos]; aux != NULL; aux = aux->sig)
        {
            if (aux->clave == unaClave)
            {
                aux->valor = nuevaPosicion;
                return;
            }
        }
    }

    int getPosTabla(int unaClave)
    {
        int pos = abs(fnHash(unaClave)) % tamanio;
        for (nodoTabla *aux = arrayTabla[pos]; aux != NULL; aux = aux->sig)
        {
            if (aux->clave == unaClave)
            {
                return aux->valor;
            }
        }
        return -1; // Elemento no encontrado
    }

    int getDato(int pos)
    {
        return arrayTabla[pos]->clave;
    }

public:
    ColaPrioridadExtendida(int tamanio)
    {
        this->arrayHeap = new nodoHeap *[tamanio + 1];
        this->primeroLibre = 1;
        this->tamanio = tamanio;
        arrayTabla = new nodoTabla *[this->tamanio]();
    }

    void encolar(int elemento, int prioridad)
    {
        /*
           1. Se inserta normalmente en el Heap
           2. Se agrega el par (elemento | posición en heap) a la Tabla de Hash
           3. Se flota el elemento en el Heap
           4. Por cada swap realizado se actualizan ambos valores en la Tabla de Hash
       */

        // 1. Se inserta normalmente en el Heap
        this->insertarEnHeap(elemento, prioridad);
        // 2. Se agrega el par (elemento | posición en heap) a la Tabla de Hash
        
    }
    int desencolar()
    {
        /*
            1. Intercambiar la raíz por la última posición del Heap
            2. Hundir la raíz
            3. Cada swap debe ser actualizado en la tabla de hash
        */

        if (estaVacia())
        {
            cout << "La cola de prioridad está vacía." << endl;
            return -1;
        }

        // 1. Intercambiar la raíz con el último elemento
        int raiz = this->getTope()->dato;
        this->eliminarTope();

        return raiz;
    }

    bool estaVacia()
    {
        return this->heapVacio();
    }

    void eliminar(int elemento)
    {
        /*
            1. Buscamos en la Tabla de Hash la posición del elemento en el Heap
            2. Eliminamos el valor intercambiandolo con la última posición del Heap
            3. Hundimos y Flotamos la posición intercambiada
            a. Puede flotar solamente si el elemento intercambiado tiene menor prioridad que el elemento borrado
            b. Puede hundirse solamente si el elemento intercambiado tiene mayor prioridad que el elemento borrado
            Un elemento intercambiado o bien flota o bien se hunde, ¡nunca suceden las dos cosas!
        */

        if (!existe(elemento))
        {
            cout << "El elemento no existe en la cola de prioridad." << endl;
            return;
        }

        // Actualizar la prioridad del elemento para eliminarlo
        this->actualizarPrioridad(this->getPosTabla(elemento), INT_MIN); // Le ponemos prioridad minima para que se coloque en el tope del heap

        // Desencolar el elemento con la nueva prioridad (esto lo eliminará del Heap)
        desencolar();

        this->eliminarTabla(elemento); // Eliminar el elemento de la tabla de hash
    }

    void cambiarPrioridad(int elemento, int nuevaPrioridad)
    {
        /*
            1. Buscamos en la Tabla de Hash la posición del elemento en el Heap
            2. Actualizamos su prioridad
            3. Hundimos y Flotamos la posición actualizada
            a. Puede flotar solamente si la prioridad actualizada es menor que la prioridad anterior
            b. Puede hundirse solamente si la prioridad actualizada es mayor que la prioridad anterior
            Un elemento actualizado o bien flota o bien se hunde, ¡nunca suceden las dos cosas!
        */
        if (!existe(elemento))
        {
            cout << "El elemento no existe en la cola de prioridad." << endl;
            return;
        }

        int posicion = this->getPosTabla(elemento); // Obtener la posición en el Heap

        // Actualizar la prioridad del elemento
        this->actualizarPrioridad(posicion, nuevaPrioridad);
    }

    bool existe(int elemento)
    {
        /*
            ● En esta operación no interviene el Heap
            ● Simplemente preguntamos si la tabla de hash incluye una correspondencia para el elemento
        */

        return this->getPosTabla(elemento) != -1;
    }
};