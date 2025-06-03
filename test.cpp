#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "EditDDI.h"

// Explica la correctitud del resultado de distancia de edicion para cualquier par de cadenas.
// Describe la secuencia minima de operaciones para transformar s en t usando solo inserciones y eliminaciones.
void printJustification(const std::string& s, const std::string& t, int dist) {
    std::cout << "Justificacion: ";
    if (s == t) {
        std::cout << "Las cadenas son identicas, no se requiere ninguna operacion. Distancia = 0." << std::endl;
        return;
    }

    // Construir la tabla de DP para reconstruir el camino optimo (solo insercion y eliminacion)
    int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= m; ++j)
        dp[0][j] = j;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + std::min(dp[i - 1][j],    // eliminacion
                                         dp[i][j - 1]);   // insercion
        }
    }

    // Reconstruir la secuencia de operaciones
    int i = n, j = m;
    std::vector<std::string> ops;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && s[i - 1] == t[j - 1]) {
            // No operacion
            --i; --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            ops.push_back("Eliminar '" + std::string(1, s[i - 1]) + "' en la posicion " + std::to_string(i - 1));
            --i;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            ops.push_back("Insertar '" + std::string(1, t[j - 1]) + "' en la posicion " + std::to_string(i));
            --j;
        }
    }
    std::reverse(ops.begin(), ops.end());
    std::cout << "Para transformar \"" << s << "\" en \"" << t << "\" se requieren " << dist << " operaciones minimas (solo inserciones y eliminaciones):\n";
    for (const auto& op : ops) {
        std::cout << "  - " << op << std::endl;
    }
}

// Verifica si una matriz es simetrica
bool isSymmetric(const std::vector<std::vector<int>>& mat) {
    int n = mat.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (mat[i][j] != mat[j][i])
                return false;
    return true;
}

// Imprime la matriz de distancias
void printMatrix(const std::vector<std::vector<int>>& mat, const std::vector<std::string>& nombres) {
    int n = mat.size();
    std::cout << "Matriz de distancias:\n    ";
    for (int j = 0; j < n; ++j)
        std::cout << nombres[j] << " ";
    std::cout << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << nombres[i] << " ";
        for (int j = 0; j < n; ++j)
            std::cout << "  " << mat[i][j] << " ";
        std::cout << "\n";
    }
}

int main() {
    std::vector<std::string> cadenas = {
        "gato", "pato", "gata", "patito"
    };
    std::cout << "Cadenas seleccionadas: (";
    for (size_t i = 0; i < cadenas.size(); ++i) {
        std::cout << cadenas[i];
        if (i + 1 < cadenas.size()) std::cout << "), (";
    }
    std::cout << ")\n";

    const int N = cadenas.size();
    std::vector<std::vector<int>> matRec(N, std::vector<int>(N));
    std::vector<std::vector<int>> matMemo(N, std::vector<int>(N));
    std::vector<std::vector<int>> matDP(N, std::vector<int>(N));
    std::vector<std::vector<int>> matDPOpt(N, std::vector<int>(N));

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
        std::cout << "La matriz de distancia es simetrica, porque d(S, T ) = d(T, S), pero se consideran todos los valores como casos de pruebas del codigo\n";
    } else {
        std::cout << "La matriz de distancia NO es simetrica (esto indica un error en la implementacion)\n";
    }

    printMatrix(matRec, cadenas);

    // Justificacion para cada caso de prueba
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << "Caso: \"" << cadenas[i] << "\" vs \"" << cadenas[j] << "\"\n";
            printJustification(cadenas[i], cadenas[j], matRec[i][j]);
        }
    }

    return 0;
}
