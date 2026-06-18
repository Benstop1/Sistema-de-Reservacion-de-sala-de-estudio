#include "Sistema.h"
#include <fstream>
#include <conio.h>
using namespace std;
int iniciado = 1;
int horaarch;
int resdia;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
char fhar[20];
int har;
int mar;
void achtuhora() {
    time_t now = time(0);
    struct tm* timeinfo;
    timeinfo = localtime(&now);
    har = timeinfo->tm_hour;
    mar = timeinfo->tm_min;
    strftime(fhar, sizeof(fhar), "%Y-%m-%d %H:%M:%S", timeinfo);
}
void actualizacion() {
    system("cls");
    int carga, contar;
    string caa[10];
    for(carga = 0; carga < 10; carga++) {
        caa[carga] = "...";
    }
    for(carga = 0; carga < 10; carga++) {
        system("COLOR A");
        caa[carga] = "|||";
        system("cls");
        cout << "Refrescando los datos..." << endl << endl;
        cout << "==============================" << endl;
        for(contar = 0; contar < 10; contar++) {
            cout << caa[contar];
        }
        cout << std::endl << "==============================" << endl << endl;
        Sleep(100);
    }
    Sleep(800);
    system("color b");
    cout << "Se actualizo el sistema con exito" << endl;
    Sleep(200);
    cout << "-------------------------------------------" << endl;
    Sleep(200);
    cout << "Presione cualquier tecla para continuar...";
    _getch();
    system("cls");
}
void setup() {
    ifstream f("br.txt");
    if(f.is_open()) {
        f.close();
        return;
    } else {
        int horasalas;
        int carga, contar;
        string caa[10];
        for(carga = 0; carga < 10; carga++) {
            caa[carga] = "...";
        }
        for(carga = 0; carga < 10; carga++) {
            caa[carga] = "|||";
            system("cls");
            SetConsoleTextAttribute(hConsole, 15);
            cout << "Creando el archivo de reservas..." << endl << endl;
            SetConsoleTextAttribute(hConsole, 2);
            if(carga == 9) SetConsoleTextAttribute(hConsole, 11);
            cout << "==============================" << endl;
            SetConsoleTextAttribute(hConsole, 10);
            if(carga == 9) SetConsoleTextAttribute(hConsole, 11);
            for(contar = 0; contar < 10; contar++) {
                cout << caa[contar];
            }
            if(carga == 9) SetConsoleTextAttribute(hConsole, 11);
            cout << endl << "==============================" << endl << endl;
            Sleep(200);
        }
        Sleep(1000);
        ofstream f_out("br.txt");
        for(int i = 0; i < 7; i++) {
            for(horasalas = 0; horasalas < 24; horasalas++) {
                f_out << "NONE" << endl;
                f_out << "NONE" << endl;
                f_out << "NONE" << endl;
                f_out << "NONE" << endl;
                f_out << "NONE" << endl;
            }
        }
        f_out.close();
        fstream archivo("br.txt", ios::in | ios::out);
        if (archivo.is_open()) {
            struct RegistroPrueba {
                int sala;
                int horaDelArchivo; 
                int dia;           
                string nombre;
                string telefono;
                string fecha;
                string horarioTexto;
            };
            RegistroPrueba pruebas[2] = {
                {1, 2, 0, "Carlos Mendoza", "987654321", "Hoy", "10:00 AM"},
                {3, 1, 0, "Maria Lopez", "966777888", "Hoy", "09:00 AM"}
            };
            for (int k = 0; k < 2; k++) {
                int posicionLineas = (pruebas[k].sala - 1) * 120;
                posicionLineas += (pruebas[k].horaDelArchivo * 5) + pruebas[k].dia;
                archivo.seekg(0, ios::beg);
                string lineasContenedor[840]; 
                
                for (int m = 0; m < 840; m++) {
                    getline(archivo, lineasContenedor[m]);
                }
                lineasContenedor[posicionLineas]     = pruebas[k].nombre;
                lineasContenedor[posicionLineas + 1] = pruebas[k].telefono;
                lineasContenedor[posicionLineas + 2] = pruebas[k].fecha;
                lineasContenedor[posicionLineas + 3] = pruebas[k].horarioTexto;
                lineasContenedor[posicionLineas + 4] = "Registro Automatico de Sistema";
                archivo.clear();
                archivo.seekp(0, ios::beg);
                for (int m = 0; m < 840; m++) {
                    archivo << lineasContenedor[m] << endl;
                }
            }
            archivo.close();
        }
        Sleep(1000);
        SetConsoleTextAttribute(hConsole, 15);
        cout << "El archivo fue creado y configurado con 2 registros de prueba con exito." << endl;
        Sleep(2000);
    }
}
