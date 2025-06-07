#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "EditDDI.h"

int main() {
    string s, t;
    cout << "Ingresa la primera cadena: ";
    cin >> s;
    cout << "Ingresa la segunda cadena: ";
    cin >> t;

    int distance = editDistanceDPOptimized(s, t);
    cout << "La distancia de Levenshtein es: " << distance << endl;

    return 0;
}
