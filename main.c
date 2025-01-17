#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main()
{
    int opcion;
    do
    {
        printf("1. Crear factura\n");
        printf("2. Ver facturas\n");
        printf("3. Buscar factura por cedula\n");
        printf("4. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar();
        switch (opcion)
        {
        case 1:
            createFactura();
            break;
        case 2:
            readFacturas();
            break;
        case 3:
        {
            int cedula;
            printf("Ingrese la cedula: ");
            scanf("%d", &cedula);
            getchar();
            if (!findFacturaByCedula(cedula))
            {
                printf("Factura no encontrada\n");
            }
            break;
        }
        case 4:
            printf("Saliendo del programa\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 4);
    return 0;
}
