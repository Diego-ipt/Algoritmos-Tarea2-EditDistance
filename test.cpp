#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "EditD.h"
#include "test.h"
using namespace std;

int main() {
    vector<string> cadenas = {
        "gato", "pato", "gata", "patito"
    };
    cout << "Cadenas seleccionadas: (";
    for (size_t i = 0; i < cadenas.size(); ++i) {
        cout << cadenas[i];
        if (i + 1 < cadenas.size()) cout << "), (";
    }
    cout << ")\n";

    const int N = cadenas.size();
    vector<vector<int>> matRec(N, vector<int>(N));
    vector<vector<int>> matMemo(N, vector<int>(N));
    vector<vector<int>> matDP(N, vector<int>(N));
    vector<vector<int>> matDPOpt(N, vector<int>(N));

    // Llenar matrices
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matRec[i][j]   = editDistanceRecursive(cadenas[i], cadenas[j]);
            matMemo[i][j]  = editDistanceMemo(cadenas[i], cadenas[j]);
            matDP[i][j]    = editDistanceDP(cadenas[i], cadenas[j]);
            matDPOpt[i][j] = editDistanceDPOptimized(cadenas[i], cadenas[j]);
        }
    }

    // Verificar que todas las matrices sean iguales
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            assert(matRec[i][j] == matMemo[i][j]);
            assert(matRec[i][j] == matDP[i][j]);
            assert(matRec[i][j] == matDPOpt[i][j]);
        }

    // Verificar simetria
    if (isSymmetric(matRec)) {
        cout << "La matriz de distancia es simetrica\n";
    } else {
        cout << "La matriz de distancia NO es simetrica\n";
    }

    printMatrix(matRec, cadenas);

    // Justificacion para cada caso de prueba
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Caso: \"" << cadenas[i] << "\" vs \"" << cadenas[j] << "\"\n";
            printJustification(cadenas[i], cadenas[j], matRec[i][j]);
        }
    }

    return 0;
}
