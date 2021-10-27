#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedido.h"
#include "cliente.h"
#include "recoleccion.h"
#include "funciones.h"
#include "tipomaterial.h"
#include "localidad.h"

void CargarDatosHardcoded(ePedido listaPedidos[], eCliente listaClientes[], eRecoleccion listaRecoleccion[], eTipoMaterial listaTipoMaterial[], eLocalidad listaLocalidades[], int tamClientes, int tamPedidos, int tamRecoleccion, int tamTipoMaterial, int tamLocalidades);
int CrearPedido(ePedido listaPedidos[], eCliente listaClientes[], eLocalidad listaLocalidades[], int tamPedido, int tamClientes, int tamLocalidades, int* id);
eRecoleccion CrearRecoleccion(int* idIncremental, int idTipo, float cantKilos);
int ProcesarResiduos(eRecoleccion listaRecoleccion[], ePedido listaPedidos[], eCliente listaClientes[], eTipoMaterial listaTipoMaterial[], int tamPedido, int tamClientes, int tamRecoleccion, int tamMateriales);
int GetIdPedidoPorIdCliente(ePedido listaPedidos[], int tamCliente, int idCliente);
int InicioProcesarResiduos(ePedido listaPedidos[], eRecoleccion listaRecoleccion[], ePedido pedido, eTipoMaterial listaTipoMaterial[], int tamRecoleccion, int tamMateriales, int tamPedidos, int* idRecoleccion);
int MostrarListaClientesPedidos(eCliente listaClientes[], ePedido listaPedidos[], eLocalidad listaLocalidad[], int tamClientes, int tamPedidos, int tamLocalidad);
int MostrarPedidosCompletados(eCliente listaClientes[], ePedido listaPedidos[], eRecoleccion listaRecoleccion[], int tamClientes, int tamPedidos, int tamRecoleccion);
int MostrarPedidosPendientes(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos);
float ObtenerHdpeTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item);
float ObtenerLdpeTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item);
float ObtenerPpTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item);
float ObtenerTotalCantidadKgPp(eRecoleccion listaRecoleccion[], int tamRecoleccion);
int ObtenerCantidadDePedidosPorLocalidad(ePedido listaPedidos[], eCliente listaClientes[], eLocalidad listaLocalidades[], int tamPedidos, int tamClientes, int tamLocalidad);
int ObtenerKgPropilenoPromedioPorCliente(eRecoleccion listaRecoleccion[], eCliente listaClientes[], int tamRecoleccion, int tamClientes);

/// \fn int AltaCliente(eCliente[], int, int*)
/// \brief Genera el alta de un cliente en el sistema
/// \param listaClientes Lista donde se guardará el cliente
/// \param tam Tamaño del array
/// \param id Puntero a un valor de id para poder incrementar
/// \return 0 Si se pudo hacer, -1 si hubo un error
int AltaCliente(eCliente listaClientes[], eLocalidad listaLocalidades[], int tam, int tamLocalidades, int* id);

/// \fn int ObtenerPrimerEspacioLibreCliente(eCliente[], int)
/// \brief Busca el primer espacio libre en el array
/// \param listaClientes Lista donde se buscará espacio
/// \param tam Tamaño del array
/// \return index del array si se hay libre, -1 si hubo un error
int ObtenerPrimerEspacioLibreCliente(eCliente listaClientes[], int tam);

/// \fn int MostrarListaClientes(eCliente[], int)
/// \brief Muestra el listado de clientes
/// \param listaClientes
/// \param tam Tamaño del array
/// \return
int MostrarListaClientes(eCliente listaClientes[], eLocalidad listaLocalidad[], int tam, int tamLocalidad);

/// \fn void CargarDatosHardcodedCliente(eCliente[], int)
/// \brief Carga datos en la lista de clientes
/// \param listaClientes a cargar
/// \param tam Tamaño del array
void CargarDatosHardcodedCliente(eCliente listaClientes[], int tam);


/// \fn int ModificarCliente(eCliente[], int)
/// \brief Modifica un cliente. Dentro pide id de cliente y lo modifica
/// \param listaClientes Lista donde se modificará el cliente
/// \param tam Tamaño del array
/// \return
int ModificarCliente(eCliente listaClientes[], eLocalidad listaLocalidades[], int tam, int tamLocalidades);

/// \fn int BorrarCliente(eCliente[], int)
/// \brief Borra un cliente. Dentro pide id de cliente y lo elimina pidiendo confirmacion
/// \param listaClientes Lista donde se borrará el cliente
/// \param tam Tamaño del array
/// \return
int BorrarCliente(eCliente listaClientes[], eLocalidad listaLocalidades[], int tam, int tamLocalidades);



int MostrarClienteConMasPedidosPendientes(eCliente listaClientes[], ePedido listaPedidos[], eLocalidad listaLocalidad[], int tamClientes, int tamPedidos, int tamLocalidad);


int CantidadPedidosPendientesPorCliente(ePedido listaPedidos[], int tamPedidos, int idCliente);


int MostrarClienteConMasPedidosCompletados(eCliente listaClientes[], ePedido listaPedidos[], eLocalidad listaLocalidad[], int tamClientes, int tamPedidos, int tamLocalidad);


int MostrarClienteConMasPedidosEnTotal(eCliente listaClientes[], ePedido listaPedidos[], eLocalidad listaLocalidad[], int tamClientes, int tamPedidos, int tamLocalidad);
