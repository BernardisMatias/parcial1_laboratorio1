
#include <stdio.h>
#include <stdlib.h>
#include "evento.h"
#include "funciones.h"

int main(void) {

	int opcion;
	int resultAlta;
	int idCliente = CLIENTE_INIT_ID;
	int idPedidos = PEDIDO_INIT_ID;
	setbuf(stdout, NULL);
	eCliente listaClientes[TAM_CLIENTES];
	ePedido listaPedidos[TAM_PEDIDOS];
	eRecoleccion listaRecoleccion[TAM_RECOLECCION];
	eTipoMaterial listaTipoMaterial[TAM_TIPO_MATERIAL];
	eLocalidad listaLocalidad[TAM_LISTA_LOCALIDAD];

	inicializarListaClientes(listaClientes, TAM_CLIENTES);
	inicializarListaPedido(listaPedidos, TAM_PEDIDOS);
	inicializarListaRecoleccion(listaRecoleccion, TAM_RECOLECCION);
	InicializarListaTipoMaterial(listaTipoMaterial, TAM_TIPO_MATERIAL);
	CargarDatosHardcoded(listaPedidos, listaClientes, listaRecoleccion, listaTipoMaterial, listaLocalidad, TAM_CLIENTES, TAM_PEDIDOS, TAM_RECOLECCION, TAM_TIPO_MATERIAL, TAM_LISTA_LOCALIDAD);


	do{
		printf("-- SISTEMA DE RECICLADO DE PLASTICO --\n");
		printf("-CLIENTES\n");
		printf("1. Alta de CLIENTE\n");
		printf("2. Modificar CLIENTE\n");
		printf("3. Borrar CLIENTE\n");
		printf("-RECICLADO\n");
		printf("4. Crear PEDIDO\n");
		printf("5. Procesar RESIDUOS\n");
		printf("6. Mostrar lista de CLIENTES\n");
		printf("7. Mostrar lista de PEDIDOS 'PENDIENTES'\n");
		printf("8. Mostrar lista de PEDIDOS 'COMPLETADOS'\n");
		printf("9. Mostrar cantidad de PEDIDOS 'PENDIENTES' por localidad ingresada\n");
		printf("10. Mostrar PROMEDIO de Kg. de Polipropileno/CLIENTE\n");
		printf("\n\n");
		printf("\nExtra\n");
		printf("11. Cliente con m?s pedidos 'PENDIENTES'\n");
		printf("12. Cliente con m?s pedidos 'COMPLETADOS'\n");
		printf("13. Cliente con m?s PEDIDOS\n");
		if(GetEntero(&opcion, "Elija una opcion: ", 1, 14, 15) == -1){
			break;
		}
		switch(opcion){
			case 1:
				resultAlta = AltaCliente(listaClientes, listaLocalidad, TAM_CLIENTES, TAM_LISTA_LOCALIDAD, &idCliente);
				if(resultAlta == 0){
					puts("El cliente se cargo exitosamente.\n");
				} else if(resultAlta == -1){
					puts("La lista de clientes esta llena.\n");
				} else {
					puts("El cliente no pudo cargarse.\n");
				}
				break;
			case 2:
				if(ModificarCliente(listaClientes, listaLocalidad, TAM_CLIENTES, TAM_LISTA_LOCALIDAD) == 0){
					printf("\nEl cliente fue modificado exitosamente.\n");
				} else{
					printf("\nEl cliente no pudo ser modificado.\n");
				}
				break;
			case 3:
				if(BorrarCliente(listaClientes, listaLocalidad, TAM_CLIENTES, TAM_LISTA_LOCALIDAD) == 1){
					printf("\nEl cliente fue eliminado exitosamente.\n");
				}else{
					printf("\nNo se pudo eliminar el cliente.\n");
				}
				break;
			case 4:
				if(CrearPedido(listaPedidos, listaClientes, listaLocalidad, TAM_PEDIDOS, TAM_CLIENTES, TAM_LISTA_LOCALIDAD, &idPedidos) == 0){
					printf("Se creo pedido correctamente\n");
				}
			   break;
			case 5:
				if(ProcesarResiduos(listaRecoleccion, listaPedidos, listaClientes, listaTipoMaterial, TAM_PEDIDOS, TAM_CLIENTES, TAM_RECOLECCION, TAM_TIPO_MATERIAL)==0){
					printf("\nResiduos procesados correctamente.\n");
				}
			   break;
			case 6:
				if(MostrarListaClientesPedidos(listaClientes, listaPedidos, listaLocalidad, TAM_CLIENTES, TAM_PEDIDOS, TAM_LISTA_LOCALIDAD) == -1){
					printf("\nLa lista esta vacia");
				}
				break;
			case 7:
				if(MostrarPedidosPendientes(listaClientes, listaPedidos, TAM_CLIENTES, TAM_PEDIDOS) == -1){
					printf("\nNo hay pedidos pendientes");
				}
				break;
			case 8:
				if(MostrarPedidosCompletados(listaClientes, listaPedidos, listaRecoleccion, TAM_CLIENTES, TAM_PEDIDOS, TAM_TIPO_MATERIAL) == -1){
					printf("\nNo hay pedidos completados\n");
				}
				break;
			case 9:
				if(ObtenerCantidadDePedidosPorLocalidad(listaPedidos, listaClientes, listaLocalidad, TAM_PEDIDOS, TAM_CLIENTES, TAM_LISTA_LOCALIDAD) ==-1){
					printf("\nNo hay pedidos para la localidad ingresada\n");
				}
				break;
			case 10:
				if(ObtenerKgPropilenoPromedioPorCliente(listaRecoleccion, listaClientes, TAM_RECOLECCION, TAM_CLIENTES) == -1){
					printf("\nOcurrio un error buscando el promedio de polipropileno por cliente.\n");
				}
				break;
			case 11:
				if(MostrarClienteConMasPedidosPendientes(listaClientes, listaPedidos, listaLocalidad, TAM_CLIENTES, TAM_PEDIDOS, TAM_LISTA_LOCALIDAD) == -1){
					printf("\nOcurrio un error en cliente con pedidos pendientes\n");
				}
				break;
			case 12:
				if(MostrarClienteConMasPedidosCompletados(listaClientes, listaPedidos, listaLocalidad, TAM_CLIENTES, TAM_PEDIDOS, TAM_LISTA_LOCALIDAD) == -1){
					printf("\nOcurrio un error en cliente con pedidos completados\n");
				}
				break;
			case 13:
				if(MostrarClienteConMasPedidosEnTotal(listaClientes, listaPedidos, listaLocalidad, TAM_CLIENTES, TAM_PEDIDOS, TAM_LISTA_LOCALIDAD) == -1){
					printf("\nOcurrio un error en cliente con pedidos en total\n");
				}
				break;
			case 14:
				printf("\nGracias!\n");
				break;
			default:
				printf("\nPor favor ingrese una opcion valida");
				break;
		}
	}while(opcion!=14);

	return EXIT_SUCCESS;
}
