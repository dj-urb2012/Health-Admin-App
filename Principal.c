#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Utils\Funciones.c"
#include "Utils\Sesion.c"
#include "Pacientes\Pacientes.h"
#include "Pacientes\Pacientes.c"

void configurarSesion(void);
bool autenticarDatos(char p1[], char p2[]);
void iniciarSesion(void);
void verificarConfiguracionDeSesion(void);
void imprimirMenu(void);

int main(int argc, char const *argv[])
{
    //Verificar si existe un usuario creado
    verificarConfiguracionDeSesion();
    int opcion = 0;
    do
    {
        imprimirMenu();
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            system("cls");
            gestionPacientes();
            break;
        case 2: 
            system("cls");
            break;
        case 3: 
            system("cls");
            break;
        case 4:
            system("cls");
            break;
        case 5: 
            system("cls");
            break;
        case 6:
            system("cls");
            configuracionDeUsuario();
            break;
        case 7:
            system("cls");
            printf("\nSE HA CERRADO SESION\n");
            break;
        default:
            printf("\nOpcion invalida!\n");
            Sleep(1000);
            system("cls");
            break;
        }
    } while (opcion != 7);
    

    return 0;
}
