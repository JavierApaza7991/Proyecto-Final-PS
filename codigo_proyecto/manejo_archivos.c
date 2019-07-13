#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void escribir_diagrama_en_txt(struct DiagramaCasosDeUso *diagrama);

void crear_archivo_txt() {
    FILE *f = NULL;
    f = fopen("archivos_txt/diagramas.txt", "a+");
    fclose(f);
}

void escribir_diagrama_en_txt(struct DiagramaCasosDeUso *diagrama) {
    FILE *f = NULL;
    f = fopen("archivos_txt/diagramas.txt", "a+");

    fprintf(f, "{\n[%s]\n[", (*diagrama).nombre);

    struct Autor *pAutores = (*diagrama).autores;
    for (int i = 0; i < (*diagrama).numeroAutores; i++) {
        fprintf(f, "%s,", (*pAutores).nombre);
        pAutores++;
    }

    fprintf(f, "]\n[");

    struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
    for (int i = 0; i < (*diagrama).numeroCasosdeUso; i++) {
        fprintf(f, "%s,", (*pCasosDeUso).nombre);
        pCasosDeUso++;
    }

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n}\n");
    fclose(f);
}