#include "GestorFlota.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

// ── Helpers de entrada (visibles solo en este .cpp) ───────────────────────────

static std::string leerLinea(const std::string& prompt) {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);
    return valor;
}

static int leerEntero(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Entrada inválida. Ingrese un número entero.\n";
    }
}

static double leerDouble(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor && valor >= 0.0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Valor inválido. Ingrese un número positivo.\n";
    }
}

static Categoria leerCategoria() {
    int op;
    while (true) {
        std::cout << "  Categoría (1. Ejecutiva / 2. Tradicional): ";
        if (std::cin >> op && (op == 1 || op == 2)) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return (op == 1) ? Categoria::Ejecutiva : Categoria::Tradicional;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Opción inválida. Ingrese 1 o 2.\n";
    }
}

// ── Constructor ───────────────────────────────────────────────────────────────

GestorFlota::GestorFlota() : contadorCorrelativo(1) {}

// ── Validación de duplicados ──────────────────────────────────────────────────

bool GestorFlota::verificarDuplicado(const std::string& placa,
                                     const std::string& numeroMotor,
                                     const std::string& dui,
                                     const std::string& seguroSocial,
                                     std::string& campoDuplicado) const {
    std::vector<Vehiculo> todos = vehiculosEnEspera.toVector();
    std::vector<Vehiculo> enRuta = vehiculosEnRuta.toVector();
    todos.insert(todos.end(), enRuta.begin(), enRuta.end());

    for (const auto& v : todos) {
        if (v.getPlaca() == placa) {
            campoDuplicado = "placa (" + placa + ")";
            return true;
        }
        if (v.getNumeroMotor() == numeroMotor) {
            campoDuplicado = "número de motor (" + numeroMotor + ")";
            return true;
        }
        if (v.getConductor().getDui() == dui) {
            campoDuplicado = "DUI del conductor (" + dui + ")";
            return true;
        }
        if (v.getConductor().getSeguroSocial() == seguroSocial) {
            campoDuplicado = "seguro social (" + seguroSocial + ")";
            return true;
        }
    }
    return false;
}

// ── Registro ──────────────────────────────────────────────────────────────────

void GestorFlota::registrarVehiculo() {
    std::cout << "\n  ┌──────────────────────────────────────┐\n";
    std::cout << "  │      REGISTRO DE NUEVO VEHÍCULO      │\n";
    std::cout << "  └──────────────────────────────────────┘\n";

    std::cout << "\n  DATOS DEL CONDUCTOR\n";
    std::cout << "  ───────────────────\n";
    std::string nombre       = leerLinea("  Nombre          : ");
    std::string apellido     = leerLinea("  Apellido        : ");
    std::string dui          = leerLinea("  DUI (00000000-0): ");
    std::string seguroSocial = leerLinea("  Seguro social   : ");
    std::string telefono     = leerLinea("  Teléfono        : ");

    std::cout << "\n  DATOS DEL VEHÍCULO\n";
    std::cout << "  ──────────────────\n";
    std::string placa       = leerLinea("  Placa           : ");
    std::string numeroMotor = leerLinea("  Número de motor : ");
    std::string modelo      = leerLinea("  Modelo          : ");
    int         anio        = leerEntero("  Año             : ");

    if (anio < 2010) {
        std::cout << "\n  [ERROR] Año " << anio
                  << " rechazado. Solo se aceptan vehículos del año 2010 en adelante.\n";
        return;
    }

    std::string campoDuplicado;
    if (verificarDuplicado(placa, numeroMotor, dui, seguroSocial, campoDuplicado)) {
        std::cout << "\n  [ERROR] Ya existe un registro con el mismo "
                  << campoDuplicado << ". Registro rechazado.\n";
        return;
    }

    Categoria   categoria = (anio >= 2015) ? Categoria::Ejecutiva : Categoria::Tradicional;
    std::string catStr    = (categoria == Categoria::Ejecutiva) ? "Ejecutiva" : "Tradicional";

    Conductor conductor(nombre, apellido, dui, seguroSocial, telefono);
    Vehiculo  vehiculo(contadorCorrelativo++, placa, numeroMotor, modelo,
                       anio, categoria, conductor);
    vehiculosEnEspera.encolar(vehiculo);

    std::cout << "\n  [OK] Vehículo registrado en cola de espera.\n";
    std::cout << "       Categoría asignada: " << catStr << "\n";
}

// ── Despacho ──────────────────────────────────────────────────────────────────

