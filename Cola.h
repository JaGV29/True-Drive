#ifndef COLA_H
#define COLA_H

#include <optional>
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

    // Elimina el primer elemento que cumple el predicado y lo devuelve
    template<typename Pred>
    std::optional<T> eliminarSi(Pred pred);

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
template <typename Pred>
std::optional<T> Cola<T>::eliminarSi(Pred pred) {
    Nodo* anterior = nullptr;
    Nodo* actual   = frente;
    while (actual != nullptr) {
        if (pred(actual->dato)) {
            T dato = actual->dato;
            if (anterior == nullptr)
                frente = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;
            if (actual == fondo)
                fondo = anterior;
            delete actual;
            cantidad--;
            return dato;
        }
        anterior = actual;
        actual   = actual->siguiente;
    }
    return std::nullopt;
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
