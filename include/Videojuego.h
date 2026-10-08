
#ifndef VIDEOJUEGO_H
#define VIDEOJUEGO_H

#include <string>
using namespace std;

class Videojuego {
private:
    string nombre;
    string genero;
    double precio;
    int stock;

public:
    // Constructor
    Videojuego(string nombre, string genero,
               double precio, int stock);

    // Metodos constantes
    string getNombre() const;
    string getGenero() const;
    double getPrecio() const;
    int getStock() const;

    // Gestion del stock
    bool reducirStock();
    void aumentarStock();

    // Mostrar informacion
    void mostrarInfo() const;

    // Funcion inline: calcular precio con descuento
    inline double aplicarDescuento(double porcentaje) const {
        return precio - (precio * porcentaje / 100);
    }
};

#endif
