
#include "../include/Videojuego.h"
#include <iostream>
using namespace std;

// Constructor
Videojuego::Videojuego(string nombre, string genero,
                       double precio, int stock) {
    this->nombre = nombre;
    this->genero = genero;
    this->precio = precio;
    this->stock = stock;
}

// Obtener nombre
string Videojuego::getNombre() const {
    return nombre;
}

// Obtener genero
string Videojuego::getGenero() const {
    return genero;
}

// Obtener precio
double Videojuego::getPrecio() const {
    return precio;
}

// Obtener stock
int Videojuego::getStock() const {
    return stock;
}

// Reducir stock en una unidad
bool Videojuego::reducirStock() {
    if (stock > 0) {
        stock--;
        return true;
    }

    return false;
}

// Aumentar stock en una unidad
void Videojuego::aumentarStock() {
    stock++;
}

// Mostrar datos del videojuego
void Videojuego::mostrarInfo() const {
    cout << "Nombre: " << nombre << endl;
    cout << "Genero: " << genero << endl;
    cout << "Precio: S/ " << precio << endl;
    cout << "Stock: " << stock << endl;
    cout << "------------------------" << endl;
}
