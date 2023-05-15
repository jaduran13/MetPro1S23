#include <iostream>
#include <stdio.h>
#include <string.h>
#include "auxiliar.h"
#define MAX 100
using namespace std;

typedef struct
{
    int dia;
    int mes;
    int año;
} fecha;

typedef struct
{
    char idUca[9];
    char nombre[30];
    char apellido[30];
    int año;
    char email[100];
    fecha fechaNac;
    float promedio;
} estudiante;

estudiante students[MAX];
int lastReg = 0;

/*
Create
Read
Update
Delete
*/

// Create
void addStudent(estudiante est);
/*Read*/
void showStudent(int pos);
int isStudent(char id[]);
void showStudents();
void startStudent(int pos);
estudiante getStudent(int pos);
/*Update*/
void updateStudent(estudiante est, int pos);
/*Delete*/
void deleteStudent(int pos);

/*Menu*/
int menu();
void start();

/*Archivos
 */
FILE *registroEstudiante;
void saveStudents();
void readStudents();
int calcUltReg(FILE *archivo);

void addStudent(estudiante est)
{
    students[lastReg] = est;
    lastReg++;
}

void showStudent(int pos)
{
    cout << "ID: " << students[pos].idUca << endl;
    cout << "NOMBRE: " << students[pos].nombre << endl;
    cout << "APELLIDOS: " << students[pos].apellido << endl;
    cout << "AÑO: " << students[pos].año << endl;
    cout << "EMAIL: " << students[pos].email << endl;
    cout << "FECHA NACIMIENTO: " << students[pos].fechaNac.dia << "/" << students[pos].fechaNac.mes << "/" << students[pos].fechaNac.año << endl;
    cout << "PROMEDIO: " << students[pos].promedio << endl;
}

estudiante getStudent(int pos)
{
    return students[pos];
}

int isStudent(char id[])
{
    int posicion = 0;
    for (int i = 0; i < lastReg; i++)
    {
        if (strcmp(id, students[i].idUca) == 0)
        {
            posicion = i;
            break;
        }
    }
    return posicion;
}

void showStudents()
{
    system("cls||clear");
    if (lastReg == 0)
    {
        cout << "No hay registros\n";
        return;
    }
    for (int i = 0; i < lastReg; i++)
    {
        cout<< "=========================\n";
        showStudent(i);
    }
    cout<< "Ultimo registro...\n";
}

void updateStudent(estudiante est, int pos)
{
    students[pos] = est;
}

void deleteStudent(int pos)
{
    if (pos == lastReg)
    {
        cout << "No hay registro\n";
        return;
    }
    for (int i = pos; i < lastReg - 1; i++)
    {
        students[i] = students[i + 1];
    }
    lastReg--;
    startStudent(lastReg);
}

void startStudent(int pos)
{
    strcpy(students[pos].idUca, "");
    strcpy(students[pos].nombre, "");
    strcpy(students[pos].apellido, "");
    students[pos].año = 0;
    strcpy(students[pos].email, "");
    students[pos].fechaNac.dia = 0;
    students[pos].fechaNac.mes = 0;
    students[pos].fechaNac.año = 0;
    students[pos].promedio = 0.00;
}

int menu()
{
    int op;

    gotoxy(10, 5);
    cout << " UNIVERSIDAD CENTROAMERICANA - UCA\n";
    gotoxy(15, 6);
    cout << "Cantidad de registros: " << lastReg << endl;
    gotoxy(10, 9);
    cout << " 1. Agregar Estudiante \n";
    gotoxy(10, 10);
    cout << " 2. Editar Estudiante \n";
    gotoxy(10, 11);
    cout << " 3. Eliminar Estudiante \n";
    gotoxy(10, 12);
    cout << " 4. Buscar Estudiante \n";
    gotoxy(10, 13);
    cout << " 5. Mostrar todos los Estudiantes \n";
    gotoxy(10, 14);
    cout << " 6. Salir \n";
    gotoxy(10, 15);
    cout << " Digite la opcion: ";
    gotoxy(29, 15);
    cin >> op;
    return op;
}

