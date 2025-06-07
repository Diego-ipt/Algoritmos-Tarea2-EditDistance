#ifndef EDIT_DDI_H
#define EDIT_DDI_H

#include <string>
#include <vector>
#include <algorithm>
#include "lcs.h"
#include <iostream>
using namespace std;

// Calcula la distancia de edición usando recursividad pura (basada en lcs_recursive).
inline int editDistanceRecursive(const string &s, const string &t) {
    int lcs = lcs_recursive_str(s, t, s.size(), t.size());
    return static_cast<int>(s.size() + t.size() - 2 * lcs);
}

// Calcula la distancia de edición usando recursividad con memoización.
inline int editDistanceMemo(const string &s, const string &t) {
    int lcs = lcs_memo_str(s, t);
    return static_cast<int>(s.size() + t.size() - 2 * lcs);
}

int editDistanceDP(string word1, string word2) {
    int size1 = word1.size();
    int size2 = word2.size();
    int verif[size1 + 1][size2 + 1]; // Matrix que se ocupa dependiendo de la palabra mas larga, tamaño O(m·n) para el espacio  

    // Si una de las cadenas está vacía, la distancia es la longitud de la otra.
    if (size1 == 0)
        return size2;
    if (size2 == 0)
        return size1;

    // Sets the first row and the first column of the verification matrix with the numerical order from 0 to the length of each word.
    for (int i = 0; i <= size1; i++)
        verif[i][0] = i;
    for (int j = 0; j <= size2; j++)
        verif[0][j] = j;

    // matrix filling.
    for (int i = 1; i <= size1; i++) {
        for (int j = 1; j <= size2; j++) {
            // calcula el costo de sustituir un carácter
            // 0 es no modificacion (letras iguales), 1 es que no lo son.
            int cost = (word2[j - 1] == word1[i - 1]) ? 0 : 1;

            if (word2[j - 1] == word1[i - 1]) {
                verif[i][j] = verif[i - 1][j - 1];  // Si son iguales, no hay costo
            } else {
                verif[i][j] = min(
                    verif[i - 1][j] + 1, // Delete
                    verif[i][j - 1] + 1  // Insert
                );
            }
        }
    }
    // Ultima posicion es la Levenshtein distance.
    return verif[size1][size2];
}

int editDistanceDPOptimized(string s, string t) {
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

#endif // EDIT_DDI_H
