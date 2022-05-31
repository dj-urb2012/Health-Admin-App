#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//tamaño maximo de usuario y clave
#define MAX_USERNAME_SIZE 50
#define MAX_PASSWORD_SIZE 50

FILE* user;
FILE* passwd;
FILE* sesion;
char p1[MAX_USERNAME_SIZE];
char p2[MAX_PASSWORD_SIZE];

void configurarSesion(void)
{
    char usuario[MAX_USERNAME_SIZE];
    char contrasena[MAX_PASSWORD_SIZE];
    printf("Digite el nombre del usuario: ");
    scanf("%s", usuario);
    printf("Digite una contrasena: ");
    scanf("%s", contrasena);
    //Creacion de archivos binarios
    fopen_s(&user, "bin\\usuario.bin", "wb");
    fopen_s(&passwd, "bin\\contrasena.bin", "wb");
    //Detectar si hay error
    if(user == NULL || passwd == NULL)
    {
        printf("Error, no se pudo configurar la sesion\n");
        configurarSesion();
    }
    //Guardar datos
    fwrite(&usuario, MAX_USERNAME_SIZE, 1, user);
    fwrite(&contrasena, MAX_PASSWORD_SIZE, 1, passwd);
    printf("Bienvenido %s\n", usuario);
    fclose(user);
    fclose(passwd);
}

//Verificar si la clave y el usuario coinciden
bool autenticarDatos(char p1[], char p2[])
{
    char usuario[MAX_USERNAME_SIZE];
    char contrasena[MAX_PASSWORD_SIZE];
    int autenticador = 0;
    printf("usuario: ");
    scanf("%s", usuario);
    printf("contrasena: ");
    scanf("%s", contrasena);

    if(strcmp(usuario, p1) == 0) autenticador++;
    if(strcmp(contrasena, p2) == 0) autenticador++;

    if(autenticador == 2) return true;
    else return false; 

}
//Lee los datos de los archivos binarios y los autentica
void iniciarSesion(void)
{  
    bool puedeIniciarSesion = false;
    fopen_s(&user, "bin\\usuario.bin", "rb");
    fopen_s(&passwd, "bin\\contrasena.bin", "rb");
    fread(&p1, MAX_USERNAME_SIZE, 1, user);
    fread(&p2, MAX_PASSWORD_SIZE, 1, passwd);
    fclose(user);
    fclose(passwd);
    
    while(puedeIniciarSesion == false)
    {
        puedeIniciarSesion = autenticarDatos(p1, p2);
        system("cls");
        if(puedeIniciarSesion == false) printf("Usuario o contrasena invalidos\n");
    }
    printf("Bienvenido %s\n", p1);

}

//Detecta si existe un usuario creado, si no hay entonces crea uno
void verificarConfiguracionDeSesion(void)
{
    fopen_s(&sesion, "bin\\usuario.bin", "rb");
    if(sesion == NULL)
    {
        printf("CREANDO CONFIGURACION DE USUARIO...\n");
        configurarSesion();
    } 
    else iniciarSesion();
    fclose(sesion);
}

void configuracionDeUsuario(void)
{
    int op = 0;
    do 
    {
        printf("1. Cambiar nombre de usuario\n2. Cambiar contrasena\n");
        printf("3. Volver al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("cls");
            cambiarNombreUsuario();
            op = 4;
            break;
        case 2:
            system("cls");
            cambiarPasswd();
            op = 4;
            break;
        case 3:
            system("cls");
            op = 3;
            break;
        default:
            printf("Opcion invalida\n");
            break;
        }
    } while(op != 3);
}

//Autentica el usuario y cambia su nombre
void cambiarNombreUsuario(void)
{
    bool autenticador = false;
    //Variables que almacenan el nombre y el usuario para ser autenticadas
    char buffer1[MAX_USERNAME_SIZE];
    char buffer2[MAX_PASSWORD_SIZE];
    fopen_s(&user, "bin\\usuario.bin", "rb");
    fopen_s(&passwd, "bin\\contrasena.bin", "rb");
    fread(&buffer1, MAX_USERNAME_SIZE, 1, user);
    fread(&buffer2, MAX_PASSWORD_SIZE, 1, passwd);

    autenticador = autenticarDatos(buffer1, buffer2);
    if(autenticador == true) 
    {
        fclose(user);
        fopen_s(&user, "bin\\usuario.bin", "wb");
        char nuevoNomUsuario[MAX_USERNAME_SIZE];
        printf("Ingrese el nuevo nombre de usuario: ");
        scanf("%s", nuevoNomUsuario);
        fwrite(&nuevoNomUsuario, MAX_PASSWORD_SIZE, 1, user);
    } else
    {
        system("cls");
        printf("Usuario o contrasena incorrectos\n");
    }

    fclose(user);
    fclose(passwd);

}

//Autentica el usuario y cambia su constraseña
void cambiarPasswd()
{
    bool autenticador = false;
    //Variables que almacenan el nombre y el usuario para ser autenticadas
    char buffer1[MAX_USERNAME_SIZE];
    char buffer2[MAX_PASSWORD_SIZE];
    fopen_s(&user, "bin\\usuario.bin", "rb");
    fopen_s(&passwd, "bin\\contrasena.bin", "rb");
    fread(&buffer1, MAX_USERNAME_SIZE, 1, user);
    fread(&buffer2, MAX_PASSWORD_SIZE, 1, passwd);

    autenticador = autenticarDatos(buffer1, buffer2);
    if(autenticador == true) 
    {
        fclose(passwd);
        fopen_s(&passwd, "bin\\contrasena.bin", "wb");
        char nuevaContrasena[MAX_PASSWORD_SIZE];
        printf("Ingrese la nueva contrasena: ");
        scanf("%s", nuevaContrasena);
        fwrite(&nuevaContrasena, MAX_PASSWORD_SIZE, 1, passwd);
    } 
    else 
    {
        system("cls");
        printf("Usuario o contrasena incorrectos\n");
    }
    fclose(user);
    fclose(passwd);
}