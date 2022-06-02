#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Citas.h"

char contenedorIDs[1000][20];
Citas registroCitas[NUM_MAX_CITAS];
Citas bufferCitas;
FILE* cantidadCitas;
FILE* archivoRegistroCitas;
FILE* archivoID;
FILE* cantidadPac;
int cantidadRegCitas = 0;
int cantPacientes;

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

int agregarCita(void)
{
    fopen_s(&archivoID, "bin\\IDs.bin", "rb");
    if(archivoID == NULL) 
    {
        printf("No hay pacientes registrados\n");
        system("pause");
        return 1;
    }
    else
    {
        fopen_s(&cantidadPac, "bin\\cantidadPacientes.bin", "rb");
        fread(&cantPacientes, sizeof(int), 1, cantidadPac);
        fread(&contenedorIDs, sizeof(contenedorIDs), 1, archivoID);
        printf("Ingrese la ID del paciente: ");
        scanf(" %[^\n]", bufferCitas.pacienteID);
        for(int i = 0; i < cantPacientes; i++)
        {
            if(strcmp(bufferCitas.pacienteID, contenedorIDs[i]) == 0)
            {
                fopen_s(&archivoRegistroCitas, "bin\\registroCitas.bin", "ab");
                fopen_s(&cantidadCitas, "bin\\cantidadCitas.bin", "wb");
                printf("Ingrese la hora: ");
                scanf(" %[^\n]", bufferCitas.hora);
                printf("Ingrese la fecha: ");
                scanf(" %[^\n]", bufferCitas.fecha);
                printf("Ingrese el area donde sera atendido el paciente: ");
                scanf(" %[^\n]", bufferCitas.area);
                strcpy(bufferCitas.estado, "pendiente");
                cantidadRegCitas++;
                fwrite(&bufferCitas, sizeof(Citas), 1, archivoRegistroCitas);
                fwrite(&cantidadRegCitas, sizeof(int), 1, cantidadCitas);
                fclose(archivoRegistroCitas);
                fclose(cantidadCitas);
                system("cls");
                return 0;
            }
            else 
            {
                printf("Paciente no registrado\n");
                system("pause");
            }
           
        }
    }
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
            break;
        default:
            system("cls");
            printf("Opcion invalida\n");
            break;
        }

    } while (op != 5);
    
}

void cambiarEstadoCita(void)
{
    fopen_s(&archivoRegistroCitas, "bin\\registroCitas.bin", "wb");
    char idEstado[20];
    char nuevoEstado[30];
    bool citaExiste = false;
    int indice = 0;
    printf("Ingrese la ID del paciente: ");
    scanf(" %[^\n]", idEstado);
    for(int i = 0; i < cantidadRegCitas; i++)
    {
        if(strcmp(idEstado, registroCitas[i].pacienteID) == 0)
        {
            citaExiste = true;
            indice = i;
        }
    }
    if(citaExiste = true)
    {
        printf("Ingrese el estado de la cita (asistio / no asistio) ");
        scanf(" %[^\n]", nuevoEstado);
        strcpy(registroCitas[indice].estado, nuevoEstado);
        fwrite(&registroCitas, sizeof(Citas) * cantidadRegCitas, 1, archivoRegistroCitas);
    } else printf("La cita no esta registrada\n");
    fclose(archivoRegistroCitas);
}

void gestionCitas(void)
{
    cargarCantidadCitas();
    int op = 0;
    do
    {
        actualizarRegistroCitas();
        printf("1. Agregar una cita\n2. Mostrar Citas\n3. Editar estado de cita\n4. Volver al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("cls");
            agregarCita();
            system("cls");
            break;
        case 2:
            system("cls");
            menuMostrarCitas();
            break;
        case 3:
            system("cls");
            cambiarEstadoCita();
            system("cls");
            break;
        case 4:
            op = 4;
            system("cls");
            break;
        default:
            system("cls");
            printf("Opcion invalida\n");
            break;
        }
    } while (op != 4);
    
}
