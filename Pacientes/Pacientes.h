#ifndef PACIENTES
#define PACIENTES

#define NUM_MAXIMO_REG 1000
#define LINE printf("=========================\n")

typedef struct
{
    char id[20];
    char nombres[50];
    char apellidos[50];
    int edad;
    char sexo[30];
    char ciudad[20];
    char numTelefono[10];
    char observaciones[200];
} Paciente;

#endif