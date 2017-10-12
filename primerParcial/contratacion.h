#ifndef CONTRATACION_H_INCLUDED
#define CONTRATACION_H_INCLUDED

typedef struct{
    int idContratacion;
    int flag_ocupado;
    int idPantallaRelacion;
    int dias;
    char cuitCliente[50];
    char archivo[50];
}sContratacion;


#endif // CONTRATACION_H_INCLUDED

#define INDICE_OCUPADO 0
#define INDICE_LIBRE 1
#include "pantalla.h"
#include "validar.h"


int cont_InitLista(sContratacion  listaContrataciones[], int limite);
int cont_obtenerEspacioLibre(sContratacion  listaContrataciones[],int limite);
int cont_generar_Proximo_Id(sContratacion listaContrataciones[], int len);
//int cont_BuscarChar(sContratacion listaContrataciones[],int len, char texto[]);
int cont_AgregarContratacion(sContratacion listaContrataciones[], int idPantalla, int index, int limite);
int cont_BorrarContratacion(sContratacion listaContrataciones[], int id,int limite);
//int cont_ContarbyMarca(sContratacion listaContrataciones[], int *contador1, int *contador2, int *contador3, int *contador4 ,int limite);
//void cont_graficoBarras(int cont18,int cont19a35,int cont35);
//void cont_ordenar_x_Hora(sContratacion listaContrataciones[],int limite);
int cont_BuscarChar(sContratacion listaContrataciones[],int len, char texto[]);

int cont_buscarIndexPorId(sContratacion listaContrataciones[],int len,int id);
int cont_modificarContratacion(sContratacion listaContrataciones[], sPantalla listaPantallas[],  int lenContratacion,int lenPantalla, int id );
