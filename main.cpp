#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "Sistema.h"
#include "Seguridad.h"

using namespace std;
int main() {
    SetConsoleTitle("Inicio de Sesion");
    ifstream r("registro.txt");
    if(!r.is_open()) {
        ofstream r_out("registro.txt");
        r_out.close();
    } else {
        r.close();
    }
    char opcion;
    bool ejecucion = true;
    while(ejecucion) {
        system("cls");
        SetConsoleTextAttribute(hConsole, 11);
        cout << "***************************************************************************\n\n";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "                             Bienvenido al sistema                          \n\n";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "*************************** MENU        ***************************\n\n";
        SetConsoleTextAttribute(hConsole, 7);
        Sleep(200);
        cout << "1.- Iniciar sesion" << std::endl;
        Sleep(200);
        cout << "2.- Registrarse" << std::endl;
        Sleep(200);
        cout << "3.- \xbfOlvidaste tu usuario o contrasena?" << std::endl;
        Sleep(200);
        cout << "4.- Salir" << std::endl;
        Sleep(400);
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\nQue desea realizar: ";
        opcion = _getch();
        SetConsoleTextAttribute(hConsole, 7);
        cout << opcion << std::endl;
        switch(opcion) {
            case '1': 
                iniciarsesion();
                break;
            case '2': 
                registrar();
                break;
            case '3': 
                olvidaris();
                break;
            case '4': 
                cout << "Gracias por usar el programa :)" << std::endl;
                Sleep(1800);
                ejecucion = false;
                break;
            default:
                system("color 4");
                Sleep(200);
                cout << std::endl << "--------------------------------------" << std::endl;
                cout << "Ingrese un numero valido, intente nuevamente." << std::endl;
                Sleep(1500);
        }
    }
    return 0;
}
