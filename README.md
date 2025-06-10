# Algoritmos-Tarea2-EditDistance
La tarea se enfoca en el c ́alculo recursivo de la distancia de edici ́on mas corta de una cadena de texto S a una cadena de texto T con los operadores de edici ́on {Delete, Insert}.

Compilacion: Se utiliza la siguiente linea para compilar el uhr y medir los tiempos de los algoritmos implementados

g++ -std=c++11 -O0 -I. -o uhr uhr-main/uhr.cpp


Running: Se utiliza la siguiente linea para correr el uhr, donde el primer valor correspondiente a las runs debe ser 64 por temas de tiempo de ejecucion permisible, el valor inicial de caracteres a evaluar es 10, el valor maximo o final de caracteres probados es de 100, y se van aumentando las pruebas de 5 en 5 caracteres


/usr/bin/time -f "%M" ./uhr dp.csv 64 10 100 5
