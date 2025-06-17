//
// Initial creation by Jonathan David Panchana Rodríguez on 27/3/2025.
//

// You can find the extended version of this project in this repository: https://github.com/jonistyle2023/SIC

// CÓDIGO DEL PROYECTO "Registro de Alertas Comunitarias" - GRUPO "E".

/* ----------------------------- DATOS ----------------------------
 * Institución: Universidad Estatal Peninsula de Santa Elena (UPSE)
 * Facultad: Sistemas y Telecomunicaciones.
 * Carrera: Ingeniería de Software.
 * Asignatura: Fundamentos de Programación.
 * Paralelo: Software 2/2 */

/* --------------------- INTEGRANTES Y ROLES ----------------------
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
#include "functions.h"
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
    cout << "\n\tBienvenido al Sistema de Incidencias Comunitárias del Municipio de La Libertad." << endl;
    setColor(4);
    cout << "\t¡Recuerda Primero registrate en el sistema para hacer tu denuncia!" << endl;

    int op;
    do {
        // Función matemática para calcular el número de incidencias y usuarios
        mostrarContadoresA();
        setColor(14);
        cout << "\n\t+-----------------------------+\n";
        cout << "\t|         MENU PRINCIPAL      |\n";
        cout << "\t+-----------------------------+\n";
        setColor(3);
        cout << "\t| 1 | Acceder al sistema      |\n";
        setColor(3);
        cout << "\t| 2 | Registrar usuario       |\n";
        setColor(12);
        cout << "\t| 3 | Salir                   |\n";
        setColor(14);
        cout << "\t+-----------------------------+\n";
        setColor(7);
        cout << "\n\tSeleccione una opción: ";
        cin >> op;

        switch (op) {
            case 1: {
                string rol, email;
                if (autenticarUsuario(rol)) {
                    cout << "\tIngrese su email para identificar su ID: ";
                    cin >> email;
                    int usuario_id = obtenerUsuarioId(email);
                    if (usuario_id != -1) {
                        if (rol == "ciudadano") {
                            menuCiudadano(usuario_id, rol);
                        } else if (rol == "administrador") {
                            menuAdministrador();
                        } else {
                            cout << "Rol desconocido." << endl;
                        }
                    } else {
                        cout << "No se pudo obtener el ID del usuario." << endl;
                    }
                }
                break;
            }
            case 2: registrarUsuarioA();
                break;
            case 3: setColor(10);
                cout << "\tGracias! Vuelva pronto..." << endl;
                break;
            default: setColor(12);
                cout << "\tOpción no válida." << endl;
                break;
        }
    } while (op != 3);

    return 0;
}
