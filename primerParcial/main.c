#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pantalla.h"
#include "contratacion.h"
#include "validar.h"
#include "informes.h"
#define LEN_PANTALLA  50
#define LEN_CONTRATACION 50


int main()
{

   char bufferOpcion[50];
    char bufferIdABorrar[50];
    char bufferIdAModificar[50];
    char bEleccionPantalla[50];
    char bufferCuit[50];
    int eleccionPantalla;
    int idPantallaAModificar;
    int idPantallaABorrar;
    int idContraAModificar;
    int idContra_A_Borrar;



    sPantalla listaPantallas[LEN_PANTALLA];
    sContratacion listaCOntrataciones[LEN_CONTRATACION];
    pant_InitLista(listaPantallas, LEN_PANTALLA);
    cont_InitLista(listaCOntrataciones,LEN_CONTRATACION);

    do
    {
        val_getUnsignedInt(bufferOpcion,"\n1- ALTA PANTALLA\n \n2- MODIFICAR PANTALLA\n \n3- BAJA PANTALA\n\n4- CONTRATAR PUBLICIDAD \n\n5- MODIFICAR COND. PUBLICACION \n \n6- CANCELAR CONTRATACION \n\n7- CONSULTAR FACTURACION \n\n8- LISTAR CONTRATACIONES \n\n9- LISTAR PANTALLAS\n\n10- INFORMAR\n","error",2,40);
        switch(atoi(bufferOpcion))
        {
        case 1:

            pant_AgregarPantalla(listaPantallas,pant_obtenerEspacioLibre(listaPantallas,LEN_PANTALLA),LEN_PANTALLA);

            break;

        case 2:
            val_getUnsignedInt(bufferIdAModificar,"\nIngrese el ID de la pantalla a modificar:\n","ID NO VALIDO!!\n",3,50);
            idPantallaAModificar = atoi(bufferIdAModificar);
            memset(bufferIdAModificar, 0, sizeof(bufferIdAModificar));
            pant_modificarPantalla(listaPantallas,LEN_PANTALLA ,idPantallaAModificar);


            break;

        case 3:
            val_getUnsignedInt(bufferIdABorrar,"\n Ingrese el ID de la Pantalla a Borrar : \n ", "ID NO VALIDO", 3, 50);
            idPantallaABorrar = atoi(bufferIdABorrar);
            memset(bufferIdABorrar, 0, sizeof(bufferIdABorrar));
            pant_BorrarPantalla(listaPantallas,idPantallaABorrar,LEN_PANTALLA);
            break;

        case 4:
           info_PrintPantallas(listaPantallas,LEN_PANTALLA);
           val_getUnsignedInt(bEleccionPantalla,"\nIngrese la pantalla seleccionada:\n","ERROR!",3,50);
           eleccionPantalla= atoi(bEleccionPantalla);
           if (pant_buscarIndexPorId(listaPantallas,LEN_PANTALLA, eleccionPantalla)!= -1)
           {
               cont_AgregarContratacion(listaCOntrataciones, eleccionPantalla,cont_obtenerEspacioLibre(listaCOntrataciones,LEN_CONTRATACION),LEN_CONTRATACION);
           }

            break;

        case 5:
            val_getUnsignedInt(bufferIdAModificar,"\nIngrese el ID de Contratacion a modificar:\n","\nERROR ID!!\n",3,50);
            idContraAModificar =atoi(bufferIdAModificar);
            memset(bufferIdAModificar, 0, sizeof(bufferIdAModificar));
            cont_modificarContratacion(listaCOntrataciones,listaPantallas,  LEN_CONTRATACION, LEN_PANTALLA,idContraAModificar);

            break;
        case 6:
            val_getUnsignedInt(bufferIdABorrar,"\nIngrese el ID de la Contratacion a Cancelar:\n","\nID NO VALIDO!!\n",3,50);
            idContra_A_Borrar= atoi(bufferIdABorrar);
            memset(bufferIdABorrar, 0, sizeof(bufferIdABorrar));
            cont_BorrarContratacion(listaCOntrataciones,idContra_A_Borrar,LEN_CONTRATACION);
            break;
        case 7:
            if (val_getCuit(bufferCuit,"\nIngrese el CUIT del Cliente a consultar:\n","\nCLIENTE NO VALIDO!:\n",3,50) != -1)
            info_CalcularMontoSegunCuit(listaCOntrataciones,listaPantallas,LEN_CONTRATACION,LEN_PANTALLA, bufferCuit);
            break;
        case 8:
            info_PrintContrataciones(listaCOntrataciones,LEN_CONTRATACION);
            break;
        case 9:
            info_PrintPantallas(listaPantallas,LEN_PANTALLA);
            break;
        case 10:

            break;
        }
    }
    while(atoi(bufferOpcion) != 11);

    return 0;
}
