#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pantalla.h"
#include "contratacion.h"
#include "validar.h"
#include "informes.h"

/** \brief idAutoincrementable
 *
 * \param array listaCliente recibe puntero al inicio del array
 * \param len es la cantidad de elementos del array
 * \return retorna el ultimo valor para utilizar en Id
 *
 */

int cliente_generar_Proximo_Id(sCliente listaClientes[], int len)
{
    static int ultimoValorIdAutoincrementable = -1;
    ultimoValorIdAutoincrementable ++;
    return ultimoValorIdAutoincrementable;

}


/** \brief Inicializa la lista
 *
 * \param array listaClientes recibe puntero al inicio del array
 * \param limite es la cantidad de elementos del array
 * \return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int cliente_InitLista(sCliente listaClientes[], int limite)
{
    int retorno = -1;
    int i;

    if( listaClientes != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            listaClientes[i].flag_ocupado = INDICE_LIBRE;
            retorno=0;
        }

    }

    return retorno;
}
/** \brief imprime la estructura
 *
 * \param listaPantallas es el array
 * \param limite la cantidad de elementos para el array
 * \return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int info_PrintPantallas(sPantalla listaPantallas[], int limite)
{
    int retorno = -1;
    int i;
    if(listaPantallas != NULL && limite > 0)
    {
        printf("*************************************************************\n");
        printf("*~~~~~~~~~~~~~~~~PANTALLAS PARA IMPRIMIR~~~~~~~~~~~~~~~~~~~~*\n");
        printf("*************************************************************\n");
        for(i=0; i<limite ; i++)
        {
            if(listaPantallas[i].flag_ocupado == INDICE_OCUPADO)
            {
                printf("\n-ID PANTALLA:\n%d\n\nDIRECCION:\n%s\n\nPRECIO:\n%.2f\n\n ",listaPantallas[i].idPantalla, listaPantallas[i].direccion,listaPantallas[i].precio);
            }
        }

    }
    return retorno;
}

/** \brief busca la posicion segun el Cuit recibido
 *
 * \param listaContrataciones es el array de la estructura sContratacion donde se va a buscar el CUIT recibido
 * \param len es el largo del array
 * \param texto es el puntero al cuit recibido para buscar
 * \return retorna la posicion donde se encontro el CUIT
 *
 */

int info_BuscarPosicionCUIT(sContratacion listaContrataciones[],int len, char texto[])
{
    int i;
    int retorno =-1;
    for (i=0; i<len; i++)
    {
        if (listaContrataciones[i].flag_ocupado == INDICE_OCUPADO )
        {
            if (strcmp(listaContrataciones[i].cuitCliente, texto) == 0)
            {
                retorno = i;
                break;

            }
        }
    }
    return retorno;
}

/** \brief lista (imprime) las contrataciones
 *
 * \param listaContrataciones es el array cuyo elementos se van a imprimir
 * \param limite es el largo del array recibido
 * \return retorno 0 si funciona, -1 si no.
 *
 */


int info_PrintContrataciones(sContratacion listaContrataciones[], int limite)
{
    int retorno = -1;
    int i;
    if(listaContrataciones != NULL && limite > 0)
    {
        printf("*************************************************************\n");
        printf("*~~~~~~~~~~~~~~~~~LISTA DE CONTRATACIONES~~~~~~~~~~~~~~~~~~~*\n");
        printf("*************************************************************\n");
        for(i=0; i<limite ; i++)
        {
            if(listaContrataciones[i].flag_ocupado == INDICE_OCUPADO)
            {
                retorno=0;
                printf("\n- ID CONTRATACION: \n%d\n DIAS:\n %d \n CUIT CLIENTE:\n%s\n NOMBRE DE ARCHIVO:\n %s\n ID PANTALLA RELACIONADA:\n %d \n",listaContrataciones[i].idContratacion, listaContrataciones[i].dias,listaContrataciones[i].cuitCliente,listaContrataciones[i].archivo,listaContrataciones[i].idPantallaRelacion );
            }
        }

    }
    return retorno;
}

/** \brief calcula el monto a pagar por un cliente, la consulta se realiza por el Cuit recibido
 *
 * \param listaContrataciones array de contrataciones
 * \param listaPantallas array de pantallas
 * \param lenContrataciones es el largo del array listaContrataciones
 * \param lenPantallas es el largo del array listaPantallas
 * \param bCUIT es el Cuit recibido que se consulta para calcular el monto.
 * \return retorno -1 si funciona mal. 0 si funciona correctamente
 *
 */


int info_CalcularMontoSegunCuit(sContratacion listaContrataciones[],sPantalla listaPantallas[], int lenContrataciones,int lenPantallas, char bCUIT[])
{
    int retorno=-1;
    int indexPantalla;
    int i;
    float monto;

    if(listaContrataciones != NULL && lenContrataciones > 0)
    {
        if(listaPantallas != NULL && lenPantallas > 0)
        {


            printf("CLIENTE:%s",bCUIT);
            for (i=0; i<lenContrataciones; i++)
            {
                if(strcmp(listaContrataciones[i].cuitCliente,bCUIT)== 0)
                {
                    indexPantalla = listaContrataciones[i].idPantallaRelacion;
                    monto = listaContrataciones[i].dias * listaPantallas[indexPantalla].precio;
                    printf("LA CONTRATACION: \n %d \n TIENE POR MONTO: \n %.2f\n ", listaContrataciones[i].idContratacion,monto);
                    retorno=0;
                }
            }

        }
    }


    return retorno;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


int info_ContratacionesPorClienteyMonto(sContratacion listaContrataciones[],sPantalla listaPantallas[], int lenContrataciones,int lenPantallas)
{
    sCliente listaClientes[LEN_CLIENTES];
    cliente_InitLista(listaClientes,LEN_CLIENTES);
    int i;
    //int acumulador;
    // int maximo;
    int j=1;
    int k;
    int pos;
    int retorno=-1;
    if(listaClientes != NULL && listaContrataciones != NULL && listaPantallas != NULL)
    {
        listaClientes[0].idCliente = cliente_generar_Proximo_Id(listaClientes,LEN_CLIENTES);
        //igualo el primer elemento
        strcpy(listaClientes[0].cuit,listaContrataciones[0].cuitCliente);
        //para recorrer clientes
        for (i=0; i<LEN_CLIENTES; i++)
        {
            //para recorrer contrataciones
            for(j=0; j<lenContrataciones; j++)
            {
                //si los elementos son iguales
                if (strcmp(listaClientes[i].cuit,listaContrataciones[j].cuitCliente)==0)
                {
                    //suma una posicion en el v de contrataciones para ese cliente
                    pos++;
                    //copia el idContratacion en el array del cliente
                    listaClientes[i].idContrataciones[pos][50]=listaContrataciones[j].idContratacion;
                    //sigue recorriendo la lista contrataciones

                }
                else if (strcmp(listaClientes[i].cuit,listaContrataciones[j].cuitCliente)!= 0)
                {
                    listaClientes[j].idCliente= cliente_generar_Proximo_Id(listaClientes,LEN_CLIENTES);
                    strcpy(listaClientes[j].cuit,listaContrataciones[j].cuitCliente);

                }
            }
        }


//        maximo= listaClientes[0].saldo;

        for (k=0; k<lenContrataciones; k++)
        {
            info_CalcularMontoSegunCuit(listaContrataciones,listaPantallas,lenContrataciones,lenPantallas,listaClientes[k].cuit);

        }
        retorno=0;
    }
    return retorno;
}

