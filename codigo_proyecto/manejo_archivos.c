#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "diagrama_de_casos_de_uso.c"

void escribir_diagrama_en_txt(struct DiagramaCasosDeUso *diagrama);

void crear_archivo_txt() {
    FILE *f = NULL;
    f = fopen("archivos_txt/diagramas.txt", "a+");
    fclose(f);
}

void agregar_diagrama_por_consola() {
    char nombre [20];
    char autor [20];
    char casodeuso [20];

    struct DiagramaCasosDeUso d;
    struct DiagramaCasosDeUso *diagrama = &d;

    printf("Ingrese el nombre para el diagrama:\n");
    gets(nombre);
    strcpy((*diagrama).nombre, nombre);

    struct Autor *pAutores = (*diagrama).autores;
    (*diagrama).numeroAutores = 0;
    for (int i = 0; i < 5; i++) {
        printf("Ingrese un autor:\n");
        gets(autor);
        strcpy((*pAutores).nombre, autor);
        pAutores++;
        (*diagrama).numeroAutores++;
    }

    struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
    (*diagrama).numeroCasosdeUso = 0;
    for (int i = 0; i < 5; i++) {
        printf("Ingrese un caso de uso:\n");
        gets(casodeuso);
        strcpy((*pCasosDeUso).nombre, casodeuso);
        pCasosDeUso++;
        (*diagrama).numeroCasosdeUso ++;
    }

    escribir_diagrama_en_txt(diagrama);
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