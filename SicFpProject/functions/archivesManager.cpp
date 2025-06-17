//
// Created by Jonathan Panchana Rodríguez on 13/6/2025.
//

/*
 * NOTA: Esta clase contiene las funciones principales para gestionar incidencias y usuarios, como:
 * registrar, listar, modificar y eliminar. Además, incluye una función para mostrar estadísticas.
 * Su principal función es aportar la lógica de negocio y manipulación de datos a la clase principal "mainFp".
 */

// BLOQUE DE DECLARACIONES
// Librerías necesarias
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <limits>

// Librerías personalizadas
#include "archivesManager.h"
#include "consola.h"

// ESPACIO ENTRE NOMBRES
using namespace std;

// --- FUNCIÓNES PARA LA GESTIÓN DE USUARIOS ---

// Función para autenticar los usuarios del sistema
bool autenticarUsuario(string &rol) {
    string email, contrasena;
    cout << "\tEmail: ";
    cin >> email;
    cout << "\tContraseña: ";
    cin >> contrasena;

    ifstream archivo("../SicFpProject/data/usuarios.csv");
    if (!archivo.is_open()) {
        setColor(12);
        cout << "\tError al abrir el archivo de usuarios." << endl;
        setColor(7);
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, emailArchivo, contrasenaArchivo, rolArchivo;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, emailArchivo, ',');
        getline(ss, contrasenaArchivo, ',');
        getline(ss, rolArchivo, ',');

        if (email == emailArchivo && contrasena == contrasenaArchivo) {
            rol = rolArchivo;
            archivo.close();
            return true;
        }
    }

    archivo.close();
    setColor(12);
    cout << "\tCredenciales incorrectas!" << endl;
    setColor(7);
    return false;
}

// Función para registrar un nuevo usuario
void registrarUsuarioA() {
    ofstream archivo("../SicFpProject/data/usuarios.csv", ios::app);
    if (!archivo.is_open()) {
        cout << "\tNo se pudo abrir el archivo de usuarios." << endl;
        return;
    }

    int id = contarRegistros("../SicFpProject/data/usuarios.csv") + 1;
    string nombre, email, contrasena, rol;
    int tipoRol;

    cout << "\tNombre: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "\tEmail: ";
    getline(cin, email);
    cout << "\tContraseña: ";
    getline(cin, contrasena);
    cout << "\tRol (1: Ciudadano, 2: Administrador): ";
    cin >> tipoRol;

    rol = (tipoRol == 1) ? "ciudadano" : "administrador";

    archivo << id << "," << nombre << "," << email << "," << contrasena << "," << rol << "\n";
    archivo.close();

    setColor(10);
    cout << "\t¡Usuario registrado exitosamente! ID asignado: " << id << endl;
}

// Función para obtener el ID del usuario a partir del email para su registro
int obtenerUsuarioId(const string &email) {
    ifstream archivo("../SicFpProject/data/usuarios.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return -1;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, emailArchivo, contrasena, rol;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, emailArchivo, ',');
        getline(ss, contrasena, ',');
        getline(ss, rol, ',');

        if (email == emailArchivo) {
            archivo.close();
            return stoi(id);
        }
    }

    archivo.close();
    return -1; // Retorna -1 si no se encuentra el usuario
}

// --- FUNCIONES PARA LA GESTIÓN DE INCIDENCIAS ---

// Función para registrar una nueva incidencia
void registrarIncidenciaA(int usuario_id, const string &rol) {
    ofstream archivo("../SicFpProject/data/incidencias.csv", ios::app);
    if (!archivo.is_open()) {
        setColor(12);
        cout << "No se pudo abrir el archivo de incidencias." << endl;
        return;
    }

    int id = contarRegistros("../SicFpProject/data/incidencias.csv") + 1;
    string titulo, descripcion, ubicacion, tipo_incidencia, estado = "pendiente";
    int tipo;

    setColor(7);
    cout << "\tTítulo: ";
    cin.ignore();
    getline(cin, titulo);
    cout << "\tDescripción: ";
    getline(cin, descripcion);
    cout << "\tUbicación: ";
    getline(cin, ubicacion);
    cout << "\tTipo de incidencia";
    cout << "\n\t(1: Avería pública, 2: Siniestro vehicular, 3: Incendio, 4: Robo, 5: Otro): ";
    cin >> tipo;

    switch (tipo) {
        case 1: tipo_incidencia = "averia_publica";
            break;
        case 2: tipo_incidencia = "siniestro_vehicular";
            break;
        case 3: tipo_incidencia = "incendio";
            break;
        case 4: tipo_incidencia = "robo";
            break;
        case 5: tipo_incidencia = "otro";
            break;
        default: cout << "Tipo inválido." << endl;
            return;
    }

    archivo << id << "," << titulo << "," << descripcion << "," << tipo_incidencia << ","
            << ubicacion << "," << estado << "," << usuario_id << "\n";
    archivo.close();
    setColor(10);
    cout << "\t¡Incidencia registrada exitosamente! El ID asignado es: " << id << endl;
}

