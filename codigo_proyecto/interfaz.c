#include <gtk/gtk.h>

#include "diagrama_de_casos_de_uso.c"
#include "manejo_archivos.c"

GtkBuilder *gladear;
GtkWidget *FrmPrincipal;
GtkWidget *nombrecrear;
GtkWidget *BtnNombre;
GtkWidget *autorcrear;
GtkWidget *BtnAutor;
GtkWidget *casousocrear;
GtkWidget *BtnCasoUso;
GtkWidget *BtnGuardar;


struct DiagramaCasosDeUso d;
struct DiagramaCasosDeUso *diagrama = &d;

void inicializar_numeros_diagrama () {
    (*diagrama).numeroAutores = 0;
    (*diagrama).numeroCasosdeUso = 0;
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
    for (int i = 0; i < (*diagrama).numeroAutores; i++){
        pAutores++;
    }
    strcpy((*pAutores).nombre, nombre);
    (*diagrama).numeroAutores++;
}

void agregar_caso_uso (GtkButton* button, gpointer user_data) 
{
    const gchar *nombre = gtk_entry_get_text(GTK_ENTRY(casousocrear));

    struct CasoDeUso *pCasosDeUso = (*diagrama).casosDeUso;
    for (int i = 0; i < (*diagrama).numeroCasosdeUso; i++){
        pCasosDeUso++;
    }
    strcpy((*pCasosDeUso).nombre, nombre);
    (*diagrama).numeroCasosdeUso++;
}

void guardar_diagrama (GtkButton* button, gpointer user_data) 
{
    escribir_diagrama_en_txt(diagrama);
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
    BtnGuardar = GTK_WIDGET(gtk_builder_get_object(gladear, "botonguardar"));

    inicializar_numeros_diagrama();

    g_signal_connect(FrmPrincipal, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(BtnNombre, "clicked", G_CALLBACK(agregar_nombre), NULL);
    g_signal_connect(BtnAutor, "clicked", G_CALLBACK(agregar_autor), NULL);
    g_signal_connect(BtnCasoUso, "clicked", G_CALLBACK(agregar_caso_uso), NULL);
    g_signal_connect(BtnGuardar, "clicked", G_CALLBACK(guardar_diagrama), NULL);
    g_signal_connect(BtnGuardar, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    g_object_unref(G_OBJECT (gladear));
    gtk_widget_show_all(FrmPrincipal);                
    gtk_main();
}