#include <stdbool.h>

struct Autor {
    char nombre [20];
    int posicionX;
    int posicionY;
};

struct CasoDeUso {
    char nombre [20];
    char descripcion [50];
    int posicionX;
    int posicionY;
};

struct Asociacion {
    struct Autor *autor;
    struct CasoDeUso *casoDeUso;
    char anotacion [20];
};

struct Dependencia {
    struct CasoDeUso casoDeUso;
    struct CasoDeUso casoDeUso2;
    char anotacion [20];
};

struct Inclusion {
    struct CasoDeUso casoDeUso;
    struct CasoDeUso casoDeUso2;
    char anotacion [20];
};

struct Extension {
    struct CasoDeUso casoDeUso;
    struct CasoDeUso casoDeUso2;
    char anotacion [20];
};

struct Generalizacion {
    //Si hay herencia, tipo puede ser a:entre autores y c:entre casos de uso    
    char tipo;
    
    struct Autor autor;
    struct Autor autor2;
    struct CasoDeUso casoDeUso;
    struct CasoDeUso casoDeUso2;
    char anotacion  [20];
};

struct DiagramaCasosDeUso {
    char nombre [20];

    int numeroAutores;
    int numeroCasosdeUso;
    int numeroAsociaciones;
    int numeroDependencias;
    int numeroInclusiones;
    int numeroExtensiones;
    int numeroGeneralizaciones;

    struct Autor autores [20];
    struct CasoDeUso casosDeUso [20];

    //relaciones
    struct Asociacion asociaciones [20];
    struct Dependencia dependencias [20];
    struct Inclusion inclusiones [20];
    struct Extension extensiones [20];
    struct Generalizacion generalizaciones [20];
};
