#ifndef GESTORFLOTA_H
#define GESTORFLOTA_H

#include "Cola.h"
#include "Vehiculo.h"
#include <string>

class GestorFlota {
private:
    Cola<Vehiculo> vehiculosEnEspera;
    Cola<Vehiculo> vehiculosEnRuta;
    int            contadorCorrelativo;

    bool verificarDuplicado(const std::string& placa,
                            const std::string& numeroMotor,
                            const std::string& dui,
                            const std::string& seguroSocial,
                            std::string& campoDuplicado) const;

    // Tabla estándar: vehículos en espera
    void imprimirEncabezadoTabla()              const;
    void imprimirFilaVehiculo(const Vehiculo& v) const;

    // Tabla extendida: vehículos en ruta (incluye datos del viaje)
    void imprimirEncabezadoTablaRuta()          const;
    void imprimirFilaRuta(const Vehiculo& v)    const;

public:
    GestorFlota();

    void registrarVehiculo();
    void despacharVehiculo();
    void recibirVehiculo();

    void mostrarVehiculos()         const;
    void mostrarVehiculosEnEspera() const;
    void mostrarVehiculosEnRuta()   const;

    int  totalEnEspera() const;
    int  totalEnRuta()   const;
    void mostrarResumen() const;
};

#endif // GESTORFLOTA_H
