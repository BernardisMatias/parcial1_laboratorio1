#include "cliente.h"
#include "funciones.h"

void CargarDatosHardcodedCliente(eCliente listaClientes[], int tam){
	int index;
	eCliente item = {100096, "GRUPO ARCOR SOCIEDAD ANONIMA", "30-70700639-7", "Maipu 1210", {"Buenos Aires"}, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item;
	eCliente item2 = {100097, "MERCADO LIBRE LTDA", "30-70988914-8", "Arias 3751", {"Buenos Aires"}, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item2;
	eCliente item3 = {100098, "TOYOTA ARGENTINA S A", "33-67913936-9", "Ruta 12 km 81", {"Zarate"}, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item3;
	eCliente item4 = {100099, "GOOGLE ARGENTINA S.R.L.", "33-70958522-9", "Av. Alicia Moreau Justo 350", {"CABA"}, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item4;
	eCliente item5 = {100100, "UNILEVER DE ARGENTINA S A", "30-50109269-6", "Tucuman 1", {"Buenos Aires"}, FULL};
	index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	listaClientes[index] = item5;
}

void inicializarListaClientes(eCliente listaClientes[], int tam){
	for(int i=0;i<tam;i++){
		listaClientes[i].isEmpty = EMPTY;
	}
}

int GetCantidadTotalClientes(eCliente listaClientes[], int tam){
	int acum = 0;
	for(int i=0;i<tam;i++){
		if(listaClientes[i].isEmpty == EMPTY){
			acum++;
		}
	}
	return acum;
}

void MostrarCliente(eCliente cliente){
  printf("%10d %33s %15s %28s %23s\n", cliente.id, cliente.razonSocial, cliente.cuit, cliente.direccion, cliente.localidad.descripcion);
}

void MostrarClientePedido(eCliente cliente, int pedidosPendientes){
  printf("%10d %25s %15s %28s %23s %15d\n", cliente.id, cliente.razonSocial, cliente.cuit, cliente.direccion, cliente.localidad.descripcion, pedidosPendientes);
}

eCliente ObtenerClientePorId(eCliente listaClientes[], int tam, int id){
	eCliente aux;
	for(int i=0;i<tam;i++){
        if(listaClientes[i].isEmpty == FULL && listaClientes[i].id == id){
            return aux = listaClientes[i];
        }
    }
	return aux;
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

/*
int AltaCliente(eCliente listaClientes[], int tam, int* id){
	int result = -2;
	int index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	if(index == -1){
		return index;
	}
	do{
		if(GetString(listaClientes[index].razonSocial, "Ingrese Razon Social: ", "Error. Razon social invalida, por favor reingrese.", TAM_RAZON_SOCIAL, MAX_INTENTOS) == -1){
			break;
		}
		fflush(stdin);
		if(GetCuit(listaClientes[index].cuit, "Ingrese Cuit (sin guiones): ", MAX_INTENTOS) == -1){
			break;
		}
		fflush(stdin);
		if(GetString(listaClientes[index].direccion, "Ingrese Direccion: ", "Error. Direccion invalida, por favor reingrese.", TAM_DIRECCION, MAX_INTENTOS) == -1){
			break;
		}
		fflush(stdin);
		if(GetString(listaClientes[index].localidad, "Ingrese Localidad: ", "Error. Localidad invalida, por favor reingrese.", TAM_LOCALIDAD, MAX_INTENTOS) == -1){
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
}*/


int AltaCliente(eCliente listaClientes[], int tam, int* id){
	int result = -2;
	int index = ObtenerPrimerEspacioLibreCliente(listaClientes, tam);
	if(index == -1){
		return index;
	}
	do{
		if(GetString(listaClientes[index].razonSocial, "Ingrese Razon Social: ", "Error. Razon social invalida, por favor reingrese.", TAM_RAZON_SOCIAL, MAX_INTENTOS) == -1){
			break;
		}
		fflush(stdin);
		if(GetCuit(listaClientes[index].cuit, "Ingrese Cuit (sin guiones): ", MAX_INTENTOS) == -1){
			break;
		}
		fflush(stdin);
		if(GetString(listaClientes[index].direccion, "Ingrese Direccion: ", "Error. Direccion invalida, por favor reingrese.", TAM_DIRECCION, MAX_INTENTOS) == -1){
			break;
		}
		fflush(stdin);
		if(GetString(listaClientes[index].localidad.descripcion, "Ingrese Localidad: ", "Error. Localidad invalida, por favor reingrese.", TAM_DE_LOCALIDAD , MAX_INTENTOS) == -1){
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

int GetPosicionPorId(eCliente listaClientes[], int tam, int id){
	int posicion = -1;
	for(int i=0;i<tam;i++){
		if(listaClientes[i].isEmpty == FULL && listaClientes[i].id == id){
			posicion = i;
			break;
		}
	}
	return posicion;
}

int MostrarListaClientes(eCliente listaClientes[], int tam){
    int retorno = -1;
    printf("\tID\t\t\tRazon Social\t\tCUIT\t\t\tDireccion\t\tLocalidad\n");
    for (int i = 0; i < tam; i++){
      if (listaClientes[i].isEmpty == FULL){
    	  MostrarCliente(listaClientes[i]);
	      retorno = 0;
	  }
    }
    return retorno;
}

/*
int ModificarCliente(eCliente listaClientes[], int tam){
	int idCliente, opcion, posAux;
	int retorno = -1;
	int muestraListaClientes = MostrarListaClientes(listaClientes, tam);
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
			if(GetString(listaClientes[posAux].localidad, "Ingrese Nueva Localidad: ", "Error. Localidad invalida, por favor reingrese.", TAM_DIRECCION, MAX_INTENTOS) == 0){
				retorno = 0;
			}
		} else if(opcion == 2){
			if(GetString(listaClientes[posAux].direccion, "Ingrese Nueva Direccion: ", "Error. Direccion invalida, por favor reingrese.", TAM_DIRECCION, MAX_INTENTOS) == 0){
				retorno = 0;
			}
		}
     } else if(posAux == -1){
    	 printf("\nError. Cliente inexistente.");
     } else{
		 printf("\nLa lista de clientes esta vacia.");
	 }
	 return retorno;
}*/

//CON LOCALIDAD
int ModificarCliente(eCliente listaClientes[], int tam){
	int idCliente, opcion, posAux;
	int retorno = -1;
	int muestraListaClientes = MostrarListaClientes(listaClientes, tam);
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
			if(GetString(listaClientes[posAux].localidad.descripcion, "Ingrese Nueva Localidad: ", "Error. Localidad invalida, por favor reingrese.", TAM_DIRECCION, MAX_INTENTOS) == 0){
				retorno = 0;
			}
		} else if(opcion == 2){
			if(GetString(listaClientes[posAux].direccion, "Ingrese Nueva Direccion: ", "Error. Direccion invalida, por favor reingrese.", TAM_DIRECCION, MAX_INTENTOS) == 0){
				retorno = 0;
			}
		}
     } else if(posAux == -1){
    	 printf("\nError. Cliente inexistente.");
     } else{
		 printf("\nLa lista de clientes esta vacia.");
	 }
	 return retorno;
}

int BorrarCliente(eCliente listaClientes[], int tam){
   int idCliente, opcion;
   int result = 0;
   if(MostrarListaClientes(listaClientes, tam) == 0){
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

