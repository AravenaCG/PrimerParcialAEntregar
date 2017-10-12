#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED

typedef struct{
    int idCliente;
    int flag_ocupado;
    char nombre[50];
    char direccion[50];
    char cuit[50];
    char idContrataciones[4036][50];
    float saldo;
}sCliente;

#endif // INFORMES_H_INCLUDED

#include "pantalla.h"
#include "contratacion.h"
#include "validar.h"
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
int cliente_generar_Proximo_Id(sCliente listaClientes[], int len);

