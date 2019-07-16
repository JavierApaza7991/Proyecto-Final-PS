#include <stdbool.h>
#include <gtk/gtk.h>

#include "diagrama_de_casos_de_uso.c"
#include "manejo_archivos.c"
#define FONT "Sans Bold 8"

GtkBuilder *gladear;
GtkBuilder *VentanaNueva;

GtkWidget *FrmPrincipal;
GtkWidget *FrmSecundario;
GtkWidget *nombrecrear;
GtkWidget *BtnNombre;
GtkWidget *autorcrear;
GtkWidget *BtnAutor;
GtkWidget *casousocrear;
GtkWidget *BtnCasoUso;
GtkWidget *ComboAutor;
GtkWidget *ComboCasoUso;
GtkWidget *BtnAsociacion;
GtkWidget *BtnEliminarAsociacion;
GtkWidget *AreaDiagrama;
GtkWidget *BtnNuevo;
GtkWidget *BtnCargar;
GtkWidget *BtnGuardar;
GtkWidget *EliminarDiagrama;
GtkWidget *AceptarDiagrama;
GtkWidget *ComboDiagrama;

float M_PI = 3.1416;

int numeroDiagramas = 0;
int *pNumeroDiagramas = &numeroDiagramas;
struct DiagramaCasosDeUso arregloDiagramas [20];
struct DiagramaCasosDeUso *pDiagramas = arregloDiagramas;

struct DiagramaCasosDeUso d;
struct DiagramaCasosDeUso *diagrama = &d;

void inicializar_numeros_diagrama ();
bool comparar_palabras(char *palabra1, char *palabra2);
int verficar_espacio (char *nombre);
void draw_text_autor (cairo_t *cr, int x, int y, struct Autor *autor);
void draw_text_caso (cairo_t *cr,int x, int y, char *caso);
void do_drawing_autor (cairo_t *cr, int x, int y, struct Autor *autor);
void do_drawing_caso (cairo_t *cr, int x, int y, char *caso);
void do_drawing_asociacion (cairo_t *cr, struct Autor *autor, struct CasoDeUso *caso);
static void do_drawing (cairo_t *cr);
static gboolean on_draw_event (GtkWidget *widget, cairo_t *cr, gpointer user_data);
void agregar_nombre (GtkButton* button, gpointer user_data);
void agregar_autor (GtkButton* button, gpointer user_data);
void agregar_caso_uso (GtkButton* button, gpointer user_data);
void agregar_asociacion (GtkButton* button, gpointer user_data);
void mensaje_error ();
void eliminar_asociacion (GtkButton* button, gpointer user_data);
void nuevo_diagrama (GtkButton* button, gpointer user_data);
void guardar_diagrama (GtkButton* button, gpointer user_data);
void seleccionar_diagrama (GtkButton* button, gpointer user_data);
void eliminar_diagrama (GtkButton* button, gpointer user_data);
void on_open_ventana (GtkButton* button, gpointer user_data);
void correr_interfaz (int argc, char *argv[]);

bool modo_editabe = false;

char *mensaje;

void inicializar_numeros_diagrama () {
    (*diagrama).numeroAutores = 0;
    (*diagrama).numeroCasosdeUso = 0;
    (*diagrama).numeroAsociaciones = 0;
}

bool comparar_palabras(char *palabra1, char *palabra2) {
    while (*palabra1 != '\0' && *palabra2 != '\0' && *palabra1 == *palabra2) {
        palabra1++;
        palabra2++;
    }

    if (*palabra1 != '\0' || *palabra2 != '\0')
        return false;

    return true;
}

int verficar_espacio (char *nombre){
    int contador = 0;
    while(*nombre != '\0'){
        if(*nombre != ' '){
            nombre++;
            contador++;
        }else
            break;
    }
    return contador;
}

void draw_text_autor (cairo_t *cr, int x, int y, struct Autor *autor)//char* autor)
{
    PangoLayout *layout;
    PangoFontDescription *desc;
    int i;

    cairo_move_to(cr, (x - 20)/2, y);
    layout = pango_cairo_create_layout (cr);

    pango_layout_set_text (layout, (*autor).nombre, -1); //autor, -1);
    desc = pango_font_description_from_string (FONT);
    pango_layout_set_font_description (layout, desc);
    pango_font_description_free (desc);
    cairo_save(cr);
    pango_cairo_show_layout (cr, layout);
}

