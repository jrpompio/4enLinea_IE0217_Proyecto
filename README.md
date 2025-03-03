# 4enLinea_IE0217_Proyecto

Este repositorio contiene los archivos relacionados al proyecto de **IE0217**, en el cual desarrollaremos el juego de **4 en línea** en C++.

## Desarrollado por los estudiantes:
- Isaí Gonzalez S.
- Mario Fabián Rocha M.
- Jr Ruiz S.

## 🚀 Instalación y Uso

Este proyecto utiliza un `Makefile` para facilitar la compilación, ejecución y limpieza de los archivos generados. A continuación, se explican los comandos disponibles:

### 📌 Compilación
Para compilar el proyecto, ejecuta el siguiente comando en la terminal dentro del directorio del repositorio:
```bash
make
```
Esto generará el ejecutable del juego.

### 🎮 Ejecución
Una vez compilado, puedes ejecutar el juego con:
```bash
make run
```
Este comando ejecutará el archivo binario generado y abrirá el juego.

### 🧹 Limpieza
Si deseas eliminar los archivos compilados y limpiar el directorio, usa:
```bash
make clean
```
Esto eliminará el ejecutable y cualquier otro archivo generado durante la compilación.

## 📂 Estructura del Proyecto
El proyecto está estructurado de la siguiente manera:
```
📁 4enLinea_IE0217_Proyecto
├── src/                # Código fuente del juego
├── build/              # Ejecutables .o
├── makefile            # Archivo Makefile para compilar el proyecto
└── README.md           # Documentación del proyecto
```

## 📜 Licencia
Este proyecto es desarrollado con fines educativos en el marco del curso **IE0217**.

## 🛠 Requerimientos
- Compilador `g++` compatible con C++11 o superior
- Biblioteca gráfica `GTK3` (Por lo general linux la trae instalada)
- Sistema operativo Linux o Windows con WSL recomendado

