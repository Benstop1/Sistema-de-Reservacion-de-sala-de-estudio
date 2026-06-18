#include "ReadReserva.h"
#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void mostrarEstadoSalas() {
    ifstream archivo("br.txt");
    if (!archivo) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Error al abrir el archivo de reservas." << endl;
        return;
    }
    string linea;
    int reservas[7] = {0};
    int contador = 0;
    while (getline(archivo, linea)) {
        if (contador % 5 == 0) {
            if (linea != "NONE") {
                reservas[contador / 120]++;
            }
        }
        contador++;
    }
    archivo.close();
    string nombresalas[7] = {
        "Sala de estudio Grupal 1", "Sala de estudio Grupal 2", 
        "Sala de estudio Individual 3", "Sala de estudio Individual 4", 
        "Sala de estudio Individual 5", "Sala de estudio VideoConferencia 6", 
        "Sala de estudio VideoConferencia 7"
    };
    SetConsoleTextAttribute(hConsole, 11);
    cout << "===========================================================================" << endl;
    cout << "                         ESTADO ACTUAL DE LAS SALAS                        " << endl;
    cout << "===========================================================================" << endl;
    for (int i = 0; i < 7; i++) {
        SetConsoleTextAttribute(hConsole, 15);
        cout << i + 1 << ".- " << nombresalas[i] << " ---> ";
        if (reservas[i] == 0) {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "[ DISPONIBLE ]" << endl;
        } else {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "[ OCUPADA (" << reservas[i] << " Horas reservadas) ]" << endl;
        }
    }
    SetConsoleTextAttribute(hConsole, 7);
    cout << "===========================================================================" << endl;
}
bool verificarSalaOcupada(int sala, int horaActual, int minutoActual, int h_arch) {
    ifstream archivo("br.txt");
    if (!archivo.is_open()) {
        return false;
    }
    int posicion = (sala - 1) * 120;
    posicion += (h_arch * 5) + resdia;
    string linea;
    int lineaactual = 0;
    bool ocupado = false;
    while (getline(archivo, linea)) {
        if (lineaactual == posicion) {
            if (linea != "NONE") {
                ocupado = true;
            }
            break;
        }
        lineaactual++;
    }
    archivo.close();
    return ocupado;
}
