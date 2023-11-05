#include <iostream>
#include <cassert>
#include <string>
using namespace std;
struct Heap {
    int valor;
};

class MinHeap {
private:
    Heap *arr;
    int primeroLibre;
    int capacidad;

    int izq(int pos) {
        return pos * 2;
    }

    int der(int pos) {
        return (pos * 2) + 1;
    }

    int padre(int pos) {
        return pos / 2;
    }

    void intercambiar(int pos1, int pos2) {
        int aux = this->arr[pos1].valor;
        this->arr[pos1].valor = this->arr[pos2].valor;
        this->arr[pos2].valor = aux;
    }

    void flotar(int pos) {
        if (pos > 1) {
            int posPadre = padre(pos);
            if (this->arr[posPadre].valor > this->arr[pos].valor) {
                intercambiar(posPadre, pos);
                flotar(posPadre);
            }
        }
    }

    void hundir(int pos) {
        int posHijoIzq = izq(pos);
        int posHijoDer = der(pos);
        int posHijoMenor = pos;

        if (posHijoIzq < primeroLibre && this->arr[posHijoIzq].valor < this->arr[posHijoMenor].valor) {
            posHijoMenor = posHijoIzq;
        }

        if (posHijoDer < primeroLibre && this->arr[posHijoDer].valor < this->arr[posHijoMenor].valor) {
            posHijoMenor = posHijoDer;
        }

        if (posHijoMenor != pos) {
            intercambiar(pos, posHijoMenor);
            hundir(posHijoMenor);
        }
    }

public:
    MinHeap(int unaCapacidad) {
        this->arr = new Heap[unaCapacidad + 1];
        this->primeroLibre = 1;
        this->capacidad = unaCapacidad;
    }

    int obtenerMinimo() {
        if (estaVacio()) {
            return -1; 
        }
        return this->arr[1].valor;
    }

    void eliminarTope() {
        if (!estaVacio()) {
            this->arr[1] = this->arr[primeroLibre - 1];
            this->primeroLibre--;
            hundir(1);
        }
    }

    void insertar(int dato) {
        if (!estaLleno()) {
            this->arr[this->primeroLibre].valor = dato;
            flotar(this->primeroLibre);
            this->primeroLibre++;
        }
    }

    bool estaLleno() {
        return this->primeroLibre > this->capacidad;
    }

    bool estaVacio() {
        return this->primeroLibre == 1;
    }

    void destruir() {
        delete[] this->arr;
    }
};

int main() {
    string numero;
    cin >> numero;

    int largo = numero.length();

    MinHeap *heap = new MinHeap(largo);

    //recorro el numero
    //int digito = numero[i] - '0'; a cada caracter le resto '0' su valor ASCII para convertir de el string a un int 
    // el 1 es 49 en ASCII y el 0 es 48 entonces 49 - 48 = 1

    for (int i = 0; i < largo; i++) {
        int digito = numero[i] - '0';
        heap->insertar(digito);
    }
    //porque anda
    int pos = 0;
    if(largo % 2 == 0){
        pos=1;

    }else{
        pos=0;
    }
    
    int mitad = largo / 2; 

    // Creo dos variables int, la primera va tener la mitad de los digitos del heap (si es impar uno mas) y el otro los demas
    // Recorro el heap sacando el numero minimo y sumandoloselo a la variable mitad correspondiente
    // El resultado que voy guardando lo multiplico por diez para evitar usar strings, si tengo 5 y el minimo es 6 5*10=50+6=56
    //por ultimo elimino el minimo del heap y aumento en la pos de heap

    int mitad1 = 0;
    int mitad2 = 0;
    
    while (!heap->estaVacio()) {
        int minimo = heap->obtenerMinimo();

        if (pos <= mitad) {
            mitad1 = mitad1 * 10 + minimo; 
        } else {
            mitad2 = mitad2 * 10 + minimo; 
        }

        heap->eliminarTope();
        pos++;
    }

    cout << mitad1 + mitad2 << endl;
    heap->destruir();
    delete heap;

    return 0;
}
