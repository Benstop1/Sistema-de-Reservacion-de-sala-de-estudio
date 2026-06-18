#include "Seguridad.h"
#include "Sistema.h"
#include "Reservas.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
string contrainput() {
    string contrasena;
    char ch;
    while(true) {
        ch = _getch();
        if(ch == '\r') {
            cout << endl;
            break;
        } else if(ch == '\b') {
            if(!contrasena.empty()) {
                contrasena.resize(contrasena.size() - 1);
                cout << "\b \b";
            }
        } else {
            contrasena += ch;
            cout << '*';
        }
    }
    return contrasena;
}
void iniciarsesion() {
    int con = 0;
    string usuario, contra, u, c;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "-----------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Usuario: ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> usuario;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Contrase\xa4a: "; 
    SetConsoleTextAttribute(hConsole, 7);
    contra = contrainput();
    ifstream ingreso("usuarios.txt");
    if(ingreso.is_open()) {
        while(ingreso >> u >> c) {
            if(u == usuario && c == contra) {
                con++;
            }
        }
    } else {
        system("color 4");
        cout << "Error al abrir el archivo de usuarios." << endl;
    }
    ingreso.close();
    if(con == 1) {
        SetConsoleTextAttribute(hConsole, 15);
        cout << "-----------------------------------------" << endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Bienvenido ";
        SetConsoleTextAttribute(hConsole, 11);
        cout << usuario;
        SetConsoleTextAttribute(hConsole, 7);
        cout << " !!!" << std::endl;
        SetConsoleTextAttribute(hConsole, 8);
        cout << "Presione cualquier tecla para continuar..." << endl;
        _getch();
        programa();
    } else {
        Sleep(200);
        system("color 4");
        cout << "--------------------------------------" << endl;
        cout << "Error al iniciar sesion, intente nuevamente" << endl;
        Sleep(1000);
        system("cls");
    }
}
void registrar() {
    string regisu, regiscontra;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Nombre de usuario: ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> regisu;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Contrase\xa4a: ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> regiscontra;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "---------------------------------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "(Recuerde muy bien su contrase\xa4a, esta tambien servira para otras acciones)";
    Sleep(2000);
    ofstream registro("usuarios.txt", ios::app); 
    if(registro.is_open()) {
        cout << "\nEl archivo se abrio correctamente" << endl;
        registro << regisu << " " << regiscontra << endl;
        registro.close();
        cout << "Se registraron los datos correctamente :)" << endl;
        Sleep(1000);
    } else {
        system("color 4");
        cout << "No se registraron los datos :(";
        Sleep(1000);
    }
}
void olvidaris() {
    int opc;
    system("cls");
    cout << "\xbfOlvido su usuario o contrasena?" << endl;
    cout << "1.Buscar ID por usuario?" << endl;
    cout << "2.Buscar ID por contrasena?" << endl;
    cout << "3.Volver al menu principal" << endl;
    cin >> opc;
    switch(opc) {
        case 1: {
            int cont = 0;
            string buscaru, bu, bu2;
            cout << "Ingrese el Nombre de usuario que recuerda: ";
            cin >> buscaru;
            ifstream buscar("usuarios.txt");
            if(buscar.is_open()) {
                while(buscar >> bu >> bu2) {
                    if(bu == buscaru) {
                        cont = 1;
                        break;
                    }
                }
            } else {
                system("color 4");
                cout << "No se pudo buscar nada en el archivo" << endl;
            }
            buscar.close();
            if(cont == 1) {
                cout << "El usuario fue encontrado!!" << endl;
                cout << "Tu contrasena es: " << bu2 << endl;
                cout << "Presione cualquier tecla para continuar" << endl;
                _getch();
            } else {
                system("color 4");
                cout << "Tu usuario no fue encontrado en el archivo :(" << endl;
                cout << "Presione cualquier tecla para continuar";
                _getch();
            }
            break;
        }
        case 2: {
            int cont = 0;
            string buscarcontra, bc, bc2;
            cout << "Ingrese la contrase\xa4a que recuerda: " << endl;
            cin >> buscarcontra;
            ifstream buscarc("usuarios.txt");
            if(buscarc.is_open()) {
                while(buscarc >> bc >> bc2) {
                    if(bc2 == buscarcontra) {
                        cont = 1;
                        break;
                    }
                }
            } else {
                cout << "No se pudo buscar nada en el archivo" << endl;
            }
            buscarc.close();
            
            if(cont == 1) {
                cout << "Tu contrasena fue encontrada en el archivo!!!" << endl;
                cout << "Tu usuario es: " << bc << endl;
                cout << "Presione cualquier tecla para continuar";
                _getch();
            } else {
                system("color 4");
                cout << "No se encontro la contrasena en el archivo";
                _getch();
            }
            break;
        }
        case 3:
            break;
        default:
            system("cls");
            system("color 4");
            cout << "Ingrese un numero valido." << endl;
            Sleep(1500);
    }
}
