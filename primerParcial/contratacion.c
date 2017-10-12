#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "validar.h"
#include "contratacion.h"
#include "pantalla.h"
#include "informes.h"




/** \brief idAutoincrementable
 *
 * \param listaContrataciones es el array, recibe puntero al inicio del array
 * \param len es la cantidad de elementos del array
 * \return retorna el ultimo valor para utilizar en Id
 *
 */

int cont_generar_Proximo_Id(sContratacion listaContrataciones[], int len)
{
    static int ultimoValorIdAutoincrementable = -1;
    ultimoValorIdAutoincrementable ++;
    return ultimoValorIdAutoincrementable;

}


/** \brief Inicializa la lista
 *
 * \param listaContrataciones recibe puntero al inicio del array
 * \param limite es la cantidad de elementos del array
 * \return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int cont_InitLista(sContratacion  listaContrataciones[], int limite)
{
    int retorno = -1;
    int i;

    if( listaContrataciones != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            listaContrataciones[i].flag_ocupado = INDICE_LIBRE;
            retorno=0;
        }

    }

    return retorno;
}

/**
 * Obtiene el primer indice libre del array.
 * @param listaContrataciones el array se pasa como parametro.
 * @return el primer indice disponible
 */
int cont_obtenerEspacioLibre(sContratacion  listaContrataciones[],int limite)
{

    int retorno = -1;
    int i;
    if(listaContrataciones != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            if(listaContrataciones[i].flag_ocupado == INDICE_LIBRE)
            {
                retorno = i;
                break;
            }
        }

    }
    return retorno;

}

/**--------------------------------------------------------------------------------------------------
*-----------------------------------------------------------------------------------------------*/


/** \brief Agrega una contratacion a la lista
 *
 * @param  index el indice en el array, es decir la posicion.
 * @param  limite cantidad de elementos en el array
 * @return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int cont_AgregarContratacion(sContratacion listaContrataciones[], int idPantalla,int index, int limite)
{
    int retorno =-1;
    char bDias[50];
    char cuit[50];
    char nombreArchivo[50];

    if(listaContrataciones != NULL && index >= 0 && index <limite)
    {

        if  (val_getUnsignedInt(bDias,"\nIngrese cantidad de dias:\n","\nError:\n",3,50)==0 )
        {
            if (val_getCuit(cuit,"\n Ingrese el CUIT del Cliente: \n(** Formato: xx-xxxxxxxx/x  **) \n","CUIT NO VALIDO\n",3,50)== 0)
            {
                if (val_getNombreArchivo(nombreArchivo,"\nIngrese el nombre del archivo para reproducir\n","\nArchivo no valido\n",3,50)==0)
                {
                    listaContrataciones[index].dias = atoi(bDias);
                    strncpy(listaContrataciones[index].archivo,nombreArchivo,50);
                    strncpy(listaContrataciones[index].cuitCliente,cuit,50);
                    listaContrataciones[index].idContratacion = cont_generar_Proximo_Id(listaContrataciones,limite);
                    listaContrataciones[index].flag_ocupado = INDICE_OCUPADO;
                    listaContrataciones[index].idPantallaRelacion = idPantalla;
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}

/** \brief modifica un elemento del array
 *
 * @param  listaContrataciones es el puntero al array que contiene las contrataciones donde buscar la que se modificara.
 * @param  listaPantallas es el puntero al array que contiene las pantallas para poder elegir que contratacion modificar.
 * @param  lenContratacion cantidad de elementos en el array de contrataciones
 * @param  lenPantallas cantidad de elementos en el array de pantallas
 * @param  id elementos a modificar en el array
 * @return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */
