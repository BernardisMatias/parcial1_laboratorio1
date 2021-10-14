#include "evento.h"


void CargarDatosHardcoded(ePedido listaPedidos[], eCliente listaClientes[], eRecoleccion listaRecoleccion[], eTipoMaterial listaTipoMaterial[], int tamClientes, int tamPedidos, int tamRecoleccion, int tamTipoMaterial){
	CargarDatosHardcodedPedido(listaPedidos, tamPedidos);
	CargarDatosHardcodedCliente(listaClientes, tamClientes);
	CargarDatosHardcodedRecoleccion(listaRecoleccion, tamRecoleccion);
	CargarDatosHardcodedTipoMaterial(listaTipoMaterial, tamTipoMaterial);
}

int CrearPedido(ePedido listaPedidos[], eCliente listaClientes[], int tamPedido, int tamClientes, int* id){
	int result = -2;
	int index = ObtenerPrimerEspacioLibrePedidos(listaPedidos, tamPedido);
	if(index == -1){
		return index;
	}
	do{
		if(MostrarListaClientes(listaClientes, tamClientes) == 0){
			if(GetEntero(&listaPedidos[index].idCliente, "Ingrese ID de Cliente: ", CLIENTE_INIT_ID, MAX_ID_VALUE, MAX_INTENTOS) == -1){
				break;
			}
			if(GetPosicionPorId(listaClientes, tamClientes, listaPedidos[index].idCliente) == -1){
				printf("\nCliente inexistente.\n");
				break;
			}
			if(GetFlotante(&listaPedidos[index].kilosTotales, "Ingrese cantidad total de kilos a reciclar: ", MIN_KILOS, MAX_KILOS, MAX_INTENTOS) == -1){
				break;
			}
			listaPedidos[index].id = AutoIncrementarId(id);
			listaPedidos[index].isEmpty = FULL;
			listaPedidos[index].cantRecoleccion = 0;
			strcpy(listaPedidos[index].estado, "PENDIENTE");
			result = 0;
		} else{
			printf("\nNo se pudo crear PEDIDO. La lista de CLIENTES esta vacia.");
			break;
		}
	} while(result != 0);
	return result;
}

int ProcesarResiduos(eRecoleccion listaRecoleccion[], ePedido listaPedidos[], eCliente listaClientes[], eTipoMaterial listaTipoMaterial[], int tamPedido, int tamClientes, int tamRecoleccion, int tamMateriales){
	int idCliente;
	int idRecoleccion = RECOLECCION_INIT_ID;
	ePedido auxPedido;
	if(MostrarListaPedidos(listaPedidos, tamPedido) == 0){
		if(GetEntero(&idCliente,"Ingrese ID del Cliente a procesar: ", CLIENTE_INIT_ID, MAX_ID_VALUE, 5) == 0){
			auxPedido = ObtenerPedidoPorIdCliente(listaPedidos, tamPedido, idCliente);
			if(InicioProcesarResiduos(listaPedidos, listaRecoleccion, auxPedido, listaTipoMaterial, tamRecoleccion, tamMateriales, tamPedido, &idRecoleccion) == -1){
				printf("\nError creando recoleccion\n");
			}
		} else{
			printf("\nError. ID Cliente inexistente.");
		}
	} else{
		printf("\nLa lista de pedidos esta vacia.");
	}
	return 0;
}

