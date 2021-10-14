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


/// \fn int AltaCliente(eCliente[], int, int*)
/// \brief Genera el alta de un cliente en el sistema
/// \param listaClientes Lista donde se guardará el cliente
/// \param tam Tamaño del array
/// \param id Puntero a un valor de id para poder incrementar
/// \return 0 Si se pudo hacer, -1 si hubo un error
int AltaCliente(eCliente listaClientes[], int tam, int* id);

/// \fn int ObtenerPrimerEspacioLibreCliente(eCliente[], int)
/// \brief Busca el primer espacio libre en el array
/// \param listaClientes Lista donde se buscará espacio
/// \param tam Tamaño del array
/// \return index del array si se hay libre, -1 si hubo un error
int ObtenerPrimerEspacioLibreCliente(eCliente listaClientes[], int tam);

/// \fn void MostrarCliente(eCliente)
/// \brief Muestra un cliente
/// \param cliente Cliente a mostrar
void MostrarCliente(eCliente cliente);

/// \fn int MostrarListaClientes(eCliente[], int)
/// \brief Muestra el listado de clientes
/// \param listaClientes
/// \param tam Tamaño del array
/// \return
int MostrarListaClientes(eCliente listaClientes[], int tam);

/// \fn int ModificarCliente(eCliente[], int)
/// \brief Modifica un cliente. Dentro pide id de cliente y lo modifica
/// \param listaClientes Lista donde se modificará el cliente
/// \param tam Tamaño del array
/// \return
int ModificarCliente(eCliente listaClientes[], int tam);

/// \fn int BorrarCliente(eCliente[], int)
/// \brief Borra un cliente. Dentro pide id de cliente y lo elimina pidiendo confirmacion
/// \param listaClientes Lista donde se borrará el cliente
/// \param tam Tamaño del array
/// \return
int BorrarCliente(eCliente listaClientes[], int tam);

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
void MostrarClientePedido(eCliente cliente, int pedidosPendientes);

/// \fn void inicializarListaClientes(eCliente[], int)
/// \brief Setea EMPTY en isEmpty de todos los elementos del array
/// \param listaClientes a inicializar
/// \param tam Tamaño del array
void inicializarListaClientes(eCliente listaClientes[], int tam);

/// \fn void CargarDatosHardcodedCliente(eCliente[], int)
/// \brief Carga datos en la lista de clientes
/// \param listaClientes a cargar
/// \param tam Tamaño del array
void CargarDatosHardcodedCliente(eCliente listaClientes[], int tam);

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
