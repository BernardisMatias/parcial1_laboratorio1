#include "pedido.h"
#include "tipoMaterial.h"
#include "cliente.h"

void CargarDatosHardcodedPedido(ePedido listaPedidos[], int tam){
	int index;
	ePedido item = {200099, 100100, 500, "PENDIENTE", {}, 0, FULL};
	index = ObtenerPrimerEspacioLibrePedidos(listaPedidos, tam);
	listaPedidos[index] = item;
	ePedido item2 = {200098, 100097, 200, "PENDIENTE", {}, 0, FULL};
	index = ObtenerPrimerEspacioLibrePedidos(listaPedidos, tam);
	listaPedidos[index] = item2;
	ePedido item3 = {200097, 100097, 200, "PENDIENTE", {}, 0, FULL};
	index = ObtenerPrimerEspacioLibrePedidos(listaPedidos, tam);
	listaPedidos[index] = item3;
}

void inicializarListaPedido(ePedido listaPedidos[], int tam){
	for(int i=0;i<tam;i++){
		listaPedidos[i].isEmpty = EMPTY;
	}
}

void MostrarPedidoCompletado(char cuitCliente[], char direccion[], float cantHdpe, float cantLdpe, float cantPp){
  printf("%10s %28s %20.2f %21.2f %21.2f\n", cuitCliente, direccion, cantHdpe, cantLdpe, cantPp);
}

void MostrarPedidoPendiente(char cuitCliente[], char direccion[], float cantKilos){
  printf("%10s %28s %35.2f\n", cuitCliente, direccion, cantKilos);
}

int ObtenerPrimerEspacioLibrePedidos(ePedido listaPedidos[], int tam){
	int lugarLibre = -1;
	for(int i=0;i<tam;i++){
        if(listaPedidos[i].isEmpty == EMPTY){
            lugarLibre = i;
            break;
        }
    }
	return lugarLibre;
}

ePedido ObtenerPedidoPorIdPedido(ePedido listaPedidos[], int tam, int idPedido){
	ePedido aux;
	for(int i=0;i<tam;i++){
		if(listaPedidos[i].isEmpty == FULL && listaPedidos[i].id == idPedido){
			aux = listaPedidos[i];
			break;
		}
	}
	return aux;
}

ePedido ObtenerPedidoPorIdCliente(ePedido listaPedidos[], int tam, int idCliente){
	ePedido aux;
	for(int i=0;i<tam;i++){
		if(listaPedidos[i].isEmpty == FULL && listaPedidos[i].idCliente == idCliente){
			aux = listaPedidos[i];
			break;
		}
	}
	return aux;
}

int CantidadPedidosDeClientePorIdCliente(ePedido listaPedidos[], int tam, int idCliente){
	int cantPedidos = 0;
	for(int i=0;i<tam;i++){
		if(listaPedidos[i].isEmpty == FULL && listaPedidos[i].idCliente == idCliente){
			cantPedidos++;
		}
	}
	return cantPedidos;
}

void MostrarPedido(ePedido pedido){
  printf("%18d %23f %19s\n", pedido.idCliente, pedido.kilosTotales, pedido.estado);
}

int MostrarListaPedidos(ePedido listaPedidos[], int tam){
    int retorno = -1;
    printf("\tID Cliente\t\tKG. Totales\t\tEstado\n");
    for(int i = 0; i < tam; i++){
      if(listaPedidos[i].isEmpty == FULL
    		  && strcmp(listaPedidos[i].estado, "PENDIENTE") == 0){
    	  MostrarPedido(listaPedidos[i]);
	      retorno = 0;
	  }
    }
    return retorno;
}

void GuardarPedidoPostRecoleccion(ePedido listaPedidos[], int tam, ePedido item){
	for(int i=0;i<tam;i++){
		if(listaPedidos[i].id == item.id){
			listaPedidos[i] = item;
			break;
		}
	}
}

int GuardarPedidoEnPrimerEspacioLibre(ePedido listaPedidos[], int tam, ePedido item){
	int result = -1;
	int index = ObtenerPrimerEspacioLibrePedidos(listaPedidos, tam);
	if(index == -1){
		printf("\nNo hay espacio libre para guardar recoleccion");
		return result;
	}
	listaPedidos[index] = item;
	listaPedidos[index].isEmpty = FULL;
	result = 0;
	return result;
}
