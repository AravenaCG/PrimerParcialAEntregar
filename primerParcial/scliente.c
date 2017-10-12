#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "validar.h"
#include "pantalla.h"
#include "contratacion.h"
#include "informes.h"
#include "scliente.h"


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


/**
 * Obtiene el primer indice libre del array.
 * @param lista el array se pasa como parametro.
 * @return el primer indice disponible
 */
int cliente_obtenerEspacioLibre(sCliente  listaClientes[],int limite)
{

    int retorno = -1;
    int i;
    if(listaClientes != NULL && limite > 0)
    {
        for(i=0; i<limite ; i++)
        {
            if(listaClientes[i].flag_ocupado == INDICE_LIBRE)
            {
                retorno =  i;
                break;
            }
        }

    }
    return retorno;

}
