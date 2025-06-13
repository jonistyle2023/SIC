//
// Created by Jonathan Panchana Rodríguez on 13/6/2025.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "archivesManager.h"

using namespace std;

// Función para registrar una nueva incidencia
void registrarIncidenciaA() {
    ofstream archivo("../SicFpProject/data/incidencias.csv", ios::app);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de incidencias." << endl;
        return;
    }

    int id = contarRegistros("../SicFpProject/data/incidencias.csv") + 1;
    string titulo, descripcion, ubicacion, tipo_incidencia, estado = "pendiente";
    int usuario_id, tipo;

    cout << "\tTítulo: ";
    cin.ignore();
    getline(cin, titulo);
    cout << "\tDescripción: ";
    getline(cin, descripcion);
    cout << "\tUbicación: ";
    getline(cin, ubicacion);
    cout << "\tTipo de incidencia (1: Avería pública, 2: Siniestro vehicular, 3: Incendio, 4: Robo, 5: Otro): ";
    cin >> tipo;

    switch (tipo) {
        case 1: tipo_incidencia = "averia_publica"; break;
        case 2: tipo_incidencia = "siniestro_vehicular"; break;
        case 3: tipo_incidencia = "incendio"; break;
        case 4: tipo_incidencia = "robo"; break;
        case 5: tipo_incidencia = "otro"; break;
        default: cout << "Tipo inválido." << endl; return;
    }

    cout << "\tID del usuario que reporta: ";
    cin >> usuario_id;

    archivo << id << "," << titulo << "," << descripcion << "," << tipo_incidencia << ","
            << ubicacion << "," << estado << "," << usuario_id << "\n";
    archivo.close();

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
    cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;
    cout << "|   ID   |        Título        |     Descripción      |         Tipo         |      Ubicación       |  Estado  |" << endl;
    cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;

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
        cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;
    }

    archivo.close();
}

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
    for (const string &l : lineas) {
        archivoSalida << l << "\n";
    }
    archivoSalida.close();
    cout << "\t¡Incidencia modificada con éxito!" << endl;
}

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
    for (const string &l : lineas) {
        archivoSalida << l << "\n";
    }
    archivoSalida.close();
    cout << "\t¡Incidencia eliminada con éxito!" << endl;
}

void registrarUsuarioA() {
    ofstream archivo("../SicFpProject/data/usuarios.csv", ios::app);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
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

    cout << "\t¡Usuario registrado exitosamente! ID asignado: " << id << endl;
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