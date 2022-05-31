#include <stdio.h>
#include <time.h>
#include "Pacientes.h"

FILE* archivo;
FILE* archivoPacientes;
FILE* arregloID;
Paciente registroPacientes[NUM_MAXIMO_REG];
Paciente buffer;

char IDs[NUM_MAXIMO_REG][20];
int cantidadPacientes;

int numeroRandom(void)
{
    srand(time(NULL));
    return rand() % 1001;
}

//Genera y retorna una ID unica
//Verifica si la ID ya existe, de lo contrario se llama otra vez hasta que
//se verifque que es unica
const char* generarID(void)
{
    fopen_s(&arregloID, "bin\\IDs.bin", "ab");
    int random = numeroRandom();
    char randIntString[10];
    sprintf(randIntString, "%d", random);
    char *ID;
    strcpy(ID, "PAC-");
    strcat(ID, randIntString);
    if(cantidadPacientes == 0)
    {
        //Cuando no existe ningun usuario
        strcpy(IDs[0], ID);
        fwrite(&IDs, sizeof(IDs), 1, arregloID);
        fclose(arregloID);
        return ID;
    }
    else
    {
        for(int i = 0; i < cantidadPacientes; i++)
        {
            if(strcmp(ID, IDs[i]) == 0)
            {
                //recursividad
                generarID();
            }
        }
        strcpy(IDs[cantidadPacientes], ID);
        fwrite(&IDs, sizeof(IDs), 1, arregloID);
        fclose(arregloID);
        return ID;
    }
}
//Lee los datos de pacientes fichero binario,
void actualizarRegistro(void)
{
    fopen_s(&archivoPacientes, "bin\\registroPacientes.bin", "rb");
    fread(&registroPacientes, sizeof(Paciente) * cantidadPacientes, 1, archivoPacientes);
    fclose(archivoPacientes);
}
//Carga la cantidad de pacientes a la variable global
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
//Carga las IDs para poder verificarlas cuando se intenta generar una nueva
void cargarIDs(void)
{
    fopen_s(&arregloID, "bin\\IDs.bin", "rb");
    if(arregloID == NULL)
    {   
        printf("NO SE PUDIERON CARGAR LOS DATOS, REGISTRE UN PACIENTE\n");
        fopen_s(&arregloID, "bin\\IDs.bin", "wb");
    }
    else 
    {
        fread(&IDs, sizeof(IDs), 1, arregloID);
    }
    fclose(arregloID);
}
//Agrega un paciente, guarda su informacion en un buffer y lo almacena en un fichero binario
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
    system("cls");
}
//Muestra todos los pacintes
void mostrarPacientes(void)
{
    fopen_s(&archivoPacientes, "bin\\registroPacientes.bin", "rb");
    if(archivo == NULL || archivoPacientes == NULL)
    {
        printf("Error\n");
    }
    else 
    {   
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
        system("pause");
        system("cls");
    }   
    fclose(archivoPacientes);
}
//Muestra un paciente que ha sido buscado con un parametro especifico
void resultadoBusqueda(int indice)
{
    LINE;
    printf("Nombres: %s\n", registroPacientes[indice].nombres);
    printf("Apellidos: %s\n", registroPacientes[indice].apellidos);
    printf("Edad: %d\n", registroPacientes[indice].edad);
    printf("Sexo: %s\n", registroPacientes[indice].sexo);
    printf("Tel: %s\n", registroPacientes[indice].numTelefono);
    printf("Lugar de residencia: %s\n", registroPacientes[indice].ciudad);
    printf("ID: %s\n", registroPacientes[indice].id);
    printf("OBSERVACIONES: %s\n", registroPacientes[indice].observaciones);
    LINE;
}

//Busca un paciente con un parametro especifico
void buscarPaciente(int parametroBusqueda)
{
    char bufferCadena[50];
    int bufferNumero;
    switch (parametroBusqueda)
    {
    case 1:
        printf("Ingrese los nombres: ");
        scanf(" %[^\n]", bufferCadena);
        system("cls");
        for(int i = 0; i < cantidadPacientes; i++)
        {
            if(strcmp(bufferCadena, registroPacientes[i].nombres) == 0)
            {
                resultadoBusqueda(i);
            }
        }
        system("pause");
        system("cls");
        break;
    case 2:
        printf("Ingrese la edad: ");
        scanf("%d", &bufferNumero);
        system("cls");
        for(int i = 0; i < cantidadPacientes; i++)
        {
            if(bufferNumero == registroPacientes[i].edad)
            {
                resultadoBusqueda(i);
            }
        }
        system("pause");
        system("cls");
        break;
    case 3:
        printf("Ingrese el sexo: ");
        scanf(" %[^\n]", bufferCadena);
        system("cls");
        for(int i = 0; i < cantidadPacientes; i++)
        {
            if(strcmp(bufferCadena, registroPacientes[i].sexo) == 0)
            {
                resultadoBusqueda(i);
            }
        }
        system("pause");
        system("cls");
        break;
    case 4:
        printf("Ingrese la ciudad: ");
        scanf(" %[^\n]", bufferCadena);
        system("cls");
        for(int i = 0; i < cantidadPacientes; i++)
        {
            if(strcmp(bufferCadena, registroPacientes[i].ciudad) == 0)
            {
                resultadoBusqueda(i);
            }
        }
        system("pause");
        system("cls");
        break;
    case 5:
        printf("Ingrese la ID: ");
        scanf(" %[^\n]", bufferCadena);
        system("cls");
        for(int i = 0; i < cantidadPacientes; i++)
        {
            if(strcmp(bufferCadena, registroPacientes[i].id) == 0)
            {
                resultadoBusqueda(i);
            }
        }
        system("pause");
        system("cls");
        break;
    default:
        system("cls");
        printf("Opcion invalida\n");
        break;
    }
}

//Muestra un menu con todos los parametros disponibles para buscar pacientes
void menuBuscarPaciente(void)
{
    int parametroDeBusqueda = 0;
    printf("1. Buscar por nombre\n2. Buscar por edad\n3. Buscar por sexo\n");
    printf("4. Buscar por ciudad\n5. Buscar por ID\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &parametroDeBusqueda);
    system("cls");
    buscarPaciente(parametroDeBusqueda);
}
//Funcion principal del modulo
void gestionPacientes(void)
{
    cargarCantidadPacientes();
    cargarIDs();
    int op = 0;
    do
    {
        actualizarRegistro();
        printf("1. Agregar paciente\n2. Mostrar Pacientes\n3. Buscar paciente\n");
        printf("4. Volver al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("cls");
            agregarPaciente();
            break;
        case 2:
            system("cls");
            mostrarPacientes();
            break;    
        case 3:
            system("cls");
            menuBuscarPaciente();
            break;
        case 4:
            system("cls");
            op = 4;
            break;
        default:
            printf("Opcion invalida\n");
            break;
        }
    } while (op != 4);
    
}
