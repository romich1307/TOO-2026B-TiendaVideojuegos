#include "../include/Cliente.h"
#include <iostream>

// Crear cliente
Cliente::Cliente(std::string nombre, double saldo) {
    this->nombre = nombre;
    this->saldo = saldo;
}

// Obtener nombre
std::string Cliente::getNombre() const {
    return nombre;
}

// Obtener saldo
double Cliente::getSaldo() const {
    return saldo;
}

// Mostrar datos
void Cliente::mostrarDatos() const {
    std::cout << "Nombre: " << nombre << '\n';
    std::cout << "Saldo: S/ " << saldo << '\n';
}

// Agregar juego
void Cliente::agregarAlCarrito(const Videojuego& juego) {
    carrito += juego;
}

// Quitar juego
void Cliente::quitarDelCarrito(const Videojuego& juego) {
    carrito -= juego;
}

// Vaciar carrito
void Cliente::vaciarCarrito() {
    carrito.vaciar();
}

// Consultar carrito
const Carrito& Cliente::getCarrito() const {
    return carrito;
}

// Finalizar compra
bool Cliente::finalizarCompra() {
    if (carrito.getProductos().empty()) {
        std::cout << "El carrito esta vacio.\n";
        return false;
    }

    double total = carrito.calcularTotal();

    if (saldo < total) {
        std::cout << "Saldo insuficiente para realizar la compra.\n";
        return false;
    }

    mostrarResumenCompra(carrito);
    saldo -= total;
    carrito.vaciar();

    std::cout << "Compra realizada.\n";
    std::cout << "Saldo restante: S/ " << saldo << '\n';
    return true;
}
