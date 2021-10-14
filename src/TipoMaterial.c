#include "tipoMaterial.h"
#include "funciones.h"

void CargarDatosHardcodedTipoMaterial(eTipoMaterial listaTipoMaterial[], int tam){

	int index;
	eTipoMaterial item = {1, "HDPE: Poliet. alta densidad", FULL};
	index = ObtenerPrimerEspacioLibreTipoMaterial(listaTipoMaterial, tam);
	listaTipoMaterial[index] = item;
	eTipoMaterial item2 = {2, "LDPE: Poliet. baja densidad", FULL};
	index = ObtenerPrimerEspacioLibreTipoMaterial(listaTipoMaterial, tam);
	listaTipoMaterial[index] = item2;
	eTipoMaterial item3 = {3, "PP: Polipropileno", FULL};
	index = ObtenerPrimerEspacioLibreTipoMaterial(listaTipoMaterial, tam);
	listaTipoMaterial[index] = item3;
}

int ObtenerPrimerEspacioLibreTipoMaterial(eTipoMaterial listaTipoMaterial[], int tam){
	int lugarLibre = -1;
	for(int i=0;i<tam;i++){
        if(listaTipoMaterial[i].isEmpty == EMPTY){
            lugarLibre = i;
            break;
        }
    }
	return lugarLibre;
}


void InicializarListaTipoMaterial(eTipoMaterial listaTipoMaterial[], int tam){
	for(int i=0;i<tam;i++){
		listaTipoMaterial[i].isEmpty = EMPTY;
	}
}

void MostrarTipoMaterial(eTipoMaterial tipoMaterial){
  printf("%20s\n", tipoMaterial.descripcion);
}

char* DescripcionTipoMaterialPorId(eTipoMaterial listaTipoMaterial[], int tam, int idTipoMaterial){
	char* descripcion = "";
	for(int i = 0; i < tam; i++){
	  if(listaTipoMaterial[i].isEmpty == FULL && listaTipoMaterial[i].id == idTipoMaterial){
		  strcat(descripcion, listaTipoMaterial[i].descripcion);
		  break;
	  }
	}
	return descripcion;
}

int MostrarTiposMateriales(eTipoMaterial listaTipoMaterial[], int tam){
    int retorno = -1;
    for (int i = 0; i < tam; i++){
      if (listaTipoMaterial[i].isEmpty == FULL){
    	  printf("%d - ", i+1);
    	  MostrarTipoMaterial(listaTipoMaterial[i]);
	      retorno = 0;
	  }
    }
    return retorno;
}
