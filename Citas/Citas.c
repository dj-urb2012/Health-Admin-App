#include<stdio.h>

struct Cita
{
    char hora[10];
    char fecha[40];
    char area[40];
} citas[100];

int main(int argc, char const *argv[])
{
    
    int cantidad = 0;

    printf("¿Cuántos citas desea almacenar?");
    scanf("%i", &cantidad);

    for(int i = 0; i < cantidad; i++){
        printf("Hora: ");
        scanf("%i", &citas[i].hora);
        printf("Fecha: ");
        scanf(" %[^\n]", citas[i].fecha);
        printf("Área: ");
        scanf(" %[^\n]", citas[i].area);
    }
    
    printf("Imprimiendo lista \n");
    for(int i = 0; i<cantidad; i++){
        printf("Hora: %i\n", citas[i].hora);
        printf("Fecha: %s\n", citas[i].fecha);
        printf("Área: %s\n", citas[i].area);
        printf("==============================================\n");
    }
    return 0;
}
