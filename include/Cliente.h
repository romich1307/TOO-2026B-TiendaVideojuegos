#ifndef CLIENTE_H
#define CLIENTE_H

#include "Carrito.h"
#include <string>

class Cliente {
private:
    std::string nombre;
    double saldo;
    Carrito carrito;

public:
    Cliente(std::string nombre, double saldo);

    std::string getNombre() const;
    double getSaldo() const;
    void mostrarDatos() const;

    void agregarAlCarrito(const Videojuego& juego);
    void quitarDelCarrito(const Videojuego& juego);
    void vaciarCarrito();
    const Carrito& getCarrito() const;
    bool finalizarCompra();
};

#endif
