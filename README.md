# Algoritmos-Tarea2-EditDistance

La tarea se enfoca en el c ́alculo recursivo de la distancia de edici ́on mas corta de una cadena de texto S a una cadena de texto T con los operadores de edici ́on {Delete, Insert}.

Compilacion: Se utiliza la siguiente linea para compilar el uhr y medir los tiempos de los algoritmos implementados

g++ -std=c++11 -O0 -I. -o uhr uhr-main/uhr.cpp

Running: Se utiliza la siguiente linea para correr el uhr, donde el primer valor correspondiente a las runs debe ser 64 por temas de tiempo de ejecucion permisible, el valor inicial de caracteres a evaluar es 10, el valor maximo o final de caracteres probados es de 100, y se van aumentando las pruebas de 5 en 5 caracteres

/usr/bin/time -f "%M" ./uhr dp.csv 64 10 100 5


# Instrucciones de compilación y ejecución

## Requisitos

- Tener instalado `g++` (compilador de C++) y `make`.

## Compilación

Desde la terminal, en la carpeta del proyecto, ejecuta:

```

make

```

Esto compilará los ejecutables `test` y `uhr`.

## Ejecución

### Para correr los tests de distancia de edición:

```

./test

```

### Para medir el desempeño con `uhr`:

```

./uhr salida.csv 32 10 100 5

```

-`salida.csv`: nombre del archivo donde se guardarán los resultados.

-`32`: número de repeticiones por caso de prueba (puedes cambiarlo, mínimo 4).

-`10`: tamaño mínimo de las cadenas a probar.

-`100`: tamaño máximo de las cadenas a probar.

-`5`: incremento del tamaño en cada iteración.

**Nota:** Para que `uhr` funcione, deben existir los archivos `texto1.txt`, `texto2.txt`, `texto3.txt`, `texto4.txt` en el mismo directorio.

## Limpieza

Para borrar los ejecutables y archivos generados:

```

make clean

```
