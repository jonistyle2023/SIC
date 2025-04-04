//
// Created by Jonathan David Panchana Rodríguez on 27/3/2025.
//

// Bloque de declaraciones
// Declaramos las librerías necesarias para el programa
#include <iostream>
#include <limits>
#include <iomanip>
#include <string>

// Librerias para hacer uso de las tildes
#include <clocale>
#include <windows.h>

// Espacio de nombres
using namespace std;

// Definimos las constantes para el tamaño máximo de incidencias y usuarios
const int MAX_INCIDENTES = 100;
const int MAX_USUARIOS = 100;

// Definimos las estructuras para Incidencia y Usuario, que son con las que vamos a trabajar
struct Incidencia {
    int id;
    string titulo;
    string descripcion;
    string tipo_incidencia;
    string ubicacion;
    string estado;
    int usuario_id;
};

struct Usuario {
    int id;
    string nombre;
    string email;
    string contrasena;
    string rol;
};

// Definimos los arreglos para almacenar las incidencias y usuarios
Incidencia incidencias[MAX_INCIDENTES];
Usuario usuarios[MAX_USUARIOS];
int totalIncidencias = 0;
int totalUsuarios = 0;

// Funciones para manejar incidencias y usuarios
void registrarIncidencia() {
    if (totalIncidencias >= MAX_INCIDENTES) {
        cout << "No se pueden registrar más incidencias." << endl;
        return;
    }

    Incidencia nuevaIncidencia;
    nuevaIncidencia.id = totalIncidencias + 1; // Asignar ID automáticamente
    cout << "Título: ";
    cin.ignore();
    getline(cin, nuevaIncidencia.titulo);
    cout << "Descripción: ";
    getline(cin, nuevaIncidencia.descripcion);
    cout << "Ubicación: ";
    getline(cin, nuevaIncidencia.ubicacion);

    cout << "Tipo de incidencia (1: Avería pública, 2: Siniestro vehicular, 3: Incendio, 4: Robo, 5: Otro): ";
    int tipo;
    cin >> tipo;
    switch (tipo) {
        case 1: nuevaIncidencia.tipo_incidencia = "averia_publica"; break;
        case 2: nuevaIncidencia.tipo_incidencia = "siniestro_vehicular"; break;
        case 3: nuevaIncidencia.tipo_incidencia = "incendio"; break;
        case 4: nuevaIncidencia.tipo_incidencia = "robo"; break;
        case 5: nuevaIncidencia.tipo_incidencia = "otro"; break;
        default: cout << "Tipo inválido." << endl; return;
    }

    cout << "ID del usuario que reporta: ";
    cin >> nuevaIncidencia.usuario_id;

    nuevaIncidencia.estado = "pendiente";
    incidencias[totalIncidencias++] = nuevaIncidencia;

    cout << "¡Incidencia registrada exitosamente!" << endl;
}

// Función para eliminar una incidencia
void eliminarIncidencia() {
    int id;
    cout << "Digite el ID de la incidencia a eliminar: ";
    cin >> id;

    for (int i = 0; i < totalIncidencias; i++) {
        if (incidencias[i].id == id) {
            for (int j = i; j < totalIncidencias - 1; j++) {
                incidencias[j] = incidencias[j + 1];
            }
            totalIncidencias--;
            cout << "Incidencia eliminada con éxito." << endl;
            return;
        }
    }
    cout << "Incidencia no encontrada." << endl;
}

// Función para mostrar todas las incidencias registradas
void listarIncidencias() {
    cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;
    cout << "|   ID   |        Título        |     Descripción      |         Tipo         |      Ubicación       |  Estado  |" << endl;
    cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;

    for (int i = 0; i < totalIncidencias; i++) {
        cout << "| " << left << setw(6) << incidencias[i].id << " | "
             << setw(20) << incidencias[i].titulo << " | "
             << setw(20) << incidencias[i].descripcion << " | "
             << setw(20) << incidencias[i].tipo_incidencia << " | "
             << setw(20) << incidencias[i].ubicacion << " | "
             << setw(8) << incidencias[i].estado << " |" << endl;
        cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;
    }
}

// Función para registrar un nuevo usuario
void registrarUsuario() {
    if (totalUsuarios >= MAX_USUARIOS) {
        cout << "No se pueden registrar más usuarios." << endl;
        return;
    }

    Usuario nuevoUsuario;
    nuevoUsuario.id = totalUsuarios + 1; // Asignar ID automáticamente
    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nuevoUsuario.nombre);
    cout << "Email: ";
    getline(cin, nuevoUsuario.email);
    cout << "Contraseña: ";
    getline(cin, nuevoUsuario.contrasena);

    cout << "Rol (1: Ciudadano, 2: Administrador): ";
    int rol;
    cin >> rol;
    nuevoUsuario.rol = (rol == 1) ? "ciudadano" : "administrador";

    usuarios[totalUsuarios++] = nuevoUsuario;

    cout << "¡Usuario registrado exitosamente!" << endl;
}

// Función principal
int main() {

    SetConsoleOutputCP(65001); // Para poder hacer uso de las tildes
    SetConsoleCP(65001);       // UTF-8 para entrada
    setlocale(LC_ALL, "es_ES.UTF-8");

    int op;

    do {
        cout << "\n+-----------------------------+\n";
        cout << "|            MENU             |\n";
        cout << "+-----------------------------+\n";
        cout << "| 1 | Registrar incidencia    |\n";
        cout << "| 2 | Eliminar incidencia     |\n";
        cout << "| 3 | Incidencias Registradas |\n";
        cout << "| 4 | Registrar usuario       |\n";
        cout << "| 5 | Salir                   |\n";
        cout << "+-----------------------------+\n";
        cout << "Seleccione una opción: ";
        cin >> op;

        switch (op) {
            case 1: registrarIncidencia(); break;
            case 2: eliminarIncidencia(); break;
            case 3: listarIncidencias(); break;
            case 4: registrarUsuario(); break;
            case 5: cout << "Saliendo..." << endl; break;
            default: cout << "Opción no válida." << endl; break;
        }
    } while (op != 5);

    return 0;
}
