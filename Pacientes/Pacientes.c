#include<stdio.h>

struct Paciente
{
    int id;
    char nombre[30];
    int edad[3];
    char sexo[10];
    char direccionCasa[200];
} citas[100];

int main(int argc, char const *argv[])
{
    int cantidad = 0;

    printf("¿Cuántos citas desea almacenar?");
    scanf("%i", &cantidad);

    for(int i = 0; i < cantidad; i++){
        printf("Id: ");
        scanf("%i", &citas[i].id);
        printf("Nombre: ");
        scanf(" %[^\n]", citas[i].nombre);
        printf("Edad: ");
        scanf(" %[^\n]", citas[i].edad);
        printf("Sexo: ");
        scanf("%f", &citas[i].sexo);
        printf("Dirección: ");
        scanf("%f", &citas[i].direccionCasa);
    }
    
    printf("Imprimiendo lista \n");
    for(int i = 0; i<cantidad; i++){
        printf("Id: %i\n", citas[i].id);
        printf("Nombre: %s\n", citas[i].nombre);
        printf("Edad: %s\n", citas[i].edad);
        printf("Sexo: %.2f\n", citas[i].sexo);
        printf("Dirección: %.2f\n", citas[i].direccionCasa);
        printf("==============================================\n");
    }
    return 0;
}
