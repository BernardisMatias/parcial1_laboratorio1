#include "evento.h"

void CargarDatosHardcoded(ePedido listaPedidos[], eCliente listaClientes[], eRecoleccion listaRecoleccion[], eTipoMaterial listaTipoMaterial[], eLocalidad listaLocalidades[], int tamClientes, int tamPedidos, int tamRecoleccion, int tamTipoMaterial, int tamLocalidades){
	CargarDatosHardcodedPedido(listaPedidos, tamPedidos);
	CargarDatosHardcodedCliente(listaClientes, tamClientes);
	CargarDatosHardcodedRecoleccion(listaRecoleccion, tamRecoleccion);
	CargarDatosHardcodedTipoMaterial(listaTipoMaterial, tamTipoMaterial);
	CargarDatosHardcodedLocalidad(listaLocalidades, tamLocalidades);
}

int CrearPedido(ePedido listaPedidos[], eCliente listaClientes[], eLocalidad listaLocalidades[], int tamPedido, int tamClientes, int tamLocalidades, int* id){
	int result = -2;
	int index = ObtenerPrimerEspacioLibrePedidos(listaPedidos, tamPedido);
	if(index == -1){
		return index;
	}
	do{
		if(MostrarListaClientes(listaClientes, listaLocalidades, tamClientes, tamLocalidades) == 0){
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
	float kgIngresadosAux, kgRestantes = 0, kgAcum = 0;
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

int MostrarListaClientesPedidos(eCliente listaClientes[], ePedido listaPedidos[], eLocalidad listaLocalidad[], int tamClientes, int tamPedidos, int tamLocalidad){
    int result = -1, contador = 0;
    char localidadAux[150];
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
			DescripcionLocalidadPorId(localidadAux, listaLocalidad, tamLocalidad, listaClientes[i].idLocalidad);
			MostrarClientePedido(listaClientes[i], localidadAux, contador);
			result = 0;
    	}
    	contador = 0;
    }
    return result;
}

int MostrarClienteConMasPedidosPendientes(eCliente listaClientes[], ePedido listaPedidos[], eLocalidad listaLocalidad[], int tamClientes, int tamPedidos, int tamLocalidad){
	int result = -1;
	int flag = 0;
	int maximo = 0;
	int actual = 0;
	eCliente clienteActual;
	char localidadAux[150];
	for(int j=0;j<tamPedidos;j++){
		if(listaPedidos[j].isEmpty == FULL && strcmp(listaPedidos[j].estado, "PENDIENTE") == 0){
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
		DescripcionLocalidadPorId(localidadAux, listaLocalidad, tamLocalidad, clienteActual.idLocalidad);
		MostrarCliente(clienteActual, localidadAux);
	}
    return result;
}

int MostrarClienteConMasPedidosCompletados(eCliente listaClientes[], ePedido listaPedidos[], eLocalidad listaLocalidad[], int tamClientes, int tamPedidos, int tamLocalidad){
	int result = -1;
	int flag = 0;
	int maximo = 0;
	int actual = 0;
	char localidadAux[150];
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
		DescripcionLocalidadPorId(localidadAux, listaLocalidad, tamLocalidad, clienteActual.idLocalidad);
		MostrarCliente(clienteActual, localidadAux);
	}
    return result;
}

int MostrarClienteConMasPedidosEnTotal(eCliente listaClientes[], ePedido listaPedidos[], eLocalidad listaLocalidad[], int tamClientes, int tamPedidos, int tamLocalidad){
	int result = -1;
	int flag = 0;
	int maximo = 0;
	int actual = 0;
	char localidadAux[150];
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
		DescripcionLocalidadPorId(localidadAux, listaLocalidad, tamLocalidad, clienteActual.idLocalidad);
		MostrarCliente(clienteActual, localidadAux);
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

int ObtenerCantidadDePedidosPorLocalidad(ePedido listaPedidos[], eCliente listaClientes[], eLocalidad listaLocalidades[], int tamPedidos, int tamClientes, int tamLocalidad){
	int result = -1, acum = 0;
	int idLocalidadAux;
	char localidadEnLista[TAM_DE_LOCALIDAD];

	if(MostrarListaLocalidades(listaLocalidades, tamLocalidad) == -1){
		printf("\nError, no hay localidades cargadas en el sistema");
		return result;
	}
	if(GetEntero(&idLocalidadAux, "Ingrese una localidad (ID): ", ID_LOCALIDAD_MIN, ID_LOCALIDAD_MAX, 5) == -1){
		return result;
	}
	printf("\n\tLocalidad\t\t\tCant. pedidos\n");
	for(int i=0;i<tamClientes;i++){
		if(idLocalidadAux == listaClientes[i].idLocalidad){
			for(int j=0;j<tamPedidos;j++){
				if(listaPedidos[j].idCliente == listaClientes[i].id
						&& strcmp(listaPedidos[j].estado, "PENDIENTE") == 0){
					result = 0;
					acum++;
				}
			}
			DescripcionLocalidadPorId(localidadEnLista, listaLocalidades, tamLocalidad, idLocalidadAux);
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

int MostrarListaClientes(eCliente listaClientes[], eLocalidad listaLocalidad[], int tam, int tamLocalidad){
    int retorno = -1;
    printf("\tID\t\t\tRazon Social\t\tCUIT\t\t\tDireccion\t\tLocalidad\n");
    char localidad[TAM_DE_LOCALIDAD];
    for (int i = 0; i < tam; i++){
      if (listaClientes[i].isEmpty == FULL){
    	  DescripcionLocalidadPorId(localidad, listaLocalidad, tam, listaClientes[i].idLocalidad);
    	  MostrarCliente(listaClientes[i], localidad);
	      retorno = 0;
	  }
    }
    return retorno;
}

int ObtenerPrimerEspacioLibreCliente(eCliente listaClientes[], int tam){
	int lugarLibre = -1;
	for(int i=0;i<tam;i++){
        if(listaClientes[i].isEmpty == EMPTY){
            lugarLibre = i;
            break;
        }
    }
	return lugarLibre;
}

void CargarDatosHardcodedCliente(eCliente listaClientes[], int tam){
	int index;
	eCliente item = {100096, "GRUPO ARCOR SOCIEDAD ANONIMA", "30-70700639-7", "Maipu 1210", 20, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item;
	eCliente item2 = {100097, "MERCADO LIBRE LTDA", "30-70988914-8", "Arias 3751", 20, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item2;
	eCliente item3 = {100098, "TOYOTA ARGENTINA S A", "33-67913936-9", "Ruta 12 km 81", 50, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item3;
	eCliente item4 = {100099, "GOOGLE ARGENTINA S.R.L.", "33-70958522-9", "Av. Alicia Moreau Justo 350", 70, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item4;
	eCliente item5 = {100100, "UNILEVER DE ARGENTINA S A", "30-50109269-6", "Tucuman 1", 80, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item5;
}

int ModificarCliente(eCliente listaClientes[], eLocalidad listaLocalidades[], int tam, int tamLocalidades){
	int idCliente, opcion, posAux;
	int retorno = -1;
	int muestraListaClientes = MostrarListaClientes(listaClientes, listaLocalidades, tam, tamLocalidades);
	if(GetEntero(&idCliente,"Ingrese ID del cliente a modificar: ", CLIENTE_INIT_ID, MAX_ID_VALUE, 5) == -1){
		return retorno;
	}
	posAux = GetPosicionPorId(listaClientes, tam, idCliente);
	if(posAux == -1){
		printf("\nCliente inexistente.");
		return retorno;
	}
	if(muestraListaClientes == 0){
		setbuf(stdout, NULL);
		printf("\nSe pueden modificar:");
		printf("\n1. Modificar localidad");
		printf("\n2. Modificar direccion");
		printf("\n3. Cancelar");
		fflush(stdin);
		GetEntero(&opcion, "\nElija una opcion: ", 1, 3, 5);
		if(opcion == 1){
			if(MostrarListaLocalidades(listaLocalidades, tamLocalidades) == -1){
				printf("\nError, no hay localidades cargadas en el sistema");
				return retorno;
			}
			if(GetEntero(&listaClientes[posAux].idLocalidad, "Ingrese una localidad (ID): ", ID_LOCALIDAD_MIN, ID_LOCALIDAD_MAX, 5) == -1){
				return retorno;
			}
			retorno = 0;
		} else if(opcion == 2){
			if(GetString(listaClientes[posAux].direccion, "Ingrese Nueva Direccion: ", "Error. Direccion invalida, por favor reingrese.", TAM_DIRECCION, MAX_INTENTOS) == -1){
				return retorno;
			}
			retorno = 0;
		}
     } else if(posAux == -1){
    	 printf("\nError. Cliente inexistente.");
     } else{
		 printf("\nLa lista de clientes esta vacia.");
	 }
	 return retorno;
}

int BorrarCliente(eCliente listaClientes[], eLocalidad listaLocalidades[], int tam, int tamLocalidades){
   int idCliente, opcion;
   int result = 0;
   if(MostrarListaClientes(listaClientes, listaLocalidades, tam, tamLocalidades) == 0){
	   fflush(stdin);
	  if(GetEntero(&idCliente,"Ingrese ID del cliente a borrar: ", CLIENTE_INIT_ID, MAX_ID_VALUE, 5) == 0){
		  int posAux = GetPosicionPorId(listaClientes, tam, idCliente);
		  if(posAux != -1){
			  printf("\nEsta seguro de que quiere borrar al cliente?");
			  printf("\n1. Eliminar cliente");
			  printf("\n2. Cancelar");
			  fflush(stdin);
			  GetEntero(&opcion, "\nElija una opcion: ", 1, 2, 5);
			  if(opcion == 1){
				   listaClientes[posAux].isEmpty = EMPTY;
				   result = 1;
			  }
		  } else {
			  printf("\nError. Cliente inexistente.");
		  }
	  } else{
		  printf("\nError. Cliente inexistente.");
	  }
   } else{
	  printf("\nLa lista de clientes esta vacia.");
   }
   return result;
}

int AltaCliente(eCliente listaClientes[], eLocalidad listaLocalidades[], int tam, int tamLocalidades, int* id){
	int result = -2;
	int index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	if(index == -1){
		return index;
	}
	do {
		if(GetString(listaClientes[index].razonSocial, "Ingrese Razon Social: ", "Error. Razon social invalida, por favor reingrese.", TAM_RAZON_SOCIAL, MAX_INTENTOS) == -1){
			break;
		}
		fflush(stdin);
		if(GetCuit(listaClientes[index].cuit, "Ingrese Cuit (sin guiones): ", MAX_INTENTOS) == -1){
			break;
		}
		fflush(stdin);
		if(MostrarListaLocalidades(listaLocalidades, tamLocalidades) == -1){
			printf("\nError, no hay localidades cargadas en el sistema");
			break;
		}
		if(GetEntero(&listaClientes[index].idLocalidad, "Ingrese una localidad (ID): ", ID_LOCALIDAD_MIN, ID_LOCALIDAD_MAX, 5) == -1){
			break;
		}
		fflush(stdin);
		if(GetString(listaClientes[index].direccion, "Ingrese Direccion: ", "Error. Direccion invalida, por favor reingrese.", TAM_DIRECCION, MAX_INTENTOS) == -1){
			break;
		}
		result = 0;
	} while(result != 0);


	if(result == 0){
		listaClientes[index].id = AutoIncrementarId(id);
		listaClientes[index].isEmpty = FULL;
	} else{
		listaClientes[index].isEmpty = EMPTY;
	}
	return result;
}

