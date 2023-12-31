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
auto previnicial = [](const Vertice& v, const std::vector<Vertice>& vertices) {
    std::vector<Vertice> predecesores(vertices.size(), verticenulo);
    //Aqui se usa transform que es el equivalente a map. Va a aplicar una operacion a cada elemento dentro del rango especificado.
    std::transform(vertices.begin(), vertices.end(), predecesores.begin(), 
                    [&v](const Vertice& x) {
                        return (x.nombre == v.nombre) ? v : verticenulo;
                    });
    return predecesores;
};

// Función para inicializar la lista de pesos acumulados
auto acuinicial = [](const std::vector<Arista>& aristas, const Vertice& v, const std::vector<Vertice>& vertices) {
    std::vector<int> pesosAcumulados(vertices.size(), 0);
    std::transform(vertices.begin(), vertices.end(), pesosAcumulados.begin(),
                    [&aristas, &v](const Vertice& x) {
                        return (x.nombre != v.nombre) ? costo(aristas, v, x) : 0;
                    });
    return pesosAcumulados;
};

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


