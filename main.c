#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100

typedef struct {
    int id;
    char nombre[50];
    int stock;
    float precio;
    float ganancias;
} Producto;

Producto productos[MAX_PRODUCTOS];
int total_productos = 0;

// Verifica si el ID existe
int existeID(int id) {
    for (int i = 0; i < total_productos; i++) {
        if (productos[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Registra un nuevo producto
void registrarProducto() {
    if (total_productos >= MAX_PRODUCTOS) {
        printf("\n*No se pueden registrar más productos.\n");
        return;
    }

    Producto nuevo_producto;
    char entrada[10];

    do {
        printf("\nIngrese ID del producto: ");
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &nuevo_producto.id) != 1) {
            printf("\n*Entrada inválida. Intente nuevamente.\n");
            continue;
        }
        if (existeID(nuevo_producto.id) != -1) {
            printf("\n*El ID ya existe. Intente con otro.\n");
        }
    } while (existeID(nuevo_producto.id) != -1);

    printf("\nIngrese nombre del producto: ");
    fgets(nuevo_producto.nombre, 50, stdin);
    nuevo_producto.nombre[strcspn(nuevo_producto.nombre, "\n")] = '\0'; // Elimina salto de línea

    do {
        printf("\nIngrese stock inicial: ");
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &nuevo_producto.stock) != 1 || nuevo_producto.stock < 0) {
            printf("\n*Stock inválido. Debe ser un número entero positivo.\n");
        }
    } while (nuevo_producto.stock < 0);

    do {
        printf("\nIngrese precio unitario: ");
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%f", &nuevo_producto.precio) != 1 || nuevo_producto.precio < 0) {
            printf("\n*Precio inválido. Intente nuevamente.\n");
        }
    } while (nuevo_producto.precio < 0);

    nuevo_producto.ganancias = 0.0;
    productos[total_productos++] = nuevo_producto;
    printf("\n*Producto registrado con éxito.\n");
}

// Vender producto
void venderProducto() {
    int id, cantidad, indice;
    char entrada[10];

    printf("\nIngrese el ID del producto a vender: ");
    fgets(entrada, sizeof(entrada), stdin);
    if (sscanf(entrada, "%d", &id) != 1) {
        printf("\n*Entrada inválida.\n");
        return;
    }

    indice = existeID(id);
    if (indice == -1) {
        printf("\n*El producto no existe.\n");
        return;
    }

    printf("\nIngrese la cantidad a vender: ");
    fgets(entrada, sizeof(entrada), stdin);
    if (sscanf(entrada, "%d", &cantidad) != 1 || cantidad <= 0) {
        printf("\n*Entrada inválida. Intente nuevamente.\n");
        return;
    }

    if (cantidad > productos[indice].stock) {
        printf("\n*Stock insuficiente.\n");
    } else {
        productos[indice].stock -= cantidad;
        productos[indice].ganancias += cantidad * productos[indice].precio;
        printf("\n*Venta realizada con éxito.\n");
    }
}

// Reabastecer producto
void reabastecerProducto() {
    int id, cantidad, indice;
    char entrada[10];

    printf("\nIngrese el ID del producto a reabastecer: ");
    fgets(entrada, sizeof(entrada), stdin);
    if (sscanf(entrada, "%d", &id) != 1) {
        printf("\n*Entrada inválida.\n");
        return;
    }

    indice = existeID(id);
    if (indice == -1) {
        printf("\n*El producto no existe.\n");
        return;
    }

    do {
        printf("\nIngrese la cantidad a agregar al stock: ");
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &cantidad) != 1 || cantidad <= 0) {
            printf("\n*Entrada inválida. Intente nuevamente.\n");
        }
    } while (cantidad <= 0);

    productos[indice].stock += cantidad;
    printf("\n*Stock actualizado con éxito.\n");
}

// Consultar productos
void consultarProductos() {
    if (total_productos == 0) {
        printf("\n*No hay productos registrados.\n");
        return;
    }

    for (int i = 0; i < total_productos; i++) {
        printf("\n--- Producto %d ---\n", i + 1);
        printf("ID: %d | Nombre: %s | Stock: %d | Precio: $%.2f | Ganancias: $%.2f\n",
               productos[i].id, productos[i].nombre, productos[i].stock,
               productos[i].precio, productos[i].ganancias);
    }
}

// Menú principal
int main() {
    int opcion;
    char entrada[10]; // Para capturar la entrada del usuario como texto

    do {
        printf("\n---- Gestión de Productos ----\n");
        printf("1. Registrar Producto\n");
        printf("2. Vender Producto\n");
        printf("3. Reabastecer Producto\n");
        printf("4. Consultar Productos\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        fgets(entrada, sizeof(entrada), stdin);

        if (sscanf(entrada, "%d", &opcion) != 1) {
            printf("\n*Entrada inválida. Intente nuevamente.\n");
            continue;
        }

        switch (opcion) {
            case 1:
                registrarProducto();
                break;
            case 2:
                venderProducto();
                break;
            case 3:
                reabastecerProducto();
                break;
            case 4:
                consultarProductos();
                break;
            case 5:
                printf("\n*Saliendo...\n");
                break;
            default:
                printf("\n*Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}