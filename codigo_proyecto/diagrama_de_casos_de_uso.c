struct DiagramaCasosDeUso {
    char nombre [20];
    struct Autor *autores [20];
    struct CasoDeUso *casosDeUso [20];

    //relaciones
    struct Asociacion *asociaciones [20];
    struct Dependencia *dependencias [20];
    struct Inclusion *inclusiones [20];
    struct Exclusion *exclusiones [20];
    struct Generalizacion *generalizaciones [20];
};

struct Autor {
    char nombre [20];
};

struct CasoDeUso {
    char nombre [20];
    char descripcion [50];
};

struct Asociacion {
    struct Autor autor;
    struct CasoDeUso casoDeUso;
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

struct Exclusion {
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
    char anotacion [20];
};
