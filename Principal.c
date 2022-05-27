#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdbool.h>
#include <string.h>
#include "Utils\Funciones.c"
#include "Utils\Sesion.c"

void configurarSesion(void);
bool autenticarDatos(char p1[], char p2[]);
void iniciarSesion(void);
void verificarConfiguracionDeSesion(void);
void imprimirMenu(void);

int main(int argc, char const *argv[])
{
    int opcion = 0;
    do
    {
        verificarConfiguracionDeSesion();
        imprimirMenu();
        printf("Ingrese una opcion\n> ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            break;
        case 2: 
            break;
        case 3: 
            break;
        case 4:
            break;
        case 5: 
            break;
        case 6:
            configuracionDeUsuario();
            break;
        case 7:
            printf("\nSE HA CERRADO SESION\n");
            break;
        default:
            printf("\nOpcion invalida!");
            Sleep(1000);
            system("cls");
            break;
        }
    } while (opcion != 7);
    

    return 0;
}