void start()
{
    int op, pos, resp;
    char id[9];
    estudiante est;
    readStudents();
    do
    {
        system("cls||clear");
        
        op = menu();
        switch (op)
        {
        case 1:
            system("cls || clear");
            gotoxy(10, 5);
            cout << "ID:";
            gotoxy(10, 6);
            cout << "NOMBRE: ";
            gotoxy(10, 7);
            cout << "APELLIDO: ";
            gotoxy(10, 8);
            cout << "AÑO: ";
            gotoxy(10, 9);
            cout << "EMAIL: ";
            gotoxy(10, 10);
            cout << "FECHA DE NACIMIENTO dd/MM/yyyy: ";
            gotoxy(10, 11);
            cout << "PROMEDIO: ";
            gotoxy(14, 5);
            scanf(" %[^\n]", est.idUca);
            gotoxy(18, 6);
            scanf(" %[^\n]", est.nombre);
            gotoxy(20, 7);
            scanf(" %[^\n]", est.apellido);
            gotoxy(16, 8);
            cin >> est.año;
            gotoxy(17, 9);
            scanf(" %[^\n]", est.email);
            gotoxy(42, 10);
            scanf("%d/%d/%d", &est.fechaNac.dia, &est.fechaNac.mes, &est.fechaNac.año);
            gotoxy(20, 11);
            cin >> est.promedio;
            addStudent(est);
            system("pause");

            break;
        case 2:
            system("cls||clear");
            cout << "Escribe el ID a buscar: ";
            scanf(" %[^\n]", id);
            pos = isStudent(id);
            showStudent(pos);
            cout << "DATOS A EDITAR\n";
            cout << "ID:";
            scanf(" %[^\n]", est.idUca);
            cout << "NOMBRE: ";
            scanf(" %[^\n]", est.nombre);
            cout << "APELLIDO: ";
            scanf(" %[^\n]", est.apellido);
            cout << "AÑO: ";
            cin >> est.año;
            cout << "EMAIL: ";
            scanf(" %[^\n]", est.email);
            cout << "FECHA DE NACIMIENTO: ";
            scanf("%d/%d/%d", &est.fechaNac.dia, &est.fechaNac.mes, &est.fechaNac.año);
            cout << "PROMEDIO: ";
            cin >> est.promedio;
            updateStudent(est, pos);
            cout << "Registro actualizado...\n";
            system("pause");
            break;
        case 3:
            system("cls||clear");
            if (lastReg == 0)
            {
                cout << "No hay nada que eliminar\n";
                break;
            }
            cout << "Escribe el ID del estudiante: ";
            cin >> id;
            pos = isStudent(id);
            est = getStudent(pos);
            cout << "¿Realmente deseas eliminar el estudiante: " << est.nombre << " " << est.apellido << "?\n";
            cout << "Escribe 1 para SI o 2 para NO: ";
            cin >> resp;
            if (resp == 1)
            {
                deleteStudent(pos);
                cout << "Registro Eliminado... \n";
            }
            else
            {
                cout << "Operaciòn cancelada.... \n";
            }
            system("pause");
            break;
        case 4:
            system("cls||clear");
            cout << "Escribe el ID a buscar: ";
            scanf(" %[^\n]", id);
            pos = isStudent(id);
            showStudent(pos);
            system("pause");
            break;
        case 5:
            system("cls||clear");
            showStudents();
            system("pause");
            break;
        case 6:
            break;
        default:
            system("clear||cls");
            cout << "Opcion invalida \n";
            system("pause");
            break;
        }
    } while (op != 6);
    saveStudents();
}

void saveStudents()
{
    registroEstudiante = fopen("datos.bin", "wb");
    fwrite(students, sizeof(estudiante), lastReg, registroEstudiante);
    fclose(registroEstudiante);
}

void readStudents()
{
    registroEstudiante = fopen("datos.bin", "rb");
    if (registroEstudiante == NULL)
    {
        return;
    }
    lastReg = calcUltReg(registroEstudiante);
    fread(students, sizeof(estudiante), MAX, registroEstudiante);

    fclose(registroEstudiante);
}

int calcUltReg(FILE *archivo)
{
    int tam_archivo, num_estudiantes;
    // Obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    tam_archivo = ftell(archivo);
    rewind(archivo);

    // Calcular el número de alumnos
    num_estudiantes = tam_archivo / sizeof(estudiante);
    return num_estudiantes;
}