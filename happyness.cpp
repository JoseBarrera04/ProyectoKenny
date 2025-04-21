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

using namespace std;

// Struct
struct Kenny {
    int diasTrabajados;
    int ciudadActual;
    int dineroActual;
};

// Funciones
int dijkstra( vector<int>& salarioCiudades, int& capital, int& destino, vector<vector<pair<int, int>>>& grafo,
    int& numCiudades, int& dineroDisponible);

/**
 * Main Principal GRAN IMPERIO AGRA
 * @return
 */
int main() {
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

        vector<vector<pair<int, int>>> grafo (numCiudades + 1);
        for (int i = 0; i < numTiquetesBus; i++) {
            int idCiudad = 0, idTiquete = 0, precioTiquete = 0;
            cin >> idCiudad >> idTiquete >> precioTiquete;

            grafo[idCiudad].push_back({idTiquete, precioTiquete});
        }

        int numDias = dijkstra(salarioCiudades, capital, destino, grafo, numCiudades, dineroDisponible);

        if (numDias != -1) {
            cout << "Kenny happiness will cost " << numDias << " days of work :)" << endl;
        } else {
            cout << "Sorry Kenny, Happiness is not for you :(" << endl;
        }
    }
    return 0;
}

/**
 * Hola
 * @param salarioCiudades
 * @param capital
 * @param destino
 * @param grafo
 * @param numCiudades
 * @return
 */
int dijkstra( vector<int>& salarioCiudades, int& capital, int& destino, vector<vector<pair<int, int>>>& grafo,
              int& numCiudades, int& dineroDisponible) {

    int totalDias = -1;

    vector<unordered_map<int, int>> distancia (numCiudades + 1);
    priority_queue<Kenny, vector<Kenny>, greater<Kenny>> pq;

    pq.push({0, capital, dineroDisponible});
    distancia[capital][dineroDisponible] = 0;
    bool continuar = true;

    while (!pq.empty() && continuar) {
        Kenny kenny = pq.top();
        pq.pop();

        if (kenny.ciudadActual == destino) {
            totalDias = kenny.diasTrabajados;
            continuar = false;
        } else {
        }
    }

    return totalDias;
}