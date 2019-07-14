#include <gtk/gtk.h>

#include "diagrama_de_casos_de_uso.c"
#include "manejo_archivos.c"
#define FONT "Sans Bold 8"

GtkBuilder *gladear;
GtkWidget *FrmPrincipal;
GtkWidget *nombrecrear;
GtkWidget *BtnNombre;
GtkWidget *autorcrear;
GtkWidget *BtnAutor;
GtkWidget *casousocrear;
GtkWidget *BtnCasoUso;
GtkWidget *ComboAutor;
GtkWidget *ComboCasoUso;
GtkWidget *BtnAsociacion;
GtkWidget *AreaDiagrama;
GtkWidget *BtnCargar;
GtkWidget *BtnGuardar;

float M_PI = 3.1416;

struct DiagramaCasosDeUso d;
struct DiagramaCasosDeUso *diagrama = &d;

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
    const gchar *nombre = gtk_entry_get_text(GTK_ENTRY(nombrecrear));

    strcpy((*diagrama).nombre, nombre);
}

void agregar_autor (GtkButton* button, gpointer user_data) 
{
    const gchar *nombre = gtk_entry_get_text(GTK_ENTRY(autorcrear));

    struct Autor *pAutores = (*diagrama).autores;
    for (int i = 0; i < (*diagrama).numeroAutores; i++) {
        pAutores++;
    }
    strcpy((*pAutores).nombre, nombre);

    gtk_widget_queue_draw((GtkWidget *) user_data);

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboAutor), (*pAutores).nombre);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ComboAutor), 0);

    (*diagrama).numeroAutores++;
}

void agregar_caso_uso (GtkButton* button, gpointer user_data) 
{
    const gchar *nombre = gtk_entry_get_text(GTK_ENTRY(casousocrear));

    struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
    for (int i = 0; i < (*diagrama).numeroCasosdeUso; i++) {
        pCasosDeUso++;
    }
    strcpy((*pCasosDeUso).nombre, nombre);

    gtk_widget_queue_draw((GtkWidget *) user_data);

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ComboCasoUso), (*pCasosDeUso).nombre);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ComboCasoUso), 0);

    (*diagrama).numeroCasosdeUso++;
}

void agregar_asociacion (GtkButton* button, gpointer user_data) 
{
    gchar *autor = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ComboAutor));
    gchar *casoDeUso = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ComboCasoUso));

    struct Asociacion *pAsociaciones = (*diagrama).asociaciones;
    for (int i = 0; i < (*diagrama).numeroAsociaciones; i++) {
        pAsociaciones++;
    }

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

    gtk_widget_queue_draw((GtkWidget *) user_data);

    (*diagrama).numeroAsociaciones++;
}

void guardar_diagrama (GtkButton* button, gpointer user_data) 
{
    //Este método pertenece a manejo_archivos.c
    escribir_diagrama_en_txt(diagrama);
}

void cargar_diagramas (GtkButton* button, gpointer user_data) 
{
    int numeroDiagramas = 0;
    struct DiagramaCasosDeUso diagramas [20];
    struct DiagramaCasosDeUso *pDiagramas = diagramas;

    //Este método pertenece a manejo_archivos.c
    obtener_diagramas(pDiagramas, numeroDiagramas);
    
    diagrama = &diagramas[0];

    gtk_widget_queue_draw((GtkWidget *) user_data);
    printf("Cargo todos los diagramas.\n");
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
    AreaDiagrama = GTK_WIDGET(gtk_builder_get_object(gladear, "areaDiagrama")); 
    BtnCargar = GTK_WIDGET(gtk_builder_get_object(gladear, "cargarDiagrama"));
    BtnGuardar = GTK_WIDGET(gtk_builder_get_object(gladear, "botonguardar"));

    inicializar_numeros_diagrama();

    g_signal_connect(FrmPrincipal, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(BtnNombre, "clicked", G_CALLBACK(agregar_nombre), NULL);
    g_signal_connect(BtnAutor, "clicked", G_CALLBACK(agregar_autor), AreaDiagrama);
    g_signal_connect(BtnCasoUso, "clicked", G_CALLBACK(agregar_caso_uso), AreaDiagrama);
    g_signal_connect(BtnAsociacion, "clicked", G_CALLBACK(agregar_asociacion), AreaDiagrama);
    g_signal_connect(G_OBJECT(AreaDiagrama), "draw", G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(BtnCargar, "clicked", G_CALLBACK(cargar_diagramas), AreaDiagrama);
    g_signal_connect(BtnGuardar, "clicked", G_CALLBACK(guardar_diagrama), NULL);
    g_signal_connect(BtnGuardar, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    g_object_unref(G_OBJECT (gladear));
    gtk_widget_show_all(FrmPrincipal);                
    gtk_main();
}