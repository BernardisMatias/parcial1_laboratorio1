#include "recoleccion.h"

void CargarDatosHardcodedRecoleccion(eRecoleccion listaRecoleccion[], int tam){
	/*int index;
	eRecoleccion item = {300001, 1, 200, FULL};
	index = ObtenerPrimerEspacioLibreRecoleccion(listaRecoleccion, tam);
	listaRecoleccion[index] = item;
	eRecoleccion item2 = {300002, 2, 250, FULL};
	index = ObtenerPrimerEspacioLibreRecoleccion(listaRecoleccion, tam);
	listaRecoleccion[index] = item2;*/
}

void inicializarListaRecoleccion(eRecoleccion listaRecoleccion[], int tam){
	for(int i=0;i<tam;i++){
		listaRecoleccion[i].isEmpty = EMPTY;
	}
}

int ObtenerPrimerEspacioLibreRecoleccion(eRecoleccion listaRecoleccion[], int tam){
	int lugarLibre = -1;
	for(int i=0;i<tam;i++){
        if(listaRecoleccion[i].isEmpty == EMPTY){
            lugarLibre = i;
            break;
        }
    }
	return lugarLibre;
}

void MostrarRecoleccion(eRecoleccion item){
  printf("%10d %25d %15f\n", item.id, item.idTipoMaterial, item.cantidadKilos);
}

void MostrarListaRecoleccion(eRecoleccion listaRecoleccion[], int tam){
	for(int i=0;i<tam;i++){
		if(listaRecoleccion[i].isEmpty == FULL){
			MostrarRecoleccion(listaRecoleccion[i]);
		}
	}
}

int GuardarRecoleccionEnPrimerEspacioLibre(eRecoleccion listaRecoleccion[], int tam, eRecoleccion item){
	int result = -1;
	int index = ObtenerPrimerEspacioLibreRecoleccion(listaRecoleccion, tam);
	if(index == -1){
		printf("\nNo hay espacio libre para guardar recoleccion");
		return result;
	}
	listaRecoleccion[index] = item;
	listaRecoleccion[index].isEmpty = FULL;
	result = 0;
	return result;
}

eRecoleccion ObtenerRecoleccionPorId(eRecoleccion listaRecoleccion[], int tam, int idRecoleccion){
	eRecoleccion aux;
	for(int i=0;i<tam;i++){
		if(listaRecoleccion[i].isEmpty == FULL && listaRecoleccion[i].id == idRecoleccion){
			aux = listaRecoleccion[i];
			break;
		}
	}
	return aux;
}
