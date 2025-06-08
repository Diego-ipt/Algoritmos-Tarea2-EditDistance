#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

int levenshteinDist(string word1, string word2) {
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

#endif // LEVENSHTEIN_H