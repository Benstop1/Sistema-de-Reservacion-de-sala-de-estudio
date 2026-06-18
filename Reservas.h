#ifndef RESERVAS_H
#define RESERVAS_H
#include <string>
using namespace std;
struct SalaResumen {
    string nombre;
    int horas;
};
int programa();
void registro();
void leyendolibros();
void calcularEstadisticasGlobales(SalaResumen arregloSalas[7], int &totalHorasSistema, string &salaMasOcupada);
void mostrarRankingSalas(SalaResumen (&arregloSalas)[7], int idSalas[7]);
void generarReporteOrdenado();
void exportarReporteEstructurado();
int busquedaBinariaRecursiva(int arreglo[], int bajo, int alto, int buscar, int &contadorLlamadas);
void buscarSalaBinaria();      
void intercalarArchivos();
#endif
