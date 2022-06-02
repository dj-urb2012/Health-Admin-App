#include <stdio.h>
#include <string.h>
#include "Citas.h"

Citas registroCitas[NUM_MAX_CITAS];
Citas bufferCitas;
FILE* cantidadCitas;
FILE* archivoRegistroCitas;

int cantidadRegCitas = 0;

void actualizarRegistroCitas(void)
{
    fopen_s(&archivoRegistroCitas, "bin\\registroCitas.bin", "rb");
    if(archivoRegistroCitas == NULL) fopen_s(&archivoRegistroCitas, "bin\\registroCitas.bin", "wb");
    else fread(&registroCitas, sizeof(Citas) * cantidadRegCitas, 1, archivoRegistroCitas);
    fclose(archivoRegistroCitas);
}

void cargarCantidadCitas(void)
{
    fopen_s(&cantidadCitas, "bin\\cantidadCitas.bin", "rb");
    if(cantidadCitas == NULL) fopen_s(&cantidadCitas, "bin\\cantidadCitas.bin", "wb");
    else fread(&cantidadRegCitas, sizeof(int), 1, cantidadCitas);
    fclose(cantidadCitas);
}

void agregarCita(void)
{
    fopen_s(&archivoRegistroCitas, "bin\\registroCitas.bin", "ab");
    fopen_s(&cantidadCitas, "bin\\cantidadCitas.bin", "wb");
    printf("Ingrese la hora: ");
    scanf(" %[^\n]", bufferCitas.hora);
    printf("Ingrese la fecha: ");
    scanf(" %[^\n]", bufferCitas.fecha);
    printf("Ingrese el area donde sera atendido el paciente: ");
    scanf(" %[^\n]", bufferCitas.area);
    printf("Ingrese la ID del paciente: ");
    scanf(" %[^\n]", bufferCitas.pacienteID);
    printf("Ingrese el estado de la cita (pendiente / asistio / no asisitio)");
    scanf(" %[^\n]", bufferCitas.estado);
    cantidadRegCitas++;
    fwrite(&bufferCitas, sizeof(Citas), 1, archivoRegistroCitas);
    fwrite(&cantidadRegCitas, sizeof(int), 1, cantidadCitas);
    fclose(archivoRegistroCitas);
    fclose(cantidadCitas);
}

void citasNoAsistidas(void)
{
    for(int i = 0; i < cantidadRegCitas; i++)
    {
        if(strcmp("no asistio", registroCitas[i].estado) == 0)
        {
            DIV_LINEA;
            printf("Hora: %s\n", registroCitas[i].hora);
            printf("Fecha: %s\n", registroCitas[i].fecha);
            printf("Area: %s\n", registroCitas[i].area);
            printf("ID: %s\n", registroCitas[i].pacienteID);
            printf("Estado: %s\n", registroCitas[i].estado);
            DIV_LINEA;
        }
    }
}

void citasAsistidas(void)
{
    for(int i = 0; i < cantidadRegCitas; i++)
    {
        if(strcmp("asistio", registroCitas[i].estado) == 0)
        {
            DIV_LINEA;
            printf("Hora: %s\n", registroCitas[i].hora);
            printf("Fecha: %s\n", registroCitas[i].fecha);
            printf("Area: %s\n", registroCitas[i].area);
            printf("ID: %s\n", registroCitas[i].pacienteID);
            printf("Estado: %s\n", registroCitas[i].estado);
            DIV_LINEA;
        }
    }
}

void mostrarPendientes(void)
{
    for(int i = 0; i < cantidadRegCitas; i++)
    {
        if(strcmp("pendiente", registroCitas[i].estado) == 0)
        {
            DIV_LINEA;
            printf("Hora: %s\n", registroCitas[i].hora);
            printf("Fecha: %s\n", registroCitas[i].fecha);
            printf("Area: %s\n", registroCitas[i].area);
            printf("ID: %s\n", registroCitas[i].pacienteID);
            printf("Estado: %s\n", registroCitas[i].estado);
            DIV_LINEA;
        }
    }
}

void mostrarTodosRegistros(void)
{
    citasNoAsistidas();
    citasAsistidas();
    mostrarPendientes();
}

void menuMostrarCitas(void)
{
    int op = 0;
    do
    {
        printf("1. Mostrar todos los registros\n");
        printf("2. Citas donde el paciente no asisitio\n");
        printf("3. Citas donde el paciente asistio\n");
        printf("4. Mostrar citas pendientes\n");
        printf("5. Volver al menu de cita\n"); 
        printf("Ingrese una opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("cls");
            mostrarTodosRegistros();
            system("pause");
            system("cls");
            break;
        case 2: 
            system("cls");
            citasNoAsistidas();
            system("pause");
        system("cls");
            break;
        case 3:
            system("cls");
            citasAsistidas();
            system("pause");
        system("cls");
            break;
        case 4:
            system("cls");
            mostrarPendientes();
            system("pause");
            system("cls");
        case 5:
            op = 5;
            system("cls");
        default:
            system("cls");
            printf("Opcion invalida");
            break;
        }

    } while (op != 5);
    
}

void gestionCitas(void)
{
    cargarCantidadCitas();
    int op = 0;
    do
    {
        actualizarRegistroCitas();
        printf("1. Agregar una cita\n2. Mostrar Citas\n3. Volver al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("cls");
            agregarCita();
            break;
        case 2:
            system("cls");
            menuMostrarCitas();
        case 3:
            op = 3;
            system("cls");
            break;
        default:
            system("cls");
            printf("Opcion invalida\n");
            break;
        }
    } while (op != 3);
    
}