void GestorFlota::despacharVehiculo() {
    if (vehiculosEnEspera.estaVacia()) {
        std::cout << "\n  No hay vehículos disponibles en espera.\n";
        return;
    }

    std::cout << "\n  ASIGNACIÓN DE VIAJE\n";
    std::cout << "  ───────────────────\n";

    Categoria   catDeseada = leerCategoria();
    std::string catStr     = (catDeseada == Categoria::Ejecutiva) ? "Ejecutiva" : "Tradicional";

    // Iterar buscando el PRIMER vehículo de la categoría solicitada
    std::vector<Vehiculo> vec = vehiculosEnEspera.toVector();
    int idx = -1;
    for (int i = 0; i < (int)vec.size(); i++) {
        if (vec[i].getCategoria() == catDeseada) { idx = i; break; }
    }

    if (idx == -1) {
        std::cout << "\n  No hay vehículos de categoría " << catStr
                  << " disponibles en este momento.\n";
        return;
    }

    // Solicitar datos del viaje
    std::string origen  = leerLinea("  Punto de salida    : ");
    std::string destino = leerLinea("  Destino            : ");
    double      costo   = leerDouble("  Costo del viaje ($): ");

    // Asignar viaje y extraer de la cola
    vec[idx].setPuntoSalida(origen);
    vec[idx].setDestino(destino);
    vec[idx].setCosto(costo);
    Vehiculo asignado = vec[idx];

    // Reconstruir vehiculosEnEspera sin el vehículo extraído
    vehiculosEnEspera.limpiar();
    for (int i = 0; i < (int)vec.size(); i++) {
        if (i != idx) vehiculosEnEspera.encolar(vec[i]);
    }
    vehiculosEnRuta.encolar(asignado);

    std::cout << "\n  [OK] Vehículo asignado exitosamente.\n";
    std::cout << "  ─────────────────────────────────────\n";
    std::cout << "  Correlativo : " << asignado.getCorrelativo()                              << "\n";
    std::cout << "  Placa       : " << asignado.getPlaca()                                    << "\n";
    std::cout << "  Categoría   : " << asignado.getCategoriaStr()                             << "\n";
    std::cout << "  Conductor   : " << asignado.getConductor().getNombre()
              << " "                << asignado.getConductor().getApellido()                  << "\n";
    std::cout << "  Origen      : " << origen                                                 << "\n";
    std::cout << "  Destino     : " << destino                                                << "\n";
    std::cout << "  Costo       : $" << std::fixed << std::setprecision(2) << costo           << "\n";
}

// ── Recepción ─────────────────────────────────────────────────────────────────

void GestorFlota::recibirVehiculo() {
    if (vehiculosEnRuta.estaVacia()) {
        std::cout << "\n  No hay vehículos en ruta actualmente.\n";
        return;
    }

    mostrarVehiculosEnRuta();

    int correlativo = leerEntero("\n  Correlativo del vehículo que retorna: ");

    std::vector<Vehiculo> vec = vehiculosEnRuta.toVector();
    int idx = -1;
    for (int i = 0; i < (int)vec.size(); i++) {
        if (vec[i].getCorrelativo() == correlativo) { idx = i; break; }
    }

    if (idx == -1) {
        std::cout << "\n  [ERROR] No se encontró el correlativo "
                  << correlativo << " entre los vehículos en ruta.\n";
        return;
    }

    Vehiculo retornado = vec[idx];

    // Reconstruir vehiculosEnRuta sin el vehículo que retorna
    vehiculosEnRuta.limpiar();
    for (int i = 0; i < (int)vec.size(); i++) {
        if (i != idx) vehiculosEnRuta.encolar(vec[i]);
    }

    // Limpiar datos del viaje y reingresar AL FINAL de espera
    retornado.setPuntoSalida("");
    retornado.setDestino("");
    retornado.setCosto(0.0);
    vehiculosEnEspera.encolar(retornado);

    std::cout << "\n  [OK] Vehículo reingresado al final de la cola de espera.\n";
    std::cout << "       Correlativo : " << retornado.getCorrelativo()                       << "\n";
    std::cout << "       Placa       : " << retornado.getPlaca()                             << "\n";
    std::cout << "       Conductor   : " << retornado.getConductor().getNombre()
              << " "                     << retornado.getConductor().getApellido()           << "\n";
}

// ── Tabla estándar: vehículos en espera ──────────────────────────────────────

static const int W_CORR  =  5;
static const int W_PLACA = 11;
static const int W_MOTOR = 15;
static const int W_MODEL = 22;
static const int W_ANIO  =  6;
static const int W_CAT   = 13;
static const int W_COND  = 22;
static const int W_TOTAL = W_CORR + W_PLACA + W_MOTOR + W_MODEL
                         + W_ANIO + W_CAT + W_COND;

void GestorFlota::imprimirEncabezadoTabla() const {
    std::cout << std::left
              << std::setw(W_CORR)  << "Corr"
              << std::setw(W_PLACA) << "Placa"
              << std::setw(W_MOTOR) << "Motor"
              << std::setw(W_MODEL) << "Modelo"
              << std::setw(W_ANIO)  << "Año"
              << std::setw(W_CAT)   << "Categoría"
              << std::setw(W_COND)  << "Conductor"
              << "\n" << std::string(W_TOTAL, '-') << "\n";
}

