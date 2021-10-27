#include "localidad.h"

void CargarDatosHardcodedLocalidad(eLocalidad listaLocalidad[], int tam){
	int index;
	eLocalidad item = {20, "Buenos Aires", FULL};
	index = ObtenerPrimerEspacioLibreLocalidad(listaLocalidad, tam);
	listaLocalidad[index] = item;
	eLocalidad item2 = {50, "Avellaneda", FULL};
	index = ObtenerPrimerEspacioLibreLocalidad(listaLocalidad, tam);
	listaLocalidad[index] = item2;
	eLocalidad item3 = {70, "CABA", FULL};
	index = ObtenerPrimerEspacioLibreLocalidad(listaLocalidad, tam);
	listaLocalidad[index] = item3;
	eLocalidad item4 = {80, "Quilmes", FULL};
	index = ObtenerPrimerEspacioLibreLocalidad(listaLocalidad, tam);
	listaLocalidad[index] = item4;
	eLocalidad item5 = {10, "Vicente Lopez", FULL};
	index = ObtenerPrimerEspacioLibreLocalidad(listaLocalidad, tam);
	listaLocalidad[index] = item5;
}

int MostrarListaLocalidades(eLocalidad listaLocalidad[], int tam){
    int retorno = -1;
    printf("\n\tID\t\tDescripcion\n");
    for(int i = 0; i < tam; i++){
      if(listaLocalidad[i].isEmpty == FULL){
    	  MostrarLocalidad(listaLocalidad[i].id, listaLocalidad[i].descripcion);
	      retorno = 0;
	  }
    }
    return retorno;
}

void MostrarLocalidad(int id, char descripcion[]){
  printf("%10d %33s\n", id, descripcion);
}

int DescripcionLocalidadPorId(char descripcionDestino[], eLocalidad listaLocalidad[], int tam, int id){
	int result = -1;
	for(int i = 0; i < tam; i++){
	  if(listaLocalidad[i].isEmpty == FULL
			  && listaLocalidad[i].id == id){
		  strcpy(descripcionDestino, listaLocalidad[i].descripcion);
		  result = 0;
		  break;
	  }
	}
	return result;
}

int ObtenerPrimerEspacioLibreLocalidad(eLocalidad listaLocalidad[], int tam){
	int lugarLibre = -1;
	for(int i=0;i<tam;i++){
        if(listaLocalidad[i].isEmpty == EMPTY){
            lugarLibre = i;
            break;
        }
    }
	return lugarLibre;
}
