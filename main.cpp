// ██████  ██    ██             ██  ██████  ███    ██ ██ ███████ ████████ ██    ██ ██      ███████ ██████   ██████  ██████  ██████
// ██   ██  ██  ██  ██          ██ ██    ██ ████   ██ ██ ██         ██     ██  ██  ██      ██           ██ ██  ████      ██      ██
// ██████    ████               ██ ██    ██ ██ ██  ██ ██ ███████    ██      ████   ██      █████    █████  ██ ██ ██  █████   █████
// ██   ██    ██    ██     ██   ██ ██    ██ ██  ██ ██ ██      ██    ██       ██    ██      ██      ██      ████  ██ ██           ██
// ██████     ██            █████   ██████  ██   ████ ██ ███████    ██       ██    ███████ ███████ ███████  ██████  ███████ ██████

// Created by jonathan Panchana on 23/3/2025.

// Definimos las librerías antes que nada.
#include <iostream>
#include <windows.h>
#include <mysql.h> // Esta libreria es específica para MySQL y la más importante para este programa.
#include <conio.h>
#include <locale.h>
#include <iomanip>

// El espacio de nombres
using namespace std;

void setColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    SetConsoleOutputCP(65001); // Para poder hacer uso de las tildes
    setlocale(LC_ALL, "es_ES.UTF-8");

    reinicio:
    system("cls");
    // Variables Globales
    string exit;
    int op;
    string id, titulo, descripcion, tipo_incidencia, ubicacion, estado;

    // Conectamos con MySQL
    MYSQL *obj;
    if (!(obj = mysql_init(0))) {
        cout << "Error al crear el objeto MySQL" << endl;
        return 1;
    }

    // Conectamos con el servidor de MySQL
    if (!mysql_real_connect(obj, "localhost", "root", "saymyname", "db_sic", 3306, NULL, 0)) {
        cout << "Error al conectar a la base de datos: " << mysql_error(obj) << endl;
        mysql_close(obj);
        return 1;
    } else {
        cout << "Felicidades! Te conectaste a la Base de Datos" << endl << endl;
    }

    menu_principal:
    system("cls");

    setColor(6);

    std::cout << "\t  ____  _     _                             _        _            _     _                 _           \n";
    std::cout << "\t / ___|(_)___| |_ ___ _ __ ___   __ _    __| | ___  (_)_ __   ___(_) __| | ___ _ __   ___(_) __ _ ___ \n";
    std::cout << "\t \\___ \\| / __| __/ _ \\ '_ ` _ \\ / _` |  / _` |/ _ \\ | | '_ \\ / __| |/ _` |/ _ \\ '_ \\ / __| |/ _` / __|\n";
    std::cout << "\t  ___) | \\__ \\ ||  __/ | | | | | (_| | | (_| |  __/ | | | | | (__| | (_| |  __/ | | | (__| | (_| \\__ \\\n";
    std::cout << "\t |____/|_|___/\\__\\___|_| |_| |_|\\__,_|  \\__,_|\\___| |_|_| |_|\\___|_|\\__,_|\\___|_| |_|\\___|_|\\__,_|___/ \n";
    cout << "\t-------------------------------------------------------------------------------------------------------" << endl;

    setColor(14);
    std::cout << "+---------------------------+\n";
    std::cout << "|          MENU             |\n";
    std::cout << "+---------------------------+\n";
    std::cout << "| 1 | Registrar incidencia  |\n";
    std::cout << "| 2 | Eliminar incidencia   |\n";
    std::cout << "| 3 | Consultar incidencias |\n";
    std::cout << "| 4 | Modificar incidencia  |\n";
    std::cout << "| 5 | Registrar usuario     |\n";
    std::cout << "| 6 | Salir                 |\n";
    std::cout << "+---------------------------+\n";

    setColor(15);
    cout << "\tDigite la opción que desea utilizar: ";
    cin >> op;

    switch (op) {
        case 1: {
            setColor(6);
            cout << "\n\tRegistrar Incidencia" << endl;

            // Capturamos los datos de la incidencia
            setColor(15);
            cin.ignore();
            cout << "Título: "; getline(cin, titulo);
            cout << "Descripción: "; getline(cin, descripcion);
            cout << "Tipo de Incidencia (averia_publica, siniestro_vehicular, incendio, robo, otro): "; getline(cin, tipo_incidencia);
            cout << "Ubicación: "; getline(cin, ubicacion);

            // Verificar si el usuario existe
            string usuario_id;
            cout << "ID del usuario que reporta la incidencia: "; getline(cin, usuario_id);

            // Validar que el usuario exista en la base de datos
            string checkUserQuery = "SELECT id FROM usuarios WHERE id = " + usuario_id + ";";
            const char* checkUser = checkUserQuery.c_str();

            if (mysql_query(obj, checkUser)) {
                cout << "Error al verificar el usuario: " << mysql_error(obj) << endl;
                break;
            }

            MYSQL_RES *userRes = mysql_store_result(obj);
            if (!userRes || mysql_num_rows(userRes) == 0) {
                cout << "El usuario con ID " << usuario_id << " no existe." << endl;
                mysql_free_result(userRes);
                break;
            }
            mysql_free_result(userRes);

            // Insertar en la base de datos
            string insert = "INSERT INTO incidencias(titulo, descripcion, tipo_incidencia, ubicacion, estado, usuario_id) VALUES ('" + titulo + "', '" + descripcion + "', '" + tipo_incidencia + "', '" + ubicacion + "', 'pendiente', " + usuario_id + ");";
            const char* i = insert.c_str();
            int q_status = mysql_query(obj, i);
            if (q_status) {
                cout << "Error al registrar incidencia: " << mysql_error(obj) << endl;
            } else {
                cout << "Incidencia registrada con éxito" << endl;
            }
            break;
        }

        case 2: {
            setColor(6);
            cout << "\n\tEliminar Incidencia" << endl;

            // Eliminar registros
            setColor(15);
            cin.ignore();
            cout << "\nDigite el ID de la incidencia a eliminar: "; getline(cin, id);

            string deleteQuery = "DELETE FROM incidencias WHERE id = " + id + ";";
            const char* i = deleteQuery.c_str();

            int q_status = mysql_query(obj, i);
            if (!q_status) {
                cout << "Incidencia eliminada con éxito" << endl;
            } else {
                cout << "Error al eliminar incidencia: " << mysql_error(obj) << endl;
            }
            break;
        }

        case 3: {
            setColor(6);
            cout << "\n\tConsultar Incidencias\n" << endl;

            string selectQuery = "SELECT * FROM incidencias;";
            const char* i = selectQuery.c_str();

            if (mysql_query(obj, i) == 0) {
                MYSQL_RES *res = mysql_store_result(obj);
                if (res) {
                    MYSQL_ROW fila;
                    setColor(14);

                    // Encabezado de la tabla
                    cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;
                    cout << "|   ID   |        Título        |     Descripción      |         Tipo         |      Ubicación       |  Estado  |" << endl;
                    cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;

                    setColor(15);
                    while ((fila = mysql_fetch_row(res))) {
                        // Mostrar cada fila de la tabla
                        cout << "| " << left << setw(6) << (fila[0] ? fila[0] : "NULL") << " | "
                             << setw(20) << (fila[1] ? fila[1] : "NULL") << " | "
                             << setw(20) << (fila[2] ? fila[2] : "NULL") << " | "
                             << setw(20) << (fila[3] ? fila[3] : "NULL") << " | "
                             << setw(20) << (fila[4] ? fila[4] : "NULL") << " | "
                             << setw(8) << (fila[5] ? fila[5] : "NULL") << " |" << endl;

                        // Separador entre filas
                        cout << "+--------+----------------------+----------------------+----------------------+----------------------+----------+" << endl;
                    }
                    mysql_free_result(res);
                } else {
                    cout << "Error al encontrar registros." << endl;
                }
            } else {
                cout << "Error en la consulta: " << mysql_error(obj) << endl;
            }

            break;
        }

        case 4: {
            setColor(6);
            cout << "\n\tModificar Incidencia" << endl;

            // Modificar Incidencias
            setColor(15);
            cin.ignore();
            cout << "\nDigite el ID de la incidencia a modificar: "; getline(cin, id);

            // Solicitar Los nuevos valores
            cout << "\nNuevo Título: ";
            getline(cin, titulo);
            cout << "\nNueva Descripción: ";
            getline(cin, descripcion);
            cout << "\nNuevo Tipo de Incidencia: ";
            getline(cin, tipo_incidencia);
            cout << "\nNueva Ubicación: ";
            getline(cin, ubicacion);
            cout << "\nNuevo Estado (pendiente, en_proceso, resuelta): ";
            getline(cin, estado);

            // Crear la consulta UPDATE
            string updateQuery = "UPDATE incidencias SET titulo = '" + titulo + "', descripcion = '" + descripcion + "', tipo_incidencia = '" + tipo_incidencia + "', ubicacion = '" + ubicacion + "', estado = '" + estado + "' WHERE id = " + id + ";";
            const char* i = updateQuery.c_str();

            // Ejecutar la consulta
            int q_status = mysql_query(obj, i);
            if (!q_status) {
                setColor(10);
                cout << "\nIncidencia actualizada con éxito" << endl;
            } else {
                setColor(12);
                cout << "Error al actualizar incidencia: " << mysql_error(obj) << endl;
            }
            break;
        }

        case 5: {  // Case para registrar usuarios
            setColor(6);
            cout << "\n\tRegistrar Usuario" << endl;

            // Capturamos los datos del usuario
            setColor(15);
            cin.ignore();
            string nombre, email, contraseña, rol;

            cout << "\nNombre: "; getline(cin, nombre);
            cout << "Email: "; getline(cin, email);
            cout << "Contraseña: "; getline(cin, contraseña);
            cout << "Rol (ciudadano, administrador): "; getline(cin, rol);

            // Validar que el rol sea válido
            if (rol != "ciudadano" && rol != "administrador") {
                cout << "Error: Rol no válido. Debe ser 'ciudadano' o 'administrador'." << endl;
                break;
            }

            // Insertar en la base de datos
            string insert = "INSERT INTO usuarios(nombre, email, contraseña, rol) VALUES ('" + nombre + "', '" + email + "', '" + contraseña + "', '" + rol + "');";
            const char* i = insert.c_str();
            int q_status = mysql_query(obj, i);
            if (q_status) {
                cout << "Error al registrar usuario: " << mysql_error(obj) << endl;
            } else {
                cout << "Usuario registrado con éxito" << endl;
            }
            break;
        }

        case 6: {
            goto salir;
            break;
        }

        default: {
            cout << "\n\tEsta opción no existe, vuelve a intentarlo..." << endl;
            getch();
            goto menu_principal;
            break;
        }
    }

    // Cerrar la conexión
    mysql_close(obj);

    // Control de Entrada y salida
    setColor(10);
    cout << "\n\t|Digite [si] para salir y [no] para reiniciar| "; cin >> exit;
    if (exit == "si") {
        salir:
        setColor(13);

        std::cout << "\t   ______                _            __     _ \n";
        std::cout << "\t  / ____/________ ______(_)___ ______/ /  _ | | \n";
        std::cout << "\t / / __/ ___/ __ `/ ___/ / __ `/ ___/ /  (_)/ / \n";
        std::cout << "\t/ /_/ / /  / /_/ / /__/ / /_/ (__  )_/  _  / /  \n";
        std::cout << "\t \\____/_/   \\__,_\\/___/_/\\__,_/____(_)  (_)/_/  \n";
        std::cout << "\t                                        /_/     \n";
        cout << "\t------------------------------------------------" << endl;
        cout << "\t|          Por utilizar este sistema :D        |" << endl;

    } else {
        goto reinicio;
    }

    return 0;
}