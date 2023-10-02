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

struct Dijkstra {
    vector<Arista> a;
    vector<Vertice> vc;
    vector<Vertice> vnc;
    vector<int> pacu;
    vector<Vertice> prev;
};

const int oo = 100;
Vertice verticenulo = {0};


// Función para calcular el costo entre dos vértices
auto costo = [](const std::vector<Arista>& aristas, const Vertice& origen, const Vertice& destino) {
    auto arista = find_if(aristas.begin(), aristas.end(), [&origen, &destino](const Arista& a) {
        return a.origen.nombre == origen.nombre && a.destino.nombre == destino.nombre;
    });
    //
    return (arista != aristas.end()) ? arista->peso : oo;
};

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

// Función para actualizar los pesos acumulados y predecesores
pair<vector<int>, vector<Vertice>> actpeso(const vector<int>& pacu,
                                           const vector<Vertice>& prev,
                                           const Arista& arista) {
    vector<int> nuevosPesosAcumulados = pacu;
    vector<Vertice> nuevosPredecesores = prev;

    int costoNuevo = pacu[arista.origen.nombre - 1] + arista.peso;

    if (costoNuevo < pacu[arista.destino.nombre - 1]) {
        nuevosPesosAcumulados[arista.destino.nombre - 1] = costoNuevo;
        nuevosPredecesores[arista.destino.nombre - 1] = arista.origen;
    }

    return make_pair(nuevosPesosAcumulados, nuevosPredecesores);
}

Dijkstra iteracion(const Dijkstra& d) {
    Dijkstra resultado = d;

    // Encuentra el próximo vértice a considerar
    Vertice next = *(min_element(d.vnc.begin(), d.vnc.end(),
        [&d](const Vertice& x, const Vertice& y) {
            return d.pacu[x.nombre - 1] < d.pacu[y.nombre - 1];
        }));

    // Actualiza la lista de vértices considerados y no considerados
    resultado.vc.insert(resultado.vc.begin(), next);
    resultado.vnc.erase(remove(resultado.vnc.begin(), resultado.vnc.end(), next), resultado.vnc.end());

    // Filtra las aristas candidatas
    vector<Arista> aristasCandidatas;
    for (const Arista& a : resultado.a) {
        if (a.origen.nombre == next.nombre && find(resultado.vnc.begin(), resultado.vnc.end(), a.destino) != resultado.vnc.end()) {
            aristasCandidatas.push_back(a);
        }
    }

    // Actualiza los pesos acumulados y predecesores
    for (const Arista& arista : aristasCandidatas) {
        auto [nuevosPacu, nuevosPrev] = actpeso(resultado.pacu, resultado.prev, arista);
        resultado.pacu = nuevosPacu;
        resultado.prev = nuevosPrev;
    }

    return resultado;
}