// Función para listar todas las incidencias
void listarIncidenciasA() {
    ifstream archivo("../SicFpProject/data/incidencias.csv");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de incidencias." << endl;
        return;
    }

    string linea;
    setColor(5);
    cout <<
            "+--------+----------------------+----------------------+----------------------+----------------------+----------+"
            << endl;
    cout <<
            "|   ID   |        Título        |     Descripción      |         Tipo         |      Ubicación       |  Estado  |"
            << endl;
    cout <<
            "+--------+----------------------+----------------------+----------------------+----------------------+----------+"
            << endl;

    setColor(7);
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, titulo, descripcion, tipo_incidencia, ubicacion, estado, usuario_id;

        getline(ss, id, ',');
        getline(ss, titulo, ',');
        getline(ss, descripcion, ',');
        getline(ss, tipo_incidencia, ',');
        getline(ss, ubicacion, ',');
        getline(ss, estado, ',');
        getline(ss, usuario_id, ',');

        cout << "| " << left << setw(6) << id << " | "
                << setw(20) << titulo << " | "
                << setw(20) << descripcion << " | "
                << setw(20) << tipo_incidencia << " | "
                << setw(20) << ubicacion << " | "
                << setw(8) << estado << " |" << endl;
        cout <<
                "+--------+----------------------+----------------------+----------------------+----------------------+----------+"
                << endl;
    }

    archivo.close();
}

// Función para modificar una incidencia
void modificarIncidenciaA() {
    ifstream archivoEntrada("../SicFpProject/data/incidencias.csv");
    if (!archivoEntrada.is_open()) {
        cout << "No se pudo abrir el archivo de incidencias." << endl;
        return;
    }

    vector<string> lineas;
    string linea;
    int id, idBuscado;
    cout << "\tDigite el ID de la incidencia a modificar: ";
    cin >> idBuscado;

    bool encontrado = false;
    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string idStr, titulo, descripcion, tipo_incidencia, ubicacion, estado, usuario_id;
        getline(ss, idStr, ',');
        id = stoi(idStr);

        if (id == idBuscado) {
            encontrado = true;
            cout << "\tIncidencia encontrada. Modifique los campos:\n";

            cout << "\tNuevo título: ";
            cin.ignore();
            getline(cin, titulo);
            cout << "\tNueva descripción: ";
            getline(cin, descripcion);
            cout << "\tNueva ubicación: ";
            getline(cin, ubicacion);
            cout << "\tNuevo estado (pendiente, en progreso, resuelto): ";
            getline(cin, estado);

            string nuevaLinea = to_string(id) + "," + titulo + "," + descripcion + "," + tipo_incidencia + "," +
                                ubicacion + "," + estado + "," + usuario_id;
            lineas.push_back(nuevaLinea);
        } else {
            lineas.push_back(linea);
        }
    }
    archivoEntrada.close();

    if (!encontrado) {
        cout << "\tIncidencia no encontrada." << endl;
        return;
    }

    ofstream archivoSalida("../SicFpProject/data/incidencias.csv");
    for (const string &l: lineas) {
        archivoSalida << l << "\n";
    }
    archivoSalida.close();
    cout << "\t¡Incidencia modificada con éxito!" << endl;
}

// Función para eliminar una incidencia
void eliminarIncidenciaA() {
    ifstream archivoEntrada("../SicFpProject/data/incidencias.csv");
    if (!archivoEntrada.is_open()) {
        cout << "No se pudo abrir el archivo de incidencias." << endl;
        return;
    }

    vector<string> lineas;
    string linea;
    int id, idBuscado;
    cout << "\tDigite el ID de la incidencia a eliminar: ";
    cin >> idBuscado;

    bool encontrado = false;
    while (getline(archivoEntrada, linea)) {
        stringstream ss(linea);
        string idStr;
        getline(ss, idStr, ',');
        id = stoi(idStr);

        if (id == idBuscado) {
            encontrado = true;
        } else {
            lineas.push_back(linea);
        }
    }
    archivoEntrada.close();

    if (!encontrado) {
        cout << "\tIncidencia no encontrada." << endl;
        return;
    }

    ofstream archivoSalida("../SicFpProject/data/incidencias.csv");
    for (const string &l: lineas) {
        archivoSalida << l << "\n";
    }
    archivoSalida.close();
    cout << "\t¡Incidencia eliminada con éxito!" << endl;
}

