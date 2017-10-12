#ifndef VALIDAR_H_INCLUDED
#define VALIDAR_H_INCLUDED



#endif // VALIDAR_H_INCLUDED

void myFgets(char* buffer, int limite ,FILE* archivo);

int val_getNombre(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_getFloat(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarNombre(char* buffer);
int val_validarFloat(char* buffer);
int val_getUnsignedInt(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_validarUnsignedInt(char* buffer);
int val_getInt(int* destino, char* mensaje,char* mensajeError,int intentos);
int val_validarEdad(int* destino, int edad_A_Validar, int intentos);
int val_validarDni(int* destino, int dni_A_Validar, int intentos);
char getNumeroAleatorio(int desde , int hasta, int iniciar);
int esNumericoFlotante(char str[]);
int esNumerico(char str[]);
int esSoloLetras(char str[]);
int esAlfaNumerico(char str[]);
int esTelefono(char str[]);
int getStringLetras(char mensaje[],char input[]);
int getStringNumeros(char mensaje[],char input[]);
int getStringNumerosFlotantes(char mensaje[],char input[]);
int getValidInt(char requestMessage[],char errorMessage[], int lowLimit, int hiLimit);
void clean_stdin(void);
void pause(char message[]);
char getChar(char mensaje[]);
int val_getAlfanumerico(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int esCuit(char str[]);
int esDireccion(char str[]);
int val_getDireccion(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_getCuit(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_getNombreArchivo(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int esNombreArchivo(char str[]);