void draw_text_caso (cairo_t *cr,int x, int y, char *caso) //char* caso  struct CasoDeUso *caso
{
    PangoLayout *layout;
    PangoFontDescription *desc;
    int i,contador=verficar_espacio(caso);

    cairo_move_to(cr, x-20,(y/2)-5);
    layout = pango_cairo_create_layout (cr);
    pango_layout_set_text (layout,caso,contador); //caso, 7);
    desc = pango_font_description_from_string (FONT);
    pango_layout_set_font_description (layout, desc);
    pango_font_description_free (desc);
    cairo_save(cr);
    pango_cairo_show_layout (cr, layout);
}

void do_drawing_autor (cairo_t *cr, int x, int y, struct Autor *autor)//char* autor)
{
    int k = x + 10;
    int l = y + 35;
    cairo_set_line_width(cr, 1);
    cairo_set_source_rgb(cr, 0.69, 0.19, 0); // color anterior //cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);

    //grafica del circulo
    cairo_arc(cr, x, y-5, 10, 0, 10); 
    //grafico de la columana
    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x, y);
    cairo_line_to(cr, x, y + 20);
    //grafico de los brazos
    cairo_move_to(cr, x / 2, y + 10);
    cairo_line_to(cr, x / 2, y + 10);
    cairo_line_to(cr, x + 15, y + 10);
    //grafico de la primera pierna
    cairo_move_to(cr, x, y + 20);
    cairo_line_to(cr, x, y + 20);
    cairo_line_to(cr, x - 10, y + 35);
    //grafico de la segunda pierna
    cairo_move_to(cr, x, y + 20);
    cairo_line_to(cr, x, y + 20);
    cairo_line_to(cr, x + 10, y + 35);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 0.3, 0.4, 0.6); 
    draw_text_autor(cr, k, l, autor);
    //cairo_close_path(cr);
    cairo_fill(cr); 
}

void do_drawing_caso (cairo_t *cr, int x, int y, char *caso) //char *caso) struct CasoDeUso *caso
{
    //cairo_set_source_rgb(cr, 0.1, 0, 0);
    cairo_set_line_width(cr, 5);  
    cairo_set_source_rgb(cr, 0.69, 0.19, 0);
    cairo_scale(cr, 1, 0.5);
    cairo_arc(cr, x, y, 50, 0, 2*M_PI);
    cairo_scale(cr, 1, 2);
    cairo_stroke_preserve(cr);
    draw_text_caso(cr,x,y,caso);
    cairo_set_source_rgba(cr, 0.3, 0.4, 0.6,0); 
    cairo_fill(cr);
}

void do_drawing_asociacion (cairo_t *cr, struct Autor *autor, struct CasoDeUso *caso) 
{
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, (*autor).posicionX, (*autor).posicionY);
    cairo_line_to(cr, (*autor).posicionX, (*autor).posicionY);
    cairo_line_to(cr, (*caso).posicionX-50, (*caso).posicionY);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);
}

static void do_drawing (cairo_t *cr)
{
    //cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
    cairo_set_line_width(cr, 1);

    struct Autor *pAutores = (*diagrama).autores;
    //Dibujando los autores
    for (int i = 0; i < (*diagrama).numeroAutores; i++) {
        (*pAutores).posicionX = 30;
        (*pAutores).posicionY = 40+i*90;

        do_drawing_autor(cr, (*pAutores).posicionX, (*pAutores).posicionY, pAutores);

        pAutores++;
    }

    struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
    //Dibujando los casos de uso
    for (int i = 0; i < (*diagrama).numeroCasosdeUso; i++) {
        (*pCasosDeUso).posicionX = 250;
        (*pCasosDeUso).posicionY = (150*i+55)/2;

        do_drawing_caso(cr, (*pCasosDeUso).posicionX, 150*i+55, (*pCasosDeUso).nombre);

        pCasosDeUso++;
    }

    struct Asociacion *pAsociaciones = (*diagrama).asociaciones;
    //Dibujando las relaciones de asociación
    for (int i = 0; i < (*diagrama).numeroAsociaciones; i++) {
        if ((*pAsociaciones).activo)
            do_drawing_asociacion(cr, (*pAsociaciones).autor, (*pAsociaciones).casoDeUso);

        pAsociaciones++;
    }
}

