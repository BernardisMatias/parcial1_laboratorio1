#include <stdio.h>
#define TAM_RECOLECCION 100
#define MAX_INGRESOS 3
#define MAX_CANTIDAD_KILOS 5000
#define EMPTY 0
#define FULL 1
#define RECOLECCION_INIT_ID 300000

typedef struct{
  int id;
  int idTipoMaterial;
  float cantidadKilos;
  int isEmpty;
} eRecoleccion;

void inicializarListaRecoleccion(eRecoleccion listaRecoleccion[], int tam);
int ObtenerPrimerEspacioLibreRecoleccion(eRecoleccion listaRecoleccion[], int tam);
eRecoleccion ObtenerRecoleccionPorId(eRecoleccion listaRecoleccion[], int tam, int idRecoleccion);
int GuardarRecoleccionEnPrimerEspacioLibre(eRecoleccion listaRecoleccion[], int tam, eRecoleccion item);
void CargarDatosHardcodedRecoleccion(eRecoleccion listaRecoleccion[], int tam);
eRecoleccion ObtenerTodasLasRecoleccionesPorId(int idRecoleccion);
//Funciones aux
void MostrarListaRecoleccion(eRecoleccion listaRecoleccion[], int tam);
void MostrarRecoleccion(eRecoleccion item);
