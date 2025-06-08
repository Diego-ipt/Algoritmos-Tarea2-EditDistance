#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int levenshteinDistOP(string s, string t) {
    int m = s.size();
    int n = t.size();

    if (m == 0) return n;
    if (n == 0) return m;

    vector<int> v0(n + 1);
    vector<int> v1(n + 1); // Se ocupan 2 vectores que se van reemplazando en vez de matrix, siendo su espacio 0(n)

    // Inicializar la primera fila
    for (int j = 0; j <= n; ++j) {
        v0[j] = j;
    }

    for (int i = 0; i < m; ++i) {
        v1[0] = i + 1; 

        for (int j = 0; j < n; ++j) {
            int deletionCost = v0[j + 1] + 1;  // Eliminar s[i]
            int insertionCost = v1[j] + 1;      // Insertar t[j]

            // Si los caracteres son iguales, podemos ignorarlos (costo 0)
            if (s[i] == t[j]) {
                v1[j + 1] = v0[j]; 
            } else {
                v1[j + 1] = min(deletionCost, insertionCost);
            }
        }
        swap(v0, v1);  // cambiamos los valores para la siguiente iteración
    }

    return v0[n];
}

#endif // LEVENSHTEIN_H