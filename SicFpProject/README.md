# **Proyecto de Fundamentos de Programación**
# **Sistema de ALERTAS COMUNITARIAS**

---

## **Estructura del proyecto**

```
SicFpProject/
├── data/
│   ├── incidencias.csv       <- Archivo para almacenar incidencias
│   └── usuarios.csv          <- Archivo para almacenar usuarios
├── include/
│   ├── consola.h
│   └── functions.h           <- Prototipos de funciones con Arreglos y Estructuras
│   └── archivesManager.h     <- Prototipos de funciones para manejar archivos
├── functions/
│   ├── consola.cpp
│   └── functions.cpp         <- Implementación de funciones con Arreglos y Estructuras
│   └── archivesManager.cpp   <- Implementación de funciones para manejar archivos
├── main.cpp                  <- Clase principal (Puede alternar la lógica de negocio)
```

### **Funciones de cada archivo:**

1. **functions.cpp:** Contiene las funciones principales para gestionar incidencias y usuarios, como registrar, listar, modificar y eliminar.
   También incluye una función para mostrar estadísticas del sistema. Aporta la lógica de negocio y manipulación de datos a la clase principal sicArrays.

2. **consola.cpp:** Define la función setColor, que cambia el color del texto en la consola. Aporta funcionalidad visual para mejorar la experiencia del
   usuario en la consola.

3. **functions.h:** Declara los prototipos de las funciones definidas en functions.cpp. Aporta una interfaz para que otras partes del programa,
   como sicArrays, puedan usar estas funciones.

4. **consola.h:** Declara el prototipo de la función setColor y las dependencias necesarias para su implementación. Aporta la interfaz para cambiar colores
   en la consola desde cualquier parte del programa.

5. **archivesManager.cpp:** Implementa funciones para manejar archivos, como leer y escribir datos de incidencias y usuarios en archivos CSV.

6. **archivesManager.h:** Declara los prototipos de las funciones de manejo de archivos definidas en archivesManager.cpp. Aporta una interfaz para

---

> [!NOTE]
> 
> Esta versión hecha en C++ permite realizar lo siguiente:
> - Registrar datos.
> - Consultar registros.
> - Modificar registros.
> - Eliminar registro.
> - Registrar usuariS.
> 
> Además, permite registrar usuarios para el acceso al sistema, validar datos, manejo de excepciones, y estructuras de control selectivas y repetitivas.
>
> Por último, decir que cuenta con almacenamiento de datos en archivos CSV, lo que permite una fácil manipulación y persistencia de la información.

---

> [!NOTE]
>
> Este proyecto es una versión simplificada del sistema de incidencias ciudadanas, el cual fue propuesto por
> **Jonathan David Panchana Rodríguez** para el municipio de Loja, en Agosto de 2023. El proyecto original constaba con tecnologías mas avanzadas,
> Como lo son:
> - **Java** como lenguaje de programación.
> - **Spring Boot** como framework.
> - **MySQL** como base de datos.
> - **Thymeleaf** como motor de plantillas.
> - **Bootstrap** como framework de diseño.
> - **JavaScript** para la lógica del lado del cliente.
> - **HTML/CSS** para la estructura y estilo de las páginas web.
> - **GitHub** como plataforma de control de versiones y colaboración.