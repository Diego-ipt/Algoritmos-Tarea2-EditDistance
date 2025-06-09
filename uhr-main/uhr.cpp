/** uhr: generic time performance tester
 * Author: LELE
 *
 * Things to set up:
 * 0. Includes: include all files to be tested,
 * 1. Time unit: in elapsed_time,
 * 2. What to write on time_data,
 * 3. Data type and distribution of RNG,
 * 4. Additive or multiplicative stepping,
 * 5. The experiments: in outer for loop. */


 // usar en terminal para medir el peak de uso de memoria /usr/bin/time -f "%M" myprogram.o
#include <cstdint>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "utils.cpp"
#include <sstream>


 // Include to be tested files here
#include "EditD.h"


// Lee un archivo de texto completo a un string (mantiene saltos de línea)
std::string leerArchivoComoCadena(const std::string& ruta) {
    std::ifstream archivo(ruta);
    std::ostringstream contenido;
    contenido << archivo.rdbuf(); // lee todo, incluyendo \n y espacios
    return contenido.str();
}

int main(int argc, char *argv[])
{
    // Validate and sanitize input
    std::int64_t runs, lower, upper, step;
    validate_input(argc, argv, runs, lower, upper, step);

    // Set up clock variables
    std::int64_t n, i, executed_runs;
    std::int64_t total_runs_additive = runs * (((upper - lower) / step) + 1);
    std::int64_t total_runs_multiplicative = runs * (floor(log(upper / double(lower)) / log(step)) + 1);
    std::vector<double> times(runs);
    std::vector<double> q;
    double mean_time, time_stdev, dev;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed_time = end_time - begin_time;

    // Set up random number generation
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<std::int64_t> u_distr; // change depending on app

    // File to write time data
    std::ofstream time_data;
    time_data.open(argv[1]);

    // Begin testing
    std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
    executed_runs = 0;

    std::vector<std::string> rutas = {
        "archivo1.txt", "archivo2.txt", "archivo3.txt", "archivo4.txt"
    };
    std::vector<std::string> cadenas;
    for (const auto& ruta : rutas) {
        cadenas.push_back(leerArchivoComoCadena(ruta));
    }
    int N = cadenas.size();

    time_data << "pair,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

    executed_runs = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;

            std::string label = rutas[i] + "-" + rutas[j];

            mean_time = 0;
            time_stdev = 0;

            for (int k = 0; k < runs; ++k) {
                display_progress(++executed_runs, runs * 12);

                begin_time = std::chrono::high_resolution_clock::now();
                int distance = editDistanceDPOptimized(cadenas[i], cadenas[j]);
                //editDistanceRecursive, editDistanceMemo, editDistanceDP, editDistanceDPOptimized

                end_time = std::chrono::high_resolution_clock::now();

                elapsed_time = end_time - begin_time;
                times[k] = elapsed_time.count();

                mean_time += times[k];
            }

            mean_time /= runs;

            for (int k = 0; k < runs; ++k) {
                dev = times[k] - mean_time;
                time_stdev += dev * dev;
            }

            time_stdev /= runs - 1;
            time_stdev = std::sqrt(time_stdev);

            quartiles(times, q);

            time_data << label << "," << mean_time << "," << time_stdev << ",";
            time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << q[4] << std::endl;
        }
    }


    // This is to keep loading bar after testing
    std::cerr << std::endl << std::endl;
    std::cerr << "\033[1;32mDone!\033[0m" << std::endl;

    time_data.close();

    return 0;
}
