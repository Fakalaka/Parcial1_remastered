#include <stdio.h>
#include <stdlib.h>
#include "entidad1.h"
#include "entidad2.h"
#include "utn.h"
#define QTYCliente 100
#define QTYPublicacion 1000

int main()
{
    Cliente clientes[QTYCliente];
    Publicacion avisos[QTYPublicacion];
    int menu;
    int auxiliarId;
    cliente_init(clientes,QTYCliente);
    publicacion_init(avisos,QTYPublicacion);
    cliente_altaForzada(clientes,QTYCliente,"Juan","Boccardi","30280568797");
    cliente_altaForzada(clientes,QTYCliente,"Pepe","Pepazo","20255063558");
    cliente_altaForzada(clientes,QTYCliente,"Laura","Grueso","19414500236");
    do
    {
        menu=0;
        getValidInt("\n1.Alta de cliente\n2.Modificar datos de cliente\n3.Baja de cliente\n4.Publicar\n5.Pausar publicacion\n6.Reanudar publicacion\n7.Imprimir clientes\n8.Imprimir publicaciones\n9.Informar clientes\n10.Informar publicaciones\n11.Salir\n","\nOpcion no valida\n",&menu,1,11,1);
        switch(menu)
        {
            case 1:
                cliente_alta(clientes,QTYCliente);
                break;
            case 2:
                getValidInt("ID? ","\nNumero no valido\n",&auxiliarId,0,999,2);
                cliente_modificacion(clientes,QTYCliente,auxiliarId);
                break;
            case 3:
                getValidInt("ID? ","\nNumero no valido\n",&auxiliarId,0,999,2);
                if(cliente_baja(clientes,QTYCliente,auxiliarId,avisos,QTYPublicacion))
                    printf("\nNo se encontro el cliente\n");
                break;
            case 4:
                if(publicacion_contratar(avisos,clientes,QTYPublicacion,QTYCliente))
                    printf("\nError\n");
                break;
            case 5:
                publicacion_pausar(avisos,QTYPublicacion,clientes,QTYCliente);
                break;
            case 6:
                publicacion_reanudar(avisos,QTYPublicacion,clientes,QTYCliente);
                break;
            case 7:
                printf("\n");
                cliente_mostrar(clientes,QTYCliente,avisos,QTYPublicacion);
                break;
            case 8:
                publicacion_mostrar(avisos,QTYPublicacion,clientes);
                break;
            case 9:
                cliente_informar(clientes,QTYCliente,avisos,QTYPublicacion);
                break;
            case 10:
                publicacion_informar(avisos,QTYPublicacion);
                break;
            case 11:
                printf("\nChau!\n");
        }
    }while(menu != 11);

    return 0;
}
