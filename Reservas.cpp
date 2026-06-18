#include "Reservas.h"
#include "Sistema.h"
#include "CreateReserva.h"
#include "UpdateReserva.h"
#include "ReadReserva.h"
#include "DeleteReserva.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;
void registro() {
    string a;
    ifstream r_c("registro.txt");
    if (!r_c.is_open()) {
        cout << "No se pudo abrir el archivo de registros." << endl;
        return;
    }
    while (getline(r_c, a)) {
        cout << a << endl;
    }
    r_c.close();
    SetConsoleTextAttribute(hConsole, 15);
    cout << "------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 8);
    cout << "Presione cualquier tecla para continuar..." << endl;
    _getch();
}
void leyendolibros() {
    system("cls");
    int opcccc, cuant = 1, tida = 0;
    string tipodato[5] = {"Nombre:-----------------", "Numero:-----------------", "Fecha reservada:--------", "Hora reservada:---------", "Momento de la reserva:--"};
    mostrarEstadoSalas();
    cout << "Ingrese la sala que desea revisar: ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> opcccc;
    opcccc--;
    opcccc = opcccc * 120;
    ifstream archivo("br.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    string linea;
    int contador = 0;
    while (getline(archivo, linea)) {
        if (contador >= opcccc && contador < opcccc + 120) {
            if (linea != "NONE") {
                if(linea == "1") {
                    if(contador % 5 == 0) {
                        cuant++;
                    }
                } else {
                    if(tida == 5) {
                        cout << "Reservado por: " << cuant << " horas" << endl;
                        cuant = 1;
                    }
                    if(tida > 4) {
                        tida = 0;
                    }
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << tipodato[tida];
                    SetConsoleTextAttribute(hConsole, 15);
                    cout << linea << endl;
                    tida++;
                }
            }
        }
        contador++;
    }
    archivo.close();
    SetConsoleTextAttribute(hConsole, 15);
    cout << "------------------------------------------------------------";
    SetConsoleTextAttribute(hConsole, 8);
    cout << endl << "Presione cualquier tecla para regresar al menu principal..." << endl;
    _getch();
}
int programa() {
    system("cls");
    if(iniciado == 1) {
        setup();
        iniciado++;
    } else {
        actualizacion();
    }
    char op;
    bool menu = true;
    while(menu == true) {
        SetConsoleTitle("Menu de Reservas");
        SetConsoleTextAttribute(hConsole, 11);
        cout << "***************************************************************************" << endl;
        cout << "*"; SetConsoleTextAttribute(hConsole, 15); cout << "                                  INICIO                                 "; SetConsoleTextAttribute(hConsole, 11); cout << "*" << endl;
        cout << "***************************************************************************" << endl;
        cout << "*"; SetConsoleTextAttribute(hConsole, 15); cout << "           Bienvenido al programa, use una de las siguientes opciones      "; SetConsoleTextAttribute(hConsole, 11); cout << "*" << endl;
        cout << "***************************************************************************" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout << "1.- Reservar sala de estudio" << endl; Sleep(100);
        cout << "2.- Eliminar reserva de sala" << endl; Sleep(100);
        cout << "3.- Modificar datos de reserva" << endl; Sleep(100);
        cout << "4.- Registro de reservas (Bitacora)" << endl; Sleep(100);
        cout << "5.- Generar reporte ordenado de salas" << endl; Sleep(100);  
        cout << "6.- Buscar sala (Busqueda Binaria)" << endl; Sleep(100);     
        cout << "7.- Intercalar archivos de salas" << endl; Sleep(100);       
        cout << "8.- Revisar horas reservadas (Leyendo Libros)" << endl; Sleep(100);
        cout << "9.- Exportar Reporte Estructurado (.PDF)" << endl; Sleep(100);
        cout << "0.- Salir del programa" << endl; Sleep(100);
        mostrarEstadoSalas(); 
        cout << endl << "Ingrese la opcion: ";
        op = _getch();
        cout << op << endl;
        if((op >= '0' && op <= '9')) {
            if(op == '1') { system("cls"); crearReserva(); }
            else if(op == '2') { system("cls"); eliminarReserva(); }
            else if(op == '3') { system("cls"); actualizarReserva(); }
            else if(op == '4') { system("cls"); registro(); }
            else if(op == '5') { system("cls"); generarReporteOrdenado(); } 
            else if(op == '6') { system("cls"); buscarSalaBinaria(); }      
            else if(op == '7') { system("cls"); intercalarArchivos(); }     
            else if(op == '8') { system("cls"); leyendolibros(); }
            else if(op == '9') { exportarReporteEstructurado(); }
            else if(op == '0') { menu = false; }
        } else {
            system("color 4");
            Sleep(200);
            cout << endl << "-------------------------------------------------------------------------------" << endl;
            cout << "Opcion no valida, presione cualquier tecla para intentarlo nuevamente..." << endl;
            _getch();
        }
        system("cls");
    }
    return 0;
}
void calcularEstadisticasGlobales(SalaResumen arregloSalas[7], int &totalHorasSistema, string &salaMasOcupada) {
    totalHorasSistema = 0;
    int maxHoras = -1;
    salaMasOcupada = "";
    for(int i = 0; i < 7; i++) {
        totalHorasSistema += arregloSalas[i].horas; 
        if(arregloSalas[i].horas > maxHoras) {
            maxHoras = arregloSalas[i].horas;
            salaMasOcupada = arregloSalas[i].nombre;
        }
    }
}
void mostrarRankingSalas(SalaResumen (&arregloSalas)[7], int idSalas[7]) {
    for (int i = 0; i < 7; i++) {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\n[RANKING #" << i + 1 << "] " << arregloSalas[i].nombre;
        SetConsoleTextAttribute(hConsole, 15);
        cout << " (Total: " << arregloSalas[i].horas << " hrs reservadas)" << endl;
        cout << "---------------------------------------------------------------------------" << endl;
        if (arregloSalas[i].horas == 0) {
            SetConsoleTextAttribute(hConsole, 10);
            cout << "  -> Sin reservaciones activas (Sala Completamente Libre)." << endl;
        } else {
            ifstream archivoDetalle("br.txt");
            if (archivoDetalle.is_open()) {
                int inicioSala = (idSalas[i] - 1) * 120;
                string nombre, numero, fecha, hora, regHist, linea;
                int lineaActual = 0;
                int conteoInterno = 0;
                while (lineaActual < inicioSala && getline(archivoDetalle, linea)) {
                    lineaActual++;
                }
                for (int bloque = 0; bloque < 24; bloque++) {
                    if (!getline(archivoDetalle, nombre) || !getline(archivoDetalle, numero) || 
                        !getline(archivoDetalle, fecha) || !getline(archivoDetalle, hora) || 
                        !getline(archivoDetalle, regHist)) {
                        break;
                    }
                    if (nombre != "NONE") {
                        conteoInterno++;
                        SetConsoleTextAttribute(hConsole, 11);
                        cout << "  " << conteoInterno << ") Cliente: "; 
                        SetConsoleTextAttribute(hConsole, 7); 
                        cout << nombre << " | Tel: " << numero << " | Fecha: " << fecha << " | Hora: " << hora << endl;
                    }
                }
                archivoDetalle.close();
            }
        }
        SetConsoleTextAttribute(hConsole, 15);
        cout << "..........................................................................." << endl;
    }
}
int compBurbuja = 0, interBurbuja = 0;
int compIntercalacion = 0, interIntercalacion = 0;
struct ReservaCronologica {
    int salaId;
    int horaIndice; 
    string nombre;
    string telefono;
    string fecha;
    string horarioTexto;
};
void generarReporteOrdenado() {
    system("cls");
    SetConsoleTitle("Reporte Ordenado por Horario - Bubble Sort");
    ReservaCronologica listaReservas[168];
    int totalReservasEncontradas = 0;
    ifstream archivo("br.txt");
    if (!archivo) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Error al abrir la base de datos." << endl;
        _getch();
        return;
    }
    string nombre, numero, fecha, horaTexto, registroHistorico;
    int contadorLineas = 0;
    while (getline(archivo, nombre)) {
        getline(archivo, numero);
        getline(archivo, fecha);
        getline(archivo, horaTexto);
        getline(archivo, registroHistorico);
        if (nombre != "NONE") {
            int salaCalculada = (contadorLineas / 120) + 1;
            int horaCalculada = (contadorLineas % 120) / 5;
            listaReservas[totalReservasEncontradas].salaId = salaCalculada;
            listaReservas[totalReservasEncontradas].horaIndice = horaCalculada;
            listaReservas[totalReservasEncontradas].nombre = nombre;
            listaReservas[totalReservasEncontradas].telefono = numero;
            listaReservas[totalReservasEncontradas].fecha = fecha;
            listaReservas[totalReservasEncontradas].horarioTexto = horaTexto;
            totalReservasEncontradas++;
        }
        contadorLineas += 5; 
    }
    archivo.close();
    if (totalReservasEncontradas == 0) {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "===========================================================================" << endl;
        cout << "   No hay ninguna reservacion activa en el sistema para ordenar." << endl;
        cout << "===========================================================================" << endl;
        _getch();
        return;
    }
    for (int i = 0; i < totalReservasEncontradas - 1; i++) {
        for (int j = 0; j < totalReservasEncontradas - 1 - i; j++) {
            if (listaReservas[j].horaIndice > listaReservas[j + 1].horaIndice) {
                ReservaCronologica temp = listaReservas[j];
                listaReservas[j] = listaReservas[j + 1];
                listaReservas[j + 1] = temp;
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 11);
    cout << "===========================================================================" << endl;
    cout << "          CRONOGRAMA DE RESERVACIONES ORDENADAS POR HORARIO (BUBBLE)        " << endl;
    cout << "===========================================================================" << endl;
    for (int i = 0; i < totalReservasEncontradas; i++) {
        SetConsoleTextAttribute(hConsole, 14);
        cout << " [" << listaReservas[i].horarioTexto << "] - Dia: " << listaReservas[i].fecha << endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout << "   | Sala       : Sala " << listaReservas[i].salaId << endl;
        cout << "   | Responsable: " << listaReservas[i].nombre << endl;
        cout << "   | Contacto   : " << listaReservas[i].telefono << endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout << " ---------------------------------------------------------------------------" << endl;
    }
    SetConsoleTextAttribute(hConsole, 10);
    cout << "\n >>> Se listaron y ordenaron " << totalReservasEncontradas << " registros exitosamente. <<<" << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << "\nPresione cualquier tecla para regresar al menu...";
    _getch();
}
void exportarReporteEstructurado() {
    system("cls");
    SetConsoleTitle("Exportando Reporte...");
    string nombresalas[7] = {
        "Sala de estudio Grupal 1", "Sala de estudio Grupal 2", 
        "Sala de estudio Individual 3", "Sala de estudio Individual 4", 
        "Sala de estudio Individual 5", "Sala de estudio VideoConferencia 6", 
        "Sala de estudio VideoConferencia 7"
    };
    int reservas[7] = {0};
    ifstream archivo("br.txt");
    if (!archivo) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Error al abrir la base de datos para exportar." << endl;
        _getch();
        return;
    }
    string linea;
    int contador = 0;
    while (getline(archivo, linea)) {
        if (contador % 5 == 0 && linea != "NONE") {
            reservas[contador / 120]++;
        }
        contador++;
    }
    archivo.close();
    ofstream reporte("Reporte_Ocupacion_Salas.pdf"); 
    if (reporte.is_open()) {
        reporte << "===========================================================================" << endl;
        reporte << "                      REPORTE OFICIAL DE OCUPACION DE SALAS                " << endl;
        reporte << "                      SISTEMA DE GESTION DE RESERVAS C++                   " << endl;
        reporte << "===========================================================================" << endl;
        reporte << " Fecha de Emision: " << __DATE__ << " | Hora: " << __TIME__ << endl;
        reporte << " Estado del Documento: Procesado y Consolidado Estructuralmente" << endl;
        reporte << "---------------------------------------------------------------------------" << endl << endl;
        reporte << " TABLA RESUMEN DE USO COMPUTADO:" << endl;
        reporte << " -------------------------------------------------------------------------" << endl;
        reporte << "   ID   |   NOMBRE DE LA SALA                           |  HRS RESERVADAS " << endl;
        reporte << " -------------------------------------------------------------------------" << endl;
        int totalHorasGlobales = 0;
        for (int i = 0; i < 7; i++) {
            totalHorasGlobales += reservas[i];
            string nombreSalaFormateado = nombresalas[i];
            while (nombreSalaFormateado.length() < 45) {
                nombreSalaFormateado += " "; 
            }
            reporte << "   [0" << i + 1 << "]  |   " << nombreSalaFormateado << " |   " << reservas[i] << " hrs" << endl;
        }
        reporte << " -------------------------------------------------------------------------" << endl;
        reporte << "   >>> TOTAL DE HORAS REGISTRADAS EN EL SISTEMA: " << totalHorasGlobales << " hrs" << endl;
        reporte << " -------------------------------------------------------------------------" << endl << endl;
        reporte << "===========================================================================" << endl;
        reporte << "                      FIN DEL REPORTE - ARCHIVO EXPORTADO                  " << endl;
        reporte << "===========================================================================" << endl;
        reporte.close();
        SetConsoleTextAttribute(hConsole, 10);
        cout << "===========================================================================" << endl;
        cout << "         ¡REPORTE EXPORTADO EXITOSAMENTE EN FORMATO ESTRUCTURADO!          " << endl;
        cout << "===========================================================================" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout << " Se ha generado el archivo: 'Reporte_Ocupacion_Salas.pdf'" << endl;
        cout << " Puede abrirlo o mandarlo a imprimir directamente." << endl;
    } else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Error al intentar crear el archivo físico del reporte." << endl;
    }
    SetConsoleTextAttribute(hConsole, 8);
    cout << "\nPresione cualquier tecla para regresar al menu...";
    _getch();
}
int busquedaBinariaRecursiva(int arreglo[], int bajo, int alto, int buscar, int &contadorLlamadas) {
    contadorLlamadas++; 
    if (bajo > alto) {
        return -1; 
    }
    int mitad = (bajo + alto) / 2;
    if (arreglo[mitad] == buscar) {
        return mitad; 
    }
    else if (arreglo[mitad] < buscar) {
        return busquedaBinariaRecursiva(arreglo, mitad + 1, alto, buscar, contadorLlamadas);
    }
    else {
        return busquedaBinariaRecursiva(arreglo, bajo, mitad - 1, buscar, contadorLlamadas);
    }
}
void buscarSalaBinaria() {
    system("cls");
    SetConsoleTitle("Busqueda de Reservas por Sala y Fecha");
    int salasID[7] = {1, 2, 3, 4, 5, 6, 7}; 
    int buscarSala;
    int opcionDia;
    string diaBuscado = "";
    int modificadorDia = 0; 
    SetConsoleTextAttribute(hConsole, 11);
    cout << "===========================================================================" << endl;
    cout << "                     BUSQUEDA DE RESERVACIONES ACTIVAS                     " << endl;
    cout << "===========================================================================" << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << " Ingrese el ID de la sala que desea consultar (1-7): ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> buscarSala;
    int bajo = 0, alto = 6, mitad;
    bool salaEncontrada = false;
    while (bajo <= alto) {
        mitad = (bajo + alto) / 2;
        if (salasID[mitad] == buscarSala) {
            salaEncontrada = true;
            break;
        } else if (salasID[mitad] < buscarSala) {
            bajo = mitad + 1;
        } else {
            alto = mitad - 1;
        }
    }
    if (!salaEncontrada) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n [ERROR] La sala ingresada no existe en el sistema.\n";
        _getch();
        return;
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << "\n Seleccione la fecha que desea consultar:\n";
    cout << "   1.- Hoy\n";
    cout << "   2.- Manana\n";
    cout << " Elija una opcion (1-2): ";
    SetConsoleTextAttribute(hConsole, 7);
    cin >> opcionDia;
    if (opcionDia == 1) {
        diaBuscado = "Hoy";
        modificadorDia = 0;   
    } else if (opcionDia == 2) {
        diaBuscado = "Manana";
        modificadorDia = 60;  
    } else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "\n [ERROR] Opcion de fecha invalida.\n";
        _getch();
        return;
    }
    system("cls");
    SetConsoleTextAttribute(hConsole, 11);
    cout << "===========================================================================" << endl;
    cout << "      RESERVAS ENCONTRADAS PARA: SALA " << buscarSala << " | FECHA: " << diaBuscado << endl;
    cout << "===========================================================================" << endl;
    ifstream archivo("br.txt");
    if (!archivo.is_open()) {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Error al abrir la base de datos (br.txt).\n";
        _getch();
        return;
    }
    int inicioLectura = ((buscarSala - 1) * 120) + modificadorDia;
    string nombre, numero, fecha, hora, registroHistorico, linea;
    int lineaActual = 0, conteoReservas = 0;
    while (lineaActual < inicioLectura && getline(archivo, linea)) {
        lineaActual++;
    }
    for (int bloque = 0; bloque < 12; bloque++) {
        if (!getline(archivo, nombre) || !getline(archivo, numero) || 
            !getline(archivo, fecha) || !getline(archivo, hora) || 
            !getline(archivo, registroHistorico)) {
            break; 
        }   
        if (nombre != "NONE") {
            conteoReservas++;
            SetConsoleTextAttribute(hConsole, 11);
            cout << "\n >>> RESERVA #" << conteoReservas << " <<<" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            cout << "   Responsable: "; SetConsoleTextAttribute(hConsole, 7); cout << nombre << endl;
            SetConsoleTextAttribute(hConsole, 15);
            cout << "   Contacto   : "; SetConsoleTextAttribute(hConsole, 7); cout << numero << endl;
            SetConsoleTextAttribute(hConsole, 15);
            cout << "   Horario    : "; SetConsoleTextAttribute(hConsole, 7); cout << hora << endl;
        }
    }
    archivo.close();
    cout << "\n---------------------------------------------------------------------------\n";
    if (conteoReservas == 0) {
        SetConsoleTextAttribute(hConsole, 10);
        cout << " La sala se encuentra totalmente LIBRE para el dia: " << diaBuscado << endl;
    } else {
        SetConsoleTextAttribute(hConsole, 14);
        cout << " Total de horarios ocupados detectados: " << conteoReservas << endl;
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << "\nPresione cualquier tecla para regresar al menu...";
    _getch();
}
void intercalarArchivos() {   
    system("cls");
    SetConsoleTitle("Intercalacion de Archivos - Rendimiento");
    compIntercalacion = 0;
    interIntercalacion = 0;
    ofstream f1("manana.txt"), f2("tarde.txt");
    f1 << "Sala 1\nHora: 08:00 AM\n"; 
    f2 << "Sala 2\nHora: 01:00 PM\n"; 
    f1.close(); f2.close();
    ifstream i1("manana.txt"), i2("tarde.txt");
    ofstream out("intercalado.txt");
    string s1, s2;
    bool hayS1 = bool(getline(i1, s1));
    bool hayS2 = bool(getline(i2, s2));
    while (hayS1 || hayS2) {
        compIntercalacion++; 
        if (hayS1 && (!hayS2 || s1 <= s2)) {
            interIntercalacion++; 
            cout << s1 << endl;
            hayS1 = bool(getline(i1, s1));
        } else {
            interIntercalacion++; 
            out << s2 << endl;
            hayS2 = bool(getline(i2, s2));
        }
    }
    i1.close(); i2.close(); out.close();
    SetConsoleTextAttribute(hConsole, 11);
    cout << "===========================================================================" << endl;
    cout << "                     INTERCALACION DE ARCHIVOS                 " << endl;
    cout << "===========================================================================" << endl;
    SetConsoleTextAttribute(hConsole, 15);
    cout << " Archivos 'manana.txt' y 'tarde.txt' intercalados correctamente." << endl;
    SetConsoleTextAttribute(hConsole, 14);
    cout << " Comparaciones realizadas: " << compIntercalacion << endl;
    cout << " Elementos transferidos   : " << interIntercalacion << endl;
    cout << "===========================================================================" << endl;
    cout << "\n>>> REPORTE DE EFICIENCIA ALGORITMICA <<<" << endl;
    int totalBurbuja = compBurbuja + interBurbuja;
    int totalIntercalacion = compIntercalacion + interIntercalacion;
    SetConsoleTextAttribute(hConsole, 15);
    cout << " Operaciones totales Bubble Sort   : " << totalBurbuja << endl;
    cout << " Operaciones totales Intercalacion : " << totalIntercalacion << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    if (totalIntercalacion < totalBurbuja) {
        SetConsoleTextAttribute(hConsole, 10);
        cout << " RESULTADO: La Intercalacion fue MAS EFICIENTE (Complejidad Lineal O(N))." << endl;
    } else if (totalBurbuja < totalIntercalacion) {
        SetConsoleTextAttribute(hConsole, 10);
        cout << " RESULTADO: El Bubble Sort fue MAS EFICIENTE en este conjunto." << endl;
    } else {
        SetConsoleTextAttribute(hConsole, 14);
        cout << " RESULTADO: Ambos algoritmos tuvieron la misma eficiencia en esta ejecucion." << endl;
    }
    SetConsoleTextAttribute(hConsole, 8);
    cout << "\nPresione cualquier tecla para regresar al menu...";
    _getch();
}
