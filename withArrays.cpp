//
// Initial creation by Jonathan David Panchana Rodr�guez on 27/3/2025.
//
// You can find the extended version of this project in the following repository: https://github.com/jonistyle2023/SIC

/* C�digo del proyecto "Sistema de incidencias" del "Grupo E", de la clase "Fundamentos de programaci�n" perteneciente
 * a la carrera de Software, de la Universidad Estatal Peninsula de Santa Elena (UPSE). */

// Paralelo: Software 2/2

/* Integrantes y Roles:
 * - Evelyn Yaritza Conforme Choez (Lider)
 * - Jonathan David Panchana Rodr�guez (Desarrollador)
 * - Joseph Anthony Gonz�lez Perero (Supervisor)
 * - Deivy Anthony Prudente Merejildo (Editor)
 * - Katherine Vill�n Soriano (Dise�adora)
 * - Carlos Andr�s Reyes Escalante (Tester) */

// IDEs used: Clion, Visual Studio Code, Dev-C++ & Code::Blocks

// Bloque de declaraciones
// Declaramos las librer�as necesarias para el programa
#include <iostream>
#include <iomanip>
#include <string>

// Librerias para hacer uso de las tildes
/* ADVERTENCIA: Si no compila en Windows o alg�n compilador online,
 * COMENTA O ELIMINA ESTAS LIBRER�AS */
#include <clocale> // Elimina o comenta esta l�nea si no compila
#include <windows.h> // Elim�na o comenta esta l�nea si no compila

// Espacio de nombres
using namespace std;

void setColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Primero definimos las constantes para determinar el m�ximo de incidencias y usuarios
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

// Esta funci�n hace de contador para el n�mero de incidencias y usuarios registrados.
void mostrarContadores() {
    setColor(11); // Color para destacar el texto, los encontrar�n a lo largo del c�digo
    cout << "\n\t+-----------------------------------+\n";
    cout << "\t|   ESTAD�STICAS DEL SISTEMA        |\n";
    cout << "\t+-----------------------------------+\n";
    cout << "\t| Incidencias registradas: " << totalIncidencias << "\t----|\n";
    cout << "\t| Usuarios registrados:    " << totalUsuarios << "\t----|\n";
    cout << "\t+-----------------------------------+\n";
    setColor(7); // Restaurar color por defecto
}

// Funciones para manejar incidencias y usuarios

// Funci�n para registrar una nueva incidencia
void registrarIncidencia() {
    if (totalIncidencias >= MAX_INCIDENTES) {
        cout << "No se pueden registrar m�s incidencias." << endl;
        return;
    }

    Incidencia nuevaIncidencia;
    nuevaIncidencia.id = totalIncidencias + 1; // Asignar ID autom�ticamente
    cout << "\tT�tulo: ";
    cin.ignore();
    getline(cin, nuevaIncidencia.titulo);
    cout << "\tDescripci�n: ";
    getline(cin, nuevaIncidencia.descripcion);
    cout << "\tUbicaci�n: ";
    getline(cin, nuevaIncidencia.ubicacion);

    cout << "\tTipo de incidencia (1: Aver�a p�blica, 2: Siniestro vehicular, 3: Incendio, 4: Robo, 5: Otro): ";
    int tipo;
    cin >> tipo;
    switch (tipo) {
        case 1: nuevaIncidencia.tipo_incidencia = "averia_publica"; break;
        case 2: nuevaIncidencia.tipo_incidencia = "siniestro_vehicular"; break;
        case 3: nuevaIncidencia.tipo_incidencia = "incendio"; break;
        case 4: nuevaIncidencia.tipo_incidencia = "robo"; break;
        case 5: nuevaIncidencia.tipo_incidencia = "otro"; break;
        default: cout << "Tipo inv�lido." << endl; return;
    }

    cout << "\tID del usuario que reporta: ";
    cin >> nuevaIncidencia.usuario_id;

    nuevaIncidencia.estado = "pendiente";
    incidencias[totalIncidencias++] = nuevaIncidencia;

    setColor(10);
    cout << "\t�Incidencia registrada exitosamente! El ID asignado es: " << nuevaIncidencia.id << endl;
}

