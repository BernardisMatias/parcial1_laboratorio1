#define TAM_CLIENTES 10
#define MAX_INTENTOS 5
#define TAM_RAZON_SOCIAL 100
#define TAM_CUIT 15
#define TAM_DIRECCION 150
#define CLIENTE_INIT_ID 100000
#define MAX_ID_VALUE  100100

typedef struct{
  int id;
  char razonSocial[TAM_RAZON_SOCIAL];
  char cuit[TAM_CUIT];
  char direccion[TAM_DIRECCION];
  int idLocalidad;
  int isEmpty;
} eCliente;


/// \fn void MostrarCliente(eCliente)
/// \brief Muestra un cliente
/// \param cliente Cliente a mostrar
void MostrarCliente(eCliente cliente, char localidad[]);


/// \fn int GetPosicionPorId(eCliente[], int, int)
/// \brief devuelve la posicion del cliente por id del cliente
/// \param listaClientes Lista donde se buscará el cliente
/// \param tam Tamaño del array
/// \param id del cliente a buscar
/// \return index del cliente si existe, -1 si no
int GetPosicionPorId(eCliente listaClientes[], int tam, int id);

/// \fn void MostrarClientePedido(eCliente, int)
/// \brief Muestra datos del cliente segun pedidos pendientes
/// \param cliente a mostrar
/// \param pedidosPendientes cantidad total de pedidos pendientes
void MostrarClientePedido(eCliente cliente, char localidad[], int pedidosPendientes);

/// \fn void inicializarListaClientes(eCliente[], int)
/// \brief Setea EMPTY en isEmpty de todos los elementos del array
/// \param listaClientes a inicializar
/// \param tam Tamaño del array
void inicializarListaClientes(eCliente listaClientes[], int tam);


/// \fn eCliente ObtenerClientePorId(eCliente[], int, int)
/// \brief Devuelve una estructura cliente segun id
/// \param listaClientes donde se buscará
/// \param tam Tamaño del array
/// \param id de cliente a buscar
/// \return eCliente si existe
eCliente ObtenerClientePorId(eCliente listaClientes[], int tam, int id);

/// \fn int GetCantidadTotalClientes(eCliente[], int)
/// \brief Develve el total de clientes
/// \param listaClientes donde se buscará
/// \param tam Tamaño del array
/// \return cantidad de clientes en array
int GetCantidadTotalClientes(eCliente listaClientes[], int tam);
