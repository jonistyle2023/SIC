cmake_minimum_required(VERSION 3.30)
project(SIC)

set(CMAKE_CXX_STANDARD 20)

# Rutas a los archivos de MySQL Connector/C (ajusta según la instalación)
include_directories("C:/Program Files/MySQL/MySQL Server 9.2/include")
link_directories("C:/Program Files/MySQL/MySQL Server 9.2/lib")

add_executable(SIC main.cpp)

# Enlazar la biblioteca MySQL
target_link_libraries(SIC libmysql)