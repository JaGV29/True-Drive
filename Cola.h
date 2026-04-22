#ifndef COLA_H
#define COLA_H

#include <vector>

template <typename T>
class Cola {
private:
    struct Nodo {
        T     dato;
        Nodo* siguiente;
        Nodo(const T& dato) : dato(dato), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* fondo;
    int   cantidad;

public:
    Cola();
    ~Cola();

    void encolar(const T& elemento);
    T    desencolar();

    T&       verFrente();
    const T& verFrente() const;

    bool estaVacia()   const;
    int  getCantidad() const;
    void limpiar();

    // Copia todos los elementos a un vector para recorrer sin modificar la cola
    std::vector<T> toVector() const;
};

// ── Implementaciones (deben estar en el .h por ser template) ──────────────────

template <typename T>
Cola<T>::Cola() : frente(nullptr), fondo(nullptr), cantidad(0) {}

template <typename T>
Cola<T>::~Cola() { limpiar(); }

template <typename T>
void Cola<T>::encolar(const T& elemento) {
    Nodo* nuevo = new Nodo(elemento);
    if (fondo == nullptr)
        frente = fondo = nuevo;
    else {
        fondo->siguiente = nuevo;
        fondo = nuevo;
    }
    cantidad++;
}

template <typename T>
T Cola<T>::desencolar() {
    T dato    = frente->dato;
    Nodo* tmp = frente;
    frente    = frente->siguiente;
    if (frente == nullptr) fondo = nullptr;
    delete tmp;
    cantidad--;
    return dato;
}

template <typename T>
T& Cola<T>::verFrente() { return frente->dato; }

template <typename T>
const T& Cola<T>::verFrente() const { return frente->dato; }

template <typename T>
bool Cola<T>::estaVacia() const { return frente == nullptr; }

template <typename T>
int Cola<T>::getCantidad() const { return cantidad; }

template <typename T>
void Cola<T>::limpiar() {
    while (!estaVacia()) desencolar();
}

template <typename T>
std::vector<T> Cola<T>::toVector() const {
    std::vector<T> resultado;
    Nodo* actual = frente;
    while (actual != nullptr) {
        resultado.push_back(actual->dato);
        actual = actual->siguiente;
    }
    return resultado;
}

#endif // COLA_H