int cont_modificarContratacion(sContratacion listaContrataciones[], sPantalla listaPantallas[],  int lenContratacion,int lenPantalla, int id )
{

    int retorno=-1;
    int index;
    char bOpcion[50];
    char bEleccionPantalla[50];
    int eleccionPantalla;
    char bDias[50];
    char cuit[14];
    char nombreArchivo[50];

    if (cont_buscarIndexPorId(listaContrataciones,lenContratacion, id) != -1)
    {
        index = cont_buscarIndexPorId(listaContrataciones,lenContratacion,id);
    }
    if (index >=0)
    {
        val_getUnsignedInt(bOpcion, "\nIngrese el campo a modificar: \n 1)-DIAS:\n2)-CUIT CLIENTE:\n3)NOMBRE DE ARCHIVO:\n4)-ID PANTALLA RELACIONADA:\n5)TODO\n","\nOpcion no valida!",3,50);
        switch(atoi(bOpcion))
        {
        case 1:

            if  (val_getUnsignedInt(bDias,"\nIngrese cantidad de dias:\n","\nError:\n",3,50)==0 )
            {
                listaContrataciones[index].dias = atoi(bDias);
            }
            break;
        case 2:
            if (val_getCuit(cuit,"\n Ingrese el CUIT del Cliente: \n(** Formato: xx-xxxxxxxx/x  **) \n","CUIT NO VALIDO\n",3,50)== 0)
            {
                strncpy(listaContrataciones[index].cuitCliente,cuit,50);
            }
            break;
        case 3:
             if (val_getNombreArchivo(nombreArchivo,"\nIngrese el nombre del archivo para reproducir\n","\nArchivo no valido\n",3,50)==0)
                {
                    strncpy(listaContrataciones[index].archivo,nombreArchivo,50);
                }
                break;
        case 4:
           info_PrintPantallas(listaPantallas,lenPantalla);
           val_getUnsignedInt(bEleccionPantalla,"\nIngrese la pantalla seleccionada:\n","ERROR!",3,50);
           eleccionPantalla= atoi(bEleccionPantalla);
           if (pant_buscarIndexPorId(listaPantallas,lenPantalla, eleccionPantalla)!= -1)
           {
                listaContrataciones[index].idPantallaRelacion = eleccionPantalla;
           }
           break;
        case 5:
           info_PrintPantallas(listaPantallas,lenPantalla);
           val_getUnsignedInt(bEleccionPantalla,"\nIngrese la pantalla seleccionada:\n","ERROR!",3,50);
           eleccionPantalla= atoi(bEleccionPantalla);
           if (pant_buscarIndexPorId(listaPantallas,lenPantalla, eleccionPantalla)!= -1)
           {
                cont_AgregarContratacion(listaContrataciones,eleccionPantalla,id,lenContratacion);
           }
           break;

        }
    }



    return retorno;


}



/** \brief busca un id en la lista
 * @param  listaContrataciones el array donde busca
 * @param  len cantidad de elementos en el array
  * @param  id el elemento a buscar
 * @return retorno :posicion donde se encontro o -1 si no se encontro
 *
 */
int cont_buscarIndexPorId(sContratacion listaContrataciones[],int len,int id)
{
    int i;
    int retorno=-1;
    if (listaContrataciones != NULL && len >0 && id >0 )
    {
        for (i=0; i<len; i++)
        {
            if (listaContrataciones[i].flag_ocupado == INDICE_OCUPADO)
            {


                if (id == listaContrataciones[i].idContratacion)
                {
                    retorno=i;
                    break;

                }
            }
        }
    }
    return retorno;
}

/** \brief pone el estado del elemento en libre para "borrarlo"
 *
 * \param listaContrataciones es el array que recibe
 * \param limite la cantidad de elementos para el array
 * @param  idABorrar es el elemento a eliminar
 * \return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int cont_BorrarContratacion(sContratacion listaContrataciones[], int idABorrar,int limite)
{
    int retorno = -1;
    int i = 0;

    if(listaContrataciones != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            if(listaContrataciones[i].flag_ocupado == INDICE_OCUPADO && listaContrataciones[i].idContratacion == idABorrar)
            {
                listaContrataciones[i].flag_ocupado = INDICE_LIBRE;
                printf("\nContratacion Eliminada!!!\n");
                retorno=0;
            }
        }

    }



    return retorno;
}

