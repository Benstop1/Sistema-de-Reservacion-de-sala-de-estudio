#include "DeleteReserva.h"
#include "ReadReserva.h"
#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
void eliminarReserva() {
    SetConsoleTitle("Eliminando Reserva...");
    int sala;
    int cronometro = 3;
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    int horaactual = timeinfo->tm_hour;
    int minutoactual = timeinfo->tm_min;
    mostrarEstadoSalas();
    cout << endl << "Ingrese el numero de la sala a eliminar (1-7): ";
    cin >> sala;
    if(sala < 1 || sala > 7) {
        system("color 4");
        cout << "Numero de sala invalido. Presione cualquier tecla para continuar..." << endl;
        _getch();
        return;
    }
    if(!verificarSalaOcupada(sala, horaactual, minutoactual, horaarch)) {
        system("color 4");
        cout << "Esta sala no se encuentra reservada, por favor seleccione otra." << endl;
        _getch();
        return;
    }
    system("cls");
    ifstream archivo("br.txt");
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
    ofstream temp("temp.txt");
    while(getline(archivo, linea)) {
        if(lineaactual >= posicion && lineaactual < posicion + 5) {
            temp << "NONE" << endl;
        } else {
            temp << linea << endl;
        }
        lineaactual++;
    }
    archivo.close();
    temp.close();
    remove("br.txt");
    rename("temp.txt", "br.txt");
    SetConsoleTextAttribute(hConsole, 10);
    cout << "La reservacion de la sala " << sala << " fue eliminada con exito." << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Presione cualquier tecla para continuar..." << endl;
    ofstream r_3("registro.txt", ios::app);
    achtuhora();
    r_3 << fhar << " || Se elimino la reserva en la sala " << sala << endl;
    r_3.close();
    _getch();
    while(cronometro > 0) {
        system("cls");
        SetConsoleTextAttribute(hConsole, 14);
        cout << "Volvera al menu principal en " << cronometro << " segundos...";
        Sleep(1000);
        cronometro--;
    }
    SetConsoleTextAttribute(hConsole, 7);
}
