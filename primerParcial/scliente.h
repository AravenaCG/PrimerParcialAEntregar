#ifndef SCLIENTE_H_INCLUDED
#define SCLIENTE_H_INCLUDED

typedef struct{
    int idCliente;
    int flag_ocupado;
    char cuit[50];
    char idContrataciones[4036];
    float saldoTotal;
}sCliente;

#endif // SCLIENTE_H_INCLUDED
#define INDICE_OCUPADO 0
#define INDICE_LIBRE 1


int cliente_generar_Proximo_Id(sCliente listaClientes[], int len);
int cliente_InitLista(sCliente listaClientes[], int limite);
int cliente_obtenerEspacioLibre(sCliente  listaClientes[],int limite);
