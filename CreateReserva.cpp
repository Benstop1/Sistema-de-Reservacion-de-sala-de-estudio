#include "CreateReserva.h"
#include "ReadReserva.h"
#include "Reservas.h" 
#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <ctime>
using namespace std;
void crearReserva() {
    SetConsoleTitle("Reservando...");
    int sala = 0, treserva;
    string nombre, numero, ampm;
    int hora, minutos = 0;
    char fechareserva[20];
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    int horaactual = timeinfo->tm_hour;
    int minutoactual = timeinfo->tm_min;
    char* fechahoraactual = ctime(&now);
    mostrarEstadoSalas();
    SetConsoleTextAttribute(hConsole, 11);
    cout << endl << "Ingrese el numero de la sala (1-7): ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> sala;
    if(sala < 1 || sala > 7) {
        system("color 4");
        cout << endl << "-------------------------------------------------------------------" << endl;
        cout << "Numero de sala invalido. Presione cualquier tecla para continuar..." << endl;
        _getch();
        return;
    }
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Ingrese su nombre: ";
    SetConsoleTextAttribute(hConsole, 7);
    cin.ignore();
    getline(cin, nombre);
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Ingrese su numero de contacto: ";
    SetConsoleTextAttribute(hConsole, 7);
    getline(cin, numero);
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Seleccione Hoy o Ma\xa4ana: (a) Hoy / (b) Ma\xa4ana: ";
    SetConsoleTextAttribute(hConsole, 7);
    char selecciondia;
    bool diavalido = false;
    string dia;
    while(!diavalido) {
        selecciondia = _getch();
        cout << selecciondia << endl;
        if(selecciondia == 'a') {
            dia = "hoy";
            resdia = 0;
            diavalido = true;
        } else if(selecciondia == 'b') {
            dia = "manana";
            resdia = 60;
            diavalido = true;
        } else {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Opcion invalida. Ingrese 'a' para hoy o 'b' para ma\xa4ana: ";
        }
    }
    if(dia == "manana") {
        timeinfo->tm_mday += 1;
        mktime(timeinfo); 
    }
    strftime(fechareserva, sizeof(fechareserva), "%Y-%m-%d", timeinfo);
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Seleccione AM o PM: (a) AM / (b) PM: ";
    SetConsoleTextAttribute(hConsole, 7);
    char seleccion;
    bool ampmvalido = false;
    while(!ampmvalido) {
        seleccion = _getch();
        cout << seleccion << endl;
        if(seleccion == 'a') {
            ampm = "AM";
            horaarch = 0;
            ampmvalido = true;
        } else if(seleccion == 'b') {
            ampm = "PM";
            horaarch = 12;
            ampmvalido = true;
        } else {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "Opcion invalida. Ingrese 'a' para AM o 'b' para PM: ";
        }
    }
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Ingrese la hora que desea reservar (En formato 12h): ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> hora;
    horaarch += hora;
    horaarch -= 8;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Ingrese la cantidad de horas que desea ocupar: ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> treserva;
    if(verificarSalaOcupada(sala, horaactual, minutoactual, horaarch)) {
        system("color 4");
        cout << "---------------------------------------------------------------" << endl;
        cout << "Esta sala ya se encuentra reservada, por favor seleccione otra." << endl;
        _getch();
        return;
    }
    if((ampm == "AM" && hora < 8) || (ampm == "PM" && hora > 7) || hora < 1 || hora > 12) {
        system("color 4");
        cout << "Hora invalida. La hora debe estar entre las 08:00 AM y las 07:00 PM. Intente de nuevo." << endl;
        _getch();
        return;
    }
    int hora_militar = hora;
    if(ampm == "PM" && hora != 12) hora_militar += 12;
    else if(ampm == "AM" && hora == 12) hora_militar = 0;
    if(hora_militar + treserva > 20) {
        system("color 4");
        cout << "La hora ingresada supera el limite de las 20:00, intente nuevamente" << endl;
        _getch();
        return;
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << "----------------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Reserva realizada con exito para el " << fechareserva << " a las " << hora << ":" << minutos << minutos << " horas." << endl;
    Sleep(1500);
    fstream archivo("br.txt", ios::in | ios::out);
    if(!archivo.is_open()) {
        system("color 4");
        cout << "Error al abrir el archivo. Presione cualquier tecla para continuar..." << endl;
        _getch();
        return;
    }
    int posicion = (sala - 1) * 120;
    posicion += (horaarch * 5) + resdia;
    string linea;
    int lineaactual = 0;
    archivo.seekg(0, ios::beg);
    ofstream temp("temp.txt");
    while(getline(archivo, linea)) {
        if(lineaactual == posicion) {
            temp << nombre << endl;
        } else if(lineaactual == posicion + 1) {
            temp << numero << endl;
        } else if(lineaactual == posicion + 2) {
            temp << fechareserva << endl;
        } else if(lineaactual == posicion + 3) {
            temp << hora << ":" << minutos << " " << ampm << endl;
        } else if(lineaactual == posicion + 4) {
            temp << fechahoraactual; 
        } else if(lineaactual > posicion + 4 && lineaactual <= posicion + 4 + ((treserva - 1) * 5)) {
            temp << "1" << endl;
        } else {
            temp << linea << endl;
        }
        lineaactual++;
    }
    archivo.close();
    temp.close();
    remove("br.txt");
    rename("temp.txt", "br.txt");
    system("cls");
    SetConsoleTextAttribute(hConsole, 3);
    cout << "====================" << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << " RESUMEN DE RESERVA " << endl;
    SetConsoleTextAttribute(hConsole, 3);
    cout << "====================" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Nombre: "; SetConsoleTextAttribute(hConsole, 7); cout << nombre << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Numero: "; SetConsoleTextAttribute(hConsole, 7); cout << numero << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Fecha: "; SetConsoleTextAttribute(hConsole, 7); cout << fechareserva << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "Hora: "; SetConsoleTextAttribute(hConsole, 7); cout << hora << ":" << minutos << minutos << " " << ampm << endl;
    cout << "Reserva realizada a las: "; SetConsoleTextAttribute(hConsole, 15); cout << fechahoraactual;
    ofstream r_2("registro.txt", ios::app);
    achtuhora();
    r_2 << fhar << " || Se realizo una reserva para " << nombre << " (" << numero << ") en la sala " << sala << " a las " << hora << ":" << minutos << minutos << " " << ampm << " | " << treserva << " Hora/s" << endl;
    r_2.close();
    cout << "------------------------------------------------------------";
    SetConsoleTextAttribute(hConsole, 8);
    cout << endl << "Presione cualquier tecla para regresar al menu principal..." << endl;
    _getch();
}
