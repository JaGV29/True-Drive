#include "Vehiculo.h"
#include <iostream>

Vehiculo::Vehiculo()
    : correlativo(0), placa(""), numeroMotor(""), modelo(""),
      anio(0), categoria(Categoria::Tradicional), conductor(),
      puntoSalida(""), destino(""), costo(0.0) {}

Vehiculo::Vehiculo(int correlativo,
                   const std::string& placa,
                   const std::string& numeroMotor,
                   const std::string& modelo,
                   int anio,
                   Categoria categoria,
                   const Conductor& conductor)
    : correlativo(correlativo), placa(placa), numeroMotor(numeroMotor),
      modelo(modelo), anio(anio), categoria(categoria), conductor(conductor),
      puntoSalida(""), destino(""), costo(0.0) {}

// Getters — vehículo
int         Vehiculo::getCorrelativo()   const { return correlativo; }
std::string Vehiculo::getPlaca()         const { return placa; }
std::string Vehiculo::getNumeroMotor()   const { return numeroMotor; }
std::string Vehiculo::getModelo()        const { return modelo; }
int         Vehiculo::getAnio()          const { return anio; }
Categoria   Vehiculo::getCategoria()     const { return categoria; }
Conductor   Vehiculo::getConductor()     const { return conductor; }

// Getters — viaje
std::string Vehiculo::getPuntoSalida()   const { return puntoSalida; }
std::string Vehiculo::getDestino()       const { return destino; }
double      Vehiculo::getCosto()         const { return costo; }

// Setters — vehículo
void Vehiculo::setCorrelativo(int c)                { correlativo = c; }
void Vehiculo::setPlaca(const std::string& p)       { placa = p; }
void Vehiculo::setNumeroMotor(const std::string& n) { numeroMotor = n; }
void Vehiculo::setModelo(const std::string& m)      { modelo = m; }
void Vehiculo::setAnio(int a)                       { anio = a; }
void Vehiculo::setCategoria(Categoria c)            { categoria = c; }
void Vehiculo::setConductor(const Conductor& c)     { conductor = c; }

// Setters — viaje
void Vehiculo::setPuntoSalida(const std::string& p) { puntoSalida = p; }
void Vehiculo::setDestino(const std::string& d)     { destino = d; }
void Vehiculo::setCosto(double c)                   { costo = c; }

std::string Vehiculo::getCategoriaStr() const {
    return (categoria == Categoria::Ejecutiva) ? "Ejecutiva" : "Tradicional";
}

void Vehiculo::mostrar() const {
    std::cout << "  Correlativo   : " << correlativo       << "\n"
              << "  Placa         : " << placa             << "\n"
              << "  Número Motor  : " << numeroMotor       << "\n"
              << "  Modelo        : " << modelo            << "\n"
              << "  Año           : " << anio              << "\n"
              << "  Categoría     : " << getCategoriaStr() << "\n"
              << "  Conductor     :\n";
    conductor.mostrar();
}