static gboolean on_draw_event (GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    do_drawing(cr);
    
    return FALSE;
}

void agregar_nombre (GtkButton* button, gpointer user_data) 
{
    bool diagrama_existe = false;
    const gchar *nombre = gtk_entry_get_text(GTK_ENTRY(nombrecrear));
    char *p = (char *) nombre;

    numeroDiagramas = 0;
    pNumeroDiagramas = &numeroDiagramas;
    pDiagramas = arregloDiagramas;
    //Este método pertenece a manejo_archivos.c
    obtener_diagramas(pDiagramas, pNumeroDiagramas);

    pDiagramas = arregloDiagramas;
    char *pNombreDiagrama;
    for (int i = 0; i < *pNumeroDiagramas; i++)
    {
        pNombreDiagrama = (*pDiagramas).nombre;
        if (comparar_palabras(p, pNombreDiagrama))
        {
            diagrama_existe = true;
            break;
        }
        pDiagramas++;
    }

    if (!diagrama_existe)
    {
        strcpy((*diagrama).nombre, nombre);
    } else
    {
        mensaje = "Ya existe un diagrama con este nombre.";
        printf("%s\n", mensaje);
        mensaje_error();
    }
}

void agregar_autor (GtkButton* button, gpointer user_data) 
{
    bool autor_existe = false;
    const gchar *nombre = gtk_entry_get_text(GTK_ENTRY(autorcrear));
    char *p = (char *) nombre;

    char *pNombreAutor;
    struct Autor *pAutores = (*diagrama).autores;
    for (int i = 0; i < (*diagrama).numeroAutores; i++) {
        pNombreAutor = (*pAutores).nombre;
        if (comparar_palabras(p, pNombreAutor))
        {
            autor_existe = true;
            break;
        }
        pAutores++;
    }
    
    if (!autor_existe)
    {
        strcpy((*pAutores).nombre, nombre);

        gtk_widget_queue_draw((GtkWidget *) user_data);

        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboAutor), (*pAutores).nombre);
        gtk_combo_box_set_active(GTK_COMBO_BOX(ComboAutor), 0);
        gtk_entry_set_text(GTK_ENTRY(autorcrear), "");

        (*diagrama).numeroAutores++;
    } else
    {
        mensaje = "El Autor ya existe.";
        printf("%s\n", mensaje);
        mensaje_error();
    }
}

void agregar_caso_uso (GtkButton* button, gpointer user_data) 
{
    bool caso_existe = false;
    const gchar *nombre = gtk_entry_get_text(GTK_ENTRY(casousocrear));
    char *p = (char *) nombre;

    char *pNombreCaso;
    struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
    for (int i = 0; i < (*diagrama).numeroCasosdeUso; i++) {
        pNombreCaso = (*pCasosDeUso).nombre;
        if (comparar_palabras(p, pNombreCaso))
        {
            caso_existe = true;
            break;
        }
        pCasosDeUso++;
    }
    
    if (!caso_existe)
    {
        strcpy((*pCasosDeUso).nombre, nombre);

        gtk_widget_queue_draw((GtkWidget *) user_data);

        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboCasoUso), (*pCasosDeUso).nombre);
        gtk_combo_box_set_active(GTK_COMBO_BOX(ComboCasoUso), 0);
        gtk_entry_set_text(GTK_ENTRY(casousocrear), "");

        (*diagrama).numeroCasosdeUso++;
    } else
    {
        mensaje = "El Caso de Uso ya existe.";
        printf("%s\n", mensaje);
        mensaje_error();
    }
}

