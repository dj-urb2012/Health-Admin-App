#ifndef CITAS
#define CITAS

#define NUM_MAX_CITAS 1000
#define DIV_LINEA printf("=========================\n")
typedef struct
{
    char hora[10];
    char fecha[40];
    char area[40];
    char pacienteID[20];
    char estado[20];
} Citas;


#endif