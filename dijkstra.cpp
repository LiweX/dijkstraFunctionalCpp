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