void agregar_asociacion (GtkButton* button, gpointer user_data) 
{
    bool asociacion_existe = false;
    gchar *autor = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ComboAutor));
    gchar *casoDeUso = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ComboCasoUso));

    char *pNombreAutor;
    char *pNombreCaso;
    struct Asociacion *pAsociaciones = (*diagrama).asociaciones;
    for (int i = 0; i < (*diagrama).numeroAsociaciones; i++) {
        pNombreAutor = ((*pAsociaciones).autor)->nombre;
        pNombreCaso = ((*pAsociaciones).casoDeUso)->nombre;
        if ((*pAsociaciones).activo && comparar_palabras(autor, pNombreAutor) && comparar_palabras(casoDeUso, pNombreCaso))
        {
            asociacion_existe = true;
            break;
        }
        pAsociaciones++;
    }

    if (!asociacion_existe)
    {
        struct Autor *pAutores = (*diagrama).autores;
        for (int i = 0; i < (*diagrama).numeroAutores; i++) {
            if (comparar_palabras((*pAutores).nombre, autor))
                break;
            pAutores++;
        }

        struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
        for (int i = 0; i < (*diagrama).numeroCasosdeUso; i++) {
            if (comparar_palabras((*pCasosDeUso).nombre, casoDeUso))
                break;
            pCasosDeUso++;
        }

        (*pAsociaciones).autor = pAutores;
        (*pAsociaciones).casoDeUso = pCasosDeUso;
        (*pAsociaciones).activo = true;

        gtk_widget_queue_draw((GtkWidget *) user_data);

        (*diagrama).numeroAsociaciones++;
    } else
    {
        mensaje = "La Relación de Asociación ya existe.";
        printf("%s\n", mensaje);
        mensaje_error();
    }
}

void mensaje_error ()
{   
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new (GTK_WINDOW(FrmPrincipal), 0, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, mensaje);
    gtk_window_set_title(GTK_WINDOW(dialog), "Error");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void eliminar_asociacion (GtkButton* button, gpointer user_data) 
{
    bool encontrado = false;
    
    gchar *autor = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ComboAutor));
    gchar *casoDeUso = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ComboCasoUso));

    char *autorAsociacion;
    char *casoAsociacion;
    struct Asociacion *pAsociaciones = (*diagrama).asociaciones;
    for (int i = 0; i < (*diagrama).numeroAsociaciones; i++) {
        autorAsociacion = ((*pAsociaciones).autor)->nombre;
        casoAsociacion = ((*pAsociaciones).casoDeUso)->nombre;
        if (comparar_palabras(autor, autorAsociacion) && comparar_palabras(casoDeUso, casoAsociacion) && (*pAsociaciones).activo) 
        {
            (*pAsociaciones).activo = false;
            encontrado = true;
            break;
        }
        pAsociaciones++;
    }
    if (!encontrado) 
    {   
        mensaje = "La relación de Asociación no se encontró.";
        printf("%s\n", mensaje);
        mensaje_error();
    }

    gtk_widget_queue_draw((GtkWidget *) user_data);
}

void nuevo_diagrama (GtkButton* button, gpointer user_data) 
{
    modo_editabe = false;

    gtk_entry_set_text(GTK_ENTRY(nombrecrear), "");
    gtk_entry_set_text(GTK_ENTRY(autorcrear), "");
    gtk_entry_set_text(GTK_ENTRY(casousocrear), "");

    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(ComboAutor));
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(ComboCasoUso));

    struct DiagramaCasosDeUso *nuevoDiagrama = malloc (sizeof (struct DiagramaCasosDeUso));
    strcpy((*nuevoDiagrama).nombre, "");
    
    diagrama = nuevoDiagrama;
    inicializar_numeros_diagrama ();

    gtk_widget_queue_draw ((GtkWidget *) user_data);
}

void guardar_diagrama (GtkButton* button, gpointer user_data) 
{
    pNumeroDiagramas = &numeroDiagramas;
    pDiagramas = arregloDiagramas;

    //Estos métodos pertenecen a manejo_archivos.c
    if (modo_editabe)
        editar_diagramas_en_txt(pDiagramas, pNumeroDiagramas);
    else
        escribir_diagrama_en_txt(diagrama);

    printf("Se ha guardado exitosamente.\n");

    modo_editabe = true;

    numeroDiagramas = 0;
    pNumeroDiagramas = &numeroDiagramas;
    pDiagramas = arregloDiagramas;
    //Este método pertenece a manejo_archivos.c
    obtener_diagramas(pDiagramas, pNumeroDiagramas);

    //Con esto el usuario puede seguir editando el diagrama que ha editado
    const gchar *nombre = gtk_entry_get_text(GTK_ENTRY(nombrecrear));
    char *p = (char *) nombre;
    char *pNombreDiagrama;

    pDiagramas = arregloDiagramas;
    for (int i = 0; i < numeroDiagramas; i++)
    {   
        pNombreDiagrama = (*pDiagramas).nombre;
        if (comparar_palabras(p, pNombreDiagrama))
            break;
        pDiagramas++;
    }

    diagrama = pDiagramas;
}

