#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "entidad1.h"
#include "utn.h"
#include "entidad2.h"

static int proximoId(void);
static int buscarLibre(Cliente* array,int limite);

/** \brief Inicializa a todos los elementos del array como vacios
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \return int -1 si la lista esta vacia
 *
 */
int cliente_init(Cliente* array,int limite)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            array[i].isEmpty=1;
        }
    }
    return retorno;
}

/** \brief Da de alta a un cliente
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param nombre char* nombre del cliente
 * \param apellido char* apellido del cliente
 * \param cuit int cuit del cliente
 * \return int -1 si no hay lugar libre
 *
 */
int cliente_altaForzada(Cliente* array,int limite,char* nombre,char* apellido,int cuit)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        i=buscarLibre(array,limite);
        if(i>=0){
            retorno=0;
            strcpy(array[i].nombre,nombre);
            strcpy(array[i].apellido,apellido);
            array[i].cuit=cuit;
            array[i].id=proximoId();
            array[i].isEmpty=0;
        }
            else retorno=-3;
    }
        else{
            retorno=-2;
        }
    return retorno;
}

/** \brief Pide los campos y da de alta a un cliente
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \return int -1 si la lista esta vacia -2 si no hay lugar libre -3 si hay error en el ingreso de datos
 *
 */
int cliente_alta(Cliente* array,int limite)
{
    int retorno=-1;
    int i;
    int cuit;
    char nombre[50];
    char apellido[50];
    if(limite>0&&array!=NULL){
        i=buscarLibre(array,limite);
        if(i>=0){
            if(!getValidString("\nNombre: ","\nEso no es un nombre\n","\n50 caracteres maximo\n",nombre,50,2)){
                if(!getValidString("\nApellido: ","\nEso no es un apellido\n","\n50 caracteres maximo\n",apellido,50,2)){
                    if(!getValidInt("\nCUIT: ","\n8 digitos sin guiones ni espacios\n",&cuit,0,99999999,2)){
                        retorno=0;
                        strcpy(array[i].nombre,nombre);
                        strcpy(array[i].apellido,apellido);
                        array[i].cuit=cuit;
                        array[i].id=proximoId();
                        array[i].isEmpty=0;
                        printf("\nID: %d\n", array[i].id);
                    }
                }
            }
            else retorno=-3;
        }
        else{
            retorno=-2;
        }
    }
    return retorno;
}

/** \brief Da de baja a un cliente y a todas sus publicaciones
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param id int id del cliente a dar de baja
 * \param arrayP Publicacion* array de publicaciones
 * \param limiteP int limite del array de publicaciones
 * \return int -1 si no se encontro el id
 *
 */
int cliente_baja(Cliente* array,int limite, int id,Publicacion* arrayP,int limiteP)
{
    int retorno=-1;
    int i;
    int choice;
    int indice=cliente_buscarId(array,limite,id);
    publicacion_mostrarPorCliente(arrayP,limiteP,id);
    getValidInt("Borrar cliente y todas sus publicaciones? [1]SI - [0]NO ","Por favor, marcar 1 o 0",&choice,0,1,2);
    if(choice){
        if(indice>=0){
            array[indice].isEmpty=1;
            retorno=0;
        }
        for(i=0;i<limiteP;i++){
            if(id==arrayP[i].idCliente)
                publicacion_baja(arrayP,limiteP,arrayP[i].id);
        }
    }
    else
        retorno=0;
    return retorno;
}

/** \brief Modifica los datos de un cliente
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param id int id del cliente a modificar
 * \return int -1 si el id no se encuentra -2 si hay un error en los datos
 *
 */
int cliente_modificacion(Cliente* array,int limite,int id)
{
    int retorno=-1;
    char nombre[50];
    char apellido[50];
    int cuit;
    int indice=cliente_buscarId(array,limite,id);
    if(indice>=0){
        retorno=-2;
        if(!getValidString("\nNombre: ","\nEso no es un nombre\n","\n50 caracteres maximo\n",nombre,50,2)){
            if(!getValidString("\nApellido: ","\nEso no es un apellido\n","\n50 caracteres maximo\n",apellido,50,2)){
                if(!getValidInt("\nCUIT: ","\nIngresar solo los digitos\n",&cuit,0,99999999,2)){
                    retorno=0;
                    strcpy(array[indice].nombre,nombre);
                    strcpy(array[indice].apellido,apellido);
                    array[indice].cuit=cuit;
                }
            }
        }
    }
    return retorno;
}

/** \brief Busca el primer lugar vacio en un array
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \return int -1 si la lista esta vacia
 *
 */
int buscarLibre(Cliente* array,int limite)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        for(i=0;i<limite;i++){
            if(array[i].isEmpty){
            retorno=i;
            break;
            }
        }
    }
    return retorno;
}

/** \brief Calcula el siguiente id a usar
 *
 * \param void
 * \return int proximo id
 *
 */
int proximoId(void)
{
    static int proximoId=-1;
    proximoId++;
    return proximoId;
}

/** \brief Muestra todos los clientes que no estan vacios
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param arrayP Publicacion* array de publicaciones
 * \param limiteP int limite del array de publicaciones
 * \return int -1 si la lista esta vacia
 *
 */
