#ifndef TEST_EDIT_DISTANCE_H
#define TEST_EDIT_DISTANCE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "EditD.h"

using namespace std;

// Explica la correctitud del resultado de distancia de edicion para cualquier par de cadenas.
// Describe la secuencia minima de operaciones para transformar s en t usando solo inserciones y eliminaciones.
void printJustification(const string& s, const string& t, int dist) {
    cout << "Justificacion: ";
    if (s == t) {
        cout << "Las cadenas son identicas, no se requiere ninguna operacion. Distancia = 0." << endl;
        return;
    }

    // Construir la tabla de DP para reconstruir el camino optimo (solo insercion y eliminacion)
    int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= m; ++j)
        dp[0][j] = j;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(dp[i - 1][j],    // eliminacion
                                    dp[i][j - 1]);   // insercion
        }
    }

    // Reconstruir la secuencia de operaciones
    int i = n, j = m;
    vector<string> ops;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && s[i - 1] == t[j - 1]) {
            // No operacion
            --i; --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            ops.push_back("Eliminar '" + string(1, s[i - 1]) + "' en la posicion " + to_string(i - 1));
            --i;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            ops.push_back("Insertar '" + string(1, t[j - 1]) + "' en la posicion " + to_string(i));
            --j;
        }
    }
    reverse(ops.begin(), ops.end());
    cout << "Para transformar \"" << s << "\" en \"" << t << "\" se requieren " << dist << " operaciones minimas (solo inserciones y eliminaciones):\n";
    for (const auto& op : ops) {
        cout << "  - " << op << endl;
    }
}

// Verifica si una matriz es simetrica
bool isSymmetric(const vector<vector<int>>& mat) {
    int n = mat.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (mat[i][j] != mat[j][i])
                return false;
    return true;
}

// Imprime la matriz de distancias
void printMatrix(const vector<vector<int>>& mat, const vector<string>& nombres) {
    int n = mat.size();
    cout << "Matriz de distancias:\n    ";
    for (int j = 0; j < n; ++j)
        cout << nombres[j] << " ";
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        cout << nombres[i] << " ";
        for (int j = 0; j < n; ++j)
            cout << "  " << mat[i][j] << " ";
        cout << "\n";
    }
}
#endif // TEST_EDIT_DISTANCE_H
