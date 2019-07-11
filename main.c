#include <stdio.h>
#include "codigo_proyecto/manejo_archivos.c"

int main () {
    printf("Hola Mundo,\n");

    //Este método pertenece a codigo_proyecto/manejo_archivos.c
    crear_archivo_txt();

    //Este método pertenece a codigo_proyecto/manejo_archivos.c
    //Por ahora se colocan los datos por consola, posteriormente se hara mediante la interfaz.
    agregar_diagrama_por_consola();

    return 1;
}