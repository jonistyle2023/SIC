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
/* ADVERTENCIA: Si no compila en Windows o algún compilador online,
 * comenta o elimina estas dos librerías */
#include <clocale> // Elimina o comenta esta línea si no compila
#include <windows.h> // Elimina o comenta esta línea si no compila

// Espacio de nombres
using namespace std;

void setColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Primero definimos las constantes para determinar el máximo de incidencias y usuarios
const int MAX_INCIDENTES = 100;
const int MAX_USUARIOS = 100;

// luego se define las estructuras para Incidencia y Usuario, que son con las que vamos a trabajar
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

// Función para registrar una nueva incidencia
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

    cout << "¡Incidencia registrada exitosamente! El ID asignado es: " << nuevaIncidencia.id << endl;
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

// Función para modificar una incidencia
void modificarIncidencia() {
    int id;
    cout << "Digite el ID de la incidencia a modificar: ";
    cin >> id;

    // Buscar la incidencia por ID
    for (int i = 0; i < totalIncidencias; i++) {
        if (incidencias[i].id == id) {
            cout << "Incidencia encontrada. Puede modificar los siguientes campos:" << endl;

            // Mostrar los datos actuales
            cout << "Título actual: " << incidencias[i].titulo << endl;
            cout << "Nuevo título (deje vacío para no modificar): ";
            cin.ignore();
            string nuevoTitulo;
            getline(cin, nuevoTitulo);
            if (!nuevoTitulo.empty()) {
                incidencias[i].titulo = nuevoTitulo;
            }

            cout << "Descripción actual: " << incidencias[i].descripcion << endl;
            cout << "Nueva descripción (deje vacío para no modificar): ";
            string nuevaDescripcion;
            getline(cin, nuevaDescripcion);
            if (!nuevaDescripcion.empty()) {
                incidencias[i].descripcion = nuevaDescripcion;
            }

            cout << "Ubicación actual: " << incidencias[i].ubicacion << endl;
            cout << "Nueva ubicación (deje vacío para no modificar): ";
            string nuevaUbicacion;
            getline(cin, nuevaUbicacion);
            if (!nuevaUbicacion.empty()) {
                incidencias[i].ubicacion = nuevaUbicacion;
            }

            cout << "Tipo de incidencia actual: " << incidencias[i].tipo_incidencia << endl;
            cout << "Nuevo tipo de incidencia (1: Avería pública, 2: Siniestro vehicular, 3: Incendio, 4: Robo, 5: Otro): ";
            int nuevoTipo;
            cin >> nuevoTipo;
            switch (nuevoTipo) {
                case 1: incidencias[i].tipo_incidencia = "averia_publica"; break;
                case 2: incidencias[i].tipo_incidencia = "siniestro_vehicular"; break;
                case 3: incidencias[i].tipo_incidencia = "incendio"; break;
                case 4: incidencias[i].tipo_incidencia = "robo"; break;
                case 5: incidencias[i].tipo_incidencia = "otro"; break;
                default: cout << "Tipo no modificado." << endl; break;
            }

            cout << "Estado actual: " << incidencias[i].estado << endl;
            cout << "Nuevo estado (pendiente, en progreso, resuelto): ";
            string nuevoEstado;
            cin.ignore();
            getline(cin, nuevoEstado);
            if (!nuevoEstado.empty()) {
                incidencias[i].estado = nuevoEstado;
            }

            cout << "¡Incidencia modificada con éxito!" << endl;
            return;
        }
    }

    // Si no se encuentra la incidencia
    cout << "Incidencia no encontrada." << endl;
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

    /* ADVERTENCIA:
     * Configuración de la consola para permitir el uso de caracteres UTF-8
     * y establecer la localización a español.
     * Asimismo, si te presenta errores, elimina o comenta estas líneas.
     */

    SetConsoleOutputCP(65001); // Elimina o comenta esta línea si no compila
    SetConsoleCP(65001);       // Elimina o comenta esta línea si no compila
    setlocale(LC_ALL, "es_ES.UTF-8"); // Elimina o comenta esta línea si no compila

    int op;

    do {
        setColor(14);
        cout << "\n+-----------------------------+\n";
        cout << "|            MENU             |\n";
        cout << "+-----------------------------+\n";
        cout << "| 1 | Registrar incidencia    |\n";
        cout << "| 2 | Incidencias Registradas |\n";
        cout << "| 3 | Actualizar incidencias  |\n";
        cout << "| 4 | Eliminar incidencias    |\n";
        cout << "| 5 | Registrar usuario       |\n";
        setColor(12);
        cout << "| 6 | Salir                   |\n";
        setColor(14);
        cout << "+-----------------------------+\n";
        setColor(7);
        cout << "Seleccione una opción: ";
        cin >> op;

        switch (op) {
            case 1: registrarIncidencia(); break;
            case 2: listarIncidencias(); break;
            case 3: modificarIncidencia(); break;
            case 4: eliminarIncidencia(); break;
            case 5: registrarUsuario(); break;
            case 6: cout << "Saliendo..." << endl; break;
            default: cout << "Opción no válida." << endl; break;
        }
    } while (op != 6);

    return 0;
}
