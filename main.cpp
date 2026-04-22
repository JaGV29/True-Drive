#include <iostream>
#include <limits>
#include <string>
#include "GestorFlota.h"

// ── Códigos ANSI ──────────────────────────────────────────────────────────────
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

// ── Utilidades de consola ─────────────────────────────────────────────────────

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Espera un Enter; compatible con leerLinea/leerEntero del gestor
void pausar() {
    std::cout << "\n" YELLOW "  Presione Enter para continuar..." RESET;
    std::string _;
    std::getline(std::cin, _);
}

// ── Menú principal ────────────────────────────────────────────────────────────

int mostrarMenu() {
    std::cout << BOLD CYAN
              << "  ╔════════════════════════════════════════════╗\n"
              << "  ║        TRUEDRIVE  -  Gestión de Flota      ║\n"
              << "  ╚════════════════════════════════════════════╝\n"
              << RESET "\n";

    std::cout << GREEN
              << "  [1]  Registrar vehículo y conductor\n"
              << "  [2]  Asignar vehículo a cliente\n"
              << "  [3]  Registrar retorno de vehículo\n"
              << "  [4]  Ver vehículos disponibles\n"
              << "  [5]  Ver vehículos en ruta\n"
              << "  [6]  Ver resumen general\n"
              << RESET "\n"
              << "  ────────────────────────────────────────────\n"
              << RED
              << "  [0]  Salir\n"
              << RESET "\n"
              << "  Opción: ";

    int opcion = 0;
    if (!(std::cin >> opcion)) {
        std::cin.clear();
        opcion = 0;   // EOF o entrada inválida → salir
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opcion;
}

// ── Punto de entrada ──────────────────────────────────────────────────────────

int main() {
    GestorFlota gestor;
    int opcion;

    do {
        limpiarPantalla();
        opcion = mostrarMenu();

        switch (opcion) {
            case 1:
                gestor.registrarVehiculo();
                pausar();
                break;

            case 2:
                gestor.despacharVehiculo();
                pausar();
                break;

            case 3:
                gestor.recibirVehiculo();
                pausar();
                break;

            case 4:
                gestor.mostrarVehiculosEnEspera();
                pausar();
                break;

            case 5:
                gestor.mostrarVehiculosEnRuta();
                pausar();
                break;

            case 6:
                gestor.mostrarResumen();
                pausar();
                break;

            case 0:
                std::cout << "\n" CYAN "  Cerrando TrueDrive. Hasta luego.\n" RESET;
                break;

            default:
                std::cout << RED "\n  Opción no válida. Intente de nuevo.\n" RESET;
                pausar();
                break;
        }

    } while (opcion != 0);

    return 0;
}
