#ifndef CONTRATACION_H_INCLUDED
#define CONTRATACION_H_INCLUDED

typedef struct
{
    int id;
    int idCliente;
    char aviso[64];
    int rubro;
    int ventas;
    int isPaused;
    int isEmpty;
}Publicacion;

#include "entidad1.h"

int publicacion_init(Publicacion* array,int limite);
int publicacion_contratar(Publicacion* array,Cliente* pantallas,int limite,int limiteP);
int publicacion_mostrar(Publicacion* array,int limite,Cliente* Clientes);
int publicacion_modificacion(Publicacion* array,int limite,int id);
int publicacion_mostrarPorCliente(Publicacion* array,int limite, int idCliente);
int publicacion_baja(Publicacion* array,int limite, int id);
int publicacion_comprar(Publicacion* array,int limite,Cliente* Clientes,int id);
int publicacion_pausar(Publicacion* array,int limite,Cliente* arrayC,int limiteC);
int publicacion_reanudar(Publicacion* array,int limite,Cliente* arrayC,int limiteC);
int publicacion_informar(Publicacion* array,int limite);

#endif // publicacion_H_INCLUDED
