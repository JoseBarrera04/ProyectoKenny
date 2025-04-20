/**
 * @author Jose Barrera Ramos
 * Arboles y grafos 20251
 * happyness.cpp
 */

#include <iostream>
#include <vector>

using namespace std;

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

        cout << "Kenny happiness will cost h days of work :)" << endl;
        cout << "Sorry Kenny, Happiness is not for you :(" << endl;
    }
    return 0;
}