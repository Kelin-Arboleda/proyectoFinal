/*
*Nombre: Proyecto final
*Fecha: 27/11/2017
*Realizado por: Kelin Arboleda - Camila Borja - Jose Alejandro Palacios.
*/

//Librerias
#include <stdio.h>
#include <stdlib.h>

//Estructura de cliente 
struct nodoCliente {
    int cedula;
    char nombre[50];
    int password;
    int puntos;
    nodoCliente *izq;
    nodoCliente *der;
};typedef nodoCliente *cliente;

//Arbol para un nuevo cliente
cliente nuevoCliente(int cedula) {
    cliente nuevo = new(struct nodoCliente);
    
	printf("Ingrese Nombre de USUARIO: ");
    fflush(stdin);
    gets(nuevo->nombre);

    nuevo->cedula = cedula;

    printf("Ingrese password: ");
    scanf("%d",&nuevo->password);

    nuevo->puntos = 0;

    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

//funcion para insertar cliente
void insertarCliente(cliente &CLIENTES, int cedula){
	//Condicion para ver en que lado del arbol se agregara el nuevo dato
	if( CLIENTES == NULL ){
        CLIENTES = nuevoCliente(cedula);
    } else if (cedula < CLIENTES->cedula) {
        insertarCliente( CLIENTES->izq, cedula );
    } else if (cedula > CLIENTES->cedula) {
        insertarCliente( CLIENTES->der, cedula );
    } else {
    	printf("ERROR: Ya existe un usuario con este numero de cedula.\n" );
    }
}

//Funcion para buscar clientes
cliente buscarCliente(cliente &CLIENTES, int cedula, int password){
	//condicion para saber a que lado del arbol buscar el dato requerido
	if( CLIENTES == NULL ) {
		printf("ALERTA: Usuario no encontrado.\n");
		return NULL;
	}
	if( CLIENTES->cedula == cedula ) {
		if( CLIENTES->password == password ) {
			printf("\nSesion iniciada con exito. ");
        	printf("Bienvenido, %s. \n\n", CLIENTES->nombre);
        	return CLIENTES;
		} else {
			printf("ERROR: Contrasena incorrecta.\n");
			return NULL;
		}
	} else if( CLIENTES->cedula < cedula ) {
		buscarCliente(CLIENTES->der,cedula,password);
	} else {
		buscarCliente(CLIENTES->izq,cedula,password);
	}
}

//Estructura del producto
struct nodoProducto {
    int id;
    char nombre[50];
    int precio;
    int cantidad;
    nodoProducto *izq;
    nodoProducto *der;
};typedef nodoProducto *producto;

//Arbol para crear un nuevo producto
producto nuevoProducto(int id) {
    producto nuevo = new(struct nodoProducto);
    
    nuevo->id = id;

    printf("Ingrese Nombre de PRODUCTO: ");
    fflush(stdin);
    gets(nuevo->nombre);

    printf("Ingrese precio: ");
    scanf("%d",&nuevo->precio);

    printf("Ingrese cantidad: ");
    scanf("%d",&nuevo->cantidad);

    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}  

//Funcion para insertar un producto
void insertarProducto(producto &PRODUCTOS, int id){ //referencia
	//Condicion para ver en que lado del arbol se agregara el nuevo dato
	if( PRODUCTOS == NULL ){
        PRODUCTOS = nuevoProducto(id);
    } else if ( id < PRODUCTOS->id ) {
        insertarProducto( PRODUCTOS->izq, id );
    } else if ( id > PRODUCTOS->id) {
        insertarProducto( PRODUCTOS->der, id );
	} else {
    	int extra;
    	printf("El producto %s tiene %d unidades en stock. \n", PRODUCTOS->nombre, PRODUCTOS->cantidad);
    	printf("Ingrese cantidad a aumentar: ");
    	scanf("%d",&extra);
    	PRODUCTOS->cantidad += extra;
    }
}

//Funcion para buscar un producto
producto buscarProducto(producto PRODUCTOS, int id){
	//Condicion para saber en que lado se debe buscar el producto
	if( PRODUCTOS == NULL ) {
		printf("ALERTA: Producto no encontrado.\n");
		return NULL;
	}
	if( PRODUCTOS->id == id ) {
		return PRODUCTOS;
	} else if( PRODUCTOS->id < id ) {
		buscarProducto(PRODUCTOS->der, id);
	} else {
		buscarProducto(PRODUCTOS->izq, id);
	}
}

//Funcion para saber la cantidad del producto
int cantidadProducto(producto PRODUCTOS) {
	if( PRODUCTOS == NULL ) return 0;
	return cantidadProducto(PRODUCTOS->izq) + cantidadProducto(PRODUCTOS->der) + 1;
}

//Funcion para imprimir el producto
void imprimirProducto(producto PRODUCTOS) {
	if( PRODUCTOS == NULL ) {
		return;
	} else {
		imprimirProducto( PRODUCTOS->izq );
		printf("\n\t. 1. (#%d) Nombre: %s, Precio: %d, Cantidad: %d.", PRODUCTOS->id, PRODUCTOS->nombre, PRODUCTOS->precio, PRODUCTOS->cantidad);
		imprimirProducto( PRODUCTOS->der );
	}
}

//Estructura del log de actividades
struct nodoLog {
    int id;
    char descripcion[50];
    nodoLog *izq;
    nodoLog *der;
};typedef nodoLog *log;

//Funcion de la cantidad de logs de actividades
int cantidadLog(log LOGS) {
	if( LOGS == NULL ) return 0;
	return cantidadLog(LOGS->izq) + cantidadLog(LOGS->der) + 1;
}

//Funcion para imprimir los logs de las actividades
void imprimirLog(log LOGS) {
	if( LOGS == NULL ) {
		return;
	} else {
		imprimirLog( LOGS->izq );
		printf("\n\t. (#%d) Descripcion: %s.", LOGS->id, LOGS->descripcion);
		imprimirLog( LOGS->der );
	}
}

//Arbol del log de las actividades
log nuevoLog(int id) {
    log nuevo = new(struct nodoLog);
     
    nuevo->id = id;

    printf("Ingrese Descripcion de LOG: ");
    fflush(stdin);
    gets(nuevo->descripcion);

    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}  

//Funcion para insertar nuevos logs
void insertarLog(log &LOGS, int id){
	//Condicion para ver en que lado del arbol se agregara el nuevo dato
	if( LOGS == NULL ){
        LOGS = nuevoLog(id);
    } else if ( id < LOGS->id ) {
        insertarLog( LOGS->izq, id );
    } else if ( id > LOGS->id) {
        insertarLog( LOGS->der, id );
    } else {
    	printf("ALERTA: Log sobreescrito.\n");
    }
}

//Prototipo de las funciones utilizadas
void menuInicio();
void loginUsuario();
void registroUsuario();
void menuPrincipal();
void menuCompras();
void informacion();
void confirmacion();
void menuAdministracion();
void agregarProductos();
void comprarProducto(int id);
void logActividades();

//Variables globales
cliente CLIENTES;
cliente usuario;
producto PRODUCTOS;
log LOGS;

//Funcion principal
int main(){
	CLIENTES = NULL;
	usuario = NULL;
	PRODUCTOS = NULL;
	LOGS = NULL;
    menuInicio();
    
    return 0;
}

//Menu para iniciar el programa
void menuInicio(){
    int opcion = 0;
    do{
    	printf("\n\t................................");
        printf("\n\t.    SUPER MERCADO COTECNOVA   .");
        printf("\n\t................................");
        printf("\n\t.   1. Iniciar Sesion          .");
        printf("\n\t.   2. Registrarme             .");
        printf("\n\t.   0. Salir                   .");
        printf("\n\t................................");
        printf("\n\nIngrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 0:
                system("cls");
                printf("\nEl programa se ha cerrado correctamente.\n");
                exit(0);
            case 1:
                system("cls");
                loginUsuario();
                break;
            case 2:
                system("cls");
                registroUsuario();
                break;
            default:
                system("cls");
                printf("\nLa opcion introducida no es valida, intente de nuevo.\n");
        }
    }while(opcion != 0);
}

//funcion para que el usuario inicie sesion
void loginUsuario(){
    int cedula, password;
    printf("\nIniciando Sesion...\n\n");
    printf("Ingrese Cedula: ");
    scanf("%d", &cedula);
    printf("Ingrese su password: ");
    scanf("%d", &password);
    system("cls");
    usuario = buscarCliente(CLIENTES, cedula, password);
    if( usuario != NULL ) {
    	menuPrincipal();
    }
}

//Funcion para que un cliente se registre en el sistema
void registroUsuario(){
	int cedula;
    printf("\nRegistrando Cliente...\n\n");
    printf("Ingrese Cedula: ");
    scanf("%d",&cedula);
    insertarCliente(CLIENTES, cedula);
    system("cls");
}


void menuPrincipal(){
    int opcion = 0;
    do{
    	printf("\n\t................................");
        printf("\n\t.   SUPER MERCADO COTECNOVA    .");
        printf("\n\t................................");
        printf("\n\t.   1. Comprar                 .");
        printf("\n\t.   2. Mi Informacion          .");
        printf("\n\t.   3. PANEL                   .");//En el panel encontramos los productos que encontramos en el supermercado y los log de actividades
        printf("\n\t.   0. Cerrar Sesion           .");
        printf("\n\t................................");
        printf("\n\t.       La Mejor Calidad.      .");
        printf("\n\t................................");
        printf("\n\nElija Una Opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 0:
                system("cls");
                usuario = NULL;
                menuInicio();
            case 1:
                system("cls");
                menuCompras();
                break;
            case 2:
                system("cls");
                informacion();
                break;
            case 3:
                system("cls");
                confirmacion();
                break;
            default:
                system("cls");
                printf("\nLa opcion introducida no es valida, intente de nuevo.\n");
        }
    }while(opcion != 0);
}

void menuCompras(){
    int i = 0, opcion = 0, productoComprar, seguridad;
    char nombre[]="Carlos Londono";
    if( cantidadProducto(PRODUCTOS) == 0){
       printf("\nNo hay productos actualmente en la tienda.\n");
    }else{
        do{
        	printf("\n\t.......................................................");
            printf("\n\t.                PRODUCTOS A COMPRAR                  .");
            printf("\n\t.......................................................");
            printf("\n\t.                                                     .");
            imprimirProducto(PRODUCTOS);
            printf("\n\t.                                                     .");
            printf("\n\t.     0. Regresar                                     .");
            printf("\n\t.......................................................");
            printf("\n\t.       Super 'COTECNOVA' La Mejor Calidad.           .");
            printf("\n\t.......................................................");
            printf("\nElija Una Opcion: ");
            scanf("%d", &opcion);
            switch(opcion){
                case 0:
                    system("cls");
                    menuPrincipal();
                case 1:
                    printf("\n\nQue producto deseas comprar?: ");
                    scanf("%d", &productoComprar);
                    printf("\nEstas seguro que deseas comprar este producto?: (1=SI/0=NO) ");
                    scanf("%d", &seguridad);
                    if(seguridad == 1){
                        system("cls");
                        comprarProducto(productoComprar);
                        printf("\nProducto comprado con exito.\n\n");
                        insertarLog( LOGS, cantidadLog(LOGS) +1 );
                    }else{
                        system("cls");
                    }
                    break;
                default:
                    system("cls");
                    printf("\nLa opcion introducida no es valida, intente de nuevo.\n");
            }
        }while(opcion != 0);
    }
}

//Funcion para mostrar la informacion del cliente
void informacion(){
    printf("\nEsta es tu Informacion\n");
    printf("\nNombre: %s.", usuario->nombre);
    printf("\nCedula: %d.", usuario->cedula);
    printf("\nTus Puntos: %d Puntos.\n", usuario->puntos);
}

//Funcion para confir los datos y entrar al panel administrativo
void confirmacion(){
    int pin = 1317, pinSolicitado;
    printf("\nIngrese PIN de Seguridad: ");
    scanf("%d", &pinSolicitado);
    
    //Condicion para hacer la comprobacion del pin y asi poder ingresar
    if(pin == pinSolicitado){
        printf("\nBienvenido %s al panel administrativo.\n", usuario->nombre);
        menuAdministracion();
    }else{
        printf("\nEl PIN ingresado es incorrecto.\n");
    }
}

//Menu donde podemos agrgar productos y ver logs de actividades
void menuAdministracion(){
    int opcion = 0;
    do{
    	printf("\n\t................................");
        printf("\n\t.  SUPER MERCADO COTECNOVA     .");
        printf("\n\t................................");
        printf("\n\t.   1. Agregar Productos       .");
        printf("\n\t.   2. Ver Logs                .");
        printf("\n\t.   0. Regresar                .");
        printf("\n\t................................");
        printf("\n\t.      La Mejor Calidad.       .");
        printf("\n\t................................");
        printf("\nElija Una Opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 0:
                system("cls");
                menuPrincipal();
            case 1:
                system("cls");
                agregarProductos();
                break;
            case 2:
                system("cls");
                logActividades();
                break;
            default:
                system("cls");
                printf("\nLa opcion introducida no es valida, intente de nuevo.\n");
        }
    }while(opcion != 0);
}

//Funcion que le permite al cliente agregar productos a la tienda
void agregarProductos(){
    int i = 0, cant, id;
    printf("\nIngrese cantidad de productos: ");
    scanf("%d", &cant);
    for(i = 0; i < cant ; i++){
        printf("\nProducto #%d \n", i+1);
        printf("Ingrese ID del producto: ");
        scanf("%d",&id);
        insertarProducto(PRODUCTOS,id);
    }
    system("cls");
    printf("Productos registrados con exito\n");
}

//Funcion para realizar la compra de un producto
void comprarProducto(int id){
	producto p = buscarProducto(PRODUCTOS, id);
	if( p != NULL ) {
		p->cantidad--;//Para disminuir la cantidad de productos de la tienda 
		usuario->puntos++;//para aumentar los puntos de un cliente
	}
}

void logActividades(){
	int i = 0, opcion = 0;
    if( cantidadLog(LOGS) == 0 ){
       printf("\nNo hay logs actualmente en la tienda.\n");
    }else{
        do{
        	printf("\n\t......................................................");
            printf("\n\t.               LOGS DE ACTIVIDADES                  .");
            printf("\n\t......................................................");
            printf("\n\t.                                                    .");
            imprimirLog(LOGS);
            printf("\n\t.                                                    .");
            printf("\n\t.     0. Regresar                                    .");
            printf("\n\t......................................................");
            printf("\n\t.       Super 'COTECNOVA' La Mejor Calidad.          .");
            printf("\n\t......................................................");
            printf("\n\nElija Una Opcion: ");
            scanf("%d", &opcion);
            switch(opcion){
                case 0:
                    system("cls");
                    menuPrincipal();
                default:
                    system("cls");
                    printf("\nLa opcion introducida no es valida, intente de nuevo.\n");
            }
        }while(opcion != 0);
    }
}