// --- FUNCIONES ADICIONALES DEL SISTEMA ---

// Función para mostrar el menú de USUARIOS CON ROL DE CIUDADANO
void menuCiudadano(int usuario_id, const string &rol) {
    int op;
    do {
        setColor(14);
        cout << "\n\t+-----------------------------+\n";
        cout << "\t|       MENU CIUDADANO        |\n";
        cout << "\t+-----------------------------+\n";
        setColor(3);
        cout << "\t| 1 | Registrar incidencia    |\n";
        setColor(14);
        cout << "\t| 2 | Listar incidencias      |\n";
        cout << "\t| 3 | Modificar incidencia    |\n";
        setColor(12);
        cout << "\t| 4 | Salir                   |\n";
        setColor(14);
        cout << "\t+-----------------------------+\n";
        setColor(7);
        cout << "\n\tSeleccione una opción: ";
        cin >> op;

        // Validar entrada
        if (cin.fail()) {
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
            cout << "\tEntrada no válida. Por favor, ingrese un número." << endl;
            continue; // Vuelve al inicio del bucle
        }

        switch (op) {
            case 1: registrarIncidenciaA(usuario_id, rol);
                break;
            case 2: listarIncidenciasA();
                break;
            case 3: modificarIncidenciaA();
                break;
            case 4: setColor(10);
                cout << "\tSaliendo del menú ciudadano..." << endl;
                break;
            default: setColor(12);
                cout << "\tOpción no válida." << endl;
                break;
        }
    } while (op != 4);
}

// Función para mostrar el menú de USUARIOS CON ROL DE ADMINISTRADOR
void menuAdministrador() {
    int op;
    do {
        setColor(14);
        cout << "\n\t+-----------------------------+\n";
        cout << "\t|      MENU ADMINISTRADOR     |\n";
        cout << "\t+-----------------------------+\n";
        cout << "\t| 1 | Modificar incidencia    |\n";
        setColor(12);
        cout << "\t| 2 | Eliminar incidencia     |\n";
        setColor(14);
        cout << "\t| 3 | Listar incidencias      |\n";
        setColor(12);
        cout << "\t| 4 | Salir                   |\n";
        setColor(14);
        cout << "\t+-----------------------------+\n";
        setColor(7);
        cout << "\n\tSeleccione una opción: ";
        cin >> op;

        switch (op) {
            case 1: modificarIncidenciaA();
                break;
            case 2: eliminarIncidenciaA();
                break;
            case 3: listarIncidenciasA();
                break;
            case 4: setColor(10);
                cout << "\tSaliendo del menú administrador..." << endl;
                break;
            default: setColor(12);
                cout << "\tOpción no válida." << endl;
                break;
        }
    } while (op != 4);
}

// Función para contar registros en un archivo
int contarRegistros(const string &rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) return 0;

    int contador = 0;
    string linea;
    while (getline(archivo, linea)) {
        contador++;
    }
    archivo.close();
    return contador;
}

// Función para mostrar contadores de incidencias y usuarios
void mostrarContadoresA() {
    // Contar registros en los archivos correspondientes
    int totalIncidencias = contarRegistros("../SicFpProject/data/incidencias.csv");
    int totalUsuarios = contarRegistros("../SicFpProject/data/usuarios.csv");

    // Mostrar los contadores en un formato visual
    setColor(11); // Color ÚNICAMENTE para destacar el texto
    cout << "\n\t+-----------------------------------+\n";
    cout << "\t|   ESTADÍSTICAS DEL SISTEMA        |\n";
    cout << "\t+-----------------------------------+\n";
    cout << "\t| Incidencias registradas: " << totalIncidencias << "\t----|\n";
    cout << "\t| Usuarios registrados:    " << totalUsuarios << "\t----|\n";
    cout << "\t+-----------------------------------+\n";
    setColor(7); // Restaurar color por DEFECTO
}