void seleccionar_diagrama (GtkButton* button, gpointer user_data)
{   
    modo_editabe = true;
    
    //g_signal_connect(BtnCargar, "clicked", G_CALLBACK(cargar_diagramas), AreaDiagrama);
    gchar *pTexto = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ComboDiagrama));
    char *pNombreDiagrama;

    printf("Número de diagramas: %d\n", numeroDiagramas);

    pDiagramas = arregloDiagramas;
    for (int i = 0; i < numeroDiagramas; i++)
    {   
        pNombreDiagrama = (*pDiagramas).nombre;
        if (comparar_palabras(pTexto, pNombreDiagrama))
            break;
        pDiagramas++;
    }

    diagrama = pDiagramas;

    //Colocar el nombre del diagrama q se va a editar
    gtk_entry_set_text(GTK_ENTRY(nombrecrear), (*diagrama).nombre);

    //Eliminar todos los elementos del combobox de autores
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(ComboAutor));
    //Colocar los autores en el combobox del diagrama q se va a editar
    struct Autor *pAutores = (*diagrama).autores;
    for (int i = 0; i < (*diagrama).numeroAutores; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboAutor), (*pAutores).nombre);
        gtk_combo_box_set_active(GTK_COMBO_BOX(ComboAutor), 0);
        pAutores++;
    }

    //Eliminar todos los elementos del combobox de casos de uso
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(ComboCasoUso));
    //Colocar los casos de uso en el combobox del diagrama q se va a editar
    struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
    for (int i = 0; i < (*diagrama).numeroCasosdeUso; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboCasoUso), (*pCasosDeUso).nombre);
        gtk_combo_box_set_active(GTK_COMBO_BOX(ComboCasoUso), 0);
        pCasosDeUso++;
    }

    //Con esto se grafica automáticamente el diagrama guardado en el .txt
    gtk_widget_queue_draw((GtkWidget *) user_data);

    gtk_widget_destroy(FrmSecundario);
}

void eliminar_diagrama (GtkButton* button, gpointer user_data)
{
    gchar *pTexto = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ComboDiagrama));
    char *pNombreDiagrama;

    pDiagramas = arregloDiagramas;
    for (int i = 0; i < numeroDiagramas; i++)
    {   
        pNombreDiagrama = (*pDiagramas).nombre;
        if (comparar_palabras(pTexto, pNombreDiagrama)) {
            (*pDiagramas).activo = false;
            break;
        }
        pDiagramas++;
    }

    pDiagramas = arregloDiagramas;
    pNumeroDiagramas = &numeroDiagramas;
    editar_diagramas_en_txt(pDiagramas, pNumeroDiagramas);

    //Cargando al combobox todos los nombres de los diagramas del .txt
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(ComboDiagrama));
    pDiagramas = arregloDiagramas;
    for (int i = 0; i < *pNumeroDiagramas; i++)
    {
        if ((*pDiagramas).activo) {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboDiagrama), (*pDiagramas).nombre);
            gtk_combo_box_set_active(GTK_COMBO_BOX(ComboDiagrama), 0);
        }
        pDiagramas++;
    }
}

