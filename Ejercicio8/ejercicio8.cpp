#include <iostream>
#include <cassert>
#include <string>
#include "ColaInt.cpp"
using namespace std;

void hallarPicos(int*& alturas, int tamanioAlturas, int posIzq, int posDer, ColaInt& picos) {
    if (posIzq <= posDer) { //Verifico estar dentro del rango
    int posMedio = (posIzq + posDer) / 2;
    hallarPicos(alturas, tamanioAlturas, posIzq, posMedio - 1, picos);//Primero hago recursión por la izquierda para mantener el orden de los picos, solo muevo el indice de la der

/*
Casos posibles:
Estoy parado al inicio (0) y soy mayor que lo que tengo a la der
Estoy parado al final (altura-1) y soy mayor que lo tengo a la izq
Estoy parado en otra posición y la altura de posMedio es mayor a lo que tiene a la izq y der
*/
    if ((posMedio == 0 || alturas[posMedio] > alturas[posMedio - 1]) && (posMedio == tamanioAlturas - 1 || alturas[posMedio] > alturas[posMedio + 1])) {
        picos.encolar(alturas[posMedio]);
    }

    hallarPicos(alturas, tamanioAlturas, posMedio + 1, posDer, picos); //Ahora hago recursión por la derecha moviendo el indice izq
    }
}

int main() {
    int N;
    cin >> N;

    int* alturas = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> alturas[i];
    }

    ColaInt picos = ColaInt();
    hallarPicos(alturas,N, 0, N - 1, picos);

    while (!picos.esVacia()) {
        cout << picos.principio() << endl;
        picos.desencolar();
    }

    return 0;
}