void GestorFlota::imprimirFilaVehiculo(const Vehiculo& v) const {
    std::string cond = v.getConductor().getNombre() + " " + v.getConductor().getApellido();
    std::cout << std::left
              << std::setw(W_CORR)  << v.getCorrelativo()
              << std::setw(W_PLACA) << v.getPlaca()
              << std::setw(W_MOTOR) << v.getNumeroMotor()
              << std::setw(W_MODEL) << v.getModelo()
              << std::setw(W_ANIO)  << v.getAnio()
              << std::setw(W_CAT)   << v.getCategoriaStr()
              << std::setw(W_COND)  << cond
              << "\n";
}

// ── Tabla extendida: vehículos en ruta (con datos del viaje) ─────────────────

static const int WR_CORR  =  5;
static const int WR_PLACA = 11;
static const int WR_CAT   = 13;
static const int WR_COND  = 22;
static const int WR_ORIG  = 18;
static const int WR_DEST  = 18;
static const int WR_COST  = 10;
static const int WR_TOTAL = WR_CORR + WR_PLACA + WR_CAT + WR_COND
                          + WR_ORIG + WR_DEST + WR_COST;

void GestorFlota::imprimirEncabezadoTablaRuta() const {
    std::cout << std::left
              << std::setw(WR_CORR)  << "Corr"
              << std::setw(WR_PLACA) << "Placa"
              << std::setw(WR_CAT)   << "Categoría"
              << std::setw(WR_COND)  << "Conductor"
              << std::setw(WR_ORIG)  << "Origen"
              << std::setw(WR_DEST)  << "Destino"
              << std::setw(WR_COST)  << "Costo"
              << "\n" << std::string(WR_TOTAL, '-') << "\n";
}

void GestorFlota::imprimirFilaRuta(const Vehiculo& v) const {
    std::string cond = v.getConductor().getNombre() + " " + v.getConductor().getApellido();
    std::ostringstream costoStr;
    costoStr << "$" << std::fixed << std::setprecision(2) << v.getCosto();

    std::cout << std::left
              << std::setw(WR_CORR)  << v.getCorrelativo()
              << std::setw(WR_PLACA) << v.getPlaca()
              << std::setw(WR_CAT)   << v.getCategoriaStr()
              << std::setw(WR_COND)  << cond
              << std::setw(WR_ORIG)  << v.getPuntoSalida()
              << std::setw(WR_DEST)  << v.getDestino()
              << std::setw(WR_COST)  << costoStr.str()
              << "\n";
}

// ── Consultas públicas ────────────────────────────────────────────────────────

void GestorFlota::mostrarVehiculosEnEspera() const {
    std::cout << "\n  VEHÍCULOS DISPONIBLES EN ESPERA ("
              << vehiculosEnEspera.getCantidad() << ")\n";
    if (vehiculosEnEspera.estaVacia()) { std::cout << "  (ninguno)\n"; return; }
    imprimirEncabezadoTabla();
    for (const auto& v : vehiculosEnEspera.toVector()) imprimirFilaVehiculo(v);
}

void GestorFlota::mostrarVehiculosEnRuta() const {
    std::cout << "\n  VEHÍCULOS EN RUTA ("
              << vehiculosEnRuta.getCantidad() << ")\n";
    if (vehiculosEnRuta.estaVacia()) { std::cout << "  (ninguno)\n"; return; }
    imprimirEncabezadoTablaRuta();
    for (const auto& v : vehiculosEnRuta.toVector()) imprimirFilaRuta(v);
}

void GestorFlota::mostrarVehiculos() const {
    mostrarVehiculosEnEspera();
    std::cout << "\n";
    mostrarVehiculosEnRuta();
}

int GestorFlota::totalEnEspera() const { return vehiculosEnEspera.getCantidad(); }
int GestorFlota::totalEnRuta()   const { return vehiculosEnRuta.getCantidad(); }

void GestorFlota::mostrarResumen() const {
    int espera = totalEnEspera();
    int ruta   = totalEnRuta();
    mostrarVehiculos();
    std::cout << "\n"
              << "  ╔══════════════════════════════╗\n"
              << "  ║      RESUMEN DE LA FLOTA     ║\n"
              << "  ╠══════════════════════════════╣\n"
              << "  ║  En espera  : " << std::left << std::setw(15) << espera         << "║\n"
              << "  ║  En ruta    : "              << std::setw(15) << ruta            << "║\n"
              << "  ║  Total      : "              << std::setw(15) << (espera + ruta) << "║\n"
              << "  ╚══════════════════════════════╝\n";
}
