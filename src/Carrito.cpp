#include "../include/Carrito.h"
#include <algorithm>
#include <iostream>

Carrito& Carrito::operator+=(const Videojuego& juego) {
    productos.push_back(juego);
    return *this;
}

Carrito& Carrito::operator-=(const Videojuego& juego) {
    const auto encontrado = std::find_if(
        productos.begin(), productos.end(),
        [&juego](const Videojuego& producto) {
            return producto.getNombre() == juego.getNombre();
        });

    if (encontrado != productos.end()) {
        productos.erase(encontrado);
    } else {
        std::cout << "El videojuego no se encuentra en el carrito.\n";
    }

    return *this;
}

double Carrito::calcularTotal() const {
    double total = 0.0;
    for (const Videojuego& juego : productos) {
        total += juego.getPrecio();
    }
    return total;
}

void Carrito::vaciar() {
    productos.clear();
}

void Carrito::mostrarCarrito() const {
    if (productos.empty()) {
        std::cout << "El carrito esta vacio.\n";
        return;
    }

    for (const Videojuego& juego : productos) {
        juego.mostrarInfo();
    }
    std::cout << "Total: S/ " << calcularTotal() << '\n';
}

const std::vector<Videojuego>& Carrito::getProductos() const {
    return productos;
}

void mostrarResumenCompra(const Carrito& carrito) {
    std::cout << "Resumen de compra\n";
    std::cout << "Cantidad de videojuegos: " << carrito.productos.size() << '\n';
    carrito.mostrarCarrito();
}
