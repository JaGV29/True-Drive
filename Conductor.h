#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include <string>

class Conductor {
private:
    std::string nombre;
    std::string apellido;
    std::string dui;           // Formato: 00000000-0
    std::string seguroSocial;  // Número de seguro social
    std::string telefono;

public:
    // Constructor por defecto
    Conductor();

    // Constructor con parámetros
    Conductor(const std::string& nombre,
              const std::string& apellido,
              const std::string& dui,
              const std::string& seguroSocial,
              const std::string& telefono);

    // Getters
    std::string getNombre()       const;
    std::string getApellido()     const;
    std::string getDui()          const;
    std::string getSeguroSocial() const;
    std::string getTelefono()     const;

    // Setters
    void setNombre(const std::string& nombre);
    void setApellido(const std::string& apellido);
    void setDui(const std::string& dui);
    void setSeguroSocial(const std::string& seguroSocial);
    void setTelefono(const std::string& telefono);

    // Mostrar información del conductor en consola
    void mostrar() const;
};

#endif // CONDUCTOR_H
