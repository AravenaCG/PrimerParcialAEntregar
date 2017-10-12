#ifndef PANTALLA_H_INCLUDED
#define PANTALLA_H_INCLUDED

typedef struct{
    int idPantalla;
    int flag_ocupado;
    char nombre[50];
    float precio;
    char direccion[50];
    int tipoPantalla;
}sPantalla;

#endif // PANTALLA_H_INCLUDED

#define LED 1
#define LCD 0
#define INDICE_OCUPADO 0
#define INDICE_LIBRE 1


int pant_InitLista(sPantalla  listaPantallas[], int limite);
int pant_obtenerEspacioLibre(sPantalla  listaPantallas[],int limite);
int pant_generar_Proximo_Id(sPantalla listaPantallas[], int len);
int pant_AgregarPantalla(sPantalla listaPantallas[], int index, int limite);
int pant_PrintPantallas(sPantalla listaPantallas[], int limite);
int pant_BorrarPantalla(sPantalla listaPantallas[], int idABorrar,int limite);
int pant_buscarIndexPorId(sPantalla listaPantallas[],int len, int id);
int pant_modificarPantalla(sPantalla listaPantallas[], int len, int id );
