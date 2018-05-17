#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "entidad1.h"
#include "entidad2.h"
#include "utn.h"

static int proximoId(void);
static int buscarId(Publicacion* array,int limite,int id);
static int buscarLibre(Publicacion* array,int limite);
static int contarRubro(Publicacion* array,int limite,int*max,int*min);

/** \brief Inicializa a todos los elementos del array como vacios
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \return int -1 si la lista esta vacia
 *
 *
 */
int publicacion_init(Publicacion* array,int limite)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            array[i].isEmpty=1;
            array[i].ventas=0;
        }
    }
    return retorno;
}

/** \brief
 *
 * \param array Publicacion* array de publicaciones
 * \param arrayC Cliente* array de clientes
 * \param limite int limite limite del array de publicaciones
 * \param limiteP int limite del array de clientes
 * \return int -1 si la lista esta vacia -2 si no hay lugar libre -3 si hay error en el ingreso de datos
 *
 */
int publicacion_contratar(Publicacion* array,Cliente* arrayC,int limite,int limiteP)
{
    int retorno=-1;
    int i;
    char aviso[64];
    int rubro;
    int id;
    if(limite>0&&array!=NULL){
        i=buscarLibre(array,limite);
        if(i>=0){
            if(!getValidString("\nAviso: ","\nEso no es un aviso\n","\n64 caracteres maximo\n",aviso,64,2)){
                if(!getValidInt("\nRubro: ","\nDe 1 a 99\n",&rubro,1,99,2)){
                    if(!getValidInt("\nID Cliente: ","\nDe 0 a 99\n",&id,0,99,2)){
                        if(cliente_buscarId(arrayC,limiteP,id)>=0){
                            retorno=0;
                            strcpy(array[i].aviso,aviso);
                            array[i].rubro=rubro;
                            array[i].id=proximoId();
                            array[i].idCliente=id;
                            array[i].isPaused=0;
                            array[i].isEmpty=0;
                        }
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

/** \brief Da de baja una publicacion dado su id
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param id int id de la publicacion
 * \return int -1 si no se encuentra la publicacion
 *
 */
int publicacion_baja(Publicacion* array,int limite, int id)
{
    int retorno=-1;
    int indice=buscarId(array,limite,id);
    if(indice>=0){
        array[indice].isEmpty=1;
        retorno=0;
    }
    return retorno;
}

/** \brief Busca el primer lugar vacio en un array
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \return int -1 si la lista esta vacia
 *
 */
static int buscarLibre(Publicacion* array,int limite)
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
static int proximoId(void)
{
    static int proximoId=-1;
    proximoId++;
    return proximoId;
}

/** \brief Calcula el indice de una publicacion dado su id
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param id int id de la publicacion
 * \return int indice de la publicacion
 *
 */
static int buscarId(Publicacion* array,int limite,int id)
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


/** \brief Imprime los datos de todas las publicaciones
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param arrayC Cliente* array de clientes
 * \return int -1 si la lista esta vacia
 *
 */
int publicacion_mostrar(Publicacion* array,int limite,Cliente* arrayC)
{
    int retorno=-1;
    int i;
    int userindex;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            if(!array[i].isEmpty&&!array[i].isPaused){
                    userindex=cliente_buscarId(arrayC,limite,array[i].idCliente);
                    printf("\nID: %d - Aviso: %s - Rubro: %d - CUIT Cliente: %d\n",array[i].id,array[i].aviso,array[i].rubro,arrayC[userindex].cuit);
            }
        }
    }
    return retorno;
}

/** \brief Muestra todas las publicaciones de un cliente dado su id
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param idCliente int id del cliente
 * \return int -1 si la lista esta vacia
 *
 */
int publicacion_mostrarPorCliente(Publicacion* array,int limite, int idCliente)
{
    int retorno=-1;
    int i;
    if(limite>0&&array!=NULL){
        retorno=0;
        for(i=0;i<limite;i++){
            if((!array[i].isEmpty&&!array[i].isPaused)&&array[i].idCliente==idCliente){
                    printf("\nID: %d - Aviso: %s - Rubro: %d\n",array[i].id,array[i].aviso,array[i].rubro);
            }
        }
    }
    return retorno;
}

/** \brief Pausa una publicacion pidiendo su id
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param arrayC Cliente* array de clientes
 * \param limiteC int limite del array de clientes
 * \return int -1 si no se ingresa un id correcto
 *
 */
int publicacion_pausar(Publicacion* array,int limite,Cliente* arrayC,int limiteC)
{
    int id;
    int index;
    int choice;
    int idCliente;
    int retorno=-1;
    if(!getValidInt("\nID Publicacion: ","\nPublicacion no encontrada\n",&id,0,999,2)){
        retorno=0;
        index=buscarId(array,limite,id);
        idCliente=cliente_buscarId(arrayC,limiteC,array[index].idCliente);
        if(cliente_mostrarPorId(arrayC,limiteC,idCliente)>=0){
            getValidInt("Cambiar estado? [1]SI - [0]NO ","Por favor, marcar 1 o 0",&choice,0,1,2);
            if(choice)
                array[index].isPaused=1;
        }
    }
    return retorno;
}

/** \brief Reanuda una publicacion pidiendo su id
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param arrayC Cliente* array de clientes
 * \param limiteC int limite del array de clientes
 * \return int -1 si no se reanudo
 *
 */
int publicacion_reanudar(Publicacion* array,int limite,Cliente* arrayC,int limiteC)
{
    int id;
    int index;
    int choice;
    int idCliente;
    int retorno=-1;
    if(!getValidInt("\nID Publicacion: ","\nPublicacion no encontrada\n",&id,0,999,2)){
        index=buscarId(array,limite,id);
        idCliente=cliente_buscarId(arrayC,limiteC,array[index].idCliente);
        if(cliente_mostrarPorId(arrayC,limiteC,idCliente)>=0){
            getValidInt("Cambiar estado? [1]SI - [0]NO ","Por favor, marcar 1 o 0",&choice,0,1,2);
            if(choice){
                array[index].isPaused=0;
                retorno=0;
            }
        }
    }
    return retorno;
}

/** \brief Imprime la cantidad de publicaciones de un rubro ingresado, el rubro con mas publicaciones activos y el rubro con menos
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del arrayt
 * \return int
 *
 */
int publicacion_informar(Publicacion* array,int limite)
{
    int i;
    int max;
    int min;
    int contador=0;
    int rubro;
    if(!getValidInt("\nRubro: ","\nEso no es un rubro\n",&rubro,1,99,2)){
        for(i=0;i<limite;i++){
            if(!array[i].isPaused && array[i].rubro==rubro)
                contador++;
        }
    contarRubro(array,limite,&max,&min);
    printf("\n*Cantidad de publicaciones del rubro %d* %d\n",rubro,contador);
    printf("\n*Rubro con mas publicaciones activas* %d\n",max);
    printf("\n*Rubro con menos publicaciones activas* %d\n",min);
    }
    return 0;
}

/** \brief Calcula los rubros con mas y menos publicaciones
 *
 * \param array Publicacion* array de publicaciones
 * \param limite int limite del array
 * \param max int* se guardara el rubro con mas publicaciones
 * \param min int* se guardara el rubro con menos publicaciones
 * \return int
 *
 */
int contarRubro(Publicacion* array,int limite,int* max,int* min)
{
    int i;
    int j;
    int auxMax=0;
    int auxMin=101;
    int contador;
    for(i=1;i<100;i++){
        contador=0;
        for(j=0;j<limite;j++){
            if(!array[j].isPaused && array[j].rubro==i)
                contador++;
        }
        if(contador>auxMax){
            auxMax=contador;
            *max=i;
        }
        if(contador<auxMin&&contador>=1){
            auxMin=contador;
            *min=i;
        }
    }
    if(auxMin==101)
            *min=0;
    return 0;
}
