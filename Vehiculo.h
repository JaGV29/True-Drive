#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
#include "Conductor.h"

// Categorías disponibles para el vehículo
enum class Categoria {
    Ejecutiva,
    Tradicional
};

class Vehiculo {
private:
    int         correlativo;    // Identificador único secuencial
    std::string placa;          // Ej: P-123456
    std::string numeroMotor;
    std::string modelo;
    int         anio;
    Categoria   categoria;
    Conductor   conductor;      // Conductor asignado al vehículo

    // Datos del viaje activo (vacíos cuando el vehículo está en espera)
    std::string puntoSalida;
    std::string destino;
    double      costo;

public:
    // Constructor por defecto
    Vehiculo();

    // Constructor con parámetros
    Vehiculo(int correlativo,
             const std::string& placa,
             const std::string& numeroMotor,
             const std::string& modelo,
             int anio,
             Categoria categoria,
             const Conductor& conductor);

    // Getters — datos del vehículo
    int         getCorrelativo()   const;
    std::string getPlaca()         const;
    std::string getNumeroMotor()   const;
    std::string getModelo()        const;
    int         getAnio()          const;
    Categoria   getCategoria()     const;
    Conductor   getConductor()     const;

    // Getters — datos del viaje activo
    std::string getPuntoSalida()   const;
    std::string getDestino()       const;
    double      getCosto()         const;

    // Setters — datos del vehículo
    void setCorrelativo(int correlativo);
    void setPlaca(const std::string& placa);
    void setNumeroMotor(const std::string& numeroMotor);
    void setModelo(const std::string& modelo);
    void setAnio(int anio);
    void setCategoria(Categoria categoria);
    void setConductor(const Conductor& conductor);

    // Setters — datos del viaje activo
    void setPuntoSalida(const std::string& p);
    void setDestino(const std::string& d);
    void setCosto(double c);

    // Devuelve la categoría como texto legible ("Ejecutiva" / "Tradicional")
    std::string getCategoriaStr() const;

    // Mostrar información completa del vehículo en consola
    void mostrar() const;
};

#endif // VEHICULO_H
