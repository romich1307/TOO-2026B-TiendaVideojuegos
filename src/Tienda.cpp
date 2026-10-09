#include "../include/Tienda.h"
#include <iostream>

using namespace std;

Tienda::Tienda() : cliente("Jugador", 500.0) {
    catalogo.push_back(Videojuego("Minecraft", "Sandbox", 89.90, 10));
    catalogo.push_back(Videojuego("Stardew Valley", "Simulacion", 39.90, 8));
    catalogo.push_back(Videojuego("Hollow Knight", "Metroidvania", 45.00, 5));
    catalogo.push_back(Videojuego("FIFA", "Deportes", 199.90, 6));
    catalogo.push_back(Videojuego("Cuphead", "Accion", 55.00, 4));
}

void Tienda::agregarVideojuego(const Videojuego& juego) {
    catalogo.push_back(juego);
}

void Tienda::mostrarCatalogo() const {
    cout << "\n===== CATALOGO DE VIDEOJUEGOS =====\n";

    if (catalogo.empty()) {
        cout << "No hay videojuegos disponibles.\n";
        return;
    }

    for (int i = 0; i < catalogo.size(); i++) {
        cout << "\n[" << i + 1 << "] ";
        catalogo[i].mostrarInfo();
    }
}

int Tienda::buscarPorNombre(const string& nombre) const {
    for (int i = 0; i < catalogo.size(); i++) {
        if (catalogo[i].getNombre() == nombre) {
            return i;
        }
    }

    return -1;
}

void Tienda::filtrarPorGenero(const string& genero) const {
    cout << "\n===== FILTRO POR GENERO =====\n";

    auto cumple = [&genero](const Videojuego& videojuego) {
        return videojuego.getGenero() == genero;
    };

    bool encontrado = false;

    for (int i = 0; i < catalogo.size(); i++) {
        if (cumple(catalogo[i])) {
            catalogo[i].mostrarInfo();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron videojuegos de ese genero.\n";
    }
}

void Tienda::filtrarPorPrecio(double precioMaximo) const {
    cout << "\n===== FILTRO POR PRECIO =====\n";

    auto cumple = [precioMaximo](const Videojuego& videojuego) {
        return videojuego.getPrecio() <= precioMaximo;
    };

    bool encontrado = false;

    for (int i = 0; i < catalogo.size(); i++) {
        if (cumple(catalogo[i])) {
            catalogo[i].mostrarInfo();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron videojuegos dentro de ese precio.\n";
    }
}

void Tienda::finalizarCompra() {
    // Guardar los productos antes de vaciar el carrito.
    vector<Videojuego> productos = cliente.getCarrito().getProductos();

    if (productos.empty()) {
        cout << "El carrito esta vacio.\n";
        return;
    }

    // Comprobar que haya stock suficiente.
    for (int i = 0; i < productos.size(); i++) {
        int posicion = buscarPorNombre(productos[i].getNombre());

        if (posicion == -1) {
            cout << "El videojuego " << productos[i].getNombre()
                 << " ya no esta en el catalogo.\n";
            return;
        }

        int cantidad = 0;

        for (int j = 0; j < productos.size(); j++) {
            if (productos[j].getNombre() == productos[i].getNombre()) {
                cantidad++;
            }
        }

        if (catalogo[posicion].getStock() < cantidad) {
            cout << "No hay stock suficiente de "
                 << productos[i].getNombre() << ".\n";
            return;
        }
    }

    // El cliente realiza el pago si tiene saldo suficiente.
    if (cliente.finalizarCompra()) {
        // Descontar del catálogo las unidades compradas.
        for (int i = 0; i < productos.size(); i++) {
            int posicion = buscarPorNombre(productos[i].getNombre());
            catalogo[posicion].reducirStock();
        }
    }
}

void Tienda::ejecutar() {
    int opcion;

    do {
        cout << "\n========== TIENDA DE VIDEOJUEGOS ==========\n";
        cout << "Cliente: " << cliente.getNombre() << "\n";
        cout << "Saldo: S/ " << cliente.getSaldo() << "\n";
        cout << "1. Mostrar catalogo\n";
        cout << "2. Buscar videojuego\n";
        cout << "3. Filtrar por genero\n";
        cout << "4. Filtrar por precio\n";
        cout << "5. Agregar al carrito\n";
        cout << "6. Quitar del carrito\n";
        cout << "7. Mostrar carrito\n";
        cout << "8. Vaciar carrito\n";
        cout << "9. Finalizar compra\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            mostrarCatalogo();
        }
        else if (opcion == 2) {
            string nombre;

            cin.ignore();
            cout << "Nombre del videojuego: ";
            getline(cin, nombre);

            int posicion = buscarPorNombre(nombre);

            if (posicion != -1) {
                catalogo[posicion].mostrarInfo();
            }
            else {
                cout << "Videojuego no encontrado.\n";
            }
        }
        else if (opcion == 3) {
            string genero;

            cin.ignore();
            cout << "Ingrese el genero: ";
            getline(cin, genero);

            filtrarPorGenero(genero);
        }
        else if (opcion == 4) {
            double precioMaximo;

            cout << "Ingrese el precio maximo: ";
            cin >> precioMaximo;

            if (precioMaximo >= 0) {
                filtrarPorPrecio(precioMaximo);
            }
            else {
                cout << "Ingrese un precio valido.\n";
            }
        }
        else if (opcion == 5) {
            mostrarCatalogo();

            if (catalogo.empty()) {
                continue;
            }

            int numero;

            cout << "\nIngrese el numero del videojuego: ";
            cin >> numero;

            if (numero < 1 || numero > catalogo.size()) {
                cout << "Numero fuera del catalogo.\n";
                continue;
            }

            Videojuego juego = catalogo[numero - 1];

            if (juego.getStock() <= 0) {
                cout << "Este videojuego no tiene stock disponible.\n";
                continue;
            }

            int cantidadEnCarrito = 0;
            const vector<Videojuego>& productos =
                cliente.getCarrito().getProductos();

            for (int i = 0; i < productos.size(); i++) {
                if (productos[i].getNombre() == juego.getNombre()) {
                    cantidadEnCarrito++;
                }
            }

            if (cantidadEnCarrito >= juego.getStock()) {
                cout << "No puedes agregar mas unidades de este videojuego.\n";
                continue;
            }

            cliente.agregarAlCarrito(juego);
            cout << "Videojuego agregado al carrito.\n";
        }
        else if (opcion == 6) {
            string nombre;

            cin.ignore();
            cout << "Nombre del videojuego que desea quitar: ";
            getline(cin, nombre);

            int posicion = buscarPorNombre(nombre);

            if (posicion != -1) {
                cliente.quitarDelCarrito(catalogo[posicion]);
            }
            else {
                cout << "Videojuego no encontrado en el catalogo.\n";
            }
        }
        else if (opcion == 7) {
            cliente.getCarrito().mostrarCarrito();
        }
        else if (opcion == 8) {
            cliente.vaciarCarrito();
            cout << "Carrito vaciado.\n";
        }
        else if (opcion == 9) {
            finalizarCompra();
        }
        else if (opcion == 0) {
            cout << "Gracias por visitar la tienda.\n";
        }
        else {
            cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);
}
