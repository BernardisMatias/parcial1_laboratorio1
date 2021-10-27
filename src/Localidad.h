#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#define TAM_DE_LOCALIDAD 150
#define TAM_LISTA_LOCALIDAD 50
#define ID_LOCALIDAD_MIN 1
#define ID_LOCALIDAD_MAX 9999

typedef struct{
   int id;
   char descripcion[TAM_DE_LOCALIDAD];
   int isEmpty;
}eLocalidad;

int MostrarListaLocalidades(eLocalidad listaLocalidad[], int tam);
void MostrarLocalidad(int id, char descripcion[]);
int ObtenerPrimerEspacioLibreLocalidad(eLocalidad listaLocalidad[], int tam);
int DescripcionLocalidadPorId(char descripcionDestino[], eLocalidad listaLocalidad[], int tam, int id);
void CargarDatosHardcodedLocalidad(eLocalidad listaLocalidad[], int tam);
