#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

void Save(struct Factura *factura)
{
    FILE *file;
    file = fopen("factura.txt", "ab+");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    else
    {
        fwrite(factura, sizeof(struct Factura), 1, file);
        printf("Factura guardada con exito\n");
    }
    fclose(file);
}

void leerCadena(char *cadena, int tam)
{
    fflush(stdin); 
    fgets(cadena, tam, stdin);
    size_t len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n')
    {
        cadena[len - 1] = '\0'; 
    }
}

void createFactura()
{
    int opcion;

    struct Factura factura;
    printf("Ingrese el nombre del cliente: ");
    leerCadena(factura.nombre, 50);
    printf("Ingrese la cedula del cliente: ");
    scanf("%d", &factura.cedula);
    getchar(); 
    printf("Ingrese la cantidad de productos: ");
    scanf("%d", &factura.cantidadProductos);
    getchar(); 
    factura.total = 0;
    for (int i = 0; i < factura.cantidadProductos; i++)
    {
        printf("Ingrese el nombre del producto %d: ", i + 1);
        leerCadena(factura.productos[i].nombre, 50);
        printf("Ingrese la cantidad del producto %d: ", i + 1);
        scanf("%d", &factura.productos[i].cantidad);
        printf("Ingrese el precio del producto %d: ", i + 1);
        scanf("%f", &factura.productos[i].precio);
        getchar(); 
        factura.total += factura.productos[i].cantidad * factura.productos[i].precio;
    }
    Save(&factura);

    printf("¿Desea imprimir su factura?\n1. Sí\n2. No\n");
    scanf("%d", &opcion);
    getchar(); 

    if (opcion == 1) {
        imprimirDetalleFactura(factura);
    }
}

void imprimirFacturas(struct Factura factura)
    {
        printf("%d\t\t%s\t\t%d\t\t%f\n", factura.cedula, factura.nombre, factura.cantidadProductos, factura.total);
    }
void imprimirDetalleFactura(struct Factura factura)
    {
        printf("Cedula: %d\n", factura.cedula);
        printf("Nombre: %s\n", factura.nombre);
        printf("Cantidad de productos: %d\n", factura.cantidadProductos);
        for (int i = 0; i < factura.cantidadProductos; i++)
        {
            printf("%s\t\t%d\t\t%f\n", factura.productos[i].nombre, factura.productos[i].cantidad, factura.productos[i].precio);
            printf("Total: %f\n", factura.total);
        }
    }

void readFacturas()
    {
        FILE *file;
        struct Factura factura;
        file = fopen("factura.txt", "rb");
        if (file == NULL)
        {
            printf("Error al abrir el archivo\n");
            exit(1);
        }
        else
        {
            printf("Cedula\tNombre\tCantidadProductos\tTotal\n");
            while (fread(&factura, sizeof(struct Factura), 1, file))
            {
                imprimirFacturas(factura);
            }
        }
        fclose(file);
        printf("Desea el detalle de una factura? 1. Si 2. No\n");
    }

int findFacturaByCedula(int cedula)
{
    FILE *file;
    struct Factura factura;
    int encontrado = 0;
    int pos = 0;

    file = fopen("factura.txt", "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return -1; 
    }

    while (fread(&factura, sizeof(struct Factura), 1, file))
    {
        if (factura.cedula == cedula)
        {
            printf("Factura encontrada:\n");
            encontrado = 1; 
            imprimirDetalleFactura(factura);

            int subopcion;
            printf("\n1. Editar la factura\n");
            printf("2. Eliminar la factura\n");
            printf("3. Regresar al menú principal\n");
            printf("Ingrese una opción: ");
            scanf("%d", &subopcion);
            getchar(); 

            switch (subopcion)
            {
            case 1:
                editFactura(cedula);
                break;
            case 2:
                deleteFactura(cedula);
                break;
            case 3:
                
                break;
            default:
                printf("Opción no válida\n");
                break;
            }

            fclose(file); 
            return 1; 
        }
        pos = ftell(file); 
    }

   
    if (!encontrado)
    {
        printf("Factura no encontrada\n");
        pos = -1; 
    }

    fclose(file);
    return pos; 
}



void editFactura(int cedula)
    {
        FILE *file;
        struct Factura factura;
        file = fopen("factura.txt", "rb+");
        if (file == NULL)
        {
            printf("Error al abrir el archivo\n");
            exit(1);
        }
        else
        {
            while (fread(&factura, sizeof(struct Factura), 1, file))
            {
                if (factura.cedula == cedula)
                {
                    printf("Ingrese el nombre del cliente: ");
                    leerCadena(factura.nombre, 20);
                    printf("Ingrese la cedula del cliente: ");
                    scanf("%d", &factura.cedula);
                    printf("Ingrese la cantidad de productos: ");
                    scanf("%d", &factura.cantidadProductos);
                    factura.total = 0;
                    for (int i = 0; i < factura.cantidadProductos; i++)
                    {
                        printf("Ingrese el nombre del producto %d: ", i + 1);
                        leerCadena(factura.productos[i].nombre, 20);
                        printf("Ingrese la cantidad del producto %d: ", i + 1);
                        scanf("%d", &factura.productos[i].cantidad);
                        printf("Ingrese el precio del producto %d: ", i + 1);
                        scanf("%f", &factura.productos[i].precio);
                        factura.total += factura.productos[i].cantidad * factura.productos[i].precio;
                    }
                    fseek(file, -sizeof(struct Factura), SEEK_CUR);
                    fwrite(&factura, sizeof(struct Factura), 1, file);
                    printf("Factura editada con exito\n");
                    break;
                }
            }
        }
        fclose(file);
    }
void deleteFactura(int cedula)
    {
        FILE *file;
        FILE *temp;
        struct Factura factura;
        file = fopen("factura.txt", "rb");
        temp = fopen("temp.txt", "wb");
        if (file == NULL)
        {
            printf("Error al abrir el archivo\n");
            exit(1);
        }
        else
        {
            while (fread(&factura, sizeof(struct Factura), 1, file))
            {
                if (factura.cedula != cedula)
                {
                    fwrite(&factura, sizeof(struct Factura), 1, temp);
                }
            }
        }
        fclose(file);
        fclose(temp);
        remove("factura.txt");
        rename("temp.txt", "factura.txt");
        printf("Factura eliminada con exito\n");
    }
