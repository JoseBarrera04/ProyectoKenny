/**
 * @author Jose Barrera Ramos
 * Arboles y grafos 20251
 * happyness.cpp
 */

// Librerias
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <chrono>

using namespace std;

// Struct
struct Kenny {
    int diasTrabajados;
    int ciudadActual;
    int dineroActual;

    bool operator>(const Kenny& other) const {
        return diasTrabajados > other.diasTrabajados;
    }
};

// Funciones
int dijkstra(vector<int>& salarioCiudades, int& capital, int& destino, vector<vector<pair<int, int>>>& grafo,
             int& numCiudades, int& dineroDisponible, int& incidenciaAux);

/**
 * Main Principal GRAN IMPERIO AGRA
 * @return
 */
int main() {
    auto start = chrono::high_resolution_clock::now(); // Tiempo de inicio
    int numCasos = 0;
    cin >> numCasos;

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
        int incidenciaAux = 0;

        vector<vector<pair<int, int>>> grafo(numCiudades + 1);
        for (int i = 0; i < numTiquetesBus; i++) {
            int idCiudad = 0, idTiquete = 0, precioTiquete = 0;
            cin >> idCiudad >> idTiquete >> precioTiquete;

            grafo[idCiudad].push_back({idTiquete, precioTiquete});

            if (idTiquete == destino) {
                incidenciaAux++;
            }
        }

        if (incidenciaAux == 0 && capital != destino) {
            cout << "Sorry Kenny, Happiness is not for you :(" << endl;
            continue;
        }

        int numDias = dijkstra(salarioCiudades, capital, destino, grafo, numCiudades,
                               dineroDisponible, incidenciaAux);

        if (numDias != -1) {
            cout << "Kenny happiness will cost " << numDias << " days of work :)" << endl;
        } else {
            cout << "Sorry Kenny, Happiness is not for you :(" << endl;
        }
    }
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
 * @return
 */
int dijkstra(vector<int>& salarioCiudades, int& capital, int& destino, vector<vector<pair<int, int>>>& grafo,
             int& numCiudades, int& dineroDisponible, int& incidenciaAux) {
    int totalDias = -1;

    vector<unordered_map<int, int>> distancia(numCiudades + 1);
    priority_queue<Kenny, vector<Kenny>, greater<Kenny>> pq;

    pq.push({0, capital, dineroDisponible});
    distancia[capital][dineroDisponible] = 0;
    bool continuar = true;

    if (capital == destino) {
        totalDias = 0;
        continuar = false;
    }

    while (!pq.empty() && continuar) {
        Kenny kenny = pq.top();
        pq.pop();

        int dias = kenny.diasTrabajados;
        int ciudadActual = kenny.ciudadActual;
        int dineroActual = kenny.dineroActual;

        if (ciudadActual == destino) {
            totalDias = dias;
            continuar = false;
        } else {
            // Trabajar
            int dineroFuturo = dineroActual + salarioCiudades[ciudadActual];
            int diaSiguiente = dias + 1;

            if (distancia[ciudadActual].find(dineroFuturo) == distancia[ciudadActual].end() ||
                distancia[ciudadActual][dineroFuturo] > diaSiguiente) {
                distancia[ciudadActual][dineroFuturo] = diaSiguiente;
                pq.push({diaSiguiente, ciudadActual, dineroFuturo});
            }

            // Tomar Bus
            for (auto it = grafo[ciudadActual].begin(); it != grafo[ciudadActual].end(); it++) {
                int siguienteCiudad = it->first;
                int costoBus = it->second;

                if (dineroActual >= costoBus) {
                    int dineroRestante = dineroActual - costoBus;
                    if (distancia[siguienteCiudad].find(dineroRestante) == distancia[siguienteCiudad].end() ||
                        distancia[siguienteCiudad][dineroRestante] > dias) {
                        distancia[siguienteCiudad][dineroRestante] = dias;
                        pq.push({dias, siguienteCiudad, dineroRestante});
                    }
                }
            }
        }
    }

    return totalDias;
}