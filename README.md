# Algoritmos-Tarea2-EditDistance

La tarea se enfoca en el c ́alculo recursivo de la distancia de edici ́on mas corta de una cadena de texto S a una cadena de texto T con los operadores de edici ́on {Delete, Insert}.

Compilacion: Se utiliza la siguiente linea para compilar el uhr y medir los tiempos de los algoritmos implementados

g++ -std=c++11 -O0 -I. -o uhr uhr-main/uhr.cpp

Running: Se utiliza la siguiente linea para correr el uhr, donde el primer valor correspondiente a las runs debe ser 64 por temas de tiempo de ejecucion permisible, el valor inicial de caracteres a evaluar es 10, el valor maximo o final de caracteres probados es de 100, y se van aumentando las pruebas de 5 en 5 caracteres

/usr/bin/time -f "%M" ./uhr dp.csv 64 10 100 5


# Instrucciones de compilación y ejecución

## Requisitos

- Tener instalado `g++` (compilador de C++). Si usas Windows, puedes instalarlo con [MinGW](https://www.mingw-w64.org/) o usando WSL.
- (Opcional) Tener instalado `make` para automatizar la compilación.

## Compilación automática (con Makefile)

Desde la terminal, en la carpeta del proyecto, ejecuta:

```

make

```

Esto compilará los ejecutables `test` y `uhr`.

## Compilación manual en Windows (sin make)

Abre una terminal en la carpeta del proyecto y ejecuta:

```

g++ -std=c++11 -O2 -Wall -I. -o test test.cpp

g++ -std=c++11 -O2 -Wall -I. -o uhr uhr-main/uhr.cpp

```

Esto generará los ejecutables `test.exe` y `uhr.exe`.

## Ejecución

### Para correr los tests de distancia de edición:

```

./test

```

o en Windows:

```

test.exe

```

### Para medir el desempeño con `uhr`:

```

./uhr salida.csv 32 10 100 5

```

o en Windows:

```

uhr.exe salida.csv 32 10 100 5

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

o simplemente borra los archivos `test.exe`, `uhr.exe` y los `.csv` manualmente.

## ¿Cómo instalar `make` en Windows?

Si deseas usar el comando `make` en Windows, puedes instalarlo de las siguientes formas:

### Opción 1: Instalar MinGW con MSYS

1. Descarga e instala [MinGW](https://www.mingw-w64.org/).
2. Durante la instalación, selecciona la opción para instalar MSYS.
3. Abre la terminal MSYS (no la CMD de Windows).
4. Escribe `make --version` para verificar que está instalado.

### Opción 2: Instalar Make con Chocolatey

1. Instala [Chocolatey](https://chocolatey.org/install) si no lo tienes.
2. Abre una terminal como administrador y ejecuta:

   ```

   choco install make

   ```
3. Cierra y abre la terminal, luego verifica con:

   ```

   make --version

   ```

### Opción 3: Usar WSL (Subsistema de Windows para Linux)

1. Instala WSL siguiendo la [guía oficial](https://learn.microsoft.com/es-es/windows/wsl/install).
2. Abre una terminal de Ubuntu o tu distribución preferida.
3. Ejecuta:

   ```

   sudo apt update

   sudo apt install make

   ```
4. Usa `make` normalmente en la terminal WSL.
