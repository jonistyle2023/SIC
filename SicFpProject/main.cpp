//
// Initial creation by Jonathan David Panchana Rodríguez on 27/3/2025.
//

// You can find the extended version of this project in this repository: https://github.com/jonistyle2023/SIC

// CÓDIGO DEL PROYECTO "Registro de Alertas Comunitarias" - GRUPO "E".

/* DATOS:
 * Institución: Universidad Estatal Peninsula de Santa Elena (UPSE)
 * Facultad: Sistemas y Telecomunicaciones.
 * Carrera: Ingeniería de Software.
 * Asignatura: Fundamentos de Programación.
 * Paralelo: Software 2/2 */

/* INTEGRANTES Y ROLES:
 * - Evelyn Yaritza Conforme Choez (Lider)
 * - Jonathan David Panchana Rodríguez (Desarrollador)
 * - Joseph Anthony González Perero (Supervisor)
 * - Deivy Anthony Prudente Merejildo (Editor)
 * - Katherine Villón Soriano (Diseñadora)
 * - Carlos Andrés Reyes Escalante (Tester) */

// IDEs used: Clion, Visual Studio Code, Dev-C++ & Code::Blocks

// BLOQUE DE DECLARACIONES
// Librerías necesarias para el programa
#include <iostream>
#include <iomanip>
#include <string>

// Librerias para hacer uso de las tildes y otros caracteres especiales
#include <clocale>
#include <windows.h>

// Librerías personalizadas (Contienes las funciones y procedimientos del programa)
#include "../include/consola.h" // Cambiar el color de la consola
#include "../include/archivesManager.h" // Puedes alternar la lógica de las funciones que usa arreglos con la gestión de archivos

// ESPACIO DE NOMBRES
using namespace std;

// FUNCIÓN PRINCIPAL
int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "es_ES.UTF-8");

    setColor(10);
    cout << "\n\tBienvenido al Sistema de Incidencias del Municipio de Salinas." << endl;
    setColor(4);
    cout << "\t¡Recuerda Primero registrate en el sistema para hacer tu denuncia!" << endl;

    int op;
    do {
        // Función matemática para calcular el número de incidencias y usuarios
        contarRegistros("../data/incidencias.csv");
        setColor(14);
        cout << "\n\t+-----------------------------+\n";
        cout << "\t|            MENU             |\n";
        cout << "\t+-----------------------------+\n";
        setColor(3);
        cout << "\t| 1 | Registrar incidencia    |\n";
        setColor(14);
        cout << "\t| 2 | Incidencias Registradas |\n";
        cout << "\t| 3 | Actualizar incidencias  |\n";
        cout << "\t| 4 | Eliminar incidencias    |\n";
        setColor(3);
        cout << "\t| 5 | Registrar usuario       |\n";
        setColor(12);
        cout << "\t| 6 | Salir                   |\n";
        setColor(14);
        cout << "\t+-----------------------------+\n";
        setColor(7);
        cout << "\n\tSeleccione una opción: ";
        cin >> op;

        // Si optas por usar arreglos asegúrate de llamar a las funciones de la librería "functions.h" y "functions.cpp"
        switch (op) {
            case 1: registrarIncidenciaA();
                break;
            case 2: listarIncidenciasA();
                break;
            case 3: modificarIncidenciaA();
                break;
            case 4: eliminarIncidenciaA();
                break;
            case 5: registrarUsuarioA();
                break;
            case 6: cout << "\tGracias! Vuelva Pronto..." << endl;
                break;
            default: cout << "\tOpción no válida." << endl;
                break;
        }
    } while (op != 6);

    return 0;
}
