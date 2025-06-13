//
// Created by Jonathan Panchana Rodríguez on 13/6/2025.
//

/*NOTA: Esta clase define la función 'setColor', con el fin de cambiar el color del texto en la consola.
 * Aporta funcionalidad visual a la ejecución del programa en consola.
 */

#include"../include/consola.h"

void setColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}