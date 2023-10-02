#include <vector>
#include <algorithm>

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
    //se recorre el vector de aristas y se devuelve el peso de la arista que cuyo
    //origen y destino coincidan con los pasados como argumento.
    //En caso que no se encuentre una arista que conecte los vertices se devuelve infinito
    for (const auto& arista : aristas) {
        if (arista.origen.nombre == origen.nombre && arista.destino.nombre == destino.nombre) {
            return arista.peso;
        }
    }
    return oo;
}

// Función para inicializar la lista de predecesores
vector<Vertice> prevInit(const Vertice& v, const vector<Vertice>& vertices) {
    // Se crea un vector que tiene el mismo tamaño que el número de vértices en el grafo 
    // y se inizalizan todos los elementos del vector en {0}
    vector<Vertice> predecesores(vertices.size(), {0});
    //Aqui se usa transform que es el equivalente a map. Va a aplicar una operacion a cada elemento dentro del rango especificado.
    transform(vertices.begin(), vertices.end(), predecesores.begin(),
                    // La función lambda compara el nombre del vértice x con el nombre del vértice v.
                    // Si son iguales, significa que x es el vértice para el cual estamos inicializando los predecesores
                    // por lo que se devuelve x. Si no son iguales, se devuelve Vertice{0}
                    // para indicar que no hay predecesor conocido para ese vértice.
                   [v](const Vertice& x) { return (x.nombre == v.nombre) ? x : Vertice{0}; });
    return predecesores;
}

// Función para inicializar la lista de pesos acumulados
vector<int> acuInit(const vector<Arista>& aristas, const Vertice& v, const vector<Vertice>& vertices) {
    // Se crea un vector que tiene el mismo tamaño que el número de vértices en el grafo 
    // y se inizalizan todos los elementos del vector en {0}
    vector<int> pesosAcumulados(vertices.size(), 0);
    //Aqui se usa transform que es el equivalente a map. Va a aplicar una operacion a cada elemento dentro del rango especificado.
    transform(vertices.begin(), vertices.end(), pesosAcumulados.begin(),
                // La función lambda verifica si el vértice x es igual al vértice inicial v. 
                // Si son iguales, significa que estamos en el vértice inicial, por lo que el peso acumulado es 0. 
                // Si no son iguales, se utiliza la función costo para calcular el costo desde v hasta x
                   [v, aristas](const Vertice& x) {
                       if (x.nombre == v.nombre) {
                           return 0;
                       } else {
                           return costo(aristas, v, x);
                       }
                   });
    return pesosAcumulados;
}