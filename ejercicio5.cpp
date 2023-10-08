#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Portal {
    int destino;
    int costo;
};

void dijkstra(int origen){
    int* visitados = initVisitados(); // array V casilleros, todos en false​
    int* costos = initCostos(origen); // array V casillero, todos en INF menos origen con 0​
    int* vengo= initVengo(); // array V casilleros, todos en -1​
    for(int i=0; i<V; i++) ​
        int v = verticeDesconocidoDeMenorCosto(visitados, costos); // vértice a procesar​   
        visitados[v] = true;​
        para cada w adyacente a v ​
        if(costos[w] > costos[v] + dist(v,w))​
            costos[w] = costos[v] + dist(v,w);​
            vengo[w] = v;

}​

}

int main() {
    int N, M;
    cin >> N >> M;

    int a, b, c;

    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        agregarPortal(a, b, c);
    }

    int origen, destino;
    cin >> origen >> destino;

    int minima_energia = encontrarMinimaEnergia(origen, destino);
    cout << minima_energia << endl;

    return 0;
}