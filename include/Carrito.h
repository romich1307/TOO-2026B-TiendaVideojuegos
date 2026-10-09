#ifndef CARRITO_H
#define CARRITO_H

#include "Videojuego.h"
#include <vector>

class Carrito {
private:
    std::vector<Videojuego> productos;

public:
    Carrito& operator+=(const Videojuego& juego);
    Carrito& operator-=(const Videojuego& juego);
    double calcularTotal() const;
    void vaciar();
    void mostrarCarrito() const;
    const std::vector<Videojuego>& getProductos() const;

    friend void mostrarResumenCompra(const Carrito& carrito);
};

#endif