int InicioProcesarResiduos(ePedido listaPedidos[], eRecoleccion listaRecoleccion[], ePedido pedido, eTipoMaterial listaTipoMaterial[], int tamRecoleccion, int tamMateriales, int tamPedidos, int* idRecoleccion){
	int idTipoMaterialAux, opcion, i=0, result = -1;
	float kgIngresadosAux, kgRestantes, kgAcum = 0;
	eRecoleccion item;
	do{
		MostrarTiposMateriales(listaTipoMaterial, tamMateriales);
		if(i == 0){
			kgRestantes = pedido.kilosTotales;
		}
		if(GetEntero(&idTipoMaterialAux,"\nIngrese tipo de material reciclado: ", 1, 3, 5) == -1){
			break;
		}
		if(GetFlotante(&kgIngresadosAux,"\nIngrese Kilos reciclados: ", 1, kgRestantes, 5) == -1){
			break;
		}
		kgAcum += kgIngresadosAux;
		kgRestantes = pedido.kilosTotales - kgAcum;
		if(kgAcum < pedido.kilosTotales){
			printf("\nQuedan %.2f kilos. Si no fueron reciclados, seran descartados.", kgRestantes);
			printf("\nDesea ingresar otro reciclaje?");
			printf("\n1. Seguir ingresando");
			printf("\n2. Finalizar\n");
			if(GetEntero(&opcion,"Opcion: ", 1, 2, 3) == -1){
				break;
			}
		}
		item = CrearRecoleccion(idRecoleccion, idTipoMaterialAux, kgIngresadosAux);
		if(GuardarRecoleccionEnPrimerEspacioLibre(listaRecoleccion, tamRecoleccion, item) == -1){
			printf("\nError al guardar recoleccion.");
			break;
		}
		pedido.idRecoleccion[i] = item.id;
		i++;
		if(kgAcum == pedido.kilosTotales || opcion == 2){
			result = 0;
			pedido.cantRecoleccion = i;
			strcpy(pedido.estado, "COMPLETADO");
			GuardarPedidoPostRecoleccion(listaPedidos, tamPedidos, pedido);
		}
	} while(result != 0);
	return result;
}

eRecoleccion CrearRecoleccion(int* idIncremental, int idTipo, float cantKilos){
	eRecoleccion aux;
	aux.id = AutoIncrementarId(idIncremental);
	aux.idTipoMaterial = idTipo;
	aux.cantidadKilos = cantKilos;
	aux.isEmpty = FULL;
	return aux;
}

int GetIdPedidoPorIdCliente(ePedido listaPedidos[], int tamCliente, int idCliente){
	int idClienteAux;
	for(int i=0;i<tamCliente;i++){
		if(listaPedidos[i].isEmpty == FULL && listaPedidos[i].idCliente == idCliente){
			idClienteAux = idCliente;
			break;
		}
	}
	return idClienteAux;
}

int MostrarListaClientesPedidos(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos){
    int result = -1, contador = 0;
    printf("\tID\t\tRazon Social\t\tCUIT\t\t\tDireccion\t\tLocalidad\tCant. pedidos 'PENDIENTE'\n");
    for(int i = 0; i < tamClientes; i++){
    	if(listaClientes[i].isEmpty == FULL){
			for(int j=0;j<tamPedidos;j++){
				if(listaPedidos[j].isEmpty == FULL
						&& listaPedidos[j].idCliente == listaClientes[i].id
							&& strcmp(listaPedidos[j].estado, "PENDIENTE") == 0){
					contador++;
				}
			}
			MostrarClientePedido(listaClientes[i], contador);
			result = 0;
    	}
    	contador = 0;
    }
    return result;
}

int MostrarClienteConMasPedidosPendientes(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos){
	int result = -1;
	int flag = 0;
	int maximo = 0;
	int actual = 0;
	eCliente clienteActual;
	for(int j=0;j<tamPedidos;j++){
		if(listaPedidos[j].isEmpty == FULL
				&& strcmp(listaPedidos[j].estado, "PENDIENTE") == 0){
			actual = CantidadPedidosPendientesPorCliente(listaPedidos, tamPedidos, listaPedidos[j].idCliente);
		}
		if(flag == 0 || actual > maximo){
			maximo = actual;
			clienteActual = ObtenerClientePorId(listaClientes, tamClientes, listaPedidos[j].idCliente);
			result = 0;
		}
	}
	if(maximo != 0){
		printf("\nCliente con mas pedidos pendientes: \n");
		MostrarCliente(clienteActual);
	}
    return result;
}