int cliente_mostrar(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int retorno=-1;
    int i;
    int avisos;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty){
                avisos=cliente_contarAvisos(arrayP,limiteP,array[i].id);
                printf("ID: %d - Nombre: %s - Apellido: %.s - CUIT: %d - Avisos activos: %d\n",array[i].id,array[i].nombre,array[i].apellido,array[i].cuit,avisos);
            }
        }
    }
    return retorno;
}

/** \brief Busca el indice de un cliente dado su id
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param id int id del cliente a buscar
 * \return int devuelve el indice del cliente. -1 si la lista esta vacia -2 si no se encontro el cliente
 *
 */
int cliente_buscarId(Cliente* array,int limite,int id)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        retorno=-2;
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty && array[i].id==id){
                retorno=i;
                break;
            }
        }
    }
    return retorno;
}


/** \brief Imprime los datos de un cliente dado su id
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param id int id del cliente
 * \return int  -1 si no se encuentra
 *
 */
int cliente_mostrarPorId(Cliente* array,int limite,int id)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty && array[i].id==id){
                printf("Nombre: %s - Apellido: %.s - CUIT: %d\n",array[i].nombre,array[i].apellido,array[i].cuit);
                retorno=0;
            }
        }
    }
    return retorno;
}

/** \brief Calcula la cantidad de avisos que tiene publicado un cliente dado su id
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param id int id del cliente
 * \return int cantidad de avisos del cliente
 *
 */
int cliente_contarAvisos(Publicacion* array,int limite,int id)
{
    int retorno=0;
    int i;
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty && array[i].idCliente==id) && !array[i].isPaused)
            retorno++;
    }
    return retorno;
}

/** \brief Calcula la cantidad de avisos activos que tiene publicado un cliente dado su id
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param id int id del cliente
 * \return int cantidad de avisos activos del cliente
 *
 */
int cliente_contarAvisosActivos(Publicacion* array,int limite,int id)
{
    int retorno=0;
    int i;
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty && array[i].idCliente==id) && !array[i].isPaused)
            retorno++;
    }
    return retorno;
}

/** \brief Calcula la cantidad de avisos pausados que tiene publicado un cliente dado su id
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param id int id del cliente
 * \return int cantidad de avisos pausados del cliente
 *
 */
int cliente_contarAvisosPausados(Publicacion* array,int limite,int id)
{
    int retorno=0;
    int i;
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty && array[i].idCliente==id) && array[i].isPaused)
            retorno++;
    }
    return retorno;
}

/** \brief Calcula la cantidad maxima de avisos publicados por un solo cliente
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param arrayP Publicacion* array de publicaciones
 * \param limiteP int limite del array de publicaciones
 * \return int cantidad maxima de avisos
 *
 */
int cliente_maximoAvisos(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int i;
    int max=0;
    int aux;
    for(i=0;i<limite;i++){
        aux=cliente_contarAvisos(arrayP,limiteP,array[i].id);
        if(!max || aux>max)
            max=aux;
    }
    return max;
}

/** \brief Calcula la cantidad maxima de avisos activos publicados por un solo cliente
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param arrayP Publicacion* array de publicaciones
 * \param limiteP int limite del array de publicaciones
 * \return int cantidad maxima de avisos activos
 *
 */
int cliente_maximoAvisosActivos(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int i;
    int max=0;
    int aux;
    for(i=0;i<limite;i++){
        aux=cliente_contarAvisosActivos(arrayP,limiteP,array[i].id);
        if(!max || aux>max)
            max=aux;
    }
    return max;
}

/** \brief Calcula la cantidad maxima de avisos pausados publicados por un solo cliente
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param arrayP Publicacion* array de publicaciones
 * \param limiteP int limite del array de publicaciones
 * \return int cantidad maxima de avisos pausados
 *
 */
int cliente_maximoAvisosPausados(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int i;
    int max=0;
    int aux;
    for(i=0;i<limite;i++){
        aux=cliente_contarAvisosPausados(arrayP,limiteP,array[i].id);
        if(!max || aux>max)
            max=aux;
    }
    return max;
}

/** \brief Imprime los clientes con mas avisos activos, mas avisos pausados, y mas avisos en general
 *
 * \param array Cliente* array de clientes
 * \param limite int limite del array
 * \param arrayP Publicacion* array de publicaciones
 * \param limiteP int limite del array de publicaciones
 * \return int
 *
 */
int cliente_informar(Cliente* array,int limite,Publicacion* arrayP,int limiteP)
{
    int i;
    int max=cliente_maximoAvisosActivos(array,limite,arrayP,limiteP);
    printf("\n*Cliente(s) con mas avisos activos*\n");
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty&&cliente_contarAvisos(arrayP,limiteP,array[i].id)==max) && max)
            cliente_mostrarPorId(array,limite,array[i].id);
    }
    printf("\n*Cliente(s) con mas avisos pausados*\n");
    max=cliente_maximoAvisosPausados(array,limite,arrayP,limiteP);
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty&&cliente_contarAvisosPausados(arrayP,limiteP,array[i].id)==max) && max)
            cliente_mostrarPorId(array,limite,array[i].id);
    }
    printf("\n*Cliente(s) con mas avisos*\n");
    max=cliente_maximoAvisos(array,limite,arrayP,limiteP);
    for(i=0;i<limite;i++){
        if((!array[i].isEmpty&&cliente_contarAvisos(arrayP,limiteP,array[i].id)==max) && max)
            cliente_mostrarPorId(array,limite,array[i].id);
    }
    return 0;
}
