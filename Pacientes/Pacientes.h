#ifndef PACIENTES
#define PACIENTES

#define NUM_MAXIMO_REG 1000
#define LINE printf("=========================\n")

typedef struct
{
    char id[25];
    char nombres[50];
    char apellidos[50];
    int edad;
    char sexo[29];
    char ciudad[200];
    char numTelefono[10];
    char observaciones[200];
} Paciente;

#endif