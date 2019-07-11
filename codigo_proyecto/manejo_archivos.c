#include <stdio.h>
#include <string.h>
#include "diagrama_de_casos_de_uso.c"

void escribir_diagrama_en_txt(struct DiagramaCasosDeUso *diagrama);

void crear_archivo_txt() {
    FILE *f = NULL;
    f = fopen("archivos_txt/archivo.txt", "a+");
    fclose(f);

    struct DiagramaCasosDeUso d;
    struct DiagramaCasosDeUso *diagrama = &d;
    strcpy((*diagrama).nombre, "Javier Apaza");
    escribir_diagrama_en_txt(diagrama);
}

void escribir_diagrama_en_txt(struct DiagramaCasosDeUso *diagrama) {
    FILE *f = NULL;
    f = fopen("archivos_txt/archivo.txt", "a+");

    fprintf(f, "{\n[%s]\n[", (*diagrama).nombre);

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n}\n");
    fclose(f);
}