// Funci�n para mostrar todas las incidencias registradas
void listarIncidencias() {
    setColor(5);
    cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;
    cout << "|   ID   |        T�tulo        |     Descripci�n      |         Tipo         |      Ubicaci�n       |  Estado  |" << endl;
    cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;
    setColor(7);
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

// Funci�n para modificar una incidencia
void modificarIncidencia() {
    int id;
    cout << "\tDigite el ID de la incidencia a modificar: ";
    cin >> id;

    // Buscar la incidencia por ID
    for (int i = 0; i < totalIncidencias; i++) {
        if (incidencias[i].id == id) {
            setColor(10);
            cout << "\tIncidencia encontrada." << endl;

            // Preguntar al usuario qu� desea modificar
            int opcion;
            setColor(7);
            cout << "\n\t�Qu� desea modificar?" << endl;
            cout << "\t1. Solo el estado de la incidencia" << endl;
            cout << "\t2. Toda la informaci�n de la incidencia" << endl;
            cout << "\n\tSeleccione una opci�n (1 o 2): ";
            cin >> opcion;
            if (opcion == 1) {
                // Actualizar solo el estado
                setColor(14);
                cout << "\tEstado actual: " << incidencias[i].estado << endl;

                int nuevoEstado;
                do {
                    setColor(7);
                    cout << "\tSeleccione el nuevo estado:" << endl;
                    cout << "\t1. Pendiente" << endl;
                    cout << "\t2. En progreso" << endl;
                    cout << "\t3. Resuelto" << endl;
                    cout << "\n\tOpci�n (1-3): ";
                    cin >> nuevoEstado;

                    switch (nuevoEstado) {
                        case 1: incidencias[i].estado = "pendiente"; break;
                        case 2: incidencias[i].estado = "en progreso"; break;
                        case 3: incidencias[i].estado = "resuelto"; break;
                        default:
                            setColor(12);
                            cout << "\tOpci�n inv�lida. Intente nuevamente." << endl;
                            continue;
                    }
                    break;

                } while (true);

                setColor(10);
                cout << "\t�Estado de la incidencia actualizado con �xito!" << endl;
            } else if (opcion == 2) {
                // Actualizar toda la informaci�n
                cout << "\tPuede modificar los siguientes campos:" << endl;

                // Mostrar y modificar los datos actuales
                cout << "\tT�tulo actual: " << incidencias[i].titulo << endl;
                cout << "\tNuevo t�tulo (deje vac�o para no modificar): ";
                cin.ignore();
                string nuevoTitulo;
                getline(cin, nuevoTitulo);
                if (!nuevoTitulo.empty()) {
                    incidencias[i].titulo = nuevoTitulo;
                }

                cout << "\tDescripci�n actual: " << incidencias[i].descripcion << endl;
                cout << "\tNueva descripci�n (deje vac�o para no modificar): ";
                string nuevaDescripcion;
                getline(cin, nuevaDescripcion);
                if (!nuevaDescripcion.empty()) {
                    incidencias[i].descripcion = nuevaDescripcion;
                }

                cout << "\tUbicaci�n actual: " << incidencias[i].ubicacion << endl;
                cout << "\tNueva ubicaci�n (deje vac�o para no modificar): ";
                string nuevaUbicacion;
                getline(cin, nuevaUbicacion);
                if (!nuevaUbicacion.empty()) {
                    incidencias[i].ubicacion = nuevaUbicacion;
                }

                cout << "\tTipo de incidencia actual: " << incidencias[i].tipo_incidencia << endl;
                cout << "\tNuevo tipo de incidencia (1: Aver�a p�blica, 2: Siniestro vehicular, 3: Incendio, 4: Robo, 5: Otro): ";
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

                setColor(14);
                cout << "\tEstado actual: " << incidencias[i].estado << endl;

                int nuevoEstado;
                do {
                    cout << "\tSeleccione el nuevo estado:" << endl;
                    cout << "\t1. Pendiente" << endl;
                    cout << "\t2. En progreso" << endl;
                    cout << "\t3. Resuelto" << endl;
                    cout << "\tOpci�n (1-3): ";
                    cin >> nuevoEstado;

                    switch (nuevoEstado) {
                        case 1: incidencias[i].estado = "pendiente"; break;
                        case 2: incidencias[i].estado = "en progreso"; break;
                        case 3: incidencias[i].estado = "resuelto"; break;
                        default:
                            setColor(12);
                            cout << "\tOpci�n inv�lida. Intente nuevamente." << endl;
                            continue;
                    }
                    break;
                } while (true);

                setColor(10);
                cout << "\t�Incidencia modificada con �xito!" << endl;
            } else {
                setColor(12);
                cout << "\tOpci�n no v�lida. No se realizaron cambios." << endl;
            }
            return;
        }
    }

    // Si no se encuentra la incidencia
    setColor(12);
    cout << "Incidencia no encontrada." << endl;
}

// Funci�n para eliminar una incidencia
void eliminarIncidencia() {
    int id;
    cout << "\tDigite el ID de la incidencia a eliminar: ";
    cin >> id;

    for (int i = 0; i < totalIncidencias; i++) {
        if (incidencias[i].id == id) {
            for (int j = i; j < totalIncidencias - 1; j++) {
                incidencias[j] = incidencias[j + 1];
            }
            totalIncidencias--;
            setColor(10);
            cout << "\tIncidencia eliminada con �xito." << endl;
            return;
        }
    }
    setColor(4);
    cout << "\tIncidencia no encontrada." << endl;
}

// Funci�n para registrar un nuevo usuario
void registrarUsuario() {
    if (totalUsuarios >= MAX_USUARIOS) {
        cout << "No se pueden registrar m�s usuarios." << endl;
        return;
    }

    Usuario nuevoUsuario;
    nuevoUsuario.id = totalUsuarios + 1; // Asignar ID autom�ticamente
    cout << "\tNombre: ";
    cin.ignore();
    getline(cin, nuevoUsuario.nombre);
    cout << "\tEmail: ";
    getline(cin, nuevoUsuario.email);
    cout << "\tContrase�a: ";
    getline(cin, nuevoUsuario.contrasena);

    cout << "\tRol (1: Ciudadano, 2: Administrador): ";
    int rol;
    cin >> rol;
    nuevoUsuario.rol = (rol == 1) ? "ciudadano" : "administrador";

    usuarios[totalUsuarios++] = nuevoUsuario;

    setColor(10);
    cout << "\t�Usuario registrado exitosamente!, ID Asignado: " << nuevoUsuario.id << endl;
}

// Funci�n principal
int main() {

    /* ADVERTENCIA:
     * Configuraci�n de la consola para permitir el uso de caracteres UTF-8
     * y establecer la localizaci�n a espa�ol.
     * Asimismo, si te presenta errores, elimina o comenta estas l�neas.
     */

    SetConsoleOutputCP(65001); // Elimina o comenta esta l�nea si no compila
    SetConsoleCP(65001);       // Elimina o comenta esta l�nea si no compila
    setlocale(LC_ALL, "es_ES.UTF-8"); // Elimina o comenta esta l�nea si no compila

    setColor(10);
    cout << "\n\tHola Papu! Bienvenido al Sistema de Incidencias del Municipio de Salinas." << endl;
    setColor(4);
    cout << "\t�Recuerda Primero registrate en el sistema para hacer tu denuncia!" << endl;

    int op;
    do {
        // Funci�n matem�tica para calcular el n�mero de incidencias y usuarios
        mostrarContadores();
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
        cout << "\n\tSeleccione una opci�n: ";
        cin >> op;

        switch (op) {
            case 1: registrarIncidencia(); break;
            case 2: listarIncidencias(); break;
            case 3: modificarIncidencia(); break;
            case 4: eliminarIncidencia(); break;
            case 5: registrarUsuario(); break;
            case 6: cout << "Gracias! Vuelva Pronto..." << endl; break;
            default: cout << "Opci�n no v�lida." << endl; break;
        }
    } while (op != 6);

    return 0;
}
