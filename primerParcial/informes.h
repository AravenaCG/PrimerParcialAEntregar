#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED



#endif // INFORMES_H_INCLUDED

#include "pantalla.h"
#include "contratacion.h"
#include "validar.h"
#include "scliente.h"
#define LEN_CLIENTES 50
#define LEN_CONTRATACION 50


int info_PrintAutos(sContratacion listaContrataciones[], int limite);
int info_PrintPantallas(sPantalla listaPantallas[], int limite);
int info_BuscarPosicionCUIT(sContratacion listaContrataciones[],int len, char texto[]);
int info_ListarFacturacion(sContratacion listaContrataciones[],sPantalla listaPantallas[], int lenEntidad1,int lenEntidad2, char cuitCliente);
int info_PrintContrataciones(sContratacion listaContrataciones[], int limite);
int info_CalcularMontoSegunCuit(sContratacion listaContrataciones[],sPantalla listaPantallas[], int lenContrataciones,int lenPantallas,char bCUIT[]);
int info_ContratacionesPorClienteyMonto(sContratacion listaContrataciones[],sPantalla listaPantallas[], int lenContrataciones,int lenPantallas);
int pant_InitLista(sPantalla listaPantallas[], int limite);
int info_CrearLista_Clientes_Por_Cuit(sContratacion listaContrataciones[],int lenContrataciones,sCliente listaClientes[],int lenClientes);
int info_ListarClientesYSusMontosSegunCuit(sContratacion listaContrataciones[],sPantalla listaPantallas[],sCliente listaClientes[], int lenClientes, int lenContrataciones,int lenPantallas);


