#define TAM_TIPO_MATERIAL 5
#define DESC_TIPO_MATERIAL 200

typedef struct{
  int id;
  char descripcion[DESC_TIPO_MATERIAL];
  int isEmpty;
} eTipoMaterial;

void InicializarListaTipoMaterial(eTipoMaterial listaTipoMaterial[], int tam);
int MostrarTiposMateriales(eTipoMaterial listaTipoMaterial[], int tam);
void MostrarTipoMaterial(eTipoMaterial tipoMaterial);
void CargarDatosHardcodedTipoMaterial(eTipoMaterial listaTipoMaterial[], int tam);
int ObtenerPrimerEspacioLibreTipoMaterial(eTipoMaterial listaTipoMaterial[], int tam);
