//
// Created by Jonathan Panchana Rodríguez on 13/6/2025.
//

#ifndef ARCHIVESMANAGER_H
#define ARCHIVESMANAGER_H

#include <string>
using namespace std;

void registrarIncidenciaA(int usuario_id, const string &rol);
void listarIncidenciasA();
void modificarIncidenciaA();
void eliminarIncidenciaA();
void registrarUsuarioA();
void menuCiudadano(int usuario_id, const string &rol);
void menuAdministrador();
void mostrarContadoresA();

int contarRegistros(const string &rutaArchivo);
int obtenerUsuarioId(const string &email);

bool autenticarUsuario(string &rol);


#endif //ARCHIVESMANAGER_H