int MostrarClienteConMasPedidosCompletados(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos){
	int result = -1;
	int flag = 0;
	int maximo = 0;
	int actual = 0;
	eCliente clienteActual;
	for(int j=0;j<tamPedidos;j++){
		if(listaPedidos[j].isEmpty == FULL
				&& strcmp(listaPedidos[j].estado, "COMPLETADO") == 0){
			actual = CantidadPedidosPendientesPorCliente(listaPedidos, tamPedidos, listaPedidos[j].idCliente);
		}
		if(flag == 0 || actual > maximo){
			maximo = actual;
			clienteActual = ObtenerClientePorId(listaClientes, tamClientes, listaPedidos[j].idCliente);
			result = 0;
		}
	}
	if(maximo != 0){
		printf("\nCliente con mas pedidos completados: \n");
		MostrarCliente(clienteActual);
	}
    return result;
}

int MostrarClienteConMasPedidosEnTotal(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos){
	int result = -1;
	int flag = 0;
	int maximo = 0;
	int actual = 0;
	eCliente clienteActual;
	for(int j=0;j<tamPedidos;j++){
		if(listaPedidos[j].isEmpty == FULL){
			actual = CantidadPedidosPendientesPorCliente(listaPedidos, tamPedidos, listaPedidos[j].idCliente);
		}
		if(flag == 0 || actual > maximo){
			maximo = actual;
			clienteActual = ObtenerClientePorId(listaClientes, tamClientes, listaPedidos[j].idCliente);
			result = 0;
		}
	}
	if(maximo != 0){
		printf("\nCliente con mas pedidos en total: \n");
		MostrarCliente(clienteActual);
	}
    return result;
}

int CantidadPedidosPendientesPorCliente(ePedido listaPedidos[], int tamPedidos, int idCliente){
	int result = 0;
	for(int i=0;i<tamPedidos;i++){
		if(listaPedidos[i].idCliente == idCliente
				&& strcmp(listaPedidos[i].estado, "PENDIENTE") == 0){
			result++;
		}
	}
	return result;
}

int MostrarPedidosPendientes(eCliente listaClientes[], ePedido listaPedidos[], int tamClientes, int tamPedidos){
    int result = -1;
    printf("\tCUIT\t\t\tDireccion\t\tCant. Kg a recolectar\n");
    for(int i=0;i<tamPedidos;i++){
    	if(listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado, "PENDIENTE") == 0){
    		eCliente aux = ObtenerClientePorId(listaClientes, tamClientes, listaPedidos[i].idCliente);
    		MostrarPedidoPendiente(aux.cuit, aux.direccion, listaPedidos[i].kilosTotales);
    		result = 0;
    	}
    }
    return result;
}

int MostrarPedidosCompletados(eCliente listaClientes[], ePedido listaPedidos[], eRecoleccion listaRecoleccion[], int tamClientes, int tamPedidos, int tamRecoleccion){
    int result = -1;
    float hdpe = 0, ldpe = 0, pp = 0;
    printf("\tCUIT\t\t\tDireccion\tCant. kg: HDPE\t\t\tLDPE\t\t\tPP\n");
    for(int i=0;i<tamPedidos;i++){
		if(listaPedidos[i].isEmpty == FULL && strcmp(listaPedidos[i].estado, "COMPLETADO") == 0){
			hdpe = ObtenerHdpeTotalPorPedido(listaRecoleccion, tamRecoleccion, listaPedidos[i]);
			ldpe = ObtenerLdpeTotalPorPedido(listaRecoleccion, tamRecoleccion, listaPedidos[i]);
			pp = ObtenerPpTotalPorPedido(listaRecoleccion, tamRecoleccion, listaPedidos[i]);
			eCliente aux = ObtenerClientePorId(listaClientes, tamClientes, listaPedidos[i].idCliente);
			MostrarPedidoCompletado(aux.cuit, aux.direccion, hdpe, ldpe, pp);
			result = 0;
			hdpe = 0;
			ldpe = 0;
			pp = 0;
		}
	}
    return result;
}

float ObtenerHdpeTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item){
	float result = 0;
	for(int i=0;i<tamRecoleccion;i++){
		if(listaRecoleccion[i].isEmpty == FULL && listaRecoleccion[i].idTipoMaterial == 1){
			for(int j=0;j<item.cantRecoleccion;j++){
				if(item.idRecoleccion[j] == listaRecoleccion[i].id){
					result += listaRecoleccion[i].cantidadKilos;
				}
			}
		}
	}
	return result;
}
float ObtenerLdpeTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item){
	float result = 0;
	for(int i=0;i<tamRecoleccion;i++){
		if(listaRecoleccion[i].isEmpty == FULL && listaRecoleccion[i].idTipoMaterial == 2){
			for(int j=0;j<item.cantRecoleccion;j++){
				if(item.idRecoleccion[j] == listaRecoleccion[i].id){
					result += listaRecoleccion[i].cantidadKilos;
				}
			}
		}
	}
	return result;
}
float ObtenerPpTotalPorPedido(eRecoleccion listaRecoleccion[], int tamRecoleccion, ePedido item){
	float result = 0;
	for(int i=0;i<tamRecoleccion;i++){
		if(listaRecoleccion[i].isEmpty == FULL && listaRecoleccion[i].idTipoMaterial == 3){
			for(int j=0;j<item.cantRecoleccion;j++){
				if(item.idRecoleccion[j] == listaRecoleccion[i].id){
					result += listaRecoleccion[i].cantidadKilos;
				}
			}
		}
	}
	return result;
}
float ObtenerTotalCantidadKgPp(eRecoleccion listaRecoleccion[], int tamRecoleccion){
	float result = 0;
	for(int i=0;i<tamRecoleccion;i++){
		if(listaRecoleccion[i].isEmpty == FULL && listaRecoleccion[i].idTipoMaterial == 3){
			result += listaRecoleccion[i].cantidadKilos;
		}
	}
	return result;
}

int ObtenerCantidadDePedidosPorLocalidad(ePedido listaPedidos[], eCliente listaClientes[], int tamPedidos, int tamClientes){
	int result = -1, acum = 0;
	char localidadAux[TAM_LOCALIDAD];
	char localidadEnLista[TAM_LOCALIDAD];
	if(GetString(localidadAux, "\nIngrese localidad: ", "Error. Localidad invalida", TAM_LOCALIDAD, 5) == -1){
		return result;
	}
	printf("\n\tLocalidad\t\t\tCant. pedidos\n");
	for(int i=0;i<tamClientes;i++){
		if(stricmp(listaClientes[i].localidad.descripcion, localidadAux) == 0){
			for(int j=0;j<tamPedidos;j++){
				if(listaPedidos[j].idCliente == listaClientes[i].id
						&& strcmp(listaPedidos[j].estado, "PENDIENTE") == 0){
					result = 0;
					acum++;
				}
			}
			strcpy(localidadEnLista, listaClientes[i].localidad.descripcion);
		}
	}
	if(acum != 0){
		printf("\t%s\t\t\t%d\n\n", localidadEnLista, acum);
	}
	return result;
}

int ObtenerKgPropilenoPromedioPorCliente(eRecoleccion listaRecoleccion[], eCliente listaClientes[], int tamRecoleccion, int tamClientes){
	int totalClientes = 0;
	float totalPp = 0, result = -1, promedio = 0;
	totalClientes = GetCantidadTotalClientes(listaClientes, tamClientes);
	totalPp = ObtenerTotalCantidadKgPp(listaRecoleccion, tamRecoleccion);
	if(totalClientes != 0 && totalPp != 0){
		result = 0;
		promedio = totalPp/totalClientes;
		printf("\nCantidad de Kg. de Polipropileno por cliente: %.2f", promedio);
	}
	return result;
}

