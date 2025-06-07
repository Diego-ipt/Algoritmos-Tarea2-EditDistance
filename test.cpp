#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "EditDDI.h"

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
        cout << "La matriz de distancia es simetrica, porque d(S, T ) = d(T, S), pero se consideran todos los valores como casos de pruebas del codigo\n";
    } else {
        cout << "La matriz de distancia NO es simetrica (esto indica un error en la implementacion)\n";
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
