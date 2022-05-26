#include<stdio.h>

struct Hospitalizacion
{
    char estado[40];
    char observaciones[300];
} hospitalizaciones[100];

int main(int argc, char const *argv[])
{
    int cantidad = 0;

    printf("¿Cuántos pacientes para hospitalización desea almacenar?");
    scanf("%i", &cantidad);

    for(int i = 0; i < cantidad; i++){
        printf("Estado: ");
        scanf("%i", &hospitalizaciones[i].estado);
        printf("Observaciones: ");
        scanf(" %[^\n]", hospitalizaciones[i].observaciones);
    }
    
    printf("Imprimiendo lista \n");
    for(int i = 0; i<cantidad; i++){
        printf("Estado: %i\n", hospitalizaciones[i].estado);
        printf("Observaciones: %s\n", hospitalizaciones[i].observaciones);
        printf("==============================================\n");
    }
    return 0;
}
