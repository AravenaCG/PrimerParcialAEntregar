#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "validar.h"
#include "pantalla.h"
#include "contratacion.h"
#include "informes.h"

/** \brief idAutoincrementable
 *
 * \param arrayLista recibe puntero al inicio del array
 * \param len es la cantidad de elementos del array
 * \return retorna el ultimo valor para utilizar en Id
 *
 */

int pant_generar_Proximo_Id(sPantalla listaPantallas[], int len)
{
    static int ultimoValorIdAutoincrementable = -1;
    ultimoValorIdAutoincrementable ++;
    return ultimoValorIdAutoincrementable;

}


/** \brief Inicializa la lista
 *
 * \param arrayLista recibe puntero al inicio del array
 * \param limite es la cantidad de elementos del array
 * \return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int pant_InitLista(sPantalla listaPantallas[], int limite)
{
    int retorno = -1;
    int i;

    if( listaPantallas != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            listaPantallas[i].flag_ocupado = INDICE_LIBRE;
            retorno=0;
        }

    }

    return retorno;
}

/**
 * Obtiene el primer indice libre del array.
 * @param lista el array se pasa como parametro.
 * @return el primer indice disponible
 */
int pant_obtenerEspacioLibre(sPantalla  listaPantallas[],int limite)
{

    int retorno = -1;
    int i;
    if(listaPantallas != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            if(listaPantallas[i].flag_ocupado == INDICE_LIBRE)
            {
                retorno =  i;
                break;
            }
        }

    }
    return retorno;

}




 /**---------------------------------------------------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------------------*/
/** \brief Agrega persona a la lista
 *
 * @param  index el indice en el array, es decir la posicion.
 * @param  limite cantidad de elementos en el array
 * @return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */
int pant_AgregarPantalla(sPantalla listaPantallas[], int index, int limite)
{
    char bTipoPantalla[20];
    int retorno = -1;
    char bNombre[50];
    char bDireccion[50];
    char bPrecio[50];
    float precio;



    if(listaPantallas != NULL && index >= 0 && index <limite)
    {
        if(val_getNombre(bNombre,"\nNOMBRE PANTALLA?\n","\nError:\n",3,50)==0)
        {
            if  (val_getDireccion(bDireccion,"\nDireccion PANTALLA?:\n","\nError:\n",3,50)==0 )
            {
                getStringNumerosFlotantes("\ningrese el precio de la publicacion: \n",bPrecio);
                val_getUnsignedInt(bTipoPantalla,"\n Ingrese el tipo de pantalla: \n1)LED \n 2)LCD\n","Error",3,20);
                precio= atof(bPrecio);
                strncpy(listaPantallas[index].nombre,bNombre,50);
                strncpy(listaPantallas[index].direccion,bDireccion,50);
                listaPantallas[index].precio= precio;
                listaPantallas[index].idPantalla = pant_generar_Proximo_Id(listaPantallas,limite);
                listaPantallas[index].flag_ocupado = INDICE_OCUPADO;

                listaPantallas[index].tipoPantalla = atoi(bTipoPantalla);
                retorno=0;
            }
        }
    }

return retorno;
}

/** \brief modifica un elemento del array
 *
 * @param  index el indice en el array, es decir la posicion.
 * @param  len cantidad de elementos en el array
 * @param  id elementos a modificar en el array
 * @return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */
int pant_modificarPantalla(sPantalla listaPantallas[], int len, int id )
{

    int retorno=-1;
    int index;


        if (pant_buscarIndexPorId(listaPantallas,len, id) != -1)
        {
            index = pant_buscarIndexPorId(listaPantallas,len,id);
        }
        if (index >=0)
        {
            pant_AgregarPantalla(listaPantallas, index, len);
        }

    return retorno;
}



/** \brief busca un id en la lista
 * @param  listaPantallas el array donde busca
 * @param  len cantidad de elementos en el array
 * @param id es el identificador a buscar
 * @return retorno :posicion donde se encontro o -1 si no se encontro
 *
 */
int pant_buscarIndexPorId(sPantalla listaPantallas[],int len,int id)
{
    int i;
    int retorno=-1;
    if (listaPantallas != NULL && len >0 && id >=0 )
    {
        for (i=0; i<len; i++)
        {
            if (listaPantallas[i].flag_ocupado == INDICE_OCUPADO)
            {


                if (id == listaPantallas[i].idPantalla)
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
 * \param listaPantallas es el array que recibe
 * \param limite la cantidad de elementos para el array
 * \param idABorrar es el identificador que permite buscar el elemento a borrar
 * \return retorno : -1 (error) ; 0 (funciona correctamente)
 *
 */

int pant_BorrarPantalla(sPantalla listaPantallas[], int idABorrar,int limite)
{
    int retorno = -1;
    int i = 0;

    if(listaPantallas != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            if(listaPantallas[i].flag_ocupado == INDICE_OCUPADO && listaPantallas[i].idPantalla == idABorrar)
            {
                listaPantallas[i].flag_ocupado = INDICE_LIBRE;
                printf("\nPantalla Eliminada!!!\n");
                retorno=0;
            }
        }

    }



    return retorno;
}
