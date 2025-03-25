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
#include <limits> // Necesario para limpiar buffer con numeric_limits
#include <clocale>
#include <cstdlib>  // Para declarar variables de acceso getenv()
#include <iomanip>

// El espacio de nombres
using namespace std;

void setColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    SetConsoleOutputCP(65001); // Para poder hacer uso de las tildes
    SetConsoleCP(65001);       // UTF-8 para entrada
    setlocale(LC_ALL, "es_ES.UTF-8");

    reinicio:
    system("cls");
    // Variables Globales
    string exit;
    int op;
    string id, titulo, descripcion, tipo_incidencia, ubicacion;

    // Credenciales de la base de datos
    const char* db_pass = getenv("DB_PASS");
    const char* db_user = getenv("DB_USER");

    // Conectamos con MySQL
    MYSQL *obj;
    if (!((obj = mysql_init(nullptr)))) {
        cout << "Error al crear el objeto MySQL" << endl;
        return 1;
    }

    // Conectamos con el servidor de MySQL
    if (!mysql_real_connect(obj, "localhost", db_user, db_pass, "db_sic", 3306, nullptr, 0)) {
        cout << "Error al conectar a la base de datos: " << mysql_error(obj) << endl;
        mysql_close(obj);
        return 1;
    }

    setColor(2);
    cout << "\tFelicidades! Te conectaste a la Base de Datos" << endl;
    cout << "\t+----------------------------------------------+" << endl;

    menu_principal:
    system("cls");

    setColor(6);
    std::cout << "\t  ____  _     _                             _        _            _     _                 _           \n";
    std::cout << "\t / ___|(_)___| |_ ___ _ __ ___   __ _    __| | ___  (_)_ __   ___(_) __| | ___ _ __   ___(_) __ _ ___ \n";
    std::cout << "\t \\___ \\| / __| __/ _ \\ '_ ` _ \\ / _` |  / _` |/ _ \\ | | '_ \\ / __| |/ _` |/ _ \\ '_ \\ / __| |/ _` / __|\n";
    std::cout << "\t  ___) | \\__ \\ ||  __/ | | | | | (_| | | (_| |  __/ | | | | | (__| | (_| |  __/ | | | (__| | (_| \\__ \\\n";
    std::cout << "\t |____/|_|___/\\__\\___|_| |_| |_|\\__,_|  \\__,_|\\___| |_|_| |_|\\___|_|\\__,_|\\___|_| |_|\\___|_|\\__,_|___/ \n";
    cout << "\t-------------------------------------------------------------------------------------------------------" << endl;

    setColor(4);
    cout << "\n\t¡Primero registrate en el sistema para poder registrar tu incidencia!\n" << endl;

    setColor(14);
    std::cout << "\t+-----------------------------+\n";
    std::cout << "\t|            MENU             |\n";
    std::cout << "\t+-----------------------------+\n";
    std::cout << "\t| 1 | Registrar incidencia    |\n";
    std::cout << "\t| 2 | Eliminar incidencia     |\n";
    std::cout << "\t| 3 | Incidencias Registradas |\n";
    std::cout << "\t| 4 | Actualizar incidencias  |\n";
    std::cout << "\t| 5 | Registrar usuario       |\n";
    std::cout << "\t| 6 | Salir                   |\n";
    std::cout << "\t+-----------------------------+\n";

    setColor(15);
    cout << "\n\tDigite la opción que desea utilizar: ";
    cin >> op;

    switch (op) {
        case 1: {
            setColor(9);
            std::cout << "\t+---------------------------+\n";
            std::cout << "\t|  REGISTRO DE INCIDENCIAS  |\n";
            std::cout << "\t+---------------------------+\n";

            // Capturar datos básicos
            setColor(15);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTítulo: ";
            getline(cin, titulo);
            cout << "\nDescripción: ";
            getline(cin, descripcion);
            cout << "\nUbicación: ";
            getline(cin, ubicacion);

            setColor(10);
            cout << "\nDatos registrados:\n";
            cout << "- Título: " << titulo << endl;
            cout << "- Descripción: " << descripcion << endl;
            cout << "- Ubicación: " << ubicacion << endl;

            // Pausa
            setColor(15);
            cout<<"\n\n";
            system("pause");

            // Menú para seleccionar el tipo de incidencia
            int opcion_tipo;
            do {
                setColor(5);

                cout << "\t+-------------------------------+\n";
                cout << "\t|       Tipo de incidencia      |\n";
                cout << "\t+-------------------------------+\n";
                cout << "\t| 1 | Avería pública            |\n";
                cout << "\t| 2 | Siniestro vehicular       |\n";
                cout << "\t| 3 | Incendio                  |\n";
                cout << "\t| 4 | Robo                      |\n";
                cout << "\t| 5 | Otro                      |\n";
                cout << "\t+-------------------------------+\n";

                setColor(15);
                cout << "\n\tSeleccione una opción: ";
                cin >> opcion_tipo;
                cin.ignore();  // Limpiar buffer

                switch(opcion_tipo) {
                    case 1: tipo_incidencia = "averia_publica"; break;
                    case 2: tipo_incidencia = "siniestro_vehicular"; break;
                    case 3: tipo_incidencia = "incendio"; break;
                    case 4: tipo_incidencia = "robo"; break;
                    case 5: tipo_incidencia = "otro"; break;
                    default:
                        setColor(12);
                        cout << "¡Error! Elija una opción válida (1-5).\n";
                        continue;
                }
                break;
            } while (true);

            // Validar usuario
            string usuario_id;
            cout << "\tID del usuario que reporta: ";
            getline(cin, usuario_id);

            string checkUserQuery = "SELECT id FROM usuarios WHERE id = " + usuario_id + ";";
            if (mysql_query(obj, checkUserQuery.c_str())) {
                cout << "Error al verificar usuario: " << mysql_error(obj) << endl;
                break;
            }

            MYSQL_RES *userRes = mysql_store_result(obj);
            if (!userRes || mysql_num_rows(userRes) == 0) {
                cout << "Error: El usuario con ID " << usuario_id << " no existe.\n";
                mysql_free_result(userRes);
                break;
            }
            mysql_free_result(userRes);

            // Insertar en BD
            string insert = "INSERT INTO incidencias(titulo, descripcion, tipo_incidencia, ubicacion, estado, usuario_id) "
                           "VALUES ('" + titulo + "', '" + descripcion + "', '" + tipo_incidencia + "', '" + ubicacion + "', 'pendiente', " + usuario_id + ");";

            if (mysql_query(obj, insert.c_str())) {
                cout << "Error al registrar: " << mysql_error(obj) << endl;
            } else {
                setColor(10);
                cout << "¡Incidencia registrada exitosamente!\n";
                setColor(15);
            }
            break;
        }

        case 2: {
            setColor(9);
            std::cout << "\t+---------------------------+\n";
            std::cout << "\t|   ELIMINAR INCIDENCIAS    |\n";
            std::cout << "\t+---------------------------+\n";

            // Eliminar registros
            setColor(15);
            cin.ignore();
            cout << "\n\tDigite el ID de la incidencia a eliminar: "; getline(cin, id);

            string deleteQuery = "DELETE FROM incidencias WHERE id = " + id + ";";
            const char* i = deleteQuery.c_str();

            int q_status = mysql_query(obj, i);
            if (!q_status) {
                cout << "\tIncidencia eliminada con éxito" << endl;
            } else {
                cout << "Error al eliminar incidencia: " << mysql_error(obj) << endl;
            }
            break;
        }

        case 3: {
            setColor(9);
            std::cout << "\t+---------------------------+\n";
            std::cout << "\t|  INCIDENCIAS REGISTRADAS  |\n";
            std::cout << "\t+---------------------------+\n";

            string selectQuery = "SELECT * FROM incidencias;";
            const char* i = selectQuery.c_str();

            if (mysql_query(obj, i) == 0) {
                if (MYSQL_RES *res = mysql_store_result(obj)) {
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
            setColor(9);
            std::cout << "\t+---------------------------+\n";
            std::cout << "\t|   ACTUALIZAR INCIDENCIA   |\n";
            std::cout << "\t+---------------------------+\n";
            setColor(15);

            // Obtener ID de incidencia a modificar
            cin.ignore();
            cout << "\n\tDigite el ID de la incidencia a modificar: ";
            string id;
            getline(cin, id);

            // Verificar si la incidencia existe
            string checkQuery = "SELECT id FROM incidencias WHERE id = " + id;
            if (mysql_query(obj, checkQuery.c_str())) {
                setColor(12);
                cout << "Error al verificar incidencia: " << mysql_error(obj) << endl;
                break;
            }

            MYSQL_RES* checkRes = mysql_store_result(obj);
            if (mysql_num_rows(checkRes) == 0) {
                setColor(12);
                cout << "No existe una incidencia con ID " << id << endl;
                mysql_free_result(checkRes);
                break;
            }
            mysql_free_result(checkRes);

            // Capturar nuevos datos
            string titulo, descripcion, tipo_incidencia, ubicacion, estado;

            cout << "\nNuevo Título: ";
            getline(cin, titulo);

            cout << "\nNueva Descripción: ";
            getline(cin, descripcion);

            // Menú para Tipo de Incidencia
            int opcion_tipo;
            do {
                setColor(14);
                cout << "\n\tSeleccione el tipo de incidencia: ";
                cout << "\n\t+-------------------------------+\n";
                cout << "\t|       Tipo de incidencia      |\n";
                cout << "\t+-------------------------------+\n";
                cout << "\t| 1 | Avería pública            |\n";
                cout << "\t| 2 | Siniestro vehicular       |\n";
                cout << "\t| 3 | Incendio                  |\n";
                cout << "\t| 4 | Robo                      |\n";
                cout << "\t| 5 | Otro                      |\n";
                cout << "\t+-------------------------------+\n";
                setColor(15);
                cout << "Seleccione una opción (1-5): ";
                cin >> opcion_tipo;
                cin.ignore();

                switch(opcion_tipo) {
                    case 1: tipo_incidencia = "averia_publica"; break;
                    case 2: tipo_incidencia = "siniestro_vehicular"; break;
                    case 3: tipo_incidencia = "incendio"; break;
                    case 4: tipo_incidencia = "robo"; break;
                    case 5: tipo_incidencia = "otro"; break;
                    default:
                        setColor(12);
                        cout << "Opción inválida. Intente nuevamente.\n";
                        continue;
                }
                break;
            } while (true);

            cout << "\nNueva Ubicación: ";
            getline(cin, ubicacion);

            // Menú para Estado
            int opcion_estado;
            do {
                setColor(14);
                cout << "\n\tSeleccione el estado actual de la incidencia: ";
                cout << "\n\t+-----------------------------+\n";
                cout << "\t|        Estado actual        |\n";
                cout << "\t+-----------------------------+\n";
                cout << "\t| 1 | Pendiente               |\n";
                cout << "\t| 2 | En proceso              |\n";
                cout << "\t| 3 | Resuelta                |\n";
                cout << "\t+-----------------------------+\n";
                setColor(15);
                cout << "Seleccione una opción (1-3): ";
                cin >> opcion_estado;
                cin.ignore();

                switch(opcion_estado) {
                    case 1: estado = "pendiente"; break;
                    case 2: estado = "en_proceso"; break;
                    case 3: estado = "resuelta"; break;
                    default:
                        setColor(12);
                        cout << "Opción inválida. Intente nuevamente.\n";
                        continue;
                }
                break;
            } while (true);

            // Construir y ejecutar consulta UPDATE
            string updateQuery = "UPDATE incidencias SET "
                                "titulo = '" + titulo + "', "
                                "descripcion = '" + descripcion + "', "
                                "tipo_incidencia = '" + tipo_incidencia + "', "
                                "ubicacion = '" + ubicacion + "', "
                                "estado = '" + estado + "' "
                                "WHERE id = " + id;

            if (mysql_query(obj, updateQuery.c_str())) {
                setColor(12);
                cout << "Error al actualizar: " << mysql_error(obj) << endl;
            } else {
                setColor(10);
                cout << "\n\t¡Incidencia actualizada con éxito!\n";
                setColor(15);
            }
            break;
        }

        case 5: {
            setColor(9);
            cout << "\t+---------------------------+\n";
            cout << "\t|   REGISTRO DE USUARIOS    |\n";
            cout << "\t+---------------------------+\n";
            setColor(15);

            // Capturar datos básicos
            cin.ignore();
            string nombre, email, contraseña, rol;

            cout << "\nNombre: ";
            getline(cin, nombre);
            cout << "\nEmail: ";
            getline(cin, email);
            cout << "\nContraseña: ";
            getline(cin, contraseña);

            // Menú para selección de rol
            int opcion_rol;
            do {
                setColor(14);
                cout << "\nSeleccione un Rol: ";
                cout << "\n\t+-----------------------+\n";
                cout << "\t|   ROLES DE USUARIO    |\n";
                cout << "\t+-----------------------+\n";
                cout << "\t| 1 | Ciudadano         |\n";
                cout << "\t| 2 | Administrador     |\n";
                cout << "\t+-----------------------+\n";
                cout << "\n\tSeleccione una opción (1-2): ";
                cin >> opcion_rol;
                cin.ignore();

                switch(opcion_rol) {
                    case 1: rol = "ciudadano"; break;
                    case 2: rol = "administrador"; break;
                    default:
                        setColor(12);
                        cout << "Error: Opción inválida. Intente nuevamente.\n";
                        continue;
                }
                break;
            } while (true);

            // Escapar caracteres especiales para prevenir SQL injection
            char nombre_esc[256], email_esc[256], pass_esc[256];
            mysql_real_escape_string(obj, nombre_esc, nombre.c_str(), nombre.length());
            mysql_real_escape_string(obj, email_esc, email.c_str(), email.length());
            mysql_real_escape_string(obj, pass_esc, contraseña.c_str(), contraseña.length());

            // Construir consulta SQL segura
            string insert = "INSERT INTO usuarios(nombre, email, contraseña, rol) VALUES ('" +
                           string(nombre_esc) + "', '" +
                           string(email_esc) + "', '" +
                           string(pass_esc) + "', '" +
                           rol + "')";

            // Ejecutar consulta
            if (mysql_query(obj, insert.c_str())) {
                setColor(12);
                cout << "Error al registrar: " << mysql_error(obj) << endl;
            } else {
                setColor(10);
                cout << "\n¡Usuario registrado exitosamente!\n";
                cout << "Rol asignado: " << rol << endl;
                setColor(15);
            }
            break;
        }


        case 6: {
            goto salir;
        }

        default: {
            cout << "\n\tEsta opción no existe, vuelve a intentarlo..." << endl;
            getch();
            goto menu_principal;
        }
    } // Fin del switch case

    // Cerrar la conexión
    mysql_close(obj);

    // Control de Entrada y salida
    setColor(1);
    cout << "\n\tDigite [si] para salir y [no] para reiniciar "; cin >> exit;
    if (exit == "si") {
        salir:
        setColor(13);

        std::cout << "\t   ______                _            __     _ \n";
        std::cout << "\t  / ____/________ ______(_)___ ______/ /  _ | | \n";
        std::cout << "\t / / __/ ___/ __ `/ ___/ / __ `/ ___/ /  (_)/ / \n";
        std::cout << "\t/ /_/ / /  / /_/ / /__/ / /_/ (__  )_/  _  / /  \n";
        std::cout << "\t \\____/_/   \\__,_\\/___/_/\\__,_/____(_)  (_)/_/  \n";
        std::cout << "\t                                        /_/     \n";
        cout << "\t+----------------------------------------------+" << endl;
        cout << "\t|               VUELVE PRONTO :D               |" << endl;
        cout << "\t+----------------------------------------------+" << endl;
    } else {
        goto reinicio;
    }
    return 0;
}