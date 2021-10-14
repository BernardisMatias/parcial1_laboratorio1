#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedido.h"
#include "cliente.h"
#include "recoleccion.h"
#include "funciones.h"
#include "tipomaterial.h"

void CargarDatosHardcoded(ePedido listaPedidos[], eCliente listaClientes[], eRecoleccion listaRecoleccion[], eTipoMaterial listaTipoMaterial[], int tamClientes, int tamPedidos, int tamRecoleccion, int tamTipoMaterial);
int CrearPedido(ePedido listaPedidos[], eCliente listaClientes[], int tamPedido, int tamClientes, int* id);
eRecoleccion CrearRecoleccion(int* idIncremental, int idTipo, float cantKilos);
int ProcesarResiduos(eRecoleccion listaRecoleccion[], ePedido listaPedidos[], eCliente listaClientes[], eTipoMaterial listaTipoMaterial[], int tamPedido, int tamClientes, int tamRecoleccion, int tamMateriales);
int GetIdPedidoPorIdCliente(ePedido listaPedidos[], int tamCliente, int idCliente);
int InicioProcesarResiduos(ePedido listaPedidos[], eRecoleccion listaRecoleccion[], ePedido pedido, eTipoMaterial listaTipoMaterial[], int tamRecoleccion, int tamMateriales, int tamPedidos, int* idRecoleccion);
int MostrarListaClientesPedidos(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos);
int MostrarPedidosCompletados(eCliente listaClientes[], ePedido listaPedidos[], eRecoleccion listaRecoleccion[], int tamClientes, int tamPedidos, int tamRecoleccion);
int MostrarPedidosPendientes(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos);
float ObtenerHdpeTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item);
float ObtenerLdpeTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item);
float ObtenerPpTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item);
float ObtenerTotalCantidadKgPp(eRecoleccion listaRecoleccion[], int tamRecoleccion);
int ObtenerCantidadDePedidosPorLocalidad(ePedido listaPedidos[], eCliente listaClientes[], int tamPedidos, int tamClientes);
int ObtenerKgPropilenoPromedioPorCliente(eRecoleccion listaRecoleccion[], eCliente listaClientes[], int tamRecoleccion, int tamClientes);



int MostrarClienteConMasPedidosPendientes(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos);
int CantidadPedidosPendientesPorCliente(ePedido listaPedidos[], int tamPedidos, int idCliente);
int MostrarClienteConMasPedidosCompletados(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos);
int MostrarClienteConMasPedidosEnTotal(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos);
