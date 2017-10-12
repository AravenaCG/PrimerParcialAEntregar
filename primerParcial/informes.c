#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pantalla.h"
#include "contratacion.h"
#include "validar.h"
#include "informes.h"

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
                printf("*************************************************************\n");
                printf("\n* ID PANTALLA:%d\n* DIRECCION:%s\n* PRECIO:%.2f\n",
                       listaPantallas[i].idPantalla,
                       listaPantallas[i].direccion,
                       listaPantallas[i].precio);
                if(listaPantallas[i].tipoPantalla == 1)
                {
                    printf( "\n* TIPO DE PANTALLA: LED\n");
                }
                else
                {
                    printf( "\n* TIPO DE PANTALLA: LCD\n");
                }
                printf("*************************************************************\n");
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
                printf("*************************************************************\n");
                printf("* CUIT CLIENTE:%s \n* ID CONTRATACION:%d\n* DIAS:%d\n* NOMBRE DE ARCHIVO:%s\n* ID PANTALLA RELACIONADA:%d\n",listaContrataciones[i].cuitCliente,
                       listaContrataciones[i].idContratacion,
                       listaContrataciones[i].dias,
                       listaContrataciones[i].archivo,
                       listaContrataciones[i].idPantallaRelacion);
                printf("*************************************************************\n");
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

            printf("*************************************************************\n");
            printf("*                      CLIENTE:%s              *",bCUIT);
            for (i=0; i<lenContrataciones; i++)
            {
                if(strcmp(listaContrataciones[i].cuitCliente,bCUIT)== 0)
                {
                    indexPantalla = listaContrataciones[i].idPantallaRelacion;
                    monto = listaContrataciones[i].dias * listaPantallas[indexPantalla].precio;
                    printf("* LA CONTRATACION: %d \n* TIENE POR MONTO:%.2f\n ", listaContrataciones[i].idContratacion,monto);
                    retorno=0;
                    printf("*************************************************************\n");
                }
            }

        }
    }


    return retorno;
}

/** \brief compara los Cuit de las contrataciones creando una listaClientes segun el CUIT sin que se repitan
 *
 * \param listaContrataciones es la lista de la estructura Contrataciones de la cual se encuentran los diferentes CUITS ingresados ya validados previamente
 * \param lenContrataciones es la dimension del array de contrataciones
 * \param listaClientes es la lista de la estructura Cliente donde se guardan los campos cuando se encuentra un CUIT nuevo o una Contratacion que pertenece a un CUIT ya existente
 * \param lenClientes es la dimension del array de clientes
 * \return -1 si no funciona. 0 si esta todo ok.
 *
 */

int info_CrearLista_Clientes_Por_Cuit(sContratacion listaContrataciones[],int lenContrataciones,sCliente listaClientes[],int lenClientes)
{
    int retorno=-1;
    int i;
    int j;
    int k;
    char buffCuit[50];
    int buffPosicion;
    int nuevaPosicion;
    int flag_existe;
    int idContratacionRelacion;
    int posicion_Array_idContrataciones=-1;
    for (i=0; i<lenContrataciones;i++)
    {
        strcpy(buffCuit,listaContrataciones[i].cuitCliente);
        for (j=0;j<lenContrataciones;j++)
        {
          if (strcmp(buffCuit,listaContrataciones[j].cuitCliente)!=0)
          {
              idContratacionRelacion=j;
              for (k=0;k<lenClientes;k++)
              {
                  if (strcmp(buffCuit,listaClientes[k].cuit)!=0)
                    {
                        flag_existe=1;
                        buffPosicion=k;
                        break;
                    }
                    else
                    {
                        nuevaPosicion=cliente_obtenerEspacioLibre(listaClientes,lenClientes);
                        listaClientes[nuevaPosicion].idCliente = cliente_generar_Proximo_Id(listaClientes,lenClientes);
                        listaClientes[nuevaPosicion].flag_ocupado = INDICE_OCUPADO;
                        strcpy(listaClientes[nuevaPosicion].cuit,buffCuit);
                        listaClientes[nuevaPosicion].idContrataciones[posicion_Array_idContrataciones+1]=idContratacionRelacion;
                    }
              }
              if (flag_existe==1)
              {
                  listaClientes[buffPosicion].idContrataciones[posicion_Array_idContrataciones+1]=idContratacionRelacion;
              }
          }
          else
          {
              printf("El CUIT:%s no tiene Contrataciones Activas",buffCuit);
          }

        }
    }
    return retorno;
}



/** \brief lista todas las contrataciones por Cliente segun el cuit para ver si tiene contrataciones activas
 *
 * \param lenContrataciones es la dimension del array de contrataciones
 * \param listaClientes es la lista de la estructura Cliente donde se guardan los campos cuando se encuentra un CUIT nuevo o una Contratacion que pertenece a un CUIT ya existente
 * \param lenClientes es la dimension del array de clientes
  * @param  listaPantallas el array donde busca
 * @param  lenPantallas cantidad de elementos en el array
 * \return -1 si no funciona. 0 si esta todo ok.
 *
 */

int info_ListarClientesYSusMontosSegunCuit(sContratacion listaContrataciones[],sPantalla listaPantallas[],sCliente listaClientes[], int lenClientes, int lenContrataciones,int lenPantallas)
{
    int retorno=-1;
    int indexMaximo=0;
    int indexPantalla;
    int i;
    int j;
    int k;
    float maximo=-1;
    float acumulador=0;
    float monto;

    if(listaContrataciones != NULL && lenContrataciones > 0)
    {
        if(listaPantallas != NULL && lenPantallas > 0)
        {
            if (listaClientes != NULL && lenClientes >0)
            {


                printf("*************************************************************\n");

                for (i=0; i<lenClientes; i++)
                {
                    printf("*                      CLIENTE:%s              *",listaClientes[i].cuit);

                    for (j=0; j<lenContrataciones; j++)
                    {
                        if(strcmp(listaContrataciones[j].cuitCliente,listaClientes[i].cuit)== 0)
                        {
                            indexPantalla = listaContrataciones[j].idPantallaRelacion;
                            monto = listaContrataciones[j].dias * listaPantallas[indexPantalla].precio;
                            printf("* LA CONTRATACION: %d \n* TIENE POR MONTO:%.2f\n ", listaContrataciones[i].idContratacion,monto);
                            retorno=0;

                            acumulador=acumulador + monto;

                        }
                         listaClientes[i].saldoTotal= acumulador;
                    }
                        printf("EL SALDO TOTAL DEL CLIENTE %s ES :%.2f" ,listaClientes[i].cuit,listaClientes[i].saldoTotal);
                        printf("*************************************************************\n");
                        printf("*************************************************************\n");

                }

                for (k=0;k<lenClientes;k++)
                {
                    if (listaClientes[k].saldoTotal>maximo)
                    {
                        maximo= listaClientes[k].saldoTotal;
                        indexMaximo = k;

                    }
                }
                        printf("EL Cliente con mas Deuda es: %s \n Con un monto total de: %.2f ", listaClientes[indexMaximo].cuit, maximo);
            }



        }


    }
    return retorno;
}
