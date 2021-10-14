#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PEDIDOS 20
#define TAM_MAX_RECOLECCION 100
#define MIN_KILOS 50
#define MAX_KILOS 2000
#define PEDIDO_INIT_ID 200000
#define PEDIDO_MAX_ID 999999
#define EMPTY 0
#define FULL 1
#define TAM_ESTADO 15

typedef struct{
  int id;
  int idCliente;
  float kilosTotales;
  char estado[TAM_ESTADO];
  int idRecoleccion[TAM_MAX_RECOLECCION];
  int cantRecoleccion;
  int isEmpty;
} ePedido;

int ObtenerPrimerEspacioLibrePedidos(ePedido listaPedidos[], int tam);
void inicializarListaPedido(ePedido listaPedidos[], int tam);
void MostrarPedidoPendiente(char cuitCliente[], char direccion[], float cantKilos);
void MostrarPedidoCompletado(char cuitCliente[], char direccion[], float cantHdpe, float cantLdpe, float cantPp);
int MostrarListaPedidos(ePedido listaPedidos[], int tam);
void MostrarPedido(ePedido pedido);
ePedido ObtenerPedidoPorIdPedido(ePedido listaPedidos[], int tam, int idPedido);
ePedido ObtenerPedidoPorIdCliente(ePedido listaPedidos[], int tam, int idCliente);
void CargarDatosHardcodedPedido(ePedido listaPedidos[], int tam);
void GuardarPedidoPostRecoleccion(ePedido listaPedidos[], int tam, ePedido item);
