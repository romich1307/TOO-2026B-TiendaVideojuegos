#ifndef TIENDA_H
#define TIENDA_H

#include "Videojuego.h"
#include "Cliente.h"
#include <string>
#include <vector>

class Tienda {
private:
    std::vector<Videojuego> catalogo;
    Cliente cliente;

public:
    Tienda();

    void agregarVideojuego(const Videojuego& juego);
    void mostrarCatalogo() const;

    int buscarPorNombre(const std::string& nombre) const;

    void filtrarPorGenero(const std::string& genero) const;
    void filtrarPorPrecio(double precioMaximo) const;

    void finalizarCompra();
    void ejecutar();
};

#endif