#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char nombre[50];
    float precio;
    int cantidad;
} Producto;

void agregarProducto(Producto *inventario, int *contador);
void mostrarInventario(const Producto *inventario, int contador);
void guardarInventario(const Producto *inventario, int contador);
void cargarInventario(Producto *inventario, int *contador);

int main()
{
    Producto inventario[100];
    int contador = 0;

    cargarInventario(inventario, &contador);

    int opcion;
    do
    {
        printf("1. Agregar producto\n");
        printf("2. Mostrar inventario\n");
        printf("3. Guardar y salir\n");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarProducto(inventario, &contador);
            break;
        case 2:
            mostrarInventario(inventario, contador);
            break;
        case 3:
            guardarInventario(inventario, contador);
            break;
        default:
            printf("Opción inválida.\n");
        }
    } while (opcion != 3);

    return 0;

    do
    {
        printf("\n1. Agregar producto\n");
        printf("2. Mostrar inventario\n");
        printf("3. Buscar producto\n");
        printf("4. Actualizar producto\n");
        printf("5. Eliminar producto\n");
        printf("6. Vender producto\n");
        printf("7. Recibir stock de producto\n");
        printf("8. Guardar y salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n')
            ;

        switch (opcion)
        {

        case 3:
            buscarProducto(inventario, contador);
            break;
        case 4:
            actualizarProducto(inventario, contador);
            break;
        case 5:
            eliminarProducto(inventario, &contador);
            break;
        case 6:
            venderProducto(inventario, contador);
            break;
        case 7:
            recibirStock(inventario, contador);
            break;
        case 8:
            guardarInventario(inventario, contador);
            break;
        }
    } while (opcion != 8);

    return 0;
}

void agregarProducto(Producto *inventario, int *contador)
{
    if (*contador < 100)
    {
        printf("Introduzca el ID del producto: ");
        scanf("%d", &inventario[*contador].id);
        printf("Introduzca el nombre del producto: ");
        scanf("%s", inventario[*contador].nombre);
        printf("Introduzca el precio del producto: ");
        scanf("%f", &inventario[*contador].precio);
        printf("Introduzca la cantidad del producto: ");
        scanf("%d", &inventario[*contador].cantidad);

        (*contador)++;
        printf("Producto agregado con éxito!\n");
    }
    else
    {
        printf("El inventario está lleno. No se puede agregar más productos.\n");
    }
}

void mostrarInventario(const Producto *inventario, int contador)
{
    printf("Inventario:\n");
    for (int i = 0; i < contador; i++)
    {
        printf("ID: %d\n", inventario[i].id);
        printf("Nombre: %s\n", inventario[i].nombre);
        printf("Precio: %.2f\n", inventario[i].precio);
        printf("Cantidad: %d\n\n", inventario[i].cantidad);
    }
}

