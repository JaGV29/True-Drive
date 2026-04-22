#include "Conductor.h"
#include <iostream>

Conductor::Conductor()
    : nombre(""), apellido(""), dui(""), seguroSocial(""), telefono("") {}

Conductor::Conductor(const std::string& nombre,
                     const std::string& apellido,
                     const std::string& dui,
                     const std::string& seguroSocial,
                     const std::string& telefono)
    : nombre(nombre), apellido(apellido), dui(dui),
      seguroSocial(seguroSocial), telefono(telefono) {}

std::string Conductor::getNombre()       const { return nombre; }
std::string Conductor::getApellido()     const { return apellido; }
std::string Conductor::getDui()          const { return dui; }
std::string Conductor::getSeguroSocial() const { return seguroSocial; }
std::string Conductor::getTelefono()     const { return telefono; }

void Conductor::setNombre(const std::string& n)       { nombre = n; }
void Conductor::setApellido(const std::string& a)     { apellido = a; }
void Conductor::setDui(const std::string& d)          { dui = d; }
void Conductor::setSeguroSocial(const std::string& s) { seguroSocial = s; }
void Conductor::setTelefono(const std::string& t)     { telefono = t; }

void Conductor::mostrar() const {
    std::cout << "    Nombre        : " << nombre << " " << apellido << "\n"
              << "    DUI           : " << dui           << "\n"
              << "    Seguro Social : " << seguroSocial  << "\n"
              << "    Teléfono      : " << telefono      << "\n";
}
