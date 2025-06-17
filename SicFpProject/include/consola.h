#ifndef CONSOLA_H
#define CONSOLA_H

// Evitar conflictos con macros de Windows
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>

// Declaración de la función para cambiar el color de la consola
void setColor(int color);

#endif // CONSOLA_H