void guardarInventario(const Producto *inventario, int contador)
{
    FILE *file = fopen("inventario.bin", "wb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo para escribir");
        exit(EXIT_FAILURE);
    }

    size_t itemsEscritos = fwrite(&contador, sizeof(int), 1, file);
    if (itemsEscritos < 1)
    {
        perror("Error al escribir la cantidad de productos");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    itemsEscritos = fwrite(inventario, sizeof(Producto), contador, file);
    if (itemsEscritos < (size_t)contador)
    {
        perror("Error al escribir el inventario");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void cargarInventario(Producto *inventario, int *contador)
{
    FILE *file = fopen("inventario.bin", "rb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo para leer");
        exit(EXIT_FAILURE);
    }

    size_t itemsLeidos = fread(contador, sizeof(int), 1, file);
    if (itemsLeidos < 1)
    {
        perror("Error al leer la cantidad de productos");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    itemsLeidos = fread(inventario, sizeof(Producto), *contador, file);
    if (itemsLeidos < (size_t)*contador)
    {
        perror("Error al leer el inventario");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void buscarProducto(const Producto *inventario, int contador)
{
    int opcionBusqueda;
    printf("Buscar por: 1) ID, 2) Nombre, 3) Rango de precios: ");
    scanf("%d", &opcionBusqueda);

    switch (opcionBusqueda)
    {
    case 1:
    {
        int id;
        printf("Introduzca el ID del producto: ");
        scanf("%d", &id);
        for (int i = 0; i < contador; i++)
        {
            if (inventario[i].id == id)
            {
                mostrarProducto(inventario[i]);
                return;
            }
        }
        printf("Producto no encontrado.\n");
        break;
    }
    case 2:
    {
        char nombreBusqueda[50];
        printf("Introduzca el nombre del producto: ");
        scanf("%s", nombreBusqueda);
        for (int i = 0; i < contador; i++)
        {
            if (strcmp(inventario[i].nombre, nombreBusqueda) == 0)
            {
                mostrarProducto(inventario[i]);
                return;
            }
        }
        printf("Producto no encontrado.\n");
        break;
    }
    case 3:
    {
        float precioMin, precioMax;
        printf("Introduzca el rango de precios: \n");
        printf("Precio mínimo: ");
        scanf("%f", &precioMin);
        printf("Precio máximo: ");
        scanf("%f", &precioMax);
        for (int i = 0; i < contador; i++)
        {
            if (inventario[i].precio >= precioMin && inventario[i].precio <= precioMax)
            {
                mostrarProducto(inventario[i]);
            }
        }
        break;
    }
    default:
        printf("Opción de búsqueda no válida.\n");
    }
}

void mostrarProducto(Producto p)
{
    printf("ID: %d\n", p.id);
    printf("Nombre: %s\n", p.nombre);
    printf("Precio: %.2f\n", p.precio);
    printf("Cantidad: %d\n", p.cantidad);
}

void actualizarProducto(Producto *inventario, int contador)
{
    int id;
    printf("Introduzca el ID del producto a actualizar: ");
    scanf("%d", &id);
    for (int i = 0; i < contador; i++)
    {
        if (inventario[i].id == id)
        {
            printf("Introduzca el nuevo nombre del producto: ");
            scanf("%s", inventario[i].nombre);
            printf("Introduzca el nuevo precio del producto: ");
            scanf("%f", &inventario[i].precio);
            printf("Introduzca la nueva cantidad del producto: ");
            scanf("%d", &inventario[i].cantidad);
            printf("Producto actualizado con éxito.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void eliminarProducto(Producto *inventario, int *contador)
{
    int id;
    printf("Introduzca el ID del producto a eliminar: ");
    scanf("%d", &id);
    for (int i = 0; i < *contador; i++)
    {
        if (inventario[i].id == id)
        {
            for (int j = i; j < *contador - 1; j++)
            {
                inventario[j] = inventario[j + 1];
            }
            (*contador)--;
            printf("Producto eliminado con éxito.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void venderProducto(Producto *inventario, int contador)
{
    int id, cantidadVendida;
    printf("Introduzca el ID del producto vendido: ");
    scanf("%d", &id);
    printf("Introduzca la cantidad vendida: ");
    scanf("%d", &cantidadVendida);
    for (int i = 0; i < contador; i++)
    {
        if (inventario[i].id == id)
        {
            if (inventario[i].cantidad >= cantidadVendida)
            {
                inventario[i].cantidad -= cantidadVendida;
                printf("Venta realizada con éxito.\n");
                return;
            }
            else
            {
                printf("No hay suficiente stock para la venta.\n");
                return;
            }
        }
    }
    printf("Producto no encontrado.\n");
}

void recibirStock(Producto *inventario, int contador)
{
    int id, cantidadRecibida;
    printf("Introduzca el ID del producto que recibe stock: ");
    scanf("%d", &id);
    printf("Introduzca la cantidad recibida: ");
    scanf("%d", &cantidadRecibida);
    for (int i = 0; i < contador; i++)
    {
        if (inventario[i].id == id)
        {
            inventario[i].cantidad += cantidadRecibida;
            printf("Stock actualizado con éxito.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}
