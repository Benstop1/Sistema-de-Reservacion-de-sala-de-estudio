#include "UpdateReserva.h"
#include "ReadReserva.h"
#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
void actualizarReserva() {
    SetConsoleTitle("Modificando Reserva...");
    system("cls");
    int sala = 0;
    string nuevoNombre, nuevoNumero, ampm;
    int hora, horaarch_local = 0, resdia_local = 0;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "===========================================================================" << endl;
    cout << "                         MODIFICAR DATOS DE RESERVA                        " << endl;
    cout << "===========================================================================" << endl;
    mostrarEstadoSalas();
    SetConsoleTextAttribute(hConsole, 11);
    cout << endl << "Ingrese el numero de la sala a modificar (1-7): ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> sala;
    if (sala < 1 || sala > 7) {
        system("color 4");
        cout << endl << "Numero de sala invalido. Presione cualquier tecla..." << endl;
        _getch();
        return;
    }
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Seleccione el dia de la reserva: (a) Hoy / (b) Ma\xa4ana: ";
    SetConsoleTextAttribute(hConsole, 7);
    char selecciondia = _getch();
    cout << selecciondia << endl;
    if (selecciondia == 'a') {
        resdia_local = 0;
    } else if (selecciondia == 'b') {
        resdia_local = 60;
    } else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Opcion de dia invalida." << endl;
        _getch();
        return;
    }
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Seleccione AM o PM de la reserva: (a) AM / (b) PM: ";
    SetConsoleTextAttribute(hConsole, 7);
    char seleccionampm = _getch();
    cout << seleccionampm << endl;
    if (seleccionampm == 'a') {
        horaarch_local = 0;
        ampm = "AM";
    } else if (seleccionampm == 'b') {
        horaarch_local = 12;
        ampm = "PM";
    } else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Opcion invalida." << endl;
        _getch();
        return;
    }
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Ingrese la hora de la reserva (Formato 12h): ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> hora;
    horaarch_local += hora;
    horaarch_local -= 8;
    int posicion = (sala - 1) * 120;
    posicion += (horaarch_local * 5) + resdia_local;
    ifstream archivoLectura("br.txt");
    string primeraLinea;
    int lineaAct = 0;
    bool existeReserva = false;
    while (getline(archivoLectura, primeraLinea)) {
        if (lineaAct == posicion) {
            if (primeraLinea != "NONE") {
                existeReserva = true;
            }
            break;
        }
        lineaAct++;
    }
    archivoLectura.close();
    if (!existeReserva) {
        system("color 4");
        cout << "---------------------------------------------------------------" << endl;
        cout << "No se encontro ninguna reserva activa en ese horario para modificar." << endl;
        _getch();
        return;
    }
    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n--- Reserva Localizada ---" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Ingrese el NUEVO nombre del responsable: ";
    SetConsoleTextAttribute(hConsole, 7);
    cin.ignore();
    getline(cin, nuevoNombre);
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Ingrese el NUEVO numero de contacto: ";
    SetConsoleTextAttribute(hConsole, 7);
    getline(cin, nuevoNumero);
    fstream archivo("br.txt", ios::in | ios::out);
    if (!archivo.is_open()) {
        cout << "Error al abrir la base de datos." << endl;
        _getch();
        return;
    }
    string linea;
    int lineaactual = 0;
    archivo.seekg(0, ios::beg);
    ofstream temp("temp.txt");
    while (getline(archivo, linea)) {
        if (lineaactual == posicion) {
            temp << nuevoNombre << endl; // Modifica Nombre
        } else if (lineaactual == posicion + 1) {
            temp << nuevoNumero << endl; // Modifica Teléfono
        } else {
            temp << linea << endl;      // Conserva Fecha, Horas, etc.
        }
        lineaactual++;
    }
    archivo.close();
    temp.close();
    remove("br.txt");
    rename("temp.txt", "br.txt");
    ofstream r_2("registro.txt", ios::app);
    achtuhora();
    r_2 << fhar << " || Se MODIFICO la reserva de la sala " << sala << " a las " << hora << ":00 " << ampm << " -> Nuevo Responsable: " << nuevoNombre << endl;
    r_2.close();
    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n----------------------------------------------------------" << endl;
    cout << "¡Reserva actualizada con exito!" << endl;
    SetConsoleTextAttribute(hConsole, 8);
    cout << "Presione cualquier tecla para regresar..." << endl;
    _getch();
}
