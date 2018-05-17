#ifndef ENTIDAD1_H_INCLUDED
#define ENTIDAD1_H_INCLUDED

typedef struct
{
    char nombre[50];
    char apellido[50];
    int cuit;
    float calificacion;
    int cantidadCalif;
    int id;
    int isEmpty;
}Cliente;

#include "entidad2.h"

int cliente_init(Cliente* array,int limite);
int cliente_alta(Cliente* array,int limite);
int cliente_baja(Cliente* array,int limite, int id,Publicacion* arrayP,int limiteP);
int cliente_modificacion(Cliente* array,int limite,int id);
int cliente_mostrar(Cliente* array,int limite,Publicacion* arrayP,int limiteP);
int cliente_mostrarDebug(Cliente* array,int limite);
int cliente_buscarId(Cliente* array,int limite,int id);
int cliente_altaForzada(Cliente* array,int limite,char* nombre,char* apellido,int cuit);
int cliente_mostrarPorId(Cliente* array,int limite,int id);
int cliente_contarAvisos(Publicacion* array,int limite,int id);
int cliente_maximoAvisos(Cliente* array,int limie,Publicacion* arrayP,int limiteP);
int cliente_contarAvisosActivos(Publicacion* array,int limite,int id);
int cliente_maximoAvisosActivos(Cliente* array,int limie,Publicacion* arrayP,int limiteP);
int cliente_contarAvisosPausados(Publicacion* array,int limite,int id);
int cliente_maximoAvisosPausados(Cliente* array,int limie,Publicacion* arrayP,int limiteP);
int cliente_informar(Cliente* array,int limite,Publicacion* arrayP,int limiteP);

#endif // ENTIDAD1_H_INCLUDED
