/**
 * @author Jose Barrera Ramos
 * Arboles y grafos 20251
 * Proyecto happyness.cpp
 * Complejidad temporal 0( N * D * log(N * D) * G )
 * Complejidad espacial 0( N * D )
 *
 * N: Numero de Ciudades
 * D: Dias posibles
 * G: Numero de conexiones nuevas por Ciudad
 */

// Librerias
#include <iostream>
#include <queue>
#include <vector>
#include <chrono>

using namespace std;

// Struct
struct Kenny {
    int diasTrabajados; // Costo Dijkstra

    // Grafo Estados
    int ciudadActual;
    int dineroActual;

    // Sobrecarga para ordebar en la Priority Queue
    bool operator>(const Kenny& other) const {
        bool ans = dineroActual < other.dineroActual;
        if (diasTrabajados != other.diasTrabajados) {
            ans = diasTrabajados > other.diasTrabajados;
        }
        return ans;
    }
};

// Funciones
int dijkstra(vector<int>& salarioCiudades, int& capital, int& destino, vector<vector<pair<int, int>>>& grafo,
             int& numCiudades, int& dineroDisponible);

/**
 * Main Principal GRAN IMPERIO AGRA
 * @return
 */
int main() {
    auto start = chrono::high_resolution_clock::now(); // Tiempo de inicio

    int numCasos = 0;
    cin >> numCasos;

    // Ciclo para procesar el numero de casos
    for (int caso = 0; caso < numCasos; caso++) {
        int numCiudades = 0, numTiquetesBus = 0, dineroInicial = 0, precioDoll = 0;
        cin >> numCiudades >> numTiquetesBus >> dineroInicial >> precioDoll;

        int dineroDisponible = dineroInicial - precioDoll; // Dinero de Kenny al Comprar la muñeca

        vector<int> salarioCiudades(numCiudades + 1);
        for (int i = 1; i <= numCiudades; i++) {
            cin >> salarioCiudades[i];
        }

        int capital = 0, destino = 0;
        cin >> capital >> destino;

        // Creacion del grafo del GRAN IMPERIO AGRA
        vector<vector<pair<int, int>>> grafo(numCiudades + 1);
        for (int i = 0; i < numTiquetesBus; i++) {
            int idCiudad = 0, idTiquete = 0, precioTiquete = 0;
            cin >> idCiudad >> idTiquete >> precioTiquete;

            grafo[idCiudad].push_back({idTiquete, precioTiquete});
        }

        int numDias = dijkstra(salarioCiudades, capital, destino, grafo, numCiudades,
            dineroDisponible);

        if (numDias != -1) {
            cout << "Kenny happiness will cost " << numDias << " days of work :)" << endl;
        } else {
            cout << "Sorry Kenny, Happiness is not for you :(" << endl;
        }
    }

    // Calcular tiempo de ejecucion:
    auto end = chrono::high_resolution_clock::now(); // Tiempo de finalización
    chrono::duration<double> duration = end - start;
    cout << "Tiempo total de ejecución: " << duration.count() << " segundos" << endl;
    return 0;
}

/**
 * Funcion para calcular el menor numero de dias para salir del GRAN IMPERIO AGRA
 * @param salarioCiudades
 * @param capital Posicion Inicial de Kenny
 * @param destino Ciudad a la que debe llegar Kenny
 * @param grafo
 * @param numCiudades
 * @param dineroDisponible Dinero Inicial de Kenny
 * @return
 */
int dijkstra(vector<int>& salarioCiudades, int& capital, int& destino, vector<vector<pair<int, int>>>& grafo,
             int& numCiudades, int& dineroDisponible) {

    int totalDias = -1;

    // Vectores de distancias
    vector<vector<int>> distancia (numCiudades + 1, vector<int>(10000, -1));
    vector<int> distanciaDias (numCiudades + 1, 10000);

    priority_queue<Kenny, vector<Kenny>, greater<Kenny>> pq;

    distancia[capital][0] = dineroDisponible;
    distanciaDias[0] = 0;
    pq.push({0, capital, dineroDisponible});

    bool continuar = true;
    while (!pq.empty() && continuar) {

        Kenny kenny = pq.top();
        int dias = kenny.diasTrabajados;
        int nodoActual = kenny.ciudadActual;
        int dineroActual = kenny.dineroActual;
        pq.pop();

        /**
         * La cola de prioridad ordena los estados priorizando los estados que tengan menor cantidad de dias y en caso
         * de ser iguales prioriza el estado con mejor dinero, permitiendonos asi trabajar con los mejores estados y
         * asi descartar estados innecesarios, por lo que solo se ejecuta dijkstra si el caso actual es mejor a algun
         * caso anterior.
         */
        if (dineroActual >= distancia[nodoActual][dias]) {
            // Actualizacion vector de distancia de Dias
            if (dias < distanciaDias[nodoActual]) {
                distanciaDias[nodoActual] = dias;
            }
            if (nodoActual == destino && totalDias == -1) {
                totalDias = dias;
                continuar = false;
            } else {
                // Trabajar
                if (dias + 1 < 10000) {
                    int dineroNuevo = dineroActual + salarioCiudades[nodoActual];
                    if (dineroNuevo >= distancia[nodoActual][dias + 1]) {
                        distancia[nodoActual][dias + 1] = dineroNuevo;
                        pq.push({dias + 1, nodoActual, dineroNuevo});
                    }
                }

                // Tomar el Bus
                for (vector<pair<int, int>>::iterator it = grafo[nodoActual].begin();
                    it != grafo[nodoActual].end(); it++) {

                    int nodoSiguiente = it->first;
                    int costoBus = it->second;

                    if (dineroActual >= costoBus) {
                        int dineroNuevo = dineroActual - costoBus;
                        if (dineroNuevo > distancia[nodoSiguiente][dias]) {
                            distancia[nodoSiguiente][dias] = dineroNuevo;
                            pq.push({dias, nodoSiguiente, dineroNuevo});
                        }
                    }
                }
            }
        }
    }

    return distanciaDias[destino] == 10000 ? -1 : distanciaDias[destino];
}