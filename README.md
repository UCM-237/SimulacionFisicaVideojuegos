# Simulación Física en Videojuegos

 

**Facultad de Informática — Universidad Complutense de Madrid (UCM)**  

**Grado en Desarrollo de Videojuegos** | 3er Curso

  

   ---

  

  Bienvenido al repositorio oficial del  **skeleton** base para las prácticas de la asignatura  **Simulación Física en Videojuegos**. Este proyecto contiene la plantilla de inicio integrada con el motor de física  **NVIDIA PhysX 4.1** y el sistema de renderizado para las prácticas del laboratorio.

  

    ---

  ## 🛠️ Flujo de Trabajo y Metodología de Entrega

Para la realización y evaluación de las prácticas del curso, se seguirá estrictamente el flujo de trabajo basado en **Fork y Git Tags**. Esto permite al profesorado realizar un seguimiento continuo de vuestro historial de commits y evaluar cada entrega de forma transparente.

### 1. Preparación de tu repositorio (Fork)

1. Haz un **Fork** de este repositorio a tu cuenta personal de GitHub mediante el botón `Fork` (esquina superior derecha).
2. Clona **tu fork** en tu equipo local:
   ```bash
   git clone [https://github.com/TU_USUARIO/SimulacionFisicaVideojuegos.git](https://github.com/TU_USUARIO/SimulacionFisicaVideojuegos.git)
   cd SimulacionFisicaVideojuegos 
   ```

3. Asegúrate de que el repositorio sea público (o privado dando acceso de lectura al profesorado de la asignatura)

## 2. Desarrollo de las prácticas

- Cada alumno trabajará directamente sobre su propio fork.

- Se requiere realizar commits frecuentes y descriptivos. El historial de control de versiones forma parte de la evaluación continua.

 ## 3. Entrega mediante Etiquetas (Git Tags)
 
 Para entregar cada una de las prácticas del cuatrimestre, deberás crear una etiqueta (tag) anotada en el commit final que corresponda a dicha entrega y subirla a GitHub.
 
 ### Nomenclatura oficial de etiquetas:
 
|Entrega                              |   Nombre del Tag  |Comando de creación |
| :--- | :---: | :--- |
| Proyecto intermedio (Proyecto intermedio) | v1.0-Intermedio    |     git tag -a v1.0-Intermedio -m "Proyecto intermedio" |
| Proyecto Final                          | v2.0-Final  |    git tag -a v2.0-Final -m "Entrega Proyecto Final" |

### Pasos para publicar el Tag en GitHub:

```bash

# 1. Crear la etiqueta localmente tras el commit final de la práctica

git tag -a v1.0-P1 -m "Entrega de la Practica 1"

# 2. Subir la etiqueta al repositorio remoto

git push origin v1.0-P1 
```


⚠️ Importante: La fecha de entrega oficial se tomará del timestamp asignado por GitHub al hacer el git push del tag. Las entregas fuera de plazo no serán evaluadas salvo causa justificada.

## 💻 Requisitos del Sistema e Instalación

### Requisitos de Software

- **Sistema Operativo:** Windows 10 / 11 (64-bit).

- **Entorno de Desarrollo:** Visual Studio 2019 o Visual Studio 2022 / 2025.

- **Cargas de Trabajo en VS:** Desarrollo para el escritorio con C++ (incluyendo SDK de Windows 10/11 y MSVC v142/v143).

### Compilación y Ejecución

1. Abre la solución skeleton/game.sln con Visual Studio.

2. Selecciona la configuración Debug o Release y la plataforma obligatoria x64 (PhysX requiere 64 bits).

3. Las dependencias externas (FreeGLUT / PhysX SDK) se restauran automáticamente vía NuGet al compilar el proyecto por primera vez.

4. Presiona F5 para compilar y lanzar la ventana de renderizado.

    
## 📂 Estructura del Repositorio

    SimulacionFisicaVideojuegos/

    ├── .gitignore          # Filtro de archivos temporales de VS y paquetes NuGet

    ├── README.md           # Guía e instrucciones del proyecto

    └── skeleton/           # Proyecto base en C++

        ├── game.sln        # Solución de Visual Studio

        ├── game.vcxproj    # Archivo de proyecto Visual C++

        ├── main.cpp        # Punto de entrada de la aplicación

        ├── Render/         # Modulo de renderizado base (Camera, Render)

        └── RenderUtils.*   # Utilidades gráficas y callbacks de teclado/ratón

## ⚠️ Resolución de Problemas Frecuentes

Asegúrate de que la plataforma seleccionada en Visual Studio sea x64 y no x86. Si el problema persiste, limpia la solución (Compilar $\rightarrow$ Limpiar solución) y fuerza la restauración de paquetes NuGet (Herramientas $\rightarrow$ Gestor de paquetes NuGet $\rightarrow$ Restaurar).

Asegúrate de no modificar la carpeta skeleton/packages/. El archivo .gitignore del repositorio está configurado para omitirla y evitar subir binarios pesados al control de versiones.

## 👨‍🏫 Profesorado y Tutorías

**Profesores:** Raúl Fernández y Lía García

**Departamento:** Arquitectura de Computadores y Automática.

**Ubicación:** Despacho 2.225, Segunda planta.  Facultad de Físicas.

