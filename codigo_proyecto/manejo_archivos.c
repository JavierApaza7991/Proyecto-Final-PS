#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool comparar_palabras(char *palabra1, char *palabra2);

void escribir_diagrama_en_txt(struct DiagramaCasosDeUso *diagrama);

void crear_archivo_txt() {
    FILE *f = NULL;
    f = fopen("archivos_txt/diagramas.txt", "a+");
    fclose(f);
}

void escribir_diagrama_en_txt(struct DiagramaCasosDeUso *diagrama) {
    FILE *f = NULL;
    f = fopen("archivos_txt/diagramas.txt", "a+");

    fprintf(f, "{\nNombre: [%s]\nAutores: [", (*diagrama).nombre);

    struct Autor *pAutores = (*diagrama).autores;
    for (int i = 0; i < (*diagrama).numeroAutores; i++) {
        fprintf(f, "%s,", (*pAutores).nombre);
        pAutores++;
    }

    fprintf(f, "]\nCasos de Uso: [");

    struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
    for (int i = 0; i < (*diagrama).numeroCasosdeUso; i++) {
        fprintf(f, "%s,", (*pCasosDeUso).nombre);
        pCasosDeUso++;
    }

    fprintf(f, "]\nAsociaciones: [");

    struct Asociacion *pAsociaciones = (*diagrama).asociaciones;
    for (int i = 0; i < (*diagrama).numeroAsociaciones; i++) {
        fprintf(f, "(%s,%s),", ((*pAsociaciones).autor)->nombre, ((*pAsociaciones).casoDeUso)->nombre);
        pAsociaciones++;
    }

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n[");

    fprintf(f, "]\n}\n");
    fclose(f);
}

void obtener_diagramas (struct DiagramaCasosDeUso *pDiagramas, int numeroDiagramas) {
    FILE *f = NULL;
    f = fopen("archivos_txt/diagramas.txt", "r");

    char linea[300] = "";
    //Sirve para identificar que hay almenos un diagrama mas
    fgets(linea, 300, f);

    while (!feof(f))
    {
        //Obtener nombre del diagrama
        fgets(linea, 300, f);
        char *p = linea;
        char *pNombre = (*pDiagramas).nombre;
        p = p + 9;
        while (*p != ']') {
            *pNombre = *p;
            pNombre++;
            p++;
        }
        printf("%s\n", (*pDiagramas).nombre);
        
        //Obtener autores del diagrama
        fgets(linea, 300, f);
        p = linea;
        struct Autor *autores = (*pDiagramas).autores;
        (*pDiagramas).numeroAutores = 0;
        p = p + 10;
        while (*p != ']') {
            char *nombreAutor = (*autores).nombre;
            while (*p != ',')
            {
                *nombreAutor = *p;
                nombreAutor++;
                p++;
            }
            printf("Autor: %s\n", (*autores).nombre);
            autores++;
            (*pDiagramas).numeroAutores++;
            p++;
        }

        //Obtener casos de uso del diagrama
        fgets(linea, 300, f);
        p = linea;
        struct CasoDeUso *casosDeUso = (*pDiagramas).casosDeUso;
        (*pDiagramas).numeroCasosdeUso = 0;
        p = p + 15;
        while (*p != ']') {
            char *nombreCaso = (*casosDeUso).nombre;
            while (*p != ',')
            {
                *nombreCaso = *p;
                nombreCaso++;
                p++;
            }
            printf("Casos: %s\n", (*casosDeUso).nombre);
            casosDeUso++;
            (*pDiagramas).numeroCasosdeUso++;
            p++;
        }

        //Obtener las relaciones de asociación del diagrama
        fgets(linea, 300, f);
        p = linea;
        struct Asociacion *asociaciones = (*pDiagramas).asociaciones;
        (*pDiagramas).numeroAsociaciones = 0;
        p = p + 15;
        while (*p != ']') {
            char autor [20] = "";
            char *nombreAutor = autor;
            p++;
            while (*p != ',')
            {
                *nombreAutor = *p;
                nombreAutor++;
                p++;
            }
            nombreAutor = autor;
            p++;
            struct Autor *pAutores = (*pDiagramas).autores;
            for (int i = 0; i < (*pDiagramas).numeroAutores; i++) {
                char *p = (*pAutores).nombre;
                if (comparar_palabras(nombreAutor, p))
                    break;
                pAutores++;
            }
            (*asociaciones).autor = pAutores;

            char caso [20] = "";
            char *nombreCaso = caso;
            while (*p != ')')
            {
                *nombreCaso = *p;
                nombreCaso++;
                p++;
            }
            nombreCaso = caso;
            p = p + 2;
            struct CasoDeUso *pCasos = (*pDiagramas).casosDeUso;
            for (int i = 0; i < (*pDiagramas).numeroCasosdeUso; i++) {
                char *p = (*pCasos).nombre;
                if (comparar_palabras(nombreCaso, p))
                    break;
                pCasos++;
            }
            (*asociaciones).casoDeUso = pCasos;

            printf("Asociacion: %s - %s\n", ((*asociaciones).autor)->nombre, ((*asociaciones).casoDeUso)->nombre);
            asociaciones++;
            (*pDiagramas).numeroAsociaciones++;
        }

        fgets(linea, 300, f);
        fgets(linea, 300, f);
        fgets(linea, 300, f);
        fgets(linea, 300, f);
        fgets(linea, 300, f);

        pDiagramas++;
        numeroDiagramas++;

        //Sirve para identificar que hay almenos un diagrama mas
        fgets(linea, 300, f);
    }
    fclose(f);
}