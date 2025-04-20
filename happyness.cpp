/**
 * @author Jose Barrera Ramos
 * Arboles y grafos 20251
 * happyness.cpp
 */

// Librerias
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Funciones
int dijkstra();

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

        int numDias = dijkstra();

        if (numDias != -1) {
            cout << "Kenny happiness will cost " << numDias << " days of work :)" << endl;
        } else {
            cout << "Sorry Kenny, Happiness is not for you :(" << endl;
        }
    }
    return 0;
}

int dijkstra() {
    int totalDias = -1;

    vector<vector<int>> distancia (1, vector<int> (10000000000));
    priority_queue<int, vector<int>, greater<int>> pq;

    pq.push(0);

    while (!pq.empty()) {
    }

    return totalDias;
}