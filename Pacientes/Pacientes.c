#include <stdio.h>
#include <time.h>
#include "Pacientes.h"

FILE* archivo;
FILE* archivoPacientes;
Paciente registroPacientes[NUM_MAXIMO_REG];
Paciente buffer;

int cantidadPacientes;

int numeroRandom(void)
{
    srand(time(NULL));
    return rand() % 1001;
}

const char* generarID(void)
{
    int random = numeroRandom();
    char randIntString[10];
    sprintf(randIntString, "%d", random);
    char *ID;
    strcpy(ID, "PAC-");
    strcat(ID, randIntString);
    return ID;
}

void cargarCantidadPacientes(void)
{
    fopen_s(&archivo, "bin\\cantidadPacientes.bin", "rb");
    if(archivo == NULL)
    {
        cantidadPacientes = 0;
        fopen_s(&archivo, "bin\\cantidadPacientes.bin", "wb");
        fwrite(&cantidadPacientes, sizeof(int), 1, archivo);
    } else fread(&cantidadPacientes, sizeof(int), 1, archivo);
    fclose(archivo);
}

void agregarPaciente(void)
{
    fopen_s(&archivo, "bin\\cantidadPacientes.bin", "wb");
    fopen_s(&archivoPacientes, "bin\\registroPacientes.bin", "ab");
    strcpy(buffer.id, generarID());
    printf("Ingrese los nombres del paciente: ");
    scanf(" %[^\n]", buffer.nombres);
    printf("Ingrese los apellidos del paciente: ");
    scanf(" %[^\n]", buffer.apellidos);
    printf("Ingrese la edad del paciente: ");
    scanf("%d", &buffer.edad);
    printf("Ingrese el sexo del paciente: ");
    scanf(" %[^\n]", buffer.sexo);
    printf("Ingrese el numero telefonico: ");
    scanf(" %[^\n]", buffer.numTelefono);
    printf("Ingrese la ciudad donde el paciente reside: ");
    scanf(" %[^\n]", buffer.ciudad);
    printf("OBSERVACIONES: ");
    scanf(" %[^\n]", buffer.observaciones);
    
    cantidadPacientes++;
    //Guardar datos

    fwrite(&cantidadPacientes, sizeof(int), 1, archivo);
    fwrite(&buffer, sizeof(Paciente), 1, archivoPacientes);

    fclose(archivo);
    fclose(archivoPacientes);
}

void mostrarPacientes(void)
{
    fopen_s(&archivo, "bin\\cantidadPacientes.bin", "rb");
    fopen_s(&archivoPacientes, "bin\\registroPacientes.bin", "rb");
    if(archivo == NULL || archivoPacientes == NULL)
    {
        printf("Por favor registre un paciente\n");
    }
    else 
    {   
        fread(&cantidadPacientes, sizeof(int), 1, archivo);
        fread(&registroPacientes, sizeof(Paciente) * cantidadPacientes, 1, archivoPacientes);
        for(int i = 0; i < cantidadPacientes; i++)
        {
            LINE;
            printf("Nombres: %s\n", registroPacientes[i].nombres);
            printf("Apellidos: %s\n", registroPacientes[i].apellidos);
            printf("Edad: %d\n", registroPacientes[i].edad);
            printf("Sexo: %s\n", registroPacientes[i].sexo);
            printf("Tel: %s\n", registroPacientes[i].numTelefono);
            printf("Lugar de residencia: %s\n", registroPacientes[i].ciudad);
            printf("ID: %s\n", registroPacientes[i].id);
            printf("OBSERVACIONES: %s\n", registroPacientes[i].observaciones);
            LINE;
        }
    }   
    fclose(archivo);
    fclose(archivoPacientes);
}

void gestionPacientes(void)
{
    cargarCantidadPacientes();
    int op = 0;
    do
    {
        printf("1. Agregar paciente\n2. Mostrar Pacientes\n3. Buscar paciente\n");
        printf("4. Volver al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            agregarPaciente();
            break;
        case 2:
            mostrarPacientes();
            break;    
        case 3:
            //buscarPaciente();
        case 4:
            op = 4;
        default:
            printf("Opcion invalida\n");
            break;
        }
    } while (op != 4);
    
}
