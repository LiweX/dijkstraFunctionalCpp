#include <vector>

using namespace std;

struct Vertice {
    int nombre;
};

struct Arista {
    Vertice origen;
    Vertice destino;
    int peso;
};

struct Grafo {
    vector<Vertice> vertices;
    vector<Arista> aristas;
};

struct Dijkstra {
    vector<Arista> aristas;
    vector<Vertice> vc;
    vector<Vertice> vnc;
    vector<int> pacu;
    vector<Vertice> prev;
};

const int oo = 100;

// Función para calcular el costo entre dos vértices
int costo(const vector<Arista>& aristas, const Vertice& origen, const Vertice& destino) {
    for (const auto& arista : aristas) {
        if (arista.origen.nombre == origen.nombre && arista.destino.nombre == destino.nombre) {
            return arista.peso;
        }
    }
    return oo;
}