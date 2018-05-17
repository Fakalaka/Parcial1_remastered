#include <stdio.h>
#include <stdlib.h>
#include "entidad1.h"
#include "entidad2.h"
#include "utn.h"
#define QTYCliente 100
#define QTYPublicacion 1000

int main()
{
    Cliente array[QTYCliente];
    Publicacion aviso[QTYPublicacion];
    int menu;
    int auxiliarId;
    cliente_init(array,QTYCliente);
    publicacion_init(aviso,QTYPublicacion);
    cliente_altaForzada(array,QTYCliente,"Ernesto","Hernandez",22056879);
    cliente_altaForzada(array,QTYCliente,"Pepito","Pepazo",25506355);
    cliente_altaForzada(array,QTYCliente,"Laura","Grueso",44450023);
    do
    {
        menu=0;
        getValidInt("\n1.Alta de cliente\n2.Modificar datos de cliente\n3.Baja de cliente\n4.Publicar\n5.Pausar publicacion\n6.Reanudar publicacion\n7.Imprimir clientes\n8.Imprimir publicaciones\n9.Informar clientes\n10.Informar publicaciones\n11.Salir\n","\nOpcion no valida\n",&menu,1,11,1);
        switch(menu)
        {
            case 1:
                cliente_alta(array,QTYCliente);
                break;
            case 2:
                getValidInt("ID? ","\nNumero no valido\n",&auxiliarId,0,999,2);
                cliente_modificacion(array,QTYCliente,auxiliarId);
                break;
            case 3:
                getValidInt("ID? ","\nNumero no valido\n",&auxiliarId,0,999,2);
                cliente_baja(array,QTYCliente,auxiliarId,aviso,QTYPublicacion);
                break;
            case 4:
                publicacion_contratar(aviso,array,QTYPublicacion,QTYCliente);
                break;
            case 5:
                publicacion_pausar(aviso,QTYPublicacion,array,QTYCliente);
                break;
            case 6:
                publicacion_reanudar(aviso,QTYPublicacion,array,QTYCliente);
                break;
            case 7:
                printf("\n");
                cliente_mostrar(array,QTYCliente,aviso,QTYPublicacion);
                break;
            case 8:
                publicacion_mostrar(aviso,QTYPublicacion,array);
                break;
            case 9:
                cliente_informar(array,QTYCliente,aviso,QTYPublicacion);
                break;
            case 10:
                publicacion_informar(aviso,QTYPublicacion);
                break;
            case 11:
                printf("\nChau!\n");
        }
    }while(menu != 11);

    return 0;
}