void on_open_ventana (GtkButton* button, gpointer user_data)
{   
    /*GtkWidget *VentanaNueva;
    GtkWidget *ComboDiagrama;

    VentanaNueva = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
    gtk_window_set_position(GTK_WINDOW(VentanaNueva), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(VentanaNueva), 600, 300); 
    gtk_window_set_title(GTK_WINDOW(VentanaNueva), "Diagramas");

    gtk_widget_show_all(VentanaNueva);*/
    VentanaNueva = gtk_builder_new();
    gtk_builder_add_from_file(VentanaNueva, "part2.glade", NULL);

    FrmSecundario = GTK_WIDGET(gtk_builder_get_object(VentanaNueva, "ventana2"));

    ComboDiagrama = GTK_WIDGET(gtk_builder_get_object(VentanaNueva, "comboDiagrama"));
    EliminarDiagrama = GTK_WIDGET(gtk_builder_get_object(VentanaNueva, "eliminardiagrama"));
    AceptarDiagrama = GTK_WIDGET(gtk_builder_get_object(VentanaNueva, "aceptarDiagrama"));

    numeroDiagramas = 0;
    pNumeroDiagramas = &numeroDiagramas;
    pDiagramas = arregloDiagramas;
    //Este método pertenece a manejo_archivos.c
    obtener_diagramas(pDiagramas, pNumeroDiagramas);

    //Cargando al combobox todos los nombres de los diagramas del .txt
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(ComboDiagrama));
    pDiagramas = arregloDiagramas;
    for (int i = 0; i < *pNumeroDiagramas; i++)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboDiagrama), (*pDiagramas).nombre);
        gtk_combo_box_set_active(GTK_COMBO_BOX(ComboDiagrama), 0);
        pDiagramas++;
    }
    
    g_signal_connect(EliminarDiagrama, "clicked", G_CALLBACK(eliminar_diagrama), NULL);
    g_signal_connect(AceptarDiagrama, "clicked", G_CALLBACK(seleccionar_diagrama), AreaDiagrama); 
    g_object_unref(G_OBJECT (VentanaNueva));
    gtk_widget_show_all(FrmSecundario);  
}

void correr_interfaz (int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    gladear = gtk_builder_new();
    gtk_builder_add_from_file(gladear, "part1.glade", NULL);

    FrmPrincipal = GTK_WIDGET(gtk_builder_get_object(gladear, "window"));

    nombrecrear = GTK_WIDGET(gtk_builder_get_object(gladear, "nombrecrear"));
    BtnNombre = GTK_WIDGET(gtk_builder_get_object(gladear, "botonnombre"));
    autorcrear = GTK_WIDGET(gtk_builder_get_object(gladear, "autorcrear"));
    BtnAutor = GTK_WIDGET(gtk_builder_get_object(gladear, "botonautor"));
    casousocrear = GTK_WIDGET(gtk_builder_get_object(gladear, "casocrear"));
    BtnCasoUso = GTK_WIDGET(gtk_builder_get_object(gladear, "botoncasos"));
    ComboAutor = GTK_WIDGET(gtk_builder_get_object(gladear, "comboautor"));
    ComboCasoUso = GTK_WIDGET(gtk_builder_get_object(gladear, "combocaso"));
    BtnAsociacion = GTK_WIDGET(gtk_builder_get_object(gladear, "botonasociacion"));
    BtnEliminarAsociacion = GTK_WIDGET(gtk_builder_get_object(gladear, "botoneliminarasociacion"));
    AreaDiagrama = GTK_WIDGET(gtk_builder_get_object(gladear, "areaDiagrama"));
    BtnNuevo = GTK_WIDGET(gtk_builder_get_object(gladear, "botonnuevodiagrama"));
    BtnCargar = GTK_WIDGET(gtk_builder_get_object(gladear, "cargarDiagrama"));
    BtnGuardar = GTK_WIDGET(gtk_builder_get_object(gladear, "botonguardar"));

    inicializar_numeros_diagrama();

    g_signal_connect(FrmPrincipal, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(BtnNombre, "clicked", G_CALLBACK(agregar_nombre), NULL);
    g_signal_connect(BtnAutor, "clicked", G_CALLBACK(agregar_autor), AreaDiagrama);
    g_signal_connect(BtnCasoUso, "clicked", G_CALLBACK(agregar_caso_uso), AreaDiagrama);
    g_signal_connect(BtnAsociacion, "clicked", G_CALLBACK(agregar_asociacion), AreaDiagrama);
    g_signal_connect(BtnEliminarAsociacion, "clicked", G_CALLBACK(eliminar_asociacion), AreaDiagrama);
    g_signal_connect(G_OBJECT(AreaDiagrama), "draw", G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(BtnNuevo, "clicked", G_CALLBACK(nuevo_diagrama), AreaDiagrama);
    g_signal_connect(BtnCargar, "clicked", G_CALLBACK(on_open_ventana), VentanaNueva);
    //g_signal_connect(BtnCargar, "clicked", G_CALLBACK(cargar_diagramas), AreaDiagrama);
    g_signal_connect(BtnGuardar, "clicked", G_CALLBACK(guardar_diagrama), NULL);
    //g_signal_connect(BtnGuardar, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    g_object_unref(G_OBJECT (gladear));
    gtk_widget_show_all(FrmPrincipal);                
    gtk_main();
}