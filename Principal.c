#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdbool.h>
#include "Utils\Funciones.c"
#include "Utils\Sesion.c"

void imprimirMenu(void);

int main(int argc, char const *argv[])
{
    int opcion = 0;
    do
    {
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
            printf("_=SE HA CERRADO SESION=_");
            break;
        default:
            printf("\nOpcion invalida!");
            Sleep(1000);
            system("cls");
            break;
        }
    } while (opcion != 6);
    

    return 0;
}
