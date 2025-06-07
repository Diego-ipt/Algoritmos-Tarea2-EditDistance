#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;
#include "EditDDI.h"
int main() {
    string word1, word2;
    cout << "Ingresa la primera cadena: ";
    cin >> word1;
    cout << "Ingresa la segunda cadena: ";
    cin >> word2;

    int distance = editDistanceDP(word1, word2);
    cout << "La distancia de Levenshtein es: " << distance << endl;

    return 0;
}