#define TAM_CLIENTES 10
#define MAX_INTENTOS 5
#define TAM_RAZON_SOCIAL 100
#define TAM_CUIT 15
#define TAM_DIRECCION 150
#define TAM_LOCALIDAD 150
#define CLIENTE_INIT_ID 100000
#define MAX_ID_VALUE  100100

typedef struct{
  int id;
  char razonSocial[TAM_RAZON_SOCIAL];
  char cuit[TAM_CUIT];
  char direccion[TAM_DIRECCION];
  char localidad[TAM_LOCALIDAD];
  int isEmpty;
} eCliente;


int AltaCliente(eCliente listaClientes[], int tam, int* id);
int ObtenerPrimerEspacioLibreCliente(eCliente listaClientes[], int tam);
void MostrarCliente(eCliente cliente);
int MostrarListaClientes(eCliente listaClientes[], int tam);
int ModificarCliente(eCliente listaClientes[], int tam);
int BorrarCliente(eCliente listaClientes[], int tam);
int GetPosicionPorId(eCliente listaClientes[], int tam, int id);
void MostrarClientePedido(eCliente cliente, int pedidosPendientes);
void inicializarListaClientes(eCliente listaClientes[], int tam);
void CargarDatosHardcodedCliente(eCliente listaClientes[], int tam);
eCliente ObtenerClientePorId(eCliente listaClientes[], int tam, int id);
int GetCantidadTotalClientes(eCliente listaClientes[], int tam);
